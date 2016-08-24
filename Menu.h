#ifndef MENU_H
#define MENU_H

#include "FileContents.h"

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
#include <menu.h>

class Menu 
{
  public:
    Menu();
 
    ~Menu();

    const char* run( const std::vector<FileContents> &files );

  private:
    void init();

    void readFileNames();

    void print_in_middle( WINDOW *win, 
                          int starty, 
                          int startx, 
                          int width, 
                          const char *string );

  private:
    ITEM **items_;

    MENU *menu_;

    WINDOW *sub_win_; 

    std::vector<std::string> file_names;

};

#endif //MENU_H
