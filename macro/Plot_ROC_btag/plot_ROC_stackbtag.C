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
void plot_ROC_stackbtag(){


  
  TFile* SIG1 = new TFile("rootfile/onlybtag/delpanj_v4_AbelianZPrime_ZH_lljj_M1500.root");   
  TFile* BKD1 = new TFile("rootfile/onlybtag/delpanj_v4_background_M1500.root"); 

  TH1F* h1_sig_CA8jetCSV = (TH1F*)SIG1->Get("h_CA8jetCSV");
  TH2F* h1_sig_subjetCSV = (TH2F*)SIG1->Get("h_CA8subjetCSV");
  TH1F* h1_sig_COMjetCSV = (TH1F*)SIG1->Get("h_COMjetCSV");


  TH1F* h1_bkd_CA8jetCSV = (TH1F*)BKD1->Get("h_CA8jetCSV");
  TH2F* h1_bkd_subjetCSV = (TH2F*)BKD1->Get("h_CA8subjetCSV");
  TH1F* h1_bkd_COMjetCSV = (TH1F*)BKD1->Get("h_COMjetCSV");

  //-------------------------------------------------------

  TFile* SIG2 = new TFile("rootfile/cutboth/delpanj_v4_AbelianZPrime_ZH_lljj_M1500.root");   
  TFile* BKD2 = new TFile("rootfile/cutboth/delpanj_v4_background_M1500.root"); 

  TH1F* h2_sig_CA8jetCSV = (TH1F*)SIG2->Get("h_CA8jetCSV");
  TH2F* h2_sig_subjetCSV = (TH2F*)SIG2->Get("h_CA8subjetCSV");
  TH1F* h2_sig_COMjetCSV = (TH1F*)SIG2->Get("h_COMjetCSV");

  TH1F* h2_bkd_CA8jetCSV = (TH1F*)BKD2->Get("h_CA8jetCSV");
  TH2F* h2_bkd_subjetCSV = (TH2F*)BKD2->Get("h_CA8subjetCSV");
  TH1F* h2_bkd_COMjetCSV = (TH1F*)BKD2->Get("h_COMjetCSV");

  
  //-----------------------------------------------------------
  //combined SIGN

  TGraphErrors* g1 = ComSIGN(h1_sig_subjetCSV,h1_sig_COMjetCSV,h1_sig_CA8jetCSV,h1_bkd_subjetCSV,h1_bkd_COMjetCSV,h1_bkd_CA8jetCSV);
  
  g1->SetTitle("Combined Significance");
  g1->GetYaxis()->SetTitle("Significance");
  g1->GetYaxis()->SetTitleOffset(1.3);
  g1->SetLineColor(4);
  g1->SetMarkerStyle(20);
  g1->SetLineWidth(2);
  g1->GetXaxis()->SetTitle("CSV work point");
  g1->GetXaxis()->SetTitleOffset(1.3);
  g1->SetMarkerColor(4);

  //---------------------------------------------------------
  // comROC

  TGraphErrors* g3 = ComROC(h1_sig_subjetCSV,h1_sig_COMjetCSV,h1_sig_CA8jetCSV,h1_bkd_subjetCSV,h1_bkd_COMjetCSV,h1_bkd_CA8jetCSV);
  
  g3->SetTitle("Combined ROC");
  g3->GetYaxis()->SetTitle("Mis-tag rate");
  g3->GetYaxis()->SetTitleOffset(1.3);
  g3->SetLineColor(4);
  g3->SetMarkerStyle(20);
  g3->SetLineWidth(2);
  g3->GetXaxis()->SetTitle("Efficiency");
  g3->GetXaxis()->SetTitleOffset(1.3);
  g3->SetMarkerColor(4);

  //---------------------------------------------------------
  //signal eff

  TGraphErrors* g5 = ComEFF(h1_sig_subjetCSV,h1_sig_COMjetCSV,h1_sig_CA8jetCSV);
  
  g5->SetTitle("Combined signal efficiency vs combined background efficiency");
  g5->GetYaxis()->SetTitle("Efficiency");
  g5->GetYaxis()->SetTitleOffset(1.3);
  g5->SetLineColor(4);
  g5->SetMarkerStyle(20);
  g5->SetLineWidth(2);
  g5->GetXaxis()->SetTitle("CSV work point");
  g5->GetXaxis()->SetTitleOffset(1.3);
  g5->SetMarkerColor(4);

  //background eff

  TGraphErrors* g6 = ComEFF(h1_bkd_subjetCSV,h1_bkd_COMjetCSV,h1_bkd_CA8jetCSV);
  
  g6->SetTitle("Combined Efficiency");
  g6->GetYaxis()->SetTitle("Efficiency");
  g6->GetYaxis()->SetTitleOffset(1.3);
  g6->SetLineColor(4);
  g6->SetMarkerStyle(22);
  g6->SetLineWidth(2);
  g6->GetXaxis()->SetTitle("CSV work point");
  g6->GetXaxis()->SetTitleOffset(1.3);
  g6->SetMarkerColor(4);



  //================== CUTBOTH ==============================


  //---------------------------------------------------------
  //combined SIGN

  TGraphErrors* g2 = ComSIGN(h2_sig_subjetCSV,h2_sig_COMjetCSV,h1_sig_CA8jetCSV,h2_bkd_subjetCSV,h2_bkd_COMjetCSV,h1_bkd_CA8jetCSV);
  
  g2->SetTitle("Combined Significance");
  g2->GetYaxis()->SetTitle("Significance");
  g2->GetYaxis()->SetTitleOffset(1.3);
  g2->SetLineColor(2);
  g2->SetMarkerStyle(20);
  g2->SetLineWidth(2);
  g2->GetXaxis()->SetTitle("CSV work point");
  g2->GetXaxis()->SetTitleOffset(1.3);
  g2->SetMarkerColor(2);

  //---------------------------------------------------------
  // combined ROC

  TGraphErrors* g4 = ComROC(h2_sig_subjetCSV,h2_sig_COMjetCSV,h1_sig_CA8jetCSV,h2_bkd_subjetCSV,h2_bkd_COMjetCSV,h1_bkd_CA8jetCSV);
  
  g4->SetTitle("Combined ROC");
  g4->GetYaxis()->SetTitle("Mis-tag rate");
  g4->GetYaxis()->SetTitleOffset(1.3);
  g4->SetLineColor(2);
  g4->SetMarkerStyle(20);
  g4->SetLineWidth(2);
  g4->GetXaxis()->SetTitle("Efficiency");
  g4->GetXaxis()->SetTitleOffset(1.3);
  g4->SetMarkerColor(2);

  //---------------------------------------------------------
  //signal eff

  TGraphErrors* g7 = ComEFF(h2_sig_subjetCSV,h2_sig_COMjetCSV,h1_sig_CA8jetCSV);
  
  g7->SetTitle("Combined Efficiency");
  g7->GetYaxis()->SetTitle("Efficiency");
  g7->GetYaxis()->SetTitleOffset(1.3);
  g7->SetLineColor(2);
  g7->SetMarkerStyle(20);
  g7->SetLineWidth(2);
  g7->GetXaxis()->SetTitle("CSV work point");
  g7->GetXaxis()->SetTitleOffset(1.3);
  g7->SetMarkerColor(2);

  //background eff

  TGraphErrors* g8 = ComEFF(h2_bkd_subjetCSV,h2_bkd_COMjetCSV,h1_bkd_CA8jetCSV);
  
  g8->SetTitle("Combined Efficiency");
  g8->GetYaxis()->SetTitle("Efficiency");
  g8->GetYaxis()->SetTitleOffset(1.3);
  g8->SetLineColor(2);
  g8->SetMarkerStyle(22);
  g8->SetLineWidth(2);
  g8->GetXaxis()->SetTitle("CSV work point");
  g8->GetXaxis()->SetTitleOffset(1.3);
  g8->SetMarkerColor(2);


  //---------------------------------------------------------

  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetPadGridX(kTRUE);
  gStyle->SetPadGridY(kTRUE);


  TCanvas *c= new TCanvas("c","",1600,1200);
  c->Divide(2,2);

  c->cd(1);
  
  gPad->SetLogy();
  g3->Draw("ap");
  g4->Draw("psame");
  

  c->cd(2);
  g1->Draw("ap");
  g2->Draw("psame");
  

  c->cd(3);
  
  g5->Draw("ap");
  g6->Draw("psame");
  g7->Draw("psame");
  g8->Draw("psame");
 

  c->cd(4);
  
  TLegend *leg = new TLegend(0.15, 0.55, 0.65, 0.9);

  leg->SetFillStyle(1001);
  leg->SetFillColor(10);
  leg->SetBorderSize(1);
  leg->AddEntry(g1,"Only CSV cut", "lp");
  leg->AddEntry(g2,"Cut both CSV and #tau_{21}", "lp");
  leg->AddEntry(g6,"Background efficiency-only CSV cut","lp");
  leg->AddEntry(g8,"Background efficiency-cut both","lp");
  //leg->AddEntry(h_bkd_CA8jetCSV,"Background CSV value","F");
  leg->Draw("a");

  

  gSystem->ProcessEvents();
  TImage *img = TImage::Create();
  img->FromPad(c);
  img->WriteImage("h_stackSIGN.png");
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
    

    cout<<"index:"<<i<<" denom:"<<denom[i]<<" numer:"<<numer[i]<<endl;




    // calculate error
    error_eff[i]=0;
    
    for(Int_t j=i+1; j<=bkd_denom_nbin; j++){
    
      Double_t numer_binerror[bkd_denom_nbin];  
      numer_binerror[j] = sqrt(pow((bkd_subjet->GetBinError(j,j)),2)+pow((bkd_fatjet->GetBinError(j)),2));  
      error_mistag[i] = error_mistag[i] + pow( (numer_binerror[j]/denom[i]),2 );

    }
    
    error_mistag[i] = sqrt(error_eff[i]);

  } // i loop




  for(int i=0; i<20; i++){

    //cout<<"index:"<<i<<" eff:"<<eff[i]<<" mistag:"<<mistag[i]<<endl;

  }


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
