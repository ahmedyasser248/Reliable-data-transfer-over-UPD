// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <queue>
#include <fstream>

#define PORT 8080

using namespace std;

//Ach-only packets (8 bytes)
struct Ack_packet {
    uint16_t len;
    uint32_t ackno;
};

struct Packet {
    uint16_t len;
    uint32_t seqno;
    char data[500];
};

uint32_t ExpectedSequenceNumber = 0;
string IPAddressServer = "", PortNumber = "", FileName = "";

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
void serializePacket(Packet *packet, char *data) {
    uint16_t *p1 = (uint16_t *) data;
    *p1 = packet->len;
    p1++;
    *p1 = packet->seqno;
    p1++;
    char *p2 = (char *) p1;
    int i = 0;
    while (i < 500) {
        *p2 = packet->data[i];
        p2++;
        i++;
    }
}
*/

/*
void deserializeAckPacket(char *data, Ack_packet *ackPacket) { // we use it on the acknowledge packets sent from the server
    uint16_t *p1 = (uint16_t *) data;
    ackPacket->len = *p1;
    p1++;
    ackPacket->ackno = *p1;
}
*/

void serializePacketAck(Ack_packet *ackPacket,
                        char *data) { // (used at the server) we use it on the acknowledge packets sent from the client to the server
    uint16_t *p1 = (uint16_t *) data;
    *p1 = ackPacket->len;
    p1++;
    *p1 = ackPacket->ackno;
    p1++;
}

void deserializePacket(char *data,
                       Packet *packet) {  // (used at the client) we use it on the packets sent from the server to the client
    uint16_t *p1 = (uint16_t *) data;
    packet->len = *p1;
    p1++;
    packet->seqno = *p1;
    p1++;
    char *p2 = (char *) p1;
    int i = 0;
    while (i < 500) {
        packet->data[i] = *p2;
        p2++;
        i++;
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char const *argv[]) {
    priority_queue<int> priorityQ; //priority queue to arrange the arriving packets

    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *message = "Hello from client";
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    send(sock, message, strlen(message), 0);
    printf("The message has been sent\n");
    valread = read(sock, buffer, 1024);

    struct Packet MyPacket = {5, 0, {'f','j'}};
//    deserializePacket(buffer, &MyPacket);

    int counter = 1;
    std::ifstream file("/home/ahmed/CLionProjects/untitled/test.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            // using printf() in all tests for consistency
            if (counter == 1) {
                IPAddressServer = line.c_str();
            } else if (counter == 2) {
                PortNumber = line.c_str();
            } else {
                FileName = line.c_str();
            }
            printf("%s\n", line.c_str());
            counter++;
        }
        file.close();
    }

    FILE *pFileTXT;
    pFileTXT = fopen("fsfs.txt", "w");
    if (ExpectedSequenceNumber == MyPacket.seqno) {
        pFileTXT = fopen("fsfs.txt", "a");
        for (int i=0; i < sizeof(MyPacket.data)/sizeof(*MyPacket.data) ;i++) {
            fprintf(pFileTXT, "%c" ,MyPacket.data[i]);
        }
        ExpectedSequenceNumber++;
    }

//    printf("%s\n", buffer);
    return 0;
}