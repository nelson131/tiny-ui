#ifndef TINY_HANDLER_H
#define TINY_HANDLER_H

#include "tiny_interface.h"
#include "tiny_logger.h"
#include <vector>

// Handler class
// Keeps storage of interfaces
// Given an access to all of them

class TinyHandler {
    public:
    TinyHandler();

    void update();
    void render();
    
    int add(TinyInterface* interface);
    int contains(TinyInterface* interface);
    TinyInterface* get(size_t id);

    int remove(TinyInterface* interface);
    int remove_by_id(size_t id);
    int remove_all();

    int get_unique_id();

    private:
    std::vector<TinyInterface*> stash;
};

#endif