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
  
  
  for(Int_t i=0; i<nbinsx; i++){
    for(Int_t j=0; j<nbinsy; j++){
      
      alpha_center[i][j] = h_alpha->GetBinContent(i+1,j+1);
      alpha_error[i][j] = h_alpha->GetBinError(i+1,j+1);
      
    }
  }
  

    
  // calculate estimated background number in data signal region
  Double_t data_content[nbinsx][nbinsy];
  Double_t data_error[nbinsx][nbinsy];
  Double_t data_Nbkg[nbinsx][nbinsy];
  Double_t data_NbkgError[nbinsx][nbinsy];
 

  for(Int_t i=0; i<nbinsx; i++){
    for(Int_t j=0; j<nbinsy; j++){

      data_content[i][j] = h_sbdata->GetBinContent(i+1,j+1);
      data_error[i][j] = h_sbdata->GetBinError(i+1,j+1);
      data_Nbkg[i][j] = data_content[i][j] * alpha_center[i][j];
      
      h_data_Nbkg->SetBinContent(i+1,j+1,data_Nbkg[i][j]);    
      data_NbkgError[i][j]=0;
      
      
      if(alpha_center[i][j]==0 || data_content[i][j]==0) continue;
      
      data_NbkgError[i][j] = (data_Nbkg[i][j])*sqrt(pow(alpha_error[i][j]/alpha_center[i][j],2)+pow(data_error[i][j]/data_content[i][j],2));
      h_data_Nbkg->SetBinError(i+1,j+1,data_NbkgError[i][j]);
      
      
      
      cout<<"binX:"<<i+1<<" |binY:"<<j+1<<" |alpha:"<<alpha_center[i][j]<<" |number of data:"<<data_content[i][j]<<" |number of etimated bkg:"<<data_Nbkg[i][j]<<" |error:"<<data_NbkgError[i][j]<<endl;
      
      
    } //j
  } //i
  
  

  TFile *temp = new TFile(inputFile1.data(), "update");
  temp->cd();

  TH1F* h_NbkgXMsCSV_DY = (TH1F*)h_data_Nbkg->Clone("h_NbkgXMsCSV_DY");
  
  h_NbkgXMsCSV_DY->Write();
  temp->Close();


}

