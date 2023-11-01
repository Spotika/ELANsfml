#pragma once

#include "SFML/Graphics.hpp"
#include "ELANsfml/Apps/AbstractApp.h"
#include "ELANsfml/Singletons/EventHandler.h"
#include "ELANsfml/Singletons/Screen.h"
#include <functional>
#include <utility>

#ifndef CMAKESFMLPROJECT_ABSTRACTSPRITE_H
#define CMAKESFMLPROJECT_ABSTRACTSPRITE_H


class AbstractSprite {
public:
    struct dims {
        sf::Vector2f size;
        sf::Vector2f position;

        dims(sf::Vector2f size, sf::Vector2f position) : size(size), position(position) {}
    };
protected:
    int layer_;

    sf::Vector2f position_;
    sf::Vector2f size_;

    std::function<dims (sf::Vector2f, sf::Vector2f, sf::Vector2f)> get_dims_on_resize_;
public:
    AbstractSprite(sf::Vector2f position,
                   sf::Vector2f size,
                   std::function<dims (sf::Vector2f, sf::Vector2f, sf::Vector2f)> on_resize,
                   int layer = 0) : position_(position),
                                    size_(size),
                                    layer_{layer},
                                    get_dims_on_resize_(std::move(on_resize)) {}

    AbstractSprite() : position_({0, 0}), size_({0, 0}), layer_{0} {}

    [[nodiscard]] int GetLayer() const {
        return layer_;
    };

    void SetLayer(int layer) {
        layer_ = layer;
    }

    bool operator<(const AbstractSprite &other) const {
        return GetLayer() < other.GetLayer();
    }

    virtual ~AbstractSprite() = default;

    virtual void Update(AbstractApp *app) {
        for (auto event : *EventHandler::GetInstance()->GetEvents()) {
            if (event.type == sf::Event::Resized) {
                Resize();
            }
        }
    };

    sf::Vector2f GetPosition() {
        return position_;
    }

    // Отображение элемента на экран
    virtual void Render() = 0;

    // Переинициализация всех полей для отрисовки
    virtual void ReInit() {};

    // Что происходит когда меняется размер окна
    virtual void Resize() {
        dims result = get_dims_on_resize_({static_cast<float>(Screen::GetInstance()->GetRenderWindow()->getSize().x), static_cast<float>(Screen::GetInstance()->GetRenderWindow()->getSize().y)},
                                          {size_},
                                          {position_});
        size_ = result.size;
        position_ = result.position;

        ReInit();
    }
//    virtual sf::RenderTexture GetRenderTexture() = 0;
};

using OnResizeFunction = std::function<AbstractSprite::dims (sf::Vector2f, sf::Vector2f, sf::Vector2f)>;

#define ON_RESIZE [](sf::Vector2f window_size, sf::Vector2f size, sf::Vector2f position) -> AbstractSprite::dims
#define NORMAL_RESIZE {return {size, position};}

#endif //CMAKESFMLPROJECT_ABSTRACTSPRITE_H
