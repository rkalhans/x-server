#ifndef XSERVER_H
#define XSERVER_H
#include "x_globals.h"
#include "x_thd.h"
#include "x_auth.h"
#include "operations.h"

void * handle_one_connection(void *_thd);
void  wait_for_query(THD *thd);
int dummy_create_ok_packet(char* buffer);
#endif /*XSERVER_H*/
