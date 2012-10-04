#ifndef SRHW_INTERNAL
#define SRHW_INTERNAL

// Splitting macros
#define LSB(x) (x & 0xFF)
#define MSB(x) ((x >> 8) & 0xFF)

sric_error send_message(sric_context ctx, int address, const unsigned char* payload, int payload_length);

sric_error send_query(sric_context ctx, int address, int message_type, unsigned char* response);

#endif
