#ifndef __SRHW_CTX
#define __SRHW_CTX

/*
	srhwctx.h - the header declaring the context struct
*/

#include "motor.h"
#include "srhwsric.h"

struct srhw_ctx {
	srhw_sric_ctx sric; // all sric related info, as declared in srhwsric.h
	srhw_motor_ctx motor; // all motor related info, as declared in motor.h
	// etc
};
	
