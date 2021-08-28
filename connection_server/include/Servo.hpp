#ifndef SERVO
#define SERVO

#define PIN_BASE 300
#define MAX_PWM 4096
#define HERTZ 50

class Servo {
    public:
        Servo(int port);
        Servo();

        void write(int angle);

        virtual void move(Direction direction, int time);
        virtual void open();
        virtual void close();

    private:
        int _port;
};

#endif