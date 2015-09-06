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
void pushBKD(std::string inputFile1, std::string inputFile2, std::string histo){


  //TFile *Data = TFile::Open(inputFile1.data());
  TFile *BKD  = TFile::Open(inputFile2.data());


  TH2F* h_temp = (TH2F*)BKD->Get(histo.data());


  TFile *temp = new TFile(inputFile1.data(), "update");
  temp->cd();


  string HisName2;
  if (histo.find("MxCA8jetCSV")!= std::string::npos)
    HisName2.assign("h_n_MxCA8jetCSV");
  else if (histo.find("MxSubjetCSV")!= std::string::npos)
    HisName2.assign("h_n_MxSubjetCSV");
  else
    HisName2.assign("!! WRONG histo");


  string HisName3;
  if (inputFile2.find("TTTo2L2Nu2B")!= std::string::npos)
    HisName3.assign("_FINAL_TTTo2L2Nu2B");
  else if (inputFile2.find("ZZ")!= std::string::npos)
    HisName3.assign("_FINAL_DiBZZ");
  else if (inputFile2.find("WZ")!= std::string::npos)
    HisName3.assign("_FINAL_DiBWZ");
  else if (inputFile2.find("WW")!= std::string::npos)
    HisName3.assign("_FINAL_DiBWW");
  else
    HisName3.assign("!! WRONG inputFile2");


  string CorrHisName;
  CorrHisName=HisName2+HisName3;


  h_temp->SetName(CorrHisName.data());
  h_temp->Write();
  temp->Close();
  
}
