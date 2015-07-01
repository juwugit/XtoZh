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
void errorband(std::string inputFile, std::string inputFileUp, std::string inputFileDown, std::string histo, std::string outputhisto){


  TFile *root = TFile::Open(inputFile.data());
  TFile *root_Up = TFile::Open(inputFileUp.data());
  TFile *root_Down = TFile::Open(inputFileDown.data());


  TH1F* h_sig = (TH1F*)root->Get(histo.data());
  TH1F* h_sigUp = (TH1F*)root_Up->Get(histo.data());
  TH1F* h_sigDown = (TH1F*)root_Down->Get(histo.data());


  TCanvas* c1 = new TCanvas("jet energy scale systematic uncertainty");

  c1->Divide(1,2);

  Int_t nbins = h_sig->GetNbinsX();
  Double_t XMass[nbins];
  Double_t NoE[nbins];
  Double_t exl[nbins];
  Double_t exh[nbins];
  Double_t eyl[nbins];
  Double_t eyh[nbins];
  Double_t ex[nbins];
  Double_t ey[nbins];
  Double_t frac[nbins];


  for(Int_t i=0; i<nbins; i++){

    XMass[i] = h_sig->GetXaxis()->GetBinCenter(i+1);
    NoE[i] = h_sig->GetBinContent(i+1);

    exl[i] = 0.0;
    exh[i] = 0.0;

    eyl[i] = fabs( (h_sigDown->GetBinContent(i+1)) - (h_sig->GetBinContent(i+1)) );
    eyh[i] = fabs( (h_sigUp->GetBinContent(i+1)) - (h_sig->GetBinContent(i+1)) );

    ex[i] = 0.0;
    ey[i] = h_sig->GetBinError(i+1);


    frac[i] = 0.0;


    if(NoE[i]==0) continue;
    if( max(eyh[i]/NoE[i],eyl[i]/NoE[i])==0 ) continue;

    frac[i] = max(eyh[i]/NoE[i],eyl[i]/NoE[i]);


    cout<<"nbin:"<<i+1<<"| center:"<<NoE[i]<<"| errUp:"<<eyh[i]<<"| errDown:"<<eyl[i]<<"| percentage:"<<100*max(eyh[i]/NoE[i],eyl[i]/NoE[i])<<"%"<<endl;



  }


  TGraph* gr = new TGraph(nbins,XMass,frac);;
  TGraphAsymmErrors* gr1 = new TGraphAsymmErrors(nbins,XMass,NoE,exl,exh,eyl,eyh);
  TGraphErrors* gr2 = new TGraphErrors(nbins,XMass,NoE,ex,ey);
  
  c1->cd(1);
  
  gr1->SetFillColor(5);
  gr1->Draw("aE4");
  gr1->SetTitle("XMass distribution with JetEnScale");
  
  //gr2->SetLineColor(1);
  //gr2->SetLineWidth(2);
  //gr2->SetMarkerColor(1);
  gr2->SetMarkerStyle(20);
  gr2->SetMarkerSize(0.6);
  gr2->Draw("e1Psame");
  
  
  c1->cd(2);

  gr->Draw("aP");
  gr->SetMarkerStyle(20);
  gr->SetMarkerSize(1);
  gr->SetTitle("sys_error / central value");


  c1->Print(outputhisto.data());
  
}

