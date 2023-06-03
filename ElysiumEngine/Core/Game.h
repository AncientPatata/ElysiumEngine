// Game.h
#pragma once
#include "Window.h"


namespace Core {

    class Game
    {
    public:
        Game(int width, int height, std::string title);
        ~Game();

        Window* GetWindow() const { return m_Window; }

        virtual void Initialize();
        virtual void Update(float deltaTime);
        virtual void Render(float deltaTime);
        void Run();

    private:
        Window* m_Window;
    };

}