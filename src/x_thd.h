/*
 *
 *
 */
#ifndef X_THD_H
#define X_THD_H
#include <x_globals.h>
#include <x_network.h>
#include <pthread.h>   /*posix threads*/
#include <x_idstate.h>
#include <x_com.h>

static Id_manager id_state;

class THD
{
private:
  pthread_t this_thread;
  int thread_id;
  char* query_text;
public:
  Net* net_io;
  X_COMMAND command;
  RESULT command_result;
  THD(Net* _net, void *(*entry)(void *));
  inline int get_thd_id(){return thread_id;}
  inline char* query(){return query_text;}
  void set_query_text();
  int handle_command();
  void send_confirmation_to_client();
};
#endif
