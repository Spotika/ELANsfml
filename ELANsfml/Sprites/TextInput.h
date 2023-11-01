#pragma once

#include <vector>
#include "ELANsfml/Singletons/Screen.h"
#include "ELANsfml/Singletons/EventHandler.h"
#include "ELANsfml/Apps/AbstractApp.h"
#include "ELANsfml/Sprites/AbstractSprite.h"

#include "ELANsfml/Helpers/Config.h"
#include "TextLabel.h"

#ifndef CMAKESFMLPROJECT_TEXTINPUT_H
#define CMAKESFMLPROJECT_TEXTINPUT_H

class TextInput : public TextLabel {
public:

    TextInput(sf::Vector2f position,
              sf::Vector2f size,
              OnResizeFunction on_resize,
              sf::Color text_color,
              sf::Color base_color,
              sf::Color active_color,
              int font_size,
              int layer = 0);

    void Update(AbstractApp *app) override;

    void Render() override;

    void ReInit() override;

private:
    sf::Color base_color_;
    sf::Color active_color_;
};


#endif //CMAKESFMLPROJECT_TEXTINPUT_H
