/*
 * x_thd.cc
 *
 *  Created on: 26-Dec-2012
 *      Author: rohit
 */
#include "x_thd.h"


THD::THD(Net* _net, void *(*entry)(void *))
{
  net_io= _net;
  id_state.set_active_thread_id(&this->thread_id);
  pthread_create(&this_thread, NULL, entry, (void *)this);
}

void
THD::set_query_text()
{
 this->query_text=  this->net_io->buff+1;
}


void
THD::send_confirmation_to_client()
{

}
