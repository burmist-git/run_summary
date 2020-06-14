/***********************************************************************
* Copyright(C) 2019 - LBS - (Single person developer.)                 *
* Tue May 14 00:29:57 JST 2019                                         *
* Autor: Leonid Burmistrov                                             *
***********************************************************************/

//my
#include "runSummaryStr.h"

//root
#include <TH1D.h>
#include <TStyle.h>
#include <TString.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>

//C, C++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <time.h>

using namespace std;

void pushStructInRoot(TString outputrootFile, runSummaryStr rss){
  //cout<<"outputrootFile : "<<outputrootFile<<endl;
  //rss.printSummary();
  //
  TFile *hfile = new TFile( outputrootFile, "UPDATE", "Data vector with unix timestamp", 1);
  if (hfile->IsZombie()) {
    std::cout << "PROBLEM with the initialization of the output ROOT ntuple " 
	      << outputrootFile << ": check that the path is correct!!!"
	      <<std::endl;
    assert(0);
  }
  //
  TTree *tree;
  if(!(TTree*)hfile->Get("T")){
    //std::cout<<" FIRST TIME"<<std::endl;
    tree = new TTree("T", "Data tree");
    tree->Branch("runType",&rss.runType);
    tree->Branch("expNumber",&rss.expNumber);
    tree->Branch("runNumber",&rss.runNumber);
    tree->Branch("runLength",&rss.runLength);
    tree->Branch("numberOfEvents",&rss.numberOfEvents);
    tree->Branch("triggerType",&rss.triggerType);
    tree->Branch("delLumiStart",&rss.delLumiStart);
    tree->Branch("delLumiStop",&rss.delLumiStop);
    tree->Branch("intLumOfRun",&rss.intLumOfRun);
    tree->Branch("nBunchesHER",&rss.nBunchesHER);
    tree->Branch("nBunchesLER",&rss.nBunchesLER);
    tree->Branch("beamIHERstart",&rss.beamIHERstart);
    tree->Branch("beamILERstart",&rss.beamILERstart);
    tree->Branch("beamIHERstop",&rss.beamIHERstop);
    tree->Branch("beamILERstop",&rss.beamILERstop);
    tree->Branch("beam_x_HERstart",&rss.beam_x_HERstart);
    tree->Branch("beam_y_HERstart",&rss.beam_y_HERstart);
    tree->Branch("beam_x_LERstart",&rss.beam_x_LERstart);
    tree->Branch("beam_y_LERstart",&rss.beam_y_LERstart);
    tree->Branch("beam_x_HERstop",&rss.beam_x_HERstop);
    tree->Branch("beam_y_HERstop",&rss.beam_y_HERstop);
    tree->Branch("beam_x_LERstop",&rss.beam_x_LERstop);
    tree->Branch("beam_y_LERstop",&rss.beam_y_LERstop);
    tree->Branch("statusPXD",&rss.statusPXD);
    tree->Branch("statusSVD",&rss.statusSVD);
    tree->Branch("statusCDC",&rss.statusCDC);
    tree->Branch("statusTOP",&rss.statusTOP);
    tree->Branch("statusARICH",&rss.statusARICH);
    tree->Branch("statusECL",&rss.statusECL);
    tree->Branch("statusKLM",&rss.statusKLM);
    tree->Branch("statusTRG",&rss.statusTRG);
    tree->Branch("startTime",&rss.startTime);
    tree->Branch("stopTime",&rss.stopTime);
  }
  else {
    //std::cout<<" NOT FIRST TIME"<<std::endl;
    tree = (TTree*)hfile->Get("T");
    tree->SetBranchAddress("runType",&rss.runType);
    tree->SetBranchAddress("expNumber",&rss.expNumber);
    tree->SetBranchAddress("runNumber",&rss.runNumber);
    tree->SetBranchAddress("runLength",&rss.runLength);
    tree->SetBranchAddress("numberOfEvents",&rss.numberOfEvents);
    tree->SetBranchAddress("triggerType",&rss.triggerType);
    tree->SetBranchAddress("delLumiStart",&rss.delLumiStart);
    tree->SetBranchAddress("delLumiStop",&rss.delLumiStop);
    tree->SetBranchAddress("intLumOfRun",&rss.intLumOfRun);
    tree->SetBranchAddress("nBunchesHER",&rss.nBunchesHER);
    tree->SetBranchAddress("nBunchesLER",&rss.nBunchesLER);
    tree->SetBranchAddress("beamIHERstart",&rss.beamIHERstart);
    tree->SetBranchAddress("beamILERstart",&rss.beamILERstart);
    tree->SetBranchAddress("beamIHERstop",&rss.beamIHERstop);
    tree->SetBranchAddress("beamILERstop",&rss.beamILERstop);
    tree->SetBranchAddress("beam_x_HERstart",&rss.beam_x_HERstart);
    tree->SetBranchAddress("beam_y_HERstart",&rss.beam_y_HERstart);
    tree->SetBranchAddress("beam_x_LERstart",&rss.beam_x_LERstart);
    tree->SetBranchAddress("beam_y_LERstart",&rss.beam_y_LERstart);
    tree->SetBranchAddress("beam_x_HERstop",&rss.beam_x_HERstop);
    tree->SetBranchAddress("beam_y_HERstop",&rss.beam_y_HERstop);
    tree->SetBranchAddress("beam_x_LERstop",&rss.beam_x_LERstop);
    tree->SetBranchAddress("beam_y_LERstop",&rss.beam_y_LERstop);
    tree->SetBranchAddress("statusPXD",&rss.statusPXD);
    tree->SetBranchAddress("statusSVD",&rss.statusSVD);
    tree->SetBranchAddress("statusCDC",&rss.statusCDC);
    tree->SetBranchAddress("statusTOP",&rss.statusTOP);
    tree->SetBranchAddress("statusARICH",&rss.statusARICH);
    tree->SetBranchAddress("statusECL",&rss.statusECL);
    tree->SetBranchAddress("statusKLM",&rss.statusKLM);
    tree->SetBranchAddress("statusTRG",&rss.statusTRG);
    tree->SetBranchAddress("startTime",&rss.startTime);
    tree->SetBranchAddress("stopTime",&rss.stopTime);
  }
  //
  hfile->SetCompressionLevel(2);
  tree->SetAutoSave(1000000);
  // Create new event
  TTree::SetBranchStyle(0);
  tree->Fill();
  hfile->Write();
  hfile->Close();
}

