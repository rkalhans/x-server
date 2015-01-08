#include "x_server.h"
/*
 *
 * @param msg
 */

THD* threads[100];
int threads_index= 0;
int main(int argc, char *argv[])
{
  int sockfd, newsockfd, portno;
  socklen_t clilen;
  struct sockaddr_in serv_addr, cli_addr;

  if (argc < 2)
  {
    fprintf(stderr,"ERROR, no port provided\n");
    exit(1);
  }
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    error("ERROR opening socket");
  bzero((char *) &serv_addr, sizeof(serv_addr));
  portno = atoi(argv[1]);
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(portno);
  if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    error("ERROR on binding");
  listen(sockfd,100);
  clilen = sizeof(cli_addr);
     while (true)
     {
         newsockfd = accept(sockfd,
               (struct sockaddr *) &cli_addr, &clilen);
         if (newsockfd < 0)
             error("ERROR on accept");
         Net* mysql= new Net(newsockfd);
         THD* thd= new THD(mysql, handle_one_connection);
         if (threads_index < 100)
           threads[threads_index++]= thd;
     } /* end of while */
     close(sockfd);
     return 0; /* we never get here */
}

void* handle_one_connection(void* _thd)
{
  /* We have got the pointer to the THD object to propogate and have fun */
  THD *thd= (THD *)_thd;

  /* Start Authentication using Authentication manager */
  Authentication_manager* auth_manager= new Authentication_manager(thd);
  if (auth_manager->do_auth())
  {
    pthread_exit(0);
    return (void*) _thd;
  }
  wait_for_query(thd);
  return (void*) _thd;
}

void  wait_for_query(THD *thd)
{
  Net *mysql= thd->net_io;
  int n=0;//, size=0, i= 0;
  //char ok_packet[100];
  while (n >= 0)
  {
    n= mysql->x_safe_net_read();
    if (n < 0)
    {
      error("error reading from the client");
      break;
    }
    thd->handle_command();
  }
  close(mysql->sock);
  pthread_exit(0);
}

int dummy_create_ok_packet(char* buffer)
{
  buffer[0]= 7; /* packet size     */
  buffer[1]= 0;
  buffer[2]= 0;
  buffer[3]= 1;
  buffer[4]= 0; /* OK              */
  buffer[5]= 0; /* affected rows   */
  buffer[6]= 0; /* last insert ID  */
  buffer[7]= 0;
  buffer[8]= 0;
  buffer[9]= 0;/* No warnings      */
  buffer[10]= 0;
        return 11;
}



