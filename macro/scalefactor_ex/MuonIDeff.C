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
#include "Uncor_eff.h"


const float Sf[2][3] = {1.0043, 1.0074, 1.022, 1.0012, 1.0043, 1.014};
const float sigma[2][3] = {0.0004, 0.0005, 0.001, 0.0004, 0.0004, 0.001};



using namespace std;
void MuonIDeff(std::string inputFile){


  //get TTree from file ...
  TreeReader data(inputFile.data());



  // declare histogram
  TH1F* h_muPt = new TH1F("h_muPt","",40,0,1200);
  TH1F* h_muPtID[2][3];
  TH1F* h_muPtID_cor[2][3];

  for(int i=0; i<2; i++){
    for(int j=0; j<3; j++){

      h_muPtID[i][j] = new TH1F(Form("h_muPtID%d%d",i,j),"",40,0,1200);
      h_muPtID[i][j]->Sumw2();

      h_muPtID_cor[i][j] = new TH1F(Form("h_muPtID_cor%d%d",i,j),"",40,0,1200);
      h_muPtID_cor[i][j]->Sumw2();

    } // eta section
  } // pt section


  //100% correlated Sf+1sigma
  float Sf_sigma[2][3];

  for(int i=0; i<2; i++){
    for(int j=0; j<3; j++){

      Sf_sigma[i][j] = Sf[i][j]+sigma[i][j];

    }
  }



  //Event loop
  for(long jEntry=0; jEntry<data.GetEntriesFast() ;jEntry++){

    data.GetEntry(jEntry);


    Int_t    nMu        = data.GetInt("nMu");
    Float_t* muPt       = data.GetPtrFloat("muPt");
    Float_t* muEta      = data.GetPtrFloat("muEta"); 
    Int_t*   muID       = data.GetPtrInt("muPassID");


    for(int i=0; i<nMu; i++){

      
      if(muPt[i]<20) continue;
      h_muPt->Fill(muPt[i]);


      if(muID[i]<=0) continue;

      if(muPt[i]<40){

	if(fabs(muEta[i])<0.8) h_muPtID[0][0]->Fill(muPt[i], Sf[0][0]);
	if(0.8<fabs(muEta[i]) && fabs(muEta[i])<2.1) h_muPtID[0][1]->Fill(muPt[i], Sf[0][1]);
   	if(2.1<fabs(muEta[i]) && fabs(muEta[i])<2.4) h_muPtID[0][2]->Fill(muPt[i], Sf[0][2]);

	// 100% correlated
	if(fabs(muEta[i])<0.8) h_muPtID_cor[0][0]->Fill(muPt[i], Sf_sigma[0][0]);
	if(0.8<fabs(muEta[i]) && fabs(muEta[i])<2.1) h_muPtID_cor[0][1]->Fill(muPt[i], Sf_sigma[0][1]);
   	if(2.1<fabs(muEta[i]) && fabs(muEta[i])<2.4) h_muPtID_cor[0][2]->Fill(muPt[i], Sf_sigma[0][2]);
	
      } //pt 20~40


      if(muPt[i]>40){

	if(fabs(muEta[i])<0.8) h_muPtID[1][0]->Fill(muPt[i], Sf[1][0]);
	if(0.8<fabs(muEta[i]) && fabs(muEta[i])<2.1) h_muPtID[1][1]->Fill(muPt[i], Sf[1][1]);
   	if(2.1<fabs(muEta[i]) && fabs(muEta[i])<2.4) h_muPtID[1][2]->Fill(muPt[i], Sf[1][2]);
	
	// 100% correlated
	if(fabs(muEta[i])<0.8) h_muPtID_cor[1][0]->Fill(muPt[i], Sf_sigma[1][0]);
	if(0.8<fabs(muEta[i]) && fabs(muEta[i])<2.1) h_muPtID_cor[1][1]->Fill(muPt[i], Sf_sigma[1][1]);
   	if(2.1<fabs(muEta[i]) && fabs(muEta[i])<2.4) h_muPtID_cor[1][2]->Fill(muPt[i], Sf_sigma[1][2]);
	
      } //pt 40~100+
     
    } //loop muon


  } //entries 




  // 100% correlated eff
  float denom = h_muPt->Integral();
  float numer = 0.0;
  float numer_sigma = 0.0;

  for(int i=0; i<2; i++){
    for(int j=0; j<3; j++){
      
      numer = numer + h_muPtID[i][j]->Integral();
      numer_sigma = numer_sigma + h_muPtID_cor[i][j]->Integral();

    } // index j
  } // index i
  
  
  float eff = numer/denom;
  float eff_sigma = numer_sigma/denom;
  float sys_cor = fabs(eff_sigma - eff);
  


  // Clear histo
  h_muPt->Clear();
  
  for(int i=0; i<2; i++){
    for(int j=0; j<3; j++){
     
      h_muPtID[i][j]->Clear();
      h_muPtID_cor[i][j]->Clear();

    }
  }



  
  // 100% uncorrelated efficiency
  float uncor_eff=0.0;
  float sys_uncor=0.0;

  for(int i=0; i<2; i++){
    for(int j=0; j<3; j++){

      Uncor_eff(data, uncor_eff, i, j);
      sys_uncor = sys_uncor + pow((uncor_eff-eff),2);

    }
  }

  sys_uncor = sqrt(sys_uncor);


  
  cout<<"Muon ID efficiency is ["<<eff<<"],"<<endl;
  cout<<"with systematic uncerntainty ["<<sys_cor<<"](100% correlated), and ["<<sys_uncor<<"](100% uncorrelated)."<<endl;
  


} //function brace
