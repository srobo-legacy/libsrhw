#ifndef __SRHW_CTX
#define __SRHW_CTX
#include <stdint.h>

#include "motor.h"
#include "srhwsric.h"

typedef struct {
	srhw_sric_ctx sric; // all sric related info, as declared in srhwsric.h

	/* List of motor boards, n_motors long */
	uint8_t n_motors;
	srhw_motor_t *motors;

	/* List of servo boards, n_servos long */
	uint8_t n_servos;
	srhw_servo_t *servos;
} srhw_t;
	
#endif // __SRHW_CTX
