//root -q -b -l plot_ROC_btag.C++\(\"inputFile1\",\"inpuFile2\"\,\"Graph_name\"\)
#include <TLegend.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <TH1D.h>
#include <TRandom.h>
#include <TLorentzVector.h>
#include <TFile.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TH1F.h>
#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TROOT.h>
#include "TImage.h"
#include "TSystem.h"
#include "TStyle.h"

//TGraph* CSV(TH1*, TH1*, TH1* , TH1*);
TGraphErrors* ROC(TH1*, TH1*);
TGraphErrors* SIGN(TH1*, TH1*);
TGraphErrors* EFF(TH1*);

TGraphErrors* D_EFF(TH2*);
TGraphErrors* D_ROC(TH2*, TH2*);
TGraphErrors* D_SIGN(TH2*, TH2*);

TGraphErrors* ComEFF(TH2*, TH1* ,TH1*);
TGraphErrors* ComROC(TH2*, TH1*, TH1*,TH2*,TH1*,TH1*);
TGraphErrors* ComSIGN(TH2*, TH1*, TH1*,TH2*,TH1*,TH1*);


using namespace std;
void plot_ROC_btag(std::string inputFile1, std::string inputFile2, std::string Graph_name){


  
  TFile* SIG = new TFile(inputFile1.data());   
  TFile* BKD = new TFile(inputFile2.data()); 

  TH1F* h_sig_CA8jetCSV = (TH1F*)SIG->Get("h_CA8jetCSV");
  TH2F* h_sig_subjetCSV = (TH2F*)SIG->Get("h_CA8subjetCSV");
  TH1F* h_bkd_CA8jetCSV = (TH1F*)BKD->Get("h_CA8jetCSV");
  TH2F* h_bkd_subjetCSV = (TH2F*)BKD->Get("h_CA8subjetCSV");

  TH1F* h_sig_SubjetCSV = (TH1F*)SIG->Get("h_SubjetCSV");
  TH1F* h_bkd_SubjetCSV = (TH1F*)BKD->Get("h_SubjetCSV");
  TH1F* h_sig_COMjetCSV = (TH1F*)SIG->Get("h_COMjetCSV");
  TH1F* h_bkd_COMjetCSV = (TH1F*)BKD->Get("h_COMjetCSV");



  /*
  TH1F* h_sig_CA8jetCSVL = (TH1F*)SIG->Get("h_CA8jetCSVL");
  TH1F* h_sig_subjetCSVL = (TH1F*)SIG->Get("h_CA8subjetCSVL");
  TH1F* h_bkd_CA8jetCSVL = (TH1F*)BKD->Get("h_CA8jetCSVL");
  TH1F* h_bkd_subjetCSVL = (TH1F*)BKD->Get("h_CA8subjetCSVL");

  TH1F* h_sig_CA8jetCSVM = (TH1F*)SIG->Get("h_CA8jetCSVM");
  TH1F* h_sig_subjetCSVM = (TH1F*)SIG->Get("h_CA8subjetCSVM");
  TH1F* h_bkd_CA8jetCSVM = (TH1F*)BKD->Get("h_CA8jetCSVM");
  TH1F* h_bkd_subjetCSVM = (TH1F*)BKD->Get("h_CA8subjetCSVM");

  TH1F* h_sig_CA8jetCSVT = (TH1F*)SIG->Get("h_CA8jetCSVT");
  TH1F* h_sig_subjetCSVT = (TH1F*)SIG->Get("h_CA8subjetCSVT");
  TH1F* h_bkd_CA8jetCSVT = (TH1F*)BKD->Get("h_CA8jetCSVT");
  TH1F* h_bkd_subjetCSVT = (TH1F*)BKD->Get("h_CA8subjetCSVT");
  */


  //------------------------------------------------------------
  
  TGraphErrors* g1 = ROC(h_sig_CA8jetCSV, h_bkd_CA8jetCSV);

  g1->SetTitle("ROC");
  g1->GetYaxis()->SetTitle("Mis-tag rate");
  g1->GetYaxis()->SetTitleOffset(1.3);
  g1->SetLineColor(4);
  g1->SetMarkerStyle(20);
  g1->SetLineWidth(2);
  g1->GetXaxis()->SetTitle("Efficiency");
  g1->GetXaxis()->SetTitleOffset(1.3);
  g1->SetMarkerColor(4);

  //-----------------------------------------------------------

  TGraphErrors* g2 = D_ROC(h_sig_subjetCSV, h_bkd_subjetCSV);

  g2->SetTitle("ROC");
  g2->GetYaxis()->SetTitle("Mis-tag rate");
  g2->GetYaxis()->SetTitleOffset(1.3);
  g2->SetLineColor(2);
  g2->SetMarkerStyle(20);
  g2->SetLineWidth(2);
  g2->GetXaxis()->SetTitle("Efficiency");
  g2->GetXaxis()->SetTitleOffset(1.3);
  g2->SetMarkerColor(2);
  
  //------------------------------------------------------------
  
  TGraphErrors* g3 = SIGN(h_sig_CA8jetCSV, h_bkd_CA8jetCSV);
 
  g3->SetTitle("Significance");
  g3->GetYaxis()->SetTitle("Significance");
  g3->GetYaxis()->SetTitleOffset(1.3);
  g3->SetLineColor(4);
  g3->SetMarkerStyle(20);
  g3->SetLineWidth(2);
  g3->GetXaxis()->SetTitle("CSV work point");
  g3->GetXaxis()->SetTitleOffset(1.3);
  g3->SetMarkerColor(4);
  
  //------------------------------------------------------------

  TGraphErrors* g4 = D_SIGN(h_sig_subjetCSV, h_bkd_subjetCSV);
  
  g4->SetTitle("Significance");
  g4->GetYaxis()->SetTitle("Significance");
  g4->GetYaxis()->SetTitleOffset(1.3);
  g4->SetLineColor(2);
  g4->SetMarkerStyle(20);
  g4->SetLineWidth(2);
  g4->GetXaxis()->SetTitle("CSV work point");
  g4->GetXaxis()->SetTitleOffset(1.3);
  g4->SetMarkerColor(2);
  
  //-----------------------------------------------------------

  TGraphErrors* g5 = EFF(h_sig_CA8jetCSV);

  g5->SetLineColor(4);
  g5->SetMarkerStyle(20);
  g5->SetLineWidth(2);
  g5->SetMarkerColor(4);
  g5->SetTitle("");
  g5->GetYaxis()->SetTitle("Efficiency");
  g5->GetYaxis()->SetTitleOffset(1.3);
  g5->GetXaxis()->SetTitle("CSV work point");
  g5->GetXaxis()->SetTitleOffset(1.3);


  TGraphErrors* g6 = EFF(h_bkd_CA8jetCSV);

  g6->SetMarkerStyle(20);
  g6->SetLineWidth(2);
  g6->SetTitle("CA8jetCSV eff: SIG vs BKD");
  g6->GetYaxis()->SetTitle("Efficiency");
  g6->GetYaxis()->SetTitleOffset(1.3);
  g6->GetXaxis()->SetTitle("CSV work point");
  g6->GetXaxis()->SetTitleOffset(1.3);
  
  //-----------------------------------------------------------


  TGraphErrors* g7 = D_EFF(h_sig_subjetCSV);

  g7->SetLineColor(2);
  g7->SetMarkerStyle(20);
  g7->SetLineWidth(2);
  g7->SetMarkerColor(2);
  g7->SetTitle("");
  g7->GetYaxis()->SetTitle("Efficiency");
  g7->GetYaxis()->SetTitleOffset(1.3);
  g7->GetXaxis()->SetTitle("CSV work point");
  g7->GetXaxis()->SetTitleOffset(1.3);


  TGraphErrors* g8 = D_EFF(h_bkd_subjetCSV);

  g8->SetMarkerStyle(20);
  g8->SetLineWidth(2);
  g8->SetTitle("SubjetCSV eff: SIG vs BKD");
  g8->GetYaxis()->SetTitle("Efficiency");
  g8->GetYaxis()->SetTitleOffset(1.3);
  g8->GetXaxis()->SetTitle("CSV work point");
  g8->GetXaxis()->SetTitleOffset(1.3);

  //-----------------------------------------------------------

  TGraphErrors* g9 = ComEFF(h_sig_subjetCSV,h_sig_COMjetCSV,h_sig_CA8jetCSV);

  g9->SetLineColor(kMagenta+2);
  g9->SetMarkerStyle(20);
  g9->SetLineWidth(2);
  g9->SetMarkerColor(kMagenta+2);
  g9->SetTitle("Combined CSV eff: SIG vs BKD");
  g9->GetYaxis()->SetTitle("Efficiency");
  g9->GetYaxis()->SetTitleOffset(1.3);
  g9->GetXaxis()->SetTitle("CSV work point");
  g9->GetXaxis()->SetTitleOffset(1.3);


  TGraphErrors* g10 = ComEFF(h_bkd_subjetCSV,h_bkd_COMjetCSV,h_bkd_CA8jetCSV);

  g10->SetMarkerStyle(20);
  g10->SetLineWidth(2);
  g10->SetTitle("Combined CSV eff: SIG vs BKD");
  g10->GetYaxis()->SetTitle("Efficiency");
  g10->GetYaxis()->SetTitleOffset(1.3);
  g10->GetXaxis()->SetTitle("CSV work point");
  g10->GetXaxis()->SetTitleOffset(1.3);

  //------------------------------------------------------------

  TGraphErrors* g11 = ComROC(h_sig_subjetCSV,h_sig_COMjetCSV,h_sig_CA8jetCSV,h_bkd_subjetCSV,h_bkd_COMjetCSV,h_bkd_CA8jetCSV);

  g11->SetTitle("ROC");
  g11->GetYaxis()->SetTitle("Mis-tag rate");
  g11->GetYaxis()->SetTitleOffset(1.3);
  g11->SetLineColor(kMagenta+2);
  g11->SetMarkerStyle(20);
  g11->SetLineWidth(2);
  g11->GetXaxis()->SetTitle("Efficiency");
  g11->GetXaxis()->SetTitleOffset(1.3);
  g11->SetMarkerColor(kMagenta+2);


  TGraphErrors* g12 = ComSIGN(h_sig_subjetCSV,h_sig_COMjetCSV,h_sig_CA8jetCSV,h_bkd_subjetCSV,h_bkd_COMjetCSV,h_bkd_CA8jetCSV);
  
  g12->SetTitle("Significance");
  g12->GetYaxis()->SetTitle("Significance");
  g12->GetYaxis()->SetTitleOffset(1.3);
  g12->SetLineColor(kMagenta+2);
  g12->SetMarkerStyle(20);
  g12->SetLineWidth(2);
  g12->GetXaxis()->SetTitle("CSV work point");
  g12->GetXaxis()->SetTitleOffset(1.3);
  g12->SetMarkerColor(kMagenta+2);



  //------------------------------------------------------------
  /*
  TGraph* sCSVL = CSV(h_sig_subjetCSV, h_sig_subjetCSVL,h_bkd_subjetCSV, h_bkd_subjetCSVL);

  sCSVL->SetMarkerStyle(5);
  sCSVL->SetMarkerSize(5);


  //------------------------------------------------------------

  TGraph* sCSVM = CSV(h_sig_subjetCSV, h_sig_subjetCSVM,h_bkd_subjetCSV, h_bkd_subjetCSVM);

  sCSVM->SetMarkerStyle(29);
  sCSVM->SetMarkerSize(5);

  //------------------------------------------------------------


  TGraph* sCSVT = CSV(h_sig_subjetCSV, h_sig_subjetCSVT,h_bkd_subjetCSV, h_bkd_subjetCSVT);

  sCSVT->SetMarkerStyle(5);
  sCSVT->SetMarkerSize(5);

  //------------------------------------------------------------

 TGraph* CSVL = CSV(h_sig_CA8jetCSV, h_sig_CA8jetCSVL,h_bkd_CA8jetCSV, h_bkd_CA8jetCSVL);

  CSVL->SetMarkerStyle(5);
  CSVL->SetMarkerSize(5);


  //------------------------------------------------------------

  TGraph* CSVM = CSV(h_sig_CA8jetCSV, h_sig_CA8jetCSVM,h_bkd_CA8jetCSV, h_bkd_CA8jetCSVM);

  CSVM->SetMarkerStyle(29);
  CSVM->SetMarkerSize(5);

  //------------------------------------------------------------


  TGraph* CSVT = CSV(h_sig_CA8jetCSV, h_sig_CA8jetCSVT,h_bkd_CA8jetCSV, h_bkd_CA8jetCSVT);

  CSVT->SetMarkerStyle(23);
  CSVT->SetMarkerSize(5);
  */
  //------------------------------------------------------------


  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetPadGridX(kTRUE);
  gStyle->SetPadGridY(kTRUE);


  TCanvas *c= new TCanvas("c","",1500,1500);
  c->Divide(2,4);

  c->cd(1);
  
  gPad->SetLogy();
  g1->Draw("ap");
  g2->Draw("psame");
  g11->Draw("psame");
  //sCSVL->Draw("psame");
  //sCSVM->Draw("psame");
  //sCSVT->Draw("psame");
  //CSVL->Draw("psame");
  //CSVM->Draw("psame");
  //CSVT->Draw("psame");
  
  /*
  TLegend *leg = new TLegend(0.15, 0.75, 0.35, 0.9);

  leg->SetFillStyle(1001);
  leg->SetFillColor(10);
  leg->SetBorderSize(1);
  leg->AddEntry(g1,"CA8jetCSV", "lp");
  leg->AddEntry(g2,"CA8prunedsubjetCSV", "lp");
  leg->AddEntry(g11,"Combined CSV","lp");
  leg->Draw("same");
  */
  
  c->cd(2);
  g3->Draw("ap");
  g4->Draw("psame");
  g12->Draw("psame");

  c->cd(3);
  //gPad->SetLogy();
  g6->Draw("ap");
  g5->Draw("psame");

  c->cd(4);
  //gPad->SetLogy();
  g8->Draw("ap");
  g7->Draw("psame");


  c->cd(5);
  g9->Draw("ap");
  g10->Draw("psame");


  c->cd(6);

  h_bkd_CA8jetCSV->SetFillColor(8);
  h_bkd_CA8jetCSV->SetLineColor(8);



  TLegend *leg = new TLegend(0.15, 0.55, 0.75, 0.9);

  leg->SetFillStyle(1001);
  leg->SetFillColor(10);
  leg->SetBorderSize(1);
  leg->AddEntry(g1,"CA8jetCSV", "lp");
  leg->AddEntry(g2,"CA8prunedsubjetCSV", "lp");
  leg->AddEntry(g11,"Combined CSV","lp");
  leg->AddEntry(g10,"Background efficiency","lp");
  leg->AddEntry(h_bkd_CA8jetCSV,"Background CSV value","F");
  leg->Draw("a");



  c->cd(7);
  
  h_sig_CA8jetCSV->Scale(1/(h_sig_CA8jetCSV->Integral()));
  h_bkd_CA8jetCSV->Scale(1/(h_bkd_CA8jetCSV->Integral()));

  h_sig_CA8jetCSV->SetLineColor(4);
  h_sig_CA8jetCSV->SetMarkerStyle(20);
  h_sig_CA8jetCSV->SetLineWidth(2);
  h_sig_CA8jetCSV->SetMarkerColor(4);

  h_bkd_CA8jetCSV->GetXaxis()->SetTitle("CSV work point");
  h_bkd_CA8jetCSV->GetXaxis()->SetTitleOffset(1.3);
  h_bkd_CA8jetCSV->SetTitle("CA8jetCSV: SIG vs BKD");
  //h_bkd_CA8jetCSV->SetFillColor(8);
  //h_bkd_CA8jetCSV->SetLineColor(8);

  h_bkd_CA8jetCSV->Draw("histe");
  h_sig_CA8jetCSV->Draw("esame");
  

  c->cd(8);
  
  h_sig_SubjetCSV->Scale(1/(h_sig_SubjetCSV->Integral()));
  h_bkd_SubjetCSV->Scale(1/(h_bkd_SubjetCSV->Integral()));

  h_sig_SubjetCSV->SetLineColor(2);
  h_sig_SubjetCSV->SetMarkerStyle(20);
  h_sig_SubjetCSV->SetLineWidth(2);
  h_sig_SubjetCSV->SetMarkerColor(2);

  h_bkd_SubjetCSV->GetXaxis()->SetTitle("CSV work point");
  h_bkd_SubjetCSV->GetXaxis()->SetTitleOffset(1.3);
  h_bkd_SubjetCSV->SetTitle("SubjetCSV: SIG vs BKD");
  h_bkd_SubjetCSV->SetFillColor(8);
  h_bkd_SubjetCSV->SetLineColor(8);

  h_bkd_SubjetCSV->Draw("histe");
  h_sig_SubjetCSV->Draw("esame");
  


  gSystem->ProcessEvents();
  TImage *img = TImage::Create();
  img->FromPad(c);
  img->WriteImage(Graph_name.data());
  delete c;
  delete img;


}




