#pragma once

#include <string>

#include <raylib.h>
#include <entt/entt.hpp>

#include "dynamic-lib-export.hpp"

struct Square
{
    Vector2 size;
    Vector2 position;
    Color color;
    float rotation;
    Vector2 velocity;
};

class IGame
{
public:
    virtual ~IGame() = default;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void SetRegistry(entt::registry &registry);

protected:
    entt::registry *m_registry = nullptr;
};

class Game : public IGame
{
private:
    Game() = default;
    ~Game() override = default;

public:
    static void Initialize();
    static IGame &GetInstance();
    static void Shutdown();

    void Update() override;
    void Draw() override;

private:
    inline static IGame *m_instance = nullptr;
};

extern "C"
{
    EXPORT_FUNC void GameInitialize();
    EXPORT_FUNC IGame *GameGetInstance();
    EXPORT_FUNC void GameShutdown();
}

typedef void (*GameInitializeFunc)();
typedef IGame *(*GameGetInstanceFunc)();
typedef void (*GameShutdownFunc)();
