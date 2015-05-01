//root -q -b -l MuonIDeff.C++\(\"inputFile\"\)

#include <map>
#include <vector>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <TH1D.h>
#include <TRandom.h>
#include <TLorentzVector.h>
#include <TFile.h>
#include "/home/juwu/XtoZh/macro/untuplizer.h"
//#include "Uncor_eff.h"


const float Sf[4][5] = {1.005, 0.981, 1.0, 0.980, 1.017, 1.004, 0.991, 1.0, 0.992, 1.019, 1.008, 0.994, 1.0, 1.004, 1.005, 1.008, 0.999, 1.0, 1.006, 1.009};
const float sigma[4][5] = {0.003, 0.003, 0.0, 0.005, 0.006, 0.001, 0.001, 0.0, 0.002, 0.003, 0.001, 0.001, 0.0, 0.002, 0.001, 0.001, 0.001, 0.0, 0.003, 0.002};



using namespace std;
void ElectronIDeff(std::string inputFile){


  //get TTree from file ...
  TreeReader data(inputFile.data());



  //TEST
  double ptX[]={20,30,40,50,200};
  const int nPtBins = sizeof(ptX)/sizeof(ptX[0])-1;

  double etaX[]={0,0.8,1.442,1.556,2.0,2.5};
  const int nEtaBins = sizeof(etaX)/sizeof(etaX[0])-1;

  TH1F* h_pt  = new TH1F("h_pt","",nPtBins,ptX);
  TH1F* h_eta = new TH1F("h_eta","",nEtaBins,etaX);



  // declare histogram
  TH1F* h_muPt = new TH1F("h_muPt","",40,0,1200);  
  TH1F* h_muPtID[4][5];
  TH1F* h_muPtID_cor[4][5];

  for(int i=0; i<4; i++){
    for(int j=0; j<5; j++){

      h_muPtID[i][j] = new TH1F(Form("h_muPtID%d%d",i,j),"",40,0,1200);
      h_muPtID[i][j]->Sumw2();

      h_muPtID_cor[i][j] = new TH1F(Form("h_muPtID_cor%d%d",i,j),"",40,0,1200);
      h_muPtID_cor[i][j]->Sumw2();

    } // eta section
  } // pt section


  //100% correlated Sf+1sigma
  float Sf_sigma[4][5];

  for(int i=0; i<4; i++){
    for(int j=0; j<5; j++){

      Sf_sigma[i][j] = Sf[i][j]+sigma[i][j];

    }
  }



  //Event loop
  for(long jEntry=0; jEntry<data.GetEntriesFast() ;jEntry++){

    data.GetEntry(jEntry);


    Int_t    nMu        = data.GetInt("nEle");
    Float_t* muPt       = data.GetPtrFloat("elePt");
    Float_t* muEta      = data.GetPtrFloat("eleEta"); 
    Int_t*   muID       = data.GetPtrInt("elePassID");


    for(int i=0; i<nMu; i++){

      if(muPt[i]>20) h_muPt->Fill(muPt[i]);
      if(muID[i]<=0) continue;

      int ptBinIndex = h_pt->FindBin(muPt[i])-1;      
      if(ptBinIndex <0) continue; // remove muonPt < 20 GeV
      if(ptBinIndex == nPtBins) ptBinIndex -= 1; // overflow bin, use the same scale factor as 40-100 GeV

      
      int etaBinIndex = h_eta->FindBin(fabs(muEta[i]))-1;
      if(etaBinIndex<0 || etaBinIndex >= nEtaBins) continue;
      
      h_muPtID[ptBinIndex][etaBinIndex]->Fill(muPt[i], Sf[ptBinIndex][etaBinIndex]);
      h_muPtID_cor[ptBinIndex][etaBinIndex]->Fill(muPt[i], Sf_sigma[ptBinIndex][etaBinIndex]);

     
    } //loop muon


  } //entries 




  // 100% correlated eff
  float denom = h_muPt->Integral();
  float numer = 0.0;
  float numer_sigma = 0.0;
  float diff[4][5];

  for(int i=0; i<4; i++){
    for(int j=0; j<5; j++){
      
      numer = numer + h_muPtID[i][j]->Integral();
      numer_sigma = numer_sigma + h_muPtID_cor[i][j]->Integral();
      diff[i][j] = (h_muPtID_cor[i][j]->Integral()) - (h_muPtID[i][j]->Integral());

    } // index j
  } // index i
  
  float eff = numer/denom;
  float eff_sigma = numer_sigma/denom;
  float sys_cor = fabs(eff_sigma - eff);



  // 100% uncorrelated
  float sys_uncor=0.0;

  for(int i=0; i<4; i++){
    for(int j=0; j<5; j++){
      
      sys_uncor = sys_uncor + pow((diff[i][j]/denom),2); // uncor_eff-eff

    }
  }

  sys_uncor = sqrt(sys_uncor);



  // Clear histo
  h_muPt->Clear();
  
  for(int i=0; i<4; i++){
    for(int j=0; j<5; j++){
     
      h_muPtID[i][j]->Clear();
      h_muPtID_cor[i][j]->Clear();

    }
  }




  
  cout<<"Electron ID efficiency is ["<<eff<<"],"<<endl;
  cout<<"with systematic uncerntainty ["<<sys_cor<<"](100% correlated), and ["<<sys_uncor<<"](100% uncorrelated)."<<endl;
  


} //function brace
