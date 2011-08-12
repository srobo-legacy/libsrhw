#include "sricdriv.h"
#include <glib.h>
#include <stdint.h>

void srhw_sric_enumerate_dev_class( srhw_ctx* srhw_context, sric_dev_class dev_class, const sric_device* sric_dev )
{
	g_assert( srhw_context != NULL );
	// enumerate devices, but only return those of the requested class:
	do
	{
		sric_dev = sric_enumerate_devices( srhw_ctx->sric.sric_ctx, sric_dev );
	} while( (sric_dev != NULL) && (sric_dev->type != dev_class));
};
