#ifndef __SRHW_INTERNAL
#define __SRHW_INTERNAL

// Splitting and merging macros
#define LSB(x) (x & 0xFF)
#define MSB(x) ((x >> 8) & 0xFF)
#define COMBINE(x, y) (x | (y << 8))

uint16_t srhw_count_devices(srhw_ctx* ctx, sric_dev_class type);

sric_error send_message(sric_context ctx, int address, const unsigned char* payload, int payload_length);

sric_error send_query(sric_context ctx, int address, int message_type, unsigned char* response);

sric_error send_query_with_payload(sric_context ctx, int address, const unsigned char* payload, int payload_length, unsigned char* response);

#endif
