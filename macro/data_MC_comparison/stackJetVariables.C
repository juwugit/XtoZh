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

const Int_t totalNEvent1 = 11765438;
const Int_t totalNEvent2 = 12511326;
const Int_t totalNEvent3 = 10783509;
const Double_t crossSection1 = 63.5;
const Double_t crossSection2 = 39.4;
const Double_t crossSection3 = 25.8;

// scale = ? fb^-1 / luminosity

Double_t scale1 = 876.225 / (totalNEvent1 / crossSection1); // DYJetsToLL_PtZ-70To100
Double_t scale2 = 876.225 / (totalNEvent2 / crossSection2); // DYJetsToLL_PtZ100
Double_t scale3 = 876.225 / (totalNEvent3 / crossSection3); // TTbar


void myPlot(TH1D*, TH1D*, TH1D*, TH1D* , Double_t , Double_t);
void myRatio(TH1D*, TH1D*, TH1D*, TH1D* , Double_t , Double_t );


void stackJetVariables(){

  cout<<"scale1:"<<scale1<<endl;
  cout<<"scale2:"<<scale2<<endl;
  cout<<"scale3:"<<scale3<<endl;


  TFile *f1e = TFile::Open("rootfile/delpanj_v2_DYJetsToLL_PtZ-70To100_ee.root");
  TFile *f2e = TFile::Open("rootfile/delpanj_v2_DYJetsToLL_PtZ-100_ee.root");
  TFile *f3e = TFile::Open("rootfile/delpanj_v2_TTTo2L2Nu2B_ee.root");
  TFile *f1m = TFile::Open("rootfile/delpanj_v2_DYJetsToLL_PtZ-70To100_mm.root");
  TFile *f2m = TFile::Open("rootfile/delpanj_v2_DYJetsToLL_PtZ-100_mm.root");
  TFile *f3m = TFile::Open("rootfile/delpanj_v2_TTTo2L2Nu2B_mm.root");
  TFile *f4 = TFile::Open("rootfile/delpanj_v2_data_DoubleEl_A.root");
  TFile *f5 = TFile::Open("rootfile/delpanj_v2_data_DoubleMu_A.root");




  gStyle->SetOptStat(0);
  gStyle->SetPadGridY(kTRUE);
  gStyle->SetPadGridX(kTRUE);



  TCanvas* c1 = new TCanvas("c1", "", 0, 0, 1500, 750);

  c1->Divide(2,2,0,0);

  //-------------------------------------------//

  c1->cd(1);
  myPlot( ((TH1D*)(f1e->Get("h_mLL"))), 
	  ((TH1D*)(f2e->Get("h_mLL"))), 
	  ((TH1D*)(f3e->Get("h_mLL"))), 
	  ((TH1D*)(f4->Get("h_mLL"))),
	  60,120);

  gPad->SetRightMargin(0.02);

  //-------------------------------------------//
  
  c1->cd(2);
  myPlot( ((TH1D*)(f1m->Get("h_mLL"))),
          ((TH1D*)(f2m->Get("h_mLL"))),
          ((TH1D*)(f3m->Get("h_mLL"))),
          ((TH1D*)(f5->Get("h_mLL"))),
          60,120);
  
  gPad->SetRightMargin(0.02);
  gPad->SetLeftMargin(0.07);

  
  //-------------------------------------------//

  c1->cd(3);
  myRatio( ((TH1D*)(f1e->Get("h_mLL"))),
	   ((TH1D*)(f2e->Get("h_mLL"))),
	   ((TH1D*)(f3e->Get("h_mLL"))),
	   ((TH1D*)(f4->Get("h_mLL"))),
	   60,120);

  
  gPad->SetTickx();
  gPad->SetRightMargin(0.02);



  //-------------------------------------------//
  
  c1->cd(4);
  myRatio( ((TH1D*)(f1m->Get("h_mLL"))),
           ((TH1D*)(f2m->Get("h_mLL"))),
           ((TH1D*)(f3m->Get("h_mLL"))),
           ((TH1D*)(f5->Get("h_mLL"))),
	   60,120);
  
  gPad->SetTickx();
  gPad->SetRightMargin(0.02);
  gPad->SetLeftMargin(0.07);


  // c1->Print("mLL.gif");
  gSystem->ProcessEvents();
  TImage *img1 = TImage::Create();
  img1->FromPad(c1);
  img1->WriteImage("h_mLL.png");
  delete c1;
  delete img1;


  //-------------------------------------------//





  TCanvas* c2 = new TCanvas("c2", "", 0, 0, 1500, 750);

  c2->Divide(2,2,0,0);


  c2->cd(1);
  myPlot( ((TH1D*)(f1e->Get("h_CA8jetTau21"))),
          ((TH1D*)(f2e->Get("h_CA8jetTau21"))),
          ((TH1D*)(f3e->Get("h_CA8jetTau21"))),
          ((TH1D*)(f4->Get("h_CA8jetTau21"))),
          0,1);

  gPad->SetRightMargin(0.02);


  //-------------------------------------------//

  c2->cd(2);
  myPlot( ((TH1D*)(f1m->Get("h_CA8jetTau21"))),
          ((TH1D*)(f2m->Get("h_CA8jetTau21"))),
          ((TH1D*)(f3m->Get("h_CA8jetTau21"))),
          ((TH1D*)(f5->Get("h_CA8jetTau21"))),
          0,1);

  gPad->SetRightMargin(0.02);
  gPad->SetLeftMargin(0.07);

  //-------------------------------------------//
  
  c2->cd(3);
  myRatio( ((TH1D*)(f1e->Get("h_CA8jetTau21"))),
           ((TH1D*)(f2e->Get("h_CA8jetTau21"))),
           ((TH1D*)(f3e->Get("h_CA8jetTau21"))),
           ((TH1D*)(f4->Get("h_CA8jetTau21"))),
           0,1);


  gPad->SetTickx();
  gPad->SetRightMargin(0.02);

  //--------------------------------------------//

  c2->cd(4);
  myRatio( ((TH1D*)(f1m->Get("h_CA8jetTau21"))),
           ((TH1D*)(f2m->Get("h_CA8jetTau21"))),
           ((TH1D*)(f3m->Get("h_CA8jetTau21"))),
           ((TH1D*)(f5->Get("h_CA8jetTau21"))),
           0,1);

  gPad->SetTickx();
  gPad->SetRightMargin(0.02);
  gPad->SetLeftMargin(0.07);



  //c1->Print("CA8jetTau21.gif");
  gSystem->ProcessEvents();
  TImage *img2 = TImage::Create();
  img2->FromPad(c2);
  img2->WriteImage("h_CA8jetTau21.png");
  delete c2;
  delete img2;


}



