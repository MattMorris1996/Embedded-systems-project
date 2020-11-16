
template <typename T>
void send_packet(int id, char * type, char * timestamp, T data);

struct __attribute__((__packed__)) packet {
    int id;
    char type[4];
    char timestamp[8];
    char message[100];
    char delimiter[4];
};