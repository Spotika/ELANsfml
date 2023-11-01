#pragma once

#include<string>

#ifndef CMAKESFMLPROJECT_ABSTRACTAPP_H
#define CMAKESFMLPROJECT_ABSTRACTAPP_H

/// <summary>
/// Абстракция приложения
/// </summary>
class AbstractApp {
protected:
    bool is_running_ = true;
public:
    /// <summary>
    /// Имя приложения
    /// </summary>
    std::string name;

    /// <summary>
    /// старт приложения
    /// </summary>
    virtual void *Start(std::pair<std::string, void *> data = {"", nullptr}) = 0;
    /// <summary>
    /// основной цикл приложения
    /// </summary>
    [[noreturn]] virtual void *Loop(std::pair<std::string, void *> data = {"", nullptr}) = 0;
    /// <summary>
    /// остановка приложения
    /// </summary>
    virtual void *Stop() = 0;

    virtual ~AbstractApp() = default;
};



#endif //CMAKESFMLPROJECT_ABSTRACTAPP_H
