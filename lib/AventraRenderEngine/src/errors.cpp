// errors.cpp by Benjamin Swaby
// created : 31.07.22
// contains: Implimentation of functions defined in /include/errors.hpp

#include "errors.hpp"

#include <iostream>
#include <fstream>

using std::ofstream;
using std::endl;
using namespace WDS;


// interact with a logger to write to a log file.
WDS::Error Error::Log() {
  // open log file
  ofstream LogFileStream;
  LogFileStream.open("log.txt",std::ios::ios_base::app);

  if (LogFileStream.fail()) {
    LogFileStream.close();
    LogFileStream.clear();
    Error("Failed to write to log file", 20, true);
  }

  LogFileStream << this->ErrorCode << " : " <<this->Message << endl;
  LogFileStream.flush();
  LogFileStream.close();

  return *this;
}

// Print the error message to the terminal.
WDS::Error Error::ToStdOut() {
  std::cout << this->ErrorCode << " : " << this->Message << std::endl;
  return *this;
}


