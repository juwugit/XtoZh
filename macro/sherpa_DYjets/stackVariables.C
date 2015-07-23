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



void stackVariables(std::string inputFile1, std::string inputFile2, std::string inputFile3, std::string outputFile1, std::string outputFile2){


  TFile *madgraph = TFile::Open(inputFile1.data());
  TFile *sherpa = TFile::Open(inputFile2.data());
  TFile *data = TFile::Open(inputFile3.data());


  gStyle->SetOptStat(0);



  TCanvas* c1 = new TCanvas("c1", "", 0, 0, 1200, 600);

  c1->Divide(2,1);


  c1->cd(1);

  TH1F* mad_sbXMass = (TH1F*)madgraph->Get("h_sbXMass");
  TH1F* she_sbXMass = (TH1F*)sherpa->Get("h_sbXMass");
  TH1F* data_sbXMass = (TH1F*)data->Get("h_sbXMass");

  mad_sbXMass->Scale(1/(mad_sbXMass->Integral() ) );
  she_sbXMass->Scale(1/(she_sbXMass->Integral() ) );
  data_sbXMass->Scale(1/(data_sbXMass->Integral() ) );

  she_sbXMass->SetTitle("sideband XMass: madgraph vs sherpa");
  she_sbXMass->GetXaxis()->SetTitle("XMass (GeV)");
  she_sbXMass->SetFillStyle(3004);
  she_sbXMass->SetFillColor(2);
  she_sbXMass->SetLineColor(2);

  mad_sbXMass->SetFillStyle(3003);
  mad_sbXMass->SetFillColor(4);
  mad_sbXMass->SetLineColor(4);

  data_sbXMass->SetLineColor(1);
  data_sbXMass->SetLineWidth(2);
  data_sbXMass->SetMarkerColor(1);
  data_sbXMass->SetMarkerStyle(20);
  data_sbXMass->SetMarkerSize(1);

  she_sbXMass->Draw("histe");
  mad_sbXMass->Draw("histesame");
  data_sbXMass->Draw("esame");


  TLegend* leg = new TLegend(0.5,0.7,0.8,0.8);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->AddEntry(data_sbXMass,"data","lep");
  leg->AddEntry(mad_sbXMass,"MadGraph","F");
  leg->AddEntry(she_sbXMass,"Sherpa","F");
  leg->Draw("same");


  c1->cd(2);

  TH1F* mad_sigXMass = (TH1F*)madgraph->Get("h_sigXMass");
  TH1F* she_sigXMass = (TH1F*)sherpa->Get("h_sigXMass");
  TH1F* data_sigXMass = (TH1F*)data->Get("h_sigXMass");

  mad_sigXMass->Scale(1/(mad_sigXMass->Integral() ) );
  she_sigXMass->Scale(1/(she_sigXMass->Integral() ) );
  data_sigXMass->Scale(1/(data_sigXMass->Integral() ) );

  she_sigXMass->SetTitle("signal region XMass: madgraph vs sherpa");
  she_sigXMass->GetXaxis()->SetTitle("XMass (GeV)");
  she_sigXMass->SetFillStyle(3004);
  she_sigXMass->SetFillColor(2);
  she_sigXMass->SetLineColor(2);

  mad_sigXMass->SetFillStyle(3003);
  mad_sigXMass->SetFillColor(4);
  mad_sigXMass->SetLineColor(4);

  data_sigXMass->SetLineColor(1);
  data_sigXMass->SetLineWidth(2);
  data_sigXMass->SetMarkerColor(1);
  data_sigXMass->SetMarkerStyle(20);
  data_sigXMass->SetMarkerSize(1);

  
  she_sigXMass->Draw("histe");
  mad_sigXMass->Draw("histesame");
  data_sigXMass->Draw("esame");


  
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
  TH1F* data_sbCA8CSV = (TH1F*)data->Get("h_sbCA8CSV");

  mad_sbCA8CSV->Scale(1/(mad_sbCA8CSV->Integral() ) );
  she_sbCA8CSV->Scale(1/(she_sbCA8CSV->Integral() ) );
  data_sbCA8CSV->Scale(1/(data_sbCA8CSV->Integral() ) );

  mad_sbCA8CSV->SetTitle("sideband CA8jetCSV: madgraph vs sherpa");
  mad_sbCA8CSV->GetXaxis()->SetTitle("CA8jetCSV");
  mad_sbCA8CSV->SetFillStyle(3003);
  mad_sbCA8CSV->SetFillColor(4);
  mad_sbCA8CSV->SetLineColor(4);

  she_sbCA8CSV->SetFillStyle(3004);
  she_sbCA8CSV->SetFillColor(2);
  she_sbCA8CSV->SetLineColor(2);

  data_sbCA8CSV->SetLineColor(1);
  data_sbCA8CSV->SetLineWidth(2);
  data_sbCA8CSV->SetMarkerColor(1);
  data_sbCA8CSV->SetMarkerStyle(20);
  data_sbCA8CSV->SetMarkerSize(1);

  mad_sbCA8CSV->Draw("histe");
  she_sbCA8CSV->Draw("histesame");
  data_sbCA8CSV->Draw("esame");


  TLegend* leg2 = new TLegend(0.5,0.7,0.8,0.8);
  leg2->SetBorderSize(0);
  leg2->SetFillColor(0);
  leg2->AddEntry(data_sbCA8CSV,"data","lep");
  leg2->AddEntry(mad_sbCA8CSV,"MadGraph","F");
  leg2->AddEntry(she_sbCA8CSV,"Sherpa","F");
  leg2->Draw("same");


  c2->cd(2);

  TH1F* mad_sigCA8CSV = (TH1F*)madgraph->Get("h_sigCA8CSV");
  TH1F* she_sigCA8CSV = (TH1F*)sherpa->Get("h_sigCA8CSV");
  TH1F* data_sigCA8CSV = (TH1F*)data->Get("h_sigCA8CSV");

  mad_sigCA8CSV->Scale(1/(mad_sigCA8CSV->Integral() ) );
  she_sigCA8CSV->Scale(1/(she_sigCA8CSV->Integral() ) );
  data_sigCA8CSV->Scale(1/(data_sigCA8CSV->Integral() ) );

  data_sigCA8CSV->SetTitle("signal region CA8jetCSV: madgraph vs sherpa");
  data_sigCA8CSV->GetXaxis()->SetTitle("CA8jetCSV");

  mad_sigCA8CSV->SetFillStyle(3003);
  mad_sigCA8CSV->SetFillColor(4);
  mad_sigCA8CSV->SetLineColor(4);

  she_sigCA8CSV->SetFillStyle(3004);
  she_sigCA8CSV->SetFillColor(2);
  she_sigCA8CSV->SetLineColor(2);

  data_sigCA8CSV->SetLineColor(1);
  data_sigCA8CSV->SetLineWidth(2);
  data_sigCA8CSV->SetMarkerColor(1);
  data_sigCA8CSV->SetMarkerStyle(20);
  data_sigCA8CSV->SetMarkerSize(1);

  data_sigCA8CSV->Draw("e");
  mad_sigCA8CSV->Draw("histesame");
  she_sigCA8CSV->Draw("histesame");
  


  c2->cd(3);

  TH1F* mad_sbSubCSV = (TH1F*)madgraph->Get("h_sbSubCSV");
  TH1F* she_sbSubCSV = (TH1F*)sherpa->Get("h_sbSubCSV");
  TH1F* data_sbSubCSV = (TH1F*)data->Get("h_sbSubCSV");

  mad_sbSubCSV->Scale(1/(mad_sbSubCSV->Integral() ) );
  she_sbSubCSV->Scale(1/(she_sbSubCSV->Integral() ) );
  data_sbSubCSV->Scale(1/(data_sbSubCSV->Integral() ) );

  mad_sbSubCSV->SetTitle("sideband SubjetCSV: madgraph vs sherpa");
  mad_sbSubCSV->GetXaxis()->SetTitle("SubjetCSV");
  mad_sbSubCSV->SetFillStyle(3003);
  mad_sbSubCSV->SetFillColor(4);
  mad_sbSubCSV->SetLineColor(4);

  she_sbSubCSV->SetFillStyle(3004);
  she_sbSubCSV->SetFillColor(2);
  she_sbSubCSV->SetLineColor(2);

  data_sbSubCSV->SetLineColor(1);
  data_sbSubCSV->SetLineWidth(2);
  data_sbSubCSV->SetMarkerColor(1);
  data_sbSubCSV->SetMarkerStyle(20);
  data_sbSubCSV->SetMarkerSize(1);

  mad_sbSubCSV->Draw("histe");
  she_sbSubCSV->Draw("histesame");
  data_sbSubCSV->Draw("esame");


  c2->cd(4);

  TH1F* mad_sigSubCSV = (TH1F*)madgraph->Get("h_sigSubCSV");
  TH1F* she_sigSubCSV = (TH1F*)sherpa->Get("h_sigSubCSV");
  TH1F* data_sigSubCSV = (TH1F*)data->Get("h_sigSubCSV");

  mad_sigSubCSV->Scale(1/(mad_sigSubCSV->Integral() ) );
  she_sigSubCSV->Scale(1/(she_sigSubCSV->Integral() ) );
  data_sigSubCSV->Scale(1/(data_sigSubCSV->Integral() ) );

  mad_sigSubCSV->SetTitle("signal region SubjetCSV: madgraph vs sherpa");
  mad_sigSubCSV->GetXaxis()->SetTitle("SubjetCSV");
  mad_sigSubCSV->SetFillStyle(3003);
  mad_sigSubCSV->SetFillColor(4);
  mad_sigSubCSV->SetLineColor(4);

  she_sigSubCSV->SetFillStyle(3004);
  she_sigSubCSV->SetFillColor(2);
  she_sigSubCSV->SetLineColor(2);

  data_sigSubCSV->SetLineColor(1);
  data_sigSubCSV->SetLineWidth(2);
  data_sigSubCSV->SetMarkerColor(1);
  data_sigSubCSV->SetMarkerStyle(20);
  data_sigSubCSV->SetMarkerSize(1);

  mad_sigSubCSV->Draw("histe");
  she_sigSubCSV->Draw("histesame");
  data_sigSubCSV->Draw("esame");



  gSystem->ProcessEvents();
  TImage *img2 = TImage::Create();
  img2->FromPad(c2);
  img2->WriteImage(outputFile2.data());
  delete c2;
  delete img2;

 

}

