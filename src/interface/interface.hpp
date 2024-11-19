#pragma once

#include <string>
#include <iostream>

#include <raylib.h>
#include <entt/entt.hpp>

#include "dynamic-lib-import.hpp"
#include "game/game.hpp"

class Interface
{
private:
    Interface();
    ~Interface();

public:
    static void Initialize();
    static Interface &GetInstance();
    static void Shutdown();

    void Run();

private:
    void Update();
    void Draw();

private:
    DLL_HANDLE m_game_handle = nullptr;
    Game *m_game = nullptr;
    struct stat dll_stat;

private:
    Vector2 m_size = {1280.0f, 720.0f};
    std::string m_title = "Game Project";

    entt::registry m_registry;

    inline static Interface *s_instance = nullptr;
};