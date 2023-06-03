#include "Input.h"

using namespace Core;

std::unordered_map<int, bool> Input::m_keyStates;
std::unordered_map<int, bool> Input::m_mouseButtonStates;
double Input::m_cursorX = 0;
double Input::m_cursorY = 0;

void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        m_keyStates[key] = true;
    }
    else if (action == GLFW_RELEASE)
    {
        m_keyStates[key] = false;
    }
}

bool Input::IsKeyPressed(int key)
{
    return m_keyStates[key];
}

void Input::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        m_mouseButtonStates[button] = true;
    }
    else if (action == GLFW_RELEASE)
    {
        m_mouseButtonStates[button] = false;
    }
}

bool Input::IsMouseButtonPressed(int button)
{
    return m_mouseButtonStates[button];
}

void Input::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    m_cursorX = xpos;
    m_cursorY = ypos;
}

void Input::GetCursorPosition(double& xpos, double& ypos)
{
    xpos = m_cursorX;
    ypos = m_cursorY;
}