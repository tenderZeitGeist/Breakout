//
// Created by zeitgeist on 05.10.23.
//

#pragma once

#include <cassert>
#include <functional>
#include <unordered_map>
#include <vector>

#include <iostream>

#include "Event.h"

namespace {
    using Handler = std::function<void(events::Event&)>;
    using TypeInfoRef = std::reference_wrapper<const std::type_info>;

    struct Hasher {
        std::size_t operator()(TypeInfoRef code) const {
            return code.get().hash_code();
        }
    };

    struct EqualTo {
        bool operator()(TypeInfoRef lhs, TypeInfoRef rhs) const {
            return lhs.get() == rhs.get();
        }
    };
}

namespace events {

    class EventManager {
        using Listeners = std::vector<Handler>;
        using ListenerMap = std::unordered_map<TypeInfoRef, Listeners, Hasher, EqualTo>;

    public:
        explicit EventManager() = default;

        template<typename T, typename EventType, void(T::*Method)(EventType&)>
        bool subscribe(T* instance) {
            auto entry = m_listeners.try_emplace(typeid(EventType), Listeners{});

            auto handler = [instance](Event& e) {
                (instance->*Method)(static_cast<EventType&>(e));
            };

            entry.first->second.emplace_back(std::move(handler));
            return true;
        }

        template<typename EventType>
        void notify(EventType&& e) const {
            notify<EventType>(std::forward<EventType>(e));
        }

        template<typename EventType>
        void notify(Event& e) const {
            const auto entry = m_listeners.find(typeid(EventType));
            if (entry == m_listeners.end()) {
                return;
            }
            for (const auto& listener: entry->second) {
                listener(e);
            }
        }

    private:
        ListenerMap m_listeners;
    };
}