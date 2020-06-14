//my
#include "mdstanabase.hh"

//root
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>
#include <TChain.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TGraph.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TProfile.h>

//C, C++
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <bits/stdc++.h>

using namespace std;

mdstanabase::mdstanabase(TString fileList) : fChain(0) 
{
  ifstream indata;
  TString rootFileName;
  //TChain *theChain = new TChain("arich");
  TChain *theChain = new TChain(treeName.Data());
  indata.open(fileList.Data()); 
  assert(indata.is_open());  
  while (indata  >> rootFileName ){
    if(indata.eof()){
      std::cout<<"EOF"<<std::endl;
      break;
    }
    cout<<"        adding "<<rootFileName<<endl;
    theChain->Add(rootFileName.Data(),-1);
  }
  indata.close();
  Init(theChain);
}

mdstanabase::mdstanabase(TString inFileName, Int_t keyID) : fChain(0) 
{
  if(keyID == 1 || keyID == 2 || keyID == 21){
    ifstream indata;
    //TChain *theChain = new TChain("T");
    TChain *theChain = new TChain(treeName.Data());
    cout<<"        adding "<<inFileName<<endl;
    theChain->Add(inFileName.Data(),-1);
    Init(theChain);
  }
  else
    assert(0);
}

void mdstanabase::tGraphInit(TGraph *gr[nChannels], TString grName, TString grTitle){
  Int_t i;
  TString grNameh;
  TString grTitleh;
  for(i = 0;i<nChannels;i++){
    grNameh = grName; grNameh += "_"; grNameh += "ch_"; grNameh += i;
    grTitleh = grTitle; grTitleh += " "; grTitleh += "ch "; grTitleh += i;
    gr[i] = new TGraph();
    gr[i]->SetTitle(grTitleh.Data());
    gr[i]->SetName(grNameh.Data());
  }
}

void mdstanabase::h1D1Init(TH1D *h1D1[nChannels],TString h1name, TString h1Title,
		      Int_t Nbin, Float_t Vmin, Float_t Vmax){
  Int_t i;
  TString h1nameh;
  TString h1Titleh;
  for(i = 0;i<nChannels;i++){    
    h1nameh = h1name; h1nameh += "_"; h1nameh += "ch_"; h1nameh += i;
    h1Titleh = h1Title; h1nameh += " "; h1Titleh += "ch "; h1Titleh += i;
    h1D1[i] = new TH1D(h1nameh.Data(), h1Titleh.Data(),
                       Nbin, Vmin, Vmax);
  }
}

void mdstanabase::h2D2Init(TH2D *h2D1[nChannels],TString h2name, TString h2Title,
		      Int_t Nbin1, Float_t Vmin1, Float_t Vmax1,
		      Int_t Nbin2, Float_t Vmin2, Float_t Vmax2){
  Int_t i;
  TString h2nameh;
  TString h2Titleh;
  for(i = 0;i<nChannels;i++){    
    h2nameh = h2name; h2nameh += "_"; h2nameh += "ch_"; h2nameh += i;
    h2Titleh = h2Title; h2nameh += " "; h2Titleh += "ch "; h2Titleh += i;
    h2D1[i] = new TH2D(h2nameh.Data(), h2Titleh.Data(),
                       Nbin1, Vmin1, Vmax1,
		       Nbin2, Vmin2, Vmax2);
  }  
}

void mdstanabase::tProfInit(TProfile *tprof[nChannels],TString prname, TString prTitle,
		       Int_t Nbin, Float_t Vmin, Float_t Vmax){
  Int_t i;
  TString prnameh;
  TString prTitleh;
  for(i = 0;i<nChannels;i++){    
    prnameh = prname; prnameh += "_"; prnameh += "ch_"; prnameh += i;
    prTitleh = prTitle; prnameh += " "; prTitleh += "ch "; prTitleh += i;
    tprof[i] = new TProfile(prnameh.Data(), prTitleh.Data(), Nbin, Vmin, Vmax,"");
  }
}

double mdstanabase::getUnixTimeFromTime(double d_year, double d_month, double d_day, double d_hour, double d_min, double d_sec){
  //time_t timer;
  struct tm y2k = {0};
  y2k.tm_year = d_year - 1900; y2k.tm_mon = d_month-1; y2k.tm_mday = d_day;
  y2k.tm_hour = d_hour;   y2k.tm_min = d_min; y2k.tm_sec = d_sec;
  return difftime(mktime(&y2k),0);
}

