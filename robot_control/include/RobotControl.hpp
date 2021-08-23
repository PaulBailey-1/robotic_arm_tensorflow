
#include "Client.hpp"
#include "Output.hpp"

class RobotControl {
    public:
        RobotControl(Client* client);
        void controlLoop();

        void kill() {
            _termination = true;
        }

        Joint base;
        Joint arm;
        Joint elbow;
        Claw claw;

    private:
        bool _termination = false;
        Client* _client;
};