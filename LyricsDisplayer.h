#ifndef LYRICS_DISPLAYER_H
#define LYRICS_DISPLAYER_H

#include <iostream>
#include <string>
#include <vector>

#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <ncurses.h>

#include "FileContents.h"
#include "Menu.h"

const int SLEEP_TIME = 10;

class LyricsDisplayer
{
  public:

    LyricsDisplayer();

    ~LyricsDisplayer();

    void init();

    void run();

    bool displayLyrics( FileContents file );

    bool readDirectory();

  private:
    Menu menu;

    std::string m_filesDirectory;

    std::vector<FileContents> m_lyricFiles;

    int MAX_ROW;
    int MAX_COL;
};


#endif //LYRICS_DISPLAYER_H
