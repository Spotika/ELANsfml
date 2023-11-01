#pragma once

#include<string>
#include "SFML/Graphics.hpp"
#include <numbers>

//#define STATIC_Y_AXIS

#ifndef CMAKESFMLPROJECT_CONFIG_H
#define CMAKESFMLPROJECT_CONFIG_H

namespace config {
    namespace window {
        /// <summary>
        /// ширина окна
        /// </summary>
        static const int width = 1200;
        /// <summary>
        /// высота окна
        /// </summary>
        static const int height = 1000;

        static const int min_width = 450;

        static const int min_height = 400;
        /// <summary>
        /// Описание окна
        /// </summary>
        static const std::string title = "SFMLtemplate";
        /// <summary>
        /// ФПС игры
        /// </summary>
        static const int FPS = 240;
    } // namespace window

    namespace color {
        static const sf::Color black {0, 0, 0};
        static const sf::Color white {255, 255, 255};
        static const sf::Color grey {100, 100, 100};
        static const sf::Color green {0, 255, 0};
        static const sf::Color dark_grey {40, 40, 40};
        static const sf::Color dark_green {0, 100, 0};
    } // namespace color

    namespace design {
        static const auto btn_color = sf::Color({119, 101, 227});
        static const auto btn_text_color = color::white;
        static const int btn_font_size = 30;
        static const int text_font_size = 30;
        static const auto btn_background_color = sf::Color({47, 36, 44});
        static const auto background_color = sf::Color({25, 25, 25});
        static const auto text_label_color = sf::Color({50, 50, 50});
        static const auto text_color = sf::Color({238, 180, 179});
        static const int corner_radius = 10;
        static const auto side_text_color = sf::Color({150, 150, 150});
        static const auto side_color = sf::Color({40, 40, 40});
//        static const auto background_color = sf::Color({80, 34, 116});
    }

    namespace control_buttons_codes {
        /// <summary>
        /// кнопка выхода
        /// </summary>
        static const auto exit_button = sf::Keyboard::Escape;
        static const auto nav_up = sf::Keyboard::Up;
        static const auto nav_down = sf::Keyboard::Down;
    } // namespace control_buttons_codes

} // namespace config
#endif //CMAKESFMLPROJECT_CONFIG_H
