
#include "mbed.h"

//enum for specifying agrinet modes

//XBEE Init
static Serial serial_port(USBTX, USBRX);

InterruptIn coulomb_counter1(p5);
InterruptIn coulomb_counter2(p6);

//Get TimeStamp Function

//Coulomb Counter Interrupt Handler
volatile int coulombs_main = 0;

//main battey system
void counter_main()
{
    coulombs_main += 1;
}

//secondary battery system
volatile int coulombs_backup = 0;
void counter_backup()
{
    coulombs_backup += 1;
}

enum agriCmd {
    NONE,
    WAKE,
    SLEEP,
    RETRIEVE_ALL,
    RETRIEVE_VITAL,
    BATTERY_RESET,
};

volatile agriCmd remote_action = NONE;
//Serial Data Recieved Interrupt Handler
void base_station_recv_interrupt()
{
    //parse and determine command
    remote_action = NONE;
}

void battery_reset_btn()
{
    remote_action = BATTERY_RESET;
}

//Send Agrinet Packet Function
template <typename T>
void send_packet(int id, char * type, double timestamp, T data)
{
    char packet_buffer[255];
    //turn off interrupt
    
    //memcpy data to packet
    for(int i = 0; i < sizeof(packet_buffer); i++)
    {
        serial_port.putc(packet[i]);
    }    
    //turn on interrupts
}

//Save to  USB Storage format
template <typename T>
void send_packet(int id, char * type, double timestamp, T data)
{
    //save standard packet to usb storage
}

enum agriState {
    BASE_STATION_PAIRING,
    ROUTINE_LOGGING_INIT,
    ROUTINE_LOGGING,
    LOW_POWER_INIT,
    LOW_POWER,
    BATTERY_RESET,
    POWER_DOWN,
};

agriState current_mode = BASE_STATION_PAIRING;

int main() {
    bool bpower_on = true;
    
    //read EEPROM here for start up data
    
    //start counter interrupts
    coulomb_counter1.rise(&counter_main);
    coulomb_counter2.rise(&counter_backup);
    
    //further interrupts for buttons
    
    while(bpower_on){
        switch(current_mode){
            case BASE_STATION_PAIRING:
                serial_port.attach(&base_station_recv_interrupt, SerialBase::RxIrq);

                //Green Pulsing LED
                
                //Broadcast Signal to Base Station
                
                //Check if pairing data has been recieved
                if (true) {
                    //Save data to EEPROM
                    
                    //Move to routine logging initialisation
                    current_mode = ROUTINE_LOGGING_INIT;
                }
                break;
            case ROUTINE_LOGGING_INIT:
                //Green Pulsing LED
                
                //Set sampling timers here
                
                //Init Sensors and Peripherals Here
                
                current_mode = ROUTINE_LOGGING;
                break;
            case ROUTINE_LOGGING:
                //Solid Green LED
                if(true /*Temperature Timer*/){
                    //To Do configure timer
                    
                    //Get Data
                    
                    //Get Timestamp
                    
                    //Send Data or Save
                    
                    //Reset Timer
                }
                if(true /*Soil Temperature*/) {
                    
                }
                if(true /*Soil Humidity*/){
                
                }
                if(true /*Soil Moisture*/){
                    
                }
                if(true /*Soil Conductivity*/) {
                
                }
                if(true /*Soil PH*/) {
                
                }
                if(true /*Surface Light*/) {
                
                }
                if(true /*GPS Pos*/) {
                
                }
                if (true /*Power*/) {
                
                }
                break;
            case LOW_POWER_INIT:
                //Orange Pulsing
                
                //Disable non essential peripherals
                
                current_mode = LOW_POWER;
                break;
            case LOW_POWER:
                //Set Orange LED
                
                break;
            case POWER_DOWN:
                //Red Pulsing LED
                
                //Save to EEPROM
                
                bpower_on = false;
                break
        }
        
        //commands
        if (remote_action == RETRIEVE_ALL /*send all*/){
            //call all functions
        }
        
        if (remote_action == RETRIEVE_VITAL /*send vital*/) {
            //call subset of logging functions
        }
        
        if (remote_action == BATTERY_RESET) {
            //reset battery values to 0
            coulombs_backup = 0;
        }
        
        remote_action = NONE;
    }

    return 0;
}
