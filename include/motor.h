#ifndef __SRHW_MOTOR_H
#define __SRHW_MOTOR_H
#include "srhwctx.h"
#include <stdint.h>

struct srhw_motor_s;
typedef struct srhw_motor_s srhw_motor_t;

void srhw_motor_init( srhw_t* ctx );
void srhw_motor_free( srhw_t* ctx );

/* Return the number of motor controllers */
uint16_t srhw_motor_count( srhw_t* srhw_context );

/* Return handle for motor controller n */
srhw_motor_t* srhw_motor_get( srhw_t* srhw_context, uint16_t n );

/* Get motor power */
uint16_t srhw_motor_power_get( srhw_motor_t* motor );

/* Set motor power */
void srhw_motor_power_set( srhw_motor_t* motor, uint16_t p );

/* Get motor brake */
bool srhw_motor_brake_get(srhw_motor_t* motor);

/* Set motor brake */
bool srhw_motor_brake_set(srhw_motor_t* motor, bool state);

#endif	/* __SRHW_MOTOR_H */
