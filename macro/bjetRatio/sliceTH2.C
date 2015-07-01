#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <TPad.h>
#include <TH1.h>
#include <TH2.h>
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


using namespace std;
void sliceTH2(std::string inputFile, std::string outputFile, std::string histo){

  
  // load rootfile
  TFile *data = TFile::Open(inputFile.data());


  // load certain TH2 in that rootfile
  TH2D* h2 = (TH2D*)data->Get(histo.data());
  

  // create a new rootfile
  TFile *temp = new TFile(outputFile.data(), "recreate");




  TH1D *hbins[5];
  for(int i=0; i<5; i++){

    hbins[i] = h2->ProjectionX(Form("bin%d",i+1), i+1, i+2);
    //hbins[i]->Write();
    //allbins->Add(hbins[i]);


  }

  TH1F *allbins = (TH1F*)hbins[0]->Clone("allbins");
  
  allbins->Add(hbins[1]);
  allbins->Add(hbins[2]);
  allbins->Add(hbins[3]);
  allbins->Add(hbins[4]);

  allbins->Write();

  temp->Close();


}

