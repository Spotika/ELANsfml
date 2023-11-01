#include "ELANsfml/Singletons/ELANsfml.h"
#include "ELANsfml/Singletons/AppManager.h"
#include "ELANsfml/Helpers/MonoFactory.h"
#include "ELANsfml/Apps/AbstractApp.h"
#include "SFML/Graphics.hpp"
#include <stdexcept>
#include <iostream>
#include <utility>

void ELANsfml::Start(std::string app_name) {
    std::cout << "Starting...\n";

    EventHandler::GetInstance()->Init();
    Screen::GetInstance()->Init();

    AppManager::GetInstance()->AddAppToQueue(std::move(app_name));

    AppManager::GetInstance()->StartLoop();

    Stop();
}

void ELANsfml::Stop() {
    std::cout << "Stopping...\n";

    Screen::GetInstance()->GetRenderWindow()->close();

    system("pause");
    exit(0);
}