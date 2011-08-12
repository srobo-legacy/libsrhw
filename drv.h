#ifndef __SRHW_DRV_H
#define __SRHW_DRV_H
#include <stdint.h>
#include "srhwctx.h"

typedef struct {
	void (*init) ( srhw_ctx* new_context );
	void (*free) ( srhw_ctx* doomed_context );
} srhw_driver_t;

#endif	/* __SRHW_DRV_H */
