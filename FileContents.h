#ifndef FILE_CONTENTS_H
#define FILE_CONTENTS_H

#include <string>
#include <list>
#include <fstream>
#include <iostream>

class FileContents
{
  public: 
    FileContents();

    FileContents( std::string directory, 
                  std::string fileName );

    ~FileContents();

    bool parseFile();

    std::string m_fileName;
    std::string m_artistName;
    std::string m_songName;
    bool m_parsed;
    std::list<std::string> m_lyrics;

};

#endif // FILE_CONTENTS_H
