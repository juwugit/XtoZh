#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <TPad.h>
#include <TH1D.h>
#include <TF1.h>
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



void stackCorVariables(std::string inputFile1, std::string inputFile2, std::string outputFile1, std::string outputFile2){


  TFile *data = TFile::Open(inputFile1.data());
  TFile *MC = TFile::Open(inputFile2.data());

  //gStyle->SetOptStat(0);




  TCanvas* c1 = new TCanvas("c1", "", 0, 0, 800, 2000);

  c1->Divide(2,4);


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



  c1->cd(7);

  TH2F* tau21_CSV_MC_sb = (TH2F*)MC->Get("tau21_CSV_sb");
  tau21_CSV_MC_sb->SetTitle("MC tau21 vs CSV (sideband)");
  tau21_CSV_MC_sb->GetYaxis()->SetTitle("CSV");
  tau21_CSV_MC_sb->GetXaxis()->SetTitle("tau21");
  tau21_CSV_MC_sb->Draw();
  
  cout<<"tau21_CSV_MC_sb:"<<(tau21_CSV_MC_sb->GetCorrelationFactor())<<endl;


  c1->cd(8);

  TH2F* tau21_CSV_data_sb = (TH2F*)data->Get("tau21_CSV_sb");
  tau21_CSV_data_sb->SetTitle("DATA tau21 vs CSV (sideband)");
  tau21_CSV_data_sb->GetYaxis()->SetTitle("CSV");
  tau21_CSV_data_sb->GetXaxis()->SetTitle("tau21");
  tau21_CSV_data_sb->Draw();

  cout<<"tau21_CSV_data_sb:"<<(tau21_CSV_data_sb->GetCorrelationFactor())<<endl;

  
  gSystem->ProcessEvents();
  TImage *img1 = TImage::Create();
  img1->FromPad(c1);
  img1->WriteImage(outputFile1.data());
  delete c1;
  delete img1;


  //--------------------------------------------------------------------




  TCanvas* c2 = new TCanvas("c2", "", 0, 0, 800, 2000);

  c2->Divide(2,4);

  c2->cd(1);

  TH1F* CSV_MC_sig = (TH1F*)MC->Get("CSV_sig");
  TH1F* CSV_MC_sb = (TH1F*)MC->Get("CSV_sb");

  CSV_MC_sig->Scale(1/(CSV_MC_sig->Integral()));
  CSV_MC_sb->Scale(1/(CSV_MC_sb->Integral()));

  CSV_MC_sig->SetTitle("MC fatjet CSV: signal(red) vs sideband");
  CSV_MC_sig->GetXaxis()->SetTitle("CSV");
  CSV_MC_sig->SetFillColor(2);
  CSV_MC_sig->SetLineColor(2);
  CSV_MC_sig->SetFillStyle(3004);

  CSV_MC_sb->Draw("histe");
  CSV_MC_sig->Draw("histesame");



  c2->cd(2);

  TH1F* CSV_data_sig = (TH1F*)data->Get("CSV_sig");
  TH1F* CSV_data_sb = (TH1F*)data->Get("CSV_sb");

  CSV_data_sig->Scale(1/(CSV_data_sig->Integral()));
  CSV_data_sb->Scale(1/(CSV_data_sb->Integral()));

  CSV_data_sig->SetTitle("DATA fatjet CSV: signal(red) vs sideband");
  CSV_data_sig->GetXaxis()->SetTitle("CSV");
  CSV_data_sig->SetFillColor(2);
  CSV_data_sig->SetLineColor(2);
  CSV_data_sig->SetFillStyle(3004);

  CSV_data_sig->Draw("histe");
  CSV_data_sb->Draw("histesame");


  c2->cd(3);

  TH1F* alpha_MC = (TH1F*)MC->Get("alpha");
  
  alpha_MC->SetTitle("MC alpha ratio: fatjet");
  alpha_MC->GetXaxis()->SetTitle("CSV");
  
  alpha_MC->Draw();



  c2->cd(4);

  TH1F* alpha_data = (TH1F*)data->Get("alpha");
  
  alpha_data->SetTitle("DATA alpha ratio: fatjet");
  alpha_data->GetXaxis()->SetTitle("CSV");
  
  alpha_data->Draw();




  c2->cd(5);

  TH1F* CSV_MC_sig_sub = (TH1F*)MC->Get("CSV_sig_sub");
  TH1F* CSV_MC_sb_sub = (TH1F*)MC->Get("CSV_sb_sub");

  CSV_MC_sig_sub->Scale(1/(CSV_MC_sig_sub->Integral()));
  CSV_MC_sb_sub->Scale(1/(CSV_MC_sb_sub->Integral()));

  CSV_MC_sig_sub->SetTitle("MC subjet CSV: signal(red) vs sideband");
  CSV_MC_sig_sub->GetXaxis()->SetTitle("CSV");
  CSV_MC_sig_sub->SetFillColor(2);
  CSV_MC_sig_sub->SetLineColor(2);
  CSV_MC_sig_sub->SetFillStyle(3004);

  CSV_MC_sb_sub->Draw("histe");
  CSV_MC_sig_sub->Draw("histesame");



  c2->cd(6);

  TH1F* CSV_data_sig_sub = (TH1F*)data->Get("CSV_sig_sub");
  TH1F* CSV_data_sb_sub = (TH1F*)data->Get("CSV_sb_sub");

  CSV_data_sig_sub->Scale(1/(CSV_data_sig_sub->Integral()));
  CSV_data_sb_sub->Scale(1/(CSV_data_sb_sub->Integral()));

  CSV_data_sig_sub->SetTitle("DATA subjet CSV: signal(red) vs sideband");
  CSV_data_sig_sub->GetXaxis()->SetTitle("CSV");
  CSV_data_sig_sub->SetFillColor(2);
  CSV_data_sig_sub->SetLineColor(2);
  CSV_data_sig_sub->SetFillStyle(3004);

  CSV_data_sb_sub->Draw("histe");
  CSV_data_sig_sub->Draw("histesame");



  c2->cd(7);

  TH1F* alpha_MC_sub = (TH1F*)MC->Get("alpha_sub");
  
  alpha_MC_sub->SetTitle("MC alpha ratio: subjet");
  alpha_MC_sub->GetXaxis()->SetTitle("CSV");
  
  alpha_MC_sub->Draw();



  c2->cd(8);

  TH1F* alpha_data_sub = (TH1F*)data->Get("alpha_sub");
  
  alpha_data_sub->SetTitle("DATA alpha ratio: subjet");
  alpha_data_sub->GetXaxis()->SetTitle("CSV");
  
  alpha_data_sub->Draw();








  gSystem->ProcessEvents();
  TImage *img2 = TImage::Create();
  img2->FromPad(c2);
  img2->WriteImage(outputFile2.data());
  delete c2;
  delete img2;



}

