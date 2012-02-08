#include "motor.h"
#include <glib.h>
#include "srhwsric.h"
#include "sric.h"

struct _srhw_motor {
	int sric_addr;
	// if we wanted to turn this into a state-storing library,
	// we would just add the state attributes here. (EXCEPT THREADS)
};

typedef enum sric_motor_commnd_t {SET, GET};

#define MIN_SPEED -100
#define MAX_SPEED 100
#define BRAKING_DEFAULT false

typedef struct sric_motor_state_t{
	int8_t speed; // in [-100..100]
	bool brake;
};
	
uint16_t srhw_motor_count( srhw_t* srhw_context )
{
	// g_assert( srhw_context != NULL ); // ??
	return srhw_context->motor.n_motor;
}

srhw_motor_t* srhw_motor_get( srhw_t* srhw_context, uint16_t n )
{
	// g_assert( srhw_context != NULL ); // ??	
	g_assert( n < srhw_context->motor.n_motor );
	return srhw_context->motor.motors[n]; // doesn't this need an &? (ie, right now, is this returning the stucture, not a pointer?)
}

uint16_t srhw_motor_power_get( srhw_t* srhw_context, srhw_motor_t* motor )
{
	g_assert( (srhw_context != NULL) && (motor != NULL) );	
	
	sric_frame tx_frame, rx_frame;
	sric_motor_command_t cmd = GET;
	
	txframe.address = motor->sric_addr;
	txframe.note = -1; // this should always be -1, as this isn't a note.
	txframe.payload_length = 1;
	txframe.payload[0] = unsigned char(cmd);

	if( sric_tx( srhw_context->sric.sric_ctx, @txframe ) == 0 )
	{
		// Cry.
	};
	
	if( sric_rx( srhw_context->sric.sric_ctx, @rxframe, -1) == 0 )
	{
		// Cry. (Again)
	};

	g_assert( rxframe.payload_length == sizeof(sric_motor_state_t) );
	// If that isn't true, then these aren't the droids we're looking for.
	sric_motor_state_t motor_state = sric_motor_state_t(rxframe.payload[0]);
	
	return motor_state.speed;	
}

inline int clamp( int val, min, max )
{
	g_assert(min <= max);	
	if(val < min)
	{
		val = min;
	};

	if(val > max)
	{	
		val = max;	
	};
	return val;
};

void srhw_motor_power_set( srhw_t* srhw_context, srhw_motor_t* motor, uint16_t p )
{	
	g_assert( (srhw_context != NULL) && (motor != NULL) );
	
	sric_frame txframe;
	sric_motor_command_t cmd = SET;
	
	sric_motor_state_t state;
	state.speed = clamp( p, MIN_SPEED, MAX_SPEED );
	state.brake = BRAKING_DEFAULT; 

	txframe.address = motor->sric_addr;
	txframe.note = -1; // This is not a note, thus -1
	txframe.payload_length = sizeof(sric_motor_command_t) + sizeof(sric_motor_state_t);
	txframe.payload[0] = unsigned char(cmd);	
	sric_motor_state_t(txframe.payload[1]) = state; // this is really, really tacky.

	if( sric_tx( srhw_context->sric.sric_ctx, @txframe ) == 0 )
	{
		// Cry and cry again.
	};
}

void srhw_motor_init( srhw_t* ctx )
{
	const sric_device* dev = NULL;

	ctx->n_motors = 0;
	ctx->motors = NULL;

	do
	{
		dev = srhw_enumerate_dev_class( srhw_context, SRIC_CLASS_MOTOR, dev );
		if( sric_dev == NULL )
			continue;

		ctx->n_motors++;
		ctx->motors = realloc( ctx->motors,
				       sizeof(srhw_motor_t) * ctx->n_motors );

		ctx->motors.ctx = ctx;
		ctx->motors.addr = dev->address;

	} while( sric_dev != NULL );
}

void srhw_motor_free( srhw_t* ctx )
{
	if( ctx->motors != NULL )
		free( ctx->motors );
	ctx->motors = NULL;
}

