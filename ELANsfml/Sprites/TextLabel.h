#pragma once

#include "AbstractSprite.h"
#include <vector>
#include <string>
#include "ELANsfml/Sprites/Inheritance/Activatable.h"

#ifndef CMAKESFMLPROJECT_TEXTLABLE_H
#define CMAKESFMLPROJECT_TEXTLABLE_H

class TextLabel : public AbstractSprite, public Activatable {
public:

    TextLabel(sf::Vector2f position,
              sf::Vector2f size,
              OnResizeFunction on_resize,
              bool toggle_enumerate,
              sf::Color background_color,
              sf::Color text_color,
              sf::Color side_color,
              sf::Color side_text_color,
              int font_size,
              int layer = 0);

    void Render() override;

    void ReInit() override;

    void Update(AbstractApp *app) override;

    int GetMaxCharsPossibleToContainInLine();

    std::vector<std::string*> * GetText();

    ~TextLabel() override {
        for (auto i : text_) {
            delete i;
        }
    }

    int GetCharacterSize();

    float GetTextFieldWidth();

protected:

    float left_border_ = 0;

    bool toggle_enumerate_ = false;
    std::vector<std::string*> text_;
    sf::Color text_color_;
    sf::Color side_color_;
    sf::Color side_text_color_;
    sf::Color background_color_;
    int font_size_;

    sf::RenderTexture render_texture_;

    int begin_ = 0;

    int current_number_of_lines_ = 0;
};

#endif //CMAKESFMLPROJECT_TEXTLABLE_H
