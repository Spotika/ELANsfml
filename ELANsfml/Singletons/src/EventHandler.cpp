#include "ELANsfml/Singletons/EventHandler.h"
#include "ELANsfml/Singletons/Screen.h"
#include "ELANsfml/Helpers/Config.h"
#include "ELANsfml/Singletons/ELANsfml.h"
#include <iostream>

void EventHandler::HandleGlobalEvent(sf::Event event) {
    // выход из программы
    if (event.type == sf::Event::Closed) {
        ELANsfml::Stop();
    } else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == config::control_buttons_codes::exit_button) {
            ELANsfml::Stop();
        }
    } else if (event.type == sf::Event::Resized) {
        // При изменении размера окна обновляем размеры View
        sf::Vector2f size(std::max((int)event.size.width, config::window::min_width), std::max((int)event.size.height, config::window::min_height));
        // Позиция View остается по центру
        sf::Vector2f center(event.size.width / 2, event.size.height / 2);

        if (Screen::GetInstance()->IsResizable()) {
            Screen::GetInstance()->GetRenderWindow()->setSize({static_cast<unsigned int>(std::max((int) event.size.width, config::window::min_width)),
                                                               static_cast<unsigned int>(std::max((int) event.size.height,
                                                                                                  config::window::min_height))});
            prev_window_size_ = Screen::GetInstance()->GetRenderWindow()->getSize();
        } else {
            Screen::GetInstance()->GetRenderWindow()->setSize({prev_window_size_});
        }


#ifdef STATIC_Y_AXIS
        Screen::GetInstance()->GetRenderWindow()->setSize({event.size.width, config::window::height});
#endif

        Screen::GetInstance()->SetView(size, center);
    }


}

void EventHandler::Init() {
    event_list_ = new std::vector<sf::Event>();
    clock_ = new sf::Clock();
    global = new Global();
}

void EventHandler::Update() {
    sf::Event event{};
    sf::Window* window = Screen::GetInstance()->GetRenderWindow();
    GetEvents()->clear();
    // добавление событий в список
    while (window->pollEvent(event)) {
        HandleGlobalEvent(event);
        GetEvents()->push_back(event);
    }

    // обновление clock
    time_elapsed_ = GetClock()->restart().asSeconds();
}

std::vector<sf::Event>* EventHandler::GetEvents() {
    return event_list_;
}

sf::Clock* EventHandler::GetClock() {
    return clock_;
}

float EventHandler::GetTimeElapsed() const {
    return time_elapsed_;
}
