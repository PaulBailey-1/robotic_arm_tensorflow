#include "Detection.hpp"

Detection::Detection(std::string objectName, int dims[4], double conf, int frameWidth, int frameHeight) {
    name = objectName;
    score = conf;
    x = dims[0];
    y = dims[1];
    width = dims[2];
    height = dims[3];
    centerX = x + width / 2;
    centerY = y + height / 2;
    scaleWidth = frameWidth;
    scaleHeight = frameHeight;
}

std::string Detection::toString() {
    return "Detection of " + name + " at (" + std::to_string(centerX)
         + ", " + std::to_string(centerY) + ") Scale: [" + std::to_string(scaleWidth)
            + ", " + std::to_string(scaleHeight) + "] Score: " + std::to_string(score);
}