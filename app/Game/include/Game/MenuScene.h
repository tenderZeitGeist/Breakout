
#pragma once

#include <Engine/KeyHandler.h>
#include <Game/Scene.h>

#include <memory>

#include <SDL2/SDL.h>

class MenuScene : public Scene {
public:
    MenuScene(std::reference_wrapper<const KeyHandler> keyHandler, std::shared_ptr<events::EventManager> eventManager);

    void update(float delta) override;
    void render(SDL_Renderer& renderer) override;
    void enter() override;
    void exit() override;
    void onDebug(bool debug) override;

private:
    std::reference_wrapper<const KeyHandler> m_keyHandler;
    std::shared_ptr<events::EventManager> m_eventManager;

    SDL_Texture* m_topicText;
    SDL_Texture* m_controlsText;
    SDL_Texture* m_spacebarText;
    SDL_Texture* m_leftArrowText;
    SDL_Texture* m_rightArrowText;

    SDL_Rect m_topicTextPosition;
    SDL_Rect m_controlTextPosition;
    SDL_Rect m_spacebarTextPosition;
    SDL_Rect m_leftArrowTextPosition;
    SDL_Rect m_rightArrowTextPosition;
};
