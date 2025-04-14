#pragma once

#include <memory>

#include <Engine/KeyHandler.h>

class Scene;
class SDL_Renderer;

namespace events {
    class EventManager;
    struct KeyPress;
    struct Debug;
    struct StartStop;
    struct GameStarted;
    struct GameOver;
}

class Game {
public:
    enum class State {
        UNINTIALIZED,
        INITIALIZED,
        RUNNING,
        STOPPED
    };

    explicit Game(std::shared_ptr<events::EventManager> eventManager, std::reference_wrapper<const KeyHandler> keyHandler);

    void update(float delta);
    void render(SDL_Renderer& renderer);

private:
    void onDebug(events::Debug&);
    void onStartStop(events::StartStop&);
    void onGameOver(events::GameOver&);
    void onGameStarted(events::GameStarted&);

    std::shared_ptr<events::EventManager> m_eventManager;
    std::reference_wrapper<const KeyHandler> m_keyHandler;
    std::unique_ptr<Scene> m_scene;
    State m_state{State::UNINTIALIZED};
    bool m_playing{false};
    bool m_debug{false};

};
