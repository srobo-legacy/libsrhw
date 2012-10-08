#include "sric.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "srhw.h"
#include "srhw-local-ctx.h"

#define REQUEST_TIMEOUT -1

static char* error_to_string(sric_error error) {
	switch (error) {
		case SRIC_ERROR_NONE:           return "No error.";
		case SRIC_ERROR_NOSUCHADDRESS:  return "No such remote address.";
		case SRIC_ERROR_NOSENDNOTE:     return "Cannot send notifications.";
		case SRIC_ERROR_BADPAYLOAD:     return "Payload too long.";
		case SRIC_ERROR_SRICD:          return "Could not connect to sricd.";
		case SRIC_ERROR_LOOP:           return "Cannot send to self.";
		case SRIC_ERROR_TIMEOUT:        return "Request timed out.";
		case SRIC_ERROR_BROADCAST:      return "Cannot listen on broadcast address.";
	}
}

uint16_t srhw_count_devices(srhw_t* srhw_ctx, sric_dev_class type) {
	const sric_device* device = 0;
	uint16_t count = 0;
	while (device = sric_enumerate_devices(srhw_ctx->ctx, device)) {
		if (device->type == type) {
			count++;
		}
	}
	return count;
}

sric_error send_message(sric_context ctx, int address, const unsigned char* payload, int payload_length) {
	sric_frame outframe;
	sric_frame inframe;
	outframe.address = address;
	outframe.note = -1;
	outframe.payload_length = payload_length;
	memcpy(outframe.payload, payload, payload_length);
	sric_error error = sric_txrx(ctx, &outframe, &inframe, REQUEST_TIMEOUT);
	
	// Check for errors
	if (error != SRIC_ERROR_NONE) {
		fprintf(stderr, "%s\n", error_to_string(error));
	}
	
	return error;
}

sric_error send_query_with_payload(sric_context ctx, int address, const unsigned char* payload, int payload_length, unsigned char* response) {
	sric_frame outframe, inframe;
	outframe.address = address;
	outframe.note = -1;
	outframe.payload_length = payload_length;
	memcpy(outframe.payload, payload, payload_length);
	sric_error error = sric_txrx(ctx, &outframe, &inframe, REQUEST_TIMEOUT);
	
	// Check for errors
	if (error != SRIC_ERROR_NONE) {
		fprintf(stderr, "%s\n", error_to_string(error));
	}
	
	memcpy(response, inframe.payload, inframe.payload_length);
	
	return error;
}

sric_error send_query(sric_context ctx, int address, int message_type, unsigned char* response) {
	unsigned char payload[] = {message_type};
	int payload_length = sizeof(payload);
	sric_error rv = send_query_with_payload(ctx, address, payload, payload_length, response);
	return rv;
}
