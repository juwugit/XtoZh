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
#include <TGraphErrors.h>


using namespace std;
void mergeDYJets(std::string inputFile1, std::string inputFile2, std::string outputFile){


  // Load file
  TFile *DY70To100 = TFile::Open(inputFile1.data());
  TFile *DY100 = TFile::Open(inputFile2.data());


  // Load TH2 histograms
  TH2F* h_sigMxCA8jetCSV1 = (TH2F*)DY70To100->Get("h_sigMxCA8jetCSV");
  TH2F* h_sbMxCA8jetCSV1  = (TH2F*)DY70To100->Get("h_sbMxCA8jetCSV");
  TH2F* h_sigMxSubjetCSV1 = (TH2F*)DY70To100->Get("h_sigMxSubjetCSV");
  TH2F* h_sbMxSubjetCSV1  = (TH2F*)DY70To100->Get("h_sbMxSubjetCSV");

  TH2F* h_sigMxCA8jetCSV2 = (TH2F*)DY100->Get("h_sigMxCA8jetCSV");
  TH2F* h_sbMxCA8jetCSV2  = (TH2F*)DY100->Get("h_sbMxCA8jetCSV");
  TH2F* h_sigMxSubjetCSV2 = (TH2F*)DY100->Get("h_sigMxSubjetCSV");
  TH2F* h_sbMxSubjetCSV2  = (TH2F*)DY100->Get("h_sbMxSubjetCSV");


  // Merge TH2 histograms
  TH2F* h_sigMxCA8jetCSV = (TH2F*)h_sigMxCA8jetCSV1->Clone("h_sigMxCA8jetCSV");
  h_sigMxCA8jetCSV->Add(h_sigMxCA8jetCSV2);
  TH2F* h_sbMxCA8jetCSV = (TH2F*)h_sbMxCA8jetCSV1->Clone("h_sbMxCA8jetCSV");
  h_sbMxCA8jetCSV->Add(h_sbMxCA8jetCSV2);
  TH2F* h_sigMxSubjetCSV = (TH2F*)h_sigMxSubjetCSV1->Clone("h_sigMxSubjetCSV");
  h_sigMxSubjetCSV->Add(h_sigMxSubjetCSV2);
  TH2F* h_sbMxSubjetCSV = (TH2F*)h_sbMxSubjetCSV1->Clone("h_sbMxSubjetCSV");
  h_sbMxSubjetCSV->Add(h_sbMxSubjetCSV2);

  
  // AlphaRatio
  const Double_t varBins[] = {680,720,760,800,840,920,1000,1100,1250,1400,1600,1800,2000,2400};
  Int_t nvarBins = sizeof(varBins)/sizeof(varBins[0])-1;


  TH2F* h_alphaMxCA8jetCSV = new TH2F("h_alphaMxCA8jetCSV","",nvarBins,varBins,5,0,1);
  h_alphaMxCA8jetCSV->Sumw2();
  h_alphaMxCA8jetCSV->Divide(h_sigMxCA8jetCSV, h_sbMxCA8jetCSV);

  TH2F* h_alphaMxSubjetCSV = new TH2F("h_alphaMxSubjetCSV","",nvarBins,varBins,5,0,1);
  h_alphaMxSubjetCSV->Sumw2();
  h_alphaMxSubjetCSV->Divide(h_sigMxSubjetCSV, h_sbMxSubjetCSV);



  // Save file
  TFile* outFile = new TFile(outputFile.data(),"recreate");

  h_sigMxCA8jetCSV->Write();
  h_sbMxCA8jetCSV->Write();

  h_sigMxSubjetCSV->Write();
  h_sbMxSubjetCSV->Write();

  h_alphaMxCA8jetCSV->Write();
  h_alphaMxSubjetCSV->Write();

  outFile->Close();

}
