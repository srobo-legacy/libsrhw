#include "motor.h"
#include <glib.h>
#include "sricdriv.h"
#include "sric.h"

struct _srhw_motor {
	srhw_sric_dev sric_data;
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
	/* Ask libsric how many motor controllers there are */
	n_motors = srhw_sric_dev_count_get( SRIC_CLASS_MOTOR );

	/* Fill the array */
	motors = malloc( sizeof(srhw_motor_t)  * n_motors );
	srhw_sric_dev_init( n_motors, motors, sizeof(srhw_motor_t), SRIC_CLASS_MOTOR );
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
