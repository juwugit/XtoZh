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
const Int_t totalNEvent4 = 9850431;
const Double_t crossSection1 = 63.5;
const Double_t crossSection2 = 39.4;
const Double_t crossSection3 = 25.8;
//const Double_t crossSection4 = 56.0;


// data El
Double_t el_data_lumi = (876.225+4412+7050);
Double_t scale1e = el_data_lumi / (totalNEvent1 / crossSection1); // DYJetsToLL_PtZ-70To100
Double_t scale2e = el_data_lumi / (totalNEvent2 / crossSection2); // DYJetsToLL_PtZ100
Double_t scale3e = el_data_lumi / (totalNEvent3 / crossSection3); // TTbar


// data Mu
Double_t mu_data_lumi = (876.225+4406+7017);
Double_t scale1m = mu_data_lumi / (totalNEvent1 / crossSection1); // DYJetsToLL_PtZ-70To100                       
Double_t scale2m = mu_data_lumi / (totalNEvent2 / crossSection2); // DYJetsToLL_PtZ100                           
Double_t scale3m = mu_data_lumi / (totalNEvent3 / crossSection3); // TTbar                                        



void myPlotE(TH1D*, TH1D*, TH1D*, TH1D*, TH1D*, TH1D*);
void myPlotM(TH1D*, TH1D*, TH1D*, TH1D*, TH1D*, TH1D*);
void myRatioE(TH1D*, TH1D*, TH1D*, TH1D*,TH1D*,TH1D*, Double_t , Double_t );
void myRatioM(TH1D*, TH1D*, TH1D*, TH1D*,TH1D*,TH1D*, Double_t , Double_t );


