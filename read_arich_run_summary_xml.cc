/***********************************************************************
* Copyright(C) 2019 - LBS - (Single person developer.)                 *
* Thu May 23 11:01:04 JST 2019                                         *
* Autor: Leonid Burmistrov                                             *
***********************************************************************/
//my
#include "pcstatlog_arichxx/libpushVectorInRoot.h"
#include "arichRunSummaryStr.h"
#include "integratedLuminosityStr.h"

//root
#include "TXMLEngine.h"
#include "TString.h"

//c, c++
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

void read_arich_run_summary_xml(const char* filename){ 
  std::vector<arichRunSummaryStr> v_arichRunSum;
  std::vector<double> v_arichRunSumF;
  // First create engine
  TXMLEngine* xml = new TXMLEngine();
  // Now try to parse xml file
  // Only file with restricted xml syntax are supported
  XMLDocPointer_t xmldoc = xml->ParseFile(filename);
  if(xmldoc==0){
    delete xml;
    cout<<" ---> ERROR : not XMLDocPointer_t created "<<endl;
    return;
  }
  // take access to main node
  XMLNodePointer_t mainnode = xml->DocGetRootElement(xmldoc);
  TString nodeName = xml->GetNodeName(mainnode);
  //cout<<nodeName<<endl;
  XMLNodePointer_t child_info = xml->GetChild(mainnode);
  while(child_info!=0){
    nodeName = xml->GetNodeName(child_info);
    //cout<<nodeName<<endl;
    XMLNodePointer_t child = xml->GetChild(child_info);
    arichRunSummaryStr ars;
    while(child!=0){
      nodeName = xml->GetNodeName(child);
      //cout<<nodeName<<endl;
      if(nodeName == "run")
        ars.run = atoi(xml->GetNodeContent(child));
      else if(nodeName == "exp")
        ars.exp = atoi(xml->GetNodeContent(child));
      else if(nodeName == "neve")
        ars.neve = atoi(xml->GetNodeContent(child));
      else if(nodeName == "hitsPerEvent")
        ars.hitsPerEvent = atof(xml->GetNodeContent(child));
      else if(nodeName == "ntracks")
        ars.ntracks = atoi(xml->GetNodeContent(child));
      else if(nodeName == "nhot")
        ars.nhot = atoi(xml->GetNodeContent(child));
      else if(nodeName == "ndead")
        ars.ndead = atoi(xml->GetNodeContent(child));
      else if(nodeName == "ndeadHapd")
        ars.ndeadHapd = atoi(xml->GetNodeContent(child));
      else if(nodeName == "ntracksPerEvent")
        ars.ntracksPerEvent = atof(xml->GetNodeContent(child));
      else if(nodeName == "nsig")
        ars.nsig = atof(xml->GetNodeContent(child));
      else if(nodeName == "nsigErr")
        ars.nsigErr = atof(xml->GetNodeContent(child));
      else if(nodeName == "nbgr")
        ars.nbgr = atof(xml->GetNodeContent(child));
      else if(nodeName == "nbgrErr")
        ars.nbgrErr = atof(xml->GetNodeContent(child));
      else if(nodeName == "theta")
        ars.theta = atof(xml->GetNodeContent(child));
      else if(nodeName == "thetaErr")
        ars.thetaErr = atof(xml->GetNodeContent(child));
      else if(nodeName == "sigma")
        ars.sigma = atof(xml->GetNodeContent(child));
      else if(nodeName == "sigmaErr")
        ars.sigmaErr = atof(xml->GetNodeContent(child));
      else if(nodeName == "timestamp")
        ars.timestamp = atoi(xml->GetNodeContent(child));
      //if(nodeName == "timestamp")
      //cout<<ars.timestamp - atoi(xml->GetNodeContent(child))<<endl;
      child = xml->GetNext(child);
    }
    v_arichRunSum.push_back(ars);
    //cout<<endl<<endl;
    child_info = xml->GetNext(child_info);
  }
  for(UInt_t ui = 0; ui < v_arichRunSum.size(); ui++){
    //v_arichRunSum.at(ui).printArichRunSummaryInfo();
    v_arichRunSumF.push_back(v_arichRunSum.at(ui).run);
    v_arichRunSumF.push_back(v_arichRunSum.at(ui).exp);
    v_arichRunSumF.push_back(v_arichRunSum.at(ui).neve);
    v_arichRunSumF.push_back(v_arichRunSum.at(ui).hitsPerEvent);
    v_arichRunSumF.push_back(v_arichRunSum.at(ui).ntracks);
    v_arichRunSumF.push_back(v_arichRunSum.at(ui).nhot);
    v_arichRunSumF.push_back(v_arichRunSum.at(ui).ndead);
    v_arichRunSumF.push_back(v_arichRunSum.at(ui).ndeadHapd);
    v_arichRunSumF.push_back(v_arichRunSum.at(ui).ntracksPerEvent);
    v_arichRunSumF.push_back(v_arichRunSum.at(ui).nsig);
    v_arichRunSumF.push_back(v_arichRunSum.at(ui).nsigErr);
    v_arichRunSumF.push_back(v_arichRunSum.at(ui).nbgr);
    v_arichRunSumF.push_back(v_arichRunSum.at(ui).nbgrErr);
    v_arichRunSumF.push_back(v_arichRunSum.at(ui).theta);
    v_arichRunSumF.push_back(v_arichRunSum.at(ui).thetaErr);
    v_arichRunSumF.push_back(v_arichRunSum.at(ui).sigma);
    v_arichRunSumF.push_back(v_arichRunSum.at(ui).sigmaErr);
    v_arichRunSumF.push_back(v_arichRunSum.at(ui).timestamp);
  }
  TString outRootFile = filename;
  outRootFile += ".root";
  int vecparID = -999;
  int unixTimeInt = -999;
  pushVectorOfDoulesInRoot (outRootFile, vecparID, unixTimeInt, v_arichRunSumF);
}

