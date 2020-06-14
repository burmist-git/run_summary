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

Int_t plots_runNumber(){

  TString fileN1;
  TString fileN2;
  //TString objectName;
  fileN1 = "./rootdata/exp03/runSummary_exp03_hist.root";
  fileN2 = "./rootdata/exp07/runSummary_exp07_hist.root";

  TFile *f1 = new TFile(fileN1.Data());
  TFile *f2 = new TFile(fileN2.Data());

  TGraph *gr1_1 = (TGraph*)f1->Get("gr_runNumber_vs_time");
  TGraph *gr1_2 = (TGraph*)f2->Get("gr_runNumber_vs_time");
  
  TCanvas *c1 = new TCanvas("c1",fileN1.Data(),10,10,1200,1000);
  c1->Divide(1,2);
  
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  gPad->SetGridx();
  gPad->SetGridy();
  //gStyle->SetOptStat(kFALSE);

  gr1_1->SetLineColor(kBlack);
  gr1_1->SetLineWidth(3.0);
  //gr1_1->SetMinimum(0.0);
  //gr1_2->SetMinimum(0.0);
  //gr1_1->SetMaximum(800);
  //gr1_1->SetLineColor(kRed);
  gr1_2->SetLineColor(kBlack);
  gr1_2->SetLineWidth(3.0);

  //gr1_1->SetTitle("Exp3");
  //gr1_2->SetTitle("Exp7");
  gr1_1->SetTitle("");
  gr1_2->SetTitle("");

  //gr1_1->Draw();
  //gr1_2->Draw("sames");
  
  c1->cd(1);
  gPad->SetGridx();
  gPad->SetGridy();
  gr1_1->Draw();
  TLegend *leg1 = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  leg1->AddEntry( gr1_1, "Exp3", "apl");
  leg1->Draw();  

  c1->cd(2);
  gPad->SetGridx();
  gPad->SetGridy();
  gr1_2->Draw();
  TLegend *leg2 = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  leg2->AddEntry( gr1_2, "Exp7", "apl");
  leg2->Draw();  

  //h1_1->GetXaxis()->SetRangeUser(0,30000);  

  gr1_1->GetXaxis()->SetTimeDisplay(1);
  gr1_1->GetXaxis()->SetTimeFormat("#splitline{%y/%m/%d}{%H:%M:%S}%F1970-01-01 00:00:00"); 
  gr1_1->GetXaxis()->SetLabelOffset(0.025);
  gr1_1->GetXaxis()->SetTitle("Time, h");

  gr1_2->GetXaxis()->SetTimeDisplay(1);
  gr1_2->GetXaxis()->SetTimeFormat("#splitline{%y/%m/%d}{%H:%M:%S}%F1970-01-01 00:00:00"); 
  gr1_2->GetXaxis()->SetLabelOffset(0.025);
  gr1_2->GetXaxis()->SetTitle("Time, h");
  
  //TString legInfo;
  //TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  //leg->AddEntry( h1_1, "All runs", "apl");
  //leg->AddEntry( h1_2, "Physics runs", "apl");
  //leg->AddEntry( h1_1, "Exp3", "apl");
  //leg->AddEntry( h1_2, "Exp7", "apl");
  //leg->Draw();  

  return 0;
}
