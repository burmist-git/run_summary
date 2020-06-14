#pragma once

//root
#include <TROOT.h>

//C, C++
#include <iostream>
#include <iomanip>

struct integratedLuminosityStr {
  Int_t expID;
  Int_t runID;
  Float_t intLum;
  integratedLuminosityStr(){
    expID = -999;
    runID = -999;
    intLum = 0.0;
  }
  ~integratedLuminosityStr(){;}
  void printIntegratedLuminosityInfo(){
    std::cout<<std::setw(15)<<expID
	     <<std::setw(15)<<runID
	     <<std::setw(15)<<intLum<<std::endl;
  }
};
