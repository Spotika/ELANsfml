#include <utility>

#include "ELANsfml/Sprites/Button.h"
#include "ELANsfml/Singletons/Screen.h"
#include "ELANsfml/Singletons/EventHandler.h"
#include "ELANsfml/Helpers/Config.h"
#include "SFML/Graphics.hpp"

void Button::Update(AbstractApp *app) {
    AbstractSprite::Update(app);
    for (auto event: *EventHandler::GetInstance()->GetEvents()) {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                int mouseX = event.mouseButton.x;
                int mouseY = event.mouseButton.y;

                if (ContainsPoint({static_cast<float>(mouseX), static_cast<float>(mouseY)})) {
                    if (on_click_) {
                        on_click_();
                    }
                }
            }
        }
    }
}

void Button::Render() {
    auto window = Screen::GetInstance()->GetRenderWindow();

    window->draw(shape_);
    window->draw(rendered_text_);
}

bool Button::ContainsPoint(sf::Vector2f point) const {
    return point.x >= position_.x && point.x <= position_.x + size_.x &&
           point.y >= position_.y && point.y <= position_.y + size_.y;
}

sf::Vector2f Button::GetNormalizedPosition() const {
    sf::Vector2u windowSize = Screen::GetInstance()->GetRenderWindow()->getSize();
    return {position_.x >= 0 ? position_.x : windowSize.x + position_.x - size_.x,
            position_.y > 0 ? position_.y : windowSize.y + position_.y - size_.y};
}

Button::Button(sf::Vector2f position,
               sf::Vector2f size,
               OnResizeFunction on_resize,
               std::string text,
               sf::Color text_color,
               sf::Color background_color,
               int font_size,
               int layer) : AbstractSprite(position,
                                           size,
                                           std::move(on_resize),
                                           layer),
                            text_color_(text_color),
                            font_size_(font_size),
                            background_color_(background_color),
                            text_(std::move(text)) {

    shape_.setSize(size_);
    shape_.setPosition(GetNormalizedPosition());
    shape_.setFillColor(background_color_);

    rendered_text_.setFont(*Screen::GetInstance()->GetFont());
    rendered_text_.setString(text_);
    rendered_text_.setCharacterSize(font_size_);
    rendered_text_.setFillColor(text_color_);
    Button::Resize();
}

void Button::ReInit() {
    shape_.setPosition(position_);
    shape_.setSize(size_);

    // Обновляем текст на кнопке
    sf::FloatRect textBounds = rendered_text_.getLocalBounds();
    sf::Vector2f textPosition(position_.x + (size_.x - textBounds.width) / 2,
                              position_.y + (size_.y - 1.5 * textBounds.height) / 2);
    rendered_text_.setPosition(textPosition);
}