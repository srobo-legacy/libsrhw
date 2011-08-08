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
	}
	while (cur_dev != NULL);

	return count;
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

const srhw_sric_driv = {
	.init = srhw_sric_drv_init;
	.free = srhw_sric_drv_free;
};
