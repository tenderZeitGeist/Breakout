//
// Created by zeitgeist on 13.10.23.
//

#pragma once

#include <cstdint>

class Entity;

enum Side : std::uint8_t {
    NONE = 0,
    LEFT = 1 << 0,
    RIGHT = 1 << 1,
    TOP = 1 << 2,
    BOTTOM = 1 << 3,
};

class Collideable {
public:
    explicit Collideable(Entity& entity);

    friend bool operator==(const Collideable& lhs, const Collideable& rhs);
    friend bool operator!=(const Collideable& lhs, const Collideable& rhs);
    friend Side collides(const Collideable& lhs, const Collideable& rhs);

    [[nodiscard]] bool isEnabled() const;
    [[nodiscard]] int getExtentX() const;
    [[nodiscard]] int getExtentY() const;
    [[nodiscard]] int getCenterX() const;
    [[nodiscard]] int getCenterY() const;

    void setEnabled(bool enabled);
    void setExtentX(int extentX);
    void setExtentY(int extentY);
    void setCenterX(int centerX);
    void setCenterY(int centerY);

private:
    bool m_enabled{true};
    int m_extentX{0};
    int m_extentY{0};
    int m_centerX{0};
    int m_centerY{0};
};