TGraphErrors* ROC(TH1* h_sig, TH1* h_bkd){


  // signal eff
  Int_t sig_nbin = h_sig->GetNbinsX();
  Double_t eff[sig_nbin];
  Double_t error_eff[sig_nbin];

  for(Int_t i=0; i<=sig_nbin; i++){

    Double_t numer[sig_nbin];
    Double_t denom[sig_nbin];
    
    if(i+1>sig_nbin) continue;
    numer[i] = h_sig->Integral(i+1,sig_nbin);
    denom[i] = h_sig->Integral();
    
    if(denom[i]<=0) continue;
    eff[i] = numer[i]/denom[i];
    
    // calculate error
    error_eff[i]=0;
    
    for(Int_t j=i+1; j<=sig_nbin; j++){
    
      Double_t numer_binerror[sig_nbin];  
      numer_binerror[j] = h_sig->GetBinError(j);  
      error_eff[i] = error_eff[i] + pow( (numer_binerror[j]/denom[i]),2 );

    }
    
    error_eff[i] = sqrt(error_eff[i]);

  } // i loop
  
  

  // background eff (mistag rate)
  Int_t bkd_nbin = h_bkd->GetNbinsX();
  Double_t mistag[bkd_nbin];
  Double_t error_mistag[bkd_nbin];

  for(Int_t i=0; i<=bkd_nbin; i++){

    Double_t numer[bkd_nbin];
    Double_t denom[bkd_nbin];
    
    if(i+1>bkd_nbin) continue;
    numer[i] = h_bkd->Integral(i+1,bkd_nbin);
    denom[i] = h_bkd->Integral();
    
    if(denom[i]<=0) continue;
    mistag[i] = numer[i]/denom[i];
    
    // calculate error
    error_mistag[i]=0;
    
    for(Int_t j=i+1; j<=bkd_nbin; j++){
      
      Double_t numer_binerror[bkd_nbin];  
      numer_binerror[j] = h_bkd->GetBinError(j);  
      error_mistag[i] = error_mistag[i] + pow( (numer_binerror[j]/denom[i]),2 );
  
    }
    
    error_mistag[i] = sqrt(error_mistag[i]);

  } // i loop


  //----------------------------------------------------

  TGraphErrors* g = new TGraphErrors(sig_nbin, eff, mistag, error_eff, error_mistag);
  return g;
  

  h_sig->Reset();
  h_bkd->Reset();

}



