#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <TPad.h>
#include <TH1D.h>
#include <TH1F.h>
#include <TMath.h>
#include <TFile.h>
#include <TList.h>
#include <TGraph.h>
#include <TStyle.h>
#include <TChain.h>
#include <THStack.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TBranch.h>
#include <TRandom.h>
#include <TVectorT.h>
#include <TProfile.h>
#include <TLorentzVector.h>
#include <TSystemDirectory.h>
#include <TGraphAsymmErrors.h>

const Int_t totalNEvent1 = 11765438;
const Int_t totalNEvent2 = 12511326;
const Int_t totalNEvent3 = 10783509;
const Double_t crossSection1 = 63.5;
const Double_t crossSection2 = 39.4;
const Double_t crossSection3 = 25.8;

// scale = ? fb^-1 / luminosity

Double_t scale1 = 876.225 / (totalNEvent1 / crossSection1); // DYJetsToLL_PtZ-70To100
Double_t scale2 = 876.225 / (totalNEvent2 / crossSection2); // DYJetsToLL_PtZ100
Double_t scale3 = 876.225 / (totalNEvent3 / crossSection3); // TTbar


void myPlot(TH1D*, TH1D*, TH1D*, TH1D*);
void myPlot2(TH1D*, TH1D*, TH1D*, TH1D*);

void stackJetVariables(){

  cout<<"scale1:"<<scale1<<endl;
  cout<<"scale2:"<<scale2<<endl;
  cout<<"scale3:"<<scale3<<endl;


  TFile *f1e = TFile::Open("delpanj_v2_DYJetsToLL_PtZ-70To100_ee.root");
  TFile *f2e = TFile::Open("delpanj_v2_DYJetsToLL_PtZ-100_ee.root");
  TFile *f3e = TFile::Open("delpanj_v2_TTTo2L2Nu2B_ee.root");
  TFile *f1m = TFile::Open("delpanj_v2_DYJetsToLL_PtZ-70To100_mm.root");
  TFile *f2m = TFile::Open("delpanj_v2_DYJetsToLL_PtZ-100_mm.root");
  TFile *f3m = TFile::Open("delpanj_v2_TTTo2L2Nu2B_mm.root");
  TFile *f4 = TFile::Open("delpanj_v2_data_DoubleEl_A.root");
  TFile *f5 = TFile::Open("delpanj_v2_data_DoubleMu_A.root");




  gStyle->SetOptStat(0);

  TCanvas* c = new TCanvas("c", "", 0, 0, 1920, 1080);
  c->Divide(2,2);


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //
 

  c->cd(1);
  myPlot( ((TH1D*)(f1e->Get("h_mLL"))), 
	  ((TH1D*)(f2e->Get("h_mLL"))), 
	  ((TH1D*)(f3e->Get("h_mLL"))), 
	  ((TH1D*)(f4->Get("h_mLL")))
	  );

  
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //


  c->cd(2);
  myPlot2( ((TH1D*)(f1m->Get("h_mLL"))), 
	   ((TH1D*)(f2m->Get("h_mLL"))), 
	   ((TH1D*)(f3m->Get("h_mLL"))), 
	   ((TH1D*)(f5->Get("h_mLL")))
	   );


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - //


  c->cd(3);
  myPlot( ((TH1D*)(f1e->Get("h_CA8jetTau21"))),
          ((TH1D*)(f2e->Get("h_CA8jetTau21"))),
          ((TH1D*)(f3e->Get("h_CA8jetTau21"))),
          ((TH1D*)(f4->Get("h_CA8jetTau21")))
          );



  c->cd(4);
  myPlot( ((TH1D*)(f1m->Get("h_CA8jetTau21"))),
          ((TH1D*)(f2m->Get("h_CA8jetTau21"))),
          ((TH1D*)(f3m->Get("h_CA8jetTau21"))),
          ((TH1D*)(f5->Get("h_CA8jetTau21")))
          );


  c->Print("JetVariable.gif");

}



void myPlot(TH1D* h_dy70, TH1D* h_dy100, TH1D* h_ttbar, TH1D* h_data){

  h_data->Sumw2();

  h_dy70->Scale(scale1);
  h_dy70->SetFillColor(kCyan-4);
  h_dy70->SetLineColor(kBlack);

  h_dy100->Scale(scale2);
  h_dy100->SetFillColor(kAzure+9);
  h_dy100->SetLineColor(kBlack);

  h_ttbar->Scale(scale3);
  h_ttbar->SetFillColor(kOrange+8);
  h_ttbar->SetLineColor(kBlack);



  THStack *h_stack = new THStack("h_stack", "");
  h_stack->Add(h_dy70);
  h_stack->Add(h_dy100);
  h_stack->Add(h_ttbar);


  h_data->SetLineColor(1);
  h_data->SetMarkerStyle(8);
  h_data->SetMarkerSize(0.5);
  h_data->Draw("e1"); 
  h_stack->Draw("same");
  h_data->Draw("e1same");



  TLegend *leg = new TLegend(0.65, 0.75, 0.9, 0.9);

  leg->SetFillStyle(1001);
  leg->SetFillColor(10);
  leg->SetBorderSize(1);
  leg->AddEntry(h_ttbar,"TTTo2L2Nu2B.root", "f"); 
  leg->AddEntry(h_dy100,"DYJetsToLL_PtZ-100", "f"); 
  leg->AddEntry(h_dy70, "DYJetsToLL_PtZ-70To100", "f"); 
  leg->AddEntry(h_data, "Data", "lp");
  leg->Draw();

}



void myPlot2(TH1D* h_dy70, TH1D* h_dy100, TH1D* h_ttbar, TH1D* h_data){

  h_data->Sumw2();

  h_dy70->Scale(scale1);
  h_dy70->SetFillColor(kCyan-4);
  h_dy70->SetLineColor(kBlack);

  h_dy100->Scale(scale2);
  h_dy100->SetFillColor(kAzure+9);
  h_dy100->SetLineColor(kBlack);

  h_ttbar->Scale(scale3);
  h_ttbar->SetFillColor(kOrange+8);
  h_ttbar->SetLineColor(kBlack);



  THStack *h_stack = new THStack("h_stack", "");
  h_stack->Add(h_dy70);
  h_stack->Add(h_dy100);
  h_stack->Add(h_ttbar);


  h_data->SetLineColor(1);
  h_data->SetMarkerStyle(8);
  h_data->SetMarkerSize(0.5);
  //h_data->Draw("e1");
  h_stack->Draw("hist");
  h_data->Draw("e1same");



  TLegend *leg = new TLegend(0.65, 0.75, 0.9, 0.9);

  leg->SetFillStyle(1001);
  leg->SetFillColor(10);
  leg->SetBorderSize(1);
  leg->AddEntry(h_ttbar,"TTTo2L2Nu2B.root", "f");
  leg->AddEntry(h_dy100,"DYJetsToLL_PtZ-100", "f");
  leg->AddEntry(h_dy70, "DYJetsToLL_PtZ-70To100", "f");
  leg->AddEntry(h_data, "Data", "lp");
  leg->Draw();

}
