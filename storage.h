#ifndef STORAGE_H
#define STORAGE_H

typedef enum { false, true } bool;

static const char * db_name = ".downtrack.db";

void initialize_db();
void close_db();

bool insert_down(char *event, char *reason);
bool update_up(char *event);
void get_status();

#endif
