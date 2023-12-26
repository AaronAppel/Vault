#include "Graphics\SetupGraphics.h"

#include <assert.h>

ShaderProgram::ShaderProgram()
{
	m_Factory = new ShaderFactory();
	m_Factory->SetPrefixes(DeepCopyString(blue_GetAttributePrefix()),
		DeepCopyString(blue_GetUniformPrefix()),
		DeepCopyString(blue_GetTransferPrefix()));
}

ShaderProgram::~ShaderProgram()
{
	CleanUp();
	delete m_Factory;
}

bool ShaderProgram::Init(eShaderTypes type)
{
	m_VertString = m_Factory->CreateVertexShader(type);
	m_FragString = m_Factory->CreateFragmentShader(type);
	// m_GeoString = m_Factory->CreateGeometryShader(type);
	return Init(NULL, NULL, NULL);
}

bool ShaderProgram::Init(const char* vertFileDir, const char* fragFileDir, const char* geoFileDir)
{
	// TODO: Handle geometry shader creation
	if (m_VertString == 0 || m_FragString == 0)
	{
		// load strings
		m_VertString = LoadCompleteFile(vertFileDir, 0);
		m_FragString = LoadCompleteFile(fragFileDir, 0);
		// m_GeoString = LoadCompleteFile(geoFile, 0);
	}
	else
	{
		// loaded by ShaderFactory
	}

	if (m_VertString == 0 || m_FragString == 0) // check if STILL null strings
	{
		assert(0); // DEBUG:
		return false;
	}

	// compile shaders
	m_VertShaderHandle = CompileShader(GL_VERTEX_SHADER, m_VertString);
	m_FragShaderHandle = CompileShader(GL_FRAGMENT_SHADER, m_FragString);
	// m_FragShaderHandle = CompileShader(GL_GEOMETRY_SHADER, m_GeoString);

	if (m_VertShaderHandle == 0 || m_FragShaderHandle == 0) // check if null handles
	{
		CleanUp(); // deallocate memory
		assert(0); // DEBUG:
		return false;
	}

	// link shaders
	m_ProgramHandle = LinkShaders(m_VertShaderHandle, m_FragShaderHandle, NULL);
	if (m_ProgramHandle == 0) { return false; } // check if null program

	// Populate shader variables lists
	SetupAttributeList();
	SetupUniformList();

	return true;
}