TGraphErrors* SIGN(TH1* h_sig, TH1* h_bkd){

  
  // signal eff
  Int_t sig_nbin = h_sig->GetNbinsX();
  Double_t eff[sig_nbin];
  Double_t error_eff[sig_nbin];

  for(Int_t i=0; i<=sig_nbin; i++){

    Double_t numer[sig_nbin];
    Double_t denom[sig_nbin];
    
    if(i+1>sig_nbin) continue;

    numer[i] = h_sig->Integral(i+1,sig_nbin);
    denom[i] = h_sig->Integral();
    
    if(denom[i]<=0) continue;
    eff[i] = numer[i]/denom[i];
    

    // calculate error
    error_eff[i]=0;
    
    for(Int_t j=i+1; j<=sig_nbin; j++){
    
      Double_t numer_binerror[sig_nbin];  
      numer_binerror[j] = h_sig->GetBinError(j);  
      error_eff[i] = error_eff[i] + pow( (numer_binerror[j]/denom[i]),2 );

    }
    
    error_eff[i] = sqrt(error_eff[i]);

  } // i loop
  
  

  // background eff (mistag rate)
  Int_t bkd_nbin = h_bkd->GetNbinsX();
  Double_t error_denom[bkd_nbin];

  for(Int_t i=0; i<=bkd_nbin; i++){

    Double_t denom[bkd_nbin];
    
    if(i+1>bkd_nbin) continue;
    denom[i] = h_bkd->Integral(i+1,bkd_nbin);
    
    // calculate error
    error_denom[i]=0;

    for(Int_t j=i+1; j<=bkd_nbin; j++){
      
      Double_t numer_binerror[bkd_nbin];  
      numer_binerror[j] = h_bkd->GetBinError(j);  
      error_denom[i] = error_denom[i] + pow( (numer_binerror[j]) ,2 );

    }
    
    error_denom[i] = sqrt(error_denom[i]);
    
  } // i loop



  // significance
  Double_t sign[sig_nbin];
  Double_t error_sign[sig_nbin];
  Double_t bincontent[sig_nbin];
  Double_t null[sig_nbin];

  for(Int_t i=0; i<=sig_nbin; i++){

    //Double_t numer[sig_nbin];
    Double_t denom[sig_nbin];
    Double_t bkd[sig_nbin];
    Double_t sign_denom[sig_nbin];
    
    if(i+1>sig_nbin) continue;
    bkd[i]= h_bkd->Integral(i+1,sig_nbin);
    sign_denom[i]= 1/(1.0+sqrt(bkd[i]));    
    
    bincontent[i]=h_sig->GetXaxis()->GetBinCenter(i+1);
    null[i]=0;
    denom[i] = h_sig->Integral();
    

    if(denom[i]<=0) continue;
    sign[i] = eff[i]*sign_denom[i];
    
    
    error_sign[i] = sign_denom[i]*sqrt( ( pow(error_eff[i],2)+(1/4)*( pow(eff[i],2)*sign_denom[i] )*pow(sign_denom[i],2)*pow(error_denom[i],2) ) );




  } // i loop


  //----------------------------------------------------

  TGraphErrors* g = new TGraphErrors(sig_nbin, bincontent , sign , null , error_sign);
  return g;
  
  h_sig->Reset();
  h_bkd->Reset();

}



