/*
 */

#include "x_globals.h"
#include "x_network.h"
#include "operations.h"
#include <stdio.h>
int
Net::x_safe_net_read()
{
    if (buff != NULL)
	free(buff);
    /*
     * read the first 4 bytes
     * this will contain the length of the packet <3 B>
     *                    sequence # of the current packet 1 BYTE
     */
     int n= 0, n_temp=0;;
     char buffer[4];
     while (n == 0)
        n = read(sock, buffer, 4);
     if (n<4)
     {
	 error("Unable to read the mysql header!");
	 return -1;
     }
     /* get the size*/
     int32 size= buftoint(buffer, 3);
     //long int seq_number= buftoint(buffer+3, 1);
     this->buff= (char *) malloc(size+1);
     n= 0;
     while( (n < size) && (n_temp >= 0))
     {
       n_temp= read(sock, (this->buff+n), size-n);
       n+=(n_temp>=0)?n_temp:0;
       if (n_temp <= 0)
         break;
     }
     return this->last_packet_len= (n_temp < 0)?-1:size;
}