void ShaderProgram::CleanUp()
{
	if (m_VertString)
		delete[] m_VertString;
	if (m_FragString)
		delete[] m_FragString;
	if (m_GeoString)
		delete[] m_GeoString;

	glDetachShader(m_ProgramHandle, m_VertShaderHandle);
	glDetachShader(m_ProgramHandle, m_FragShaderHandle);
	//glDetachShader(m_ProgramHandle, m_GeoShaderHandle); // TODO:

	if (m_VertShaderHandle)
		glDeleteShader(m_VertShaderHandle);
	if (m_FragShaderHandle)
		glDeleteShader(m_FragShaderHandle);
	if (m_GeoShaderHandle)
		glDeleteShader(m_GeoShaderHandle);
	if (m_ProgramHandle)
		glDeleteProgram(m_ProgramHandle);

	m_VertString = 0;
	m_FragString = 0;
	m_GeoString = 0;

	m_VertShaderHandle = 0;
	m_FragShaderHandle = 0;
	m_GeoShaderHandle = 0;
	m_ProgramHandle = 0;
}
// Returns new shader handle is successful, else 0
GLuint ShaderProgram::CompileShader(GLenum shaderType, const char* shaderString)
{
	GLuint shaderHandle = glCreateShader(shaderType);
	glShaderSource(shaderHandle, 1, &shaderString, NULL);
	glCompileShader(shaderHandle);

	GLint success = 0;
	glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		// Error compiling shader
		GLchar infoLog[512];
		glGetShaderInfoLog(shaderHandle, 512, NULL, infoLog);

		char* shaderTypeString = "";
		if (shaderType == GL_VERTEX_SHADER)
			shaderTypeString = (char*)"GL_VERTEX_SHADER";
		else if (shaderType == GL_FRAGMENT_SHADER)
			shaderTypeString = (char*)"GL_FRAGMENT_SHADER";
		else if (shaderType == GL_GEOMETRY_SHADER)
			shaderTypeString = (char*)"GL_GEOMETRY_SHADER";

		char* next_token = 0;
		char* ShaderName = strtok_s((char*)shaderString, "\n", &next_token);
		OutputMessage("\n%s: ShaderProgram: CompileShader() %s compile error-> ", ShaderName, shaderTypeString);
		OutputMessage(infoLog); // OpenGL message

		// cleanup
		glDeleteShader(shaderHandle);
		shaderHandle = 0;
	}

	return shaderHandle;
}
// Returns new shader handle is successful, else 0
GLuint ShaderProgram::ReCompileShader(GLenum shaderType, const char* shaderString)
{
	GLuint result = 0;
	result = CompileShader(shaderType, shaderString);

	if (result > 0)
	{ // Success
		// re-link shaders
		result = LinkShaders(m_ProgramHandle, m_VertShaderHandle, m_FragShaderHandle);
		if (result > 0)
		{
			OutputMessage("ReCompileShader(): Success recompiling %s. Changes saved.\n", shaderString);
			if (shaderType == GL_VERTEX_SHADER) { m_VertShaderHandle = result; }
			if (shaderType == GL_FRAGMENT_SHADER) { m_FragShaderHandle = result; }
			if (shaderType == GL_GEOMETRY_SHADER) { m_GeoShaderHandle = result; }
			m_ProgramHandle = result; // update program handle
		}
		else
		{
			OutputMessage("ReCompileShader(): Error relinking %s. Changes saved.\n", shaderString);
		}
		// TODO: unlink shaders
	}
	else
	{
		OutputMessage("ReCompileShader(): Error recompiling %s. No changes were made.\n", shaderString);
		// TODO: unlink shaders
		glDeleteShader(result);
	}

	return result;
}
// Returns new program handle is successful, else 0
GLuint ShaderProgram::LinkShaders(GLuint vert, GLuint frag, GLuint geo)
{
	GLuint result = 0;
	result = glCreateProgram(); // create new program

	glAttachShader(result, vert); // link vertex shader
	glAttachShader(result, frag); // link fragment shader
	// glAttachShader(result, geo); // link geometry shader

	glLinkProgram(result);
	/*
	GL_INVALID_VALUE is generated if program is not a value generated by OpenGL.
	GL_INVALID_OPERATION is generated if program is not a program object.
	GL_INVALID_OPERATION is generated if program is the currently active program object and transform feedback mode is active.
	*/

	GLint success;
	glGetProgramiv(result, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512];
		glGetProgramInfoLog(result, 512, NULL, infoLog);
		OutputMessage("\nShaderProgram: LinkShaders() linking error-> ");
		OutputMessage(infoLog); // OpenGL message

		CleanUp(); // deallocate memory
		return false;
	}

	glDeleteShader(vert); // no longer needed
	glDeleteShader(frag);
	// glDeleteShader(geo);

	return result;
}
/* Texture setup */
void ShaderProgram::SetupTextures(GLuint textures[], int numTextures)
{
	for (int i = 0; i < numTextures; i++)
	{
		std::string id = "Texture";
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textures[i]);
		id.append(std::to_string(i));
		this->SetUniformInt1(id.c_str(), i);
	}
}
/* Uniform value assignment */
// int
void ShaderProgram::SetUniformInt1(const char* name, int value)
{
	glUniform1i(glGetUniformLocation(m_ProgramHandle, name), value);
}
void ShaderProgram::SetUniformInt2(const char* name, int value1, int value2)
{
	glUniform2i(glGetUniformLocation(m_ProgramHandle, name), value1, value2);
}
void ShaderProgram::SetUniformInt3(const char* name, int value1, int value2, int value3)
{
	glUniform3i(glGetUniformLocation(m_ProgramHandle, name), value1, value2, value3);
}
void ShaderProgram::SetUniformInt4(const char* name, int value1, int value2, int value3, int value4)
{
	glUniform4i(glGetUniformLocation(m_ProgramHandle, name), value1, value2, value3, value4);
}
// float
void ShaderProgram::SetUniformFloat1(const char* name, float value)
{
	glUniform1f(glGetUniformLocation(m_ProgramHandle, name), value);
}
void ShaderProgram::SetUniformFloat2(const char* name, float value1, float value2)
{
	glUniform2f(glGetUniformLocation(m_ProgramHandle, name), value1, value2);
}
void ShaderProgram::SetUniformFloat3(const char* name, float value1, float value2, float value3)
{
	glUniform3f(glGetUniformLocation(m_ProgramHandle, name), value1, value2, value3);
}
void ShaderProgram::SetUniformFloat4(const char* name, float value1, float value2, float value3, float value4)
{
	glUniform4f(glGetUniformLocation(m_ProgramHandle, name), value1, value2, value3, value4);
}
// matrix
void ShaderProgram::SetUniformMat4(const char* name, const GLfloat* matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(m_ProgramHandle, name), 1, GL_FALSE, matrix);
}
// Private functions
void ShaderProgram::SetupAttributeList()
{
	// TODO: Handle "in" and "attribute"
	if (m_VertString == 0)
	{
		return;
	}
	// store string in temp buffer
	char* buffer = (char*)DeepCopyString(m_VertString); // Delete buffer when done

	// store lines in std::vector
	char* next_token = 0;
	char* line = strtok_s(buffer, "\n", &next_token);

	std::vector<std::string> vertStringList;

	while (line)
	{
		//OutputMessage("%s\n", line);
		vertStringList.push_back(line);
		line = strtok_s(0, "\n", &next_token);
	}
	delete[] buffer; // cleanup

	/* Populate .vert attributes */
	// vert
	for (uint i = 0; i < vertStringList.size(); i++) // stringList.size() = number of lines in file
	{
		std::string loopString = vertStringList.at(i);
		if (loopString.at(0) == 'i' && loopString.find("in") != loopString.npos) // starts with 'i' and has "in" in line
		{
			uint size = 20;
			std::string t_Variable;
			sscanf_s((char*)loopString.c_str(), "%*s %*s %s", (char*)t_Variable.c_str(), size);
			strtok_s((char*)t_Variable.c_str(), ";", &next_token); // remove ';' from end

			std::string loopString;
			int counter = 2; // remove 'u_' from beginning
			while (t_Variable[counter] != '\0')
			{
				loopString.push_back(t_Variable[counter]);
				counter++;
			}

			m_AttributeList.push_back(loopString);
		}
		// duplicates caught in .vert by compiler
	}
}
void ShaderProgram::SetupUniformList()
{
	if (m_VertString == 0 || m_FragString == 0)
	{
		return;
	}
	// vert
	// store string in temp buffer
	char* buffer = (char*)DeepCopyString(m_VertString);

	// store lines in std::vector
	char* next_token = 0;
	char* line = strtok_s(buffer, "\n", &next_token);

	std::vector<std::string> vertStringList;
	std::vector<std::string> fragStringList;

	while (line)
	{
		//OutputMessage("%s\n", line);
		vertStringList.push_back(line);
		line = strtok_s(0, "\n", &next_token);
	}
	delete[] buffer; // cleanup

	// frag
	buffer = (char*)DeepCopyString(m_FragString);
	line = strtok_s(buffer, "\n", &next_token);

	while (line)
	{
		//OutputMessage("%s\n", line);
		fragStringList.push_back(line);
		line = strtok_s(0, "\n", &next_token);
	}
	delete[] buffer; // cleanup

	/* Populate .vert uniforms */
	// VERTEX
	for (uint i = 0; i < vertStringList.size(); i++) // stringList.size() = number of lines in file
	{
		std::string loopString = vertStringList.at(i);
		if (loopString.at(0) == 'u' && loopString.find("uniform") != loopString.npos) // starts with 'u' and has uniform in line
		{
			uint size = 20;
			std::string t_Variable;
			sscanf_s((char*)loopString.c_str(), "%*s %*s %s", (char*)t_Variable.c_str(), size);
			strtok_s((char*)t_Variable.c_str(), ";", &next_token); // remove ';' from end

			std::string loopString;
			int counter = 2; // remove 'u_' from beginning
			while (t_Variable[counter] != '\0')
			{
				loopString.push_back(t_Variable[counter]);
				counter++;
			}
			m_UniformList.push_back(loopString);
		}
		// duplicates caught in .vert by compiler
	}
	// FRAGMENT
	/* Populate .frag uniforms */
	for (uint i = 0; i < fragStringList.size(); i++) // stringList.size() = number of lines in file
	{
		std::string loopString = fragStringList.at(i);
		if (loopString.at(0) == 'u' && loopString.find("uniform") != loopString.npos)
		{
			uint size = 20;
			std::string t_Variable;
			sscanf_s((char*)loopString.c_str(), "%*s %*s %s", (char*)t_Variable.c_str(), size);
			strtok_s((char*)t_Variable.c_str(), ";", &next_token); // remove ';' from end

			std::string loopString;
			int counter = 2; // remove 'u_' from beginning
			while (t_Variable[counter] != '\0')
			{
				loopString.push_back(t_Variable[counter]);
				counter++;
			}
			for (uint i = 0; i < m_UniformList.size(); i++) // check for duplicates
			{
				if (StringCompare(loopString.c_str(), m_UniformList.at(i)))
				{
					int bp = 1; // duplicate
				}
				else
				{
					m_UniformList.push_back(loopString);
					break;
				}
			}
		}
	}
}