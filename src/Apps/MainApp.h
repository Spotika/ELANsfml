#pragma once

#include "ELANsfml/Apps/AbstractApp.h"
#include "src/Designs/MainDesign.h"
#include <iostream>

class MainApp : public AbstractApp, MainDesign {
private:
  void *Start(std::pair<std::string, void *> data) override;

  void *Loop(std::pair<std::string, void *> data) override;

  void *Stop() override;

public:
};
