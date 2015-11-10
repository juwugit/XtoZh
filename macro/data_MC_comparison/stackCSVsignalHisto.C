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



void stackCSVsignalHisto(){


  TFile *dy70    = TFile::Open("../summary/result_cuts/TH2_DYJetsPtZ70To100_Mu_Cen.root");
  TFile *dy100   = TFile::Open("../summary/result_cuts/TH2_DYJetsPtZ100_Mu_Cen.root");
  TFile *ttbar   = TFile::Open("../summary/result_cuts/TH2_TTTo2L2Nu2B_Mu_Cen.root");
  TFile *wz      = TFile::Open("../summary/result_cuts/TH2_DiBWZ_Mu_Cen.root");
  TFile *zz      = TFile::Open("../summary/result_cuts/TH2_DiBZZ_Mu_Cen.root");
  TFile *data    = TFile::Open("rootfile/data_Mu_Cen.root");
  TFile *sig800  = TFile::Open("../summary/result_cuts/ZPrime_ZH_lljj_M800_Mu_Cen.root");
  TFile *sig1200 = TFile::Open("../summary/result_cuts/ZPrime_ZH_lljj_M1200_Mu_Cen.root");
  TFile *sig1300 = TFile::Open("../summary/result_cuts/ZPrime_ZH_lljj_M1300_Mu_Cen.root");
  TFile *sig1400 = TFile::Open("../summary/result_cuts/ZPrime_ZH_lljj_M1400_Mu_Cen.root");
  TFile *sig1600 = TFile::Open("../summary/result_cuts/ZPrime_ZH_lljj_M1600_Mu_Cen.root");
  TFile *sig1800 = TFile::Open("../summary/result_cuts/ZPrime_ZH_lljj_M1800_Mu_Cen.root");
  TFile *sig1900 = TFile::Open("../summary/result_cuts/ZPrime_ZH_lljj_M1900_Mu_Cen.root");
  TFile *sig2000 = TFile::Open("../summary/result_cuts/ZPrime_ZH_lljj_M2000_Mu_Cen.root");

  /*
  TH1D *h_dy70    = (TH1D*)(dy70->Get("h_sigSubjetCSV"));
  TH1D *h_dy100   = (TH1D*)(dy100->Get("h_sigSubjetCSV"));
  TH1D *h_ttbar   = (TH1D*)(ttbar->Get("h_sigSubjetCSV"));
  TH1D *h_wz      = (TH1D*)(wz->Get("h_sigSubjetCSV"));
  TH1D *h_zz      = (TH1D*)(zz->Get("h_sigSubjetCSV"));
  TH1D *h_data    = (TH1D*)(data->Get("h_sigSubjetCSV"));
  TH1D *h_sig800  = (TH1D*)(sig800->Get("h_sigSubjetCSV"));
  TH1D *h_sig1200 = (TH1D*)(sig1200->Get("h_sigSubjetCSV"));
  TH1D *h_sig1300 = (TH1D*)(sig1300->Get("h_sigSubjetCSV"));
  TH1D *h_sig1400 = (TH1D*)(sig1400->Get("h_sigSubjetCSV"));
  TH1D *h_sig1600 = (TH1D*)(sig1600->Get("h_sigSubjetCSV"));
  TH1D *h_sig1800 = (TH1D*)(sig1800->Get("h_sigSubjetCSV"));
  TH1D *h_sig1900 = (TH1D*)(sig1900->Get("h_sigSubjetCSV"));
  TH1D *h_sig2000 = (TH1D*)(sig2000->Get("h_sigSubjetCSV"));
  */

  TH1D *h_dy70    = (TH1D*)(dy70->Get("h_sigXMass"));
  TH1D *h_dy100   = (TH1D*)(dy100->Get("h_sigXMass"));
  TH1D *h_ttbar   = (TH1D*)(ttbar->Get("h_sigXMass"));
  TH1D *h_wz      = (TH1D*)(wz->Get("h_sigXMass"));
  TH1D *h_zz      = (TH1D*)(zz->Get("h_sigXMass"));
  TH1D *h_data    = (TH1D*)(data->Get("h_sigXMass"));
  TH1D *h_sig800  = (TH1D*)(sig800->Get("h_sigXMass"));
  TH1D *h_sig1200 = (TH1D*)(sig1200->Get("h_sigXMass"));
  TH1D *h_sig1300 = (TH1D*)(sig1300->Get("h_sigXMass"));
  TH1D *h_sig1400 = (TH1D*)(sig1400->Get("h_sigXMass"));
  TH1D *h_sig1600 = (TH1D*)(sig1600->Get("h_sigXMass"));
  TH1D *h_sig1800 = (TH1D*)(sig1800->Get("h_sigXMass"));
  TH1D *h_sig1900 = (TH1D*)(sig1900->Get("h_sigXMass"));
  TH1D *h_sig2000 = (TH1D*)(sig2000->Get("h_sigXMass"));


  gStyle->SetOptStat(0);
  gStyle->SetPadGridY(kTRUE);
  gStyle->SetPadGridX(kTRUE);



  TCanvas* c1 = new TCanvas("c1", "", 0, 0, 750, 750);


  const Double_t varBins[] = {680,720,760,800,840,920,1000,1100,1250,1400,1600,1800,2000,2400};
  Int_t nvarBins = sizeof(varBins)/sizeof(varBins[0])-1;

  TH1D* h_stack = new TH1D("h_stack","",nvarBins,varBins);
  //TH1D* h_stack = new TH1D("h_stack","",20,0,1);
  h_stack->Add(h_zz);
  h_stack->Add(h_wz);
  h_stack->Add(h_ttbar);
  h_stack->Add(h_dy70);
  h_stack->Add(h_dy100);


  h_stack->SetFillColor(kCyan-4);
  h_stack->SetLineColor(kBlack);


  h_data->SetLineColor(1);
  h_data->SetMarkerStyle(8);
  h_data->SetMarkerSize(1);
  h_data->SetLabelSize(0);


  h_sig800->SetLineColor(kOrange+6);
  h_sig1200->SetLineColor(kAzure);
  h_sig1300->SetLineColor(kRed);
  h_sig1400->SetLineColor(kGreen+3);
  h_sig1600->SetLineColor(kRed);
  h_sig1800->SetLineColor(kViolet+2);
  h_sig1900->SetLineColor(kPink+10);
  h_sig2000->SetLineColor(kBlack);


  /*
  h_stack->Scale(1/h_stack->Integral());
  h_data->Scale(1/h_data->Integral());
  h_sig800->Scale(1/h_sig800->Integral());
  h_sig1200->Scale(1/h_sig1200->Integral());
  h_sig1300->Scale(1/h_sig1300->Integral());
  h_sig1400->Scale(1/h_sig1400->Integral());
  h_sig1600->Scale(1/h_sig1600->Integral());
  h_sig1800->Scale(1/h_sig1800->Integral());
  h_sig1900->Scale(1/h_sig1900->Integral());
  h_sig2000->Scale(1/h_sig2000->Integral());
  */
  
  h_stack->Draw("histe");
  //h_sig800->Draw("histesame");
  //h_sig1200->Draw("histesame");
  h_sig1300->Draw("histesame");
  h_sig1400->Draw("histesame");
  //h_sig1600->Draw("histesame");
  //h_sig1800->Draw("histesame");
  //h_sig1900->Draw("histesame");
  //h_sig2000->Draw("histesame");
  h_data->Draw("e1same");
  


  TLegend *leg = new TLegend(0.73, 0.68, 0.98, 0.98);

  leg->SetFillStyle(1001);
  leg->SetFillColor(10);
  leg->SetBorderSize(1);
  leg->AddEntry(h_stack, "Background MC", "f");
  leg->AddEntry(h_data, "Data", "lp");
  //leg->AddEntry(h_sig800, "ZprimeToZhTollqq_M800", "f");
  //leg->AddEntry(h_sig1200, "ZprimeToZhTollqq_M1200", "f");
  leg->AddEntry(h_sig1300, "ZprimeToZhTollqq_M1300", "f");
  leg->AddEntry(h_sig1400, "ZprimeToZhTollqq_M1400", "f");
  //leg->AddEntry(h_sig1600, "ZprimeToZhTollqq_M1600", "f");
  //leg->AddEntry(h_sig1800, "ZprimeToZhTollqq_M1800", "f");
  //leg->AddEntry(h_sig1900, "ZprimeToZhTollqq_M1900", "f");
  //leg->AddEntry(h_sig2000, "ZprimeToZhTollqq_M2000", "f");
  leg->Draw();



  c1->SaveAs("sigXMass.root");



  cout<<"bkg MC:"<<h_stack->Integral()<<endl;
  cout<<"sig800:"<<h_sig800->Integral()<<endl;
  cout<<"sig1200:"<<h_sig1200->Integral()<<endl;
  cout<<"sig1300:"<<h_sig1300->Integral()<<endl;
  cout<<"sig1400:"<<h_sig1400->Integral()<<endl;
  cout<<"sig1600:"<<h_sig1600->Integral()<<endl;
  cout<<"sig1800:"<<h_sig1800->Integral()<<endl;
  cout<<"sig1900:"<<h_sig1900->Integral()<<endl;
  cout<<"sig2000:"<<h_sig2000->Integral()<<endl;
  cout<<"data:"<<h_data->Integral()<<endl;


  /*
  gSystem->ProcessEvents();
  TImage *img1 = TImage::Create();
  img1->FromPad(c1);
  img1->WriteImage("h_sigXMass.png");
  delete c1;
  delete img1;
  */

}




