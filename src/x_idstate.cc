#include <x_idstate.h>

Id_manager::Id_manager()
{
  if (!thd_lock_inited)
  {
    /* Initialize the lock */
    pthread_mutex_init(&THD_LOCK, NULL);
    thd_lock_inited= true;
  }
}


void
Id_manager::set_active_thread_id(int * _thread_id)
{
  pthread_mutex_lock(&(this->THD_LOCK));
  this->active_thread_id++;
  *_thread_id= this->active_thread_id;
  pthread_mutex_unlock(&(this->THD_LOCK));
}
