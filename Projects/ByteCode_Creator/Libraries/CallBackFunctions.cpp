#include "stdafx.h"

extern MyGLFW* g_MainWindow;
extern int g_WindowWidth, g_WindowHeight;
extern bool g_Debugging;

void SetupCallbacks(MyGLFW* window)
{
	// input
	window->SetKeyCallback(key_callback);
	window->SetScrollCallback(scroll_callback);
	window->SetCharCallback(char_callback);
	window->SetCharModsCallback(char_mods_callback);
	window->SetCursorMoveCallback(cursor_position_callback);
	window->SetMouseButtonCallback(mouse_button_callback);
	// window
	window->SetWindowMoveCallback(window_position_callback);
	window->SetWindowResizeCallback(window_resize_callback);
	window->SetWindowCloseCallback(window_close_callback);
	window->SetWindowRefreshCallback(window_refresh_callback);
	window->SetWindowFocusCallback(window_focus_callback);
	window->SetWindowIconifyCallback(window_iconify_callback);
	window->SetFrameBufferResizeCallback(framebuffer_resize_callback);
	// error
	window->SetErrorCallback(error_callback);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
}
void char_callback(GLFWwindow* window, unsigned int codePoint)
{
}
void char_mods_callback(GLFWwindow* window, unsigned int codepoint, int mods)
{
}
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
}
void cursor_enter_callback(GLFWwindow* window, int entered)
{
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
}
void joystick_callback(int joy, int event)
{
	// joystick button pressed
	int bp = 1;
}
// window callbacks
void window_position_callback(GLFWwindow* window, int x, int y)
{
	// window moved
	int bp = 1;
}
void window_resize_callback(GLFWwindow* window, int width, int height)
{
	// window resized
	int bp = 1;
}
void window_close_callback(GLFWwindow* window)
{
	// window closed
	int bp = 1;
}
void window_refresh_callback(GLFWwindow* window)
{
	// window refreshed
	int bp = 1;
}
void window_focus_callback(GLFWwindow* window, int isFocused)
{
	if (isFocused == GLFW_TRUE)
	{
		// debug_GetGameCore()->GetSceneManager()->GetCurrentScene()->SetIsPaused(false); // regained focus
	}
	else
	{
		// debug_GetGameCore()->GetSceneManager()->GetCurrentScene()->SetIsPaused(true); // lost focus
	}
}
void window_iconify_callback(GLFWwindow* window, int isIconified)
{
	if (isIconified == GLFW_TRUE)
	{
		// iconified
		int bp = 1;
	}
	else
	{
		int bp = 1;
	}
}
void framebuffer_resize_callback(GLFWwindow* window, int x, int y)
{
	// framebuffer resized
}
void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error %d: %s\n", error, description);
}
// file
void file_drop_callback(GLFWwindow* window, int count, const char** paths)
{
	// path of file drag and dropped onto this window
}