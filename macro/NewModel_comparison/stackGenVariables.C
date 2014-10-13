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



void myPlotL(TH1D*, TH1D*, TH1D*);
void myPlotR(TH1D*, TH1D*, TH1D*);
void myPlotN(TH1D*, TH1D*, TH1D*);
void myRatio(TH1D*, TH1D*, TH1D*, Double_t , Double_t );


void stackGenVariables(){


  TFile *f1 = TFile::Open("rootfile/delpanj_v2_ZPrime_hZ_qqll_LHC8_M1000.root");
  TFile *f2 = TFile::Open("rootfile/delpanj_my_xzh_LO_M1000.root");
  TFile *f3 = TFile::Open("rootfile/delpanj_MZp_LO_M1000.root");


  gStyle->SetOptStat(0);
  //gStyle->SetPadGridY(kTRUE);
  //gStyle->SetPadGridX(kTRUE);



  TCanvas* c1 = new TCanvas("c1", "", 0, 0, 1500, 750);

  c1->Divide(2,2,0,0);

  //-------------------------------------------//

  c1->cd(1);
  myPlotL( ((TH1D*)(f1->Get("h_genHPt"))), 
	   ((TH1D*)(f2->Get("h_genHPt"))),
	   ((TH1D*)(f3->Get("h_genHPt")))
	  );
  
  gPad->SetRightMargin(0.02);
  
  //-------------------------------------------//
  
  c1->cd(2);
  myPlotN( ((TH1D*)(f1->Get("h_genZPt"))),
	   ((TH1D*)(f2->Get("h_genZPt"))),
	   ((TH1D*)(f3->Get("h_genZPt")))
          );
  
  gPad->SetRightMargin(0.02);
  gPad->SetLeftMargin(0.07);

  
  //-------------------------------------------//

  c1->cd(3);
  myRatio( ((TH1D*)(f1->Get("h_genHPt"))),
	   ((TH1D*)(f2->Get("h_genHPt"))),
	   ((TH1D*)(f3->Get("h_genHPt"))),
	   0,1200);
  
  
  gPad->SetTickx();
  gPad->SetRightMargin(0.02);



  //-------------------------------------------//
  
  c1->cd(4);
  myRatio( ((TH1D*)(f1->Get("h_genZPt"))),
           ((TH1D*)(f2->Get("h_genZPt"))),
	   ((TH1D*)(f3->Get("h_genZPt"))),
	   0,1200);
  
  gPad->SetTickx();
  gPad->SetRightMargin(0.02);
  gPad->SetLeftMargin(0.07);


  
  gSystem->ProcessEvents();
  TImage *img1 = TImage::Create();
  img1->FromPad(c1);
  img1->WriteImage("h_genPt.png");
  delete c1;
  delete img1;


  //-------------------------------------------//



  

  TCanvas* c2 = new TCanvas("c2", "", 0, 0, 1500, 750);

  c2->Divide(2,2,0,0);



  c2->cd(1);
  myPlotL( ((TH1D*)(f1->Get("h_genHEta"))),
	   ((TH1D*)(f2->Get("h_genHEta"))),
	   ((TH1D*)(f3->Get("h_genHEta")))
	   );

  gPad->SetRightMargin(0.02);


  //-------------------------------------------//

  c2->cd(2);
  myPlotN( ((TH1D*)(f1->Get("h_genZEta"))),
	   ((TH1D*)(f2->Get("h_genZEta"))),
	   ((TH1D*)(f3->Get("h_genZEta")))
	   );

  gPad->SetRightMargin(0.02);
  gPad->SetLeftMargin(0.07);

  //-------------------------------------------//
  
  c2->cd(3);
  myRatio( ((TH1D*)(f1->Get("h_genHEta"))),
           ((TH1D*)(f2->Get("h_genHEta"))),
	   ((TH1D*)(f3->Get("h_genHEta"))),
	   -3,3);
  

  gPad->SetTickx();
  gPad->SetRightMargin(0.02);

  //--------------------------------------------//

  c2->cd(4);
  myRatio( ((TH1D*)(f1->Get("h_genZEta"))),
           ((TH1D*)(f2->Get("h_genZEta"))),
	   ((TH1D*)(f3->Get("h_genZEta"))),
           -3,3);

  gPad->SetTickx();
  gPad->SetRightMargin(0.02);
  gPad->SetLeftMargin(0.07);



  gSystem->ProcessEvents();
  TImage *img2 = TImage::Create();
  img2->FromPad(c2);
  img2->WriteImage("h_genEta.png");
  delete c2;
  delete img2;
  




  TCanvas* c3 = new TCanvas("c3", "", 0, 0, 1500, 750);

  c3->Divide(2,2,0,0);



  c3->cd(1);
  myPlotR( ((TH1D*)(f1->Get("h_genDeltaRqq"))),
	   ((TH1D*)(f2->Get("h_genDeltaRqq"))),
	   ((TH1D*)(f3->Get("h_genDeltaRqq")))
	   );

  gPad->SetRightMargin(0.02);

  //-------------------------------------------//                                                                    

  c3->cd(2);
  myPlotN( ((TH1D*)(f1->Get("h_genDeltaRll"))),
	   ((TH1D*)(f2->Get("h_genDeltaRll"))),
	   ((TH1D*)(f3->Get("h_genDeltaRll")))
	   );
  
  gPad->SetRightMargin(0.02);
  gPad->SetLeftMargin(0.07);

  //-------------------------------------------//                                                                    

  c3->cd(3);
  myRatio( ((TH1D*)(f1->Get("h_genDeltaRqq"))),
           ((TH1D*)(f2->Get("h_genDeltaRqq"))),
	   ((TH1D*)(f3->Get("h_genDeltaRqq"))),
	   0,1.5);


  gPad->SetTickx();
  gPad->SetRightMargin(0.02);

  //--------------------------------------------//               

  c3->cd(4);
  myRatio( ((TH1D*)(f1->Get("h_genDeltaRll"))),
           ((TH1D*)(f2->Get("h_genDeltaRll"))),
	   ((TH1D*)(f3->Get("h_genDeltaRll"))),
	   0,1.5);

  gPad->SetTickx();
  gPad->SetRightMargin(0.02);
  gPad->SetLeftMargin(0.07);



  gSystem->ProcessEvents();
  TImage *img3 = TImage::Create();
  img3->FromPad(c3);
  img3->WriteImage("h_genDeltaR.png");
  delete c3;
  delete img3;



  TCanvas* c4 = new TCanvas("c4", "", 0, 0, 1500, 750);

  c4->Divide(2,2,0,0);

  //-------------------------------------------//

  c4->cd(1);
  myPlotR( ((TH1D*)(f1->Get("h_genXPt"))), 
	   ((TH1D*)(f2->Get("h_genXPt"))),
	   ((TH1D*)(f3->Get("h_genXPt")))
	   );
  
  gPad->SetRightMargin(0.02);
  
  //-------------------------------------------//
  
  c4->cd(2);
  myPlotN( ((TH1D*)(f1->Get("h_genXY"))),
	   ((TH1D*)(f2->Get("h_genXY"))),
	   ((TH1D*)(f3->Get("h_genXY")))
	   );
  
  gPad->SetRightMargin(0.02);
  gPad->SetLeftMargin(0.07);

  
  //-------------------------------------------//

  c4->cd(3);
  myRatio( ((TH1D*)(f1->Get("h_genXPt"))),
	   ((TH1D*)(f2->Get("h_genXPt"))),
	   ((TH1D*)(f3->Get("h_genXPt"))),
	   0,600);
  
  
  gPad->SetTickx();
  gPad->SetRightMargin(0.02);



  //-------------------------------------------//
  
  c4->cd(4);
  myRatio( ((TH1D*)(f1->Get("h_genXY"))),
           ((TH1D*)(f2->Get("h_genXY"))),
	   ((TH1D*)(f3->Get("h_genXY"))),
	   3,-3);
  
  gPad->SetTickx();
  gPad->SetRightMargin(0.02);
  gPad->SetLeftMargin(0.07);


  
  gSystem->ProcessEvents();
  TImage *img4 = TImage::Create();
  img4->FromPad(c4);
  img4->WriteImage("h_genX.png");
  delete c4;
  delete img4;





}



