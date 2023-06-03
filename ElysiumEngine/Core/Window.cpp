//#include "../pch.h"

#include "Window.h"
#include "Input.h"

using namespace Core;

Window::Window(int width, int height, std::string title): m_Width(width), m_Height(height), m_Title(title)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_window);

    glfwSetKeyCallback(m_window, Input::KeyCallback);
    glfwSetMouseButtonCallback(m_window, Input::MouseButtonCallback);
    glfwSetCursorPosCallback(m_window, Input::CursorPositionCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        // Handle error
    }
}

Window::~Window()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void Window::HideCursor() const
{
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void Window::ShowCursor() const
{
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

int Window::GetWidth() const
{
    return m_Width;
}

int Window::GetHeight() const
{
	return m_Height;
}

bool Window::ShouldClose() const
{
    return glfwWindowShouldClose(m_window);
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(m_window);
}

void Window::PollEvents()
{
    glfwPollEvents();
}