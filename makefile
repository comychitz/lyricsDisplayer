CC=g++
CFLAGS=-Wall
LFLAGS=-lncurses -lmenu
CLASS_FILES=LyricsDisplayer.cpp FileContents.cpp Menu.cpp
BIN_NAME=lyrics
DEBUG_BIN_NAME=lyrics_debug

all: clean lyrics

debug: clean compile_debug
	./lyrics_debug

run: clean lyrics
	./lyrics

lyrics: 
	$(CC) $(CFLAGS) $(LFLAGS) $(CLASS_FILES) main.cpp -o $(BIN_NAME)

compile_debug:
	$(CC) $(CFLAGS) $(LFLAGS) $(CLASS_FILES) main.cpp -o $(DEBUG_BIN_NAME) -DDEBUG

clean:
	rm -f lyrics