void myPlot(TH1D* h_dy70, TH1D* h_dy100, TH1D* h_ttbar, TH1D* h_data , Double_t min , Double_t max){

  //h_data->Sumw2();
  
  h_dy70->Scale(scale1);
  h_dy70->SetFillColor(kCyan-4);
  h_dy70->SetLineColor(kBlack);

  h_dy100->Scale(scale2);
  h_dy100->SetFillColor(kAzure+9);
  h_dy100->SetLineColor(kBlack);

  h_ttbar->Scale(scale3);
  h_ttbar->SetFillColor(kOrange+8);
  h_ttbar->SetLineColor(kBlack);



  THStack *h_stack = new THStack("h_stack", "");
  h_stack->Add(h_dy70);
  h_stack->Add(h_dy100);
  h_stack->Add(h_ttbar);


  h_data->SetLineColor(1);
  h_data->SetMarkerStyle(8);
  h_data->SetMarkerSize(1);

  Double_t ymin = -0.05*(h_data->GetMaximum());

  h_data->SetMinimum(ymin);
  h_data->GetXaxis()->SetRangeUser(min,max);
  h_data->SetLabelSize(0);
  h_data->SetXTitle("");


  h_data->Draw("e1"); 
  h_stack->Draw("histsame");
  h_data->Draw("e1same");



  TLegend *leg = new TLegend(0.73, 0.78, 0.98, 0.98);

  leg->SetFillStyle(1001);
  leg->SetFillColor(10);
  leg->SetBorderSize(1);
  leg->AddEntry(h_ttbar,"TTTo2L2Nu2B.root", "f"); 
  leg->AddEntry(h_dy100,"DYJetsToLL_PtZ-100", "f"); 
  leg->AddEntry(h_dy70, "DYJetsToLL_PtZ-70To100", "f"); 
  leg->AddEntry(h_data, "Data", "lp");
  leg->Draw();

}




void myRatio(TH1D* h_dy70, TH1D* h_dy100, TH1D* h_ttbar, TH1D* h_data , Double_t min , Double_t max){


  
  TH1D* h_bkg = (TH1D*)h_dy100->Clone("h_bkg");
  h_bkg->Reset();
  //h_bkg->Sumw2();
  h_bkg->Add(h_dy70,1);
  h_bkg->Add(h_dy100,1);
  h_bkg->Add(h_ttbar,1);



  TH1D* h_ratio = (TH1D*)h_dy100->Clone("h_ratio");
  h_ratio->Reset();
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


  }
  
 
  //h_ratio->SetLineColor(1);
  h_ratio->SetMarkerStyle(8);
  h_ratio->SetMarkerSize(1);

  h_ratio->GetXaxis()->SetRangeUser(min,max);
  h_ratio->GetYaxis()->SetRangeUser(0.5,1.55);
  h_ratio->SetYTitle("data/MC");
  h_ratio->Draw();


  TLine* l2 = new TLine(min,1.,max,1.);
  l2->SetLineColor(4);
  l2->SetLineStyle(3);
  l2->Draw("same");


}



