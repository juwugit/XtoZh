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



// data El
Double_t el_data_lumi = (876.225+4412+7050);
Double_t scale1e = el_data_lumi / (totalNEvent1 / crossSection1); // DYJetsToLL_PtZ-70To100
Double_t scale2e = el_data_lumi / (totalNEvent2 / crossSection2); // DYJetsToLL_PtZ100
Double_t scale3e = el_data_lumi / (totalNEvent3 / crossSection3); // TTbar



void myPlotE(TH1D*, TH1D*, TH1D*, TH1D*, TH1D*, TH1D*);
void myRatioE(TH1D*, TH1D*, TH1D*, TH1D*,TH1D*,TH1D*, Double_t , Double_t );


void stackJetID(){


  TFile *b1e = TFile::Open("delpanj_v3_DYJetsToLL_PtZ-70To100_ee.root");
  TFile *b2e = TFile::Open("delpanj_v3_DYJetsToLL_PtZ-100_ee.root");
  TFile *b3e = TFile::Open("delpanj_v3_TTTo2L2Nu2B_ee.root");

  TFile *Ae = TFile::Open("delpanj_v3_data_DoubleEl_A.root");
  TFile *Be = TFile::Open("delpanj_v3_data_DoubleEl_B.root");
  TFile *Ce = TFile::Open("delpanj_v3_data_DoubleEl_C.root");





  gStyle->SetOptStat(0);
  gStyle->SetPadGridY(kTRUE);
  gStyle->SetPadGridX(kTRUE);


  
  TCanvas* c1 = new TCanvas("c1", "", 0, 0, 1500, 750);

  c1->Divide(2,2);

  //-------------------------------------------//

  c1->cd(1);
  myPlotE( ((TH1D*)(b1e->Get("h_CA8jetMuEF"))), 
	   ((TH1D*)(b2e->Get("h_CA8jetMuEF"))), 
	   ((TH1D*)(b3e->Get("h_CA8jetMuEF"))), 
	   ((TH1D*)(Ae->Get("h_CA8jetMuEF"))),
	   ((TH1D*)(Be->Get("h_CA8jetMuEF"))),
	   ((TH1D*)(Ce->Get("h_CA8jetMuEF")))
	   );
  
  //gPad->SetRightMargin(0.02);

  //-------------------------------------------//


  c1->cd(2);
  myPlotE( ((TH1D*)(b1e->Get("h_CA8jetPhoEF"))),
           ((TH1D*)(b2e->Get("h_CA8jetPhoEF"))),
           ((TH1D*)(b3e->Get("h_CA8jetPhoEF"))),
           ((TH1D*)(Ae->Get("h_CA8jetPhoEF"))),
           ((TH1D*)(Be->Get("h_CA8jetPhoEF"))),
           ((TH1D*)(Ce->Get("h_CA8jetPhoEF")))
           );

  
  //gPad->SetRightMargin(0.02);
  //gPad->SetLeftMargin(0.07);


  
  //-------------------------------------------//

  c1->cd(3);
  myRatioE( ((TH1D*)(b1e->Get("h_CA8jetMuEF"))),
	    ((TH1D*)(b2e->Get("h_CA8jetMuEF"))),
	    ((TH1D*)(b3e->Get("h_CA8jetMuEF"))),
	    ((TH1D*)(Ae->Get("h_CA8jetMuEF"))),
	    ((TH1D*)(Be->Get("h_CA8jetMuEF"))),
	    ((TH1D*)(Ce->Get("h_CA8jetMuEF"))),
	    0,1);
  
  //gPad->SetTickx();
  //gPad->SetRightMargin(0.02);



  //-------------------------------------------//
  

  c1->cd(4);
  myRatioE( ((TH1D*)(b1e->Get("h_CA8jetPhoEF"))),
            ((TH1D*)(b2e->Get("h_CA8jetPhoEF"))),
            ((TH1D*)(b3e->Get("h_CA8jetPhoEF"))), 
            ((TH1D*)(Ae->Get("h_CA8jetPhoEF"))),
            ((TH1D*)(Be->Get("h_CA8jetPhoEF"))),
            ((TH1D*)(Ce->Get("h_CA8jetPhoEF"))),
            0,1);

  
  
  //gPad->SetTickx();
  //gPad->SetRightMargin(0.02);
  //gPad->SetLeftMargin(0.07);



  gSystem->ProcessEvents();
  TImage *img1 = TImage::Create();
  img1->FromPad(c1);
  img1->WriteImage("h_CA8jetMuPhoEF.png");
  delete c1;
  delete img1;


  //-------------------------------------------//

  

  
  TCanvas* c3 = new TCanvas("c3", "", 0, 0, 1500, 750);

  c3->Divide(2,2);

  //-------------------------------------------//

  c3->cd(1);
  myPlotE( ((TH1D*)(b1e->Get("h_CA8jetCEmEF"))), 
	   ((TH1D*)(b2e->Get("h_CA8jetCEmEF"))), 
	   ((TH1D*)(b3e->Get("h_CA8jetCEmEF"))), 
	   ((TH1D*)(Ae->Get("h_CA8jetCEmEF"))),
	   ((TH1D*)(Be->Get("h_CA8jetCEmEF"))),
	   ((TH1D*)(Ce->Get("h_CA8jetCEmEF")))
	   );
  
  //gPad->SetRightMargin(0.02);

  //-------------------------------------------//
  

  c3->cd(2);
  myPlotE( ((TH1D*)(b1e->Get("h_CA8jetCHadEF"))),
           ((TH1D*)(b2e->Get("h_CA8jetCHadEF"))),
           ((TH1D*)(b3e->Get("h_CA8jetCHadEF"))),
           ((TH1D*)(Ae->Get("h_CA8jetCHadEF"))),
           ((TH1D*)(Be->Get("h_CA8jetCHadEF"))),
           ((TH1D*)(Ce->Get("h_CA8jetCHadEF")))
           );



  
  //gPad->SetRightMargin(0.02);
  //gPad->SetLeftMargin(0.07);

  
  //-------------------------------------------//

  c3->cd(3);
  myRatioE( ((TH1D*)(b1e->Get("h_CA8jetCEmEF"))),
	    ((TH1D*)(b2e->Get("h_CA8jetCEmEF"))),
	    ((TH1D*)(b3e->Get("h_CA8jetCEmEF"))),
	    ((TH1D*)(Ae->Get("h_CA8jetCEmEF"))),
	    ((TH1D*)(Be->Get("h_CA8jetCEmEF"))),
	    ((TH1D*)(Ce->Get("h_CA8jetCEmEF"))),
	    0,1);
  
  //gPad->SetTickx();
  //gPad->SetRightMargin(0.02);



  //-------------------------------------------//
  

  c3->cd(4);
  myRatioE( ((TH1D*)(b1e->Get("h_CA8jetCHadEF"))),
            ((TH1D*)(b2e->Get("h_CA8jetCHadEF"))),
            ((TH1D*)(b3e->Get("h_CA8jetCHadEF"))),
            ((TH1D*)(Ae->Get("h_CA8jetCHadEF"))),
            ((TH1D*)(Be->Get("h_CA8jetCHadEF"))),
            ((TH1D*)(Ce->Get("h_CA8jetCHadEF"))),
            0,1);


  
  
  //gPad->SetTickx();
  //gPad->SetRightMargin(0.02);
  //gPad->SetLeftMargin(0.07);



  gSystem->ProcessEvents();
  TImage *img3 = TImage::Create();
  img3->FromPad(c3);
  img3->WriteImage("h_CA8jetCEmHadEF.png");
  delete c3;
  delete img3;


  //-------------------------------------------//


  

  TCanvas* c4 = new TCanvas("c4", "", 0, 0, 750, 750);

  c4->Divide(1,2);

  //-------------------------------------------//

  c4->cd(1);
  myPlotE( ((TH1D*)(b1e->Get("h_CA8jetNHadEF"))), 
	   ((TH1D*)(b2e->Get("h_CA8jetNHadEF"))), 
	   ((TH1D*)(b3e->Get("h_CA8jetNHadEF"))), 
	   ((TH1D*)(Ae->Get("h_CA8jetNHadEF"))),
	   ((TH1D*)(Be->Get("h_CA8jetNHadEF"))),
	   ((TH1D*)(Ce->Get("h_CA8jetNHadEF")))
      	   );
  



  c4->cd(2);
  myRatioE( ((TH1D*)(b1e->Get("h_CA8jetNHadEF"))),
	    ((TH1D*)(b2e->Get("h_CA8jetNHadEF"))),
	    ((TH1D*)(b3e->Get("h_CA8jetNHadEF"))),
	    ((TH1D*)(Ae->Get("h_CA8jetNHadEF"))),
	    ((TH1D*)(Be->Get("h_CA8jetNHadEF"))),
	    ((TH1D*)(Ce->Get("h_CA8jetNHadEF"))),
	    0,1);
  
  //gPad->SetTickx();




  gSystem->ProcessEvents();
  TImage *img4 = TImage::Create();
  img4->FromPad(c4);
  img4->WriteImage("h_CA8jetNHadEF.png");
  delete c4;
  delete img4;





}



