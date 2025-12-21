#ifndef TINY_HANDLER_H
#define TINY_HANDLER_H

#include "tiny_interface.h"
#include "tiny_logger.h"
#include <vector>

class TinyHandler {
    public:
    TinyHandler();

    void update();
    void render();
    void free();

    void add(TinyInterface* interface);
    void remove(TinyInterface* interface);
    int contains(TinyInterface* interface);

    int get_unique_id();

    private:
    std::vector<TinyInterface*> stash;
};

#endif