/*
TGraph* CSV(TH1* h_sig,TH1* h_sig_CSV, TH1* h_bkd, TH1* h_bkd_CSV ){


  // signal eff
  Double_t eff[1]={0};
  if( (h_sig->Integral())>0 ) eff[0] = (h_sig_CSV->Integral())/(h_sig->Integral());
  
  // background eff (mistag rate)
  Double_t mistag[1]={0};
  if( (h_bkd->Integral())>0 ) mistag[0] = (h_bkd_CSV->Integral())/(h_bkd->Integral());  
  


  cout<<"eff:"<<eff[0]<<" mistag:"<<mistag[0]<<endl;


  //----------------------------------------------------


  TGraph* g = new TGraph(1, eff, mistag);
  return g;
  
  h_sig->Reset();
  h_bkd->Reset();
  h_sig_CSV->Reset();
  h_bkd_CSV->Reset();

}
*/


TGraphErrors* EFF(TH1* h_sig){


  // signal eff
  Int_t sig_nbin = h_sig->GetNbinsX();
  Double_t eff[sig_nbin];
  Double_t error_eff[sig_nbin];
  Double_t null[sig_nbin];
  Double_t bincontent[sig_nbin];


  for(Int_t i=0; i<=sig_nbin; i++){

    Double_t numer[sig_nbin];
    Double_t denom[sig_nbin];

    if(i+1>sig_nbin) continue;

    numer[i] = h_sig->Integral(i+1,sig_nbin);
    denom[i] = h_sig->Integral();
    bincontent[i] = h_sig->GetXaxis()->GetBinCenter(i+1);

    if(denom[i]<=0) continue;
    eff[i] = numer[i]/denom[i];
    
    // calculate error
    error_eff[i]=0;
    
    for(Int_t j=i+1; j<=sig_nbin; j++){
    
      Double_t numer_binerror[sig_nbin];  
      numer_binerror[j] = h_sig->GetBinError(j);  
      error_eff[i] = error_eff[i] + pow( (numer_binerror[j]/denom[i]),2 );

    }
    
    null[i] = 0;
    error_eff[i] = sqrt(error_eff[i]);
    
    
  } // i loop
  


  TGraphErrors* g = new TGraphErrors(sig_nbin, bincontent, eff , null , error_eff);
  return g;
  
  h_sig->Reset();

}


