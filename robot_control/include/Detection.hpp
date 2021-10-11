#ifndef DETECTION
#define DETECTION

#include <string>

class Detection {
    public:
        Detection() {};
        Detection(std::string objectName, int dims[4], double conf, int frameWidth, int frameHeight); // x,y,w,h
        
        int x, y, width, height;
        double centerX, centerY, score;
        std::string name;
        int scaleWidth, scaleHeight;

        std::string toString();
};

#endif