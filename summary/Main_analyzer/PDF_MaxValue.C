#include <map>
#include <vector>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <TH1.h>
#include <TH2.h>
#include <TRandom.h>
#include <TLorentzVector.h>
#include <TFile.h>

using namespace std;

void PDF_MaxValue(string inputFile){


  // load file and 2d histos
  TFile *rootfile  = TFile::Open(inputFile.data());

  TH2F *hzy0   = (TH2F*)(rootfile->Get("h_sigMxSubjetCSVPDF0"));
  TH2F *hzy1   = (TH2F*)(rootfile->Get("h_sigMxSubjetCSVPDF1"));
  TH2F *hzy2   = (TH2F*)(rootfile->Get("h_sigMxSubjetCSVPDF2"));
  TH2F *hzy3   = (TH2F*)(rootfile->Get("h_sigMxSubjetCSVPDF3"));
  TH2F *hzy4   = (TH2F*)(rootfile->Get("h_sigMxSubjetCSVPDF4"));
  TH2F *hzy5   = (TH2F*)(rootfile->Get("h_sigMxSubjetCSVPDF5"));

  TH2F* hzyUp  = (TH2F*)hzy0->Clone("hzyUp");
  TH2F* hzyDown= (TH2F*)hzy0->Clone("hzyDown");

  hzyUp->Reset();
  hzyDown->Reset();



  // get value from histos
  Int_t nbinsx = hzy0->GetNbinsX();
  Int_t nbinsy = hzy0->GetNbinsY();
  
  Float_t contentUp[nbinsx][nbinsy];
  Float_t contentDown[nbinsx][nbinsy];


  for(Int_t i=0; i<nbinsx; i++){
    for(Int_t j=0; j<nbinsy; j++){

      
      Float_t center = hzy0->GetBinContent(i+1,j+1);
      Float_t pdf[5];
      Float_t diff[5];

      pdf[0] = hzy1->GetBinContent(i+1,j+1);
      pdf[1] = hzy2->GetBinContent(i+1,j+1);
      pdf[2] = hzy3->GetBinContent(i+1,j+1);
      pdf[3] = hzy4->GetBinContent(i+1,j+1);
      pdf[4] = hzy5->GetBinContent(i+1,j+1);

      diff[0] = fabs(pdf[0]-center);
      diff[1] = fabs(pdf[1]-center);
      diff[2] = fabs(pdf[2]-center);
      diff[3] = fabs(pdf[3]-center);
      diff[4] = fabs(pdf[4]-center);

      std::sort(diff,diff+5);
      
      Float_t diff_max = diff[4];
      
      contentUp[i][j] = center + diff_max;

      if( (center-diff_max)>=0 ) 
      contentDown[i][j] = center-diff_max;
      else contentDown[i][j] = center;
      

      // fill 
      hzyUp->SetBinContent(i+1,j+1,contentUp[i][j]);
      hzyDown->SetBinContent(i+1,j+1,contentDown[i][j]);

    } //j
  } //i


  TFile* outFile = new TFile(inputFile.data(),"update");
  outFile->cd();

  hzyUp->SetName("h_sigMxSubjetCSV_pdfshapeUp");
  hzyUp->Write();
  hzyDown->SetName("h_sigMxSubjetCSV_pdfshapeDown");
  hzyDown->Write();


  outFile->Close();

}
