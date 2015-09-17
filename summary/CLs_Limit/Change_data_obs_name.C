#include <iostream>
#include <fstream>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TH2F.h>
#include <cstdlib>




void Change_data_obs_name()
{
  for(int n=1;n<6;n++)
  {
  TFile *f = new TFile(Form("output_0819_%d.root",n),"UPDATE");

  TH1F  *h_data=(TH1F*)f->Get(Form("data_obs_%d",n));
  h_data->SetName("data_obs");
  h_data->Write(); 

  TH1F  *h_sig=(TH1F*)f->Get(Form("signal_%d",n));
  h_sig->SetName("signal");
  h_sig->Write(); 

  TH1F  *h_sig_up=(TH1F*)f->Get(Form("signal_sigmaUp_%d",n));
  h_sig_up->SetName("signal_sigmaUp");
  h_sig_up->Write(); 

  TH1F  *h_sig_down=(TH1F*)f->Get(Form("signal_sigmaDown_%d",n));
  h_sig_down->SetName("signal_sigmaDown");
  h_sig_down->Write(); 
  

  // DYJets
  TH1F  *h_dy_up=(TH1F*)f->Get(Form("background_DY_alphaUp_%d",n));
  h_dy_up->SetName(Form("background_DY_%d_alphaUp",n));
  h_dy_up->Write(); 

  TH1F  *h_dy_down=(TH1F*)f->Get(Form("background_DY_alphaDown_%d",n));
  h_dy_down->SetName(Form("background_DY_%d_alphaDown",n));
  h_dy_down->Write(); 


  // TTbar
  TH1F  *h_tt_up=(TH1F*)f->Get(Form("background_TT_alphaUp_%d",n));
  h_tt_up->SetName(Form("background_TT_%d_alphaUp",n));
  h_tt_up->Write(); 

  TH1F  *h_tt_down=(TH1F*)f->Get(Form("background_TT_alphaDown_%d",n));
  h_tt_down->SetName(Form("background_TT_%d_alphaDown",n));
  h_tt_down->Write(); 

  
  // ZZ
  TH1F  *h_zz_up=(TH1F*)f->Get(Form("background_ZZ_alphaUp_%d",n));
  h_zz_up->SetName(Form("background_ZZ_%d_alphaUp",n));
  h_zz_up->Write(); 

  TH1F  *h_zz_down=(TH1F*)f->Get(Form("background_ZZ_alphaDown_%d",n));
  h_zz_down->SetName(Form("background_ZZ_%d_alphaDown",n));
  h_zz_down->Write(); 


  // WZ
  TH1F  *h_wz_up=(TH1F*)f->Get(Form("background_WZ_alphaUp_%d",n));
  h_wz_up->SetName(Form("background_WZ_%d_alphaUp",n));
  h_wz_up->Write(); 

  TH1F  *h_wz_down=(TH1F*)f->Get(Form("background_WZ_alphaDown_%d",n));
  h_wz_down->SetName(Form("background_WZ_%d_alphaDown",n));
  h_wz_down->Write(); 


  f->Close();
  }


}