void findAndReplaceString(string& str, const string& oldStr, const string& newStr){
  std::string::size_type pos = 0u;
  while((pos = str.find(oldStr, pos)) != std::string::npos){
    str.replace(pos, oldStr.length(), newStr);
    pos += newStr.length();
  }
}

Int_t getUnixTimeFrom_year_month_day_hour_min_sec(double d_year, double d_month, double d_day, double d_hour, double d_min, double d_sec){
  struct tm y2k = {0};
  y2k.tm_year = d_year - 1900; y2k.tm_mon = d_month-1; y2k.tm_mday = d_day;
  y2k.tm_hour = d_hour;   y2k.tm_min = d_min; y2k.tm_sec = d_sec;
  return difftime(mktime(&y2k),0);
}

//2019-05-01-01:07:22
Int_t getUnixTimeFromStr(string mot){
  string tstr = mot;
  findAndReplaceString( tstr, "-", " ");
  findAndReplaceString( tstr, ":", " ");
  istringstream buf(tstr);
  //cout<<tstr<<endl;
  double d_year, d_month, d_day, d_hour, d_min, d_sec;
  buf>>d_year>>d_month>>d_day>>d_hour>>d_min>>d_sec;
  //cout<<d_year<<endl;
  return getUnixTimeFrom_year_month_day_hour_min_sec(d_year, d_month, d_day, d_hour, d_min, d_sec);
}

