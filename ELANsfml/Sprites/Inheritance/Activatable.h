#pragma once

#include "ELANsfml/Sprites/AbstractSprite.h"
#include "ELANsfml/Singletons/EventHandler.h"
#include "SFML/Graphics.hpp"
#include <iostream>

#ifndef CMAKESFMLPROJECT_ACTIVATABLE_H
#define CMAKESFMLPROJECT_ACTIVATABLE_H

class Activatable {
public:

    [[nodiscard]] bool IsActive() const {
        return is_active_;
    }

    bool UpdateActivatable(sf::Vector2f position, sf::Vector2f size) {
        for (auto event : *EventHandler::GetInstance()->GetEvents()) {
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    int mouseX = event.mouseButton.x;
                    int mouseY = event.mouseButton.y;

                    int prev = is_active_;
                    is_active_ = IsPointInObject(position, size, {static_cast<float>(mouseX), static_cast<float>(mouseY)});

                    if (prev != is_active_) {
                        return true;
                    } else {
                        return false;
                    }
                }
            }
        }
        return false;
    }

private:

    static bool IsPointInObject(sf::Vector2f position, sf::Vector2f size, sf::Vector2f point) {
        return (position.x <= point.x && point.x <= position.x + size.x) && (position.y <= point.y && point.y <= position.y + size.y);
    }

    bool is_active_ = false;
};

#endif //CMAKESFMLPROJECT_ACTIVATABLE_H
