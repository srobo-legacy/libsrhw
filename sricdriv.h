/* 
	A hardware driver to initialise the sric context
	used by all sric-powered hardware present in libsrhw.

	Also provides some convienience functions.
*/
#ifndef __SRHW_DRV_H
#define __SRHW_DRV_H

#include "sric.h"

void srhw_sric_enumerate_dev_class( srhw_ctx* srhw_context, sric_dev_class dev_class, const sric_device* sric_dev );

#endif // __SRHW_DRV_H


