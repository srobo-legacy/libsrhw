#include "motor.h"
#include <glib.h>
#include "srhwsric.h"
#include "sric.h"

struct _srhw_motor {
	int sric_addr;
	// if we wanted to turn this into a state-storing library,
	// we would just add the state attributes here.
};

uint16_t srhw_motor_count( srhw_ctx* srhw_context )
{
	// g_assert( srhw_context != NULL ); // ??
	return srhw_context->motor.n_motor;
}

srhw_motor_t* srhw_motor_get( srhw_ctx* srhw_context, uint16_t n )
{
	// g_assert( srhw_context != NULL ); // ??	
	g_assert( n < srhw_context->motor.n_motor );
	return srhw_context->motor.motors[n]; // doesn't this need an &? (ie, right now, is this returning the stucture, not a pointer?)
}

uint16_t srhw_motor_power_get( srhw_ctx* srhw_context, srhw_motor_t* motor )
{
	/* Interact with the motor board using libsric... */
}

void srhw_motor_power_set( srhw_ctx* srhw_context, srhw_motor_t* motor, uint16_t p )
{
	/* Interact with the motor board using libsric... */
}

static void srhw_motor_drv_init( srhw_ctx* srhw_context )
{
	// g_assert( srhw_context != NULL ); // ??
	srhw_context->motor.n_motor = 0;
	srhw_context->motor.motors = NULL;	
	
	/* Reallocating memory can be slow, so count once, allocate once, get data */
	sric_device* sric_dev = NULL;
	do
	{
		sric_dev = srhw_enumerate_dev_class( srhw_context, SRIC_CLASS_MOTOR, sric_dev );
		if(sric_dev != NULL)
		{
			srhw_context->motor.n_motor += 1;
		}
	} while( sric_dev != NULL );
	// todo: GArray:	
	srhw_context->motor.motors = getmem( sizeof(srhw_motor_t) * srhw_context->motor.n_motor );
	
	sric_dev = NULL;
	int i = 0;
	do
	{
		sric_dev = srhw_enumerate_dev_class( srhw_context, SRIC_CLASS_MOTOR, sric_dev );
		if(sric_dev != NULL)
		{
			srhw_context->motor.motors[i].sric_addr = sric_dev->address;
			i += 1;
		}
	} while( sric_dev != NULL );
	g_assert( i == srhw_context->motor.n_motor ); // else: Much weirdness.
}

static void srhw_motor_drv_free( srhw_ctx* srhw_context )
{
	if( motors != NULL ) {
		free(motors);
		motors = NULL;
	}
}

const srhw_driver_t srhw_motor_drv = {
	.init = init,
	.free = free,
};
