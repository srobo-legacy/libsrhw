/* 
	Common code related to sric for libsrhw
*/
#ifndef __SRHW_DRV_H
#define __SRHW_DRV_H

#include "sric.h"

struct srhw_sric_ctx {
	sric_context sric_ctx;
}; 

void srhw_sric_enumerate_dev_class( srhw_ctx* srhw_context, sric_dev_class dev_class, const sric_device* sric_dev );

#endif // __SRHW_DRV_H


