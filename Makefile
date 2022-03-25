CC = cc
ARGS = -std=c90 -Wall -Wpedantic

# installation directory
INST_DIR = /bin

all: build install

build:
	mkdir -p bin
	$(CC) $(ARGS) -o bin/synchead synchead.c

build-dbg:
	mkdir -p bin
	$(CC) $(ARGS) -g -o bin/synchead_dbg synchead.c

clean:
	rm -r bin

install:
	mv synchead $(INST_DIR)

uninstall:
	rm $(INST_DIR)/synchead
	
