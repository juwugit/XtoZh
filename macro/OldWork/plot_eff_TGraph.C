//root -q -b -l plot_eff.C++\(\"inputFile\"\)

#include <vector>
#include <iostream>
#include <algorithm>
#include <TH1D.h>
#include <TRandom.h>
#include <TLorentzVector.h>
#include <TFile.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TH1F.h>
#include <TH1.h>
#include <TCanvas.h>
#include <TROOT.h>
#include "TImage.h"
#include "TSystem.h"


TGraphErrors* Eff(TH1*, TH1*);


using namespace std;
void plot_eff(std::string inputFile){


  
  TFile* root = new TFile(inputFile.data());   
 

  TH1F* h_CA8jetPt      = (TH1F*)root->Get("h_CA8jetPt"); 
  TH1F* h_CA8jetPt_ID   = (TH1F*)root->Get("h_CA8jetPt_ID");
  TH1F* h_CA8jetEta     = (TH1F*)root->Get("h_CA8jetEta");
  TH1F* h_CA8jetEta_ID  = (TH1F*)root->Get("h_CA8jetEta_ID");

  TH1F* h_elePt         = (TH1F*)root->Get("h_elePt");
  TH1F* h_eleSecPt      = (TH1F*)root->Get("h_eleSecPt");
  TH1F* h_elePt_ID      = (TH1F*)root->Get("h_elePt_ID");
  TH1F* h_eleSecPt_ID   = (TH1F*)root->Get("h_eleSecPt_ID");
  TH1F* h_eleEta        = (TH1F*)root->Get("h_eleEta");
  TH1F* h_eleEta_ID     = (TH1F*)root->Get("h_eleEta_ID");

  TH1F* h_muPt          = (TH1F*)root->Get("h_muPt");
  TH1F* h_muSecPt       = (TH1F*)root->Get("h_muSecPt");
  TH1F* h_muPt_track    = (TH1F*)root->Get("h_muPt_track");
  TH1F* h_muSecPt_track = (TH1F*)root->Get("h_muSecPt_track");
  TH1F* h_muPt_globe    = (TH1F*)root->Get("h_muPt_globe");
  TH1F* h_muSecPt_globe = (TH1F*)root->Get("h_muSecPt_track");
  TH1F* h_muEta         = (TH1F*)root->Get("h_muEta");
  TH1F* h_muEta_track   = (TH1F*)root->Get("h_muEta_track");
  TH1F* h_muEta_globe   = (TH1F*)root->Get("h_muEta_globe");


  //------------------------------------------------------------

  TGraphErrors* g11 = Eff(h_muEta_globe,h_muEta);

  g11->SetTitle("");
  g11->GetYaxis()->SetTitle("Efficiency");
  g11->GetYaxis()->SetTitleOffset(1.3);
  g11->SetLineColor(4);
  g11->SetMarkerStyle(20);
  g11->SetLineWidth(2);
  g11->GetXaxis()->SetTitle("Muon #eta");
  g11->GetXaxis()->SetTitleOffset(1.3);

  gROOT->SetStyle("Plain");
  TCanvas *c11= new TCanvas("c11","",200,10,800,800);

  g11->SetMarkerColor(4);
  g11->Draw("ap");

  gSystem->ProcessEvents();
  TImage *img11 = TImage::Create();
  img11->FromPad(c11);
  img11->WriteImage("h_GlobeMuEta_Eff.png");
  delete c11;
  delete img11;


  //------------------------------------------------------------

  TGraphErrors* g10 = Eff(h_muEta_track,h_muEta);

  g10->SetTitle("");
  g10->GetYaxis()->SetTitle("Efficiency");
  g10->GetYaxis()->SetTitleOffset(1.3);
  g10->SetLineColor(4);
  g10->SetMarkerStyle(20);
  g10->SetLineWidth(2);
  g10->GetXaxis()->SetTitle("Muon #eta");
  g10->GetXaxis()->SetTitleOffset(1.3);

  gROOT->SetStyle("Plain");
  TCanvas *c10= new TCanvas("c10","",200,10,800,800);

  g10->SetMarkerColor(4);
  g10->Draw("ap");

  gSystem->ProcessEvents();
  TImage *img10 = TImage::Create();
  img10->FromPad(c10);
  img10->WriteImage("h_TrackMuEta_Eff.png");
  delete c10;
  delete img10;



  //------------------------------------------------------

  TGraphErrors* g9 = Eff(h_muSecPt_globe,h_muSecPt);

  g9->SetTitle("");
  g9->GetYaxis()->SetTitle("Efficiency");
  g9->GetYaxis()->SetTitleOffset(1.3);
  g9->SetLineColor(4);
  g9->SetMarkerStyle(20);
  g9->SetLineWidth(2);
  g9->GetXaxis()->SetTitle("Muon P_{T} [GeV]");
  g9->GetXaxis()->SetTitleOffset(1.3);

  gROOT->SetStyle("Plain");
  TCanvas *c9= new TCanvas("c9","",200,10,800,800);

  g9->SetMarkerColor(4);
  g9->Draw("ap");

  gSystem->ProcessEvents();
  TImage *img9 = TImage::Create();
  img9->FromPad(c9);
  img9->WriteImage("h_GlobeMuSecPt_Eff.png");
  delete c9;
  delete img9;


  //--------------------------------------------

  TGraphErrors* g8 = Eff(h_muSecPt_track,h_muSecPt);

  g8->SetTitle("");
  g8->GetYaxis()->SetTitle("Efficiency");
  g8->GetYaxis()->SetTitleOffset(1.3);
  g8->SetLineColor(4);
  g8->SetMarkerStyle(20);
  g8->SetLineWidth(2);
  g8->GetXaxis()->SetTitle("Muon P_{T} [GeV]");
  g8->GetXaxis()->SetTitleOffset(1.3);

  gROOT->SetStyle("Plain");
  TCanvas *c8= new TCanvas("c8","",200,10,800,800);

  g8->SetMarkerColor(4);
  g8->Draw("ap");

  gSystem->ProcessEvents();
  TImage *img8 = TImage::Create();
  img8->FromPad(c8);
  img8->WriteImage("h_TrackMuSecPt_Eff.png");
  delete c8;
  delete img8;


  //------------------------------------------------------------

  TGraphErrors* g7 = Eff(h_muPt_globe,h_muPt);

  g7->SetTitle("");
  g7->GetYaxis()->SetTitle("Efficiency");
  g7->GetYaxis()->SetTitleOffset(1.3);
  g7->SetLineColor(4);
  g7->SetMarkerStyle(20);
  g7->SetLineWidth(2);
  g7->GetXaxis()->SetTitle("Muon P_{T} [GeV]");
  g7->GetXaxis()->SetTitleOffset(1.3);

  gROOT->SetStyle("Plain");
  TCanvas *c7= new TCanvas("c7","",200,10,800,800);

  g7->SetMarkerColor(4);
  g7->Draw("ap");

  gSystem->ProcessEvents();
  TImage *img7 = TImage::Create();
  img7->FromPad(c7);
  img7->WriteImage("h_GlobeMuPt_Eff.png");
  delete c7;
  delete img7;

  //---------------------------------------------------------

  TGraphErrors* g6 = Eff(h_muPt_track,h_muPt);

  g6->SetTitle("");
  g6->GetYaxis()->SetTitle("Efficiency");
  g6->GetYaxis()->SetTitleOffset(1.3);
  g6->SetLineColor(4);
  g6->SetMarkerStyle(20);
  g6->SetLineWidth(2);
  g6->GetXaxis()->SetTitle("Muon P_{T} [GeV]");
  g6->GetXaxis()->SetTitleOffset(1.3);

  gROOT->SetStyle("Plain");
  TCanvas *c6= new TCanvas("c6","",200,10,800,800);

  g6->SetMarkerColor(4);
  g6->Draw("ap");

  gSystem->ProcessEvents();
  TImage *img6 = TImage::Create();
  img6->FromPad(c6);
  img6->WriteImage("h_TrackMuPt_Eff.png");
  delete c6;
  delete img6;




  //-------------------------------------------------------------

  TGraphErrors* g5 = Eff(h_eleEta_ID,h_eleEta);

  g5->SetTitle("");
  g5->GetYaxis()->SetTitle("Efficiency");
  g5->GetYaxis()->SetTitleOffset(1.3);
  g5->SetLineColor(4);
  g5->SetMarkerStyle(20);
  g5->SetLineWidth(2);
  g5->GetXaxis()->SetTitle("Electron #eta");
  g5->GetXaxis()->SetTitleOffset(1.3);

  gROOT->SetStyle("Plain");
  TCanvas *c5= new TCanvas("c5","",200,10,800,800);

  g5->SetMarkerColor(4);
  g5->Draw("ap");

  gSystem->ProcessEvents();
  TImage *img5 = TImage::Create();
  img5->FromPad(c5);
  img5->WriteImage("h_eleEta_Eff.png");
  delete c5;
  delete img5;


  //-----------------------------------------------------

  TGraphErrors* g4 = Eff(h_eleSecPt_ID,h_eleSecPt);

  g4->SetTitle("");
  g4->GetYaxis()->SetTitle("Efficiency");
  g4->GetYaxis()->SetTitleOffset(1.3);
  g4->SetLineColor(4);
  g4->SetMarkerStyle(20);
  g4->SetLineWidth(2);
  g4->GetXaxis()->SetTitle("Electron Sec P_{T} [GeV]");
  g4->GetXaxis()->SetTitleOffset(1.3);

  gROOT->SetStyle("Plain");
  TCanvas *c4= new TCanvas("c4","",200,10,800,800);

  g4->SetMarkerColor(4);
  g4->Draw("ap");

  gSystem->ProcessEvents();
  TImage *img4 = TImage::Create();
  img4->FromPad(c4);
  img4->WriteImage("h_eleSecPt_Eff.png");
  delete c4;
  delete img4;



  //--------------------------------------------------------------

  TGraphErrors* g3 = Eff(h_elePt_ID,h_elePt);

  g3->SetTitle("");
  g3->GetYaxis()->SetTitle("Efficiency");
  g3->GetYaxis()->SetTitleOffset(1.3);
  g3->SetLineColor(4);
  g3->SetMarkerStyle(20);
  g3->SetLineWidth(2);
  g3->GetXaxis()->SetTitle("Electron Leading P_{T} [GeV]");
  g3->GetXaxis()->SetTitleOffset(1.3);

  gROOT->SetStyle("Plain");
  TCanvas *c3= new TCanvas("c3","",200,10,800,800);

  g3->SetMarkerColor(4);
  g3->Draw("ap");

  gSystem->ProcessEvents();
  TImage *img3 = TImage::Create();
  img3->FromPad(c3);
  img3->WriteImage("h_elePt_Eff.png");
  delete c3;
  delete img3;


  //--------------------------------------------------------

  TGraphErrors* g2 = Eff(h_CA8jetEta_ID,h_CA8jetEta);

  g2->SetTitle("");
  g2->GetYaxis()->SetTitle("Efficiency");
  g2->GetYaxis()->SetTitleOffset(1.3);
  g2->SetLineColor(4);
  g2->SetMarkerStyle(20);
  g2->SetLineWidth(2);
  g2->GetXaxis()->SetTitle("CA8jet #eta");
  g2->GetXaxis()->SetTitleOffset(1.3);

  gROOT->SetStyle("Plain");
  TCanvas *c2= new TCanvas("c2","",200,10,800,800);

  g2->SetMarkerColor(4);
  g2->Draw("ap");

  gSystem->ProcessEvents();
  TImage *img2 = TImage::Create();
  img2->FromPad(c2);
  img2->WriteImage("h_CA8jetEta_Eff.png");
  delete c2;
  delete img2;

  //------------------------------------------------

  TGraphErrors* g1 = Eff(h_CA8jetPt_ID,h_CA8jetPt);

  g1->SetTitle(""); 
  g1->GetYaxis()->SetTitle("Efficiency");
  g1->GetYaxis()->SetTitleOffset(1.3);
  g1->SetLineColor(4);
  g1->SetMarkerStyle(20);
  g1->SetLineWidth(2);
  g1->GetXaxis()->SetTitle("CA8jet P_{T} [GeV]");
  g1->GetXaxis()->SetTitleOffset(1.3);

  gROOT->SetStyle("Plain");
  TCanvas *c1= new TCanvas("c1","",200,10,800,800);

  g1->SetMarkerColor(4);
  g1->Draw("ap");

  gSystem->ProcessEvents();
  TImage *img1 = TImage::Create();
  img1->FromPad(c1);
  img1->WriteImage("h_CA8jetPt_Eff.png");
  delete c1;
  delete img1;









}



