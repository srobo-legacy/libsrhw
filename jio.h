#ifndef __SRHW_JIO_H
#define __SRHW_JIO_H
#include "srhwctx.h"
#include <stdint.h>

typedef struct {
	srhw_t* ctx;

	/* The SRIC address of the JointIO board */
	int addr;
} srhw_jio_t;

void srhw_jio_init( srhw_t* ctx );
void srhw_jio_free( srhw_t* ctx );

/* Return the number of JointIO boards */
void srhw_jio_count( srhw_t* ctx );

/* Return handle for JointIO board n */
srhw_jio_t* srhw_jio_get( srhw_t* ctx, uint16_t n );

/* Turn on/off the JIO's 3.3v rail */
void srhw_jio_psu_set( srhw_jio_t* jio, bool state );

/* Set the outputs */
void srhw_jio_outputs_set( srhw_jio_t* jio, uint8_t vals );

/* Get the outputs */
uint8_t	srhw_jio_outputs_get( srhw_jio_t* jio);

/* Get the inputs in digital form */
uint8_t	sr_jio_inputs_d_get( srhw_jio_t* jio );

/* Read the analogue inputs
 * Puts the input values in array pointed to by vals.
 * If *vals is NULL, an array is allocated that the caller must free. */
void sr_jio_inputs_a_get( srhw_jio_t* jio, uint16_t **vals );

#endif	/* __SRHW_JIO_H */
