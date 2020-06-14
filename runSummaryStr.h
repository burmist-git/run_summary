#pragma once

//root
#include <TROOT.h>

//C, C++
#include <iostream>

struct runSummaryStr {
  Int_t runType;           //01 --> RC.runtype               (start)       cosmic physics - 0 1  
  Int_t expNumber;         //02 --> DAQ.ExpNumber            (start)
  Int_t runNumber;         //03 --> DAQ.RunNumber            (start)
  Float_t runLength;       //04 --> TTD.run.length           (end)
  Int_t numberOfEvents;    //05 --> TTD.trig.count.out       (end)
  Int_t triggerType;       //06 --> TTD.trig.type            (start)       aux    gdl     - 0 1
  Float_t delLumiStart;    //07 --> ECL.Luminosity.accel     (start)
  Float_t delLumiStop;     //08 --> ECL.Luminosity.accel     (end)
  Float_t intLumOfRun;     //09 --> ECL.Luminosity.det.total (end)
  Int_t nBunchesHER;       //10 --> SKB.CGHINJ.BKSEL.NOB_SET (start)
  Int_t nBunchesLER;       //11 --> SKB.CGLINJ.BKSEL.NOB_SET (start)
  Float_t beamIHERstart;   //12 --> SKB.HER.beam.current     (start)
  Float_t beamILERstart;   //13 --> SKB.LER.beam.current     (start)
  Float_t beamIHERstop;    //14 --> SKB.HER.beam.current     (end)
  Float_t beamILERstop;    //15 --> SKB.LER.beam.current     (end)
  Float_t beam_x_HERstart; //16 --> SKB.HER.beam.size.x      (start)
  Float_t beam_y_HERstart; //17 --> SKB.HER.beam.size.y      (start)
  Float_t beam_x_LERstart; //18 --> SKB.LER.beam.size.x      (start)
  Float_t beam_y_LERstart; //19 --> SKB.LER.beam.size.y      (start)
  Float_t beam_x_HERstop;  //20 --> SKB.HER.beam.size.x      (end)
  Float_t beam_y_HERstop;  //21 --> SKB.HER.beam.size.y      (end)
  Float_t beam_x_LERstop;  //22 --> SKB.LER.beam.size.x      (end)
  Float_t beam_y_LERstop;  //23 --> SKB.LER.beam.size.y      (end)
  Int_t statusPXD;         //24 --> RC.PXD.used              (start)
  Int_t statusSVD;         //25 --> RC.SVD.used              (start)
  Int_t statusCDC;         //26 --> RC.CDC.used              (start)
  Int_t statusTOP;         //27 --> RC.TOP.used              (start)
  Int_t statusARICH;       //28 --> RC.ARICH.used            (start)
  Int_t statusECL;         //29 --> RC.ECL.used              (start)
  Int_t statusKLM;         //30 --> RC.KLM.used              (start)
  Int_t statusTRG;         //31 --> RC.TRG.used              (start)
  //
  Int_t startTime;         //32 --> DAQ.Date                 (start)
  Int_t stopTime;          //33 --> DAQ.Date                 (end)
  runSummaryStr(){
    runType = -999;
    expNumber = -999;
    runNumber = -999;
    runLength = -999.0;
    numberOfEvents = -999;
    triggerType = -999;
    delLumiStart = -999.0;
    delLumiStop = -999.0;
    intLumOfRun = -999.0;
    nBunchesHER = -999;
    nBunchesLER = -999;
    beamIHERstart = -999.0;
    beamILERstart = -999.0;
    beamIHERstop = -999.0;
    beamILERstop = -999.0;
    beam_x_HERstart = -999.0;
    beam_y_HERstart = -999.0;
    beam_x_LERstart = -999.0;
    beam_y_LERstart = -999.0;
    beam_x_HERstop = -999.0;
    beam_y_HERstop = -999.0;
    beam_x_LERstop = -999.0;
    beam_y_LERstop = -999.0;
    statusPXD = -999;
    statusSVD = -999;
    statusCDC = -999;
    statusTOP = -999;
    statusARICH = -999;
    statusECL = -999;
    statusKLM = -999;
    statusTRG = -999;
    startTime = -999;
    stopTime = -999;
  }
  ~runSummaryStr(){;}
  void printSummary(){
    std::cout<<"runType         "<<runType<<std::endl
	     <<"expNumber       "<<expNumber<<std::endl
	     <<"runNumber       "<<runNumber<<std::endl
	     <<"runLength       "<<runLength<<std::endl
	     <<"numberOfEvents  "<<numberOfEvents<<std::endl
	     <<"triggerType     "<<triggerType<<std::endl
	     <<"delLumiStart    "<<delLumiStart<<std::endl
	     <<"delLumiStop     "<<delLumiStop<<std::endl
	     <<"intLumOfRun     "<<intLumOfRun<<std::endl
	     <<"nBunchesHER     "<<nBunchesHER<<std::endl;
    std::cout<<"nBunchesLER     "<<nBunchesLER<<std::endl
	     <<"beamIHERstart   "<<beamIHERstart<<std::endl
	     <<"beamILERstart   "<<beamILERstart<<std::endl
	     <<"beamIHERstop    "<<beamIHERstop<<std::endl
	     <<"beamILERstop    "<<beamILERstop<<std::endl
	     <<"beam_x_HERstart "<<beam_x_HERstart<<std::endl
	     <<"beam_y_HERstart "<<beam_y_HERstart<<std::endl
	     <<"beam_x_LERstart "<<beam_x_LERstart<<std::endl
	     <<"beam_y_LERstart "<<beam_y_LERstart<<std::endl
	     <<"beam_x_HERstop  "<<beam_x_HERstop<<std::endl;
    std::cout<<"beam_y_HERstop  "<<beam_y_HERstop<<std::endl
	     <<"beam_x_LERstop  "<<beam_x_LERstop<<std::endl
	     <<"beam_y_LERstop  "<<beam_y_LERstop<<std::endl
	     <<"statusPXD       "<<statusPXD<<std::endl
	     <<"statusSVD       "<<statusSVD<<std::endl
	     <<"statusCDC       "<<statusCDC<<std::endl
	     <<"statusTOP       "<<statusTOP<<std::endl
	     <<"statusARICH     "<<statusARICH<<std::endl
	     <<"statusECL       "<<statusECL<<std::endl
	     <<"statusKLM       "<<statusKLM<<std::endl;
    std::cout<<"statusTRG       "<<statusTRG<<std::endl
	     <<"startTime       "<<startTime<<std::endl
	     <<"stopTime        "<<stopTime<<std::endl;
  }
};
