#include "motor.h"
#include <glib.h>

struct _srhw_motor {
	int sric_addr;
};

static srhw_motor_t* motors = NULL;
static uint16_t n_motors = 0;

uint16_t srhw_motor_count( void )
{
	return n_motors;
}

srhw_motor_t* srhw_motor_get( uint16_t n )
{
	g_assert( n < n_motors );
	return motors[n];
}

uint16_t srhw_motor_power_get( srhw_motor_t* motor )
{
	/* Interact with the motor board using libsric... */
}

void srhw_motor_power_set( srhw_motor_t* motor, uint16_t p )
{
	/* Interact with the motor board using libsric... */
}

static void srhw_motor_drv_init( void )
{
	/* Ask libsric how many motor controllers there are */
	n_motors = ...;

	/* Fill the array */
	motors = malloc( sizeof(srhw_motor_t) ) * n_motors;
}

static void srhw_motor_drv_free( void )
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
