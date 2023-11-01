#pragma once

#ifndef SFMLTEMPLATE_SINGLETON_H
#define SFMLTEMPLATE_SINGLETON_H

template <class T>
class Singleton {
protected:
    Singleton() = default;
    Singleton(const Singleton&) = default;
public:
    static T* GetInstance() {
        static T instance;
        return &instance;
    }
};

#endif //SFMLTEMPLATE_SINGLETON_H
