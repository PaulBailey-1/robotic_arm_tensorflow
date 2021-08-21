#include <opencv2/opencv.hpp>

class Camera {
    public:
        Camera();
        void getFrame(unsigned char* &data, unsigned int &size);
    
    private:
        cv::VideoCapture _cap;
};