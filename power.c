#include "power.h"

struct srhw_power_s {
	srhw_t *ctx;

	/* The SRIC address of the power board */
	int addr;
};
