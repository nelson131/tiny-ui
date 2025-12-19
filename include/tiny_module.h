#ifndef TINY_MODULE_H
#define TINY_MODULE_H

#include "tiny_interface.h"
#include "tiny_vector.h"
#include "tiny_texture.h"
#include <SDL2/SDL.h>
#include <string>

namespace TinyModule {

    struct Base {
        Base();
        virtual ~Base();

        SDL_Renderer* renderer = nullptr;
        TinyInterface* relative_inf = nullptr;
        Vector* relative_position = nullptr;

        Vector global_position = {0, 0};
        Vector local_position = {0, 0};
        Vector size = {0, 0};
        SDL_Rect dest_rect = {0, 0}, src_rect = {0, 0};

        bool visible = false;

        virtual void init(SDL_Renderer* renderer, TinyInterface* relative_inf, Vector position, Vector size);
        virtual void update();
        virtual void render();

        int load_rects(Vector* size);
    };

    struct Image : public Base {
        std::string texture_path = "";
        SDL_Texture* texture = nullptr;

        void init(SDL_Renderer* renderer, TinyInterface* relative_inf, Vector position, Vector size) override;
        void update() override;
        void render() override;

        void load();
    };

};

#endif