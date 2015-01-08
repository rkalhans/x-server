#ifndef X_GLOBALS_H
#define X_GLOBALS_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "x_error.h"
#include "operations.h"

typedef int32_t int32;
typedef int64_t int64;

/* SERVER globals*/
#define SERVER_VERSION "X-SERVER-1.0-development-unreleased"
#define SERVER_VERSION_LEN 35
/* Authentication globals  version v-4.0*/
#define AUTH_HANDSHAKE_PACKET_1_LEN 32+SERVER_VERSION_LEN+1


#endif /*X_GLOBALS_H*/
