#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <TPad.h>
#include <TH1D.h>
#include <TH1F.h>
#include <TSystem.h>
#include <TMath.h>
#include <TFile.h>
#include <TList.h>
#include <TImage.h>
#include <TLine.h>
#include <TAxis.h>
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


void ratio(){

  TFile *f = TFile::Open("test_Mu.root");

  gStyle->SetOptStat(0);


  TH1F* h_sigXMass = (TH1F*)f->Get("h_sigXMass");
  TH1F* h_sigXMassPlus = (TH1F*)f->Get("h_sigXMassPlus");
  TH1F* h_sigRatio = (TH1F*)h_sigXMass->Clone("h_sigRatio");
  h_sigRatio->Divide(h_sigXMassPlus,h_sigXMass);


  TH1F* h_sbXMass = (TH1F*)f->Get("h_sbXMass");
  TH1F* h_sbXMassPlus = (TH1F*)f->Get("h_sbXMassPlus");
  TH1F* h_sbRatio = (TH1F*)h_sbXMass->Clone("h_sbRatio");
  h_sbRatio->Divide(h_sbXMassPlus,h_sbXMass);



  TCanvas* c1 = new TCanvas();

  c1->Divide(2,2);
  c1->cd(1);

  h_sigXMassPlus->SetFillColor(2);
  h_sigXMassPlus->SetFillStyle(3004);

  h_sigXMass->SetFillColor(4);
  h_sigXMass->SetFillStyle(3005);

  h_sigXMassPlus->Draw("histe");
  h_sigXMass->Draw("histesame");
 

  c1->cd(3);

  h_sigRatio->Draw();




  c1->cd(2);

  h_sbXMassPlus->SetFillColor(2);
  h_sbXMassPlus->SetFillStyle(3004);

  h_sbXMass->SetFillColor(4);
  h_sbXMass->SetFillStyle(3005);

  h_sbXMassPlus->Draw("histe");
  h_sbXMass->Draw("histesame");

  c1->cd(4);

  h_sbRatio->Draw();


  c1->Print("c1.png");

}
