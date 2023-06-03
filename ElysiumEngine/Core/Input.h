// CONSIDER EVENTUALLY SWITCHING TO EVENT DRIVEN INPUT

// Input.h
#pragma once
#include <unordered_map>
#include "../vendor/GLFW/glfw3.h"

namespace Core {

    class Input
    {
    public:
        static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static bool IsKeyPressed(int key);
        static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
        static bool IsMouseButtonPressed(int button);
        static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
        static void GetCursorPosition(double& xpos, double& ypos);

    private:
        static std::unordered_map<int, bool> m_keyStates;
        static std::unordered_map<int, bool> m_mouseButtonStates;
        static double m_cursorX;
        static double m_cursorY;
    };
}