void makePlots(const char* filenameArichSum, const char* filenameLum, const char* outHistFileName){
  TString inRootFileArichsum = filenameArichSum;
  TString inRootFileLum = filenameLum;
  //cout<<"inRootFileArichsum "<<inRootFileArichsum<<endl
  //  <<"inRootFileLum      "<<inRootFileLum<<endl;
  Long64_t jentry = 0;
  Float_t intLumSum = 0;
  Float_t intLumSumOld = 0;
  Int_t tZero = 0;
  //arich_run_summary
  std::vector<double> v_arichRunSumF = getDataVectorOfDoules (inRootFileArichsum, jentry);
  std::vector<arichRunSummaryStr> v_arichRunSum;
  Int_t nData = 18;
  for(UInt_t ui = 0; ui < v_arichRunSumF.size()/nData; ui++){
    arichRunSummaryStr ars;
    ars.run = v_arichRunSumF.at(ui*nData + 0);
    ars.exp = v_arichRunSumF.at(ui*nData + 1);
    ars.neve = v_arichRunSumF.at(ui*nData + 2);
    ars.hitsPerEvent = v_arichRunSumF.at(ui*nData + 3);
    ars.ntracks = v_arichRunSumF.at(ui*nData + 4);
    ars.nhot = v_arichRunSumF.at(ui*nData + 5);
    ars.ndead = v_arichRunSumF.at(ui*nData + 6);
    ars.ndeadHapd = v_arichRunSumF.at(ui*nData + 7);
    ars.ntracksPerEvent = v_arichRunSumF.at(ui*nData + 8);
    ars.nsig = v_arichRunSumF.at(ui*nData + 9);
    ars.nsigErr = v_arichRunSumF.at(ui*nData + 10);
    ars.nbgr = v_arichRunSumF.at(ui*nData + 11);
    ars.nbgrErr = v_arichRunSumF.at(ui*nData + 12);
    ars.theta = v_arichRunSumF.at(ui*nData + 13);
    ars.thetaErr = v_arichRunSumF.at(ui*nData + 14);
    ars.sigma = v_arichRunSumF.at(ui*nData + 15);
    ars.sigmaErr = v_arichRunSumF.at(ui*nData + 16);
    ars.timestamp = v_arichRunSumF.at(ui*nData + 17);
    //cout<<"ars.timestamp "<<ars.timestamp<<endl;
    v_arichRunSum.push_back(ars);
  }
  //exp_**.Luminosity
  std::vector<float> v_intLumF = getDataVector( inRootFileLum, jentry);
  vector<integratedLuminosityStr> v_intLum;
  for(UInt_t ui = 0;ui<v_intLumF.size() /3.0;ui++){
    integratedLuminosityStr intLum;
    intLum.expID = v_intLumF.at(ui*3 + 0);
    intLum.runID = v_intLumF.at(ui*3 + 1);
    intLum.intLum = v_intLumF.at(ui*3 + 2);
    v_intLum.push_back(intLum);
  }
  ///////////////////////////////////////////////////
  TH1D *h1_neve = new TH1D("h1_neve","neve",100,0.0,10000000.0);
  TH1D *h1_hitsPerEvent = new TH1D("h1_hitsPerEvent","hitsPerEvent",100,0.0,100.0);
  TH1D *h1_ntracks = new TH1D("h1_ntracks","ntracks",100,0.0,100000.0);
  TH1D *h1_nhot = new TH1D("h1_nhot","nhot",100,0.0,1000.0);
  TH1D *h1_ndead = new TH1D("h1_ndead","ndead",100,0.0,100.0);
  TH1D *h1_ndeadHapd = new TH1D("h1_ndeadHapd","ndeadHapd",100,0.0,100.0);
  TH1D *h1_ntracksPerEvent = new TH1D("h1_ntracksPerEvent","ntracksPerEvent",400,0.0,2.0);
  TH1D *h1_nsig = new TH1D("h1_nsig","nsig",200,0.0,20.0);
  TH1D *h1_nbgr = new TH1D("h1_nbgr","nbgr",200,0.0,20.0);
  TH1D *h1_theta = new TH1D("h1_theta","theta",100,0.0,0.5);
  TH1D *h1_sigma = new TH1D("h1_sigma","sigma",400,0.0,0.1);
  //
  TGraph *gr_intLumSum_vs_time = new TGraph();
  gr_intLumSum_vs_time->SetName("gr_intLumSum_vs_time");
  gr_intLumSum_vs_time->SetTitle("intLumSum vs time");
  //
  TGraph *gr_intLumSum_vs_time_zero = new TGraph();
  gr_intLumSum_vs_time_zero->SetName("gr_intLumSum_vs_time_zero");
  gr_intLumSum_vs_time_zero->SetTitle("intLumSum vs time_zero");
  //
  TGraph *gr_run_vs_time = new TGraph();
  gr_run_vs_time->SetName("gr_run_vs_time");
  gr_run_vs_time->SetTitle("run vs time");
  ///////////////////////////////////////////////////
  for(UInt_t ui = 0; ui < v_arichRunSum.size(); ui++){  
    //v_arichRunSum.at(ui).printArichRunSummaryInfo();
    arichRunSummaryStr ars = v_arichRunSum.at(ui);
    h1_neve->Fill(ars.neve);
    h1_hitsPerEvent->Fill(ars.hitsPerEvent);
    h1_ntracks->Fill(ars.ntracks);
    h1_nhot->Fill(ars.nhot);
    h1_ndead->Fill(ars.ndead);
    h1_ndeadHapd->Fill(ars.ndeadHapd);
    h1_ntracksPerEvent->Fill(ars.ntracksPerEvent);
    h1_nsig->Fill(ars.nsig);
    h1_nbgr->Fill(ars.nbgr);
    h1_theta->Fill(ars.theta);
    h1_sigma->Fill(ars.sigma);
    if(ars.timestamp>0 && ars.run > 0)
      gr_run_vs_time->SetPoint(gr_run_vs_time->GetN(), ars.timestamp, ars.run);
    //cout<<"ars.timestamp "<<ars.timestamp<<endl;
    //
    for(UInt_t ui = 0;ui<v_intLum.size();ui++){
      integratedLuminosityStr intLum = v_intLum.at(ui);
      if(intLum.expID == ars.exp){
        if(intLum.runID == ars.run){
	  if(ars.timestamp>0){
	    intLumSum += intLum.intLum/1000; //pb
	    if(intLumSumOld == 0.0 && intLumSum>0.0)
	      tZero = ars.timestamp;
	    gr_intLumSum_vs_time->SetPoint(gr_intLumSum_vs_time->GetN(), ars.timestamp, intLumSum);
	    gr_intLumSum_vs_time_zero->SetPoint(gr_intLumSum_vs_time_zero->GetN(), ars.timestamp - tZero, intLumSum);
	    intLumSumOld = intLumSum;
	  }
	}
      }
    }
    //
  }
  /////////////////////////////////
  TString histOut = outHistFileName;
  TFile* rootFile = new TFile(histOut.Data(), "RECREATE", " Histograms", 1);
  rootFile->cd();
  if (rootFile->IsZombie()){
    cout<<"  ERROR ---> file "<<histOut.Data()<<" is zombi"<<endl;
    assert(0);
  }
  else
    cout<<"  Output Histos file ---> "<<histOut.Data()<<endl;
  h1_neve->Write();
  h1_hitsPerEvent->Write();
  h1_ntracks->Write();
  h1_nhot->Write();
  h1_ndead->Write();
  h1_ndeadHapd->Write();
  h1_ntracksPerEvent->Write();
  h1_nsig->Write();
  h1_nbgr->Write();
  h1_theta->Write();
  h1_sigma->Write();
  gr_intLumSum_vs_time->Write();
  gr_run_vs_time->Write();
  gr_intLumSum_vs_time_zero->Write();
  //
  rootFile->Close();
}

#ifdef READ_ARICH_RUN_SUMMARY_XML_MAIN
int main(int argc, char *argv[]){
  if(argc == 3 && atoi(argv[1]) == 1){
    read_arich_run_summary_xml(argv[2]); 
  }
  if(argc == 5 && atoi(argv[1]) == 2){
    makePlots(argv[2],argv[3],argv[4]);
  }
  return 0;
}
#endif //READ_ARICH_RUN_SUMMARY_XML_MAIN
