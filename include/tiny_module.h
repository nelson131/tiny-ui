#ifndef TINY_MODULE_H
#define TINY_MODULE_H

#include "tiny_text.h"
#include "tiny_vector.h"
#include "tiny_texture.h"
#include <SDL2/SDL.h>
#include <string>

// Modules class
// Objects of UI

struct TinyInterface;

namespace TinyModule {

    struct Base {
        Base(Vector pos = {}, Vector size = {});
        virtual ~Base();

        SDL_Renderer* renderer = nullptr;
        TinyInterface* relative_inf = nullptr;
        Vector* relative_position = nullptr;

        size_t id = -1;

        Vector global_position = {0, 0};
        Vector local_position = {0, 0};
        Vector size = {0, 0};
        SDL_Rect dest_rect = {0, 0}, src_rect = {0, 0};

        bool visible = false;

        virtual int init(SDL_Renderer* renderer, TinyInterface* relative_inf, size_t id);
        virtual void update();
        virtual void render();

        int setup(SDL_Renderer* renderer, TinyInterface* relative_inf, std::string module_name, size_t id);
        int load_rects(Vector* size);
    };

    struct Image : public Base {
        Image(std::string texture, Vector position, Vector size);
        ~Image();
        std::string texture_path = "";
        SDL_Texture* texture = nullptr;

        int init(SDL_Renderer* renderer, TinyInterface* relative_inf, size_t id) override;
        void update() override;
        void render() override;

        void load();
    };

    struct Text : public Base {
        Text(std::string font_path, std::string content, Vector position, Vector size);
        ~Text();
        TinyText text;
        std::string font_path = "";
        std::string content = "";

        int init(SDL_Renderer* renderer, TinyInterface* relative_inf, size_t id) override;
        void update() override;
        void render() override;
    };
};

#endif