TGraphErrors* Eff(TH1* NUMER, TH1* DENOM){


  int nbinsx = NUMER->GetNbinsX();

  double eff[nbinsx];
  double nbincontent[nbinsx];
  double errory[nbinsx];
  double errorx[nbinsx];


  for (int i=1; i<=nbinsx; i++ ){
 
    double numer = NUMER->GetBinContent(i);
    double denom = DENOM->GetBinContent(i);

    nbincontent[i] = NUMER->GetXaxis()->GetBinCenter(i);

    if (denom!=0 ) eff[i]=numer/denom;
    else eff[i]=0;
  
    if (denom!=0){

    double ratio1[nbinsx];
    ratio1[i] = pow(numer,3)/pow(denom,6);
    double ratio2[nbinsx];
    ratio2[i] = pow(numer,2)/pow(denom,3);
    double ratio3[nbinsx];
    ratio3[i] = pow(numer,3)/pow(denom,4);


    errory[i]=sqrt(ratio1[i]+ratio2[i]-ratio3[i]);

    
    if(errory[i]>0.5){
      cout<<"denom:"<<denom<<"numer:"<<numer<<endl;
      cout<<"ratio1:"<<ratio1[i]<<"  ratio2:"<<ratio2[i]<<"  ratio3:"<<ratio3[i]<<endl;
      cout<<"eff"<<eff[i]<<endl;
      cout<<"error:"<<errory[i]<<endl;
    }
    

    }

    else errory[i]=0;
    errorx[i]=0;
  

  }


  TGraphErrors* g = new TGraphErrors(nbinsx,nbincontent,eff,errorx,errory);
  return g;


}
