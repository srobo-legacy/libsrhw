#ifndef __SRHW_MOTOR_H
#define __SRHW_MOTOR_H
#include "drv.h"
#include "srhwctx.h"
#include <stdint.h>

extern const srhw_driver_t srhw_motor_drv;
typedef struct _srhw_motor srhw_motor_t;

struct srhw_motor_ctx { // the motor-related info held within a context.
	uint16_t n_motors;
	srhw_motor_t* motors;
};

/* Return the number of motor controllers */
uint16_t srhw_motor_count( srhw_ctx* srhw_context );

/* Return handle for motor controller n */
srhw_motor_t* srhw_motor_get( srhw_ctx* srhw_context, uint16_t n );

/* Get motor power */
uint16_t srhw_motor_power_get( srhw_ctx* srhw_context, srhw_motor_t* motor );

/* Set motor power */
void srhw_motor_power_set( srhw_ctx* srhw_context, srhw_motor_t* motor, uint16_t p );

#endif	/* __SRHW_MOTOR_H */
