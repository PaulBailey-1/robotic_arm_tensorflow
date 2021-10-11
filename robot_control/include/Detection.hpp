#ifndef DETECTION
#define DETECTION

#include <string>

class Detection {
    public:
        Detection(std::string objectName, int dims[4], int frameWidth, int frameHeight); // x,y,w,h
        
        double x, y, width, height, centerX, centerY;
        std::string name;
        int scaleWidth, scaleHeight;

        std::string toString();
};

#endif