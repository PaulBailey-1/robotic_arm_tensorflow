// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 7070

int main(int argc, char const *argv[])
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "192.168.1.67", &serv_addr.sin_addr) <= 0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    send(sock, hello, strlen(hello), 0);
    printf("Hello message sent\n");
    valread = read(sock, buffer, 1024);
    printf("%s\n", buffer);
    return 0;
}

// #include <thread>
// #include <vector>

// #include "RobotArm.hpp"
// #include "Vision.hpp"
// #include "Output.hpp"
// #include "Detection.hpp"

// int main() {

//     RobotArm* robotArm = new RobotArm();
//     Vision* vision = new Vision();
//     Output* output = new Output(robotArm);

//     std::thread visionThread(&Vision::detectionLoop, vision);
//     std::thread robotArmThread(&RobotArm::servoControlLoop, robotArm);

//     while(!output->terminated) {
//         std::vector<Detection*> detections;
//         if (vision->getDetections(detections)) {
//             output->setDetections(detections);
//         }
//         output->frameUpdate(vision->getFrame());
//     }

//     output->closeWindow();
//     vision->termination = true;
//     visionThread.join();
//     robotArm->termination = true;
//     robotArmThread.join();

//     return 0;
// }