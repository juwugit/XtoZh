//root -q -b -l plot_eff.C++\(\"inputFile\"\,\)

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



using namespace std;
void plot_eff(std::string inputFile , std::string outputFile){


  
  TFile* root = new TFile(inputFile.data());   
 

  TH1F* h_CA8jetPt      = (TH1F*)root->Get("h_CA8jetPt"); 
  h_CA8jetPt->Sumw2();

  TH1F* h_CA8jetPt_ID   = (TH1F*)root->Get("h_CA8jetPt_ID");
  h_CA8jetPt_ID->Sumw2();

  TH1F* h_CA8jetEta     = (TH1F*)root->Get("h_CA8jetEta");
  h_CA8jetEta->Sumw2();

  TH1F* h_CA8jetEta_ID  = (TH1F*)root->Get("h_CA8jetEta_ID");
  h_CA8jetEta_ID->Sumw2();


  
  TH1F* h_elePt         = (TH1F*)root->Get("h_elePt");
  h_elePt->Sumw2();

  TH1F* h_eleSecPt      = (TH1F*)root->Get("h_eleSecPt");
  h_eleSecPt->Sumw2();

  TH1F* h_elePt_ID      = (TH1F*)root->Get("h_elePt_ID");
  h_elePt_ID->Sumw2();

  TH1F* h_eleSecPt_ID   = (TH1F*)root->Get("h_eleSecPt_ID");
  h_eleSecPt_ID->Sumw2();

  TH1F* h_eleEta        = (TH1F*)root->Get("h_eleEta");
  h_eleEta->Sumw2();

  TH1F* h_eleEta_ID     = (TH1F*)root->Get("h_eleEta_ID");
  h_eleEta_ID->Sumw2();

  
  TH1F* h_muPt          = (TH1F*)root->Get("h_muPt");
  h_muPt->Sumw2();

  TH1F* h_muSecPt       = (TH1F*)root->Get("h_muSecPt");
  h_muSecPt->Sumw2();

  TH1F* h_muPt_track    = (TH1F*)root->Get("h_muPt_track");
  h_muPt_track->Sumw2();

  TH1F* h_muSecPt_track = (TH1F*)root->Get("h_muSecPt_track");
  h_muSecPt_track->Sumw2();

  TH1F* h_muPt_globe    = (TH1F*)root->Get("h_muPt_globe");
  h_muPt_globe->Sumw2();

  TH1F* h_muSecPt_globe = (TH1F*)root->Get("h_muSecPt_globe");
  h_muSecPt_globe->Sumw2();

  TH1F* h_muEta         = (TH1F*)root->Get("h_muEta");
  h_muEta->Sumw2();

  TH1F* h_muEta_track   = (TH1F*)root->Get("h_muEta_track");
  h_muEta_track->Sumw2();

  TH1F* h_muEta_globe   = (TH1F*)root->Get("h_muEta_globe");
  h_muEta_globe->Sumw2();

  



  // Eff plots
  TH1F* h_CA8jetPt_eff  = (TH1F*)h_CA8jetPt->Clone("h_CA8jetPt_eff");
  h_CA8jetPt_eff->Divide(h_CA8jetPt_ID,h_CA8jetPt,1,1,"B");

  TH1F* h_CA8jetEta_eff = (TH1F*)h_CA8jetEta->Clone("h_CA8jetEta_eff");
  h_CA8jetEta_eff->Divide(h_CA8jetEta_ID,h_CA8jetEta,1,1,"B");


    
  TH1F* h_elePt_eff     = (TH1F*)h_elePt->Clone("h_elePt_eff");
  h_elePt_eff->Divide(h_elePt_ID,h_elePt,1,1,"B");

  TH1F* h_eleSecPt_eff  = (TH1F*)h_eleSecPt->Clone("h_eleSecPt_eff");
  h_eleSecPt_eff->Divide(h_eleSecPt_ID,h_eleSecPt,1,1,"B");

  TH1F* h_eleEta_eff    = (TH1F*)h_eleEta->Clone("h_eleEta_eff");
  h_eleEta_eff->Divide(h_eleEta_ID,h_eleEta,1,1,"B");
  



  TH1F* h_TrackMuPt_eff = (TH1F*)h_muPt->Clone("h_TrackMuPt_eff");
  h_TrackMuPt_eff->Divide(h_muPt_track,h_muPt,1,1,"B");

  TH1F* h_GlobeMuPt_eff = (TH1F*)h_muPt->Clone("h_GlobeMuPt_eff");
  h_GlobeMuPt_eff->Divide(h_muPt_globe,h_muPt,1,1,"B");

  TH1F* h_TrackMuSecPt_eff = (TH1F*)h_muSecPt->Clone("h_TrackMuSecPt_eff");
  h_TrackMuSecPt_eff->Divide(h_muSecPt_track,h_muSecPt,1,1,"B");

  TH1F* h_GlobeMuSecPt_eff = (TH1F*)h_muSecPt->Clone("h_GlobeMuSecPt_eff");
  h_GlobeMuSecPt_eff->Divide(h_muSecPt_globe,h_muSecPt,1,1,"B");

  TH1F* h_TrackMuEta_eff= (TH1F*)h_muEta->Clone("h_TrackMuEta_eff");
  h_TrackMuEta_eff->Divide(h_muEta_track,h_muEta,1,1,"B");

  TH1F* h_GlobeMuEta_eff= (TH1F*)h_muEta->Clone("h_GlobeMuEta_eff");
  h_GlobeMuEta_eff->Divide(h_muEta_globe,h_muEta,1,1,"B");



  

  TFile* outFile = new TFile(outputFile.data(),"recreate");

  h_CA8jetPt_eff->Write();
  h_CA8jetEta_eff->Write();

  
  h_elePt_eff->Write();
  h_eleSecPt_eff->Write();
  h_eleEta_eff->Write();



  h_TrackMuPt_eff->Write();
  h_GlobeMuPt_eff->Write();
  h_TrackMuSecPt_eff->Write();
  h_GlobeMuSecPt_eff->Write();
  h_TrackMuEta_eff->Write();
  h_GlobeMuEta_eff->Write();


  outFile->Close();


}