#ifdef PUSHSTRUCTINROOT_MAIN
int main(int argc, char *argv[]){  
  //cout<<"argc "<<argc<<endl;
  if(argc == 69 && atoi(argv[1])==0){
    TString outputrootFile = argv[2];
    cout<<"outputrootFile : "<<outputrootFile<<endl;
    runSummaryStr rss;
    string mot;
    Int_t i = 0;
    for(i = 3; i <argc ; i++){
      mot = argv[i];
      //01
      if(mot == "runType"){
	mot = argv[i+1];
	if(mot == "cosmic")
	  rss.runType = 0;
	else if (mot == "physics")
	  rss.runType = 1;
      }
      //02
      if(mot == "expNumber")
	  rss.expNumber = atoi(argv[i+1]);
      //03
      if(mot == "runNumber")
	  rss.runNumber = atoi(argv[i+1]);
      //04
      if(mot == "runLength")
	rss.runLength = atof(argv[i+1]);
      //05
      if(mot == "numberOfEvents")
	rss.numberOfEvents = atoi(argv[i+1]);
      //06
      if(mot == "triggerType"){
	mot = argv[i+1];
	if(mot == "aux")
	  rss.triggerType = 0;
	else if (mot == "gdl")
	  rss.triggerType = 1;
      }
      //07
      if(mot == "delLumiStart")
	rss.delLumiStart = atof(argv[i+1]);
      //08
      if(mot == "delLumiStop")
	rss.delLumiStop = atof(argv[i+1]);
      //09
      if(mot == "intLumOfRun")
	rss.intLumOfRun = atof(argv[i+1]);
      //10
      if(mot == "nBunchesHER")
	rss.nBunchesHER = atoi(argv[i+1]);
      //11
      if(mot == "nBunchesLER")
	rss.nBunchesLER = atoi(argv[i+1]);
      //12
      if(mot == "beamIHERstart")
	rss.beamIHERstart = atof(argv[i+1]);
      //13
      if(mot == "beamILERstart")
	rss.beamILERstart = atof(argv[i+1]);
      //14
      if(mot == "beamIHERstop")
	rss.beamIHERstop = atof(argv[i+1]);
      //15
      if(mot == "beamILERstop")
	rss.beamILERstop = atof(argv[i+1]);
      //16
      if(mot == "beam_x_HERstart")
	rss.beam_x_HERstart = atof(argv[i+1]);
      //17
      if(mot == "beam_y_HERstart")
	rss.beam_y_HERstart = atof(argv[i+1]);
      //18
      if(mot == "beam_x_LERstart")
	rss.beam_x_LERstart = atof(argv[i+1]);
      //19
      if(mot == "beam_y_LERstart")
	rss.beam_y_LERstart = atof(argv[i+1]);
      //20
      if(mot == "beam_x_HERstop")
	rss.beam_x_HERstop = atof(argv[i+1]);
      //21
      if(mot == "beam_y_HERstop")
	rss.beam_y_HERstop = atof(argv[i+1]);
      //22
      if(mot == "beam_x_LERstop")
	rss.beam_x_LERstop = atof(argv[i+1]);
      //23
      if(mot == "beam_y_LERstop")
	rss.beam_y_LERstop = atof(argv[i+1]);
      //24
      if(mot == "statusPXD")
	rss.statusPXD = atoi(argv[i+1]);
      //25
      if(mot == "statusSVD")
	rss.statusSVD = atoi(argv[i+1]);
      //26
      if(mot == "statusCDC")
	rss.statusCDC = atoi(argv[i+1]);
      //27
      if(mot == "statusTOP")
	rss.statusTOP = atoi(argv[i+1]);
      //28
      if(mot == "statusARICH")
	rss.statusARICH = atoi(argv[i+1]);
      //29
      if(mot == "statusECL")
	rss.statusECL = atoi(argv[i+1]);
      //30
      if(mot == "statusKLM")
	rss.statusKLM = atoi(argv[i+1]);
      //31
      if(mot == "statusTRG")
	rss.statusTRG = atoi(argv[i+1]);
      //32
      if(mot == "startTime"){
	mot = argv[i+1];
	rss.startTime = getUnixTimeFromStr(mot);
      }
      //33
      if(mot == "stopTime"){
	mot = argv[i+1];
	rss.stopTime = getUnixTimeFromStr(mot);
      }
    }
    pushStructInRoot( outputrootFile, rss);
  }
  else{
    cout<<" ERROR --->  in input arguments "<<endl
        <<"  runID [1] = 0  "<<endl
        <<"        [2] - outputrootFile"<<endl
        <<"        [.] - parname"<<endl
        <<"        [.] - par"<<endl;
  }  
  return 0;
}
#endif //ifdef PUSHSTRUCTINROOT_MAIN
