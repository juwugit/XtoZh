/*

Input arguments

scale: 0=return central value of scalefactor
       1=return central value of scalefactor +1 sigma


####  THIS IS A TEST VERSION  ####
####  TRY THE COMMAND BELOW   ####
####  FILL ARGUMENTS YOU WANT ####

$root -l MuonIDWeight.C++\(pt\,eta\,scale\)

  
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

float MuonIDWeight(float pt, float eta, int scale=0){



  float Sf[2][3] = {1.0043, 1.0074, 1.022, 1.0012, 1.0043, 1.014};
  float sigma[2][3] = {0.0004, 0.0005, 0.001, 0.0004, 0.0004, 0.001};

  // pt and eta section
  double ptX[]={20,40,100};
  const int nPtBins = sizeof(ptX)/sizeof(ptX[0])-1;

  double etaX[]={0,0.8,2.1,2.4};
  const int nEtaBins = sizeof(etaX)/sizeof(etaX[0])-1;

  TH1F* h_pt  = new TH1F("h_pt","",nPtBins,ptX);
  TH1F* h_eta = new TH1F("h_eta","",nEtaBins,etaX);


  // choose scalefactor
  int ptBinIndex = h_pt->FindBin(pt)-1;      
  h_pt->Clear();

  if(ptBinIndex <0) return 1.0; // remove muonPt < 20 GeV
  if(ptBinIndex == nPtBins) ptBinIndex -= 1; // overflow bin, use the same scale factor as 40-100 GeV
  
  int etaBinIndex = h_eta->FindBin(fabs(eta))-1;
  h_eta->Clear();

  if(etaBinIndex<0 || etaBinIndex >= nEtaBins) return 1.0;
  
  
  return (Sf[ptBinIndex][etaBinIndex]+scale*sigma[ptBinIndex][etaBinIndex]);



} //function brace
