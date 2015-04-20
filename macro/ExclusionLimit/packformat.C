#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <TPad.h>
#include <TH1.h>
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
void packformat(std::string inputFile1, std::string inputFile2, std::string outputFile){


  TFile *data = TFile::Open(inputFile1.data());
  TFile *MC_sig = TFile::Open(inputFile2.data());


  TH1F* signal = (TH1F*)MC_sig->Get("h_sigSubCSV");
  TH1F* background = (TH1F*)data->Get("h_NbkgSubCSV");
  TH1F* data_sig = (TH1F*)data->Get("h_sigSubCSV");
  TH1F* data_obs = (TH1F*)data->Get("h_sbSubCSV");


  signal->Scale(0.003217348); // El:0.003217348 ; Mu:0.003209842
  data_obs->Add(data_sig);






  

  TFile *temp = new TFile(outputFile.data(), "recreate");

  
  signal->Write();
  background->Write();
  data_obs->Write();
  data_sig->Write();


  temp->Close();


}

