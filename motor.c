#include "motor.h"
#include <glib.h>
#include "sricdriv.h"
#include "sric.h"

struct _srhw_motor {
	srhw_sric_dev sric_data;
	// if we wanted to turn this into a state-storing library,
	// we would just add the state attributes here.
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
	n_motors = srhw_sric_dev_count_get( SRIC_CLASS_MOTOR );

	/* Fill the array */
	motors = malloc( sizeof(srhw_motor_t)  * n_motors );
	srhw_sric_dev_init( n_motors, motors, sizeof(srhw_motor_t), SRIC_CLASS_MOTOR );
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
