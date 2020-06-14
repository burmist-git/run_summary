//my
#include "src/mdstana.hh"
#include "pcstatlog_arichxx/libpushVectorInRoot.h"

//root
#include "TROOT.h"
#include "TString.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TRandom3.h"
#include "TGraph.h"

//C, C++
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <fstream>
#include <iomanip>
#include <time.h>

using namespace std;

int main(int argc, char *argv[]){
  int nargcMin = 5;
  int nargcMinLumi = 5;
  if(argc == 4 && atoi(argv[1])==0){
    TString rootFilesList = argv[2];
    TString outRootFileF = argv[3];
    cout<<"--> Parameters <--"<<endl
	<<"rootFilesList : "<<rootFilesList<<endl
	<<"outRootFileF  : "<<outRootFileF<<endl;
    mdstana a(rootFilesList);
    a.Loop(outRootFileF);
  }
  else if(argc == 4 && atoi(argv[1])==1){
    TString inRootFiles = argv[2];
    TString outRootFileF = argv[3];
    cout<<"--> Parameters <--"<<endl
	<<"inRootFiles  : "<<inRootFiles<<endl
	<<"outRootFileF : "<<outRootFileF<<endl;
    mdstana a( inRootFiles, atoi(argv[1]));
    a.Loop(outRootFileF);
  }
  else if(argc == 5 && atoi(argv[1])==2){
    TString inRootFiles = argv[2];
    TString outRootFileF = argv[3];
    TString inProcessingInfoRootFile = argv[4];
    cout<<"--> Parameters <--"<<endl
	<<"inRootFiles       : "<<inRootFiles<<endl
	<<"outRootFileF      : "<<outRootFileF<<endl
	<<"inProcessingInfoRootFile : "<<inProcessingInfoRootFile<<endl;
    mdstana a( inRootFiles, atoi(argv[1]));
    //a.SetProcessingInfoFile(runProcessingInfo);
    Long64_t jentry = 0;
    a.Set_v_procInfF_cdst(getDataVector( inProcessingInfoRootFile, jentry));
    a.Loop(outRootFileF);
  }
  else if(argc == 6 && atoi(argv[1])==21){
    TString inRootFiles = argv[2];
    TString outRootFileF = argv[3];
    TString inProcessingInfoRootFile = argv[4];
    TString inLuminosityInfoRootFile = argv[5];
    cout<<"--> Parameters <--"<<endl
	<<"inRootFiles       : "<<inRootFiles<<endl
	<<"outRootFileF      : "<<outRootFileF<<endl
	<<"inProcessingInfoRootFile : "<<inProcessingInfoRootFile<<endl
    	<<"inLuminosityInfoRootFile : "<<inLuminosityInfoRootFile<<endl;
    mdstana a( inRootFiles, atoi(argv[1]));
    //a.SetProcessingInfoFile(runProcessingInfo);
    Long64_t jentry = 0;
    a.Set_v_procInfF_cdst(getDataVector( inProcessingInfoRootFile, jentry));
    a.Set_v_intLumF(getDataVector( inLuminosityInfoRootFile, jentry));
    a.Loop(outRootFileF);
  }
  else if(argc > nargcMin && atoi(argv[1]) == 3 ){
    cout<<"--> Push a vector of data processing info <--"<<endl;
    TString outRootFile = argv[2];
    int vecparID = atoi(argv[3]);
    int nv = atoi(argv[4]);
    cout<<"--> Parameters <--"<<endl
	<<"outRootFile : "<<outRootFile<<endl
	<<"vecparID    : "<<vecparID<<endl
	<<"nv          : "<<nv<<endl;    
    std::vector<float> v;
    for(int i = 0;i < nv; i++){
      v.push_back(atof(argv[nargcMin+i]));
      //std::cout<<atof(argv[nargcMin+i])<<std::endl;
    }
    int ut = -999;
    pushVectorInRoot ( outRootFile, vecparID, ut, v);
  }
  else if(argc > nargcMinLumi && atoi(argv[1]) == 4 ){
    cout<<"--> Push a vector of integrated luminosities <--"<<endl;
    TString outRootFile = argv[2];
    int vecparID = atoi(argv[3]);
    int nv = atoi(argv[4]);
    cout<<"--> Parameters <--"<<endl
	<<"outRootFile : "<<outRootFile<<endl
	<<"vecparID    : "<<vecparID<<endl
	<<"nv          : "<<nv<<endl;    
    std::vector<float> v;
    for(int i = 0;i < nv; i++){
      v.push_back(atof(argv[nargcMinLumi+i]));
      //std::cout<<atof(argv[nargcMinLumi+i])<<std::endl;
    }
    int ut = -999;
    pushVectorInRoot ( outRootFile, vecparID, ut, v);
  }
  else{
    cout<<" --> ERROR in input arguments "<<endl
	<<" runID [1] = 0 (execution ID number)"<<endl
      	<<"       [2] - file with list of the root files"<<endl
	<<"       [3] - name of root file with histograms"<<endl;
    cout<<" runID [1] = 1 (execution ID number)"<<endl
      	<<"       [2] - in root files"<<endl
	<<"       [3] - name of root file with histograms"<<endl;
    cout<<" runID [1] = 2 (execution ID number)"<<endl
      	<<"       [2] - inRootFiles"<<endl
	<<"       [3] - outRootFileF"<<endl
      	<<"       [3] - runProcessingInfo"<<endl;
    cout<<" runID [1] = 21 (execution ID number)"<<endl
      	<<"       [2] - inRootFiles"<<endl
	<<"       [3] - outRootFileF"<<endl
      	<<"       [4] - inProcessingInfoRootFile"<<endl
	<<"       [5] - inLuminosityInfoRootFile"<<endl;
    cout<<" runID [1] = 3 (execution ID number) <- processing info"<<endl
      	<<"       [2] - outRootFile"<<endl
	<<"       [3] - vecparID (offskim_bhabhaecl = 0  offskim_dstar = 1  offskim_mumu = 2)"<<endl
      	<<"       [4] - vector length"<<endl
	<<"       [5] - data vector"<<endl;
    cout<<" runID [1] = 4 (execution ID number)"<<endl
      	<<"       [2] - outRootFile"<<endl
	<<"       [3] - vecparID (recorded  = 0 delivered = 1) <- integrated luminosities"<<endl
      	<<"       [4] - vector length"<<endl
	<<"       [5] - data vector"<<endl;
  }
  return 0;
}
