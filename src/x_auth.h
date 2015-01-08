#ifndef X_AUTH_H
#define X_AUTH_H

#include "x_globals.h"
#include "x_auth.h"
#include "x_thd.h"

class Authentication_manager
{
private:
  THD* thd;
protected:
  void send_initial_packet();
  void create_initial_packet(char* buffer, int thd_id);
  void read_auth_packet();
  bool handle_auth_packet();
  void send_auth_confirmation(bool granted);
  int create_ok_packet(char* buffer);
  int create_err_packet(char* buffer, char* msg);
public:
   bool do_auth();
   Authentication_manager(THD* _thd){thd= _thd;}
};

#endif
