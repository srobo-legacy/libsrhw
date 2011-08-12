#include "srhw.h"
#include "drv.h"
#include <glib.h>

static const srhw_driver_t drivers[] = {	
	srhw_motor_drv,
	NULL,
};

srhw_ctx* srhw_init( void )
{
	srhw_ctx* new_context = NULL;		
	new_context = getmem( sizeof(srhw_ctx) );
	g_assert( new_context != NULL ); // Check for out of memory. We cannot recover from that.

	srhw_driver_t *drv;
	for( drv = drivers; *drv != NULL; drv ++ ) {
		drv->init( new_context );
	}
	return new_context;
}

void srhw_free( srhw_ctx* srhw_context )
{
	srhw_driver_t *drv;

	for( drv = drivers; *drv != NULL; drv ++ ) {
		drv->free( srhw_context );
	};

	free( srhw_context );
}
