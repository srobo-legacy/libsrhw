#include "srhw.h"

static const srhw_driver_t drivers[] = {
	srhw_sriv_drv,	
	srhw_motor_drv,
	NULL,
};

int srhw_init( void )
{
	srhw_driver_t *drv;

	for( drv = drivers; *drv != NULL; drv ++ ) {
		drv->init();
	}
	return 0;
}

void srhw_free( void )
{
	srhw_driver_t *drv;

	for( drv = drivers; *drv != NULL; drv ++ ) {
		drv->free();
	}
}
