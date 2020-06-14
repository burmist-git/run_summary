#pragma once

//root
#include <TROOT.h>

//C, C++
#include <iostream>
#include <iomanip>

struct arichRunSummaryStr {
  Int_t run;               // 01 <run>2563</run>
  Int_t exp;               // 02 <exp>7</exp>
  Int_t neve;              // 03 <neve>3708901</neve>
  Float_t hitsPerEvent;    // 04 <hitsPerEvent>2.25376</hitsPerEvent>
  Int_t ntracks;           // 05 <ntracks>15</ntracks>
  Int_t nhot;              // 06 <nhot>79</nhot>
  Int_t ndead;             // 07 <ndead>958</ndead>
  Int_t ndeadHapd;         // 08 <ndeadHapd>4</ndeadHapd>
  Float_t ntracksPerEvent; // 09 <ntracksPerEvent>4.04432e-06</ntracksPerEvent>
  Float_t nsig;            // 10 <nsig>0.28036</nsig>
  Float_t nsigErr;         // 11 <nsigErr>6.90798</nsigErr>
  Float_t nbgr;            // 12 <nbgr>0.122553</nbgr>
  Float_t nbgrErr;         // 13 <nbgrErr>0.332585</nbgrErr>
  Float_t theta;           // 14 <theta>0.403203</theta>
  Float_t thetaErr;        // 15 <thetaErr>0.0382725</thetaErr>
  Float_t sigma;           // 16 <sigma>0.00317876</sigma>
  Float_t sigmaErr;        // 17 <sigmaErr>0.0211683</sigmaErr>
  Int_t timestamp;         // 18 <timestamp>1555640337</timestamp>
  arichRunSummaryStr(){
    run = -999;
    exp = -999;
    neve = -999;
    hitsPerEvent = -999.0;
    ntracks = -999;
    nhot = -999;
    ndead = -999;
    ndeadHapd = -999;
    ntracksPerEvent = -999.0;
    nsig = -999.0;
    nsigErr = -999.0;
    nbgr = -999.0;
    nbgrErr = -999.0;
    theta = -999.0;
    thetaErr = -999.0;
    sigma = -999.0;
    sigmaErr = -999.0;
    timestamp = -999;
  }
  ~arichRunSummaryStr(){;}
  void printArichRunSummaryInfo(){
    std::cout<<std::setw(15)<<run
	     <<std::setw(15)<<exp
	     <<std::setw(15)<<neve
	     <<std::setw(15)<<hitsPerEvent
	     <<std::setw(15)<<ntracks
	     <<std::setw(15)<<nhot
	     <<std::setw(15)<<ndead
	     <<std::setw(15)<<ndeadHapd
	     <<std::setw(15)<<ntracksPerEvent
	     <<std::setw(15)<<nsig
	     <<std::setw(15)<<nsigErr
	     <<std::setw(15)<<nbgr
	     <<std::setw(15)<<nbgrErr
	     <<std::setw(15)<<theta
	     <<std::setw(15)<<thetaErr
	     <<std::setw(15)<<sigma
	     <<std::setw(15)<<sigmaErr
	     <<std::setw(15)<<timestamp<<std::endl;
  }
};
