//my
#include "mdstana.hh"
#include "processingInfoStr.h"
#include "integratedLuminosityStr.h"

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
#include <TRandom3.h>
#include <TGraphErrors.h>
#include <TMath.h>

//C, C++
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <bits/stdc++.h>

using namespace std;

void mdstana::Loop(TString histOut){
  //
  GetExpTimeStartStop();
  //
  cout<<"v_procInfF_cdst.size() = "<<v_procInfF_cdst.size()<<endl;
  vector<processingInfoStr> v_procInf;
  for(UInt_t ui = 0;ui<v_procInfF_cdst.size()/4.0;ui++){
    processingInfoStr procInf;
    procInf.entryID = v_procInfF_cdst.at(ui*4 + 0);
    procInf.procFileSize = v_procInfF_cdst.at(ui*4 + 1);
    procInf.expID = v_procInfF_cdst.at(ui*4 + 2);
    procInf.runID = v_procInfF_cdst.at(ui*4 + 3);
    v_procInf.push_back(procInf);
  }
  cout<<"v_procInf.size() = "<<v_procInf.size()<<endl;
  //
  cout<<"v_intLumF.size() = "<<v_intLumF.size()<<endl;
  vector<integratedLuminosityStr> v_intLum;
  for(UInt_t ui = 0;ui<v_intLumF.size()/3.0;ui++){
    integratedLuminosityStr intLum;
    intLum.expID = v_intLumF.at(ui*3 + 0);
    intLum.runID = v_intLumF.at(ui*3 + 1);
    intLum.intLum = v_intLumF.at(ui*3 + 2);
    v_intLum.push_back(intLum);
  }
  cout<<"v_intLum.size() = "<<v_intLum.size()<<endl;
  //
  TH1D *h1_procFileSize = new TH1D("h1_procFileSize","procFileSize",100,0.0,250.0);
  for(UInt_t ui = 0;ui<v_procInf.size();ui++){
    h1_procFileSize->Fill(v_procInf.at(ui).procFileSize/1024.0);
  }
  //
  TH1D *h1_intLum_pb = new TH1D("h1_intLum_pb","intLum pb",1000,0.0,50.0);
  for(UInt_t ui = 0;ui<v_intLum.size();ui++){
    //v_intLum.at(ui).printIntegratedLuminosityInfo();
    h1_intLum_pb->Fill(v_intLum.at(ui).intLum/1000.0);
  }
  //
  Double_t rate = -999.0;
  Int_t startTimeOld = -999;
  /////////////////// HIST /////////////////
  TH1D *h1_runType_all = new TH1D("h1_runType_all","runType all",5,-2.5,2.5);
  TH1D *h1_runType = new TH1D("h1_runType","runType",5,-2.5,2.5);
  TH1D *h1_triggerType_all = new TH1D("h1_triggerType_all","triggerType all",5,-2.5,2.5);
  TH1D *h1_triggerType = new TH1D("h1_triggerType","triggerType",5,-2.5,2.5);
  //
  TH1D *h1_runLength = new TH1D("h1_runLength","runLength",200,0.0,10000);  
  TH1D *h1_numberOfEvents = new TH1D("h1_numberOfEvents","numberOfEvents",400,0.0,10*1000000);
  TH1D *h1_rate = new TH1D("h1_rate","rate",400,0.0,10000);
  TH1D *h1_nBunchesHER = new TH1D("h1_nBunchesHER","nBunchesHER",100,0.0,5000);
  TH1D *h1_nBunchesLER = new TH1D("h1_nBunchesLER","nBunchesLER",100,0.0,5000);
  //
  TH1D *h1_beamIHERstart = new TH1D("h1_beamIHERstart","beamIHERstart",400,0.0,400);
  TH1D *h1_beamILERstart = new TH1D("h1_beamILERstart","beamILERstart",400,0.0,400);
  TH1D *h1_beamIHERstop = new TH1D("h1_beamIHERstop","beamIHERstop",400,0.0,400);
  TH1D *h1_beamILERstop = new TH1D("h1_beamILERstop","beamILERstop",400,0.0,400);
  //
  TH1D *h1_beam_dI_HER = new TH1D("h1_beam_dI_HER","beam_dI_HER",400,0.0,400);
  TH1D *h1_beam_dI_LER = new TH1D("h1_beam_dI_LER","beam_dI_LER",400,0.0,400);
  //
  TH1D *h1_statusCDC = new TH1D("h1_statusCDC","statusCDC",4,-1.5,2.5);
  TH1D *h1_statusARICH = new TH1D("h1_statusARICH","statusARICH",4,-1.5,2.5);
  TH1D *h1_statusECL = new TH1D("h1_statusECL","statusECL",4,-1.5,2.5);
  TH1D *h1_statusKLM = new TH1D("h1_statusKLM","statusKLM",4,-1.5,2.5);
  TH1D *h1_statusTRG = new TH1D("h1_statusTRG","statusTRG",4,-1.5,2.5);
  //
  TH1D *h1_statusPXD = new TH1D("h1_statusPXD","statusPXD",4,-1.5,2.5);
  TH1D *h1_statusSVD = new TH1D("h1_statusSVD","statusSVD",4,-1.5,2.5);
  TH1D *h1_statusTOP = new TH1D("h1_statusTOP","statusTOP",4,-1.5,2.5);
  //
  TGraphErrors *gr_numberOfEvents_vs_time = new TGraphErrors();
  gr_numberOfEvents_vs_time->SetName("gr_numberOfEvents_vs_time");
  gr_numberOfEvents_vs_time->SetTitle("numberOfEvents vs time");
  //
  TGraph *gr_runNumber_vs_time = new TGraph();
  gr_runNumber_vs_time->SetName("gr_runNumber_vs_time");
  gr_runNumber_vs_time->SetTitle("runNumber vs time");
  //
  TH1D *h1_touLER = new TH1D("h1_touLER","h1_touLER",400,0.0,50000.0);
  TH1D *h1_touHER = new TH1D("h1_touHER","h1_touHER",400,0.0,50000.0);
  //
  TH1D *h1_beam_x_HERstart = new TH1D("h1_beam_x_HERstart","beam x HERstart",400,0.0,300.0);
  TH1D *h1_beam_y_HERstart = new TH1D("h1_beam_y_HERstart","beam y HERstart",400,0.0,300.0);
  TH1D *h1_beam_x_LERstart = new TH1D("h1_beam_x_LERstart","beam x LERstart",400,0.0,300.0);
  TH1D *h1_beam_y_LERstart = new TH1D("h1_beam_y_LERstart","beam y LERstart",400,0.0,300.0);
  //
  TH1D *h1_beam_x_HERstop = new TH1D("h1_beam_x_HERstop","beam x HERstop",400,0.0,300.0);
  TH1D *h1_beam_y_HERstop = new TH1D("h1_beam_y_HERstop","beam y HERstop",400,0.0,300.0);
  TH1D *h1_beam_x_LERstop = new TH1D("h1_beam_x_LERstop","beam x LERstop",400,0.0,300.0);
  TH1D *h1_beam_y_LERstop = new TH1D("h1_beam_y_LERstop","beam y LERstop",400,0.0,300.0);
  //
  TH2D *h2_touHER_vs_beam_y_HERstart = new TH2D("h2_touHER_vs_beam_y_HERstart","touHER vs beam y HERstart",400,0.0,300.0,400,0.0,50000.0);
  TH2D *h2_touHER_vs_beamIHERstart = new TH2D("h2_touHER_vs_beamIHERstart","touHER vs beamIHERstart",400,0.0,400.0,400,0.0,50000.0);
  TH2D *h2_touHER_vs_dbeamIHER = new TH2D("h2_touHER_vs_dbeamIHER","touHER vs dbeamIHER",400,0.0,400.0,400,0.0,50000.0);
  TH2D *h2_touHER_vs_dtime = new TH2D("h2_touHER_vs_dtime","touHER vs dtime",400,0.0,4000.0,400,0.0,50000.0);
  TH2D *h2_dbeamIHER_vs_dtime = new TH2D("h2_dbeamIHER_vs_dtime","dbeamIHER vs dtime",400,0.0,4000.0,400,0.0,400.0);
  //
  TGraph *gr_cdstsize_vs_numberOfEvents = new TGraph();
  gr_cdstsize_vs_numberOfEvents->SetName("gr_cdstsize_vs_numberOfEvents");
  gr_cdstsize_vs_numberOfEvents->SetTitle("cdstsize vs numberOfEvents");
  //
  TGraph *gr_intLum_vs_numberOfEvents = new TGraph();
  gr_intLum_vs_numberOfEvents->SetName("gr_intLum_vs_numberOfEvents");
  gr_intLum_vs_numberOfEvents->SetTitle("intLum vs numberOfEvents");
  TGraph *gr_intLumSum_vs_time = new TGraph();
  gr_intLumSum_vs_time->SetName("gr_intLumSum_vs_time");
  gr_intLumSum_vs_time->SetTitle("intLumSum vs time");
  Float_t intLumSum = 0.0;
  //
  //Float_t bins[] = { 50, 55, 60, 65, 72, 80, 90, 100, 120, 160 };
  //Int_t  binnum = sizeof(bins)/sizeof(Float_t) - 1; // or just = 9
  //TH1D *h1_test = new TH1D("h1_test","test", binnum, bins);
  //for(Int_t i = 1;i<10;i++)
  //h1_test->SetBinContent(i,i);
  //////////////////////////////////////////
  cout<<"expTimeStart  "<<expTimeStart<<endl
      <<"expTimeStop   "<<expTimeStop<<endl
      <<"durationOfDataTakingCampaign_day "<<durationOfDataTakingCampaign_day<<endl;
  //////////////////////////////////////////
  Long64_t nentries = fChain->GetEntriesFast();
  cout<<"nentries = "<<nentries<<endl;
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    //
    if(startTimeOld <= startTime){
      startTimeOld = startTime;
    }
    else{
      cout<<"expNumber = "<<expNumber<<endl
	  <<"runNumber = "<<runNumber<<endl;
      assert(0);
    }
    //
    if(runType == cosmic || runType == physics)
      h1_runType_all->Fill(runType);
    else
      h1_runType_all->Fill(-1.0);
    if(triggerType ==  aux || triggerType == gdl)
      h1_triggerType_all->Fill(triggerType);
    else
      h1_triggerType_all->Fill(-1.0);
    //
    if(false == ifCut())
      continue;
    if(runType == cosmic || runType == physics)
      h1_runType->Fill(runType);
    else
      h1_runType->Fill(-1.0);
    if(triggerType ==  aux || triggerType == gdl)
      h1_triggerType->Fill(triggerType);
    else
      h1_triggerType->Fill(-1.0);
    //
    h1_runLength->Fill(runLength);
    h1_numberOfEvents->Fill(numberOfEvents);
    rate = -999.0;
    if(runLength>0)
      rate = numberOfEvents/runLength;
    h1_rate->Fill(rate);
    h1_nBunchesHER->Fill(nBunchesHER);
    h1_nBunchesLER->Fill(nBunchesLER);
    //
    h1_beamIHERstart->Fill(beamIHERstart);
    h1_beamILERstart->Fill(beamILERstart);
    h1_beamIHERstop->Fill(beamIHERstop);
    h1_beamILERstop->Fill(beamILERstop);
    h1_beam_dI_HER->Fill(beamIHERstart - beamIHERstop);
    h1_beam_dI_LER->Fill(beamILERstart - beamILERstop);
    //    
    h1_statusCDC->Fill(statusCDC);
    h1_statusARICH->Fill(statusARICH);
    h1_statusECL->Fill(statusECL);
    h1_statusKLM->Fill(statusKLM);
    h1_statusTRG->Fill(statusTRG);
    //
    h1_statusPXD->Fill(statusPXD);
    h1_statusSVD->Fill(statusSVD);
    h1_statusTOP->Fill(statusTOP);
    //
    gr_numberOfEvents_vs_time->SetPoint(gr_numberOfEvents_vs_time->GetN(), startTime + runLength/2.0, numberOfEvents);
    gr_numberOfEvents_vs_time->SetPointError(gr_numberOfEvents_vs_time->GetN()-1, runLength/2.0, 0.0);
    //
    gr_runNumber_vs_time->SetPoint(gr_runNumber_vs_time->GetN(), startTime, runNumber);
    //
    h1_touHER->Fill(getBeamTou(beamIHERstart,beamIHERstop,startTime,stopTime));
    h1_touLER->Fill(getBeamTou(beamILERstart,beamILERstop,startTime,stopTime));
    //
    h1_beam_x_HERstart->Fill(beam_x_HERstart);
    h1_beam_y_HERstart->Fill(beam_y_HERstart);
    h1_beam_x_LERstart->Fill(beam_x_LERstart);
    h1_beam_y_LERstart->Fill(beam_y_LERstart);
    //
    h1_beam_x_HERstop->Fill(beam_x_HERstop);
    h1_beam_y_HERstop->Fill(beam_y_HERstop);
    h1_beam_x_LERstop->Fill(beam_x_LERstop);
    h1_beam_y_LERstop->Fill(beam_y_LERstop);
    //
    h2_touHER_vs_beam_y_HERstart->Fill(beam_y_HERstart,getBeamTou(beamIHERstart,beamIHERstop,startTime,stopTime));
    h2_touHER_vs_beamIHERstart->Fill(beamIHERstart,getBeamTou(beamIHERstart,beamIHERstop,startTime,stopTime));
    h2_touHER_vs_dbeamIHER->Fill(beamIHERstart - beamIHERstop,getBeamTou(beamIHERstart,beamIHERstop,startTime,stopTime));
    h2_touHER_vs_dtime->Fill(stopTime - startTime,getBeamTou(beamIHERstart,beamIHERstop,startTime,stopTime));
    h2_dbeamIHER_vs_dtime->Fill(stopTime - startTime,beamIHERstart - beamIHERstop);
    //
    for(UInt_t ui = 0;ui<v_procInf.size();ui++){
      if(v_procInf.at(ui).expID == expNumber){
	if(v_procInf.at(ui).runID == runNumber){
	  gr_cdstsize_vs_numberOfEvents->SetPoint(gr_cdstsize_vs_numberOfEvents->GetN(), numberOfEvents, v_procInf.at(ui).procFileSize/1024.0);
	}
      }
    }
    //
    for(UInt_t ui = 0;ui<v_intLum.size();ui++){
      if(v_intLum.at(ui).expID == expNumber){
	if(v_intLum.at(ui).runID == runNumber){
	  gr_intLum_vs_numberOfEvents->SetPoint(gr_intLum_vs_numberOfEvents->GetN(), numberOfEvents, v_intLum.at(ui).intLum/1000.0);
	  intLumSum += v_intLum.at(ui).intLum/1000.0;
	  gr_intLumSum_vs_time->SetPoint(gr_intLumSum_vs_time->GetN(), startTime, intLumSum);
	}
      }
    }
  }
  /////////////////////////////////
  Int_t nbinsx_ev_vs_t = 0;
  Float_t *xbins_ev_vs_t = new Float_t[gr_numberOfEvents_vs_time->GetN()*2+1];
  Float_t *valbins_ev_vs_t = new Float_t[gr_numberOfEvents_vs_time->GetN()*2+1];
  Int_t i = 0;
  Int_t ii = 0;
  Double_t timeRun_start;
  Double_t timeRun_stop;
  Double_t timeRun;
  Double_t nEvRun;
  Double_t timeWindowBetweenTwoRuns_stop;
  cout<<"gr_numberOfEvents_vs_time->GetN() = "<<gr_numberOfEvents_vs_time->GetN()<<endl;
  for( i = 0; i<gr_numberOfEvents_vs_time->GetN(); i++){
    gr_numberOfEvents_vs_time->GetPoint(i, timeRun, nEvRun);
    timeRun_start = timeRun - gr_numberOfEvents_vs_time->GetErrorX(i);
    timeRun_stop = timeRun + gr_numberOfEvents_vs_time->GetErrorX(i);
    //cout<<"i "<<i<<endl;
    if(i == 0){
      xbins_ev_vs_t[ii] = timeRun_start;
      valbins_ev_vs_t[ii] = 0.0;
      ii++;
    }
    else{
      gr_numberOfEvents_vs_time->GetPoint(i, timeRun, nEvRun);
      timeWindowBetweenTwoRuns_stop = timeRun - gr_numberOfEvents_vs_time->GetErrorX(i);
      xbins_ev_vs_t[ii] = timeWindowBetweenTwoRuns_stop;
      valbins_ev_vs_t[ii] = 0.0;
      ii++;
    }
    xbins_ev_vs_t[ii] = timeRun_stop;
    valbins_ev_vs_t[ii] = nEvRun;
    ii++;
  }
  nbinsx_ev_vs_t = ii-1;
  TH1D *h1_numberOfEvents_vs_time = new TH1D("h1_numberOfEvents_vs_time","numberOfEvents vs time",nbinsx_ev_vs_t,xbins_ev_vs_t);
  //cout<<"ii "<<ii<<endl;
  for( i = 0;i<ii;i++)
    h1_numberOfEvents_vs_time->SetBinContent(i,valbins_ev_vs_t[i]);
  /////////////////////////////////
  TFile* rootFile = new TFile(histOut.Data(), "RECREATE", " Histograms", 1);
  rootFile->cd();
  if (rootFile->IsZombie()){
    cout<<"  ERROR ---> file "<<histOut.Data()<<" is zombi"<<endl;
    assert(0);
  }
  else
    cout<<"  Output Histos file ---> "<<histOut.Data()<<endl;
  h1_runType_all->Write();
  h1_runType->Write();
  h1_triggerType_all->Write();
  h1_triggerType->Write();
  h1_runLength->Write();
  h1_numberOfEvents->Write();
  h1_rate->Write();
  h1_nBunchesHER->Write();
  h1_nBunchesLER->Write();
  h1_beamIHERstart->Write();
  h1_beamILERstart->Write();
  h1_beamIHERstop->Write();
  h1_beamILERstop->Write();
  h1_beam_dI_HER->Write();
  h1_beam_dI_LER->Write();
  h1_statusCDC->Write();
  h1_statusARICH->Write();
  h1_statusECL->Write();
  h1_statusKLM->Write();
  h1_statusTRG->Write();
  h1_statusPXD->Write();
  h1_statusSVD->Write();
  h1_statusTOP->Write();
  gr_numberOfEvents_vs_time->Write();
  gr_runNumber_vs_time->Write();
  h1_numberOfEvents_vs_time->Write();
  h1_touHER->Write();
  h1_touLER->Write();
  h1_beam_x_HERstart->Write();
  h1_beam_y_HERstart->Write();
  h1_beam_x_LERstart->Write();
  h1_beam_y_LERstart->Write();
  h1_beam_x_HERstop->Write();
  h1_beam_y_HERstop->Write();
  h1_beam_x_LERstop->Write();
  h1_beam_y_LERstop->Write();
  h2_touHER_vs_beam_y_HERstart->Write();
  h2_touHER_vs_beamIHERstart->Write();
  h2_touHER_vs_dbeamIHER->Write();
  h2_touHER_vs_dtime->Write();
  h2_dbeamIHER_vs_dtime->Write();
  gr_cdstsize_vs_numberOfEvents->Write();
  h1_procFileSize->Write();
  h1_intLum_pb->Write();
  gr_intLum_vs_numberOfEvents->Write();
  gr_intLumSum_vs_time->Write();
  //h1_test->Write();  
  rootFile->Close();
}

