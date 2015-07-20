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



void stackVariables(std::string inputFile1, std::string inputFile2, std::string outputFile1, std::string outputFile2){


  TFile *madgraph = TFile::Open(inputFile1.data());
  TFile *sherpa = TFile::Open(inputFile2.data());


  gStyle->SetOptStat(0);



  TCanvas* c1 = new TCanvas("c1", "", 0, 0, 1200, 600);

  c1->Divide(2,1);


  c1->cd(1);

  TH1F* mad_sbXMass = (TH1F*)madgraph->Get("h_sbXMass");
  TH1F* she_sbXMass = (TH1F*)sherpa->Get("h_sbXMass");
  mad_sbXMass->Scale(1/(mad_sbXMass->Integral() ) );
  she_sbXMass->Scale(1/(she_sbXMass->Integral() ) );

  she_sbXMass->SetTitle("sideband XMass: madgraph vs sherpa");
  she_sbXMass->GetXaxis()->SetTitle("XMass (GeV)");
  she_sbXMass->SetFillStyle(3004);
  she_sbXMass->SetFillColor(2);
  she_sbXMass->SetLineColor(2);

  she_sbXMass->Draw("histe");
  mad_sbXMass->Draw("histesame");


  TLegend* leg = new TLegend(0.5,0.7,0.8,0.8);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->AddEntry(mad_sbXMass,"MadGraph","lep");
  leg->AddEntry(she_sbXMass,"Sherpa","F");
  leg->Draw("same");


  c1->cd(2);

  TH1F* mad_sigXMass = (TH1F*)madgraph->Get("h_sigXMass");
  TH1F* she_sigXMass = (TH1F*)sherpa->Get("h_sigXMass");
  mad_sigXMass->Scale(1/(mad_sigXMass->Integral() ) );
  she_sigXMass->Scale(1/(she_sigXMass->Integral() ) );

  she_sigXMass->SetTitle("signal region XMass: madgraph vs sherpa");
  she_sigXMass->GetXaxis()->SetTitle("XMass (GeV)");
  she_sigXMass->SetFillStyle(3004);
  she_sigXMass->SetFillColor(2);
  she_sigXMass->SetLineColor(2);
  
  she_sigXMass->Draw("histe");
  mad_sigXMass->Draw("histesame");


  
  gSystem->ProcessEvents();
  TImage *img1 = TImage::Create();
  img1->FromPad(c1);
  img1->WriteImage(outputFile1.data());
  delete c1;
  delete img1;


  //--------------------------------------------------------------------

  


  TCanvas* c2 = new TCanvas("c2", "", 0, 0, 1200, 1200);

  c2->Divide(2,2);

  c2->cd(1);

  TH1F* mad_sbCA8CSV = (TH1F*)madgraph->Get("h_sbCA8CSV");
  TH1F* she_sbCA8CSV = (TH1F*)sherpa->Get("h_sbCA8CSV");
  mad_sbCA8CSV->Scale(1/(mad_sbCA8CSV->Integral() ) );
  she_sbCA8CSV->Scale(1/(she_sbCA8CSV->Integral() ) );

  mad_sbCA8CSV->SetTitle("sideband CA8jetCSV: madgraph vs sherpa");
  mad_sbCA8CSV->GetXaxis()->SetTitle("CA8jetCSV");
  she_sbCA8CSV->SetFillStyle(3004);
  she_sbCA8CSV->SetFillColor(2);
  she_sbCA8CSV->SetLineColor(2);

  mad_sbCA8CSV->Draw("histe");
  she_sbCA8CSV->Draw("histesame");


  TLegend* leg2 = new TLegend(0.5,0.7,0.8,0.8);
  leg2->SetBorderSize(0);
  leg2->SetFillColor(0);
  leg2->AddEntry(mad_sbCA8CSV,"MadGraph","lep");
  leg2->AddEntry(she_sbCA8CSV,"Sherpa","F");
  leg2->Draw("same");


  c2->cd(2);

  TH1F* mad_sigCA8CSV = (TH1F*)madgraph->Get("h_sigCA8CSV");
  TH1F* she_sigCA8CSV = (TH1F*)sherpa->Get("h_sigCA8CSV");
  mad_sigCA8CSV->Scale(1/(mad_sigCA8CSV->Integral() ) );
  she_sigCA8CSV->Scale(1/(she_sigCA8CSV->Integral() ) );

  mad_sigCA8CSV->SetTitle("signal region CA8jetCSV: madgraph vs sherpa");
  mad_sigCA8CSV->GetXaxis()->SetTitle("CA8jetCSV");
  she_sigCA8CSV->SetFillStyle(3004);
  she_sigCA8CSV->SetFillColor(2);
  she_sigCA8CSV->SetLineColor(2);

  mad_sigCA8CSV->Draw("histe");
  she_sigCA8CSV->Draw("histesame");



  c2->cd(3);

  TH1F* mad_sbSubCSV = (TH1F*)madgraph->Get("h_sbSubCSV");
  TH1F* she_sbSubCSV = (TH1F*)sherpa->Get("h_sbSubCSV");
  mad_sbSubCSV->Scale(1/(mad_sbSubCSV->Integral() ) );
  she_sbSubCSV->Scale(1/(she_sbSubCSV->Integral() ) );

  mad_sbSubCSV->SetTitle("sideband SubjetCSV: madgraph vs sherpa");
  mad_sbSubCSV->GetXaxis()->SetTitle("SubjetCSV");
  she_sbSubCSV->SetFillStyle(3004);
  she_sbSubCSV->SetFillColor(2);
  she_sbSubCSV->SetLineColor(2);

  mad_sbSubCSV->Draw("histe");
  she_sbSubCSV->Draw("histesame");


  c2->cd(4);

  TH1F* mad_sigSubCSV = (TH1F*)madgraph->Get("h_sigSubCSV");
  TH1F* she_sigSubCSV = (TH1F*)sherpa->Get("h_sigSubCSV");
  mad_sigSubCSV->Scale(1/(mad_sigSubCSV->Integral() ) );
  she_sigSubCSV->Scale(1/(she_sigSubCSV->Integral() ) );

  mad_sigSubCSV->SetTitle("signal region SubjetCSV: madgraph vs sherpa");
  mad_sigSubCSV->GetXaxis()->SetTitle("SubjetCSV");
  she_sigSubCSV->SetFillStyle(3004);
  she_sigSubCSV->SetFillColor(2);
  she_sigSubCSV->SetLineColor(2);

  mad_sigSubCSV->Draw("histe");
  she_sigSubCSV->Draw("histesame");




  gSystem->ProcessEvents();
  TImage *img2 = TImage::Create();
  img2->FromPad(c2);
  img2->WriteImage(outputFile2.data());
  delete c2;
  delete img2;

 

}

