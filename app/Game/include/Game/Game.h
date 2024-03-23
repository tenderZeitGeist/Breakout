#pragma once

#include <memory>

#include <Engine/KeyHandler.h>

class Scene;
class SDL_Renderer;

namespace events {
    class EventManager;
    struct KeyPress;
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
    [[nodiscard]] const KeyHandler& getKeyHandler() const;

private:
    void onKeyEvent(events::KeyPress& e);

    std::shared_ptr<events::EventManager> m_eventManager;
    std::shared_ptr<Scene> m_scene;
    KeyHandler m_keyHandler;
    State m_state{State::UNINTIALIZED};

};
