#include "motor.h"
#include <glib.h>
#include "sric.h"
#include "srhw_internal.h"

#define CMD_MOTOR_SET 0
#define CMD_MOTOR_GET 1

#define MIN_SPEED       -100
#define MAX_SPEED       100
#define BRAKING_DEFAULT false

struct srhw_motor_s {
	srhw_t* srhw_ctx;
	uint16_t id;
	
	int address;
};

void srhw_motor_init(srhw_t* srhw_ctx) {
	g_assert(srhw_ctx != NULL);
	
	// Count motors
	const sric_device* device = 0;
	srhw_ctx->num_motors = 0;
	while (device = sric_enumerate_devices(srhw_ctx, device)) {
		if (devices->type == SRIC_CLASS_MOTOR) {
			srhw_ctx->num_motors++;
		}
	}
	uint16_t count = srhw_ctx->num_motors;
	srhw_ctx->motors = (srhw_motor_t**)malloc(count * sizeof(srhw_motor_t*));
	
	// Add motors to array
	device = 0;
	int i = 0;
	while (device = sric_enumerate_devices(srhw_ctx->ctx, device)) {
		if (device->type == SRIC_CLASS_MOTOR) {
			srhw_ctx->motors[i] = (srhw_motor_t*)malloc(sizeof(srhw_motor_t));
			srhw_ctx->motors[i]->srhw_ctx = &srhw_ctx;
			srhw_ctx->motors[i]->id = i;
			srhw_ctx->motors[i]->address = device->address;
			i++;
		}
	}
}

void srhw_motor_free(srhw_t* srhw_ctx) {
	g_assert(srhw_ctx != NULL);
	
	for (int i = 0; i < srhw_ctx->num_motors; i++) {
		free(srhw_ctx->motors[i]);
	}
	
	free(srhw_ctx->motors);
}

uint16_t srhw_motor_count(srhw_t* srhw_ctx) {
	g_assert(srhw_ctx != NULL);
	
	return srhw_ctx->num_motors;
}

srhw_motor_t* srhw_motor_get(srhw_t* srhw_ctx, uint16_t n) {
	g_assert(srhw_ctx != NULL);
	g_assert(n < srhw_ctx->num_motors);
	
	return srhw_ctx->motors[n];
}

uint8_t srhw_motor_state_get(srhw_motor_t* motor, bool* brake) {
	g_assert(motor != NULL);
	
	char response[2];
	send_query(motor->srhw_ctx->ctx, motor->address, CMD_MOTOR_GET, response);
	*brake = response[1];
	return response[0];
}

void srhw_motor_state_set(srhw_motor_t* motor, uint8_t power, bool brake) {
	g_assert(motor != NULL);
	unsigned char payload[] = {CMD_MOTOR_SET, power, brake};
	send_message(motor->srhw_ctx->ctx, motor->address, payload, 3);
}
