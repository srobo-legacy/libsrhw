sric_error send_message(sric_context ctx, int address, const unsigned char* payload, int payload_length);

sric_error send_query(sric_context ctx, int address, int message_type, unsigned char* response);