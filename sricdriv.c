#include "sricdriv.h"
#include <glib.h>
#include <stdint.h>

int srhw_sric_dev_count_get( sric_dev_class dev_class )
{
	sric_device* cur_dev = NULL;
	int count = 0;
	// Enumerate through all devices, incrementing count if
	// we find one of class dev_class.
	do
	{
		cur_dev = sric_enumerate_devices( srhw_sric_ctx, cur_dev);
		if((cur_dev) && (cur_dev->type == dev_class))
		{
			count += 1;
		};
	} while (cur_dev != NULL);

	return count;
};

void srhw_sric_dev_init( int count, srhw_sric_dev* devices, int struct_size, sric_dev_class dev_class )
{
	// check that at least count devices of the specified class exist:
	g_assert( count <= srhw_sriv_dev_count_get( dev_class ) );
	g_assert( devices != NULL ); // shouldn't happen (this is an internal routine)
	g_assert( struct_size >= 0 ); // More horrifying possible bugs.
	
	sric_device* cur_dev = NULL;
	/* Algorithm:
		Enumerate devices.
		For each device, check if cur_dev->type == dev_class
		if so, then 
			devices->$FIELD = $VALUE; (currently only sric_addr)			
			count -= 1; 
			devices += struct_size;
		
		if we run out of devices, ensure we found all the devices
		the caller expected (ie, count == 0) before returning.
	*/
	do
	{
		cur_dev = sric_enumerate_devices( srhw_sric_ctx, cur_dev );
		if(!cur_dev)
		{
			g_assert( count == 0 );
			return;
		};
		if(cur_dev->type == dev_class)
		{
			devices->sric_addr = cur_dev->address;
			count -= 1;
			devices += struct_size;
		};
	} while(cur_dev != NULL);
};

static void srhw_sric_drv_init ( void )
{
	srhw_sric_ctx = sric_init();
	// check for errors:
	g_assert( sric_get_error( srhw_sric_ctx ) == SRIC_ERROR_NONE );
};

static void srhw_sric_drv_free ( void )
{
	sric_quit( srhw_sric_ctx );
};

const srhw_driver_t srhw_sric_drv = {
	.init = srhw_sric_drv_init;
	.free = srhw_sric_drv_free;
};
