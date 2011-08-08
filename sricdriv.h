/* 
	A hardware driver to initialise the sric context
	used by all sric-powered hardware present in libsrhw.

	Also provides some convienience functions.
*/
#ifndef __SRHW_DRV_H
#define __SRHW_DRV_H

#include "sric.h"

extern const srhw_driver_t srhw_sric_drv;

extern const sric_context srhw_sric_ctx; // the library-wide sric context

/* Returns the number of devices of the given sric device class: */
int srhw_sric_dev_count( sric_dev_class dev_class );


#endif // __SRHW_DRV_H


