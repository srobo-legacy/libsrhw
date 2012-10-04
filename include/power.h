#ifndef __SRHW_POWER_H
#define __SRHW_POWER_H
#include "srhwctx.h"
#include <stdint.h>

struct srhw_power_s;
typedef struct srhw_power_s srhw_power_t;

void srhw_power_init( srhw_t* ctx );
void srhw_power_free( srhw_t* ctx );

/* Return the number of power boards */
uint16_t srhw_power_count( srhw_t* ctx );

/* Grab power board n */
srhw_power_t* srhw_power_get(srhw_t* ctx);

/* Get the voltage being supplied by the battery */
void srhw_power_supply_get( srhw_power_t* pwr, float* voltage, float* current );

/* Set the LEDs */
void srhw_power_leds_set( srhw_power_t* pwr, uint8_t vals );

/* Get the state of the LEDs */
uint8_t	srhw_power_leds_get( srhw_power_t* pwr );

/* Set an LED */
void srhw_power_led_set(srhw_power_t* pwr, int led, bool state);

/* Get the state of an LED */
bool srhw_power_led_get(srhw_power_t* pwr, int led);

/* Turn the motor rail on/off */
void srhw_power_motor_rail_set( srhw_power_t* pwr, bool state );

/* Make the power board beep */
typedef struct {
	uint16_t frequency;
	uint16_t duration;
} srhw_beep_t;

void srhw_power_beep(srhw_power_t* pwr, srhw_beep_t* beeps, int num_beeps);

#endif	/* __SRHW_POWER_H */
