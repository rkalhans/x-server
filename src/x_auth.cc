#include "x_auth.h"


bool
Authentication_manager::do_auth()
{
  send_initial_packet();
  read_auth_packet();
  if (handle_auth_packet())
  {
	  /* Auth failed */
	  send_auth_confirmation(false);
          return true;
  }
  else
  {
	  /* Auth succeeded*/
	  send_auth_confirmation(true);
          return false;
  }
  return false;/* un-reachable but lets keep the compiler happy */
}

void
Authentication_manager::send_initial_packet()
{
  Net* mysql= this->thd->net_io;
  char buffer[4 + AUTH_HANDSHAKE_PACKET_1_LEN];
  create_initial_packet(buffer, this->thd->get_thd_id());
  int n= 0;
  n= write(mysql->sock, buffer, AUTH_HANDSHAKE_PACKET_1_LEN+4);
  mysql->last_packet_seq=1;
  if (n < 0)
    error("ERROR writing to socket");
}

void
Authentication_manager::create_initial_packet(char* buffer, int thd_id)
{
   int  i= 0;
   buffer[0]=(AUTH_HANDSHAKE_PACKET_1_LEN);
   buffer[1]=0;
   buffer[2]=0;
   buffer[3]=0;
   char* sptr= buffer+4;
   *(sptr++)= '\n';                        /* auth protocol #10          */
   strcpy(sptr, SERVER_VERSION);           /* server version             */
   sptr+= SERVER_VERSION_LEN;
   *sptr++= 0;
   *(sptr++)= thd_id;                /* thread_id 4 B              */
   for (; i < 3; i++)
     *(sptr++)= 0;                       /* thread_id 4 B              */
   for (i= 0; i < 8; i++)
     *(sptr++)= 0;                         /* random seed 8 B            */
   *(sptr++)= 0;
   for (i= 0; i < 2; i++)
     *(sptr++)= 0;                         /* Server capability bit Mask */
   *(sptr++)= 0;                           /* Default collation          */
   for (i= 0; i < 2; i++)
     *(sptr++)= 0;                         /* Status flags               */
   for (i= 0; i < 2; i++)
     *(sptr++)= 0;                         /* Server capability bit Mask */
   *(sptr++)= 0;
   for (i= 0; i < 10; i++)
     *(sptr++)= 0;                         /* __UNUSED__                 */
}

void
Authentication_manager::read_auth_packet()
{
  Net* mysql= this->thd->net_io;
  int n= 0;
  n= mysql->x_safe_net_read();
  if (n < 0) error("ERROR reading from socket");
}

bool
Authentication_manager::handle_auth_packet()
{
  Net* mysql= this->thd->net_io;
  char *sptr= mysql->buff;
  sptr+=2; /*unused capability flags*/
  /* max_allowed_packet_size*/
  mysql->max_allowed_packet= buftoint(sptr, 3);
  sptr+=3; /*3 Bytes*/
  /*compare username*/
  if (memcmp(sptr,"root",4))
    return true;
  else
    return false;
}

void
Authentication_manager::send_auth_confirmation(bool granted)
{
  Net* mysql= this->thd->net_io;
  char packet[100];
  int size, n;
  if (granted)
  {
    size= create_ok_packet(packet);
  }
  else
  {
    char errmsg[]= "Access denied! Only user who can login is the"
    " 'root'";
    size= create_err_packet(packet, errmsg);
  }
  packet[3]= 2;//mysql->last_packet_end_seq++;
  n= write(mysql->sock, packet, size);
  if(n < 0)
  {
    error("Failed to send authorization conformation/denial!");
  }
}

int
Authentication_manager::create_ok_packet(char* buffer)
{
  buffer[0]= 7; /* packet size     */
  buffer[1]= 0;
  buffer[2]= 0;
  buffer[3]= 0;
  buffer[4]= 0; /* OK              */
  buffer[5]= 0; /* affected rows   */
  buffer[6]= 0; /* last insert ID  */
  buffer[7]= 0;
  buffer[8]= 0;
  buffer[9]= 0;/* No warnings      */
  buffer[10]= 0;
	return 11;
}

int
Authentication_manager::create_err_packet(char* buffer, char* msg)
{
  buffer[0]= 2+strlen(msg); /* packet size     */
  buffer[1]= 0;
  buffer[2]= 0;
  buffer[4]= 0xff; /* denied       */
  buffer[5]= 48; /* error num  */
  buffer[6]=0;
  strcpy(buffer+7, msg);
  return 6+ strlen(msg);
}
