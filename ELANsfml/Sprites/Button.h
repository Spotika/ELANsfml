#pragma once

#include <utility>

#include "AbstractSprite.h"
#include "ELANsfml/Apps/AbstractApp.h"
#include "ELANsfml/Singletons/Screen.h"
#include "functional"

#ifndef CMAKESFMLPROJECT_BUTTON_H
#define CMAKESFMLPROJECT_BUTTON_H

using ClickMethod = std::function<void()>;

class Button : public AbstractSprite {
public:
    Button(sf::Vector2f position,
           sf::Vector2f size,
           OnResizeFunction on_resize,
           std::string text,
           sf::Color text_color,
           sf::Color background_color,
           int font_size,
           int layer = 0);

    void ReInit() override;

    template<class T>
    void LinkMethod(T *object, void (T::*method)()) {
        on_click_ = std::bind(method, object);
    }

    void Update(AbstractApp *app) override;

    void Render() override;

    [[nodiscard]] bool ContainsPoint(sf::Vector2f point) const;

private:
    ClickMethod on_click_;
    std::string text_;
    sf::Color text_color_;
    sf::Color background_color_;
    int font_size_;

    sf::RectangleShape shape_;
    sf::Text rendered_text_;

    sf::Vector2f GetNormalizedPosition() const;
};

#endif //CMAKESFMLPROJECT_BUTTON_H
