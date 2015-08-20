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


  //XMass
  TH1F* h_DY_sbXMass = (TH1F*)DY->Get("h_sbXMass");
  TH1F* h_BKD_sbXMass = (TH1F*)BKD->Get("h_sbXMass");

  TH1F* h_ratio_sbXMass = (TH1F*)h_BKD_sbXMass->Clone("h_ratio_sbXMass");
  h_ratio_sbXMass->Reset();
  h_ratio_sbXMass->Divide(h_DY_sbXMass,h_BKD_sbXMass);


  //CA8jetCSV
  TH1F* h_DY_sbCA8jetCSV = (TH1F*)DY->Get("h_sbCA8jetCSV");
  TH1F* h_BKD_sbCA8jetCSV = (TH1F*)BKD->Get("h_sbCA8jetCSV");

  TH1F* h_ratio_sbCA8jetCSV = (TH1F*)h_BKD_sbCA8jetCSV->Clone("h_ratio_sbCA8jetCSV");
  h_ratio_sbCA8jetCSV->Reset();
  h_ratio_sbCA8jetCSV->Divide(h_DY_sbCA8jetCSV,h_BKD_sbCA8jetCSV);


  //SubjetCSV
  TH1F* h_DY_sbSubjetCSV = (TH1F*)DY->Get("h_sbSubjetCSV");
  TH1F* h_BKD_sbSubjetCSV = (TH1F*)BKD->Get("h_sbSubjetCSV");

  TH1F* h_ratio_sbSubjetCSV = (TH1F*)h_BKD_sbSubjetCSV->Clone("h_ratio_sbSubjetCSV");
  h_ratio_sbSubjetCSV->Reset();
  h_ratio_sbSubjetCSV->Divide(h_DY_sbSubjetCSV,h_BKD_sbSubjetCSV);


  
    
  TFile *temp = new TFile(outputFile.data(),"RECREATE");

  h_ratio_sbXMass->Write();
  h_ratio_sbCA8jetCSV->Write();
  h_ratio_sbSubjetCSV->Write();


  temp->Close();
  
}

