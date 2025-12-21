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

    int free(TinyInterface* interface);
    int free_by_id(size_t id);
    int free_all();
    
    int add(TinyInterface* interface);
    int remove(TinyInterface* interface);
    int contains(TinyInterface* interface);

    int get_unique_id();

    private:
    std::vector<TinyInterface*> stash;
};

#endif