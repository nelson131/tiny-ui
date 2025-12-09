#ifndef TINY_INTERFACE_H
#define TINY_INTERFACE_H

#include <vector>
#include <string>

class TinyInterface {
    public:
    TinyInterface();

    int id = -1;

    bool operator == (const TinyInterface& other);

    private:
    //std::vector<UI> stash;
};

#endif