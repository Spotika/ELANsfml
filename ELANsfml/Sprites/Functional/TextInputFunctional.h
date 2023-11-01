#pragma once

#include "ELANsfml/Sprites/TextInput.h"

#ifndef CMAKESFMLPROJECT_TEXTINPUTFUNCTIONAL_H
#define CMAKESFMLPROJECT_TEXTINPUTFUNCTIONAL_H

class TextInputFunctional {
public:
    static std::vector<std::string*>* GetContainedText(AbstractSprite *text_input) {
        auto *new_button = dynamic_cast<TextInput*>(text_input);

        if (new_button == nullptr) {
            throw std::invalid_argument("button is not a Button\n");
        }

        return new_button->GetText();
    }
};

#endif //CMAKESFMLPROJECT_TEXTINPUTFUNCTIONAL_H
