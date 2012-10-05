#include "sric.h"
#include <stdio.h>

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

sric_error send_query(sric_context ctx, int address, int message_type, unsigned char* response) {
	unsigned char payload[] = {message_type};
	int payload_length = sizeof(payload);
	sric_error rv = send_query_with_payload(ctx, address, payload, payload_length, response);
	return rv;
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
