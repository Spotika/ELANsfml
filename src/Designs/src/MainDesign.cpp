#include "src/Designs/MainDesign.h"
#include "ELANsfml/Sprites/Button.h"
#include "ELANsfml/Sprites/BackgroundColor.h"
#include "ELANsfml/Helpers/Config.h"
#include "ELANsfml/Sprites/TextInput.h"
#include <iostream>
#include "ELANsfml/Sprites/TextLabel.h"
#include "ELANsfml/Sprites/PlainText.h"


void MainDesign::Init() {}

void MainDesign::Render(bool do_clear) {
    AbstractDesign::Render(true);
}
