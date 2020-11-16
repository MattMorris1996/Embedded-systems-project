#include "mbed.h"
#include "string.h"
#include "LM75B.h"

#include "message.h"

template <typename T>
void send_packet(int id, char * type, char * timestamp, T data)
{
    char packet_buffer[255];
    
    struct packet send;
    send.id = id;
    strcpy(send.type, type);
    strcpy(send.timestamp, timestamp);
    memcpy(send.message, &data, sizeof(float));
    strcpy(send.delimiter,">>>>");
    
    memcpy(packet_buffer, &send, sizeof(struct packet));
    //memcpy data to packet
    
    //turn off interrupts
    for(int i = 0; i < sizeof(send); i++)
    {
        pc.putc(packet_buffer[i]);
    }    
    //turn on interrupts
}

int main()
{
    pc.baud(9600);
    const int id = 34; //dummy id
    char * timestamp = "12:00:00"; //dummy timestamp
    
    timer_temperature.start(); //timer temperature
    float timer_temperature_start = timer_temperature.read();
    float timer_temperature_duration = 1;
    
    timer_pot1.start(); //timer pot1
    float timer_pot1_start = timer_pot1.read();
    float timer_pot1_duration = 0.25;
    
    timer_pot2.start(); //timer pot2
    float timer_pot2_start = timer_pot2.read();
    float timer_pot2_duration = 0.25;
    
    while(1) {
        if(timer_temperature.read() - timer_temperature_start >= timer_temperature_duration) {
            if (sensor.open()){
                send_packet<float>(id, "TEMP", timestamp, sensor.temp());
                timer_temperature_start = timer_temperature.read();
            }
        }
        if(timer_pot1.read() - timer_pot1_start >= timer_pot1_duration) {
            if (sensor.open()){
                send_packet<unsigned short>(id, "LIGT", timestamp, pot1.read_u16());
                timer_pot1_start = timer_pot1.read();
            }
        }
        if(timer_pot2.read() - timer_pot2_start >= timer_pot2_duration) {
            if (sensor.open()){
                send_packet<unsigned short>(id, "MOIS", timestamp, pot2.read_u16());
                timer_pot2_start = timer_pot2.read();
            }
        }
    }
}