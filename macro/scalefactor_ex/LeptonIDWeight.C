/*

Input arguments

lepton: 0=Electron, 1=Muon
 scale: 0=return central value of scalefactor
        1=return central value of scalefactor +1 sigma


####  THIS IS A TEST VERSION  ####
####  TRY THE COMMAND BELOW   ####
####  FILL ARGUMENTS YOU WANT ####

$root -l LeptonIDWeight.C++\(pt\,eta\,scale\)

  
*/


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


using namespace std;

float LeptonIDWeight(/*int lepton,*/ float pt, float eta, int scale){



  float Sf[2][3] = {1.0043, 1.0074, 1.022, 1.0012, 1.0043, 1.014};
  float sigma[2][3] = {0.0004, 0.0005, 0.001, 0.0004, 0.0004, 0.001};

  // pt and eta section
  double ptX[]={20,40,100};
  const int nPtBins = sizeof(ptX)/sizeof(ptX[0])-1;

  double etaX[]={0,0.8,2.1,2.4};
  const int nEtaBins = sizeof(etaX)/sizeof(etaX[0])-1;

  TH1F* h_pt  = new TH1F("h_pt","",nPtBins,ptX);
  TH1F* h_eta = new TH1F("h_eta","",nEtaBins,etaX);



  // Sf+1sigma
  if(scale==1){    
    for(int i=0; i<2; i++){
      for(int j=0; j<3; j++){
	
	Sf[i][j] = Sf[i][j]+sigma[i][j];
	
      }
    }
  }
  

  // choose scalefactor
  int ptBinIndex = h_pt->FindBin(pt)-1;      
  if(ptBinIndex <0) return 1.0; // remove muonPt < 20 GeV
  if(ptBinIndex == nPtBins) ptBinIndex -= 1; // overflow bin, use the same scale factor as 40-100 GeV
  
  int etaBinIndex = h_eta->FindBin(fabs(eta))-1;
  if(etaBinIndex<0 || etaBinIndex >= nEtaBins) return 1.0;
  
  
  return Sf[ptBinIndex][etaBinIndex];
 


} //function brace
