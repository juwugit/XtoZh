#include <iostream>
#include <fstream>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TH2F.h>
#include <cstdlib>

void ChangeOneBin(TH2F* h_in, int ibin, string name,TH1F* h[]){
  double oldbincontent = h_in->GetBinContent(ibin) ;
  double newbincontent_up   = oldbincontent + sqrt(oldbincontent) ;
  double newbincontent_down = oldbincontent - sqrt(oldbincontent) ;

  cout<<"Here:"<<ibin<<endl;  

  h[ibin] = (TH1F*)h_in->ProjectionX(Form("%s_%d",name.data(),ibin),ibin,ibin);

    
    TFile *f2 = new TFile(Form("output_0819_%d.root",ibin) , "UPDATE");
    h[ibin]->Write();
    f2->Close();
  
}


void AllBin(TH2F* h_in, int ibin, string name,TH1F* h[]){
  double oldbincontent = h_in->GetBinContent(ibin) ;
  double newbincontent_up   = oldbincontent + sqrt(oldbincontent) ;
  double newbincontent_down = oldbincontent - sqrt(oldbincontent) ;

  cout<<"Here:"<<ibin<<endl;  
    h[20] = (TH1F*)h_in->ProjectionX(Form("%s",name.data()),1,6);
   
    TFile *f2 = new TFile("Shape1d_0819.root", "UPDATE");
    h[20]->Write();
    f2->Close();
  
}



void ProjectHistograms_YJ(string inputsigFile)
{


  TFile* fresult = new TFile("../Bkg_estimation/Total_data_El_Cen.root" , "read");
  TFile* fsig = new TFile(inputsigFile.data(),"read");

  
  string DATA_name="h_sigMxSubjetCSV";
  TH2F *h2_data=(TH2F*)fresult->Get(DATA_name.data());

  string SIG_name="h_sigMxSubjetCSV";
  TH2F *h2_sig=(TH2F*)fsig->Get(SIG_name.data());

  string DY_name="h_n_MxSubjetCSV_FINAL_DYJets";
  TH2F *h2_background_DY=(TH2F*)fresult->Get(DY_name.data());

  string TT_name="h_n_MxSubjetCSV_FINAL_TTTo2L2Nu2B";
  TH2F *h2_background_TT=(TH2F*)fresult->Get(TT_name.data());
  
  string ZZ_name="h_n_MxSubjetCSV_FINAL_DiBZZ";
  TH2F *h2_background_ZZ=(TH2F*)fresult->Get(ZZ_name.data());

  string WZ_name="h_n_MxSubjetCSV_FINAL_DiBWZ";
  TH2F *h2_background_WZ=(TH2F*)fresult->Get(WZ_name.data());


  
  int NbinX=0;
  NbinX=h2_background_DY->GetNbinsY();
  
  
  TH1F *h_DATA[50],*h_DY[50],*h_SIG[50],*h_TT[50],*h_ZZ[50],*h_WZ[50]; 


  TString neam="test";
 
  for(int ibin=1;ibin<=NbinX;ibin++)
  {
    
    ChangeOneBin(h2_data,          ibin,"data_obs",h_DATA);
    ChangeOneBin(h2_sig,           ibin,"signal",h_SIG);
    ChangeOneBin(h2_background_DY, ibin,"background_DY" ,h_DY);
    ChangeOneBin(h2_background_TT, ibin,"background_TT" ,h_TT);
    ChangeOneBin(h2_background_ZZ, ibin,"background_ZZ" ,h_ZZ);
    ChangeOneBin(h2_background_WZ, ibin,"background_WZ" ,h_WZ);

  } 
    AllBin(h2_data,          99,"data_obs",h_DATA);
    AllBin(h2_sig,           99,"signal",h_SIG);
    AllBin(h2_background_DY, 99,"background_DY" ,h_DY);
    AllBin(h2_background_TT, 99,"background_TT" ,h_TT);
    AllBin(h2_background_ZZ, 99,"background_ZZ" ,h_ZZ);
    AllBin(h2_background_WZ, 99,"background_WZ" ,h_WZ);


}
