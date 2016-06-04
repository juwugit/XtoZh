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
#include "setNCUStyle.C"


void myPlot(TH1D*, TH1D*, TH1D*, TH1D*, TH1D*, TH1D*, TH1D*);
void myRatio(TH1D*, TH1D*, TH1D*, TH1D*, TH1D*, TH1D*, TH1D*, Double_t, Double_t);

using namespace std;
void stackHisto(std::string inputhisto, std::string outputhisto, Double_t min, Double_t max, bool logY=false){


  TFile *dy70  = TFile::Open("result_cuts/TH2_DYJetsPtZ70To100_FN_Cen.root");
  TFile *dy100 = TFile::Open("result_cuts/TH2_DYJetsPtZ100_FN_Cen.root");
  TFile *ttbar = TFile::Open("result_cuts/TH2_TTTo2L2Nu2B_FN_Cen.root");
  TFile *ww    = TFile::Open("result_cuts/TH2_DiBWW_FN_Cen.root");
  TFile *wz    = TFile::Open("result_cuts/TH2_DiBWZ_FN_Cen.root");
  TFile *zz    = TFile::Open("result_cuts/TH2_DiBZZ_FN_Cen.root");
  TFile *data  = TFile::Open("result_cuts/data_FN_Cen.root");


  gStyle->SetOptStat(0);
  gStyle->SetPadGridY(kTRUE);
  gStyle->SetPadGridX(kTRUE);

  setNCUStyle(true);
  

  TCanvas* c = new TCanvas("c", "", 0, 0, 900, 900);

  Double_t up_height     = 0.8;
  Double_t dw_correction = 1.455;
  Double_t dw_height     = (1-up_height)*dw_correction;


  c->Divide(1,2);

  TPad* c_up = (TPad*) c->GetListOfPrimitives()->FindObject("c_1");
  TPad* c_dw = (TPad*) c->GetListOfPrimitives()->FindObject("c_2");

  c_up->SetPad(0,1-up_height,1,1);
  c_dw->SetPad(0,0,1,dw_height);
  c_dw->SetBottomMargin(0.25);

  c_up->cd();
  

  //-------------------------------------------//

  if(logY == true) c_up->SetLogy();
  myPlot( ((TH1D*)(dy70->Get(inputhisto.data()))), 
	  ((TH1D*)(dy100->Get(inputhisto.data()))), 
	  ((TH1D*)(ttbar->Get(inputhisto.data()))), 
	  ((TH1D*)(ww->Get(inputhisto.data()))), 
	  ((TH1D*)(wz->Get(inputhisto.data()))), 
	  ((TH1D*)(zz->Get(inputhisto.data()))), 
	  ((TH1D*)(data->Get(inputhisto.data())))
	  );

  //-------------------------------------------//

  c_dw->cd();
  myRatio( ((TH1D*)(dy70->Get(inputhisto.data()))), 
	  ((TH1D*)(dy100->Get(inputhisto.data()))), 
	  ((TH1D*)(ttbar->Get(inputhisto.data()))), 
	  ((TH1D*)(ww->Get(inputhisto.data()))), 
	  ((TH1D*)(wz->Get(inputhisto.data()))), 
	  ((TH1D*)(zz->Get(inputhisto.data()))), 
	  ((TH1D*)(data->Get(inputhisto.data()))),min,max
	  );

  
  


  gSystem->ProcessEvents();
  TImage *img1 = TImage::Create();
  img1->FromPad(c);
  img1->WriteImage(outputhisto.data());
  delete c;
  delete img1;


  //-------------------------------------------//




}



void myPlot(TH1D* h_dy70, TH1D* h_dy100, TH1D* h_ttbar, TH1D* h_ww, TH1D* h_wz, TH1D* h_zz, TH1D* h_data){

    

  h_dy70->SetFillColor(kCyan-4);
  h_dy70->SetLineColor(kBlack);

  h_dy100->SetFillColor(kAzure+9);
  h_dy100->SetLineColor(kBlack);

  h_ttbar->SetFillColor(kOrange+8);
  h_ttbar->SetLineColor(kBlack);

  h_ww->SetFillColor(kViolet+1);
  h_ww->SetLineColor(kBlack);

  h_wz->SetFillColor(kViolet+2);
  h_wz->SetLineColor(kBlack);

  h_zz->SetFillColor(kViolet+3);
  h_zz->SetLineColor(kBlack);

  THStack *h_stack = new THStack("h_stack", "");
  h_stack->Add(h_zz);
  h_stack->Add(h_wz);
  h_stack->Add(h_ww);
  h_stack->Add(h_ttbar);
  h_stack->Add(h_dy70);
  h_stack->Add(h_dy100);

  //h_stack->GetXaxis()->SetLabelOffset(0.1);//->SetLabelSize(0);
 
  h_data->SetLineColor(1);
  h_data->SetMarkerStyle(8);
  h_data->SetMarkerSize(1);
  h_data->SetLabelSize(0);

  
  
  h_data->Draw("e1"); 
  h_stack->Draw("histesame");
  h_data->Draw("e1same");


  h_data->Clear();
  h_stack->Clear();
  h_dy70->Clear();
  h_dy100->Clear();
  h_ttbar->Clear();
  h_ww->Clear();
  h_wz->Clear();
  h_zz->Clear();

  TLegend *leg = new TLegend(0.63, 0.75, 0.95, 0.90);
  leg->SetNColumns(2);
  leg->SetFillStyle(0);
  //leg->SetFillColor(0);
  //leg->SetBorderSize(0);
  leg->AddEntry(h_zz,"ZZ_pythia_filtered", "f"); 
  leg->AddEntry(h_wz,"WZ_pythia_filtered", "f"); 
  leg->AddEntry(h_ww,"WW_pythia_filtered", "f"); 
  leg->AddEntry(h_ttbar,"TTTo2L2Nu2B", "f"); 
  leg->AddEntry(h_dy100,"DYJetsToLL_PtZ-100", "f"); 
  leg->AddEntry(h_dy70, "DYJetsToLL_PtZ-70To100", "f"); 
  leg->AddEntry(h_data, "Data", "lp");
  leg->Draw();



}