void stackJetID(){


  TFile *b1e = TFile::Open("rootfile/delpanj_v3_DYJetsToLL_PtZ-70To100_ee.root");
  TFile *b2e = TFile::Open("rootfile/delpanj_v3_DYJetsToLL_PtZ-100_ee.root");
  TFile *b3e = TFile::Open("rootfile/delpanj_v3_TTTo2L2Nu2B_ee.root");
  //TFile *b4e = TFile::Open("rootfile/delpanj_v3_WW_pythia_ee.root");

  TFile *b1m = TFile::Open("rootfile/delpanj_v3_DYJetsToLL_PtZ-70To100_mm.root");
  TFile *b2m = TFile::Open("rootfile/delpanj_v3_DYJetsToLL_PtZ-100_mm.root");
  TFile *b3m = TFile::Open("rootfile/delpanj_v3_TTTo2L2Nu2B_mm.root");
  //TFile *b4m = TFile::Open("rootfile/delpanj_v3_WW_pythia_mm.root");

  TFile *Ae = TFile::Open("rootfile/delpanj_v3_data_DoubleEl_A.root");
  TFile *Be = TFile::Open("rootfile/delpanj_v3_data_DoubleEl_B.root");
  TFile *Ce = TFile::Open("rootfile/delpanj_v3_data_DoubleEl_C.root");

  TFile *Am = TFile::Open("rootfile/delpanj_v3_data_DoubleMu_A.root");
  TFile *Bm = TFile::Open("rootfile/delpanj_v3_data_DoubleMu_B.root");
  TFile *Cm = TFile::Open("rootfile/delpanj_v3_data_DoubleMu_C.root");
  




  gStyle->SetOptStat(0);
  gStyle->SetPadGridY(kTRUE);
  gStyle->SetPadGridX(kTRUE);



  TCanvas* c1 = new TCanvas("c1", "", 0, 0, 1500, 750);

  c1->Divide(2,2,0,0);

  //-------------------------------------------//

  c1->cd(1);
  myPlotE( ((TH1D*)(b1e->Get("h_CA8jetMuEF"))), 
	   ((TH1D*)(b2e->Get("h_CA8jetMuEF"))), 
	   ((TH1D*)(b3e->Get("h_CA8jetMuEF"))), 
	   //	   ((TH1D*)(b4e->Get("h_CA8jetMuEF"))),
	   ((TH1D*)(Ae->Get("h_CA8jetMuEF"))),
	   ((TH1D*)(Be->Get("h_CA8jetMuEF"))),
	   ((TH1D*)(Ce->Get("h_CA8jetMuEF")))
	   );
  
  gPad->SetRightMargin(0.02);

  //-------------------------------------------//
  
  c1->cd(2);
  myPlotM( ((TH1D*)(b1m->Get("h_CA8jetMuEF"))),
	   ((TH1D*)(b2m->Get("h_CA8jetMuEF"))),
	   ((TH1D*)(b3m->Get("h_CA8jetMuEF"))),
	   //	   ((TH1D*)(b4m->Get("h_CA8jetMuEF"))),
	   ((TH1D*)(Am->Get("h_CA8jetMuEF"))),
	   ((TH1D*)(Bm->Get("h_CA8jetMuEF"))),
	   ((TH1D*)(Cm->Get("h_CA8jetMuEF")))
	   );
  
  gPad->SetRightMargin(0.02);
  gPad->SetLeftMargin(0.07);

  
  //-------------------------------------------//

  c1->cd(3);
  myRatioE( ((TH1D*)(b1e->Get("h_CA8jetMuEF"))),
	    ((TH1D*)(b2e->Get("h_CA8jetMuEF"))),
	    ((TH1D*)(b3e->Get("h_CA8jetMuEF"))),
	    //	    ((TH1D*)(b4e->Get("h_CA8jetMuEF"))),
	    ((TH1D*)(Ae->Get("h_CA8jetMuEF"))),
	    ((TH1D*)(Be->Get("h_CA8jetMuEF"))),
	    ((TH1D*)(Ce->Get("h_CA8jetMuEF"))),
	    0,1);
  
  gPad->SetTickx();
  gPad->SetRightMargin(0.02);



  //-------------------------------------------//
  
  c1->cd(4);
  myRatioM( ((TH1D*)(b1m->Get("h_CA8jetMuEF"))),
            ((TH1D*)(b2m->Get("h_CA8jetMuEF"))),
            ((TH1D*)(b3m->Get("h_CA8jetMuEF"))),
            //((TH1D*)(b4m->Get("h_CA8jetMuEF"))),
            ((TH1D*)(Am->Get("h_CA8jetMuEF"))),
	    ((TH1D*)(Bm->Get("h_CA8jetMuEF"))),
	    ((TH1D*)(Cm->Get("h_CA8jetMuEF"))),
            0,1);
  
  
  gPad->SetTickx();
  gPad->SetRightMargin(0.02);
  gPad->SetLeftMargin(0.07);



  gSystem->ProcessEvents();
  TImage *img1 = TImage::Create();
  img1->FromPad(c1);
  img1->WriteImage("h_CA8jetMuEF.png");
  delete c1;
  delete img1;


  //-------------------------------------------//






  TCanvas* c2 = new TCanvas("c2", "", 0, 0, 1500, 750);

  c2->Divide(2,2,0,0);

  //-------------------------------------------//

  c2->cd(1);
  myPlotE( ((TH1D*)(b1e->Get("h_CA8jetPhoEF"))), 
	   ((TH1D*)(b2e->Get("h_CA8jetPhoEF"))), 
	   ((TH1D*)(b3e->Get("h_CA8jetPhoEF"))), 
	   //	   ((TH1D*)(b4e->Get("h_CA8jetPhoEF"))),
	   ((TH1D*)(Ae->Get("h_CA8jetPhoEF"))),
	   ((TH1D*)(Be->Get("h_CA8jetPhoEF"))),
	   ((TH1D*)(Ce->Get("h_CA8jetPhoEF")))
	   );
  
  gPad->SetRightMargin(0.02);

  //-------------------------------------------//
  
  c2->cd(2);
  myPlotM( ((TH1D*)(b1m->Get("h_CA8jetPhoEF"))),
	   ((TH1D*)(b2m->Get("h_CA8jetPhoEF"))),
	   ((TH1D*)(b3m->Get("h_CA8jetPhoEF"))),
	   //((TH1D*)(b4m->Get("h_CA8jetPhoEF"))),
	   ((TH1D*)(Am->Get("h_CA8jetPhoEF"))),
	   ((TH1D*)(Bm->Get("h_CA8jetPhoEF"))),
	   ((TH1D*)(Cm->Get("h_CA8jetPhoEF")))
	   );
  
  gPad->SetRightMargin(0.02);
  gPad->SetLeftMargin(0.07);

  
  //-------------------------------------------//

  c2->cd(3);
  myRatioE( ((TH1D*)(b1e->Get("h_CA8jetPhoEF"))),
	    ((TH1D*)(b2e->Get("h_CA8jetPhoEF"))),
	    ((TH1D*)(b3e->Get("h_CA8jetPhoEF"))),
	    //((TH1D*)(b4e->Get("h_CA8jetPhoEF"))),
	    ((TH1D*)(Ae->Get("h_CA8jetPhoEF"))),
	    ((TH1D*)(Be->Get("h_CA8jetPhoEF"))),
	    ((TH1D*)(Ce->Get("h_CA8jetPhoEF"))),
	    0,1);
  
  gPad->SetTickx();
  gPad->SetRightMargin(0.02);



  //-------------------------------------------//
  
  c2->cd(4);
  myRatioM( ((TH1D*)(b1m->Get("h_CA8jetPhoEF"))),
            ((TH1D*)(b2m->Get("h_CA8jetPhoEF"))),
            ((TH1D*)(b3m->Get("h_CA8jetPhoEF"))),
            //((TH1D*)(b4m->Get("h_CA8jetPhoEF"))),
            ((TH1D*)(Am->Get("h_CA8jetPhoEF"))),
	    ((TH1D*)(Bm->Get("h_CA8jetPhoEF"))),
	    ((TH1D*)(Cm->Get("h_CA8jetPhoEF"))),
	    0,1);
  
  
  gPad->SetTickx();
  gPad->SetRightMargin(0.02);
  gPad->SetLeftMargin(0.07);



  gSystem->ProcessEvents();
  TImage *img2 = TImage::Create();
  img2->FromPad(c2);
  img2->WriteImage("h_CA8jetPhoEF.png");
  delete c2;
  delete img2;


  //-------------------------------------------//



  TCanvas* c3 = new TCanvas("c3", "", 0, 0, 1500, 750);

  c3->Divide(2,2,0,0);

  //-------------------------------------------//

  c3->cd(1);
  myPlotE( ((TH1D*)(b1e->Get("h_CA8jetCEmEF"))), 
	   ((TH1D*)(b2e->Get("h_CA8jetCEmEF"))), 
	   ((TH1D*)(b3e->Get("h_CA8jetCEmEF"))), 
	   //((TH1D*)(b4e->Get("h_CA8jetCEmEF"))),
	   ((TH1D*)(Ae->Get("h_CA8jetCEmEF"))),
	   ((TH1D*)(Be->Get("h_CA8jetCEmEF"))),
	   ((TH1D*)(Ce->Get("h_CA8jetCEmEF")))
	   );
  
  gPad->SetRightMargin(0.02);

  //-------------------------------------------//
  
  c3->cd(2);
  myPlotM( ((TH1D*)(b1m->Get("h_CA8jetCEmEF"))),
	   ((TH1D*)(b2m->Get("h_CA8jetCEmEF"))),
	   ((TH1D*)(b3m->Get("h_CA8jetCEmEF"))),
	   //((TH1D*)(b4m->Get("h_CA8jetCEmEF"))),
	   ((TH1D*)(Am->Get("h_CA8jetCEmEF"))),
	   ((TH1D*)(Bm->Get("h_CA8jetCEmEF"))),
	   ((TH1D*)(Cm->Get("h_CA8jetCEmEF")))
	   );
  
  gPad->SetRightMargin(0.02);
  gPad->SetLeftMargin(0.07);

  
  //-------------------------------------------//

  c3->cd(3);
  myRatioE( ((TH1D*)(b1e->Get("h_CA8jetCEmEF"))),
	    ((TH1D*)(b2e->Get("h_CA8jetCEmEF"))),
	    ((TH1D*)(b3e->Get("h_CA8jetCEmEF"))),
	    //((TH1D*)(b4e->Get("h_CA8jetCEmEF"))),
	    ((TH1D*)(Ae->Get("h_CA8jetCEmEF"))),
	    ((TH1D*)(Be->Get("h_CA8jetCEmEF"))),
	    ((TH1D*)(Ce->Get("h_CA8jetCEmEF"))),
	    0,1);
  
  gPad->SetTickx();
  gPad->SetRightMargin(0.02);



  //-------------------------------------------//
  
  c3->cd(4);
  myRatioM( ((TH1D*)(b1m->Get("h_CA8jetCEmEF"))),
            ((TH1D*)(b2m->Get("h_CA8jetCEmEF"))),
            ((TH1D*)(b3m->Get("h_CA8jetCEmEF"))),
            //((TH1D*)(b4m->Get("h_CA8jetCEmEF"))),
            ((TH1D*)(Am->Get("h_CA8jetCEmEF"))),
	    ((TH1D*)(Bm->Get("h_CA8jetCEmEF"))),
	    ((TH1D*)(Cm->Get("h_CA8jetCEmEF"))),
            0,1);

  
  
  gPad->SetTickx();
  gPad->SetRightMargin(0.02);
  gPad->SetLeftMargin(0.07);



  gSystem->ProcessEvents();
  TImage *img3 = TImage::Create();
  img3->FromPad(c3);
  img3->WriteImage("h_CA8jetCEmEF.png");
  delete c3;
  delete img3;


  //-------------------------------------------//




  TCanvas* c4 = new TCanvas("c4", "", 0, 0, 1500, 750);

  c4->Divide(2,2,0,0);

  //-------------------------------------------//

  c4->cd(1);
  myPlotE( ((TH1D*)(b1e->Get("h_CA8jetCHadEF"))), 
	   ((TH1D*)(b2e->Get("h_CA8jetCHadEF"))), 
	   ((TH1D*)(b3e->Get("h_CA8jetCHadEF"))), 
	   //((TH1D*)(b4e->Get("h_CA8jetCHadEF"))),
	   ((TH1D*)(Ae->Get("h_CA8jetCHadEF"))),
	   ((TH1D*)(Be->Get("h_CA8jetCHadEF"))),
	   ((TH1D*)(Ce->Get("h_CA8jetCHadEF")))
      	   );
  
  gPad->SetRightMargin(0.02);

  //-------------------------------------------//
  
  c4->cd(2);
  myPlotM( ((TH1D*)(b1m->Get("h_CA8jetCHadEF"))),
	   ((TH1D*)(b2m->Get("h_CA8jetCHadEF"))),
	   ((TH1D*)(b3m->Get("h_CA8jetCHadEF"))),
	   //((TH1D*)(b4m->Get("h_CA8jetCHadEF"))),
	   ((TH1D*)(Am->Get("h_CA8jetCHadEF"))),
	   ((TH1D*)(Bm->Get("h_CA8jetCHadEF"))),
	   ((TH1D*)(Cm->Get("h_CA8jetCHadEF")))
	   );
  

  gPad->SetRightMargin(0.02);
  gPad->SetLeftMargin(0.07);

  
  //-------------------------------------------//

  c4->cd(3);
  myRatioE( ((TH1D*)(b1e->Get("h_CA8jetCHadEF"))),
	    ((TH1D*)(b2e->Get("h_CA8jetCHadEF"))),
	    ((TH1D*)(b3e->Get("h_CA8jetCHadEF"))),
	    //((TH1D*)(b4e->Get("h_CA8jetCHadEF"))),
	    ((TH1D*)(Ae->Get("h_CA8jetCHadEF"))),
	    ((TH1D*)(Be->Get("h_CA8jetCHadEF"))),
	    ((TH1D*)(Ce->Get("h_CA8jetCHadEF"))),
	    0,1);
  
  gPad->SetTickx();
  gPad->SetRightMargin(0.02);



  //-------------------------------------------//
  
  c4->cd(4);
  myRatioM( ((TH1D*)(b1m->Get("h_CA8jetCHadEF"))),
            ((TH1D*)(b2m->Get("h_CA8jetCHadEF"))),
            ((TH1D*)(b3m->Get("h_CA8jetCHadEF"))),
            //((TH1D*)(b4m->Get("h_CA8jetCHadEF"))),
            ((TH1D*)(Am->Get("h_CA8jetCHadEF"))),
	    ((TH1D*)(Bm->Get("h_CA8jetCHadEF"))),
	    ((TH1D*)(Cm->Get("h_CA8jetCHadEF"))),
            0,1);

  
  
  gPad->SetTickx();
  gPad->SetRightMargin(0.02);
  gPad->SetLeftMargin(0.07);



  gSystem->ProcessEvents();
  TImage *img4 = TImage::Create();
  img4->FromPad(c4);
  img4->WriteImage("h_CA8jetCHadEF.png");
  delete c4;
  delete img4;


  //-------------------------------------------//


  TCanvas* c5 = new TCanvas("c5", "", 0, 0, 1500, 750);

  c5->Divide(2,2,0,0);

  //-------------------------------------------//

  c5->cd(1);
  myPlotE( ((TH1D*)(b1e->Get("h_CA8jetNEmEF"))), 
	   ((TH1D*)(b2e->Get("h_CA8jetNEmEF"))), 
	   ((TH1D*)(b3e->Get("h_CA8jetNEmEF"))), 
	   //((TH1D*)(b4e->Get("h_CA8jetNEmEF"))),
	   ((TH1D*)(Ae->Get("h_CA8jetNEmEF"))),
	   ((TH1D*)(Be->Get("h_CA8jetNEmEF"))),
	   ((TH1D*)(Ce->Get("h_CA8jetNEmEF")))
	   );
  
  gPad->SetRightMargin(0.02);

  //-------------------------------------------//
  
  c5->cd(2);
  myPlotM( ((TH1D*)(b1m->Get("h_CA8jetNEmEF"))),
	   ((TH1D*)(b2m->Get("h_CA8jetNEmEF"))),
	   ((TH1D*)(b3m->Get("h_CA8jetNEmEF"))),
	   //((TH1D*)(b4m->Get("h_CA8jetNEmEF"))),
	   ((TH1D*)(Am->Get("h_CA8jetNEmEF"))),
	   ((TH1D*)(Bm->Get("h_CA8jetNEmEF"))),
	   ((TH1D*)(Cm->Get("h_CA8jetNEmEF")))
	   );
  
  gPad->SetRightMargin(0.02);
  gPad->SetLeftMargin(0.07);

  
  //-------------------------------------------//

  c5->cd(3);
  myRatioE( ((TH1D*)(b1e->Get("h_CA8jetNEmEF"))),
	    ((TH1D*)(b2e->Get("h_CA8jetNEmEF"))),
	    ((TH1D*)(b3e->Get("h_CA8jetNEmEF"))),
	    //((TH1D*)(b4e->Get("h_CA8jetNEmEF"))),
	    ((TH1D*)(Ae->Get("h_CA8jetNEmEF"))),
	    ((TH1D*)(Be->Get("h_CA8jetNEmEF"))),
	    ((TH1D*)(Ce->Get("h_CA8jetNEmEF"))),
	    0,1);
  
  gPad->SetTickx();
  gPad->SetRightMargin(0.02);



  //-------------------------------------------//
  
  c5->cd(4);
  myRatioM( ((TH1D*)(b1m->Get("h_CA8jetNEmEF"))),
            ((TH1D*)(b2m->Get("h_CA8jetNEmEF"))),
            ((TH1D*)(b3m->Get("h_CA8jetNEmEF"))),
            //((TH1D*)(b4m->Get("h_CA8jetNEmEF"))),
            ((TH1D*)(Am->Get("h_CA8jetNEmEF"))),
	    ((TH1D*)(Bm->Get("h_CA8jetNEmEF"))),
	    ((TH1D*)(Cm->Get("h_CA8jetNEmEF"))),
            0,1);
  
  
  gPad->SetTickx();
  gPad->SetRightMargin(0.02);
  gPad->SetLeftMargin(0.07);



  gSystem->ProcessEvents();
  TImage *img5 = TImage::Create();
  img5->FromPad(c5);
  img5->WriteImage("h_CA8jetNEmEF.png");
  delete c5;
  delete img5;


  //-------------------------------------------//



  TCanvas* c6 = new TCanvas("c6", "", 0, 0, 1500, 750);

  c6->Divide(2,2,0,0);

  //-------------------------------------------//

  c6->cd(1);
  myPlotE( ((TH1D*)(b1e->Get("h_CA8jetNHadEF"))), 
	   ((TH1D*)(b2e->Get("h_CA8jetNHadEF"))), 
	   ((TH1D*)(b3e->Get("h_CA8jetNHadEF"))), 
	   //((TH1D*)(b4e->Get("h_CA8jetNHadEF"))),
	   ((TH1D*)(Ae->Get("h_CA8jetNHadEF"))),
	   ((TH1D*)(Be->Get("h_CA8jetNHadEF"))),
	   ((TH1D*)(Ce->Get("h_CA8jetNHadEF")))
	   );
  
  gPad->SetRightMargin(0.02);

  //-------------------------------------------//
  
  c6->cd(2);
  myPlotM( ((TH1D*)(b1m->Get("h_CA8jetNHadEF"))),
	   ((TH1D*)(b2m->Get("h_CA8jetNHadEF"))),
	   ((TH1D*)(b3m->Get("h_CA8jetNHadEF"))),
	   //((TH1D*)(b4m->Get("h_CA8jetNHadEF"))),
	   ((TH1D*)(Am->Get("h_CA8jetNHadEF"))),
	   ((TH1D*)(Bm->Get("h_CA8jetNHadEF"))),
	   ((TH1D*)(Cm->Get("h_CA8jetNHadEF")))
	   );
  
  gPad->SetRightMargin(0.02);
  gPad->SetLeftMargin(0.07);

  
  //-------------------------------------------//

  c6->cd(3);
  myRatioE( ((TH1D*)(b1e->Get("h_CA8jetNHadEF"))),
	    ((TH1D*)(b2e->Get("h_CA8jetNHadEF"))),
	    ((TH1D*)(b3e->Get("h_CA8jetNHadEF"))),
	    //((TH1D*)(b4e->Get("h_CA8jetNHadEF"))),
	    ((TH1D*)(Ae->Get("h_CA8jetNHadEF"))),
	    ((TH1D*)(Be->Get("h_CA8jetNHadEF"))),
	    ((TH1D*)(Ce->Get("h_CA8jetNHadEF"))),
	    0,1);
  
  gPad->SetTickx();
  gPad->SetRightMargin(0.02);



  //-------------------------------------------//
  
  c6->cd(4);
  myRatioM( ((TH1D*)(b1m->Get("h_CA8jetNHadEF"))),
            ((TH1D*)(b2m->Get("h_CA8jetNHadEF"))),
            ((TH1D*)(b3m->Get("h_CA8jetNHadEF"))),
            //((TH1D*)(b4m->Get("h_CA8jetNHadEF"))),
            ((TH1D*)(Am->Get("h_CA8jetNHadEF"))),
  	    ((TH1D*)(Bm->Get("h_CA8jetNHadEF"))),
	    ((TH1D*)(Cm->Get("h_CA8jetNHadEF"))),
	    0,1);
  
  
  gPad->SetTickx();
  gPad->SetRightMargin(0.02);
  gPad->SetLeftMargin(0.07);



  gSystem->ProcessEvents();
  TImage *img6 = TImage::Create();
  img6->FromPad(c6);
  img6->WriteImage("h_CA8jetNHadEF.png");
  delete c6;
  delete img6;


  //-------------------------------------------//



  TCanvas* c7 = new TCanvas("c7", "", 0, 0, 1500, 750);

  c7->Divide(2,2,0,0);

  //-------------------------------------------//

  c7->cd(1);
  myPlotE( ((TH1D*)(b1e->Get("h_CA8jetCMulti"))), 
	   ((TH1D*)(b2e->Get("h_CA8jetCMulti"))), 
	   ((TH1D*)(b3e->Get("h_CA8jetCMulti"))), 
	   //((TH1D*)(b4e->Get("h_CA8jetCMulti"))),
	   ((TH1D*)(Ae->Get("h_CA8jetCMulti"))),
	   ((TH1D*)(Be->Get("h_CA8jetCMulti"))),
	   ((TH1D*)(Ce->Get("h_CA8jetCMulti")))
	   );
  
  gPad->SetRightMargin(0.02);

  //-------------------------------------------//
  
  c7->cd(2);
  myPlotM( ((TH1D*)(b1m->Get("h_CA8jetCMulti"))),
	   ((TH1D*)(b2m->Get("h_CA8jetCMulti"))),
	   ((TH1D*)(b3m->Get("h_CA8jetCMulti"))),
	   //((TH1D*)(b4m->Get("h_CA8jetCMulti"))),
	   ((TH1D*)(Am->Get("h_CA8jetCMulti"))),
	   ((TH1D*)(Bm->Get("h_CA8jetCMulti"))),
	   ((TH1D*)(Cm->Get("h_CA8jetCMulti")))
	   );
  
  gPad->SetRightMargin(0.02);
  gPad->SetLeftMargin(0.07);

  
  //-------------------------------------------//

  c7->cd(3);
  myRatioE( ((TH1D*)(b1e->Get("h_CA8jetCMulti"))),
	    ((TH1D*)(b2e->Get("h_CA8jetCMulti"))),
	    ((TH1D*)(b3e->Get("h_CA8jetCMulti"))),
	    //((TH1D*)(b4e->Get("h_CA8jetCMulti"))),
	    ((TH1D*)(Ae->Get("h_CA8jetCMulti"))),
	    ((TH1D*)(Be->Get("h_CA8jetCMulti"))),
	    ((TH1D*)(Ce->Get("h_CA8jetCMulti"))),
	    0,250);
  
  gPad->SetTickx();
  gPad->SetRightMargin(0.02);



  //-------------------------------------------//
  
  c7->cd(4);
  myRatioM( ((TH1D*)(b1m->Get("h_CA8jetCMulti"))),
            ((TH1D*)(b2m->Get("h_CA8jetCMulti"))),
            ((TH1D*)(b3m->Get("h_CA8jetCMulti"))),
            //((TH1D*)(b4m->Get("h_CA8jetCMulti"))),
            ((TH1D*)(Am->Get("h_CA8jetCMulti"))),
	    ((TH1D*)(Bm->Get("h_CA8jetCMulti"))),
	    ((TH1D*)(Cm->Get("h_CA8jetCMulti"))),
	    0,250);
  
  
  gPad->SetTickx();
  gPad->SetRightMargin(0.02);
  gPad->SetLeftMargin(0.07);



  gSystem->ProcessEvents();
  TImage *img7 = TImage::Create();
  img7->FromPad(c7);
  img7->WriteImage("h_CA8jetCMulti.png");
  delete c7;
  delete img7;


  //-------------------------------------------//





  TCanvas* c8 = new TCanvas("c8", "", 0, 0, 1500, 750);

  c8->Divide(2,2,0,0);

  //-------------------------------------------//

  c8->cd(1);
  myPlotE( ((TH1D*)(b1e->Get("h_CA8jetTau21"))), 
	   ((TH1D*)(b2e->Get("h_CA8jetTau21"))), 
	   ((TH1D*)(b3e->Get("h_CA8jetTau21"))), 
	   //((TH1D*)(b4e->Get("h_CA8jetTau21"))),
	   ((TH1D*)(Ae->Get("h_CA8jetTau21"))),
	   ((TH1D*)(Be->Get("h_CA8jetTau21"))),
	   ((TH1D*)(Ce->Get("h_CA8jetTau21")))
	   );
  
  gPad->SetRightMargin(0.02);

  //-------------------------------------------//
  
  c8->cd(2);
  myPlotM( ((TH1D*)(b1m->Get("h_CA8jetTau21"))),
	   ((TH1D*)(b2m->Get("h_CA8jetTau21"))),
	   ((TH1D*)(b3m->Get("h_CA8jetTau21"))),
	   //((TH1D*)(b4m->Get("h_CA8jetTau21"))),
	   ((TH1D*)(Am->Get("h_CA8jetTau21"))),
	   ((TH1D*)(Bm->Get("h_CA8jetTau21"))),
	   ((TH1D*)(Cm->Get("h_CA8jetTau21")))
	   );
  
  gPad->SetRightMargin(0.02);
  gPad->SetLeftMargin(0.07);

  
  //-------------------------------------------//

  c8->cd(3);
  myRatioE( ((TH1D*)(b1e->Get("h_CA8jetTau21"))),
	    ((TH1D*)(b2e->Get("h_CA8jetTau21"))),
	    ((TH1D*)(b3e->Get("h_CA8jetTau21"))),
	    //((TH1D*)(b4e->Get("h_CA8jetTau21"))),
	    ((TH1D*)(Ae->Get("h_CA8jetTau21"))),
	    ((TH1D*)(Be->Get("h_CA8jetTau21"))),
	    ((TH1D*)(Ce->Get("h_CA8jetTau21"))),
	    0,1);
  
  gPad->SetTickx();
  gPad->SetRightMargin(0.02);



  //-------------------------------------------//
  
  c8->cd(4);
  myRatioM( ((TH1D*)(b1m->Get("h_CA8jetTau21"))),
            ((TH1D*)(b2m->Get("h_CA8jetTau21"))),
            ((TH1D*)(b3m->Get("h_CA8jetTau21"))),
            //((TH1D*)(b4m->Get("h_CA8jetTau21"))),
            ((TH1D*)(Am->Get("h_CA8jetTau21"))),
	    ((TH1D*)(Bm->Get("h_CA8jetTau21"))),
	    ((TH1D*)(Cm->Get("h_CA8jetTau21"))),
	    0,1);
  
  
  gPad->SetTickx();
  gPad->SetRightMargin(0.02);
  gPad->SetLeftMargin(0.07);



  gSystem->ProcessEvents();
  TImage *img8 = TImage::Create();
  img8->FromPad(c8);
  img8->WriteImage("h_CA8jetTau21.png");
  delete c8;
  delete img8;


  //-------------------------------------------//



  TCanvas* c9 = new TCanvas("c9", "", 0, 0, 1500, 750);

  c9->Divide(2,2,0,0);

  //-------------------------------------------//

  c9->cd(1);
  myPlotE( ((TH1D*)(b1e->Get("h_PrunedjetM"))), 
	   ((TH1D*)(b2e->Get("h_PrunedjetM"))), 
	   ((TH1D*)(b3e->Get("h_PrunedjetM"))), 
	   //((TH1D*)(b4e->Get("h_CA8jetCEmEF"))),
	   ((TH1D*)(Ae->Get("h_PrunedjetM"))),
	   ((TH1D*)(Be->Get("h_PrunedjetM"))),
	   ((TH1D*)(Ce->Get("h_PrunedjetM")))
	   );
  
  gPad->SetRightMargin(0.02);

  //-------------------------------------------//
  
  c9->cd(2);
  myPlotM( ((TH1D*)(b1m->Get("h_PrunedjetM"))),
	   ((TH1D*)(b2m->Get("h_PrunedjetM"))),
	   ((TH1D*)(b3m->Get("h_PrunedjetM"))),
	   //((TH1D*)(b4m->Get("h_CA8jetCEmEF"))),
	   ((TH1D*)(Am->Get("h_PrunedjetM"))),
	   ((TH1D*)(Bm->Get("h_PrunedjetM"))),
	   ((TH1D*)(Cm->Get("h_PrunedjetM")))
	   );
  
  gPad->SetRightMargin(0.02);
  gPad->SetLeftMargin(0.07);

  
  //-------------------------------------------//

  c9->cd(3);
  myRatioE( ((TH1D*)(b1e->Get("h_PrunedjetM"))),
	    ((TH1D*)(b2e->Get("h_PrunedjetM"))),
	    ((TH1D*)(b3e->Get("h_PrunedjetM"))),
	    //((TH1D*)(b4e->Get("h_CA8jetCEmEF"))),
	    ((TH1D*)(Ae->Get("h_PrunedjetM"))),
	    ((TH1D*)(Be->Get("h_PrunedjetM"))),
	    ((TH1D*)(Ce->Get("h_PrunedjetM"))),
	    0,150);
  
  gPad->SetTickx();
  gPad->SetRightMargin(0.02);



  //-------------------------------------------//
  
  c9->cd(4);
  myRatioM( ((TH1D*)(b1m->Get("h_PrunedjetM"))),
            ((TH1D*)(b2m->Get("h_PrunedjetM"))),
            ((TH1D*)(b3m->Get("h_PrunedjetM"))),
            //((TH1D*)(b4m->Get("h_CA8jetCEmEF"))),
            ((TH1D*)(Am->Get("h_PrunedjetM"))),
            ((TH1D*)(Bm->Get("h_PrunedjetM"))),
            ((TH1D*)(Cm->Get("h_PrunedjetM"))),
            0,150);
  
  
  gPad->SetTickx();
  gPad->SetRightMargin(0.02);
  gPad->SetLeftMargin(0.07);



  gSystem->ProcessEvents();
  TImage *img9 = TImage::Create();
  img9->FromPad(c9);
  img9->WriteImage("h_PrunedjetM.png");
  delete c9;
  delete img9;


  //-------------------------------------------//





  TCanvas* c10 = new TCanvas("c10", "", 0, 0, 1500, 750);

  c10->Divide(2,2,0,0);

  //-------------------------------------------//

  c10->cd(1);
  myPlotE( ((TH1D*)(b1e->Get("h_CA8jetCSV"))), 
	   ((TH1D*)(b2e->Get("h_CA8jetCSV"))), 
	   ((TH1D*)(b3e->Get("h_CA8jetCSV"))), 
	   //((TH1D*)(b4e->Get("h_CA8jetCSV"))),
	   ((TH1D*)(Ae->Get("h_CA8jetCSV"))),
	   ((TH1D*)(Be->Get("h_CA8jetCSV"))),
	   ((TH1D*)(Ce->Get("h_CA8jetCSV")))
	   );
  
  gPad->SetRightMargin(0.02);

  //-------------------------------------------//
  
  c10->cd(2);
  myPlotM( ((TH1D*)(b1m->Get("h_CA8jetCSV"))),
	   ((TH1D*)(b2m->Get("h_CA8jetCSV"))),
	   ((TH1D*)(b3m->Get("h_CA8jetCSV"))),
	   //((TH1D*)(b4m->Get("h_CA8jetCSV"))),
	   ((TH1D*)(Am->Get("h_CA8jetCSV"))),
	   ((TH1D*)(Bm->Get("h_CA8jetCSV"))),
	   ((TH1D*)(Cm->Get("h_CA8jetCSV")))
	   );
  
  gPad->SetRightMargin(0.02);
  gPad->SetLeftMargin(0.07);

  
  //-------------------------------------------//

  c10->cd(3);
  myRatioE( ((TH1D*)(b1e->Get("h_CA8jetCSV"))),
	    ((TH1D*)(b2e->Get("h_CA8jetCSV"))),
	    ((TH1D*)(b3e->Get("h_CA8jetCSV"))),
	    //((TH1D*)(b4e->Get("h_CA8jetCSV"))),
	    ((TH1D*)(Ae->Get("h_CA8jetCSV"))),
	    ((TH1D*)(Be->Get("h_CA8jetCSV"))),
	    ((TH1D*)(Ce->Get("h_CA8jetCSV"))),
	    0,1);
  
  gPad->SetTickx();
  gPad->SetRightMargin(0.02);



  //-------------------------------------------//
  
  c10->cd(4);
  myRatioM( ((TH1D*)(b1m->Get("h_CA8jetCSV"))),
            ((TH1D*)(b2m->Get("h_CA8jetCSV"))),
            ((TH1D*)(b3m->Get("h_CA8jetCSV"))),
            //((TH1D*)(b4m->Get("h_CA8jetCSV"))),
            ((TH1D*)(Am->Get("h_CA8jetCSV"))),
	    ((TH1D*)(Bm->Get("h_CA8jetCSV"))),
	    ((TH1D*)(Cm->Get("h_CA8jetCSV"))),
            0,1);
  
  
  gPad->SetTickx();
  gPad->SetRightMargin(0.02);
  gPad->SetLeftMargin(0.07);



  gSystem->ProcessEvents();
  TImage *img10 = TImage::Create();
  img10->FromPad(c10);
  img10->WriteImage("h_CA8jetCSV.png");
  delete c10;
  delete img10;


  //-------------------------------------------//




  TCanvas* c11 = new TCanvas("c11", "", 0, 0, 1500, 750);

  c11->Divide(2,2,0,0);

  //-------------------------------------------//

  c11->cd(1);
  myPlotE( ((TH1D*)(b1e->Get("h_CA8nSubPrunedJet"))), 
	   ((TH1D*)(b2e->Get("h_CA8nSubPrunedJet"))), 
	   ((TH1D*)(b3e->Get("h_CA8nSubPrunedJet"))), 
	   //((TH1D*)(b4e->Get("h_CA8nSubPrunedJet"))),
	   ((TH1D*)(Ae->Get("h_CA8nSubPrunedJet"))),
	   ((TH1D*)(Be->Get("h_CA8nSubPrunedJet"))),
	   ((TH1D*)(Ce->Get("h_CA8nSubPrunedJet")))
	   );
  
  gPad->SetRightMargin(0.02);

  //-------------------------------------------//
  
  c11->cd(2);
  myPlotM( ((TH1D*)(b1m->Get("h_CA8nSubPrunedJet"))),
	   ((TH1D*)(b2m->Get("h_CA8nSubPrunedJet"))),
	   ((TH1D*)(b3m->Get("h_CA8nSubPrunedJet"))),
	   //((TH1D*)(b4m->Get("h_CA8nSubPrunedJet"))),
	   ((TH1D*)(Am->Get("h_CA8nSubPrunedJet"))),
	   ((TH1D*)(Bm->Get("h_CA8nSubPrunedJet"))),
	   ((TH1D*)(Cm->Get("h_CA8nSubPrunedJet")))
	   );
  
  gPad->SetRightMargin(0.02);
  gPad->SetLeftMargin(0.07);

  
  //-------------------------------------------//

  c11->cd(3);
  myRatioE( ((TH1D*)(b1e->Get("h_CA8nSubPrunedJet"))),
	    ((TH1D*)(b2e->Get("h_CA8nSubPrunedJet"))),
	    ((TH1D*)(b3e->Get("h_CA8nSubPrunedJet"))),
	    //((TH1D*)(b4e->Get("h_CA8nSubPrunedJet"))),
	    ((TH1D*)(Ae->Get("h_CA8nSubPrunedJet"))),
	    ((TH1D*)(Be->Get("h_CA8nSubPrunedJet"))),
	    ((TH1D*)(Ce->Get("h_CA8nSubPrunedJet"))),
	    0,5);
  
  gPad->SetTickx();
  gPad->SetRightMargin(0.02);



  //-------------------------------------------//
  
  c11->cd(4);
  myRatioM( ((TH1D*)(b1m->Get("h_CA8nSubPrunedJet"))),
            ((TH1D*)(b2m->Get("h_CA8nSubPrunedJet"))),
            ((TH1D*)(b3m->Get("h_CA8nSubPrunedJet"))),
            //((TH1D*)(b4m->Get("h_CA8nSubPrunedJet"))),
            ((TH1D*)(Am->Get("h_CA8nSubPrunedJet"))),
	    ((TH1D*)(Bm->Get("h_CA8nSubPrunedJet"))),
	    ((TH1D*)(Cm->Get("h_CA8nSubPrunedJet"))),
            0,5);
  
  
  gPad->SetTickx();
  gPad->SetRightMargin(0.02);
  gPad->SetLeftMargin(0.07);



  gSystem->ProcessEvents();
  TImage *img11 = TImage::Create();
  img11->FromPad(c11);
  img11->WriteImage("h_CA8nSubPrunedJet.png");
  delete c11;
  delete img11;


  //-------------------------------------------//



  TCanvas* c12 = new TCanvas("c12", "", 0, 0, 1500, 750);

  c12->Divide(2,2,0,0);

  //-------------------------------------------//

  c12->cd(1);
  myPlotE( ((TH1D*)(b1e->Get("h_CA8nJet"))), 
	   ((TH1D*)(b2e->Get("h_CA8nJet"))), 
	   ((TH1D*)(b3e->Get("h_CA8nJet"))), 
	   //((TH1D*)(b4e->Get("h_CA8nJet"))),
	   ((TH1D*)(Ae->Get("h_CA8nJet"))),
	   ((TH1D*)(Be->Get("h_CA8nJet"))),
	   ((TH1D*)(Ce->Get("h_CA8nJet")))
	   );
  
  gPad->SetRightMargin(0.02);

  //-------------------------------------------//
  
  c12->cd(2);
  myPlotM( ((TH1D*)(b1m->Get("h_CA8nJet"))),
	   ((TH1D*)(b2m->Get("h_CA8nJet"))),
	   ((TH1D*)(b3m->Get("h_CA8nJet"))),
	   //((TH1D*)(b4m->Get("h_CA8nJet"))),
	   ((TH1D*)(Am->Get("h_CA8nJet"))),
	   ((TH1D*)(Bm->Get("h_CA8nJet"))),
	   ((TH1D*)(Cm->Get("h_CA8nJet")))
	   );
  
  gPad->SetRightMargin(0.02);
  gPad->SetLeftMargin(0.07);

  
  //-------------------------------------------//

  c12->cd(3);
  myRatioE( ((TH1D*)(b1e->Get("h_CA8nJet"))),
	    ((TH1D*)(b2e->Get("h_CA8nJet"))),
	    ((TH1D*)(b3e->Get("h_CA8nJet"))),
	    //((TH1D*)(b4e->Get("h_CA8nJet"))),
	    ((TH1D*)(Ae->Get("h_CA8nJet"))),
	    ((TH1D*)(Be->Get("h_CA8nJet"))),
	    ((TH1D*)(Ce->Get("h_CA8nJet"))),
	    0,10);
  
  gPad->SetTickx();
  gPad->SetRightMargin(0.02);



  //-------------------------------------------//
  
  c12->cd(4);
  myRatioM( ((TH1D*)(b1m->Get("h_CA8nJet"))),
            ((TH1D*)(b2m->Get("h_CA8nJet"))),
            ((TH1D*)(b3m->Get("h_CA8nJet"))),
            //((TH1D*)(b4m->Get("h_CA8nJet"))),
	    ((TH1D*)(Am->Get("h_CA8nJet"))),
	    ((TH1D*)(Bm->Get("h_CA8nJet"))),
            ((TH1D*)(Cm->Get("h_CA8nJet"))),
            0,10);
  
  
  gPad->SetTickx();
  gPad->SetRightMargin(0.02);
  gPad->SetLeftMargin(0.07);



  gSystem->ProcessEvents();
  TImage *img12 = TImage::Create();
  img12->FromPad(c12);
  img12->WriteImage("h_CA8nJet.png");
  delete c12;
  delete img12;


  //-------------------------------------------//



  TCanvas* c13 = new TCanvas("c13", "", 0, 0, 1500, 750);

  c13->Divide(2,2,0,0);

  //-------------------------------------------//

  c13->cd(1);
  myPlotE( ((TH1D*)(b1e->Get("h_CA8subjetPrunedCSV"))), 
	   ((TH1D*)(b2e->Get("h_CA8subjetPrunedCSV"))), 
	   ((TH1D*)(b3e->Get("h_CA8subjetPrunedCSV"))), 
	   //((TH1D*)(b4e->Get("h_CA8subjetPrunedCSV"))),
	   ((TH1D*)(Ae->Get("h_CA8subjetPrunedCSV"))),
	   ((TH1D*)(Be->Get("h_CA8subjetPrunedCSV"))),
	   ((TH1D*)(Ce->Get("h_CA8subjetPrunedCSV")))
	   );
  
  gPad->SetRightMargin(0.02);

  //-------------------------------------------//
  
  c13->cd(2);
  myPlotM( ((TH1D*)(b1m->Get("h_CA8subjetPrunedCSV"))),
	   ((TH1D*)(b2m->Get("h_CA8subjetPrunedCSV"))),
	   ((TH1D*)(b3m->Get("h_CA8subjetPrunedCSV"))),
	   //((TH1D*)(b4m->Get("h_CA8subjetPrunedCSV"))),
	   ((TH1D*)(Am->Get("h_CA8subjetPrunedCSV"))),
	   ((TH1D*)(Bm->Get("h_CA8subjetPrunedCSV"))),
	   ((TH1D*)(Cm->Get("h_CA8subjetPrunedCSV")))
	   );
  
  gPad->SetRightMargin(0.02);
  gPad->SetLeftMargin(0.07);

  
  //-------------------------------------------//

  c13->cd(3);
  myRatioE( ((TH1D*)(b1e->Get("h_CA8subjetPrunedCSV"))),
	    ((TH1D*)(b2e->Get("h_CA8subjetPrunedCSV"))),
	    ((TH1D*)(b3e->Get("h_CA8subjetPrunedCSV"))),
	    //((TH1D*)(b4e->Get("h_CA8subjetPrunedCSV"))),
	    ((TH1D*)(Ae->Get("h_CA8subjetPrunedCSV"))),
	    ((TH1D*)(Be->Get("h_CA8subjetPrunedCSV"))),
	    ((TH1D*)(Ce->Get("h_CA8subjetPrunedCSV"))),
	    0,1);
  

  gPad->SetTickx();
  gPad->SetRightMargin(0.02);



  //-------------------------------------------//
  
  c13->cd(4);
  myRatioM( ((TH1D*)(b1m->Get("h_CA8subjetPrunedCSV"))),
            ((TH1D*)(b2m->Get("h_CA8subjetPrunedCSV"))),
            ((TH1D*)(b3m->Get("h_CA8subjetPrunedCSV"))),
            //((TH1D*)(b4m->Get("h_CA8subjetPrunedCSV"))),
            ((TH1D*)(Am->Get("h_CA8subjetPrunedCSV"))),
            ((TH1D*)(Bm->Get("h_CA8subjetPrunedCSV"))),
            ((TH1D*)(Cm->Get("h_CA8subjetPrunedCSV"))),
            0,1);
  
  
  gPad->SetTickx();
  gPad->SetRightMargin(0.02);
  gPad->SetLeftMargin(0.07);



  gSystem->ProcessEvents();
  TImage *img13 = TImage::Create();
  img13->FromPad(c13);
  img13->WriteImage("h_CA8subjetPrunedCSV.png");
  delete c13;
  delete img13;


  //-------------------------------------------//




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

  /*
  h_WWe->Scale(scale4e);
  h_WWe->SetFillColor(kGreen+2);
  h_WWe->SetLineColor(kBlack);
  */

  THStack* h_stack = new THStack("h_stack", "");
  h_stack->Add(h_dy70e);
  h_stack->Add(h_dy100e);
  h_stack->Add(h_ttbare);
  //h_stack->Add(h_WWe);


  // data
  TH1D* h_data = (TH1D*)h_dataA->Clone("h_data");
  h_data->Reset();
  h_data->Add(h_dataA,1);
  h_data->Add(h_dataB,1);
  h_data->Add(h_dataC,1);


  h_data->SetLineColor(1);
  h_data->SetMarkerStyle(8);
  h_data->SetMarkerSize(1);

  Double_t ymin = -0.05*(h_data->GetMaximum());

  h_data->SetMinimum(ymin);
  h_data->SetLabelSize(0);
  h_data->SetXTitle("");


  h_data->Draw("e1"); 
  h_stack->Draw("histesame");
  h_data->Draw("e1same");



  TLegend *leg = new TLegend(0.73, 0.78, 0.98, 0.99);

  leg->SetFillStyle(1001);
  leg->SetFillColor(10);
  leg->SetBorderSize(1);
  leg->AddEntry(h_ttbare,"TTTo2L2Nu2B.root", "f"); 
  leg->AddEntry(h_dy100e,"DYJetsToLL_PtZ-100", "f"); 
  leg->AddEntry(h_dy70e, "DYJetsToLL_PtZ-70To100", "f"); 
  //leg->AddEntry(h_WWe, "WW", "f"); 
  leg->AddEntry(h_data, "Data", "lp");
  leg->Draw();

} // myplotE




