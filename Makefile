SQLITE3_DIR=/usr/local/opt/sqlite
CFLAGS+=-I$(SQLITE3_DIR)/include
LDFLAGS+=-L$(SQLITE3_DIR)/lib -lsqlite3

CFLAGS+=-Wall -Werror -std=gnu99 -O2 

TARGETS=downtrack
OBJS=action.o display.o storage.o

all: $(TARGETS)

clean:
	$(RM) $(TARGETS)
	$(RM) $(OBJS)

downtrack: $(OBJS) downtrack.o
	$(CC) -o $@ $^ $(LDFLAGS) 

.PHONY: all clean
