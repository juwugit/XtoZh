/*

Input arguments

scale: 0=return central value of scalefactor
       1=return central value of scalefactor +1 sigma


####  THIS IS A TEST VERSION  ####
####  TRY THE COMMAND BELOW   ####
####  FILL ARGUMENTS YOU WANT ####

$root -l ElectronIDWeight.C++\(pt\,eta\,scale\)

  
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

float ElectronIDWeight(float pt, float eta, int scale=0){



  float Sf[4][5] = {1.005, 0.981, 1.0, 0.980, 1.017, 1.004, 0.991, 1.0, 0.992, 1.019, 1.008, 0.994, 1.0, 1.004, 1.005, 1.008, 0.999, 1.0, 1.006, 1.009};
  float sigma[4][5] = {0.003, 0.003, 0.0, 0.005, 0.006, 0.001, 0.001, 0.0, 0.002, 0.003, 0.001, 0.001, 0.0, 0.002, 0.001, 0.001, 0.001, 0.0, 0.003, 0.002};

  // pt and eta section
  double ptX[]={20,30,40,50,200};
  const int nPtBins = sizeof(ptX)/sizeof(ptX[0])-1;

  double etaX[]={0,0.8,1.442,1.556,2.0,2.5};
  const int nEtaBins = sizeof(etaX)/sizeof(etaX[0])-1;

  TH1F* h_pt  = new TH1F("h_pt","",nPtBins,ptX);
  TH1F* h_eta = new TH1F("h_eta","",nEtaBins,etaX);


  // choose scalefactor
  int ptBinIndex = h_pt->FindBin(pt)-1;      
  h_pt->Clear();

  if(ptBinIndex <0) return 1.0; // remove muonPt < 20 GeV
  if(ptBinIndex == nPtBins) ptBinIndex -= 1; // overflow bin, use the same scale factor as 50-200 GeV
  
  int etaBinIndex = h_eta->FindBin(fabs(eta))-1;
  h_eta->Clear();

  if(etaBinIndex<0 || etaBinIndex >= nEtaBins) return 1.0;
  
  
  return (Sf[ptBinIndex][etaBinIndex]+scale*sigma[ptBinIndex][etaBinIndex]);


} //function brace
