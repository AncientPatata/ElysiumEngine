// Game.cpp
//#include "../pch.h"
#include "Game.h"
#include "Log.h"
#include <chrono>   
#include "../Core/ResourceManager/ResourceManager.h"
#include "../Resources/ShaderResourceLoader.h"
#include "../Resources/MaterialResourceLoader.h"


using namespace Core;

Game::Game(int width, int height, std::string title)
    :m_Window(new Window(width, height, title))
{

    // Configure the log instances
    Log::Instance().SetLogFile("engine.log");
    Log::Instance().SetLogLevelFilter(LogLevel::Debug);
    Log::Instance().SetMaxFileSize(1024 * 1024); // 1 MB
    Log::Instance().SetMaxFiles(5);

    //Log::Instance().AddOutput(std::cout); // Output log messages to console
    Log::Instance().Out(LogLevel::Info) << "Game started";

    // Register resource loaders (after log because they use it)
    // Register the shader resource loader
    ResourceManager::Instance().RegisterResourceLoader<Resources::ShaderResourceLoader>();
    ResourceManager::Instance().RegisterResourceLoader<Resources::MaterialResourceLoader>();

}

Game::~Game()
{
    // Destructor
}

void Game::Initialize()
{
    // Initialize game objects and 
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
}

void Game::Update(float deltaTime)
{
    // Update game logic, objects, and resources
}

void Game::Render(float deltaTime)
{
    // Render game objects
}

void Game::Run()
{
    const double fixedDeltaTime = 1.0 / 60.0; // Fixed time step for game logic

    std::chrono::time_point<std::chrono::high_resolution_clock> previousTime = std::chrono::high_resolution_clock::now();
    double accumulator = 0.0;

    while (!m_Window->ShouldClose())
    {
        std::chrono::time_point<std::chrono::high_resolution_clock> currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::chrono::seconds::period> deltaTime = currentTime - previousTime;
        previousTime = currentTime;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //m_Window->HandleCursorClamping();

        m_Window->PollEvents();


        // Accumulate time for game logic updates
        accumulator += deltaTime.count();

        // Update game logic at fixed time step
        while (accumulator >= fixedDeltaTime)
        {
            Update(fixedDeltaTime);
            accumulator -= fixedDeltaTime;
        }

        Render(deltaTime.count());
        m_Window->SwapBuffers();

    }
}

