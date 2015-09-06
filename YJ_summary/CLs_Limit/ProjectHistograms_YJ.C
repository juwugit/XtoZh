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
//  TString binnumber = Form("_%d",ibin);
//  TString namecentral= name+binnumber;
//  TString nameup = name+binnumber+"_Up";
//  TString namedown = name+binnumber+"_Down";
  
  
 // h[ibin] = (TH1F*)h_in->ProjectionX(Form("%s_%d",name.data(),ibin),ibin,ibin);
 //   if(strcmp(name.data(),"data_obs_temp")==0)
//    {
//     cout<<"data"<<name.data()<<endl;
//       h[ibin] = (TH1F*)h_in->ProjectionX("data_obs",ibin,ibin);
//    }
//    else
//    {
       h[ibin] = (TH1F*)h_in->ProjectionX(Form("%s_%d",name.data(),ibin),ibin,ibin);
  //   cout<<"other"<<name.data()<<endl;
//    } 
    
    TFile *f2 = new TFile(Form("output_0819_%d.root",ibin) , "UPDATE");
    h[ibin]->Write();
    f2->Close();
//  h[ibin]->SetBinContent(ibin,oldbincontent);
//  h->Write();
 
 // h_up[ibin] = (TH1F*)h_in->Clone(nameup);
//  h_up[ibin]->SetBinContent(ibin,newbincontent_up);
//  h_up->Write();

 /// h_down[ibin] = (TH1F*)h_in->Clone(namedown);
//  if(newbincontent_down<0) newbincontent_down = 0.;
//  h_down[ibin]->SetBinContent(ibin,newbincontent_down);
//  h_down->Write();

  
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

//  TFile* f = new TFile("/afs/cern.ch/work/y/yunju/private/CLs_setting/CMSSW_7_1_5/src/HZ_Samples/XMassVsCA8jetCSV_TH2_M1000_Mu.root" , "read");
//  TFile* f = new TFile("/afs/cern.ch/work/y/yunju/private/CLs_setting/CMSSW_7_1_5/src/HZ_Samples/XMassVsSubjetCSV_TH2_M1000_Mu.root" , "read");
  TFile* fresult = new TFile("../Bkg_estimation/Total_data_El_Cen.root" , "read");
  
  TFile* fsig = new TFile(inputsigFile.data(),"read");


//TFile* f = new TFile("/afs/cern.ch/work/y/yunju/private/CLs_setting/CMSSW_7_1_5/src/HZ_Samples/XMassVsCA8jetCSV_TH2_M1000_Mu.root" , "read");
  
  string DATA_name="h_sigXMsCSV";
  
  TH2F *h2_data=(TH2F*)fresult->Get(DATA_name.data());
 // TH2F *h2_data_clone=(TH2F*)h2_data->Clone("data_obs_temp");
 // cout<<"For clone"<<endl;
//  h2_data->Delete(); 
  string SIG_name="h_sigXMsCSV";
  TH2F *h2_sig=(TH2F*)fsig->Get(SIG_name.data());
//  TH1F *h_sig_x =(TH1F*)h2_sig->ProjectionX();

  string DY_name="h_n_XMsCSV_DYSbCorred";
  TH2F *h2_background_DY=(TH2F*)fresult->Get(DY_name.data());
//  TH1F *h_background_DY_x =(TH1F*)h2_background_DY->ProjectionX();



  string TT_name="h_n_XMsCSV_FINALTTTo2L2Nu2B";
  TH2F *h2_background_TT=(TH2F*)fresult->Get(TT_name.data());
//  TH1F *h_background_TT_x =(TH1F*)h2_background_TT->ProjectionX();
  
  string ZZ_name="h_n_XMsCSV_FINALDiBZZ";
  TH2F *h2_background_ZZ=(TH2F*)fresult->Get(ZZ_name.data());
//  TH1F *h_background_ZZ_x =(TH1F*)h2_background_ZZ->ProjectionX();
  string WZ_name="h_n_XMsCSV_FINALDiBWZ";
  TH2F *h2_background_WZ=(TH2F*)fresult->Get(WZ_name.data());

  
  int NbinX=0;
  NbinX=h2_background_DY->GetNbinsY();
  
  
  TH1F *h_DATA[50],*h_DY[50],*h_SIG[50],*h_TT[50],*h_ZZ[50],*h_WZ[50]; 
//  TH1F *h_DY_up[50],*h_SIG_up[50],*h_TT_up[50],*h_ZZ_up[50]; 
//  TH1F *h_DY_down[50],*h_SIG_down[50],*h_TT_down[50],*h_ZZ_down[50];
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







/*
TFile* f2[50];
   
  for(int ibin=1;ibin<=NbinX;ibin++)
  {
    f2[ibin] = new TFile(Form("output_0603_%d.root",ibin) , "recreate");
    

    h_DATA[ibin]->Write();

    h_DY[ibin]->Write();
    //h_DY_down[ibin]->Write();
   // h_DY_up[ibin]->Write();
    h_SIG[ibin]->Write();
   // h_SIG_down[ibin]->Write();
   // h_SIG_up[ibin]->Write();
    h_TT[ibin]->Write();
  //  h_TT_down[ibin]->Write();
  //  h_TT_up[ibin]->Write();
    h_ZZ[ibin]->Write();
  //  h_ZZ_down[ibin]->Write();
  //  h_ZZ_up[ibin]->Write();
  
    f2[ibin]->Close();
  } 
*/


}












