#include "ELANsfml/Sprites/BackgroundColor.h"
#include "ELANsfml/Singletons/Screen.h"
#include "ELANsfml/Singletons/EventHandler.h"

void BackgroundColor::Render() {
    auto window = Screen::GetInstance()->GetRenderWindow();

    window->clear(color_);
}

void BackgroundColor::Update(AbstractApp *app) {}

BackgroundColor::BackgroundColor(sf::Color color, OnResizeFunction on_resize) : AbstractSprite(
                                                                        {0, 0},
                                                                        {0, 0},
                                                                        std::move(on_resize),
                                                                        -1e9),
                                                                        color_(color) {}


