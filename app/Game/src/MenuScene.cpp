#include <Engine/Configuration.h>
#include <Engine/Text.h>
#include <Engine/TextureRenderer.h>
#include <Game/MenuScene.h>

MenuScene::MenuScene(std::shared_ptr<events::EventManager> eventManager, const TextureRenderer& textureRenderer)
    : m_eventManager(std::move(eventManager)) {
    for (const auto& text : {"BREAKOUT",
                             "Controls:",
                             "[Spacebar]: Pause/Unpause the game",
                             "[Left arrow]: Move paddle left",
                             "[Right arrow]: Move paddle right",
                             "[Enter]: Start the game"}) {
        auto textObject = textureRenderer.createText(text);
        auto& textPosition = textObject.position;
        // Query text size ...
        SDL_QueryTexture(textObject.texture.get(), nullptr, nullptr, &textPosition.w, &textPosition.h);
        // ... center it ...
        textPosition.x = config::windowHalfWidth - textPosition.w / 2;
        m_texts.emplace_back(std::move(textObject));
    }
    //... and space them out along the y-axis
    constexpr int titlePosition = static_cast<int>(config::windowWidth / 4);
    m_texts[0].position.y = titlePosition;
    constexpr int controlPosition = config::slotHeight * 5;
    constexpr int spacer = 28;
    for (std::size_t i = 1; i < m_texts.size(); ++i) {
        m_texts[i].position.y = static_cast<int>(titlePosition + controlPosition + (config::slotHeight * i)
                                                 + (spacer * i));
    }
}

void MenuScene::update(float) {
}

void MenuScene::render(SDL_Renderer& renderer) {
    for (const auto& text : m_texts) {
        SDL_RenderCopy(&renderer, text.texture.get(), nullptr, &text.position);
    }
}

void MenuScene::reset() {
}

void MenuScene::enter() {
}

void MenuScene::exit() {
}

void MenuScene::onDebug(bool) {
}
