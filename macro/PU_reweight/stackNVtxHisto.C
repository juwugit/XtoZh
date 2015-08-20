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
const Int_t totalNEvent4 = 9959752;
const Int_t totalNEvent5 = 9910267;
const Int_t totalNEvent6 = 9769891;

const Double_t crossSection1 = 63.5;
const Double_t crossSection2 = 39.4;
const Double_t crossSection3 = 25.8;
const Double_t crossSection4 = 56.0;
const Double_t crossSection5 = 22.4;
const Double_t crossSection6 = 7.6;


// scale = fb^-1 / luminosity

Double_t data_lumi = 19671.225; // El: 19712.225 ; Mu: 19671.225

Double_t scale1 = data_lumi / (totalNEvent1 / crossSection1); // DYJetsToLL_PtZ-70To100
Double_t scale2 = data_lumi / (totalNEvent2 / crossSection2); // DYJetsToLL_PtZ100
Double_t scale3 = data_lumi / (totalNEvent3 / crossSection3); // TTbar
Double_t scale4 = data_lumi / (totalNEvent4 / crossSection4); // WW
Double_t scale5 = data_lumi / (totalNEvent5 / crossSection5); // WZ
Double_t scale6 = data_lumi / (totalNEvent6 / crossSection6); // ZZ


void myPlot(TH1D*, TH1D*, TH1D*, TH1D*, TH1D*, TH1D*, TH1D*);


void stackNVtxHisto(){


  TFile *dy70  = TFile::Open("rootfile/DY70To100_Mu.root");
  TFile *dy100 = TFile::Open("rootfile/DY100_Mu.root");
  TFile *ttbar = TFile::Open("rootfile/TTbar_Mu.root");
  TFile *ww    = TFile::Open("rootfile/WW_Mu.root");
  TFile *wz    = TFile::Open("rootfile/WZ_Mu.root");
  TFile *zz    = TFile::Open("rootfile/ZZ_Mu.root");
  TFile *data  = TFile::Open("rootfile/data_Mu.root");


  gStyle->SetOptStat(0);
  gStyle->SetPadGridY(kTRUE);
  gStyle->SetPadGridX(kTRUE);



  TCanvas* c1 = new TCanvas("c1", "", 0, 0, 1500, 750);

  c1->Divide(2,2);

  //-------------------------------------------//

  c1->cd(1);
  myPlot( ((TH1D*)(dy70->Get("h_nVtx"))), 
	  ((TH1D*)(dy100->Get("h_nVtx"))), 
	  ((TH1D*)(ttbar->Get("h_nVtx"))), 
	  ((TH1D*)(ww->Get("h_nVtx"))), 
	  ((TH1D*)(wz->Get("h_nVtx"))), 
	  ((TH1D*)(zz->Get("h_nVtx"))), 
	  ((TH1D*)(data->Get("h_nVtx")))
	  );

  //-------------------------------------------//
  
  c1->cd(2);
  myPlot( ((TH1D*)(dy70->Get("h_nVtx_central"))), 
	  ((TH1D*)(dy100->Get("h_nVtx_central"))), 
	  ((TH1D*)(ttbar->Get("h_nVtx_central"))), 
	  ((TH1D*)(ww->Get("h_nVtx_central"))), 
	  ((TH1D*)(wz->Get("h_nVtx_central"))), 
	  ((TH1D*)(zz->Get("h_nVtx_central"))), 
	  ((TH1D*)(data->Get("h_nVtx")))
	  );

  //-------------------------------------------//

  c1->cd(3);
  myPlot( ((TH1D*)(dy70->Get("h_nVtx_down"))), 
	  ((TH1D*)(dy100->Get("h_nVtx_down"))), 
	  ((TH1D*)(ttbar->Get("h_nVtx_down"))), 
	  ((TH1D*)(ww->Get("h_nVtx_down"))), 
	  ((TH1D*)(wz->Get("h_nVtx_down"))), 
	  ((TH1D*)(zz->Get("h_nVtx_down"))), 
	  ((TH1D*)(data->Get("h_nVtx")))
	  );


  //------------------------------------------//

  c1->cd(4);
  myPlot( ((TH1D*)(dy70->Get("h_nVtx_up"))), 
	  ((TH1D*)(dy100->Get("h_nVtx_up"))), 
	  ((TH1D*)(ttbar->Get("h_nVtx_up"))), 
	  ((TH1D*)(ww->Get("h_nVtx_up"))), 
	  ((TH1D*)(wz->Get("h_nVtx_up"))), 
	  ((TH1D*)(zz->Get("h_nVtx_up"))), 
	  ((TH1D*)(data->Get("h_nVtx")))
	  );




  gSystem->ProcessEvents();
  TImage *img1 = TImage::Create();
  img1->FromPad(c1);
  img1->WriteImage("h_nVtx_Mu.png");
  delete c1;
  delete img1;


  //-------------------------------------------//




}



