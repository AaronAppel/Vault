#ifndef __ShaderProgram_H__
#define __ShaderProgram_H__

class ShaderFactory;

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();

	/* Setup */
	bool Init(eShaderTypes type);
	bool Init(const char* vertFileDir, const char* fragFileDir, const char* geoFileDir = 0);
	GLuint ReCompileShader(GLenum shaderType, const char* shaderString);

	/* Utility */
	void Use() { glUseProgram(m_ProgramHandle); };
	void CleanUp();

	/* Getters + Setters */
	// Getters
	GLuint GetProgram() { return m_ProgramHandle; };

	/* Texture setup */
	void SetupTextures(GLuint textures[], int numTextures);

	/* uniform value assignment */
	// int
	void SetUniformInt1(const char* name, int value);
	void SetUniformInt2(const char* name, int value1, int value2);
	void SetUniformInt3(const char* name, int value1, int value2, int value3);
	void SetUniformInt4(const char* name, int value1, int value2, int value3, int value4);
	// float
	void SetUniformFloat1(const char* name, float value);
	void SetUniformFloat2(const char* name, float value1, float value2);
	void SetUniformFloat3(const char* name, float value1, float value2, float value3);
	void SetUniformFloat4(const char* name, float value1, float value2, float value3, float value4);
	// matrices
	void SetUniformMat4(const char* name, const GLfloat* matrix);

	// uniform list
	std::vector<std::string> GetAttributeList() { return m_AttributeList; };
	std::vector<std::string> GetUniformList() { return m_UniformList; };
	void SetUniformList(std::vector<std::string> list) { m_UniformList = list; };

private:
	/* Variables */
	const char* m_VertString = 0;
	const char* m_FragString = 0;
	const char* m_GeoString = 0;

	// TODO: Add geometry shader
	GLuint m_VertShaderHandle = 0;
	GLuint m_FragShaderHandle = 0;
	GLuint m_GeoShaderHandle = 0;
	GLuint m_ProgramHandle = 0;

	/* Functionality */
	GLuint CompileShader(GLenum shaderType, const char* shaderString);
	GLuint LinkShaders(GLuint vert, GLuint frag, GLuint geo);

	ShaderFactory* m_Factory; // Necessary?

	void SetupAttributeList(); // TODO:: Parse m_VertString and m_FragString for all attributes and store them in m_AttributesList
	void SetupUniformList(); // TODO:: Parse shaderstrings and m_FragString for all uniforms and store them in m_UniformList
	std::vector<std::string> m_AttributeList; // Shader->SetupAttributes() sets up values. Mesh->SetupShaderAttributes() uses the list to enable vertex array data.
	std::vector<std::string> m_UniformList; // GameObject->RenderRoutine->Draw() sets values
};

#endif //__ShaderProgram_H__
