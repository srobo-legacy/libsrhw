#ifndef __SRHW_LOCAL_CTX_H
#define __SRHW_LOCAL_CTX_H
#include <stdint.h>

#include "motor.h"
#include "srhwsric.h"

struct srhw_s {
	srhw_sric_ctx sric; // all sric related info, as declared in srhwsric.h

	/* List of motor boards, n_motors long */
	uint8_t n_motors;
	srhw_motor_t *motors;

	/* List of servo boards, n_servos long */
	uint8_t n_servos;
	srhw_servo_t *servos;
};

#endif	/* __SRHW_LOCAL_CTX_H */
