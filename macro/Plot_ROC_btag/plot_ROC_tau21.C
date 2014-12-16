//root -q -b -l plot_ROC_tau21.C++\(\"inputFile1\",\"inpuFile2\"\,\"Graph_name\"\)
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
#include <TCanvas.h>
#include <TROOT.h>
#include "TImage.h"
#include "TSystem.h"
#include "TStyle.h"


TGraphErrors* ROC(TH1*, TH1*);
TGraphErrors* SIGN(TH1*, TH1*);
TGraphErrors* EFF(TH1*);



using namespace std;
void plot_ROC_tau21(std::string inputFile1, std::string inputFile2, std::string Graph_name){


  
  TFile* SIG = new TFile(inputFile1.data());   
  TFile* BKD = new TFile(inputFile2.data()); 

  TH1F* h_sig_tau21 = (TH1F*)SIG->Get("h_Tau21");
  TH1F* h_bkd_tau21 = (TH1F*)BKD->Get("h_Tau21");


  //------------------------------------------------------------
  
  TGraphErrors* g1 = ROC(h_sig_tau21, h_bkd_tau21);

  g1->SetTitle("ROC");
  g1->GetYaxis()->SetTitle("Mis-tag rate");
  g1->GetYaxis()->SetTitleOffset(1.3);
  g1->SetLineColor(4);
  g1->SetMarkerStyle(20);
  g1->SetLineWidth(2);
  g1->GetXaxis()->SetTitle("Efficiency");
  g1->GetXaxis()->SetTitleOffset(1.3);
  g1->SetMarkerColor(4);

  //------------------------------------------------------------
  
  TGraphErrors* g2 = SIGN(h_sig_tau21, h_bkd_tau21);
 
  g2->SetTitle("Significance");
  g2->GetYaxis()->SetTitle("Significance");
  g2->GetYaxis()->SetTitleOffset(1.3);
  g2->SetLineColor(4);
  g2->SetMarkerStyle(20);
  g2->SetLineWidth(2);
  g2->GetXaxis()->SetTitle("#Tau_{21} upper threshold");
  g2->GetXaxis()->SetTitleOffset(1.3);
  g2->SetMarkerColor(4);
  
  //------------------------------------------------------------

  TGraphErrors* g5 = EFF(h_sig_tau21);

  g5->SetLineColor(4);
  g5->SetMarkerStyle(20);
  g5->SetLineWidth(2);
  g5->SetMarkerColor(4);
  g5->SetTitle("");
  g5->GetYaxis()->SetTitle("Efficiency");
  g5->GetYaxis()->SetTitleOffset(1.3);
  g5->GetXaxis()->SetTitle("#Tau_{21} upper threshold");
  g5->GetXaxis()->SetTitleOffset(1.3);


  TGraphErrors* g6 = EFF(h_bkd_tau21);

  g6->SetMarkerStyle(20);
  g6->SetLineWidth(2);
  g6->SetTitle("CA8jetTau21 eff: SIG vs BKD");
  g6->GetYaxis()->SetTitle("Efficiency");
  g6->GetYaxis()->SetTitleOffset(1.3);
  g6->GetXaxis()->SetTitle("#Tau_{21} upper threshold");
  g6->GetXaxis()->SetTitleOffset(1.3);

  //-----------------------------------------------------------


  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetPadGridX(kTRUE);
  gStyle->SetPadGridY(kTRUE);


  TCanvas *c= new TCanvas("c","",1500,1200);
  c->Divide(2,2);

  c->cd(1);
  //gPad->SetLogy();
  g1->Draw("ap");
  
  
  h_bkd_tau21->SetFillColor(8);
  h_bkd_tau21->SetLineColor(8);
  

  
  TLegend *leg = new TLegend(0.15, 0.65, 0.45, 0.85);

  leg->SetFillStyle(1001);
  leg->SetFillColor(10);
  leg->SetBorderSize(1);
  leg->AddEntry(g1,"Signal #Tau_{21}", "lp");
  leg->AddEntry(g6,"Background eff", "lp");
  leg->AddEntry(h_bkd_tau21,"Background #Tau_{21} value","F");
  leg->Draw("same");
  
  
  c->cd(2);
  g2->Draw("ap");
  
  

  c->cd(3);
  g6->Draw("ap");
  g5->Draw("psame");



  c->cd(4);
  h_sig_tau21->Scale(1/(h_sig_tau21->Integral()));
  h_bkd_tau21->Scale(1/(h_bkd_tau21->Integral()));

  h_sig_tau21->SetLineColor(4);
  h_sig_tau21->SetMarkerStyle(20);
  h_sig_tau21->SetLineWidth(2);
  h_sig_tau21->SetMarkerColor(4);

  h_sig_tau21->GetXaxis()->SetTitle("#Tau_{21}");
  h_sig_tau21->GetXaxis()->SetTitleOffset(1.3);
  h_sig_tau21->SetTitle("CA8jetTau21: SIG vs BKD");
  h_bkd_tau21->SetFillColor(8);
  h_bkd_tau21->SetLineColor(8);

  h_sig_tau21->Draw("e");
  h_bkd_tau21->Draw("histesame");
  h_sig_tau21->Draw("esame");



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
    numer[i] = h_sig->Integral(1,i+1);
    denom[i] = h_sig->Integral();
    
    if(denom[i]<=0) continue;
    eff[i] = numer[i]/denom[i];
    
    // calculate error
    error_eff[i]=0;
    
    for(Int_t j=1; j<=i+1; j++){
    
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
    numer[i] = h_bkd->Integral(1,i+1);
    denom[i] = h_bkd->Integral();
    
    if(denom[i]<=0) continue;
    mistag[i] = numer[i]/denom[i];
    
    // calculate error
    error_mistag[i]=0;
    
    for(Int_t j=1; j<=i+1; j++){
      
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

    numer[i] = h_sig->Integral(1,i+1);
    denom[i] = h_sig->Integral();
    
    if(denom[i]<=0) continue;
    eff[i] = numer[i]/denom[i];
    

    // calculate error
    error_eff[i]=0;
    
    for(Int_t j=1; j<=i+1; j++){
    
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
    denom[i] = h_bkd->Integral(1,i+1);
    
    // calculate error
    error_denom[i]=0;

    for(Int_t j=1; j<=i+1; j++){
      
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
    bkd[i]= h_bkd->Integral(1,i+1);
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

    numer[i] = h_sig->Integral(1,i+1);
    denom[i] = h_sig->Integral();
    bincontent[i] = h_sig->GetXaxis()->GetBinCenter(i+1);

    if(denom[i]<=0) continue;
    eff[i] = numer[i]/denom[i];
    
    // calculate error
    error_eff[i]=0;
    
    for(Int_t j=1; j<=i+1; j++){
    
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


