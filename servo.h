#ifndef __SRHW_SERVO_H
#define __SRHW_SERVO_H

#include "drv.h"
#include "srhwctx.h"
#include <stdint.h>

extern const srhw_driver_t srhw_servo_drv;

typedef struct {
	srhw_t* ctx;

	/* The SRIC address of the servo board */
	int addr;
} srhw_servo_t;

/* Return the number of servo controllers */
uint16_t srhw_servo_count( srhw_t* srhw_context );

/* Return handle for servo controller (board) n */
srhw_servo_t* srhw_servo_get( srhw_t* srhw_context, uint16_t n );

/* Get servo n's current angle */
uint16_t srhw_servo_angle_get( srhw_servo_t* servo );

/* Set servo n's angle */
void srhw_servo_angle_set( srhw_servo_t* servo, uint16_t a );

#endif /* __SRHW_SERVO_H */