void myPlotE(TH1D* h_dy70e, TH1D* h_dy100e, TH1D* h_ttbare, TH1D* h_dataA, TH1D* h_dataB, TH1D* h_dataC){


  //  bkg
  h_dy70e->Scale(scale1e);
  h_dy70e->SetFillColor(kCyan-4);
  h_dy70e->SetLineColor(kBlack);

  h_dy100e->Scale(scale2e);
  h_dy100e->SetFillColor(kAzure+9);
  h_dy100e->SetLineColor(kBlack);

  h_ttbare->Scale(scale3e);
  h_ttbare->SetFillColor(kOrange+8);
  h_ttbare->SetLineColor(kBlack);



  THStack* h_stack = new THStack("h_stack", "");
  h_stack->Add(h_dy70e);
  h_stack->Add(h_dy100e);
  h_stack->Add(h_ttbare);



  // data
  TH1D* h_data = (TH1D*)h_dataA->Clone("h_data");
  h_data->Reset();
  h_data->Add(h_dataA,1);
  h_data->Add(h_dataB,1);
  h_data->Add(h_dataC,1);


  h_data->SetLineColor(1);
  h_data->SetMarkerStyle(8);
  h_data->SetMarkerSize(1);

  //Double_t ymin = -0.05*(h_data->GetMaximum());

  //h_data->SetMinimum(ymin);
  //h_data->SetLabelSize(0);
  //h_data->SetXTitle("");


  //h_data->Draw("e1"); 
  h_stack->Draw("histe");
  h_data->Draw("e1same");



  TLegend *leg = new TLegend(0.73, 0.78, 0.98, 0.99);

  leg->SetFillStyle(1001);
  leg->SetFillColor(10);
  leg->SetBorderSize(1);
  leg->AddEntry(h_ttbare,"TTTo2L2Nu2B.root", "f"); 
  leg->AddEntry(h_dy100e,"DYJetsToLL_PtZ-100", "f"); 
  leg->AddEntry(h_dy70e, "DYJetsToLL_PtZ-70To100", "f"); 
  leg->AddEntry(h_data, "Data", "lp");
  leg->Draw();

} // myplotE








