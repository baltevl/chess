#https://codereview.stackexchange.com/questions/74136/makefile-that-places-object-files-into-an-alternate-directory-bin
CC=gcc
CFLAGS=-Wall -I include
LDFLAGS=-lncurses
EXECUTABLE_NAME=chess

SRC=src
BUILD=build
OBJ=$(BUILD)/obj

SOURCE_FILES=\
			 menu.c\
			 game_ui.c\
			 game.c\
			 board.c\
			 piece.c\
			 main.c

EXECUTABLE_FILES = $(EXECUTABLE_NAME:%=$(BUILD)/%)
OBJECT_FILES     = $(SOURCE_FILES:%.c=$(OBJ)/%.o)

build: $(EXECUTABLE_FILES)

clean:
	rm -rf $(BUILD)

run: build
	./$(EXECUTABLE_FILES)

.PHON: build clean run

$(EXECUTABLE_FILES): $(OBJECT_FILES)
	$(CC) $(LDFLAGS) -o $@ $^ 

$(OBJECT_FILES): $(OBJ)/%.o: $(SRC)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ -c $<


