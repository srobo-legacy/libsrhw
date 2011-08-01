#ifndef __SRHW_DRV_H
#define __SRHW_DRV_H
#include <stdint.h>

typedef struct {
	void (*init) (void);
	void (*free) (void);
} srhw_driver_t;

#endif	/* __SRHW_DRV_H */
