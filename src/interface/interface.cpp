#include "interface.hpp"

void Interface::Initialize()
{
    if (s_instance != nullptr)
    {
        throw std::runtime_error("Interface instance already exists");
    }

    s_instance = new Interface();
}

Interface &Interface::GetInstance()
{
    if (s_instance == nullptr)
    {
        throw std::runtime_error("Interface instance does not exist");
    }

    return *s_instance;
}

void Interface::Shutdown()
{
    if (s_instance == nullptr)
    {
        throw std::runtime_error("Interface instance does not exist");
    }

    delete s_instance;
    s_instance = nullptr;
}

Interface::Interface()
{
    InitWindow(this->m_size.x, this->m_size.y, this->m_title.c_str());
    SetTargetFPS(60);

    SetExitKey(0);

    auto textEntity = this->m_registry.create();
    m_registry.emplace<entt::tag<entt::hashed_string{"MyText"}>>(textEntity);
    m_registry.emplace<std::string>(textEntity, "Please Work!!!");
}

Interface::~Interface()
{
    CloseWindow();
}

void Interface::Run()
{
    while (!WindowShouldClose())
    {
        time_t last_modified = this->dll_stat.st_mtime;
        int resp = stat("libgame" LIB_EXTENSION, &this->dll_stat);
        if (resp != 0)
        {
            std::cerr << "Failed to get library stats" << std::endl;
            exit(EXIT_FAILURE);
        }

        if (last_modified != this->dll_stat.st_mtime)
        {
            if (this->m_game_handle != nullptr)
            {
                GameShutdownFunc p_shutdown_func = reinterpret_cast<GameShutdownFunc>(GET_FUNCTION(this->m_game, "GameShutdown"));
                if (p_shutdown_func)
                {
                    p_shutdown_func();
                }

                FREE_LIBRARY(this->m_game_handle);
                this->m_game_handle = nullptr;
            }

            this->m_game_handle = static_cast<IGame *>(LOAD_LIBRARY("libgame" LIB_EXTENSION));

            WaitTime(0.5f);

            if (this->m_game_handle == nullptr)
            {
                std::cerr << "Failed to load game library" << std::endl;
                exit(EXIT_FAILURE);
            }

            GameInitializeFunc p_initialize_func = reinterpret_cast<GameInitializeFunc>(GET_FUNCTION(this->m_game_handle, "GameInitialize"));
            GameGetInstanceFunc p_getInstance_func = reinterpret_cast<GameGetInstanceFunc>(GET_FUNCTION(this->m_game_handle, "GameGetInstance"));

            if (p_initialize_func)
            {
                p_initialize_func();
                if (p_getInstance_func)
                {
                    this->m_game = static_cast<Game *>(p_getInstance_func());
                    this->m_game->SetRegistry(this->m_registry);
                }
            }

            WaitTime(0.5f);
        }

        this->Update();
        this->Draw();
    }
}

void Interface::Update()
{
    if (this->m_game != nullptr)
    {
        this->m_game->Update();
    }
}

void Interface::Draw()
{
    BeginDrawing();
    ClearBackground(BLACK);
    if (this->m_game != nullptr)
    {
        this->m_game->Draw();
    }
    EndDrawing();
}