#include "servo.c"
#include <glib.h>
#include "sric.h"
#include "srhw_internal.h"

#define NUM_SERVOS_PER_BOARD 8

#define SERVO_ANGLE     400
#define SERVO_API_ANGLE 100

#define CMD_SERVO_SET  0
#define CMD_SERVO_GET  1
#define CMD_SERVO_SMPS 7

struct srhw_servo_s {
	srhw_t* ctx;

	/* The SRIC address of the servo board */
	int address;
};

void srhw_servo_init(srhw_t* srhw_ctx) {
	g_assert(srhw_ctx != NULL);

	// Count servo boards
	uint16_t count = srhw_count_devices(srhw_ctx, SRIC_CLASS_MOTOR);
	srhw_ctx->num_servos = count;
	srhw_ctx->servos = (srhw_servo_t**)malloc(count * sizeof(srhw_servo_t*));

	// Add servos to array
	const sric_device* device = 0;
	int i = 0;
	while (device = sric_enumerate_devices(srhw_ctx->ctx, device)) {
		if (device->type == SRIC_CLASS_SERVO) {
			srhw_ctx->servos[i] = (srhw_servo_t*)malloc(sizeof(srhw_servo_t));
			srhw_ctx->servos[i]->srhw_ctx = &srhw_ctx;
			srhw_ctx->servos[i]->id = i;
			srhw_ctx->servos[i]->address = device->address;
			i++;
		}
	}
}

void srhw_servo_free(srhw_t* srhw_ctx) {
	g_assert(srhw_ctx != NULL);
	
	for (int i = 0; i < srhw_ctx->num_servos; i++) {
		free(srhw_ctx->servos[i]);
	}

	free(srhw_ctx->servos);
}

uint16_t srhw_servo_count(srhw_t* srhw_context) {
	g_assert(srhw_ctx != NULL);

	return srhw_ctx->num_servos;
}

srhw_servo_t* srhw_servo_get(srhw_t* srhw_context, uint16_t n) {
	g_assert(srhw_ctx != NULL);
	g_assert(n < srhw_ctx->num_servos);

	return srhw_ctx->servos[n];
}

uint16_t srhw_servo_angle_get(srhw_servo_t* board, uint16_t servo) {
	g_assert(board != NULL);
	g_assert(servo < NUM_SERVOS_PER_BOARD);

	char payload[] = {CMD_SERVO_GET, servo};
	char response[2];
	send_query_with_payload(board->srhw_ctx->ctx, board->address, payload, 2, response);
	return COMBINE(response[0], response[1]) / (SERVO_ANGLE/SERVO_API_ANGLE);
}

void srhw_servo_angle_set(srhw_servo_t* board, uint16_t servo, uint16_t a) {
	g_assert(board != NULL);
	g_assert(servo < NUM_SERVOS_PER_BOARD);

	uint16_t tmp = val * (SERVO_ANGLE/SERVO_API_ANGLE);
	char payload[] = {CMD_SERVO_SET, LSB(tmp), MSB(tmp)};
	send_message(board->srhw_ctx->ctx, board->address, payload, 3);
}

void srhw_servo_smps_set(srhw_servo_t* board, bool state) {
	g_assert(board != NULL);

	char payload[] = {CMD_SERVO_SMPS, state};
	send_message(board->srhw_ctx->ctx, board->address, payload, 2);
}
