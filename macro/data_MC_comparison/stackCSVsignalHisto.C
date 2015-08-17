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


/*
const Int_t totalNEvent1 = 11765438;
const Int_t totalNEvent2 = 12511326;
const Int_t totalNEvent3 = 10783509;
const Int_t totalNEvent4 = 9959752;
const Int_t totalNEvent5 = 9910267;
const Int_t totalNEvent6 = 9769891;
//const Int_t totalNEvent7 = 19997;

const Double_t crossSection1 = 63.5;
const Double_t crossSection2 = 39.4;
const Double_t crossSection3 = 25.8;
const Double_t crossSection4 = 56.0;
const Double_t crossSection5 = 22.4;
const Double_t crossSection6 = 7.6;
//const Double_t crossSection7 = 0.003263;


// scale = fb^-1 / luminosity

Double_t data_lumi = 19671.225; // El: 19712.225 ; Mu: 19671.225

Double_t scale1 = data_lumi / (totalNEvent1 / crossSection1); // DYJetsToLL_PtZ-70To100
Double_t scale2 = data_lumi / (totalNEvent2 / crossSection2); // DYJetsToLL_PtZ100
Double_t scale3 = data_lumi / (totalNEvent3 / crossSection3); // TTbar
Double_t scale4 = data_lumi / (totalNEvent4 / crossSection4); // WW
Double_t scale5 = data_lumi / (totalNEvent5 / crossSection5); // WZ
Double_t scale6 = data_lumi / (totalNEvent6 / crossSection6); // ZZ
//Double_t scale7 = data_lumi / (totalNEvent7 / crossSection7); // signal

*/


void myPlot(TH1D*, TH1D*, TH1D*, TH1D*, TH1D*, TH1D*, TH1D*, TH1D*);


void stackCSVsignalHisto(){


  TFile *dy70  = TFile::Open("rootfile/DY70To100_El.root");
  TFile *dy100 = TFile::Open("rootfile/DY100_El.root");
  TFile *ttbar = TFile::Open("rootfile/TTbar_El.root");
  TFile *ww    = TFile::Open("rootfile/WW_El.root");
  TFile *wz    = TFile::Open("rootfile/WZ_El.root");
  TFile *zz    = TFile::Open("rootfile/ZZ_El.root");
  TFile *data  = TFile::Open("rootfile/data_El.root");
  TFile *SIG   = TFile::Open("rootfile/signal_M1500_El.root");


  gStyle->SetOptStat(0);
  gStyle->SetPadGridY(kTRUE);
  gStyle->SetPadGridX(kTRUE);



  TCanvas* c1 = new TCanvas("c1", "", 0, 0, 1500, 750);


  c1->Divide(2,2);

  //-------------------------------------------//

  c1->cd(1);
  myPlot( ((TH1D*)(dy70->Get("h_sbCA8jetCSV"))), 
	  ((TH1D*)(dy100->Get("h_sbCA8jetCSV"))), 
	  ((TH1D*)(ttbar->Get("h_sbCA8jetCSV"))), 
	  ((TH1D*)(ww->Get("h_sbCA8jetCSV"))), 
	  ((TH1D*)(wz->Get("h_sbCA8jetCSV"))), 
	  ((TH1D*)(zz->Get("h_sbCA8jetCSV"))), 
	  ((TH1D*)(data->Get("h_sbCA8jetCSV"))),
	  ((TH1D*)(SIG->Get("h_sbCA8jetCSV")))
	  );

  //-------------------------------------------//
  
  c1->cd(2);
  myPlot( ((TH1D*)(dy70->Get("h_sigCA8jetCSV"))), 
	  ((TH1D*)(dy100->Get("h_sigCA8jetCSV"))), 
	  ((TH1D*)(ttbar->Get("h_sigCA8jetCSV"))), 
	  ((TH1D*)(ww->Get("h_sigCA8jetCSV"))), 
	  ((TH1D*)(wz->Get("h_sigCA8jetCSV"))), 
	  ((TH1D*)(zz->Get("h_sigCA8jetCSV"))), 
	  ((TH1D*)(data->Get("h_sigCA8jetCSV"))),
	  ((TH1D*)(SIG->Get("h_sbCA8jetCSV")))
	  );

  //-------------------------------------------//

  c1->cd(3);
  myPlot( ((TH1D*)(dy70->Get("h_sbSubjetCSV"))), 
	  ((TH1D*)(dy100->Get("h_sbSubjetCSV"))), 
	  ((TH1D*)(ttbar->Get("h_sbSubjetCSV"))), 
	  ((TH1D*)(ww->Get("h_sbSubjetCSV"))), 
	  ((TH1D*)(wz->Get("h_sbSubjetCSV"))), 
	  ((TH1D*)(zz->Get("h_sbSubjetCSV"))), 
	  ((TH1D*)(data->Get("h_sbSubjetCSV"))),
	  ((TH1D*)(SIG->Get("h_sbCA8jetCSV")))
	  );


  //------------------------------------------//

  c1->cd(4);
  myPlot( ((TH1D*)(dy70->Get("h_sigSubjetCSV"))), 
	  ((TH1D*)(dy100->Get("h_sigSubjetCSV"))), 
	  ((TH1D*)(ttbar->Get("h_sigSubjetCSV"))), 
	  ((TH1D*)(ww->Get("h_sigSubjetCSV"))), 
	  ((TH1D*)(wz->Get("h_sigSubjetCSV"))), 
	  ((TH1D*)(zz->Get("h_sigSubjetCSV"))), 
	  ((TH1D*)(data->Get("h_sigSubjetCSV"))),
	  ((TH1D*)(SIG->Get("h_sbCA8jetCSV")))
	  );





  gSystem->ProcessEvents();
  TImage *img1 = TImage::Create();
  img1->FromPad(c1);
  img1->WriteImage("h_jetCSVshape1500_El.png");
  delete c1;
  delete img1;


  //-------------------------------------------//




}



