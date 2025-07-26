#pragma once

#include <Engine/KeyHandler.h>

#include <memory>
#include <unordered_set>

class Scene;
class SDL_Renderer;
class TextureRenderer;

namespace events {
    class EventManager;
    struct KeyPress;
    struct Debug;
    struct StartStop;
    struct GameStarted;
    struct GameOver;
}

class Game {
    using UpdateFunction = void (Game::*)(float);
public:
    enum class State {
        UNINITIALIZED,
        INITIALIZED,
        RUNNING,
        STOPPED
    };

    explicit Game(std::shared_ptr<events::EventManager> eventManager, std::reference_wrapper<const inputs::KeyHandler> keyHandler);

    void update(float delta);
    void render(SDL_Renderer& renderer);
    void initializeGame(const TextureRenderer& textureRenderer);

private:
    void resetGame();
    void updateGame(float delta);
    void queryInputs();
    void triggerEvent(inputs::InputEvent inputEvent);

    void onDebug();
    void onStartStop();
    void onGameOver(events::GameOver&);
    void onGameStarted(events::GameStarted&);

    std::shared_ptr<events::EventManager> m_eventManager;
    std::reference_wrapper<const inputs::KeyHandler> m_keyHandler;
    std::unordered_set<inputs::Keys> m_pressedKeys;
    std::unique_ptr<Scene> m_menuScene;
    std::unique_ptr<Scene> m_gameScene;
    Scene* m_activeScene;
    State m_state{State::UNINITIALIZED};
    bool m_playing{false};
    bool m_debug{false};
};