void myPlot(TH1D* h_dy70, TH1D* h_dy100, TH1D* h_ttbar, TH1D* h_ww, TH1D* h_wz, TH1D* h_zz, TH1D* h_data){

  
  h_dy70->Scale(scale1);
  h_dy70->SetFillColor(kCyan-4);
  h_dy70->SetLineColor(kBlack);

  h_dy100->Scale(scale2);
  h_dy100->SetFillColor(kAzure+9);
  h_dy100->SetLineColor(kBlack);

  h_ttbar->Scale(scale3);
  h_ttbar->SetFillColor(kOrange+8);
  h_ttbar->SetLineColor(kBlack);

  h_ww->Scale(scale4);
  h_ww->SetFillColor(kViolet+1);
  h_ww->SetLineColor(kBlack);

  h_wz->Scale(scale5);
  h_wz->SetFillColor(kViolet+2);
  h_wz->SetLineColor(kBlack);

  h_zz->Scale(scale6);
  h_zz->SetFillColor(kViolet+3);
  h_zz->SetLineColor(kBlack);



  THStack *h_stack = new THStack("h_stack", "");
  h_stack->Add(h_zz);
  h_stack->Add(h_wz);
  h_stack->Add(h_ww);
  h_stack->Add(h_ttbar);
  h_stack->Add(h_dy70);
  h_stack->Add(h_dy100);


 
  h_data->SetLineColor(1);
  h_data->SetMarkerStyle(8);
  h_data->SetMarkerSize(1);
  h_data->SetLabelSize(0);


  Float_t dymaxbin = h_dy100->GetBinContent(h_dy100->GetMaximumBin()) + h_dy70->GetBinContent(h_dy70->GetMaximumBin());
  Float_t datamaxbin = h_data->GetBinContent(h_data->GetMaximumBin());

  cout<<"dymaxbin:"<<dymaxbin<<" datamaxbin:"<<datamaxbin<<endl;

  if( dymaxbin > datamaxbin ){


    h_stack->Draw("histe");
    h_stack->GetXaxis()->SetTitle( h_dy100->GetTitle() );
    h_data->Draw("e1same");
    
    cout<< "dymaxbin is bigger" <<endl;

  }
  
  if( dymaxbin < datamaxbin ){
    
    h_data->GetXaxis()->SetTitle( h_dy100->GetTitle() );
    h_data->Draw("e1"); 
    h_stack->Draw("histesame");
    h_data->Draw("e1same");
    
    cout<< "datamaxbin is bigger" <<endl;

  }


  h_data->Clear();
  h_stack->Clear();
  h_dy70->Clear();
  h_dy100->Clear();
  h_ttbar->Clear();
  h_ww->Clear();
  h_wz->Clear();
  h_zz->Clear();


  TLegend *leg = new TLegend(0.73, 0.68, 0.98, 0.98);

  leg->SetFillStyle(1001);
  leg->SetFillColor(10);
  leg->SetBorderSize(1);
  leg->AddEntry(h_zz,"ZZ_pythia_filtered", "f"); 
  leg->AddEntry(h_wz,"WZ_pythia_filtered", "f"); 
  leg->AddEntry(h_ww,"WW_pythia_filtered", "f"); 
  leg->AddEntry(h_ttbar,"TTTo2L2Nu2B", "f"); 
  leg->AddEntry(h_dy100,"DYJetsToLL_PtZ-100", "f"); 
  leg->AddEntry(h_dy70, "DYJetsToLL_PtZ-70To100", "f"); 
  leg->AddEntry(h_data, "Data", "lp");
  leg->Draw();



}