TGraphErrors* D_EFF(TH2* h_denom){


  // signal eff
  Int_t denom_nbin = h_denom->GetNbinsX();
  Double_t eff[denom_nbin];
  Double_t error_eff[denom_nbin];
  Double_t null[denom_nbin];
  Double_t bincontent[denom_nbin];


  for(Int_t i=0; i<=denom_nbin; i++){

    Double_t numer[denom_nbin];
    Double_t denom[denom_nbin];

    if(i+1>denom_nbin) continue;

    numer[i] = h_denom->Integral(i+1,denom_nbin,i+1,denom_nbin);
    denom[i] = h_denom->Integral(1,denom_nbin,1,denom_nbin);
    bincontent[i] = h_denom->GetXaxis()->GetBinCenter(i+1);

    if(denom[i]<=0) continue;
    eff[i] = numer[i]/denom[i];
    
    // calculate error
    error_eff[i]=0;
    
    for(Int_t j=i+1; j<=denom_nbin; j++){
    
      Double_t numer_binerror[denom_nbin];  
      numer_binerror[j] = h_denom->GetBinError(j,j);  
      error_eff[i] = error_eff[i] + pow( (numer_binerror[j]/denom[i]),2 );

    }
    
    null[i] = 0;
    error_eff[i] = sqrt(error_eff[i]);
    
    
  } // i loop
  

  TGraphErrors* g = new TGraphErrors(denom_nbin, bincontent, eff , null , error_eff);
  return g;
  
  h_denom->Reset();

}



