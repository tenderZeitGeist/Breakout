//
// Created by zeitgeist on 13.10.23.
//

#pragma once

#include <Engine/Component.h>

#include <cstdint>
#include <functional>

class Entity;

enum Side : std::uint8_t {
    NONE = 0,
    LEFT = 1 << 0,
    RIGHT = 1 << 1,
    TOP = 1 << 2,
    BOTTOM = 1 << 3,
};

class Collidable : public Component {
public:
    explicit Collidable(std::reference_wrapper<Entity> entity);

    friend bool operator==(const Collidable& lhs, const Collidable& rhs);
    friend bool operator!=(const Collidable& lhs, const Collidable& rhs);
    friend Side determineSide(const Collidable& lhs, const Collidable& rhs);

    [[nodiscard]] bool isEnabled() const;
    void setEnabled(bool enabled);

private:
    bool m_enabled{true};
    std::reference_wrapper<Entity> m_entity;
};
