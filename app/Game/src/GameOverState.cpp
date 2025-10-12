#include <Engine/Configuration.h>
#include <Engine/TextureRenderer.h>
#include <Game/GameOverState.h>

namespace {

Text createText(std::reference_wrapper<const TextureRenderer> textureRenderer, std::string_view displayText) {
    auto text = textureRenderer.get().createText(displayText.data(), true);
    if (!text) {
        return {};
    }
    auto& textPosition = text.position;
    SDL_QueryTexture(text.texture.get(), nullptr, nullptr, &textPosition.w, &textPosition.h);
    textPosition.x = config::windowHalfWidth - textPosition.w / 2;
    textPosition.y = config::windowHalfHeight - textPosition.h / 2;
    return text;
}

}

GameOverState::GameOverState(std::reference_wrapper<const TextureRenderer> textureRenderer) noexcept
    : Entity(0)
    , m_activeText{std::cref(m_losingText)} {
    initializeTexts(textureRenderer);
}

void GameOverState::render(SDL_Renderer& renderer) {
    static constexpr int blinksInMs = 2000;
    static constexpr int blinkRate = blinksInMs / config::frameTimes;
    m_counter = (m_counter + 1) % blinkRate;
    if (m_counter == 0) {
        m_visible = !m_visible;
    }
    if (!m_visible) {
        return;
    }
    const auto& activeText = getActiveText().get();
    SDL_RenderCopy(&renderer, activeText.texture.get(), nullptr, &activeText.position);
}

void GameOverState::reset() {
    m_visible = true;
    m_counter = 0;
}

void GameOverState::setActiveText(GameOverText state) {
    m_activeText = std::cref(state == GameOverText::WINNING ? m_winningText : m_losingText);
}

std::reference_wrapper<const Text> GameOverState::getActiveText() const {
    return m_activeText;
}

void GameOverState::initializeTexts(std::reference_wrapper<const TextureRenderer> textureRenderer) {
    auto losingText = createText(std::ref(textureRenderer), "GAME OVER");
    auto winningText = createText(std::ref(textureRenderer), "YOU WON!");
    if (!losingText || !winningText) {
        // TODO: Error handling/logging?
        return;
    }
    m_winningText = std::move(winningText);
    m_losingText = std::move(losingText);
}
