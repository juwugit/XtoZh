#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <TPad.h>
#include <TH1D.h>
#include <TH1F.h>
#include <TH2F.h>
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



void stackCorVariables(std::string inputFile1, std::string inputFile2, std::string outputFile){


  TFile *data = TFile::Open(inputFile1.data());
  TFile *MC = TFile::Open(inputFile2.data());

  gStyle->SetOptStat(0);




  TCanvas* c1 = new TCanvas("c1", "", 0, 0, 750, 1500);

  c1->Divide(2,3);


  c1->cd(1);

  TH2F* pruned_tau21_MC = (TH2F*)MC->Get("pruned_tau21");
  pruned_tau21_MC->SetTitle("MC prunedmass vs tau21");
  pruned_tau21_MC->GetYaxis()->SetTitle("tau21");
  pruned_tau21_MC->GetXaxis()->SetTitle("prunedmass");
  pruned_tau21_MC->Draw();

  cout<<"pruned_tau21_MC:"<<(pruned_tau21_MC->GetCorrelationFactor())<<endl;

  c1->cd(2);

  TH2F* pruned_tau21_data = (TH2F*)data->Get("pruned_tau21");
  pruned_tau21_data->SetTitle("DATA prunedmass vs tau21");
  pruned_tau21_data->GetYaxis()->SetTitle("tau21");
  pruned_tau21_data->GetXaxis()->SetTitle("prunedmass");
  pruned_tau21_data->Draw();

  cout<<"pruned_tau21_data:"<<(pruned_tau21_data->GetCorrelationFactor())<<endl;

  c1->cd(3);

  TH2F* pruned_CSV_MC = (TH2F*)MC->Get("pruned_CSV");
  pruned_CSV_MC->SetTitle("MC prunedmass vs CSV");
  pruned_CSV_MC->GetYaxis()->SetTitle("CSV");
  pruned_CSV_MC->GetXaxis()->SetTitle("prunedmass");
  pruned_CSV_MC->Draw();

  cout<<"pruned_CSV_MC:"<<(pruned_CSV_MC->GetCorrelationFactor())<<endl;

  c1->cd(4);

  TH2F* pruned_CSV_data = (TH2F*)data->Get("pruned_CSV");
  pruned_CSV_data->SetTitle("DATA prunedmass vs CSV");
  pruned_CSV_data->GetYaxis()->SetTitle("CSV");
  pruned_CSV_data->GetXaxis()->SetTitle("prunedmass");
  pruned_CSV_data->Draw();

  cout<<"pruned_CSV_data:"<<(pruned_CSV_data->GetCorrelationFactor())<<endl;

  c1->cd(5);

  TH2F* tau21_CSV_MC = (TH2F*)MC->Get("tau21_CSV");
  tau21_CSV_MC->SetTitle("MC tau21 vs CSV");
  tau21_CSV_MC->GetYaxis()->SetTitle("CSV");
  tau21_CSV_MC->GetXaxis()->SetTitle("tau21");
  tau21_CSV_MC->Draw();
  
  cout<<"tau21_CSV_MC:"<<(tau21_CSV_MC->GetCorrelationFactor())<<endl;


  c1->cd(6);

  TH2F* tau21_CSV_data = (TH2F*)data->Get("tau21_CSV");
  tau21_CSV_data->SetTitle("DATA tau21 vs CSV");
  tau21_CSV_data->GetYaxis()->SetTitle("CSV");
  tau21_CSV_data->GetXaxis()->SetTitle("tau21");
  tau21_CSV_data->Draw();

  cout<<"tau21_CSV_data:"<<(tau21_CSV_data->GetCorrelationFactor())<<endl;

  
  gSystem->ProcessEvents();
  TImage *img1 = TImage::Create();
  img1->FromPad(c1);
  img1->WriteImage(outputFile.data());
  delete c1;
  delete img1;



}

