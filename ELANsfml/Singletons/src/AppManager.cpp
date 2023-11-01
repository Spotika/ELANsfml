#include "ELANsfml/Singletons/AppManager.h"

void AppManager::StartLoop() {
    while (!app_queue_.empty()) {
        AbstractApp *cur_app = app_queue_.front().first;
        cur_app->Start(app_queue_.front().second);
        delete app_queue_.back().first;
        app_queue_.pop();
    }
}

void *AppManager::StartApp(std::string name, const std::pair<std::string, void *> data) {
    CheckName(name);
    AbstractApp *new_app = create_function_by_name_[name]();
    auto to_return = new_app->Start(data);
    delete new_app;
    return to_return;
}

void AppManager::AddAppToQueue(std::string name, std::pair<std::string, void *> data) {
    CheckName(name);
    AbstractApp *new_app = create_function_by_name_[name]();
    app_queue_.emplace(new_app, data);
}

void AppManager::AddCreateFunction(std::string name, AbstractApp *(*function)()) {
    create_function_by_name_[name] = function;
}