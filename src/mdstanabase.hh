#ifndef mdstanabase_hh
#define mdstanabase_hh

#include <TROOT.h>

class TChain;
class TFile;
class TTree;
class TString;
class TBranch;
class TGraph;
class TH1D;
class TH2D;
class TProfile;

class mdstanabase {

public :
  mdstanabase(TString fileList);
  mdstanabase(TString inFileName, Int_t keyID);
  ~mdstanabase();
  Int_t GetEntry(Long64_t entry);
  Long64_t LoadTree(Long64_t entry);
  void Init(TTree *tree);
  void Loop(TString histOut);
  Bool_t Notify();
  void Show(Long64_t entry = -1);
  Int_t Cut(Long64_t entry);

protected :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain
  //Int_t           evt;
  //Int_t           run;
  //Float_t         pValue;
  //...
  //...
  //
  //---------------------------------------------------
  // ADD HERE :
  //Tree name
  //const TString treeName = "arich";
  const TString treeName = "T";
  static const Int_t nChannels = 10;
  Int_t           runType;
  Int_t           expNumber;
  Int_t           runNumber;
  Float_t         runLength;
  Int_t           numberOfEvents;
  Int_t           triggerType;
  Float_t         delLumiStart;
  Float_t         delLumiStop;
  Float_t         intLumOfRun;
  Int_t           nBunchesHER;
  Int_t           nBunchesLER;
  Float_t         beamIHERstart;
  Float_t         beamILERstart;
  Float_t         beamIHERstop;
  Float_t         beamILERstop;
  Float_t         beam_x_HERstart;
  Float_t         beam_y_HERstart;
  Float_t         beam_x_LERstart;
  Float_t         beam_y_LERstart;
  Float_t         beam_x_HERstop;
  Float_t         beam_y_HERstop;
  Float_t         beam_x_LERstop;
  Float_t         beam_y_LERstop;
  Int_t           statusPXD;
  Int_t           statusSVD;
  Int_t           statusCDC;
  Int_t           statusTOP;
  Int_t           statusARICH;
  Int_t           statusECL;
  Int_t           statusKLM;
  Int_t           statusTRG;
  Int_t           startTime;
  Int_t           stopTime;  
  //---------------------------------------------------
  
  // List of branches
  //TBranch        *b_evt;
  //TBranch        *b_run;
  //TBranch        *b_pValue;
  //...
  //...
  //
  //---------------------------------------------------
  // ADD HERE :
  TBranch        *b_runType;   //!
  TBranch        *b_expNumber;   //!
  TBranch        *b_runNumber;   //!
  TBranch        *b_runLength;   //!
  TBranch        *b_numberOfEvents;   //!
  TBranch        *b_triggerType;   //!
  TBranch        *b_delLumiStart;   //!
  TBranch        *b_delLumiStop;   //!
  TBranch        *b_intLumOfRun;   //!
  TBranch        *b_nBunchesHER;   //!
  TBranch        *b_nBunchesLER;   //!
  TBranch        *b_beamIHERstart;   //!
  TBranch        *b_beamILERstart;   //!
  TBranch        *b_beamIHERstop;   //!
  TBranch        *b_beamILERstop;   //!
  TBranch        *b_beam_x_HERstart;   //!
  TBranch        *b_beam_y_HERstart;   //!
  TBranch        *b_beam_x_LERstart;   //!
  TBranch        *b_beam_y_LERstart;   //!
  TBranch        *b_beam_x_HERstop;   //!
  TBranch        *b_beam_y_HERstop;   //!
  TBranch        *b_beam_x_LERstop;   //!
  TBranch        *b_beam_y_LERstop;   //!
  TBranch        *b_statusPXD;   //!
  TBranch        *b_statusSVD;   //!
  TBranch        *b_statusCDC;   //!
  TBranch        *b_statusTOP;   //!
  TBranch        *b_statusARICH;   //!
  TBranch        *b_statusECL;   //!
  TBranch        *b_statusKLM;   //!
  TBranch        *b_statusTRG;   //!
  TBranch        *b_startTime;   //!
  TBranch        *b_stopTime;   //!
  //---------------------------------------------------
  void tGraphInit(TGraph *gr[nChannels], TString grName, TString grTitle);
  void h1D1Init(TH1D *h1D1[nChannels],TString h1name, TString h1Title,
		Int_t Nbin, Float_t Vmin, Float_t Vmax);
  void h2D2Init(TH2D *h2D1[nChannels],TString h2name, TString h2Title,
                Int_t Nbin1, Float_t Vmin1, Float_t Vmax1,
                Int_t Nbin2, Float_t Vmin2, Float_t Vmax2);
  void tProfInit(TProfile *tprof[nChannels],TString prname, TString prTitle,
                 Int_t Nbin, Float_t Vmin, Float_t Vmax);
  double getUnixTimeFromTime(double d_year, double d_month, double d_day, double d_hour, double d_min, double d_sec);  
  //
  
};

#endif