TGraphErrors* D_ROC(TH2* h_sig, TH2* h_bkd){


  // signal eff
  Int_t sig_nbin = h_sig->GetNbinsX();
  Double_t eff[sig_nbin];
  Double_t error_eff[sig_nbin];

  for(Int_t i=0; i<=sig_nbin; i++){

    Double_t numer[sig_nbin];
    Double_t denom[sig_nbin];
    
    if(i+1>sig_nbin) continue;
    numer[i] = h_sig->Integral(i+1,sig_nbin,i+1,sig_nbin);
    denom[i] = h_sig->Integral();
    
    if(denom[i]<=0) continue;
    eff[i] = numer[i]/denom[i];
    
    // calculate error
    error_eff[i]=0;
    
    for(Int_t j=i+1; j<=sig_nbin; j++){
    
      Double_t numer_binerror[sig_nbin];  
      numer_binerror[j] = h_sig->GetBinError(j,j);  
      error_eff[i] = error_eff[i] + pow( (numer_binerror[j]/denom[i]),2 );

    }
    
    error_eff[i] = sqrt(error_eff[i]);

  } // i loop
  
  

  // background eff (mistag rate)
  Int_t bkd_nbin = h_bkd->GetNbinsX();
  Double_t mistag[bkd_nbin];
  Double_t error_mistag[bkd_nbin];

  for(Int_t i=0; i<=bkd_nbin; i++){

    Double_t numer[bkd_nbin];
    Double_t denom[bkd_nbin];
    
    if(i+1>bkd_nbin) continue;
    numer[i] = h_bkd->Integral(i+1,bkd_nbin,i+1,bkd_nbin);
    denom[i] = h_bkd->Integral();
    
    if(denom[i]<=0) continue;
    mistag[i] = numer[i]/denom[i];
    
    // calculate error
    error_mistag[i]=0;
    
    for(Int_t j=i+1; j<=bkd_nbin; j++){
      
      Double_t numer_binerror[bkd_nbin];  
      numer_binerror[j] = h_bkd->GetBinError(j,j);  
      error_mistag[i] = error_mistag[i] + pow( (numer_binerror[j]/denom[i]),2 );
  
    }
    
    error_mistag[i] = sqrt(error_mistag[i]);

  } // i loop


  //----------------------------------------------------

  TGraphErrors* g = new TGraphErrors(sig_nbin, eff, mistag, error_eff, error_mistag);
  return g;
  

  h_sig->Reset();
  h_bkd->Reset();

}







TGraphErrors* D_SIGN(TH2* h_sig, TH2* h_bkd){

  
  // signal eff
  Int_t sig_nbin = h_sig->GetNbinsX();
  Double_t eff[sig_nbin];
  Double_t error_eff[sig_nbin];

  for(Int_t i=0; i<=sig_nbin; i++){

    Double_t numer[sig_nbin];
    Double_t denom[sig_nbin];
    
    if(i+1>sig_nbin) continue;

    numer[i] = h_sig->Integral(i+1,sig_nbin,i+1,sig_nbin);
    denom[i] = h_sig->Integral();
    
    if(denom[i]<=0) continue;
    eff[i] = numer[i]/denom[i];
    

    // calculate error
    error_eff[i]=0;
    
    for(Int_t j=i+1; j<=sig_nbin; j++){
    
      Double_t numer_binerror[sig_nbin];  
      numer_binerror[j] = h_sig->GetBinError(j,j);  
      error_eff[i] = error_eff[i] + pow( (numer_binerror[j]/denom[i]),2 );

    }
    
    error_eff[i] = sqrt(error_eff[i]);

  } // i loop
  
  

  // background eff (mistag rate)
  Int_t bkd_nbin = h_bkd->GetNbinsX();
  Double_t error_denom[bkd_nbin];

  for(Int_t i=0; i<=bkd_nbin; i++){

    Double_t denom[bkd_nbin];
    
    if(i+1>bkd_nbin) continue;
    denom[i] = h_bkd->Integral(i+1,bkd_nbin,i+1,bkd_nbin);
    
    // calculate error
    error_denom[i]=0;

    for(Int_t j=i+1; j<=bkd_nbin; j++){
      
      Double_t numer_binerror[bkd_nbin];  
      numer_binerror[j] = h_bkd->GetBinError(j,j);  
      error_denom[i] = error_denom[i] + pow( (numer_binerror[j]) ,2 );

    }
    
    error_denom[i] = sqrt(error_denom[i]);
    
  } // i loop



  // significance
  Double_t sign[sig_nbin];
  Double_t error_sign[sig_nbin];
  Double_t bincontent[sig_nbin];
  Double_t null[sig_nbin];

  for(Int_t i=0; i<=sig_nbin; i++){

    //Double_t numer[sig_nbin];
    Double_t denom[sig_nbin];
    Double_t bkd[sig_nbin];
    Double_t sign_denom[sig_nbin];
    
    if(i+1>sig_nbin) continue;
    bkd[i]= h_bkd->Integral(i+1,sig_nbin,i+1,sig_nbin);
    sign_denom[i]= 1/(1.0+sqrt(bkd[i]));    
    
    bincontent[i]=h_sig->GetXaxis()->GetBinCenter(i+1);
    null[i]=0;
    denom[i] = h_sig->Integral();
    

    if(denom[i]<=0) continue;
    sign[i] = eff[i]*sign_denom[i];
    
    
    error_sign[i] = sign_denom[i]*sqrt( ( pow(error_eff[i],2)+(1/4)*( pow(eff[i],2)*sign_denom[i] )*pow(sign_denom[i],2)*pow(error_denom[i],2) ) );




  } // i loop


  //----------------------------------------------------

  TGraphErrors* g = new TGraphErrors(sig_nbin, bincontent , sign , null , error_sign);
  return g;
  
  h_sig->Reset();
  h_bkd->Reset();

}




