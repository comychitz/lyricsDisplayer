#include "LyricsDisplayer.h"
#include <unistd.h>
#include <sstream>

LyricsDisplayer::LyricsDisplayer( ) : MAX_ROW(), MAX_COL()
{
  m_lyricFiles.clear();
  m_filesDirectory = "/etc/lyrics";
#ifdef DEBUG
  m_filesDirectory = "/tmp/lyrics";
#endif
}

LyricsDisplayer::~LyricsDisplayer( )
{
}


void LyricsDisplayer::init( )
{
  /* make sure the m_filesDirectory exists, 
   * if not, create it */
  struct stat temp;
  if( stat( m_filesDirectory.c_str(), &temp ) != 0 )
  {
    int res = mkdir( m_filesDirectory.c_str(), 0744 );
    if( res == 0 )
    {
      std::cout << "Created directory \'" 
                << m_filesDirectory << "\' "
                << "to hold lyric files!" 
                << std::endl;
    } else 
    {
      std::cout << "Failed to create directory \'"
                << m_filesDirectory << "\': "
                << strerror( errno ) << " ("
                << errno << ") " << std::endl;
      exit(-1);
    }
  }
}

void LyricsDisplayer::run( )
{
  /* do any prep work */
  init();

  /* get all files in the directory */
  readDirectory();

  /* get the screen ready */
  initscr();
  cbreak();
  noecho(); // turn off echoing characters ready be getch() */
  curs_set(0); // hide the cursor
  clear(); // clear the screen
  MAX_ROW = LINES;
  MAX_COL = COLS;

  bool run = true;
  int pressedKey;

  std::vector<FileContents>::iterator i;
  i = m_lyricFiles.begin();

  const char* nextSong;
  while( run )
  {
    i->parseFile();
    displayLyrics( *i );
    ++i;
    if( i == m_lyricFiles.end() )
    {
      i = m_lyricFiles.begin();
    }
    
    int timeOut = 0;
    while( timeOut < 360 )
    {
      if( (pressedKey = getch()) )
        break;
      usleep( 333333 );
      timeOut++;
    }
    //
    // used to find out what key i pressed (lol)
    //std::stringstream ss;
    //ss << "echo " << pressedKey << " >> ./log.log";
    //system( ss.str().c_str() );
    //
    //
    switch( pressedKey )
    {
      case 109: // m 
        nextSong = menu.run( m_lyricFiles );
        break;
      case 113: // q
        run = false;     
        break;
    }
    
    if( nextSong != NULL )
    {
      i = m_lyricFiles.begin();
      std::string temp = i->m_artistName;
      temp += "-" + i->m_songName;
      while( temp != std::string(nextSong) )
      {
        ++i;
        temp = i->m_artistName;
        temp += "-" + i->m_songName;
      }
      nextSong = NULL;
    }
    clear();
    refresh();
  }
  endwin(); // ncurses end window
}

/* displays contents of m_currentFileContents */
bool LyricsDisplayer::displayLyrics( FileContents file )
{
  /* show the song name at the top */
  mvprintw( (MAX_ROW - file.m_lyrics.size())/2 - 3, 
            (MAX_COL - file.m_songName.length())/2, 
            "%s", 
            file.m_songName.c_str() );
  refresh();
  usleep( 30000 );

  /* show the lyrics */
  int counter = 0;
  std::list<std::string>::iterator i;
  for( i = file.m_lyrics.begin(); i != file.m_lyrics.end(); ++i )
  {
    mvprintw( (MAX_ROW - file.m_lyrics.size())/2 + counter, 
              (MAX_COL - i->length())/2, 
              "%s", 
              i->c_str() );
    counter++;
    usleep( 30000 );
    refresh();
  }

  mvprintw( (MAX_ROW - file.m_lyrics.size())/2 + file.m_lyrics.size() + 2, 
            (MAX_COL - file.m_artistName.length())/2, 
            "%s", 
            file.m_artistName.c_str() );
  refresh();
  return true;
}

/* reads the m_filesDirectory and populates
 * m_fileNames */
bool LyricsDisplayer::readDirectory()
{
  DIR *d;
  struct dirent *dir;
  
  d = opendir( m_filesDirectory.c_str() );
  if( !d )
  {
    std::cout << "ERR: Failed to open directory: "
              << strerror( errno ) << " ("
              << errno << ") " << std::endl;
    return false;
  }
  while( (dir = readdir( d )) != NULL )
  {
    if( dir->d_name[0] != '.' )
    {
      m_lyricFiles.push_back( FileContents( std::string(m_filesDirectory),
                                            std::string(dir->d_name)) );
    }
  }
  return true;
}
