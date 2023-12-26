#include "Graphics\SetupGraphics.h"

// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-5-a-textured-cube/

// OpenGLHelpers.cpp
void CheckforGLErrors()
{
	GLenum error = glGetError();
	if (error != 0)
		OutputMessage("\nglGetError: %i-> ", error);
	if (error == GL_INVALID_VALUE)
		OutputMessage("Invalid value used.", error);
	if (error == GL_INVALID_OPERATION)
		OutputMessage("Invalid operation.", error);
}

void CheckforGLErrors(char* file, int line)
{
	GLenum error = glGetError();
	if (error != 0)
		OutputMessage("\nglGetError: Error caught in file %s, line %i -> ", file, line);
	if (error == GL_INVALID_VALUE)
		OutputMessage("Invalid value. Can't find value.", error);
	if (error == GL_INVALID_OPERATION)
		OutputMessage("Invalid operation.", error);
}

void CheckforGLErrors(const char* file, int line)
{
	GLenum error = glGetError();
	if (error != 0)
		OutputMessage("\nglGetError: Error caught in file %s, line %i -> ", file, line);
	if (error == GL_INVALID_VALUE)
		OutputMessage("Invalid value. Can't find value.", error);
	if (error == GL_INVALID_OPERATION)
		OutputMessage("Invalid operation.", error);
}

GLuint Load2DTexture(const char* filename, bool flipVertically)
{
    unsigned char* pngbuffer = 0;
    unsigned int width, height;
    long filesize;
    unsigned int result = -1;

    // buffer file data
    unsigned char* filebuffer = (unsigned char*)LoadCompleteFile(filename, &filesize);

    if (filebuffer != NULL) // decode file data
    {
        result = lodepng_decode32(&pngbuffer, &width, &height, filebuffer, filesize);
    }

    if (flipVertically)
    {
        Flip32BitImageVertically(pngbuffer, width, height);
    }

    if (result != 0) // error decoding image data
    {
        OutputMessage("LoadTexture(): Error loading image: %s\n", filename);
        free(pngbuffer);
        delete[] filebuffer;
        return 0; // exit
    }

    GLuint texhandle = 0;
    glGenTextures(1, &texhandle);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texhandle);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pngbuffer);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    // glGenerateMipmap(GL_TEXTURE_2D); // Create mipmap

    glBindTexture(GL_TEXTURE_2D, 0);

    // cleanup
    free(pngbuffer);
    delete[] filebuffer;
    return texhandle;
}

char* blue_GetAttributePrefix()
{
    return (char*)"a_"; // for attributes or i_ for inputs
}

char* blue_GetUniformPrefix()
{
    return (char*)"u_"; // uniforms
}

char* blue_GetTransferPrefix()
{
    return (char*)"t_"; // for transfers or v_ for varyings
}