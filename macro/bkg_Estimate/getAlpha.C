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


Double_t scale1 = 876.225 / (totalNEvent1 / crossSection1); // DYJetsToLL_PtZ-70To100
Double_t scale2 = 876.225 / (totalNEvent2 / crossSection2); // DYJetsToLL_PtZ100
Double_t scale3 = 876.225 / (totalNEvent3 / crossSection3); // TTbar


void myPlot(TH1D*, TH1D*, TH1D*);
void alpha(TH1D*, TH1D*, TH1D*,TH1D*, TH1D*, TH1D*);


void getAlpha(){

  cout<<"scale1:"<<scale1<<endl;
  cout<<"scale2:"<<scale2<<endl;
  cout<<"scale3:"<<scale3<<endl;


  TFile *f1e = TFile::Open("rootfile/delpanj_v2_DYJetsToLL_PtZ-70To100_ee.root");
  TFile *f2e = TFile::Open("rootfile/delpanj_v2_DYJetsToLL_PtZ-100_ee.root");
  TFile *f3e = TFile::Open("rootfile/delpanj_v2_TTTo2L2Nu2B_ee.root");
  TFile *f1m = TFile::Open("rootfile/delpanj_v2_DYJetsToLL_PtZ-70To100_mm.root");
  TFile *f2m = TFile::Open("rootfile/delpanj_v2_DYJetsToLL_PtZ-100_mm.root");
  TFile *f3m = TFile::Open("rootfile/delpanj_v2_TTTo2L2Nu2B_mm.root");
  
  




  gStyle->SetOptStat(0);
  //gStyle->SetPadGridY(kTRUE);
  //gStyle->SetPadGridX(kTRUE);


  
  TCanvas* c1 = new TCanvas("c1", "", 0, 0, 1600, 800);

  c1->Divide(3,2);

  //-------------------------------------------//


  
  c1->cd(1);
  myPlot( ((TH1D*)(f1e->Get("h_sbXMass"))), 
	  ((TH1D*)(f2e->Get("h_sbXMass"))), 
	  ((TH1D*)(f3e->Get("h_sbXMass")))
	  );
  

  

  //-------------------------------------------//
  
  c1->cd(2);
  myPlot( ((TH1D*)(f1e->Get("h_sigXMass"))),
          ((TH1D*)(f2e->Get("h_sigXMass"))),
          ((TH1D*)(f3e->Get("h_sigXMass")))
	  );
  
  
  //--------------------------------------------//


  c1->cd(3);
  alpha( ((TH1D*)(f1e->Get("h_sigXMass"))),
	 ((TH1D*)(f2e->Get("h_sigXMass"))),
	 ((TH1D*)(f3e->Get("h_sigXMass"))),
	 ((TH1D*)(f1e->Get("h_sbXMass"))),
	 ((TH1D*)(f2e->Get("h_sbXMass"))),
	 ((TH1D*)(f3e->Get("h_sbXMass")))
	 );
  
  //-------------------------------------------//

  c1->cd(4);
  myPlot( ((TH1D*)(f1m->Get("h_sbXMass"))),
          ((TH1D*)(f2m->Get("h_sbXMass"))),
          ((TH1D*)(f3m->Get("h_sbXMass")))
          );




  //-------------------------------------------//                                                                     

  c1->cd(5);
  myPlot( ((TH1D*)(f1m->Get("h_sigXMass"))),
          ((TH1D*)(f2m->Get("h_sigXMass"))),
          ((TH1D*)(f3m->Get("h_sigXMass")))
          );

  //------------------------------------------//



  c1->cd(6);
  alpha( ((TH1D*)(f1m->Get("h_sigXMass"))),
         ((TH1D*)(f2m->Get("h_sigXMass"))),
         ((TH1D*)(f3m->Get("h_sigXMass"))),
         ((TH1D*)(f1m->Get("h_sbXMass"))),
         ((TH1D*)(f2m->Get("h_sbXMass"))),
         ((TH1D*)(f3m->Get("h_sbXMass")))
         );










  

  gSystem->ProcessEvents();
  TImage *img1 = TImage::Create();
  img1->FromPad(c1);
  img1->WriteImage("h_getAlpha.png");
  delete c1;
  delete img1;



  


}



void myPlot(TH1D* h_dy70, TH1D* h_dy100, TH1D* h_ttbar){


  const Float_t varBins[] = {840,920,1000,1100,1250,1400,1600,1800,2000,2200,2400};
  Int_t nvarBins = sizeof(varBins)/sizeof(varBins[0])-1;


  TH1D* h_bkg = new TH1D("h_bkg","",nvarBins,varBins);

  h_bkg->Sumw2();

  h_bkg->Add(h_dy70,scale1);
  h_bkg->Add(h_dy100,scale2);
  h_bkg->Add(h_ttbar,scale3);

  h_bkg->GetXaxis()->SetTitle("M_{X} [GeV]");
  h_bkg->Draw(); 



}



void alpha(TH1D* h_dy70, TH1D* h_dy100, TH1D* h_ttbar, TH1D* h_dy70sb, TH1D* h_dy100sb, TH1D* h_ttbarsb){


  const Float_t varBins[] = {840,920,1000,1100,1250,1400,1600,1800,2000,2200,2400};
  Int_t nvarBins = sizeof(varBins)/sizeof(varBins[0])-1;


  TH1D* h_bkg_sig = new TH1D("h_bkg_sig","",nvarBins,varBins);
  TH1D* h_bkg_sb = new TH1D("h_bkg_sb","",nvarBins,varBins);
  TH1D* h_alpha = new TH1D("h_alpha","Alpha Ratio",nvarBins,varBins);


  h_bkg_sig->Sumw2();
  h_bkg_sb->Sumw2();
  h_alpha->Sumw2();


  h_bkg_sig->Add(h_dy70,scale1);
  h_bkg_sig->Add(h_dy100,scale2);
  h_bkg_sig->Add(h_ttbar,scale3);
  h_bkg_sb->Add(h_dy70sb,scale1);
  h_bkg_sb->Add(h_dy100sb,scale2);
  h_bkg_sb->Add(h_ttbarsb,scale3);


  

  h_alpha->Divide(h_bkg_sig, h_bkg_sb);
  h_alpha->GetXaxis()->SetTitle("M_{X} [GeV]");
  h_alpha->SetMarkerStyle(8);
  h_alpha->SetMarkerSize(1);
  h_alpha->Draw();


  cout<<"9:"<<(h_alpha->GetBinError(9))/(h_alpha->GetBinContent(9))<<" 10:"<<(h_alpha->GetBinError(10))/(h_alpha->GetBinContent(10))<<endl;




}


