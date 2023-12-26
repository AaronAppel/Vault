#include "SetupLibraries.h"

#include "../Libraries/glew/GL/glew.h"
#include "../Libraries/glfw/GLFW/glfw3.h"
#include "../Libraries/imgui/imgui.h"
#include "../Libraries/imgui/imgui_impl_glfw_gl3.h"

GLFWwindow* Setup(const char* windowTitle, int winWidth, int winHeight)
{
    GLFWwindow* window;

    if (!glfwInit())
        return nullptr; // Failed to setup

    window = glfwCreateWindow(winWidth, winHeight, windowTitle, NULL, NULL);
    if (!window)
        return nullptr; // Failed to setup

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        return nullptr; // Failed to setup

    glViewport(0, 0, winWidth, winHeight);

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplGlfwGL3_Init(window, true);

    return window;
}

void TearDown(GLFWwindow* window)
{
    glfwDestroyWindow(window);
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}
