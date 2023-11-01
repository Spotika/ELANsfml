#pragma once

#ifndef CMAKESFMLPROJECT_MONOFACTORY_H
#define CMAKESFMLPROJECT_MONOFACTORY_H

template<class Gen, class Type> class MonoFactory {
private:

public:
    /// <summary>
    /// Создает и возвращает функцию, создающую объект типа Type и приводит к более широкому типу Gen
    /// </summary>
    /// <returns>Возвращает указатель на созданную функцию</returns>
    Gen* (*getCreateFunction())() {
        Gen* (*function)() = []() {
            return (Gen*)new Type();
        };
        return function;
    };
};

#endif //CMAKESFMLPROJECT_MONOFACTORY_H
