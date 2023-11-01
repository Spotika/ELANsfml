#pragma once

#include "AbstractSprite.h"

#ifndef CMAKESFMLPROJECT_PLAINTEXT_H
#define CMAKESFMLPROJECT_PLAINTEXT_H

// класс для простого отображения текста
class PlainText : public AbstractSprite {
public:

    PlainText(sf::Vector2f position,
              sf::Vector2f size,
              OnResizeFunction on_resize,
              std::string text,
              sf::Color text_color,
              int font_size,
              int layer = 0);

    void Update(AbstractApp *app) override;

    void ReInit() override;

    void Render() override;

    void Resize() override;

private:

    std::string raw_text_;
    sf::Color text_color_;
    int font_size_;
    sf::Text text_;
};

#endif //CMAKESFMLPROJECT_PLAINTEXT_H
