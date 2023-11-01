#include "../src/Apps/MainApp.h"
#include "ELANsfml/Singletons/ELANsfml.h"
#include <iostream>

#include <SFML/Graphics.hpp>
#include <iomanip>
#include <iostream>
#include <sstream>

int main() {
  ELANsfml::LinkApp<MainApp>("MainApp");

  ELANsfml::Start("MainApp");

  return 0;
}
