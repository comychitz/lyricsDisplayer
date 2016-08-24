#include "Menu.h"
#include <sstream>

Menu::Menu() : items_(NULL), menu_(NULL), sub_win_(NULL)
{
}

Menu::~Menu()
{
}

void Menu::init()
{
  initscr();
  clear();
  noecho();
}

const char* Menu::run( const std::vector<FileContents> &files)
{
  init();

  // put file menu names into items_
  items_ = (ITEM**)calloc( files.size()+1, sizeof(ITEM *) );

  // TODO - clean me up START
  std::vector<FileContents>::const_iterator iter;
  for( iter = files.begin(); iter != files.end(); ++iter )
  {
    std::string tmp = iter->m_artistName;
    tmp += "-";
    tmp += iter->m_songName;
    file_names.push_back( tmp );
  }

  for( int i = 0; i < file_names.size(); i++ )
  {
    items_[i] = new_item( file_names[i].c_str(), "" );
  }
  items_[files.size()] = (ITEM *)NULL;
  // TODO - clean me up END

  //
  // create menu & set menu options
  //
  menu_ = new_menu( (ITEM**)items_ );
  // set the menu mark for the selected item to be no char
  set_menu_mark( menu_, " * " );

  //
  // create the sub window the menu will reside in
  //
  sub_win_ = newwin( LINES-5, COLS-5, 2, 2 );
  keypad( sub_win_, TRUE );
  set_menu_win( menu_, sub_win_ );
  set_menu_sub( menu_, derwin( sub_win_, LINES-10, COLS-10, 3, 3 ) );
  set_menu_format( menu_, LINES-4, 1 );
  box( sub_win_, 0, 0 );

  mvwaddch( sub_win_, 2, 0, ACS_LTEE);
  mvwhline( sub_win_, 2, 1, ACS_HLINE, COLS-5);
  mvwaddch( sub_win_, 2, COLS-6, ACS_RTEE);
  print_in_middle( sub_win_, 1, 0, COLS/4, "SELECT A SONG");

  refresh();

  //
  // post menu
  //
  post_menu( menu_ );
  wrefresh( sub_win_ );

  bool run = true;
  const char *nextSongName = NULL;
  while( run )
  {
    int keyPressed = getch();
    switch( keyPressed )
    {
      case 10: // enter
        nextSongName = menu_->curitem->name.str;
        run = false;
        break;
      case 113: // q
        run = false;
        break;  
      case 65: // up
      case 107:// k
        menu_driver( menu_, REQ_UP_ITEM);
        break;
      case 66: // down
      case 106:// j
        menu_driver( menu_, REQ_DOWN_ITEM );
        break;
    }
    wrefresh( sub_win_ );
  }
  
  for( int i = 0; i < files.size(); i++ )
  {
    free_item( items_[i] );
  }
  free_menu( menu_ );

  clear();
  refresh();

  if( nextSongName )
  {
    return nextSongName;
  }
  else 
  {
    return NULL;
  }
}

void Menu::print_in_middle( WINDOW *win, 
                            int starty, 
                            int startx, 
                            int width, 
                            const char *string )
{	
  int length, x, y;
  float temp;

  if(win == NULL)
    win = stdscr;
  getyx(win, y, x);
  if(startx != 0)
    x = startx;
  if(starty != 0)
    y = starty;
  if(width == 0)
    width = 80;

  length = strlen(string);
  temp = (width - length)/ 2;
  x = startx + (int)temp;
  mvwprintw(win, y, x, "%s", string);
  refresh();
}
