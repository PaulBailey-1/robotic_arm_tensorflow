#ifndef OUTPUT
#define OUTPUT

#include "Client.hpp"

class Output {
    public:
        Output(int port);

    private:
        int _port;
        Client *client;
};

enum Direction
{
    CW = 1,
    CC = -1
};

class Joint : public Output{
    public:
        Joint();
        Joint(int port) : Output(port) {};
        void move(Direction dir, int time);
};

class Claw : public Output{
    public:
        Claw();
        Claw(int port) : Output(port) {};
        void open();
        void close();
};

#endif