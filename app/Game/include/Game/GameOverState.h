
#pragma once

#include <Engine/Entity.h>
#include <Engine/Text.h>

#include <utility>

class TextureRenderer;

enum class GameOverText {
    WINNING,
    LOSING
};

class GameOverState : public Entity {
public:
    explicit GameOverState(std::reference_wrapper<const TextureRenderer> textureRenderer) noexcept;

    void render(SDL_Renderer& renderer) override;
    void reset() override;
    void setActiveText(GameOverText state);
    [[nodiscard]] std::reference_wrapper<const Text> getActiveText() const;

private:
    void initializeTexts(std::reference_wrapper<const TextureRenderer> textureRenderer);

    Text m_winningText;
    Text m_losingText;
    std::reference_wrapper<const Text> m_activeText;
    int m_counter{0};
    bool m_visible{true};
};
