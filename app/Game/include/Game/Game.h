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
}

class Game {
public:
    enum class State {
        UNINTIALIZED,
        INITIALIZED,
        RUNNING,
        STOPPED
    };

    explicit Game(std::shared_ptr<events::EventManager> eventManager);

    void update(float delta);
    void render(SDL_Renderer& renderer);

    void setScene(std::unique_ptr<Scene> scene);
    [[nodiscard]] const Scene* getScene() const;

private:
    void onDebug(events::Debug&);
    void onStartStop(events::StartStop&);

    std::shared_ptr<events::EventManager> m_eventManager;
    std::shared_ptr<Scene> m_scene;
    State m_state{State::UNINTIALIZED};
    bool m_playing{false};
    bool m_debug{false};
};
