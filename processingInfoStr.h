#pragma once

//root
#include <TROOT.h>

//C, C++
#include <iostream>
#include <iomanip>

struct processingInfoStr {
  Int_t entryID;
  Float_t procFileSize;
  Int_t expID;
  Int_t runID;
  processingInfoStr(){
    entryID = -999;
    procFileSize = -999.0;
    expID = -999;
    runID = -999;
  }
  ~processingInfoStr(){;}
  void printProcInfo(){
    std::cout<<std::setw(15)<<entryID
	     <<std::setw(15)<<procFileSize
	     <<std::setw(15)<<expID
	     <<std::setw(15)<<runID<<std::endl;
  }
};