void myRatio(TH1D* h_dy70, TH1D* h_dy100, TH1D* h_ttbar, TH1D* h_ww, TH1D* h_wz, TH1D* h_zz, TH1D* h_data, Double_t min , Double_t max){


  h_dy70->SetFillColor(kCyan-4);
  h_dy70->SetLineColor(kBlack);


  h_dy100->SetFillColor(kAzure+9);
  h_dy100->SetLineColor(kBlack);


  h_ttbar->SetFillColor(kOrange+8);
  h_ttbar->SetLineColor(kBlack);


  h_ww->SetFillColor(kViolet+1);
  h_ww->SetLineColor(kBlack);


  h_wz->SetFillColor(kViolet+2);
  h_wz->SetLineColor(kBlack);


  h_zz->SetFillColor(kViolet+3);
  h_zz->SetLineColor(kBlack);







  TH1D* h_bkg = (TH1D*)h_dy100->Clone("h_bkg");
  h_bkg->Reset();
  h_bkg->Sumw2();
  h_bkg->Add(h_dy70);
  h_bkg->Add(h_dy100);
  h_bkg->Add(h_ttbar);
  h_bkg->Add(h_ww);
  h_bkg->Add(h_wz);
  h_bkg->Add(h_zz);


  TH1D* h_ratio = (TH1D*)h_dy100->Clone("h_ratio");
  h_ratio->Reset();
  h_ratio->SetTitle("");
  //h_ratio->Sumw2();


  Int_t nbin=h_ratio->GetNbinsX();
  Double_t ratio[nbin];
  Double_t error[nbin];
  Double_t numer_nbincontent[nbin];
  Double_t denom_nbincontent[nbin];
  Double_t numer_binerror[nbin];
  Double_t denom_binerror[nbin];
  

  for(Int_t i=1; i<=nbin; i++){


    numer_nbincontent[i] = h_data->GetBinContent(i);
    denom_nbincontent[i] = h_bkg->GetBinContent(i);
    numer_binerror[i] = h_data->GetBinError(i);
    denom_binerror[i] = h_bkg->GetBinError(i);


    if(denom_nbincontent[i]<=0 || numer_nbincontent[i]<=0) continue;
    if(denom_binerror[i]<=0 || numer_binerror[i]<=0) continue;


    ratio[i] = numer_nbincontent[i]/denom_nbincontent[i];
    error[i] = (ratio[i])*sqrt(pow(numer_binerror[i]/numer_nbincontent[i],2)+pow(denom_binerror[i]/denom_nbincontent[i],2));

    h_ratio->SetBinContent(i,ratio[i]);
    h_ratio->SetBinError(i,error[i]);


    cout<<"MC_CenterValue["<<i<<"]:"<<(h_data->GetBinContent(i))<<"  MC_Error["<<i<<"]:"<<numer_binerror[i]<<endl;


  }
  
  //h_ratio->SetLineColor(1);
  h_ratio->SetMarkerStyle(8);
  h_ratio->SetMarkerSize(1);
  
  h_ratio->GetXaxis()->SetRangeUser(min,max);
  h_ratio->GetYaxis()->SetRangeUser(-1,3);
  //h_ratio->SetYTitle("data/MC");
  h_ratio->GetYaxis()->SetTitle("data/MC");
  h_ratio->GetXaxis()->SetTitle(h_dy70->GetXaxis()->GetTitle());
  h_ratio->GetYaxis()->SetTitleOffset(0.45);
  h_ratio->GetXaxis()->SetLabelSize(0.1);
  h_ratio->GetXaxis()->SetLabelOffset(0.005);
  h_ratio->GetXaxis()->SetTitleSize(0.125);
  h_ratio->GetXaxis()->SetTitleOffset(0.8);
  h_ratio->GetYaxis()->SetLabelSize(0.1);
  h_ratio->GetYaxis()->SetTitleSize(0.1);
  h_ratio->Draw();


  TLine* l2 = new TLine(min,1.,max,1.);
  l2->SetLineColor(2);
  //l2->SetLineStyle(3);
  l2->Draw("same");


}


