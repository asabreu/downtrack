/* standard includes */
#include <string.h>

/* application includes */
#include "action.h"

enum action_type get_action_type(int argc, char *argv[]) {
	enum action_type result = Help; // defaults to Help

	if (argc == 1) {
		return Display;

	} else {
		char *cmd = argv[1];
	
		if (argc == 2) {
			if (strncmp("-r", cmd, strlen(cmd)) == 0) {
				return Report;
			}
	
		} else if (argc == 3) {
			if (strncmp("-d", cmd, strlen(cmd)) == 0) {
				return Down;
			} else if (strncmp("-u", cmd, strlen(cmd)) == 0) {
				return Up;
			}
		
		} else if (argc == 4) {
			if (strncmp("-d", cmd, strlen(cmd)) == 0) {
                        	return Down;
                        }
		}
	}

	return result;
}
