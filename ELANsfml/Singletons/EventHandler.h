#pragma once

#include "SFML/Graphics.hpp"
#include "ELANsfml/Helpers/Singleton.h"
#include "ELANsfml/Helpers/Config.h"

#ifndef CMAKESFMLPROJECT_EVENTHANDLER_H
#define CMAKESFMLPROJECT_EVENTHANDLER_H

class EventHandler : public Singleton<EventHandler> {
private:
    std::vector<sf::Event> *event_list_ = nullptr;

    /// Отслеживание глобальных событий
    void HandleGlobalEvent(sf::Event event);

    /// время с прошлого обновления
    float time_elapsed_ = 0;

    /// Глобальные часы
    sf::Clock *clock_ = nullptr;

    sf::Vector2u prev_window_size_ = {config::window::width, config::window::height};

public:

    struct Global {
    };

    Global *global = nullptr;

    /// Инициализация системы событий
    void Init();

    /// обновление событий, вызывается в цикле приложения
    void Update();

    /// <returns>Возвращает указатель на вектор событий</returns>
    [[nodiscard]] std::vector<sf::Event> *GetEvents();

    /// <returns>Указатель на объект clock</returns>
    sf::Clock *GetClock();

    /// Возвращает время в секундах с прошлого обновления
    [[nodiscard]] float GetTimeElapsed() const;
};

#endif //CMAKESFMLPROJECT_EVENTHANDLER_H