void myPlotM(TH1D* h_dy70m, TH1D* h_dy100m, TH1D* h_ttbarm, TH1D* h_dataA, TH1D* h_dataB, TH1D* h_dataC){

  
  //  bkg         
  h_dy70m->Scale(scale1m);
  h_dy70m->SetFillColor(kCyan-4);
  h_dy70m->SetLineColor(kBlack);

  h_dy100m->Scale(scale2m);
  h_dy100m->SetFillColor(kAzure+9);
  h_dy100m->SetLineColor(kBlack);

  h_ttbarm->Scale(scale3m);
  h_ttbarm->SetFillColor(kOrange+8);
  h_ttbarm->SetLineColor(kBlack);
  
  /*
  h_WWm->Scale(scale4m);
  h_WWm->SetFillColor(kGreen+2);
  h_WWm->SetLineColor(kBlack);
  */

  THStack* h_stack = new THStack("h_stack", "");
  h_stack->Add(h_dy70m);
  h_stack->Add(h_dy100m);
  h_stack->Add(h_ttbarm);
  //h_stack->Add(h_WWm);


  // data                                                           
  TH1D* h_data = (TH1D*)h_dataA->Clone("h_data");
  h_data->Reset();
  h_data->Add(h_dataA,1);
  h_data->Add(h_dataB,1);
  h_data->Add(h_dataC,1);



  h_data->SetLineColor(1);
  h_data->SetMarkerStyle(8);
  h_data->SetMarkerSize(1);


  Double_t ymin = -0.05*(h_data->GetMaximum());

  h_data->SetMinimum(ymin);
  h_data->SetLabelSize(0);
  h_data->SetXTitle("");


  h_data->Draw("e1");
  h_stack->Draw("histesame");
  h_data->Draw("e1same");





} // myplotM




