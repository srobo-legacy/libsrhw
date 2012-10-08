#ifndef __SRHW_LOCAL_CTX_H
#define __SRHW_LOCAL_CTX_H
#include <stdint.h>
#include "srhw.h"
#include "srhwctx.h"

struct srhw_s {
	sric_context ctx;

	/* Power board */
	srhw_power_t *power;

	/* List of motor boards, num_motors long */
	uint8_t num_motors;
	srhw_motor_t* *motors;

	/* List of servo boards, num_servos long */
	uint8_t num_servos;
	srhw_servo_t* *servos;

	/* List of jio boards, num_jios long */
	uint8_t num_jios;
	srhw_jio_t* *jios;
};

#endif	/* __SRHW_LOCAL_CTX_H */
