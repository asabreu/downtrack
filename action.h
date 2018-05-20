#ifndef ACTION_H
#define ACTION_H

enum action_type { Display, Report, Down, Up, Help }; 

enum action_type get_action_type(int argc, char *argv[]);

#endif
