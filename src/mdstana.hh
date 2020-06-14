#ifndef mdstana_hh
#define mdstana_hh

//My
#include "mdstanabase.hh"

//root
#include <TROOT.h>

class TChain;
class TFile;
class TTree;
class TString;
class TBranch;

class mdstana: public mdstanabase {
public:
  mdstana(TString fileList) : mdstanabase(fileList)
  {
  }

  mdstana(TString file, Int_t key) : mdstanabase(file, key)
  {
  }

  void Loop(TString histOut);
  bool ifCut();
  
  enum expRunType { cosmic, physics };
  enum expTriggerType { aux , gdl};
  enum intLuminosityType { recorded, delivered};
  
  Int_t expTimeStart;
  Int_t expTimeStop;
  Double_t durationOfDataTakingCampaign_day;
  void GetExpTimeStartStop();
  Float_t getBeamTou( Float_t beamIstart, Float_t beamIstop, Int_t startTime, Int_t stopTime);

  std::vector<float> v_procInfF_cdst;
  void Set_v_procInfF_cdst(std::vector<float> v) {v_procInfF_cdst = v;};

  std::vector<float> v_intLumF;
  void Set_v_intLumF(std::vector<float> v) {v_intLumF = v;};
  
};

#endif
