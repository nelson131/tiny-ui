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

    Vector position = {0, 0};
    Vector size = {0, 0};
    int id = -1;
    bool visible = false;

    void init(SDL_Renderer* renderer, Vector position, Vector size);
    void update();
    void render();

    template<typename T, typename... Args>
    T* create_module(Args&&... args);

    bool operator == (const TinyInterface& other);

    private:
    std::vector<std::unique_ptr<TinyModule::Base>> stash_modules;

    SDL_Renderer* renderer = nullptr;
};

#endif