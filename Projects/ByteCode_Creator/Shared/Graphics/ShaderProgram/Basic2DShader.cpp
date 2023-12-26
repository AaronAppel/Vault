#include "Graphics\SetupGraphics.h"

std::string ShaderFactory::Basic2DShaderVert(std::string vertString)
{
	/* Header */
	vertString.append("// Basic2D.vert");
	// SetVersion(vertString);

	// input
	AddAttributeVec3("Position", vertString);

	// output

	/* Body */
	OpenMain(vertString);

	vertString.append("\ngl_Position = vec4(a_Position, 1.0);");

	CloseMain(vertString);
	OutputMessage("%s\n", vertString.c_str());
	return vertString;
}

std::string ShaderFactory::Basic2DShaderFrag(std::string fragString)
{
	/* Header */
	fragString.append("// Basic2D.frag");
	// SetVersion(fragString);

	//input

	// output

	/* Body */
	OpenMain(fragString); // end header / begin body
	fragString.append("\ngl_FragColor = vec4(1,1,1,1);");

	CloseMain(fragString);
	OutputMessage("%s\n", fragString.c_str());
	return fragString;
}