void myPlot(TH1D* h_dy70, TH1D* h_dy100, TH1D* h_ttbar, TH1D* h_ww, TH1D* h_wz, TH1D* h_zz, TH1D* h_data, TH1D* h_sig){

  
  /*
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
  */


  TH1D* h_stack = new TH1D("h_stack","",20,0,1);
  h_stack->Add(h_zz);
  h_stack->Add(h_wz);
  h_stack->Add(h_ww);
  h_stack->Add(h_ttbar);
  h_stack->Add(h_dy70);
  h_stack->Add(h_dy100);

  h_stack->Scale(1/h_stack->Integral());
  h_stack->SetFillColor(kCyan-4);
  h_stack->SetLineColor(kBlack);


  h_data->Scale(1/h_data->Integral());
  h_data->SetLineColor(1);
  h_data->SetMarkerStyle(8);
  h_data->SetMarkerSize(1);
  h_data->SetLabelSize(0);

  //h_sig->Scale(scale7);
  h_sig->Scale(1/h_sig->Integral());
  h_sig->SetLineColor(kRed);
  h_sig->SetMarkerColor(kRed);
  h_sig->SetMarkerStyle(8);
  h_sig->SetMarkerSize(1);
  h_sig->SetLabelSize(0);



  Float_t dymaxbin =  h_stack->GetBinContent(h_stack->GetMaximumBin());
  Float_t sigmaxbin = h_sig->GetBinContent(h_sig->GetMaximumBin());

  if( dymaxbin > sigmaxbin ){

    h_stack->Draw("histe");
    h_stack->GetXaxis()->SetTitle( h_dy100->GetTitle() );
    h_data->Draw("e1same");
    h_sig->Draw("e1same");

    }
    
  else if( dymaxbin < sigmaxbin ){
    
    h_sig->GetXaxis()->SetTitle( h_data->GetTitle() );
    h_sig->Draw("e1"); 
    h_stack->Draw("histesame");
    h_data->Draw("e1same");
    h_sig->Draw("e1same");

  }
  





  h_data->Clear();
  h_stack->Clear();
  h_dy70->Clear();
  h_dy100->Clear();
  h_ttbar->Clear();
  h_ww->Clear();
  h_wz->Clear();
  h_zz->Clear();
  h_sig->Clear();


  TLegend *leg = new TLegend(0.73, 0.68, 0.98, 0.98);

  leg->SetFillStyle(1001);
  leg->SetFillColor(10);
  leg->SetBorderSize(1);
  /*
  leg->AddEntry(h_zz,"ZZ_pythia_filtered", "f"); 
  leg->AddEntry(h_wz,"WZ_pythia_filtered", "f"); 
  leg->AddEntry(h_ww,"WW_pythia_filtered", "f"); 
  leg->AddEntry(h_ttbar,"TTTo2L2Nu2B", "f"); 
  leg->AddEntry(h_dy100,"DYJetsToLL_PtZ-100", "f"); 
  leg->AddEntry(h_dy70, "DYJetsToLL_PtZ-70To100", "f");
  */
  leg->AddEntry(h_stack, "Background MC", "f");
  leg->AddEntry(h_data, "Data", "lp");
  leg->AddEntry(h_sig, "ZprimeToZhTollqq", "lp");
  leg->Draw();



}


