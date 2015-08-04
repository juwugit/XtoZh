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



void cout_diff(std::string inputFile1, std::string inputFile2, std::string inputHisto){


  TFile *madgraph = TFile::Open(inputFile1.data());
  TFile *sherpa = TFile::Open(inputFile2.data());

  TH1F* h_madgraph = (TH1F*)madgraph->Get(inputHisto.data());
  TH1F* h_sherpa   = (TH1F*)sherpa->Get(inputHisto.data());

  Int_t nbin = h_madgraph->GetNbinsX();
  Float_t mad_bincontent[nbin];
  Float_t she_bincontent[nbin];
  Float_t diff[nbin];

  for(Int_t i=0; i<nbin; i++){

    mad_bincontent[i] = h_madgraph->GetBinContent(i+1);
    she_bincontent[i] = h_sherpa->GetBinContent(i+1);

    diff[i] = fabs(mad_bincontent[i]-she_bincontent[i]);

    cout<<"bin:"<<i+1<<" | diff:"<<diff[i]<<" | mad:"<<mad_bincontent[i]<<" | she:"<<she_bincontent[i]<<endl;

  }
}

