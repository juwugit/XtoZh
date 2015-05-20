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
void getRatio(std::string inputFile1, std::string inputFile2, std::string outputFile){


  TFile *DY  = TFile::Open(inputFile1.data());
  TFile *BKD = TFile::Open(inputFile2.data());


  //CA8jetCSV
  TH2F* h_DY_sbXMCSV = (TH2F*)DY->Get("h_sbXMCSV");
  TH2F* h_BKD_sbXMCSV = (TH2F*)BKD->Get("h_sbXMCSV");

  TH2F* h_ratio_sbXMCSV = (TH2F*)h_BKD_sbXMCSV->Clone("h_ratio_sbXMCSV");
  h_ratio_sbXMCSV->Reset();
  h_ratio_sbXMCSV->Divide(h_DY_sbXMCSV,h_BKD_sbXMCSV);


  //subjetCSV
  TH2F* h_DY_sbXMsCSV = (TH2F*)DY->Get("h_sbXMsCSV");
  TH2F* h_BKD_sbXMsCSV = (TH2F*)BKD->Get("h_sbXMsCSV");

  TH2F* h_ratio_sbXMsCSV = (TH2F*)h_BKD_sbXMsCSV->Clone("h_ratio_sbXMsCSV");
  h_ratio_sbXMsCSV->Reset();
  h_ratio_sbXMsCSV->Divide(h_DY_sbXMsCSV,h_BKD_sbXMsCSV);

  
    
  TFile *temp = new TFile(outputFile.data(),"RECREATE");


  h_ratio_sbXMCSV->Write();
  h_ratio_sbXMsCSV->Write();


  temp->Close();
  
}

