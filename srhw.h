#ifndef __SRHW_H
#define __SRHW_H
#include "motor.h"
#include "srhwctx.h"

/* Return an initialised context.
   Will return NULL on failure. */
srhw_ctx* srhw_init( void );

void srhw_free( srhw_ctx* srhw_context );

#endif /* __SRHW_H */
