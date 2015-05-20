#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <TPad.h>
#include <TH1.h>
#include <TH2.h>
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


using namespace std;
void packformat_TH2(){


  TFile *data = TFile::Open("data_El.root");
  TFile *DY_Up = TFile::Open("data_El_Up.root");
  TFile *DY_Down = TFile::Open("data_El_Down.root");

  TFile *TTbar = TFile::Open("TTbar/TTbar_El.root");
  TFile *TTbar_Up = TFile::Open("TTbar/TTbar_El_Up.root");
  TFile *TTbar_Down = TFile::Open("TTbar/TTbar_El_Down.root");

  TFile *WW = TFile::Open("WW/WW_El.root");
  TFile *WW_Up = TFile::Open("WW/WW_El_Up.root");
  TFile *WW_Down = TFile::Open("WW/WW_El_Down.root");

  TFile *WZ = TFile::Open("WZ/WZ_El.root");
  TFile *WZ_Up = TFile::Open("WZ/WZ_El_Up.root");
  TFile *WZ_Down = TFile::Open("WZ/WZ_El_Down.root");

  TFile *ZZ = TFile::Open("ZZ/ZZ_El.root");
  TFile *ZZ_Up = TFile::Open("ZZ/ZZ_El_Up.root");
  TFile *ZZ_Down = TFile::Open("ZZ/ZZ_El_Down.root");

  TFile *Sig = TFile::Open("Signal/MC_sig_M1000_El.root");
  TFile *Sig_Up = TFile::Open("Signal/MC_sig_M1000_El_Up.root");
  TFile *Sig_Down = TFile::Open("Signal/MC_sig_M1000_El_Down.root");

  //-----------------------------


  // data
  TH2F *data_sig = (TH2F*)data->Get("h_sigXMCSV");
  TH2F *data_obs = (TH2F*)data->Get("h_sbXMCSV");
  data_obs->Add(data_sig);
  data_obs->SetNameTitle("data_obs","");
  data_sig->SetNameTitle("data_sig","");



  // DY
  TH2F *background_DY = (TH2F*)data->Get("h_NbkgXMCSV_DY");
  TH2F *background_DY_alphaUp = (TH2F*)DY_Up->Get("h_NbkgXMCSV_DY");
  TH2F *background_DY_alphaDown = (TH2F*)DY_Down->Get("h_NbkgXMCSV_DY");
  background_DY->SetNameTitle("background_DY","");
  background_DY_alphaUp->SetNameTitle("background_DY_alphaUp","");
  background_DY_alphaDown->SetNameTitle("background_DY_alphaDown","");



  // TTbar
  TH2F *background_TT = (TH2F*)TTbar->Get("h_sigXMCSV");
  TH2F *background_TT_sigmaUp = (TH2F*)TTbar_Up->Get("h_sigXMCSV");
  TH2F *background_TT_sigmaDown = (TH2F*)TTbar_Down->Get("h_sigXMCSV");
  background_TT->SetNameTitle("background_TT","");
  background_TT_sigmaUp->SetNameTitle("background_TT_sigmaUp","");
  background_TT_sigmaDown->SetNameTitle("background_TT_sigmaDown","");



  // WW
  TH2F *background_WW = (TH2F*)WW->Get("h_sigXMCSV");
  TH2F *background_WW_sigmaUp = (TH2F*)WW_Up->Get("h_sigXMCSV");
  TH2F *background_WW_sigmaDown = (TH2F*)WW_Down->Get("h_sigXMCSV");
  background_WW->SetNameTitle("background_WW","");
  background_WW_sigmaUp->SetNameTitle("background_WW_sigmaUp","");
  background_WW_sigmaDown->SetNameTitle("background_WW_sigmaDown","");



  // WZ
  TH2F *background_WZ = (TH2F*)WZ->Get("h_sigXMCSV");
  TH2F *background_WZ_sigmaUp = (TH2F*)WZ_Up->Get("h_sigXMCSV");
  TH2F *background_WZ_sigmaDown = (TH2F*)WZ_Down->Get("h_sigXMCSV");
  background_WZ->SetNameTitle("background_WZ","");
  background_WZ_sigmaUp->SetNameTitle("background_WZ_sigmaUp","");
  background_WZ_sigmaDown->SetNameTitle("background_WZ_sigmaDown","");



  // ZZ
  TH2F *background_ZZ = (TH2F*)ZZ->Get("h_sigXMCSV");
  TH2F *background_ZZ_sigmaUp = (TH2F*)ZZ_Up->Get("h_sigXMCSV");
  TH2F *background_ZZ_sigmaDown = (TH2F*)ZZ_Down->Get("h_sigXMCSV");
  background_ZZ->SetNameTitle("background_ZZ","");
  background_ZZ_sigmaUp->SetNameTitle("background_ZZ_sigmaUp","");
  background_ZZ_sigmaDown->SetNameTitle("background_ZZ_sigmaDown","");



  // Signal
  TH2F* signal = (TH2F*)Sig->Get("h_sigXMsCSV");
  TH2F* signal_sigmaUp = (TH2F*)Sig_Up->Get("h_sigXMsCSV");
  TH2F* signal_sigmaDown = (TH2F*)Sig_Down->Get("h_sigXMsCSV");

  signal->Scale(0.003217348); // El:0.003217348 ; Mu:0.003209842  
  signal_sigmaUp->Scale(0.003217348);
  signal_sigmaDown->Scale(0.003217348);

  signal->SetNameTitle("signal","");
  signal_sigmaUp->SetNameTitle("signal_sigmaUp","");
  signal_sigmaDown->SetNameTitle("signal_sigmaDown","");
  



  TFile *temp = new TFile("XMassVsCA8jetCSV_TH2_M1000_El.root", "recreate");

  
  signal->Write();
  signal_sigmaUp->Write();
  signal_sigmaDown->Write();

  background_DY->Write();
  background_DY_alphaUp->Write();
  background_DY_alphaDown->Write();

  background_TT->Write();
  background_TT_sigmaUp->Write();
  background_TT_sigmaDown->Write();

  background_WW->Write();
  background_WW_sigmaUp->Write();
  background_WW_sigmaDown->Write();

  background_WZ->Write();
  background_WZ_sigmaUp->Write();
  background_WZ_sigmaDown->Write();

  background_ZZ->Write();
  background_ZZ_sigmaUp->Write();
  background_ZZ_sigmaDown->Write();

  data_obs->Write();
  data_sig->Write();


  temp->Close();


}

