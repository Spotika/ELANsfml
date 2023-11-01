#include <utility>

#include "../TextLabel.h"
#include <sstream>
#include <iostream>
#include "ELANsfml/Helpers/Config.h"
#include <iomanip>
#include "ELANsfml/Singletons/Screen.h"

TextLabel::TextLabel(sf::Vector2f position,
                     sf::Vector2f size,
                     OnResizeFunction on_resize,
                     bool toggle_enumerate,
                     sf::Color background_color,
                     sf::Color text_color,
                     sf::Color side_color,
                     sf::Color side_text_color,
                     int font_size_,
                     int layer) : AbstractSprite(position,
                                                 size,
                                                 std::move(on_resize),
                                                 layer),
                                 side_color_(side_color),
                                 text_color_(text_color),
                                 side_text_color_(side_text_color),
                                 background_color_(background_color),
                                 toggle_enumerate_(toggle_enumerate),
                                 font_size_(font_size_) {
    TextLabel::Resize();
    TextLabel::ReInit();
}

int TextLabel::GetMaxCharsPossibleToContainInLine() {
    return 0;
}

void TextLabel::ReInit() {

    sf::Color back_color = background_color_;
    if (!IsActive()) {
        back_color = {static_cast<sf::Uint8>(background_color_.r - 10),
                              static_cast<sf::Uint8>(background_color_.g - 10),
                               static_cast<sf::Uint8>(background_color_.b - 10)};
    }

    render_texture_.create(size_.x, size_.y);
    render_texture_.clear(back_color);

    sf::Text text;
    text.setFont(*Screen::GetInstance()->GetFont());
    text.setCharacterSize(font_size_);
    text.setLetterSpacing(1.0f);

    int num_lines = 100; // Количество строк, которые могут поместиться
    int line_height = font_size_ + 3; // Высота строки с небольшим отступом

    // Определите, сколько строк поместится
    if (num_lines > render_texture_.getSize().y / line_height) {
        num_lines = render_texture_.getSize().y / line_height;
    }

    int max_num_len = (std::to_string(begin_ + num_lines)).length();
    if (toggle_enumerate_) {
        text.setString(std::to_string(begin_ + num_lines));
    }

    current_number_of_lines_ = num_lines;

    int left_border = text.getLocalBounds().width;

    sf::RectangleShape shape;
    shape.setFillColor(side_color_);
    shape.setSize({static_cast<float>(left_border) + 25, size_.y});
    render_texture_.draw(shape);

    left_border_ = static_cast<float>(left_border);

    text.setFillColor(side_text_color_);
    // Отрисовка столбца с номерами
    for (int i = 0; i < num_lines; ++i) {
        int line_index = begin_ + i;
        if (toggle_enumerate_) {
            std::stringstream ss;
            ss << std::setw(max_num_len) << std::setfill('0') << line_index + 1; // Форматирование числа с ведущими нулями
            text.setFillColor(side_text_color_);
            text.setString(ss.str());
            text.setPosition(10, i * line_height); // Определение позиции текста
            render_texture_.draw(text);
        }

        if (line_index >= text_.size()) {
            continue;
        }

        text.setFillColor(text_color_);
        text.setString(*text_[line_index]);
        text.setPosition(left_border + 30, i * line_height);
        render_texture_.draw(text);
    }

    render_texture_.display();
}

void TextLabel::Render() {
    sf::Sprite sprite(render_texture_.getTexture());

    sprite.setPosition(position_);

    Screen::GetInstance()->GetRenderWindow()->draw(sprite);
}

void TextLabel::Update(AbstractApp *app) {
    AbstractSprite::Update(app);

    if (UpdateActivatable(position_, size_)) {
        ReInit();
    }

    if (IsActive()) {
        for (auto event : *EventHandler::GetInstance()->GetEvents()) {
            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == config::control_buttons_codes::nav_up) {
                    begin_ -= 1;
                    begin_ = std::max(0, begin_);
                    ReInit();
                } else if (event.key.code == config::control_buttons_codes::nav_down) {
                    if (begin_ + 1 < text_.size()) {
                        begin_ += 1;
                        ReInit();
                }
            }
        }
    }
}

std::vector<std::string *> * TextLabel::GetText() {
    return &text_;
}

int TextLabel::GetCharacterSize() {
    return font_size_;
}

float TextLabel::GetTextFieldWidth() {
    return size_.x - 30 - left_border_;
}
