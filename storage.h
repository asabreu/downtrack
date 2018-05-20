#ifndef STORAGE_H
#define STORAGE_H

typedef enum { false, true } bool;

static const char * db_name = ".downtrack.db";

void initialize_db();
void close_db();

bool insert_down(char *env, char *reason);
bool update_up(char *env);
void get_status();

#endif
