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

void Window::HideCursor()
{
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    m_bCursorHidden = true;
}

void Window::ShowCursor()
{
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    m_bCursorHidden = false;
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

void Window::HandleCursorClamping()
{
    if (m_bCursorHidden)
    {
        // Handle cursor clamping
        double cursorX, cursorY;
        glfwGetCursorPos(m_window, &cursorX, &cursorY);
        if (cursorX < 0.0) {
            cursorX = 0.0;
            glfwSetCursorPos(m_window, cursorX, cursorY);
        }
        else if (cursorX >= m_Width) {
            cursorX = m_Width - 1;
            glfwSetCursorPos(m_window, cursorX, cursorY);
        }
        if (cursorY < 0.0) {
            cursorY = 0.0;
            glfwSetCursorPos(m_window, cursorX, cursorY);
        }
        else if (cursorY >= m_Height) {
            cursorY = m_Height - 1;
            glfwSetCursorPos(m_window, cursorX, cursorY);
        }
    }
}
