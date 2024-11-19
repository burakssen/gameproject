#include "game.hpp"

extern "C"
{
    EXPORT_FUNC void GameInitialize()
    {
        Game::Initialize();
    }

    EXPORT_FUNC IGame *GameGetInstance()
    {
        return &Game::GetInstance();
    }

    EXPORT_FUNC void GameShutdown()
    {
        Game::Shutdown();
    }
}

void IGame::SetRegistry(entt::registry &registry)
{
    m_registry = &registry;
}

void Game::Initialize()
{
    if (m_instance != nullptr)
    {
        throw std::runtime_error("Game instance already exists");
    }

    m_instance = new Game();
}

IGame &Game::GetInstance()
{
    if (m_instance == nullptr)
    {
        throw std::runtime_error("Game instance does not exist");
    }

    return *m_instance;
}

void Game::Shutdown()
{
    if (m_instance == nullptr)
    {
        throw std::runtime_error("Game instance does not exist");
    }

    delete m_instance;
    m_instance = nullptr;
}

void Game::Update()
{
    if (m_registry == nullptr)
        return;

    auto view = m_registry->view<entt::tag<entt::hashed_string("MyText")>, std::string>();
    for (auto entity : view)
    {
        auto text = view.get<std::string>(entity);
        text = "Please Work!!!";
        view.get<std::string>(entity) = text;
    }

    if (IsKeyPressed(KEY_SPACE))
    {
        entt::entity newEntity = m_registry->create();
        m_registry->emplace<Square>(newEntity, Vector2{50.0f, 50.0f}, Vector2{50.0f, 100.0f}, YELLOW, 0.0f, Vector2{2.0f, 0.0f});
    }

    auto squareView = m_registry->view<Square>();
    for (auto entity : squareView)
    {
        auto &square = squareView.get<Square>(entity);
        square.position.x += square.velocity.x;
        square.position.y += square.velocity.y;
        square.rotation -= GetFrameTime() * 100.0f;
    }
}

void Game::Draw()
{
    if (m_registry == nullptr)
        return;

    auto view = m_registry->view<entt::tag<entt::hashed_string("MyText")>, std::string>();
    for (auto entity : view)
    {
        auto text = view.get<std::string>(entity);
        DrawText(text.c_str(), 10, 10, 20, WHITE);
    }

    auto squareView = m_registry->view<Square>();
    for (auto entity : squareView)
    {
        auto &square = squareView.get<Square>(entity);
        DrawRectanglePro(Rectangle{square.position.x, square.position.y, square.size.x, square.size.y}, Vector2{square.size.x / 2, square.size.y / 2}, square.rotation, square.color);
    }
}