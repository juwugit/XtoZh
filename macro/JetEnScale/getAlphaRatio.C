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
#include <TGraphErrors.h>


using namespace std;
void getAlphaRatio(float data_lumi, std::string inputFile1, std::string inputFile2, std::string outputFile){


  float scale1 = (data_lumi)/(11764538/63.5); //DY70To100   
  float scale2 = (data_lumi)/(12511326/39.4); //DY100    


  // load file
  TFile *DY70To100 = TFile::Open(inputFile1.data());
  TFile *DY100 = TFile::Open(inputFile2.data());


  // TH1 declare
  TH1F* h_sigXMass1 = (TH1F*)DY70To100->Get("h_sigXMass");
  TH1F* h_sbXMass1 = (TH1F*)DY70To100->Get("h_sbXMass");
  TH1F* h_sigCA8jetCSV1 = (TH1F*)DY70To100->Get("h_sigCA8jetCSV");
  TH1F* h_sbCA8jetCSV1 = (TH1F*)DY70To100->Get("h_sbCA8jetCSV");
  TH1F* h_sigSubjetCSV1 = (TH1F*)DY70To100->Get("h_sigSubjetCSV");
  TH1F* h_sbSubjetCSV1 = (TH1F*)DY70To100->Get("h_sbSubjetCSV");

  TH1F* h_sigXMass2 = (TH1F*)DY100->Get("h_sigXMass");
  TH1F* h_sbXMass2 = (TH1F*)DY100->Get("h_sbXMass");
  TH1F* h_sigCA8jetCSV2 = (TH1F*)DY100->Get("h_sigCA8jetCSV");
  TH1F* h_sbCA8jetCSV2 = (TH1F*)DY100->Get("h_sbCA8jetCSV");
  TH1F* h_sigSubjetCSV2 = (TH1F*)DY100->Get("h_sigSubjetCSV");
  TH1F* h_sbSubjetCSV2 = (TH1F*)DY100->Get("h_sbSubjetCSV");


  // XMass
  TH1F* h_sigXMass = (TH1F*)h_sigXMass1->Clone("h_sigXMass");
  h_sigXMass->Scale(scale1);
  h_sigXMass->Add(h_sigXMass2, scale2);

  TH1F* h_sbXMass = (TH1F*)h_sbXMass1->Clone("h_sbXMass");
  h_sbXMass->Scale(scale1);
  h_sbXMass->Add(h_sbXMass2, scale2);


  // CSV
  TH1F* h_sigCA8jetCSV = (TH1F*)h_sigCA8jetCSV1->Clone("h_sigCA8jetCSV");
  h_sigCA8jetCSV->Scale(scale1);
  h_sigCA8jetCSV->Add(h_sigCA8jetCSV2, scale2);

  TH1F* h_sbCA8jetCSV = (TH1F*)h_sbCA8jetCSV1->Clone("h_sbCA8jetCSV");
  h_sbCA8jetCSV->Scale(scale1);
  h_sbCA8jetCSV->Add(h_sbCA8jetCSV2, scale2);

  TH1F* h_sigSubjetCSV = (TH1F*)h_sigSubjetCSV1->Clone("h_sigSubjetCSV");
  h_sigSubjetCSV->Scale(scale1);
  h_sigSubjetCSV->Add(h_sigSubjetCSV2, scale2);

  TH1F* h_sbSubjetCSV = (TH1F*)h_sbSubjetCSV1->Clone("h_sbSubjetCSV");
  h_sbSubjetCSV->Scale(scale1);
  h_sbSubjetCSV->Add(h_sbSubjetCSV2, scale2);

  
  // AlphaRatio
  TH1F* h_alphaXMass = (TH1F*)h_sigXMass->Clone("h_alphaXMass");
  h_alphaXMass->Clear();
  h_alphaXMass->Divide(h_sigXMass, h_sbXMass);
  h_alphaXMass->SetName("h_alphaXMass");

  TH1F* h_alphaCA8jetCSV = (TH1F*)h_sigCA8jetCSV->Clone("h_alphaCA8jetCSV");
  h_alphaCA8jetCSV->Clear();
  h_alphaCA8jetCSV->Divide(h_sigCA8jetCSV, h_sbCA8jetCSV);
  h_alphaCA8jetCSV->SetName("h_alphaCA8jetCSV");

  TH1F* h_alphaSubjetCSV = (TH1F*)h_sigSubjetCSV->Clone("h_alphaSubjetCSV");
  h_alphaSubjetCSV->Clear();
  h_alphaSubjetCSV->Divide(h_sigSubjetCSV, h_sbSubjetCSV);
  h_alphaSubjetCSV->SetName("h_alphaSubjetCSV");


  // save file
  TFile* outFile = new TFile(outputFile.data(),"recreate");

  h_sbXMass->Write();
  h_sigXMass->Write();
  h_alphaXMass->Write();

  h_sbCA8jetCSV->Write();
  h_sigCA8jetCSV->Write();
  h_alphaCA8jetCSV->Write();

  h_sbSubjetCSV->Write();
  h_sigSubjetCSV->Write();
  h_alphaSubjetCSV->Write();


  outFile->Close();




}