void myPlotL(TH1D* h_sigold, TH1D* h_sig , TH1D* h_signew){


  h_sigold->SetLineColor(1);
  h_sigold->SetLineWidth(2);
  h_sigold->SetMarkerColor(1);
  h_sigold->SetMarkerStyle(20);
  h_sigold->SetMarkerSize(1);

  h_sig->SetLineColor(kCyan-4);
  h_sig->SetFillColor(kCyan-4);

  h_signew->SetFillColor(2);
  h_signew->SetLineColor(2);
  h_signew->SetFillStyle(3444);


  Double_t ymin = -0.03*(h_sigold->GetMaximum());

  h_sigold->SetMinimum(ymin);


  h_sigold->Draw("e1");
  h_sig->Draw("histesame");
  h_signew->Draw("histesame");
  h_sigold->Draw("e1same");


  TLegend *leg = new TLegend(0.15, 0.8, 0.4, 1);

  leg->SetFillStyle(1001);
  leg->SetFillColor(10);
  leg->SetBorderSize(1);
  leg->AddEntry(h_sig,"new LHE+pythia8", "f"); 
  leg->AddEntry(h_signew,"old LHE+pythia8", "f"); 
  leg->AddEntry(h_sigold,"old LHE+pythia6", "lp");
  leg->Draw();

}




