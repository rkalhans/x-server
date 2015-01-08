
#ifndef X_IDSTATE_H
#define X_IDSTATE_H
#include <x_globals.h>
#include <pthread.h>

class Id_manager
{
private:
  int active_thread_id;
  pthread_mutex_t THD_LOCK;
public:
  bool thd_lock_inited;
  void set_active_thread_id(int * _thread_id);
  Id_manager();
};
#endif
