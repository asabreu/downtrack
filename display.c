/* standard includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* application includes */
#include "display.h"
#include "storage.h"

void display_usage() {
	printf("usage: downtrack [-r | -h] [-d | -u] 'event' <'reason'> ...\n\n");

	printf("without option, display if exists status for down events with since date/time information.\n\n");

	printf("with option:\n");
	printf("\t-r\tDisplay detailed report.\n");
	printf("\t-h\tDisplay this usage help.\n\n");

	printf("\t-d\tAdd down event entry.\n");
	printf("\t-u\tUpdate down event if exists with up state.\n");
}

void display_status() {
	printf("\n");
	get_status();
 	printf("\n");
}
