#include "jio.h"

typedef struct srhw_servo_s {
	srhw_t* ctx;

	/* The SRIC address of the JointIO board */
	int addr;
};


