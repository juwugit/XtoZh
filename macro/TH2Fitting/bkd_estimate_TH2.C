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
void bkd_estimate_TH2(std::string inputFile1, std::string inputFile2, std::string histo1, std::string histo2){


  TFile *data = TFile::Open(inputFile1.data());
  TFile *MC = TFile::Open(inputFile2.data());


  TH2F* h_alpha = (TH2F*)MC->Get(histo1.data());
  TH2F* h_sbdata = (TH2F*)data->Get(histo2.data());
  TH2F* h_data_Nbkg = (TH2F*)h_sbdata->Clone("h_data_Nbkg");

  h_data_Nbkg->Reset();
  h_data_Nbkg->SetTitle("number of estimated background in data signal region");


  // get value of alpha ratio each bin
  Int_t nbinsx = h_alpha->GetNbinsX();
  Int_t nbinsy = h_alpha->GetNbinsY();
  Double_t alpha_center[nbinsx][nbinsy];
  Double_t alpha_error[nbinsx][nbinsy];


  for(Int_t i=1; i<=nbinsx; i++){
    for(Int_t j=1; j<=nbinsy; j++){
    
      alpha_center[i][j] = h_alpha->GetBinContent(i,j);
      alpha_error[i][j] = h_alpha->GetBinError(i,j);
  
    }
  }


    
  // calculate estimated background number in data signal region
  Double_t data_content[nbinsx][nbinsy];
  Double_t data_error[nbinsx][nbinsy];
  Double_t data_Nbkg[nbinsx][nbinsy];
  Double_t data_NbkgError[nbinsx][nbinsy];


  for(Int_t i=1; i<=nbinsx; i++){
    for(Int_t j=1; j<=nbinsy; j++){

      data_content[i][j] = h_sbdata->GetBinContent(i,j);
      data_error[i][j] = h_sbdata->GetBinError(i,j);
    data_Nbkg[i][j] = data_content[i][j] * alpha_center[i][j];

    h_data_Nbkg->SetBinContent(i,j,data_Nbkg[i][j]);    
    data_NbkgError[i][j]=0;
    

    if(alpha_center[i][j]==0 || data_content[i][j]==0) continue;
    
    data_NbkgError[i][j] = (data_Nbkg[i][j])*sqrt(pow(alpha_error[i][j]/alpha_center[i][j],2)+pow(data_error[i][j]/data_content[i][j],2));
    h_data_Nbkg->SetBinError(i,j,data_NbkgError[i][j]);
    
    

    //cout<<"bin:"<<i<<" | alpha:"<<alpha_center[i]<<" | number of data:"<<data_content[i]<<" | number of etimated bkg:"<<data_Nbkg[i]<<" | error:"<<data_NbkgError[i]<<endl;
    

    } //j
  } //i
  
  

  TFile *test = new TFile(inputFile1.data(), "update");
  test->cd();

  TH1F* h_NbkgSubCSV = (TH1F*)h_data_Nbkg->Clone("h_NbkgSubCSV");
  
  h_NbkgSubCSV->Write();
  test->Close();


}