TGraphErrors* ComEFF(TH2* h_subjet , TH1* h_fatjet , TH1* h_denom){


  //eff
  Int_t denom_nbin = h_denom->GetNbinsX();
  Double_t eff[denom_nbin];
  Double_t error_eff[denom_nbin];
  Double_t null[denom_nbin];
  Double_t bincontent[denom_nbin];


  for(Int_t i=0; i<=denom_nbin; i++){

    Double_t numer[denom_nbin];
    Double_t denom[denom_nbin];

    if(i+1>denom_nbin) continue;

    numer[i] = (h_subjet->Integral(i+1,denom_nbin,i+1,denom_nbin))+(h_fatjet->Integral(i+1,denom_nbin));
    denom[i] = h_denom->Integral();
    bincontent[i] = h_denom->GetXaxis()->GetBinCenter(i+1);

    if(denom[i]<=0) continue;
    eff[i] = numer[i]/denom[i];
    
    // calculate error
    error_eff[i]=0;
    
    for(Int_t j=i+1; j<=denom_nbin; j++){
    
      Double_t numer_binerror[denom_nbin];  
      numer_binerror[j] = sqrt(pow((h_subjet->GetBinError(j,j)),2)+pow((h_fatjet->GetBinError(j)),2));  
      error_eff[i] = error_eff[i] + pow( (numer_binerror[j]/denom[i]),2 );

    }
    
    null[i] = 0;
    error_eff[i] = sqrt(error_eff[i]);
    
    
  } // i loop
  

  cout<<"h_subjet:"<<h_subjet->Integral(1,20,1,20)<<"h_comjet"<<h_fatjet->Integral(1,20)<<"denom"<<h_denom->Integral()<<endl;
  cout<<"eff[0]:"<<eff[0]<<endl;

  TGraphErrors* g = new TGraphErrors(denom_nbin, bincontent, eff , null , error_eff);
  return g;
  
  h_subjet->Reset();
  h_fatjet->Reset();


  

}



TGraphErrors* ComROC(TH2* sig_subjet, TH1* sig_fatjet, TH1* sig_denom , TH2* bkd_subjet ,TH1* bkd_fatjet, TH1* bkd_denom){


  // signal eff
  Int_t sig_denom_nbin = sig_denom->GetNbinsX();
  Double_t eff[sig_denom_nbin];
  Double_t error_eff[sig_denom_nbin];

  for(Int_t i=0; i<=sig_denom_nbin; i++){

    Double_t numer[sig_denom_nbin];
    Double_t denom[sig_denom_nbin];
    
    if(i+1>sig_denom_nbin) continue;
    numer[i] = (sig_subjet->Integral(i+1,sig_denom_nbin,i+1,sig_denom_nbin))+(sig_fatjet->Integral(i+1,sig_denom_nbin));
    denom[i] = sig_denom->Integral();
    
    if(denom[i]<=0) continue;
    eff[i] = numer[i]/denom[i];
    
    // calculate error
    error_eff[i]=0;
    
    for(Int_t j=i+1; j<=sig_denom_nbin; j++){
    
      Double_t numer_binerror[sig_denom_nbin];  
      numer_binerror[j] = sqrt(pow((sig_subjet->GetBinError(j,j)),2)+pow((sig_fatjet->GetBinError(j)),2));  
      error_eff[i] = error_eff[i] + pow( (numer_binerror[j]/denom[i]),2 );

    }
    
    error_eff[i] = sqrt(error_eff[i]);

  } // i loop
  
  

  // background eff (mistag rate)
  Int_t bkd_denom_nbin = bkd_denom->GetNbinsX();
  Double_t mistag[bkd_denom_nbin];
  Double_t error_mistag[bkd_denom_nbin];

  for(Int_t i=0; i<=bkd_denom_nbin; i++){

    Double_t numer[bkd_denom_nbin];
    Double_t denom[bkd_denom_nbin];
    
    if(i+1>bkd_denom_nbin) continue;
    numer[i] = (bkd_subjet->Integral(i+1,bkd_denom_nbin,i+1,bkd_denom_nbin))+(bkd_fatjet->Integral(i+1,bkd_denom_nbin));
    denom[i] = bkd_denom->Integral();
    
    if(denom[i]<=0) continue;
    mistag[i] = numer[i]/denom[i];
    
    // calculate error
    error_eff[i]=0;
    
    for(Int_t j=i+1; j<=bkd_denom_nbin; j++){
    
      Double_t numer_binerror[bkd_denom_nbin];  
      numer_binerror[j] = sqrt(pow((bkd_subjet->GetBinError(j,j)),2)+pow((bkd_fatjet->GetBinError(j)),2));  
      error_mistag[i] = error_mistag[i] + pow( (numer_binerror[j]/denom[i]),2 );

    }
    
    error_mistag[i] = sqrt(error_eff[i]);

  } // i loop


  //----------------------------------------------------

  TGraphErrors* g = new TGraphErrors(sig_denom_nbin, eff, mistag, error_eff, error_mistag);
  return g;
  
  sig_subjet->Reset(); 
  sig_fatjet->Reset();
  sig_denom->Reset();
  bkd_subjet->Reset();
  bkd_fatjet->Reset();
  bkd_denom->Reset();
  
}




