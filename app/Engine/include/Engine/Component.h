#pragma once

class Component {
    friend class Entity;
public:
    virtual ~Component() = default;
    [[nodiscard]] virtual bool isActive() const;
protected:
    virtual void setActive(bool active);
    bool m_active{false};
};

