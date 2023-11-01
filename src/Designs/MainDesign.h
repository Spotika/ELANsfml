#pragma once

#include "ELANsfml/Designs/AbstractDesign.h"
#include "ELANsfml/Sprites/Button.h"

#ifndef CMAKESFMLPROJECT_MAINDESIGN_H
#define CMAKESFMLPROJECT_MAINDESIGN_H

class MainDesign : public AbstractDesign {
protected:
  void Init() override;

  void Render(bool do_clear) override;
};

#endif // CMAKESFMLPROJECT_MAINDESIGN_H