void myRatioE(TH1D* h_dy70e, TH1D* h_dy100e, TH1D* h_ttbare, TH1D* h_dataA,  TH1D* h_dataB, TH1D* h_dataC , Double_t min , Double_t max){


  
  TH1D* h_bkg = (TH1D*)h_dy100e->Clone("h_bkg");
  h_bkg->Reset();
  //h_bkg->Sumw2();
  h_bkg->Add(h_dy70e,1);
  h_bkg->Add(h_dy100e,1);
  h_bkg->Add(h_ttbare,1);
  //h_bkg->Add(h_WWe,1);


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


    //cout<<"MC_CenterValue["<<i<<"]:"<<(h_data->GetBinContent(i))<<"  MC_Error["<<i<<"]:"<<numer_binerror[i]<<endl;


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


void myRatioM(TH1D* h_dy70m, TH1D* h_dy100m, TH1D* h_ttbarm,  TH1D* h_dataA,TH1D* h_dataB, TH1D* h_dataC, Double_t min, Double_t max){

  /*
  h_dy70->Reset();
  h_dy70->Scale(scale1m);
  h_dy100->Reset();
  h_dy100->Scale(scale2m);
  h_ttbar->Reset();
  h_ttbar->Scale(scale3m);
  h_WW->Reset();
  h_WW->Scale(scale4m);
  */


  TH1D* h_bkg = (TH1D*)h_dy100m->Clone("h_bkg");
  h_bkg->Reset();
  //h_bkg->Sumw2();
  h_bkg->Add(h_dy70m,1);
  h_bkg->Add(h_dy100m,1);
  h_bkg->Add(h_ttbarm,1);
  //h_bkg->Add(h_WWm,1);


  TH1D* h_data = (TH1D*)h_dataA->Clone("h_data");
  h_data->Reset();
  h_data->Add(h_dataA,1);
  h_data->Add(h_dataB,1);
  h_data->Add(h_dataC,1);



  TH1D* h_ratio = (TH1D*)h_dy100m->Clone("h_ratio");
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




} // myratioM