void myRatioE(TH1D* h_dy70e, TH1D* h_dy100e, TH1D* h_ttbare, TH1D* h_dataA,  TH1D* h_dataB, TH1D* h_dataC , Double_t min , Double_t max){


  
  TH1D* h_bkg = (TH1D*)h_dy100e->Clone("h_bkg");
  h_bkg->Reset();
  //h_bkg->Sumw2();
  h_bkg->Add(h_dy70e,1);
  h_bkg->Add(h_dy100e,1);
  h_bkg->Add(h_ttbare,1);



  TH1D* h_data = (TH1D*)h_dataA->Clone("h_data");
  h_data->Reset();
  h_data->Add(h_dataA,1);
  h_data->Add(h_dataB,1);
  h_data->Add(h_dataC,1);


  TH1D* h_ratio = (TH1D*)h_dy100e->Clone("h_ratio");
  h_ratio->Reset();
  //h_ratio->Sumw2();


  Int_t nbin=h_ratio->GetNbinsX();
  Double_t ratio[nbin];
  Double_t error[nbin];
  Double_t numer_nbincontent[nbin];
  Double_t denom_nbincontent[nbin];
  Double_t numer_binerror[nbin];
  Double_t denom_binerror[nbin];

  
  for(Int_t i=1; i<=nbin; i++){


    numer_nbincontent[i] = h_data->GetBinContent(i);
    denom_nbincontent[i] = h_bkg->GetBinContent(i);
    numer_binerror[i] = h_data->GetBinError(i);
    denom_binerror[i] = h_bkg->GetBinError(i);


    if(denom_nbincontent[i]<=0 || numer_nbincontent[i]<=0) continue; 
    if(denom_binerror[i]<=0 || numer_binerror[i]<=0) continue;


    ratio[i] = numer_nbincontent[i]/denom_nbincontent[i];
    error[i] = (ratio[i])*sqrt(pow(numer_binerror[i]/numer_nbincontent[i],2)+pow(denom_binerror[i]/denom_nbincontent[i],2));


    h_ratio->SetBinContent(i,ratio[i]);
    h_ratio->SetBinError(i,error[i]);




  }
  
 
  //h_ratio->SetLineColor(1);
  h_ratio->SetMarkerStyle(8);
  h_ratio->SetMarkerSize(1);

  h_ratio->GetXaxis()->SetRangeUser(min,max);
  h_ratio->GetYaxis()->SetRangeUser(0,2);
  h_ratio->SetYTitle("data/MC");
  h_ratio->Draw();


  TLine* l2 = new TLine(min,1.,max,1.);
  l2->SetLineColor(4);
  l2->SetLineStyle(3);
  l2->Draw("same");


} // myratioE





