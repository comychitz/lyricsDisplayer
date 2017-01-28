# lyrics_displayer
A program that shows your favorite lyrics in a nice and neat format on your terminal window.

## Build
Simple makefile
* make 
* make run
* make debug
* make clean

Note: My machine is a Macbook Pro 10,1 (Intel i7)
* Apple LLVM version 8.0.0 (clang-800.0.42.1)
* Dependency: ncurses 

## Run
Run using './lyrics'
Controls:
* press the m key to go to the menu screen
* use the up/down arrow keys or j/k to select in menu (hit enter once selected)
* press q to quit

## Notes
* There will be a directory created '/etc/lyrics', where you can place lyric files to show on the screen. The name of the files must follow the format "Artist Name-Song Name.txt". Contents are the lyrics, line-separated. It will be centered when put on the screen.
* When running debug mode, the lyrics file directory is /tmp/lyrics/

