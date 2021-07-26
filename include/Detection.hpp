#ifndef DETECTION
#define DETECTION

#include <string>

struct Detection {
    bool empty = false;
    int box[4]; // x,y,w,h
    std::string name;
};

#endif