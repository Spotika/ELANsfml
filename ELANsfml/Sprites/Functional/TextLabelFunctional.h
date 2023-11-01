#pragma once

#include "ELANsfml/Sprites/TextLabel.h"
#include <stdexcept>

#ifndef CMAKESFMLPROJECT_TEXTLABELFUNCTIONAL_H
#define CMAKESFMLPROJECT_TEXTLABELFUNCTIONAL_H

class TextLabelFunctional {
protected:
    std::vector<std::string*>* GetText(AbstractSprite* sprite) {
        auto* text_label = dynamic_cast<TextLabel*>(sprite);

        if (text_label == nullptr) {
            throw std::invalid_argument("sprite is not a TextLabel");
        }

        return text_label->GetText();
    };
};

#endif //CMAKESFMLPROJECT_TEXTLABELFUNCTIONAL_H