void myRatio(TH1D* h_sigold, TH1D* h_sig, TH1D* h_signew, Double_t min , Double_t max){
  
  

  TH1D* h_ratio1 = (TH1D*)h_sig->Clone("h_ratio1");
  h_ratio1->Reset();


  TH1D* h_ratio2 = (TH1D*)h_sig->Clone("h_ratio2");
  h_ratio2->Reset();
  h_ratio2->Divide(h_signew,h_sigold,1,1);
  h_ratio2->SetFillColor(2);
  h_ratio2->SetFillStyle(3444);



  Int_t nbin=h_ratio1->GetNbinsX();
  Double_t ratio[nbin];
  Double_t error[nbin];
  Double_t numer_nbincontent[nbin];
  Double_t denom_nbincontent[nbin];
  Double_t numer_binerror[nbin];
  Double_t denom_binerror[nbin];

  for(Int_t i=1; i<=nbin; i++){


    numer_nbincontent[i] = h_sig->GetBinContent(i);
    denom_nbincontent[i] = h_sigold->GetBinContent(i);
    numer_binerror[i] = h_sig->GetBinError(i);
    denom_binerror[i] = h_sigold->GetBinError(i);


    if(denom_nbincontent[i]<=0 || numer_nbincontent[i]<=0) continue;
    if(denom_binerror[i]<=0 || numer_binerror[i]<=0) continue;


    ratio[i] = numer_nbincontent[i]/denom_nbincontent[i];
    error[i] = (ratio[i])*sqrt(pow(numer_binerror[i]/numer_nbincontent[i],2)+pow(denom_binerror[i]/denom_nbincontent[i],2));


    h_ratio1->SetBinContent(i,ratio[i]);
    h_ratio1->SetBinError(i,error[i]);
   


  }


  h_ratio1->SetFillColor(kCyan-4);
  h_ratio1->GetXaxis()->SetRangeUser(min,max);
  h_ratio1->GetYaxis()->SetRangeUser(0.2,1.7);
  h_ratio1->SetYTitle("new MC/MC");
  h_ratio1->Draw("9e3");
  h_ratio2->Draw("e3same");


  TLine* l2 = new TLine(min,1.,max,1.);
  l2->SetLineColor(4);
  l2->SetLineStyle(3);
  l2->Draw("same");


}



void myPlotN(TH1D* h_sigold, TH1D* h_sig, TH1D* h_signew){


  h_sigold->SetLineColor(1);
  h_sigold->SetLineWidth(2);
  h_sigold->SetMarkerColor(1);
  h_sigold->SetMarkerStyle(20);
  h_sigold->SetMarkerSize(1);

  h_sig->SetLineColor(kCyan-4);
  h_sig->SetFillColor(kCyan-4);

  h_signew->SetFillColor(2);
  h_signew->SetLineColor(2);
  h_signew->SetFillStyle(3444);



  Double_t ymin = -0.03*(h_sigold->GetMaximum());

  h_sigold->SetMinimum(ymin);

  h_sigold->Draw("e1");
  h_sig->Draw("histesame");
  h_signew->Draw("histesame");
  h_sigold->Draw("e1same");



}


void myPlotR(TH1D* h_sigold, TH1D* h_sig, TH1D* h_signew){


  h_sigold->SetLineColor(1);
  h_sigold->SetLineWidth(2);
  h_sigold->SetMarkerColor(1);
  h_sigold->SetMarkerStyle(20);
  h_sigold->SetMarkerSize(1);

  h_sig->SetLineColor(kCyan-4);
  h_sig->SetFillColor(kCyan-4);

  h_signew->SetFillColor(2);
  h_signew->SetLineColor(2);
  h_signew->SetFillStyle(3444);


  Double_t ymin = -0.03*(h_sigold->GetMaximum());

  h_sigold->SetMinimum(ymin);

  h_sigold->Draw("e1");
  h_sig->Draw("histesame");
  h_signew->Draw("histesame");
  h_sigold->Draw("e1same");



  
  TLegend *leg = new TLegend(0.73, 0.8, 0.98, 1);

  leg->SetFillStyle(1001);
  leg->SetFillColor(10);
  leg->SetBorderSize(1);
  leg->AddEntry(h_sig,"new LHE+pythia8", "f"); 
  leg->AddEntry(h_signew,"old LHE+pythia8", "f"); 
  leg->AddEntry(h_sigold,"old LHE+pythia6", "lp");
  leg->Draw();




}
