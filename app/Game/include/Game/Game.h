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
    struct BallOutOfBounds;
}

class Game {
    using UpdateFunction = void (Game::*)(float);
public:
    enum class State {
        UNINITIALIZED,
        INITIALIZED,
        START,
        RUNNING,
        STOPPED
    };

    explicit Game(std::shared_ptr<events::EventManager> eventManager, std::reference_wrapper<const inputs::KeyHandler> keyHandler);

    void update(float delta);
    void render(SDL_Renderer& renderer);
    void initializeGame(const TextureRenderer& textureRenderer);

private:
    void startGame();
    void resetGame();
    void updateGame(float delta);
    void queryInputs();
    void triggerEvent(inputs::InputEvent inputEvent);
    void togglePlayingState();

    void onDebug();
    void onStartGame();
    void onBallOutOfBounds(events::BallOutOfBounds&);
    void onGameOver(events::GameOver&);

    std::shared_ptr<events::EventManager> m_eventManager;
    std::reference_wrapper<const inputs::KeyHandler> m_keyHandler;
    std::unordered_set<inputs::Keys> m_pressedKeys;
    std::unique_ptr<Scene> m_menuScene;
    std::unique_ptr<Scene> m_gameScene;
    Scene* m_activeScene{nullptr};
    State m_state{State::UNINITIALIZED};
    bool m_playing{false};
    bool m_debug{false};
};
