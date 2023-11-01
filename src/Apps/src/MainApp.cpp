#include "../MainApp.h"
#include "ELANsfml/Singletons/AppManager.h"
#include "ELANsfml/Singletons/EventHandler.h"
#include "ELANsfml/Singletons/Screen.h"
#include "src/Designs/MainDesign.h"
#include <iostream>
#include <utility>

void *MainApp::Start(std::pair<std::string, void *> data) {
  std::cout << "Starting MainApp\n";

  MainDesign::Init();

  return Loop(data);
}

void *MainApp::Loop(std::pair<std::string, void *>) { return Stop(); }

void *MainApp::Stop() {
  std::cout << "Stopping MainApp\n";
  return nullptr;
}
