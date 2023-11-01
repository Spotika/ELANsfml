#include <utility>

#include "../TextInput.h"
#include <sstream>
#include <iostream>
#include <iomanip>

TextInput::TextInput(sf::Vector2f position,
                     sf::Vector2f size,
                     OnResizeFunction on_resize,
                     sf::Color text_color,
                     sf::Color base_color,
                     sf::Color active_color,
                     int font_size,
                     int layer) : TextLabel(position,
                                            size,
                                            std::move(on_resize),
                                            false,
                                            base_color,
                                            text_color,
                                            base_color,
                                            active_color,
                                            font_size,
                                            layer),
                                    active_color_(active_color),
                                    base_color_(base_color) {
    text_.emplace_back(new std::string(""));
    TextInput::Resize();
    TextInput::ReInit();
}

void TextInput::Update(AbstractApp *app) {
    TextLabel::Update(app);

    if (IsActive()) {
        for (auto event: *EventHandler::GetInstance()->GetEvents()) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) {
                    text_.emplace_back(new std::string);
                    ReInit();
                }
            } else if (event.type == sf::Event::TextEntered) {
                // Добавляем символы в текст
                if (event.text.unicode == 8) { // Обработка клавиши Backspace
                    if (!text_.empty()) {
                        if (text_.back()->empty()) {
                            if (text_.size() > 1) {
                                delete text_.back();
                                text_.pop_back();
                                ReInit();
                            }
                            continue;
                        }

                        if (text_.empty()) {
                            continue;
                        }

                        text_.back()->pop_back();
                        ReInit();
                    }
                } else {
                    if ((event.text.unicode >= 32 && event.text.unicode <= 126) || event.text.unicode == 8) {
                        if (text_.empty()) {
                            text_.emplace_back(new std::string);
                        }
                        *text_.back() += static_cast<char>(event.text.unicode);
                        ReInit();
                    }
                }
            }
        }
    }
}

void TextInput::Render() {
    TextLabel::Render();
}

sf::Color operator+(const sf::Color& other, int n) {
    return {static_cast<sf::Uint8>(other.r + n), static_cast<sf::Uint8>(other.g + n), static_cast<sf::Uint8>(other.b + n)};
}

void TextInput::ReInit() {
    if (IsActive()) {
        background_color_ = active_color_;
    } else {
        background_color_ = base_color_;
    }

    render_texture_.create(size_.x, size_.y);
    render_texture_.clear(background_color_);

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

    if (IsActive()) {
        sf::RectangleShape highlight;
        int i = static_cast<int>(text_.size()) - 1 - begin_;
        highlight.setPosition({0, static_cast<float>(i * line_height) + 2});
        highlight.setSize({size_.x, static_cast<float>(line_height) + 4});
        highlight.setFillColor(base_color_);
        render_texture_.draw(highlight);

        sf::RectangleShape cursor;
        cursor.setFillColor(active_color_ + 20);
        cursor.setSize({10, static_cast<float>(line_height) + 4});

        if (text_.empty()) {
            cursor.setPosition({2, 2});
        } else {
            text.setString(*text_.back());
            cursor.setPosition({left_border + text.getLocalBounds().width + 32, static_cast<float>(i * line_height) + 2});
        }

        render_texture_.draw(cursor);
    }

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
