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


// lumi 876.224 for A , 4409 for B

Double_t scale1 = (876.225+4409) / (totalNEvent1 / crossSection1); // DYJetsToLL_PtZ-70To100
Double_t scale2 = (876.225+4409) / (totalNEvent2 / crossSection2); // DYJetsToLL_PtZ100
Double_t scale3 = (876.225+4409) / (totalNEvent3 / crossSection3); // TTbar


//void myPlot(TH1D*, TH1D*, TH1D*);
//void myPlot(TH1D*, TH1D*, TH1D*,TH1D*, TH1D*, TH1D*);


void bkg_estimate(){


  TFile *f1de = TFile::Open("rootfile/delpanj_v2_data_DoubleEl_A.root");
  TFile *f2de = TFile::Open("rootfile/delpanj_v2_data_DoubleEl_B.root");

  TFile *f1e = TFile::Open("rootfile/delpanj_v2_DYJetsToLL_PtZ-70To100_ee.root");
  TFile *f2e = TFile::Open("rootfile/delpanj_v2_DYJetsToLL_PtZ-100_ee.root");
  TFile *f3e = TFile::Open("rootfile/delpanj_v2_TTTo2L2Nu2B_ee.root");

  //TFile *f1m = TFile::Open("rootfile/delpanj_v2_DYJetsToLL_PtZ-70To100_mm.root");
  //TFile *f2m = TFile::Open("rootfile/delpanj_v2_DYJetsToLL_PtZ-100_mm.root");
  //TFile *f3m = TFile::Open("rootfile/delpanj_v2_TTTo2L2Nu2B_mm.root");
  
  




  gStyle->SetOptStat(0);
  //gStyle->SetPadGridY(kTRUE);
  //gStyle->SetPadGridX(kTRUE);


  
  TCanvas* c1 = new TCanvas("c1", "", 0, 0, 1600, 400);

  c1->Divide(3,1);


  
  

  const Float_t varBins[] = {840,920,1000,1100,1250,1400,1600,1800,2000,2200,2400};
  Int_t nvarBins = sizeof(varBins)/sizeof(varBins[0])-1;


  TH1D* h_bkg_sig = new TH1D("h_bkg_sig","",nvarBins,varBins);
  TH1D* h_bkg_sb = new TH1D("h_bkg_sb","",nvarBins,varBins);
  TH1D* h_alpha = new TH1D("h_alpha","Alpha Ratio",nvarBins,varBins);
  

  h_bkg_sig->Sumw2();
  h_bkg_sb->Sumw2();
  h_alpha->Sumw2();
  
  
  h_bkg_sig->Add( ((TH1D*)(f1e->Get("h_sigXMass"))), scale1 );
  h_bkg_sig->Add( ((TH1D*)(f2e->Get("h_sigXMass"))), scale2 );
  h_bkg_sig->Add( ((TH1D*)(f3e->Get("h_sigXMass"))), scale3 );
  //h_bkg_sig->Add( ((TH1D*)(f1m->Get("h_sigXMass"))), scale1 );
  //h_bkg_sig->Add( ((TH1D*)(f2m->Get("h_sigXMass"))), scale2 );
  //h_bkg_sig->Add( ((TH1D*)(f3m->Get("h_sigXMass"))), scale3 );

  h_bkg_sb->Add( ((TH1D*)(f1e->Get("h_sbXMass"))), scale1 );
  h_bkg_sb->Add( ((TH1D*)(f2e->Get("h_sbXMass"))), scale2 );
  h_bkg_sb->Add( ((TH1D*)(f3e->Get("h_sbXMass"))), scale3 );
  //h_bkg_sb->Add( ((TH1D*)(f1m->Get("h_sbXMass"))), scale1 );
  //h_bkg_sb->Add( ((TH1D*)(f2m->Get("h_sbXMass"))), scale2 );
  //h_bkg_sb->Add( ((TH1D*)(f3m->Get("h_sbXMass"))), scale3 );



  h_alpha->Divide(h_bkg_sig, h_bkg_sb);  
  h_alpha->GetYaxis()->SetRangeUser(0,1.7);
  h_alpha->SetMarkerStyle(8);
  h_alpha->SetMarkerSize(1);

  c1->cd(1);
  h_alpha->Draw();


  Int_t alpha_nbin = h_alpha->GetNbinsX();
  Double_t alpha_center[alpha_nbin];
  Double_t alpha_error[alpha_nbin];

  for(Int_t i=1; i<=alpha_nbin; i++){

    alpha_center[i] = h_alpha->GetBinContent(i);
    alpha_error[i] = h_alpha->GetBinError(i);

  }



  
  TH1D* h_data_sb = new TH1D("h_data_sb","data_sb_XMass",nvarBins,varBins);
  h_data_sb->Sumw2();
  h_data_sb->Add( ((TH1D*)(f1de->Get("h_sbXMass"))), 1 );
  h_data_sb->Add( ((TH1D*)(f2de->Get("h_sbXMass"))), 1 );

  //cout<<"data_integral: "<<h_data_sb->Integral()<<endl;
  
  c1->cd(2);
  h_data_sb->Draw();




  TH1D* h_data_Nbkg = new TH1D("h_data_Nbkg","",nvarBins,varBins);
  h_data_Nbkg->Sumw2();

  
  Double_t data_content[alpha_nbin];
  Double_t data_error[alpha_nbin];
  Double_t data_Nbkg[alpha_nbin];
  Double_t data_NbkgError[alpha_nbin];


  for(Int_t i=1; i<=alpha_nbin; i++){

    data_content[i] = h_data_sb->GetBinContent(i);
    data_Nbkg[i] = data_content[i] * alpha_center[i];

    h_data_Nbkg->SetBinContent(i,data_Nbkg[i]);


    
    if(alpha_center[i]==0 || data_content==0) continue;
    
    if(data_Nbkg[i]!=0)
      data_NbkgError[i] = (data_Nbkg[i])*sqrt(pow(alpha_error[i]/alpha_center[i],2)+pow(data_error[i]/data_content[i],2));
    
    else data_NbkgError[i]=0;
    

    cout<<"bin:"<<i<<" | alpha:"<<alpha_center[i]<<" | number of data:"<<data_content[i]<<" | number of etimated bkg:"<<data_Nbkg[i]<<" | error:"<<data_NbkgError[i]<<endl;


    
    h_data_Nbkg->SetBinError(i,data_NbkgError[i]);


  }


  h_data_Nbkg->GetXaxis()->SetTitle("M_{X} [GeV]");
  h_data_Nbkg->GetYaxis()->SetTitle("number of estimated background");
  h_data_Nbkg->GetYaxis()->SetTitleOffset(1.5);



  c1->cd(3);
  h_data_Nbkg->Draw("histe");
  h_bkg_sig->Draw("histesame");
  h_bkg_sig->SetLineColor(3);




  TLegend *leg = new TLegend(0.6, 0.8, 0.9, 0.9);

  leg->SetFillStyle(1001);
  leg->SetFillColor(10);
  leg->SetBorderSize(1);
  leg->AddEntry(h_data_Nbkg, "Data", "f");
  leg->AddEntry(h_bkg_sig,"MC background signal region", "f");
  leg->Draw("same");


  



  cout<<"data*alpha: "<<h_data_Nbkg->Integral()<<endl;
  cout<<"MC_signal region: "<<h_bkg_sig->Integral()<<endl;


  //------------------------------------------//
  

  gSystem->ProcessEvents();
  TImage *img1 = TImage::Create();
  img1->FromPad(c1);
  img1->WriteImage("h_BkgEstimate.png");
  delete c1;
  delete img1;


}





