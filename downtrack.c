/* standard includes */
#include <sqlite3.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>

/* application includes */
#include "action.h"
#include "display.h"
#include "storage.h"

/* forward declaration */
void convert_to_uppercase(char *str);

int main(int argc, char *argv[]) {
	// initialize db
        initialize_db();

	// get action type from command line arguments
	enum action_type action = get_action_type(argc, argv);

	// process action
	switch (action) {
		case Display:
			display_status();
			break;

		case Down:
		{
			char *env = argv[2];
			char *reason = NULL;
			if (argc == 4) {
				reason = argv[3];
			}

			convert_to_uppercase(env);
			update_up(env);
			if (insert_down(env, reason) == true) {
				display_status();
			}
		}
		break;
		
		case Up:
		{
			char *env = argv[2];
                        convert_to_uppercase(env);
			if (update_up(env) == true) {
				display_status();
			}
		}
		break;
		
		default:
			display_usage();
	}

	// close db
	close_db();

	return 0;
}

void convert_to_uppercase(char *str) {
	while (*str != '\0') {
		if (islower(*str))
			*str = toupper((unsigned char) *str);
		++str;
	}
}
