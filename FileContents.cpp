#include "FileContents.h"

FileContents::FileContents()
{
  m_fileName.clear();
  m_artistName.clear();
  m_songName.clear();
  m_lyrics.clear();
  m_parsed = false;
}

FileContents::FileContents( std::string directory, std::string fileName )
{
  m_fileName = directory + "/" + fileName;
  
  int pos = fileName.find( "-" );
  
  if( pos == -1 )
  {
    std::cout << "Improper file name detected!: " << fileName << std::endl;
  }
  else
  {
    m_artistName = fileName.substr( 0, pos );
    m_songName = fileName.substr( pos+1, fileName.length() - pos - 5 ); // -4 for .txt, -1 more
  }
}

FileContents::~FileContents()
{
}

bool FileContents::parseFile()
{
  /*
   * file is in a specific format
   * the file name will always be
   * Artist-Song.txt
   * the songname should
   * contain spaces where it needs
   * but not around the '-' char
   * and the contents of the file
   * are just the lyrics themselves
   *
   * no need for formatting as it 
   * will be centered and aligned
   * when printed on the screen
   * using ncurses api calls
   *
   */
  if( m_parsed )
  {
    return true;
  } 
  std::ifstream fileStream( m_fileName );
  std::string line;
  while( std::getline( fileStream, line ) )
  {
    m_lyrics.push_back( line );
  }

  m_parsed = true;
  
  return true;
}
