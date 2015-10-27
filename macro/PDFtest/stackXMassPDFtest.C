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


using namespace std;

void stackXMassPDFtest(string inputFile, string outputFile){


  TFile *rootfile    = TFile::Open(inputFile.data());

  TH1D *hzy0   = (TH1D*)(rootfile->Get("h_sigXMassPDF0"));
  TH1D *hzy1   = (TH1D*)(rootfile->Get("h_sigXMassPDF1"));
  TH1D *hzy2   = (TH1D*)(rootfile->Get("h_sigXMassPDF2"));
  TH1D *hzy3   = (TH1D*)(rootfile->Get("h_sigXMassPDF3"));
  TH1D *hzy4   = (TH1D*)(rootfile->Get("h_sigXMassPDF4"));


  gStyle->SetOptStat(0);
  gStyle->SetPadGridY(kTRUE);
  gStyle->SetPadGridX(kTRUE);



  TCanvas* c1 = new TCanvas("c1", "", 0, 0, 750, 750);


  hzy0->SetLineColor(kOrange+6);
  hzy1->SetLineColor(kAzure);
  hzy2->SetLineColor(kGreen+3);
  hzy3->SetLineColor(kViolet+2);
  hzy4->SetLineColor(kBlack);
  
  hzy0->Scale(1/hzy0->Integral());
  hzy1->Scale(1/hzy1->Integral());
  hzy2->Scale(1/hzy2->Integral());
  hzy3->Scale(1/hzy3->Integral());
  hzy4->Scale(1/hzy4->Integral());

  hzy1->Draw("histe");
  hzy0->Draw("histesame");
  hzy2->Draw("histesame");
  hzy3->Draw("histesame");
  hzy4->Draw("histesame");


  TLegend *leg = new TLegend(0.73, 0.68, 0.98, 0.98);

  leg->SetFillStyle(1001);
  leg->SetFillColor(10);
  leg->SetBorderSize(1);
  leg->AddEntry(hzy0, "CTEQ6L1", "f");
  leg->AddEntry(hzy1, "MSTW2008lo68cl", "f");
  leg->AddEntry(hzy2, "NNPDF21_lo_as_0119_100", "f");
  leg->AddEntry(hzy3, "MSTW2008nlo68cl", "f");
  leg->AddEntry(hzy4, "NNPDF21_nlo_collider_as_0118", "f");
  leg->Draw("same");



  c1->SaveAs(outputFile.data());


}