mdstanabase::~mdstanabase(){
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

void mdstanabase::Loop(TString histOut){
}

Int_t mdstanabase::GetEntry(Long64_t entry){
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}

Long64_t mdstanabase::LoadTree(Long64_t entry){
  // Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (fChain->GetTreeNumber() != fCurrent) {
    fCurrent = fChain->GetTreeNumber();
    Notify();
  }
  return centry;
}

void mdstanabase::Init(TTree *tree){
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).
  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);
  //fChain->SetBranchAddress("evt", &evt, &b_evt);
  //fChain->SetBranchAddress("run", &run, &b_run);
  //fChain->SetBranchAddress("pValue", &pValue, &b_pValue);
  //...
  //...
  //
  //---------------------------------------------------
  // ADD HERE :
  fChain->SetBranchAddress("runType", &runType, &b_runType);
  fChain->SetBranchAddress("expNumber", &expNumber, &b_expNumber);
  fChain->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
  fChain->SetBranchAddress("runLength", &runLength, &b_runLength);
  fChain->SetBranchAddress("numberOfEvents", &numberOfEvents, &b_numberOfEvents);
  fChain->SetBranchAddress("triggerType", &triggerType, &b_triggerType);
  fChain->SetBranchAddress("delLumiStart", &delLumiStart, &b_delLumiStart);
  fChain->SetBranchAddress("delLumiStop", &delLumiStop, &b_delLumiStop);
  fChain->SetBranchAddress("intLumOfRun", &intLumOfRun, &b_intLumOfRun);
  fChain->SetBranchAddress("nBunchesHER", &nBunchesHER, &b_nBunchesHER);
  fChain->SetBranchAddress("nBunchesLER", &nBunchesLER, &b_nBunchesLER);
  fChain->SetBranchAddress("beamIHERstart", &beamIHERstart, &b_beamIHERstart);
  fChain->SetBranchAddress("beamILERstart", &beamILERstart, &b_beamILERstart);
  fChain->SetBranchAddress("beamIHERstop", &beamIHERstop, &b_beamIHERstop);
  fChain->SetBranchAddress("beamILERstop", &beamILERstop, &b_beamILERstop);
  fChain->SetBranchAddress("beam_x_HERstart", &beam_x_HERstart, &b_beam_x_HERstart);
  fChain->SetBranchAddress("beam_y_HERstart", &beam_y_HERstart, &b_beam_y_HERstart);
  fChain->SetBranchAddress("beam_x_LERstart", &beam_x_LERstart, &b_beam_x_LERstart);
  fChain->SetBranchAddress("beam_y_LERstart", &beam_y_LERstart, &b_beam_y_LERstart);
  fChain->SetBranchAddress("beam_x_HERstop", &beam_x_HERstop, &b_beam_x_HERstop);
  fChain->SetBranchAddress("beam_y_HERstop", &beam_y_HERstop, &b_beam_y_HERstop);
  fChain->SetBranchAddress("beam_x_LERstop", &beam_x_LERstop, &b_beam_x_LERstop);
  fChain->SetBranchAddress("beam_y_LERstop", &beam_y_LERstop, &b_beam_y_LERstop);
  fChain->SetBranchAddress("statusPXD", &statusPXD, &b_statusPXD);
  fChain->SetBranchAddress("statusSVD", &statusSVD, &b_statusSVD);
  fChain->SetBranchAddress("statusCDC", &statusCDC, &b_statusCDC);
  fChain->SetBranchAddress("statusTOP", &statusTOP, &b_statusTOP);
  fChain->SetBranchAddress("statusARICH", &statusARICH, &b_statusARICH);
  fChain->SetBranchAddress("statusECL", &statusECL, &b_statusECL);
  fChain->SetBranchAddress("statusKLM", &statusKLM, &b_statusKLM);
  fChain->SetBranchAddress("statusTRG", &statusTRG, &b_statusTRG);
  fChain->SetBranchAddress("startTime", &startTime, &b_startTime);
  fChain->SetBranchAddress("stopTime", &stopTime, &b_stopTime);
  //---------------------------------------------------
  Notify();
}

Bool_t mdstanabase::Notify(){
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.
  return kTRUE;
}

void mdstanabase::Show(Long64_t entry){
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}

Int_t mdstanabase::Cut(Long64_t entry){
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}
