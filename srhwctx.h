#ifndef __SRHW_CTX
#define __SRHW_CTX
#include "motor.h"
#include "srhwsric.h"

typedef struct srhw_ctx {
	srhw_sric_ctx sric; // all sric related info, as declared in srhwsric.h
	srhw_motor_ctx motor; // all motor related info, as declared in motor.h
} srhw_ctx;
	
#endif // __SRHW_CTX
