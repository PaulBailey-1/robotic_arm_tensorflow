#include "math.h"
#include "unistd.h"

#include "Client.hpp"
#include "Detection.hpp"

class RobotControl {
    public:
        RobotControl(Client* client);
        void controlLoop();

        void setDetections(std::vector<Detection> detections) {
            if (detections.size() > 0) {
                _target = detections[0];
                _targetPresent = true;
            } else {
                _targetPresent = false;
            }
        }

        void kill() {
            _termination = true;
        }

    private:
        bool _termination = false;

        Detection _target;
        bool _targetPresent = false;

        Client* _client;

        double _alignmentError;
};