TGraphErrors* ComSIGN(TH2* sig_subjet, TH1* sig_fatjet, TH1* sig_denom , TH2* bkd_subjet ,TH1* bkd_fatjet,TH1* bkd_denom){


  // signal eff
  Int_t sig_denom_nbin = sig_denom->GetNbinsX();
  Double_t eff[sig_denom_nbin];
  Double_t error_eff[sig_denom_nbin];

  for(Int_t i=0; i<=sig_denom_nbin; i++){

    Double_t numer[sig_denom_nbin];
    Double_t denom[sig_denom_nbin];
    
    if(i+1>sig_denom_nbin) continue;
    numer[i] = (sig_subjet->Integral(i+1,sig_denom_nbin,i+1,sig_denom_nbin))+(sig_fatjet->Integral(i+1,sig_denom_nbin));
    denom[i] = sig_denom->Integral();
    
    if(denom[i]<=0) continue;
    eff[i] = numer[i]/denom[i];
    
    // calculate error
    error_eff[i]=0;
    
    for(Int_t j=i+1; j<=sig_denom_nbin; j++){
    
      Double_t numer_binerror[sig_denom_nbin];  
      numer_binerror[j] = sqrt(pow((sig_subjet->GetBinError(j,j)),2)+pow((sig_fatjet->GetBinError(j)),2));  
      error_eff[i] = error_eff[i] + pow( (numer_binerror[j]/denom[i]),2 );

    }
    
    error_eff[i] = sqrt(error_eff[i]);

  } // i loop
  
  
  // background eff (mistag rate)
  Int_t bkd_nbin = bkd_denom->GetNbinsX();
  Double_t error_denom[bkd_nbin];

  for(Int_t i=0; i<=bkd_nbin; i++){

    Double_t denom[bkd_nbin];
    
    if(i+1>bkd_nbin) continue;
    denom[i] = (bkd_subjet->Integral(i+1,bkd_nbin,i+1,bkd_nbin))+(bkd_fatjet->Integral(i+1,bkd_nbin));
    
    // calculate error
    error_denom[i]=0;

    for(Int_t j=i+1; j<=bkd_nbin; j++){
      
      Double_t numer_binerror[bkd_nbin];  
      numer_binerror[j] = sqrt(pow((bkd_subjet->GetBinError(j,j)),2)+pow((bkd_fatjet->GetBinError(j)),2));  
      error_denom[i] = error_denom[i] + pow( (numer_binerror[j]) ,2 );

    }
    
    error_denom[i] = sqrt(error_denom[i]);
    
  } // i loop



  // significance
  Double_t sign[sig_denom_nbin];
  Double_t error_sign[sig_denom_nbin];
  Double_t bincontent[sig_denom_nbin];
  Double_t null[sig_denom_nbin];

  for(Int_t i=0; i<=sig_denom_nbin; i++){

    //Double_t numer[sig_nbin];
    Double_t denom[sig_denom_nbin];
    Double_t bkd[sig_denom_nbin];
    Double_t sign_denom[sig_denom_nbin];
    
    if(i+1>sig_denom_nbin) continue;
    bkd[i]=(bkd_subjet->Integral(i+1,sig_denom_nbin,i+1,sig_denom_nbin))+(bkd_fatjet->Integral(i+1,sig_denom_nbin));
    sign_denom[i]= 1/(1.0+sqrt(bkd[i]));    
    
    bincontent[i]=sig_denom->GetXaxis()->GetBinCenter(i+1);
    null[i]=0;
    denom[i] = sig_denom->Integral();
    

    if(denom[i]<=0) continue;
    sign[i] = eff[i]*sign_denom[i];
    
    
    error_sign[i] = sign_denom[i]*sqrt( ( pow(error_eff[i],2)+(1/4)*( pow(eff[i],2)*sign_denom[i] )*pow(sign_denom[i],2)*pow(error_denom[i],2) ) );




  } // i loop
  



  //----------------------------------------------------

  TGraphErrors* g = new TGraphErrors(sig_denom_nbin, bincontent , sign , null , error_sign);
  return g;
  
  sig_subjet->Reset(); 
  sig_fatjet->Reset();
  sig_denom->Reset();
  bkd_subjet->Reset();
  bkd_fatjet->Reset();
    
}
