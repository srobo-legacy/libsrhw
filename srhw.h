#ifndef __SRHW_H
#define __SRHW_H
#include "motor.h"

/* Initialise the library.
   Return 0 on success, -ve on fail. */
int srhw_init( void );

void srhw_free( void );

#endif /* __SRHW_H */
