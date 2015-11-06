#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <TPad.h>
#include <TH1D.h>
#include <TH1F.h>
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

void PDF_MaxError(string inputFile, string inputFile2){


  TFile *rootfile  = TFile::Open(inputFile.data());
  TFile *rootfile2 = TFile::Open(inputFile2.data());
  /*
  TH1D *hzy0   = (TH1D*)(rootfile->Get("h_sigXMassPDF0"));
  TH1D *hzy1   = (TH1D*)(rootfile->Get("h_sigXMassPDF1"));
  TH1D *hzy2   = (TH1D*)(rootfile->Get("h_sigXMassPDF2"));
  TH1D *hzy3   = (TH1D*)(rootfile->Get("h_sigXMassPDF3"));
  TH1D *hzy4   = (TH1D*)(rootfile->Get("h_sigXMassPDF4"));
  TH1D *hzy5   = (TH1D*)(rootfile2->Get("h_sigXMassPDF2"));
  */
  TH1D *hzy0   = (TH1D*)(rootfile->Get("h_sigSubjetCSVPDF0"));
  TH1D *hzy1   = (TH1D*)(rootfile->Get("h_sigSubjetCSVPDF1"));
  TH1D *hzy2   = (TH1D*)(rootfile->Get("h_sigSubjetCSVPDF2"));
  TH1D *hzy3   = (TH1D*)(rootfile->Get("h_sigSubjetCSVPDF3"));
  TH1D *hzy4   = (TH1D*)(rootfile->Get("h_sigSubjetCSVPDF4"));
  TH1D *hzy5   = (TH1D*)(rootfile2->Get("h_sigSubjetCSVPDF2"));


  Int_t nbinsx = hzy0->GetNbinsX();
  Double_t diff_max[nbinsx];
  Double_t error[nbinsx];
  //Double_t error_max[nbinsx];
  double total_error=0.0;

  for(int i=0; i<nbinsx; i++){

    double center = hzy0->GetBinContent(i+1);
    Double_t pdf[5];
    Double_t diff[5];
    
    pdf[0] = hzy1->GetBinContent(i+1);
    pdf[1] = hzy2->GetBinContent(i+1);
    pdf[2] = hzy3->GetBinContent(i+1);
    pdf[3] = hzy4->GetBinContent(i+1);
    pdf[4] = hzy5->GetBinContent(i+1);

    diff[0] = fabs(pdf[0]-center);
    diff[1] = fabs(pdf[1]-center);
    diff[2] = fabs(pdf[2]-center);
    diff[3] = fabs(pdf[3]-center);
    diff[4] = fabs(pdf[4]-center);

    std::sort(diff,diff+5);

    for(int j=0; j<5; j++) cout<<"bin:"<<i+1<<" | center:"<<center<<" | diff:"<<diff[j]<<endl;
    
    diff_max[i]=diff[4];
    cout<<"diff_max:"<<diff_max[i]<<endl;
    
    if(center==0.0) continue;

    error[i] = diff_max[i]/center;
    cout<<"error:"<<error[i]<<endl;

    total_error = total_error + pow(error[i],2);


  } //for

  total_error = sqrt(total_error);
  //cout<<"total_error(100% uncor):"<<total_error<<endl;
  std::sort(error,error+nbinsx);
  //double error_max = diff_max[nbinsx-1]/
  cout<<"======================================================="<<endl;
  cout<<"error_max:"<<error[nbinsx-1]<<endl;

  double denom = hzy0->Integral();
  double sum=0.0;

  for(int i=0; i<nbinsx; i++) sum=sum+diff_max[i];

  

  //cout<<"total_error(100% cor):"<<sum/denom<<endl;

}
