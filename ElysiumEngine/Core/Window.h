// Window.h
#pragma once
#include "../vendor/glad/glad.h"
#include "../vendor/GLFW/glfw3.h"
#include <string>

namespace Core {

    class Window
    {
    public:
        Window(int width, int height, std::string title);
        ~Window();

        void HideCursor() const;
        void ShowCursor() const;

        int GetWidth() const;
        int GetHeight() const;

        bool ShouldClose() const;
        void SwapBuffers();
        void PollEvents();

    private:
        GLFWwindow* m_window;
        int m_Width;
        int m_Height;
        std::string m_Title;
    };

}