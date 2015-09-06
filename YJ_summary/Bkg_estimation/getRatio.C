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
void getRatio(std::string inputFile1, std::string inputFile2){


  TFile *DY  = TFile::Open(inputFile1.data());
  TFile *BKD = TFile::Open(inputFile2.data());


  //CA8jetCSV
  TH2F* h_DY_sbMxCA8jetCSV = (TH2F*)DY->Get("h_sbMxCA8jetCSV");
  TH2F* h_BKD_sbMxCA8jetCSV = (TH2F*)BKD->Get("h_sbMxCA8jetCSV");

  TH2F* h_ratio_sbMxCA8jetCSV = (TH2F*)h_BKD_sbMxCA8jetCSV->Clone("h_ratio_sbMxCA8jetCSV");
  h_ratio_sbMxCA8jetCSV->Reset();
  h_ratio_sbMxCA8jetCSV->Divide(h_DY_sbMxCA8jetCSV,h_BKD_sbMxCA8jetCSV);
  

  //SubjetCSV
  TH2F* h_DY_sbMxSubjetCSV = (TH2F*)DY->Get("h_sbMxSubjetCSV");
  TH2F* h_BKD_sbMxSubjetCSV = (TH2F*)BKD->Get("h_sbMxSubjetCSV");

  TH2F* h_ratio_sbMxSubjetCSV = (TH2F*)h_BKD_sbMxSubjetCSV->Clone("h_ratio_sbMxSubjetCSV");
  h_ratio_sbMxSubjetCSV->Reset();
  h_ratio_sbMxSubjetCSV->Divide(h_DY_sbMxSubjetCSV,h_BKD_sbMxSubjetCSV);


      

  TFile *temp = new TFile(inputFile1.data(), "update");
  temp->cd();

  h_ratio_sbMxCA8jetCSV->Write();
  h_ratio_sbMxSubjetCSV->Write();

  temp->Close();
  
}
