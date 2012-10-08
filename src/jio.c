#include "jio.h"
#include <stdlib.h>
#include <glib.h>
#include "sric.h"
#include "srhw-local-ctx.h"
#include "srhw_internal.h"

#define CMD_PSU_SET    4
#define CMD_OUTPUT_SET 0
#define CMD_OUTPUT_GET 1
#define CMD_INPUT_A    2
#define CMD_INPUT_D    3

#define NUM_INPUTS 8

struct srhw_jio_s {
	srhw_t* srhw_ctx;

	int id;
	/* The SRIC address of the JointIO board */
	int address;
};

void srhw_jio_init(srhw_t* srhw_ctx) {
	g_assert(srhw_ctx != NULL);

	// Count jio boards
	uint16_t count = srhw_count_devices(srhw_ctx, SRIC_CLASS_JOINTIO);
	srhw_ctx->num_jios = count;
	srhw_ctx->jios = (srhw_jio_t**)malloc(count * sizeof(srhw_jio_t*));

	// Add jio to array
	const sric_device* device = 0;
	int i = 0;
	while (device = sric_enumerate_devices(srhw_ctx->ctx, device)) {
		if (device->type == SRIC_CLASS_SERVO) {
			srhw_jio_t* jio = (srhw_jio_t*)malloc(sizeof(srhw_jio_t));
			jio->srhw_ctx = srhw_ctx;
			jio->id = i;
			jio->address = device->address;
			srhw_ctx->jios[i] = jio;
			i++;
		}
	}
}

void srhw_jio_free(srhw_t* srhw_ctx) {
	g_assert(srhw_ctx != NULL);
	
	int i;
	for (i = 0; i < srhw_ctx->num_jios; i++) {
		free(srhw_ctx->jios[i]);
	}

	free(srhw_ctx->jios);
}

srhw_jio_t* srhw_jio_get(srhw_t* srhw_ctx, uint16_t n) {
	g_assert(srhw_ctx != NULL);
	g_assert(n < srhw_ctx->num_jios);

	return srhw_ctx->jios[n];
}

void srhw_jio_psu_set(srhw_jio_t* jio, bool state) {
	g_assert(jio != NULL);

	char payload[] = {CMD_PSU_SET, state};
	send_message(jio->srhw_ctx->ctx, jio->address, payload, 2);
}

void srhw_jio_outputs_set(srhw_jio_t* jio, uint8_t vals) {
	g_assert(jio != NULL);
	
	char payload[] = {CMD_OUTPUT_SET, vals};
	send_message(jio->srhw_ctx->ctx, jio->address, payload, 2);
}

uint8_t srhw_jio_outputs_get(srhw_jio_t* jio) {
	g_assert(jio != NULL);

	char response[1];
	send_query(jio->srhw_ctx->ctx, jio->address, CMD_OUTPUT_GET, response);
	return response[0];
}

uint8_t srhw_jio_inputs_d_get(srhw_jio_t* jio) {
	g_assert(jio != NULL);

	char response[1];
	send_query(jio->srhw_ctx->ctx, jio->address, CMD_INPUT_D, response);
	return response[0];
}


void srhw_jio_inputs_a_get(srhw_jio_t* jio, uint16_t* vals) {
	g_assert(jio != NULL);
	g_assert(vals != NULL);

	char response[NUM_INPUTS * 2];
	send_query(jio->srhw_ctx->ctx, jio->address, CMD_INPUT_A, response);
	int i;
	uint16_t* val = vals;
	for (i = 0; i < NUM_INPUTS; i++, val++) {
		*val = COMBINE(response[i], response[i+1]);
	}
}
