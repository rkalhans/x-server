#ifndef X_NETWORK_H
#define X_NETWORK_H
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

 class Net
 {
public:
    long int last_packet_seq;
    long int max_allowed_packet;
    long int last_packet_len;
    int sock;
    char* buff;
    Net(int _sock){sock= _sock;}
    int x_safe_net_read();
    int x_safe_net_write();
 };
#endif
