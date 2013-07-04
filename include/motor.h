#ifndef __SRHW_MOTOR_H
#define __SRHW_MOTOR_H
#include "srhwctx.h"
#include <stdint.h>
#include <stdbool.h>

struct srhw_motor_s;
typedef struct srhw_motor_s srhw_motor_t;

void srhw_motor_init( srhw_t* ctx );
void srhw_motor_free( srhw_t* ctx );

/* Return the number of motor controllers */
uint16_t srhw_motor_count( srhw_t* srhw_context );

/* Return handle for motor controller n */
srhw_motor_t* srhw_motor_get( srhw_t* srhw_context, uint16_t n );

/* Get motor state */
uint8_t srhw_motor_state_get(srhw_motor_t* motor, bool* brake);

/* Get motor state */
void srhw_motor_state_set(srhw_motor_t* motor, uint8_t power, bool brake);

#endif	/* __SRHW_MOTOR_H */