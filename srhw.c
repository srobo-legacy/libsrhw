#include "srhw.h"

static const srhw_driver_t drivers[] = {
	srhw_motor_drv,
	NULL,
};

int srhw_init( void )
{
	srhw_driver_t *drv;

	for( drv = drivers; *drv != NULL; drv ++ ) {
		drv->init();
	}
}

void srhw_free( void )
{
	srhw_driver_t *drv;

	for( drv = drivers; *drv != NULL; drv ++ ) {
		drv->free();
	}
}
