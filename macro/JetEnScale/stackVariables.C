#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <TPad.h>
#include <TH1D.h>
#include <TF1.h>
#include <TH1F.h>
#include <TH2F.h>
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



void stackVariables(){


  TFile *central = TFile::Open("rootfile/data_El.root");
  TFile *up = TFile::Open("rootfile/data_El_up.root");
  TFile *down = TFile::Open("rootfile/data_El_down.root");


  gStyle->SetOptStat(0);


  TH1F* central_NbkgXMass = (TH1F*)central->Get("h_NbkgXMass_DYJets");
  TH1F* up_NbkgXMass = (TH1F*)up->Get("h_NbkgXMass_DYJets");
  TH1F* down_NbkgXMass = (TH1F*)down->Get("h_NbkgXMass_DYJets");


  //up_NbkgXMass->SetTitle("sideband XMass: madgraph vs sherpa");
  up_NbkgXMass->GetXaxis()->SetTitle("XMass (GeV)");
  up_NbkgXMass->SetFillStyle(3004);
  up_NbkgXMass->SetFillColor(2);
  up_NbkgXMass->SetLineColor(2);

  down_NbkgXMass->SetFillStyle(3003);
  down_NbkgXMass->SetFillColor(4);
  down_NbkgXMass->SetLineColor(4);

  central_NbkgXMass->SetLineColor(1);
  central_NbkgXMass->SetLineWidth(2);
  central_NbkgXMass->SetMarkerColor(1);
  central_NbkgXMass->SetMarkerStyle(20);
  central_NbkgXMass->SetMarkerSize(1);

  up_NbkgXMass->Draw("histe");
  down_NbkgXMass->Draw("histesame");
  central_NbkgXMass->Draw("esame");


  TLegend* leg = new TLegend(0.5,0.7,0.8,0.8);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->AddEntry(central_NbkgXMass,"CENTRAL","lep");
  leg->AddEntry(up_NbkgXMass,"UP","F");
  leg->AddEntry(down_NbkgXMass,"DOWN","F");
  leg->Draw("same");



}

