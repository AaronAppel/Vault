#ifndef _SetupLibraries_H_
#define _SetupLibraries_H_

struct GLFWwindow;

GLFWwindow* Setup(const char* windowTitle, int winWidth = 1280, int winHeight = 720);
void TearDown(GLFWwindow* window);

#define LibrariesDir "../Libraries/"

#include "../Libraries/glew/GL/glew.h"
#include "../Libraries/glfw/GLFW/glfw3.h"
#include "../Libraries/imgui/imgui.h"
#include "../Libraries/imgui/imgui_impl_glfw_gl3.h"

#pragma comment( lib, LibrariesDir "glew/glew32d.lib" )
#pragma comment( lib, LibrariesDir "glfw/glfw3dll.lib" )

#endif // _SetupLibraries_H_