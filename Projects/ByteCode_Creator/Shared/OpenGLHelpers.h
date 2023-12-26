#ifndef __OpenGLHelpers_H_
#define __OpenGLHelpers_H_

#include "../Libraries/glew/GL/glew.h"

void CheckforGLErrors();
void CheckforGLErrors(char* file, int line);
void CheckforGLErrors(const char* file, int line);

GLuint Load2DTexture(const char* filename, bool flipVertically);

char* blue_GetAttributePrefix(); // #TODO Deprecate old methods and naming
char* blue_GetUniformPrefix();
char* blue_GetTransferPrefix();

#endif // __OpenGLHelpers_H_