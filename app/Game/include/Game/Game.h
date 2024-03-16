#pragma once

#include <memory>

class Scene;
class SDL_Renderer;

namespace events {
    class EventManager;
    class KeyPress;
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
    [[nodiscard]]const Scene* getScene() const;

private:
    void onKeyEvent(events::KeyPress* e);

    std::shared_ptr<events::EventManager> m_eventManager;
    std::shared_ptr<Scene> m_scene;
    State m_state{State::UNINTIALIZED};
};
