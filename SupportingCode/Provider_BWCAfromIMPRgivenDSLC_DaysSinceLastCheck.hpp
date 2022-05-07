#ifndef PROVIDER_BWCAFROMIMPRGIVENDSLC__DAYSSINCELASTCHECK_HPP_
#define PROVIDER_BWCAFROMIMPRGIVENDSLC__DAYSSINCELASTCHECK_HPP_

#include "include/my_transform.hpp"
#include <cstdio>
#include <cstdlib>

#include <iostream>
#include <fstream>
#include <string>

// A class to perform a file read line by line.
class FileReader {
private:
  std::string fileName;
  std::fstream file;

public:
  FileReader() = default;
  ~FileReader() { close(); };

  // returns true if the file is open, indicated by whether a file name 
  // has been provided
  bool isOpen() {
    return !fileName.empty();
  }

  // opens the file given by name
  void open(std::string fileName) {
    this->fileName = fileName;
    file.open(fileName, std::ios::in);
  }

  // closes an open file
  void close() {
    file.close();
    fileName.clear();
  }

  // fetches the next line of text from the file
  std::string nextLine() {
    std::string line;
    std::getline(file, line);
    return line;
  }

  // static instanceOf method, returns a pointer to the
  // current instance
  static FileReader *instanceOf() {
    if (instance == nullptr) {
      instance = new FileReader();
    }
    return instance;
  }

  static FileReader *instance;
};

FileReader *FileReader::instance = nullptr;

class Provider_BWCAfromIMPRgivenDSLC_DaysSinceLastCheck {

public:
    Provider_BWCAfromIMPRgivenDSLC_DaysSinceLastCheck() = default;
    ~Provider_BWCAfromIMPRgivenDSLC_DaysSinceLastCheck() = default;

   BWCAfromIMPRgivenDSLC::DaysSinceLastCheck get() {
       BWCAfromIMPRgivenDSLC::DaysSinceLastCheck param;
       
       // get an instance of the file reader, open a file if one isn't already open
       FileReader *reader = FileReader::instanceOf();
       if (!reader->isOpen()) {
           reader->open("/media/sf_toy_movies/output3.txt");
       }
       
       // assume the line just contains a single integer, convert it and store it 
       // in the contextual parameters
       //param._dslc = std::stoi(line);
       std::string line = reader->nextLine();
       reader->close();
       int my_number = std::stoi(line); 

       param._dslc = my_number;

        //TODO--Populate param here and remove the following
       //fprintf(stderr, "*** ERROR: Contextual parameters not populated in file Provider_BWCAfromIMPRgivenDSLC_DaysSinceLastCheck.hpp!\n");
       //abort();

       return param;
   }
};

#endif