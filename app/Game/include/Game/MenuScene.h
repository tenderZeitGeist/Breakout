
#pragma once

#include <Engine/KeyHandler.h>
#include <Engine/Text.h>
#include <Game/Scene.h>

#include <memory>
#include <vector>

#include <SDL2/SDL.h>

class TextureRenderer;

class MenuScene : public Scene {
public:
    MenuScene(std::shared_ptr<events::EventManager> eventManager,
              const TextureRenderer& textureRenderer);
    void update(float delta) override;
    void render(SDL_Renderer& renderer) override;
    void enter() override;
    void exit() override;
    void onDebug(bool debug) override;

private:
    std::shared_ptr<events::EventManager> m_eventManager;
    std::vector<Text> m_texts;
};
