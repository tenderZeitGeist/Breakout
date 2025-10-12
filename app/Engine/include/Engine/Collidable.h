#pragma once

#include <Engine/Component.h>

#include <functional>

class Entity;

class Collidable : public Component {
public:
    explicit Collidable(std::reference_wrapper<Entity> entity);

    friend bool operator==(const Collidable& lhs, const Collidable& rhs);
    friend bool operator!=(const Collidable& lhs, const Collidable& rhs);

    [[nodiscard]] bool isEnabled() const;
    void setEnabled(bool enabled);

private:
    bool m_enabled{true};
    std::reference_wrapper<Entity> m_entity;
};
