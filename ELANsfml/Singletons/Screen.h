#pragma once

#include "ELANsfml/Helpers/Singleton.h"
#include "SFML/Graphics.hpp"

#ifndef CMAKESFMLPROJECT_SCREEN_H
#define CMAKESFMLPROJECT_SCREEN_H

class Screen : public Singleton<Screen> {
private:
    sf::RenderWindow *render_window = nullptr;

    sf::Font* font;

    bool is_resizable_ = true;
public:

    /// Инициализирует видео систему
    void Init();

    /// Возвращает указатель на объект окна
    sf::RenderWindow *GetRenderWindow();

    [[nodiscard]] sf::Font* GetFont();

    void SetView(sf::Vector2f size, sf::Vector2f center);

    void SetResizable(bool is_resizable);

    bool IsResizable() const;
};

#endif //CMAKESFMLPROJECT_SCREEN_H
