#ifndef DETECTION
#define DETECTION

#include <string>

struct Detection {
    int box[4]; // x,y,w,h
    std::string name;
};

#endif