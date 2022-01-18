#include <iostream>
#include <queue>
#include <list>
#include "Packet.h"
int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
    std::queue<Packet> packetsQueue;
    //TODO read data from the file into the queue

}
  /*#include <iostream>

#include <cstring>
#include <cinttypes>
#define packetSize sizeof(Packet)
struct Packet{
    uint16_t len;
    uint32_t seqno;
    char data[500];
};
struct Ack_packet{
    uint16_t len;
    uint32_t ackno;
};

void serializePacket(Packet* packet,char *data);
void serializePacketAck(Ack_packet* ackPacket,char *data);
void deserializePacket(char *data ,Packet* packet);
void deserializeAckPacket(char *data,Ack_packet *ackPacket);
int main() {
    Packet *test = new Packet;
    test->len=2078;
    test->seqno=32988;
    char data[500]={'a','v','c'};
    char carrier[packetSize];
    strcpy(test->data,"abdo khaled bashaanjkahabhaghjaghsgkhaghsakh");
    serializePacket(test,carrier);
    Packet *temp = new Packet;
    deserializePacket(carrier,temp);
    std::cout<<temp->data<<std::endl;
    std::cout<<temp->seqno<<std::endl;
    std::cout<<temp->len<<std::endl;
    std::cout<<sizeof(temp->data);

    return 0;
}
void serializePacket(Packet* packet,char *data){
    uint16_t * p1 = (uint16_t*)data;
    *p1=packet->len;
    p1++;
    uint32_t *p2=(uint16_t)
    *p1=packet->seqno;
    p1++;

    char *p2 = (char*)p1;
    int  i = 0;
    while(i<500){
        *p2=packet->data[i];
        p2++;
        i++;
    }

}
void serializePacketAck(Ack_packet* ackPacket,char *data){
    uint16_t * p1 = (uint16_t*)data;
    *p1=ackPacket->len;
    p1++;
    *p1=ackPacket->ackno;
    p1++;
}
void deserializePacket(char *data ,Packet* packet){
    uint16_t *p1 =(uint16_t*)data;
    packet->len=*p1;p1++;
    uint32_t *p2=(uint32_t*)p1;
    packet->seqno=*p2;p2++;
    char *p3 = (char*)p2;
    int  i = 0 ;
    while(i<500){
        packet->data[i]=*p3;
        p3++;
        i++;
    }
}
void deserializeAckPacket(char *data,Ack_packet *ackPacket){
    uint16_t *p1 =(uint16_t*)data;
    ackPacket->len=*p1;
    p1++;
    ackPacket->ackno=*p1;
}
void congestionAvoidance(){

}*/