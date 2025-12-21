#ifndef TINY_INTERFACE_H
#define TINY_INTERFACE_H

#include "tiny_module.h"
#include "tiny_vector.h"
#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include <memory>

class TinyInterface {
    public:
    TinyInterface();

    void init(SDL_Renderer* renderer, Vector position, Vector size);
    void update();
    void render();

    Vector position = {0, 0};
    Vector size = {0, 0};
    int id = -1;
    bool visible = false;

    bool operator == (const TinyInterface& other);

    private:
    std::vector<std::unique_ptr<TinyModule::Base>> stash_modules;

    SDL_Renderer* renderer = nullptr;
};

#endif