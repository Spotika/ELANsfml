#pragma once

#include <string>
#include <map>
#include <stdexcept>
#include <iostream>
#include "ELANsfml/Sprites/AbstractSprite.h"
#include "ELANsfml/Singletons/Screen.h"
#include "ELANsfml/Singletons/EventHandler.h"
#include "ELANsfml/Singletons/ELANsfml.h"

#ifndef CMAKESFMLPROJECT_ABSTRACTDESIGN_H
#define CMAKESFMLPROJECT_ABSTRACTDESIGN_H

class AbstractDesign {
private:

    std::map<std::string, AbstractSprite *> sprites_;

protected:

    void SetSprite(std::string name, AbstractSprite *sprite) {
        sprites_[name] = sprite;
    };

    AbstractSprite *GetSpriteByName(std::string name) {
        if (sprites_.find(name) == sprites_.end()) {
            throw std::invalid_argument("Sprite name is not linked");
        }
        return sprites_[name];
    };

    virtual void Init() = 0;

    virtual void Render(bool do_clear = true) {
        if (do_clear) {
            Screen::GetInstance()->GetRenderWindow()->clear();
        }

        std::vector<AbstractSprite *> for_render(sprites_.size());
        int i = 0;
        for (const auto &elem: sprites_) {
            for_render[i] = elem.second;
            ++i;
        }

        std::sort(for_render.begin(), for_render.end(), [](AbstractSprite *first, AbstractSprite *second) {
            return *first < *second;
        });

        for (AbstractSprite *elem: for_render) {
            elem->Render();
        }

        Screen::GetInstance()->GetRenderWindow()->display();
    };

    virtual void Update(AbstractApp *app) {
        for (auto i: sprites_) {
            i.second->Update(app);
        }

        EventHandler::GetInstance()->Update();
    }

    virtual ~AbstractDesign() {
        for (auto &i: sprites_) {
            delete i.second;
        }
    }

public:
};

#endif //CMAKESFMLPROJECT_ABSTRACTDESIGN_H

