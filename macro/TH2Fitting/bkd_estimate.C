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
void bkd_estimate(std::string inputFile1, std::string inputFile2, std::string histo1, std::string histo2){


  TFile *data = TFile::Open(inputFile1.data());
  TFile *MC = TFile::Open(inputFile2.data());


  TH1F* h_alpha = (TH1F*)MC->Get(histo1.data());
  TH1F* h_sbdata = (TH1F*)data->Get(histo2.data());
  TH1F* h_data_Nbkg = (TH1F*)h_sbdata->Clone("h_data_Nbkg");

  h_data_Nbkg->Reset();
  h_data_Nbkg->SetTitle("number of estimated background in data signal region");


  // get value of alpha ratio each bin
  Int_t alpha_nbin = h_alpha->GetNbinsX();
  Double_t alpha_center[alpha_nbin];
  Double_t alpha_error[alpha_nbin];

  for(Int_t i=1; i<=alpha_nbin; i++){

    alpha_center[i] = h_alpha->GetBinContent(i);
    alpha_error[i] = h_alpha->GetBinError(i);

  }

  
  // calculate estimated background number in data signal region
  Double_t data_content[alpha_nbin];
  Double_t data_error[alpha_nbin];
  Double_t data_Nbkg[alpha_nbin];
  Double_t data_NbkgError[alpha_nbin];


  for(Int_t i=1; i<=alpha_nbin; i++){

    data_content[i] = h_sbdata->GetBinContent(i);
    data_error[i] = h_sbdata->GetBinError(i);
    data_Nbkg[i] = data_content[i] * alpha_center[i];

    h_data_Nbkg->SetBinContent(i,data_Nbkg[i]);    
    data_NbkgError[i]=0;
    

    if(alpha_center[i]==0 || data_content[i]==0) continue;
    
    data_NbkgError[i] = (data_Nbkg[i])*sqrt(pow(alpha_error[i]/alpha_center[i],2)+pow(data_error[i]/data_content[i],2));
    h_data_Nbkg->SetBinError(i,data_NbkgError[i]);
    
    

    cout<<"bin:"<<i<<" | alpha:"<<alpha_center[i]<<" | number of data:"<<data_content[i]<<" | number of etimated bkg:"<<data_Nbkg[i]<<" | error:"<<data_NbkgError[i]<<endl;
    

  }

  

  TFile *test = new TFile(inputFile1.data(), "update");
  test->cd();

  TH1F* h_NbkgSubCSV = (TH1F*)h_data_Nbkg->Clone("h_NbkgSubCSV");
  
  h_NbkgSubCSV->Write();
  test->Close();


}

