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

// scale = fb^-1 / luminosity

Double_t scale1 = 19712.225 / (totalNEvent1 / crossSection1); // DYJetsToLL_PtZ-70To100
Double_t scale2 = 19712.225 / (totalNEvent2 / crossSection2); // DYJetsToLL_PtZ100
Double_t scale3 = 19712.225 / (totalNEvent3 / crossSection3); // TTbar

// El: 19712.225 ; Mu: 19671.225

void myPlot(TH1D*, TH1D*, TH1D*, TH1D*);


void stackCSVhisto(){

  cout<<"scale1:"<<scale1<<endl;
  cout<<"scale2:"<<scale2<<endl;
  cout<<"scale3:"<<scale3<<endl;


  TFile *dy70  = TFile::Open("rootfile/DY70To100_El.root");
  TFile *dy100 = TFile::Open("rootfile/DY100_El.root");
  TFile *ttbar = TFile::Open("rootfile/TTbar_El.root");
  TFile *data  = TFile::Open("rootfile/data_El.root");
  //TFile *signal= TFile::Open("rootfile/signal_M1000_El.root");


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
	  ((TH1D*)(data->Get("h_sbCA8jetCSV")))
	  /*((TH1D*)(signal->Get("h_sbCA8jetCSV")))*/ 
	  );

  //-------------------------------------------//
  
  c1->cd(2);
  myPlot( ((TH1D*)(dy70->Get("h_sigCA8jetCSV"))), 
	  ((TH1D*)(dy100->Get("h_sigCA8jetCSV"))), 
	  ((TH1D*)(ttbar->Get("h_sigCA8jetCSV"))), 
	  ((TH1D*)(data->Get("h_sigCA8jetCSV")))
	  /*((TH1D*)(signal->Get("h_sbCA8jetCSV")))*/ 
	  );

  //-------------------------------------------//

  c1->cd(3);
  myPlot( ((TH1D*)(dy70->Get("h_sbSubjetCSV"))), 
	  ((TH1D*)(dy100->Get("h_sbSubjetCSV"))), 
	  ((TH1D*)(ttbar->Get("h_sbSubjetCSV"))), 
	  ((TH1D*)(data->Get("h_sbSubjetCSV")))
	  /*((TH1D*)(signal->Get("h_sbCA8jetCSV")))*/ 
	  );


  //------------------------------------------//

  c1->cd(4);
  myPlot( ((TH1D*)(dy70->Get("h_sigSubjetCSV"))), 
	  ((TH1D*)(dy100->Get("h_sigSubjetCSV"))), 
	  ((TH1D*)(ttbar->Get("h_sigSubjetCSV"))), 
	  ((TH1D*)(data->Get("h_sigSubjetCSV")))
	  /*((TH1D*)(signal->Get("h_sbCA8jetCSV")))*/ 
	  );





  gSystem->ProcessEvents();
  TImage *img1 = TImage::Create();
  img1->FromPad(c1);
  img1->WriteImage("h_jetCSV_El.png");
  delete c1;
  delete img1;


  //-------------------------------------------//




}



void myPlot(TH1D* h_dy70, TH1D* h_dy100, TH1D* h_ttbar, TH1D* h_data /*, TH1D* h_signal*/){

  
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
  h_stack->Add(h_ttbar);
  h_stack->Add(h_dy70);
  h_stack->Add(h_dy100);


 
  h_data->SetLineColor(1);
  h_data->SetMarkerStyle(8);
  h_data->SetMarkerSize(1);
  h_data->SetLabelSize(0);


  Float_t dymaxbin =  h_dy100->GetBinContent(h_dy100->GetMaximumBin());
  Float_t datamaxbin =  h_data->GetBinContent(h_data->GetMaximumBin());

  if( dymaxbin > datamaxbin ){


    h_stack->Draw("histe");
    h_stack->GetXaxis()->SetTitle( h_dy100->GetTitle() );
    h_data->Draw("e1same");
    
  }
  
  else if( dymaxbin < datamaxbin ){
    
    h_data->GetXaxis()->SetTitle( h_data->GetTitle() );
    h_data->Draw("e1"); 
    h_stack->Draw("histesame");
    h_data->Draw("e1same");
    

  }


  h_data->Clear();
  h_stack->Clear();
  h_dy70->Clear();
  h_dy100->Clear();
  h_ttbar->Clear();


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


