#ifndef OPERATIONS_H
#define OPERATIONS_H
#include "x_globals.h"

typedef int32_t int32;
typedef int64_t int64;

/**
 *
 * @param  __UNUSED__
 */

inline unsigned short swap_16bit(unsigned short us)
{
    return (unsigned short)(((us & 0xFF00) >> 8) |
                            ((us & 0x00FF) << 8));
}

inline unsigned long swap_32bit(unsigned long ul)
{
    return (unsigned long)(((ul & 0xFF000000) >> 24) |
                           ((ul & 0x00FF0000) >>  8) |
                           ((ul & 0x0000FF00) <<  8) |
                           ((ul & 0x000000FF) << 24));
}

inline int32 buftoint(char* buff, int bytes)
{
	int32 ret= 0;
	memcpy(&ret, buff, bytes);
	return ret;
}
#endif




