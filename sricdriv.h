/* 
	A hardware driver to initialise the sric context
	used by all sric-powered hardware present in libsrhw.

	Also provides some convienience functions.
*/
#ifndef __SRHW_DRV_H
#define __SRHW_DRV_H

#include "sric.h"
#include "drv.h"

/* 
	The struct from which all sric-powered devices
	within libsrhw should "derive".
*/
	
typedef struct {
	int sric_addr;
	} srhw_sric_dev_t;

extern const srhw_driver_t srhw_sric_drv;

extern sric_context srhw_sric_ctx; // the library-wide sric context

/* Returns the number of devices of the given sric device class: */
int srhw_sric_dev_count_get( sric_dev_class dev_class );

/* 
	Initialises the field(s) of the /count/ srhw_sric_dev structs /devices/ (potentially 
	contained within other structs of size /struct_size/, which can be sizeof(srhw_sric_dev))
	using the value(s) for devices of class /dev_class/ in the order sric enumerates them. 

	See motor.c for example usage.
*/
void srhw_sric_dev_init( int count, srhw_sric_dev_t* devices, int struct_size, sric_dev_class dev_class );	

void srhw_sric_enumerate_dev_class( srhw_ctx* context, sric_dev_class dev_class, const sric_device* sric_dev );

#endif // __SRHW_DRV_H


