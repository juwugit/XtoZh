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
  TH1F  *h1_data=(TH1F*)f->Get(Form("data_obs_%d",n));
  h1_data->SetName("data_obs");
  h1_data->Write(); 
  TH1F  *h2=(TH1F*)f->Get(Form("signal_%d",n));
  h2->SetName("signal");
  h2->Write(); 
  


  f->Close();
  }








}
