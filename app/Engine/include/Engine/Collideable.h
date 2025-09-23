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

class Collideable : public Component {
public:
    explicit Collideable(std::reference_wrapper<Entity> entity);

    friend bool operator==(const Collideable& lhs, const Collideable& rhs);
    friend bool operator!=(const Collideable& lhs, const Collideable& rhs);
    friend Side collides(const Entity& lhs, const Entity& rhs);

    [[nodiscard]] bool isEnabled() const;
    void setEnabled(bool enabled);

private:
    bool m_enabled{true};
    std::reference_wrapper<Entity> m_entity;
};
