#pragma once

#include "AppManager.h"
#include "ELANsfml/Helpers/MonoFactory.h"
#include "EventHandler.h"
#include "Screen.h"
#include <string>
#include <type_traits>
#include <vector>

#define NAME_ID(appName) *(new std::string(appName))

#ifndef CMAKESFMLPROJECT_ELANSFML_H
#define CMAKESFMLPROJECT_ELANSFML_H

class ELANsfml {
public:
  template <class App> static void LinkApp(std::string app_name) {
    if (!std::is_base_of<AbstractApp, App>::value) {
      throw std::invalid_argument("class App must has base class AbstractApp");
    }

    AppManager::GetInstance()->AddCreateFunction(
        app_name, MonoFactory<AbstractApp, App>().getCreateFunction());
  }

  static void Start(std::string app_name);

  [[noreturn]] static void Stop();
};

#endif // CMAKESFMLPROJECT_ELANSFML_H
