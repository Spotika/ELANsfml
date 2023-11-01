#include <utility>

#include "../PlainText.h"
#include "ELANsfml/Singletons/Screen.h"
#include "ELANsfml/Singletons/EventHandler.h"

PlainText::PlainText(sf::Vector2f position,
                     sf::Vector2f size,
                     OnResizeFunction on_resize,
                     std::string text,
                     sf::Color text_color,
                     int font_size,
                     int layer) : AbstractSprite(position,
                                                 size,
                                                 std::move(on_resize),
                                                 layer),
                                 text_color_(text_color),
                                 font_size_(font_size),
                                 raw_text_(std::move(text)) {

    text_.setFont(*Screen::GetInstance()->GetFont());
    text_.setFillColor(text_color_);
    text_.setCharacterSize(font_size_);
    text_.setString(raw_text_);
    PlainText::Resize();
    PlainText::ReInit();
}

void PlainText::Update(AbstractApp *app) {
    AbstractSprite::Update(app);
}


void PlainText::Render() {
    Screen::GetInstance()->GetRenderWindow()->draw(text_);
}

void PlainText::ReInit() {
    AbstractSprite::ReInit();

    text_.setPosition(position_);
}

void PlainText::Resize() {
    AbstractSprite::Resize();

    size_ = {text_.getLocalBounds().width, text_.getLocalBounds().height};
}
