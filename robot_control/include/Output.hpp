#ifndef OUTPUT
#define OUTPUT

#include "Client.hpp"

class Output {
    public:
        Output(Client* client);

    protected:
        Client* _client;
};

enum Direction
{
    CW = 1,
    CC = -1
};

class Joint : public Output{
    public:
        Joint();
        Joint(Client* client) : Output(client) {};
        void move(Direction dir, int time);
};

class Claw : public Output{
    public:
        Claw();
        Claw(Client* client) : Output(client) {};
        void open();
        void close();
};

#endif