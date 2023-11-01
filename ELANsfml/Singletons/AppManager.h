#pragma once

#include "ELANsfml/Helpers/Singleton.h"
#include "ELANsfml/Apps/AbstractApp.h"
#include <map>
#include <string>
#include <exception>
#include <queue>
#include <stdexcept>

#ifndef CMAKESFMLPROJECT_APPMANAGER_H
#define CMAKESFMLPROJECT_APPMANAGER_H

class AppManager : public Singleton<AppManager> {
private:
    std::map<std::string, AbstractApp* (*)()> create_function_by_name_;
    std::queue<std::pair<AbstractApp*, std::pair<std::string, void*>>> app_queue_;

    /// <summary>
    /// вызывает исключение, если ключ name отсутствует
    /// </summary>
    /// <param name="">Имя приложения</param>
    void CheckName(std::string name) {
        if (create_function_by_name_.find(name) == create_function_by_name_.end()) {
            throw std::invalid_argument("App name is not linked");
        }
    }
public:
    /// <summary>
    /// запуск основного цикла программы
    /// </summary>
    void StartLoop();
    /// <summary>
    /// добавление приложения в очередь для запуска
    /// </summary>
    /// <param name="name">Имя приложения</param>
    void AddAppToQueue(std::string name, std::pair<std::string, void *> data = {"", nullptr});
    /// <summary>
    /// Запуск приложения на месте, не дожидаясь окончания предыдущего
    /// </summary>
    /// <param name="name">Имя преложения</param>
    void * StartApp(std::string name, const std::pair<std::string, void *> data = {"", nullptr});
    /// <summary>
    /// Добавление функции создания объекта приложения
    /// </summary>
    /// <param name="name">Имя приложения</param>
    /// <param name="function">Указатель на функцию</param>
    void AddCreateFunction(std::string name, AbstractApp* (*function)());
};

#endif //CMAKESFMLPROJECT_APPMANAGER_H
