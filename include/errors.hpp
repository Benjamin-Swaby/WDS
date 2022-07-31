// errors.hpp by Benjamin Swaby
// created : 31.07.22
// contains: error interface.

#pragma once

#include <string>
#include <unistd.h>

namespace WDS {

  class Error {
  private:

    int ErrorCode;
    std::string Message;
    
    void Panic(){exit(this->ErrorCode);};
    void Ignore();

  public:
    void Log();
    void ToStdOut();

    Error(std::string message, int code, bool panic) {
      this->ErrorCode = code;
      this->Message = message;

      if (panic) {
	this->ToStdOut();
	this->Log();
	this->Panic();
      }
    }

  
  };
  
};
