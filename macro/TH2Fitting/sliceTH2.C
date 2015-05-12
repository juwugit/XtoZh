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
void sliceTH2(std::string inputFile, /*std::string outputFile,*/ std::string histo){

  
  // load rootfile
  TFile *data = TFile::Open(inputFile.data());


  // load certain TH2 in that rootfile
  TH2* h2 = (TH2F*)data->Get(histo.data());
  

  // create a new rootfile
  //TFile *temp = new TFile(outputFile.data(), "recreate");


  TCanvas *c[20];


  TH1 *hbins[20];
  for(int i=0; i<20; i++){

    hbins[i] = h2->ProjectionX(Form("bin%d",i+1), i+1, i+2);
    //hbins[i]->Write();
    c[i] = new TCanvas(Form("bin%d",i+1));
    c[i]->cd();
    hbins[i]->Draw();
    c[i]->Print(Form("bin%d.png",i+1));


  }




  //temp->Close();


}

