#ifndef TINY_INTERFACE_H
#define TINY_INTERFACE_H

#include "tiny_module.h"
#include "tiny_vector.h"
#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include <memory>

// Interface class
// Invisible(or visible if you want) basis of another modules
// Creates, keeps and changes them all

class TinyInterface {
    public:
    TinyInterface();
    ~TinyInterface();

    Vector position = {0, 0};
    Vector size = {0, 0};
    int id = -1;
    bool visible = false;

    int init(SDL_Renderer* renderer, Vector position, Vector size);
    void update();
    void render();

    template<typename T, typename... Args>
    T* create_module(Args&&... args){
        static_assert(std::is_base_of_v<TinyModule::Base, T>, "T must be part of TinyModule::Base");

        auto module = std::make_unique<T>(std::forward<Args>(args)...);
        if(module->init(renderer, this, get_unique_id()) < 0){
            Logger::print(Logger::ERROR, "Failed to create a module (InterfaceID:", id, ")");
            return nullptr;
        }
        T* raw = module.get();

        stash_modules.push_back(std::move(module));
        return raw;
    }

    int delete_module(TinyModule::Base* module);
    int delete_module_by_id(size_t id);
    int delete_all();

    bool operator == (const TinyInterface& other);

    private:
    size_t get_unique_id();

    std::vector<std::unique_ptr<TinyModule::Base>> stash_modules;

    SDL_Renderer* renderer = nullptr;
};

#endif