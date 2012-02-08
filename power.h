#ifndef __SRHW_POWER_H
#define __SRHW_POWER_H
#include "srhwctx.h"
#include <stdint.h>

typedef struct {
	srhw_t *ctx;

	/* The SRIC address of the power board */
	int addr;
} srhw_power_t;

void srhw_power_init( srhw_t* ctx );
void srhw_power_free( srhw_t* ctx );

/* Return the number of power boards */
uint16_t srhw_power_count( srhw_t* ctx );

/* Grab power board n */
srhw_power_t* srhw_power_get( srhw_t* ctx, uint16_t n );

/* Set the LEDs (TODO: define what vals is, or expand it into multiple vars) */
void srhw_power_set_leds( srhw_power_t* pwr, uint8_t vals );

/* Get the state of the LEDs */
uint8_t	srhw_power_get_leds( srhw_power_t* pwr );

/* Turn the motor rail on/off */
void srhw_power_motor_rail_set( srhw_power_t* pwr, bool state );

/* TODO: beep API */

#endif	/* __SRHW_POWER_H */
