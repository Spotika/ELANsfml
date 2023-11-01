#pragma once

#include "../Button.h"
#include "ELANsfml/Sprites/AbstractSprite.h"
#include <stdexcept>

#ifndef CMAKESFMLPROJECT_BUTTONFUNCTIONAL_H
#define CMAKESFMLPROJECT_BUTTONFUNCTIONAL_H

class ButtonFunctional {
protected:

    template<class T>
    void LinkFunctionToButton(AbstractSprite *button, T* object, void(T::*method)()) {
        auto *new_button = dynamic_cast<Button*>(button);

        if (new_button == nullptr) {
            throw std::invalid_argument("button is not a Button\n");
        }

        new_button->LinkMethod(object, method);
    }
};

#endif //CMAKESFMLPROJECT_BUTTONFUNCTIONAL_H