//if(runNumber == 4176 || runNumber > 4500)
bool mdstana::ifCut(){
  if(runType == physics){
    if(triggerType == gdl || triggerType == aux){
      if(numberOfEvents>0){
	if(runLength>0){
	  if(expNumber == 3)
	    if(runNumber == 5608)
	      return false;
	  return true;
	}
      }
    }
  }
  return false;
}

void mdstana::GetExpTimeStartStop(){
  Long64_t nentries = fChain->GetEntriesFast();
  //Int_t nentriesInt = nentries;
  LoadTree(0);
  GetEntry(0);
  expTimeStart = startTime;
  LoadTree((nentries-1));
  GetEntry((nentries-1));
  expTimeStop = stopTime;
  durationOfDataTakingCampaign_day = (expTimeStop - expTimeStart)/3600.0/24.0;
}

Float_t mdstana::getBeamTou( Float_t beamIstart, Float_t beamIstop, Int_t startTime, Int_t stopTime){
  if ( beamIstart <= 0.0 )
    return -999.0;
  if ( beamIstop <= 0.0 )
    return -999.0;
  if ( beamIstart <= beamIHERstop )
    return -999.0;
  if ( (stopTime - startTime) <= 0.0 )
    return -999.0;
  return (stopTime - startTime)/(TMath::Log(beamIstart) - TMath::Log(beamIstop));
}
