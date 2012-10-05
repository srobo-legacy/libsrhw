#ifndef __SRHW_SERVO_H
#define __SRHW_SERVO_H
#include "srhwctx.h"
#include <stdint.h>

struct srhw_servo_s;
typedef struct srhw_servo_s srhw_servo_t;

void srhw_servo_init(srhw_t* srhw_ctx);
void srhw_servo_free(srhw_t* srhw_ctx);

/* Return the number of servo controllers */
uint16_t srhw_servo_count(srhw_t* srhw_context);

/* Return handle for servo controller (board) n */
srhw_servo_t* srhw_servo_get(srhw_t* srhw_context, uint16_t n);

/* Get servo n's current angle */
uint16_t srhw_servo_angle_get(srhw_servo_t* board, uint16_t servo);

/* Set servo n's angle */
void srhw_servo_angle_set(srhw_servo_t* board, uint16_t servo, uint16_t a);

/* Enable or disable SMPS */
void srhw_servo_smps_set(srhw_servo_t* board, bool state);

#endif /* __SRHW_SERVO_H */
