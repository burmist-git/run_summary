//C, C++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include <time.h>

using namespace std;

TString getObjectName(TString namein, Int_t i);

Int_t plots(){

  TString fileN1;
  TString fileN2;
  TString objectName;
  fileN1 = "./rootdata/exp03/runSummary_exp03_hist.root";
  fileN2 = "./rootdata/exp07/runSummary_exp07_hist.root";
  fileN1 = fileN2;

  TFile *f1 = new TFile(fileN1.Data());
  TFile *f2 = new TFile(fileN2.Data());

  TGraph *h1_1 = (TGraph*)f1->Get("gr_cdstsize_vs_numberOfEvents");
  TGraph *h1_2 = (TGraph*)f2->Get("gr_cdstsize_vs_numberOfEvents");

  //TH1D *h1_1 = (TH1D*)f1->Get("h1_numberOfEvents_vs_time");
  //TH1D *h1_2 = (TH1D*)f2->Get("h1_numberOfEvents_vs_time");
  
  //h1_1->Rebin(4);
  //h1_2->Rebin(4);
  //h1_1->SetTitle("");
  TCanvas *c1 = new TCanvas("c1",fileN1.Data(),10,10,800,800);

  //TCanvas *c1 = new TCanvas("c1",fileN1.Data(),10,10,1200,1000);
  //c1->Divide(1,2);
  
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  gPad->SetGridx();
  gPad->SetGridy();
  //gStyle->SetOptStat(kFALSE);

  h1_1->SetLineColor(kBlack);
  h1_1->SetLineWidth(3.0);
  h1_1->SetMinimum(0.0);
  h1_2->SetMinimum(0.0);
  h1_1->SetMaximum(800);
  //h1_1->SetMaximum(10*1000000);
  //h1_2->SetMaximum(10*1000000);
  //h1_2->SetLineColor(kRed);
  h1_2->SetLineColor(kBlack);
  h1_2->SetLineWidth(3.0);

  //h1_1->SetTitle("Exp3");
  //h1_2->SetTitle("Exp7");
  h1_1->SetTitle("");
  h1_2->SetTitle("");

  h1_2->Draw("AP");
  //h1_2->Draw("sames");
  
  //c1->cd(1);
  //gPad->SetGridx();
  //gPad->SetGridy();
  //h1_1->Draw();
  //TLegend *leg1 = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  //leg1->AddEntry( h1_1, "Exp3", "apl");
  //leg1->Draw();  

  //c1->cd(2);
  //h1_2->Draw();
  //gPad->SetGridx();
  //gPad->SetGridy();
  //TLegend *leg2 = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  //leg2->AddEntry( h1_2, "Exp7", "apl");
  //leg2->Draw();  
  //h1_2->Draw("sames");

  //h1_1->GetXaxis()->SetRangeUser(0,30000);  

  //h1_1->GetXaxis()->SetTimeDisplay(1);
  //h1_1->GetXaxis()->SetTimeFormat("#splitline{%y/%m/%d}{%H:%M:%S}%F1970-01-01 00:00:00"); 
  //h1_1->GetXaxis()->SetLabelOffset(0.025);
  //h1_1->GetXaxis()->SetTitle("Time, h");

  //h1_2->GetXaxis()->SetTimeDisplay(1);
  //h1_2->GetXaxis()->SetTimeFormat("#splitline{%y/%m/%d}{%H:%M:%S}%F1970-01-01 00:00:00"); 
  //h1_2->GetXaxis()->SetLabelOffset(0.025);
  //h1_2->GetXaxis()->SetTitle("Time, h");
  
  TString legInfo;
  TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  //leg->AddEntry( h1_1, "All runs", "apl");
  //leg->AddEntry( h1_2, "Physics runs", "apl");
  //leg->AddEntry( h1_1, "Exp3", "apl");
  leg->AddEntry( h1_2, "Exp7", "apl");
  leg->Draw();  

  return 0;
}
