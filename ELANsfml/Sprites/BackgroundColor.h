#pragma once

#include <utility>

#include "ELANsfml/Sprites/AbstractSprite.h"
#include "SFML/Graphics.hpp"

#ifndef CMAKESFMLPROJECT_BACKGROUNDCOLOR_H
#define CMAKESFMLPROJECT_BACKGROUNDCOLOR_H

class BackgroundColor : public AbstractSprite {
private:
    sf::Color color_;

public:
    BackgroundColor(sf::Color color, OnResizeFunction on_resize = ON_RESIZE NORMAL_RESIZE);

    void Render() override;
    void Update(AbstractApp *app) override;
};

#endif //CMAKESFMLPROJECT_BACKGROUNDCOLOR_H
