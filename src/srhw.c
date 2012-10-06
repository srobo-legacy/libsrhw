#include "sric.h"
#include "srhw.h"
#include <glib.h>

srhw_t* srhw_init( void ) {
	srhw_t* new_context = NULL;
	new_context = getmem( sizeof(srhw_t) );
	g_assert(new_context != NULL); // Check for out of memory. We cannot recover from that.

	(*new_context).ctx = &sric_init();

	srhw_power_init(new_context);
	srhw_motor_init(new_context);
	srhw_servo_init(new_context);
	srhw_jio_init(new_context);
	
	return new_context;
}

void srhw_free( srhw_t* srhw_ctx ) {
	srhw_power_free(srhw_ctx);
	srhw_motor_free(srhw_ctx);
	srhw_servo_free(srhw_ctx);
	srhw_jio_init(srhw_ctx);

	free( (*srhw_ctx).ctx );
	free( srhw_ctx );
}
