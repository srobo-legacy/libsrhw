#include "sric.h"
#include "srhw.h"
#include <glib.h>

srhw_t* srhw_init( void ) {
	srhw_t* new_context = NULL;
	new_context = getmem( sizeof(srhw_t) );
	g_assert(new_context != NULL); // Check for out of memory. We cannot recover from that.

	(*new_context).ctx = &sric_init();

	return new_context;
}

void srhw_free( srhw_t* srhw_context ) {
	free( (*srhw_context).ctx );
	free( srhw_context );
}
