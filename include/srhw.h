#ifndef __SRHW_H
#define __SRHW_H
#include "srhwctx.h"
#include "power.h"
#include "motor.h"
#include "servo.h"
#include "jio.h"

/* Return an initialised context.
   Will return NULL on failure. */
srhw_t* srhw_init( void );

void srhw_free( srhw_t* srhw_context );

#endif /* __SRHW_H */
