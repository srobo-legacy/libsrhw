#include "power.h"
#include "srhw_internal.h"

#define CMD_PLAY_PIEZO     6
#define CMD_SET_LEDS       7
#define CMD_SET_MOTOR_RAIL 8
#define CMD_GET_LEDS       9
#define CMD_GET_VI         10

#define VOLTAGE_MULTIPLIER 0.0036621
#define CURRENT_MULTIPLIER 0.012201

struct srhw_power_s {
	srhw_t *srhw_ctx;

	int address;
};

void srhw_power_init(srhw_t* srhw_ctx) {
	g_assert(srhw_ctx != NULL);

	const sric_device* device;
	srhw_ctx->power = (srhw_power_t*)malloc(sizeof(srhw_power_t));
	srhw_ctx->power->srhw_ctx = srhw_ctx;
	srhw_ctx->power->address = 0;
	while (device = sric_enumerate_devices(srhw_ctx->ctx, device)) {
		if (device->type == SRIC_CLASS_POWER) {
			srhw_ctx->power->address = device->address;
			break;
		}
	}
	g_assert(srhw_ctx->power->address);
}

void srhw_power_free(srhw_t* ctx) {
	g_assert(ctx != NULL);
	free(srhw_ctx->power);
}

uint16_t srhw_power_count(srhw_t* ctx) {
	g_assert(ctx != NULL);
	return ctx->num_power;
}

srhw_power_t* srhw_power_get(srhw_t* ctx) {
	g_assert(ctx != NULL);

	return ctx->power;
}

// Power //

void srhw_power_supply_get(srhw_power_t* pwr, float* voltage, float* current) {
	g_assert(pwr != NULL);

	char response[4];
	send_query(pwr->srhw_ctx->ctx, pwr->address, CMD_GET_VI, response);
	byte voltage_raw = response[0] | (response[1] << 8);
	byte current_raw = response[2] | (response[3] << 8);
	*voltage = voltage_raw * VOLTAGE_MULTIPLIER;
	*current = current_raw * CURRENT_MULTIPLIER;
}

// LEDs //

void srhw_power_leds_set(srhw_power_t* pwr, uint8_t vals) {
	g_assert(pwr != NULL);

	unsigned char payload[] = {CMD_SET_LEDS, vals};
	send_message(pwr->srhw_ctx->ctx, pwr->address, payload, 2);
}

uint8_t srhw_power_leds_get(srhw_power_t* pwr) {
	g_assert(pwr != NULL);
	
	char response[1];
	send_query(pwr->srhw_ctx->ctx, pwr->address, CMD_GET_LEDS, response);
	return response[0];
}

void srhw_power_led_set(srhw_power_t* pwr, int led, bool state) {
	g_assert(pwr != NULL);
	
	uint8_t vals = srhw_power_leds_get(pwr);
	vals = vals & (state ? (1 << led) : !(1 << led));
	srhw_power_leds_set(pwr, vals);
}

bool srhw_power_led_get(srhw_power_t* pwr, int led) {
	g_assert(pwr != NULL);

	uint8_t vals = srhw_power_leds_get(pwr);
	return vals & (1 << led) > 0;
}

// Motor Rail //

void srhw_power_motor_rail_set(srhw_power_t* pwr, bool state) {
	g_assert(pwr != NULL);
	
	unsigned char payload[] = {CMD_SET_MOTOR_RAIL, state};
	send_message(pwr->srhw_ctx->ctx, pwr->address, payload, 2);
}

// Beeping //

void srhw_power_beep(srhw_power_t* pwr, srhw_beep_t* beeps, int num_beeps) {
	g_assert(pwr != NULL);
	g_assert(beeps != NULL);
	g_assert(num_beeps > 0);

	uint8_t payload_length = 2 + 4 * num_beeps;
	unsigned char payload[payload_length];
	payload[0] = CMD_PLAY_PIEZO;
	payload[1] = num_beeps;

	// Add the beeps to the payload
	int i;
	srhw_beep_t* beep = beeps;
	for (i = 0; i < num_beeps; i++, beep++) {
		payload[2+i+0] = MSB(beep->frequency);
		payload[2+i+1] = LSB(beep->frequency):
		payload[2+i+2] = MSB(beep->duration);
		payload[2+i+3] = MSB(beep->duration);
	}

	send_message(pwr->srhw_ctx->ctx, pwr->address, payload, payload_length);
}
