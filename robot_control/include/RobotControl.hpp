
#include "Client.hpp"

class RobotControl {
    public:
        RobotControl(Client* client);
        void controlLoop();

        void kill() {
            _termination = true;
        }

    private:
        bool _termination = false;

        Client* _client;
};