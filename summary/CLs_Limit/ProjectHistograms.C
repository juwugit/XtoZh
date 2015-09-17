#include <iostream>
#include <fstream>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TH2F.h>
#include <cstdlib>

void ChangeOneBin(TH2F* h_in, int ibin, string name,TH1F* h[]){

  cout<<"Here:"<<ibin<<endl;  
  
  h[ibin] = (TH1F*)h_in->ProjectionX(Form("%s_%d",name.data(),ibin),ibin,ibin);
  
  
  TFile *f2 = new TFile(Form("output_0819_%d.root",ibin) , "UPDATE");
  h[ibin]->Write();
  f2->Close();
  
  
}

void AllBin(TH2F* h_in, int ibin, string name,TH1F* h[]){
  
  cout<<"Here:"<<ibin<<endl;  
  h[20] = (TH1F*)h_in->ProjectionX(Form("%s",name.data()),1,6);
   
  TFile *f2 = new TFile("Shape1d_0819.root", "UPDATE");
  h[20]->Write();
  f2->Close();
  
}



void ProjectHistograms(string inputsigFile, string inputsigFile_Up, string inputsigFile_Down, string inputdataFile, string inputdataFile_Up, string inputdataFile_Down)
{


  TFile* fresult = new TFile(inputdataFile.data() , "read");
  TFile* fresult_up = new TFile(inputdataFile_Up.data() , "read");
  TFile* fresult_down = new TFile(inputdataFile_Down.data() , "read");
  
  TFile* fsig = new TFile(inputsigFile.data(),"read");
  TFile* fsig_up = new TFile(inputsigFile_Up.data(),"read");
  TFile* fsig_down = new TFile(inputsigFile_Down.data(),"read");

  
  
  string DATA_name="h_sigMxSubjetCSV";  
  TH2F *h2_data=(TH2F*)fresult->Get(DATA_name.data());


  string SIG_name="h_sigMxSubjetCSV";
  TH2F *h2_sig=(TH2F*)fsig->Get(SIG_name.data());
  TH2F *h2_sig_up=(TH2F*)fsig_up->Get(SIG_name.data());
  TH2F *h2_sig_down=(TH2F*)fsig_down->Get(SIG_name.data());
  

  string DY_name="h_n_MxSubjetCSV_FINAL_DYJets";
  TH2F *h2_background_DY=(TH2F*)fresult->Get(DY_name.data());
  TH2F *h2_background_DY_up=(TH2F*)fresult_up->Get(DY_name.data());
  TH2F *h2_background_DY_down=(TH2F*)fresult_down->Get(DY_name.data());


  string TT_name="h_n_MxSubjetCSV_FINAL_TTTo2L2Nu2B";
  TH2F *h2_background_TT=(TH2F*)fresult->Get(TT_name.data());
  TH2F *h2_background_TT_up=(TH2F*)fresult_up->Get(TT_name.data());
  TH2F *h2_background_TT_down=(TH2F*)fresult_down->Get(TT_name.data());


  string ZZ_name="h_n_MxSubjetCSV_FINAL_DiBZZ";
  TH2F *h2_background_ZZ=(TH2F*)fresult->Get(ZZ_name.data());
  TH2F *h2_background_ZZ_up=(TH2F*)fresult_up->Get(ZZ_name.data());
  TH2F *h2_background_ZZ_down=(TH2F*)fresult_down->Get(ZZ_name.data());


  string WZ_name="h_n_MxSubjetCSV_FINAL_DiBWZ";
  TH2F *h2_background_WZ=(TH2F*)fresult->Get(WZ_name.data());
  TH2F *h2_background_WZ_up=(TH2F*)fresult_up->Get(WZ_name.data());
  TH2F *h2_background_WZ_down=(TH2F*)fresult_down->Get(WZ_name.data());

  
  int NbinX=0;
  NbinX=h2_background_DY->GetNbinsY();
  
  
  TH1F *h_DATA[50],*h_DY[50],*h_SIG[50],*h_TT[50],*h_ZZ[50],*h_WZ[50]; 
  TH1F *h_DY_up[50],*h_SIG_up[50],*h_TT_up[50],*h_ZZ_up[50],*h_WZ_up[50]; 
  TH1F *h_DY_down[50],*h_SIG_down[50],*h_TT_down[50],*h_ZZ_down[50],*h_WZ_down[50];

  TString neam="test";
 
  for(int ibin=1;ibin<=NbinX;ibin++)
  {
    
    ChangeOneBin(h2_data,              ibin,"data_obs",h_DATA);

    ChangeOneBin(h2_sig,               ibin,"signal",h_SIG);
    ChangeOneBin(h2_sig_up,            ibin,"signal_sigmaUp",h_SIG_up);
    ChangeOneBin(h2_sig_down,          ibin,"signal_sigmaDown",h_SIG_down);

    ChangeOneBin(h2_background_DY,     ibin,"background_DY" ,h_DY);
    ChangeOneBin(h2_background_DY_up,  ibin,"background_DY_alphaUp" ,h_DY_up);
    ChangeOneBin(h2_background_DY_down,ibin,"background_DY_alphaDown" ,h_DY_down);

    ChangeOneBin(h2_background_TT,     ibin,"background_TT" ,h_TT);
    ChangeOneBin(h2_background_TT_up,  ibin,"background_TT_alphaUp" ,h_TT_up);
    ChangeOneBin(h2_background_TT_down,ibin,"background_TT_alphaDown" ,h_TT_down);

    ChangeOneBin(h2_background_ZZ,     ibin,"background_ZZ" ,h_ZZ);
    ChangeOneBin(h2_background_ZZ_up,  ibin,"background_ZZ_alphaUp" ,h_ZZ_up);
    ChangeOneBin(h2_background_ZZ_down,ibin,"background_ZZ_alphaDown" ,h_ZZ_down);

    ChangeOneBin(h2_background_WZ,     ibin,"background_WZ" ,h_WZ);
    ChangeOneBin(h2_background_WZ_up,  ibin,"background_WZ_alphaUp" ,h_WZ_up);
    ChangeOneBin(h2_background_WZ_down,ibin,"background_WZ_alphaDown" ,h_WZ_down);


  } 
    AllBin(h2_data,          99,"data_obs",h_DATA);

    AllBin(h2_sig,           99,"signal",h_SIG);
    AllBin(h2_sig_up,           99,"signal_sigmaUp",h_SIG_up);
    AllBin(h2_sig_down,           99,"signal_sigmaDown",h_SIG_down);

    AllBin(h2_background_DY, 99,"background_DY" ,h_DY);
    AllBin(h2_background_DY_up, 99,"background_DY_alphaUp" ,h_DY_up);
    AllBin(h2_background_DY_down, 99,"background_DY_alphaDown" ,h_DY_down);

    AllBin(h2_background_TT, 99,"background_TT" ,h_TT);
    AllBin(h2_background_TT_up, 99,"background_TT_alphaUp" ,h_TT_up);
    AllBin(h2_background_TT_down, 99,"background_TT_alphaDown" ,h_TT_down);

    AllBin(h2_background_ZZ, 99,"background_ZZ" ,h_ZZ);
    AllBin(h2_background_ZZ_up, 99,"background_ZZ_alphaUp" ,h_ZZ_up);
    AllBin(h2_background_ZZ_down, 99,"background_ZZ_alphaDown" ,h_ZZ_down);

    AllBin(h2_background_WZ, 99,"background_WZ" ,h_WZ);
    AllBin(h2_background_WZ_up, 99,"background_WZ_alphaUp" ,h_WZ_up);
    AllBin(h2_background_WZ_down, 99,"background_WZ_alphaDown" ,h_WZ_down);


}












