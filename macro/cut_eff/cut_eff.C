//root -q -b -l cut_eff.C++\(masspoint\,\"inputFile\"\)

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <TPad.h>
#include <TH1D.h>
#include <TH1F.h>
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
#include <map>
#include "untuplizer.h"
#include "passElectronID.h"
#include "passMuonID.h"
#include "JetSelections_onlyID.h"



const Int_t cut_number=7;
const char* cut_name[cut_number] = {"lepton ID","Z P_{T} & mLL","jetID","Higgs P_{T}","Prunedjet Mass","X Mass","#tau_{21}"};




using namespace std;
void cut_eff(float masspoint, std::string inputFile){


  //get TTree from file ...
  TreeReader data(inputFile.data());


  //histogram anoucement
  TH1F* h_CutEff = new TH1F("h_CutEff","",cut_number,0,cut_number);
  h_CutEff->Sumw2();


  Int_t denom = data.GetEntriesFast();
  Int_t counter[cut_number];
  Float_t eff[cut_number];
  Float_t error[cut_number];



  // reset array
  for(Int_t i=0; i<cut_number; i++){

    counter[i]=0;
    eff[i]=0;
    
    cout<<"i:"<<i<<" counter:"<<counter[i]<<" eff:"<<eff[i]<<endl;


  }



  //Event loop
  for(long jEntry=0; jEntry<data.GetEntriesFast() ;jEntry++){

    data.GetEntry(jEntry);


    Int_t    CA8nJet     = data.GetInt("CA8nJet");
    Float_t* CA8jetPt    = data.GetPtrFloat("CA8jetPt");
    Float_t* CA8jetEta   = data.GetPtrFloat("CA8jetEta");
    Float_t* CA8jetPhi   = data.GetPtrFloat("CA8jetPhi");
    Float_t* CA8jetM     = data.GetPtrFloat("CA8jetMass");
    Float_t* CA8jetTau1  = data.GetPtrFloat("CA8jetTau1");
    Float_t* CA8jetTau2  = data.GetPtrFloat("CA8jetTau2");
    Float_t* CA8jetPrunedM  = data.GetPtrFloat("CA8jetPrunedMass");   

    
    Int_t    nEle        = data.GetInt("nEle");
    Float_t* elePt       = data.GetPtrFloat("elePt");
    Float_t* eleEta      = data.GetPtrFloat("eleEta");
    Float_t* elePhi      = data.GetPtrFloat("elePhi");
    Float_t* eleM        = data.GetPtrFloat("eleM");
   
    Int_t    nMu         = data.GetInt("nMu");
    Float_t* muPt        = data.GetPtrFloat("muPt");
    Float_t* muEta       = data.GetPtrFloat("muEta");
    Float_t* muPhi       = data.GetPtrFloat("muPhi");
    Float_t* muM         = data.GetPtrFloat("muM");
   

    Int_t leadjet;
    PassJet(data, leadjet);    
    Int_t leadEle, secEle;
    passElectronID(data, &leadEle, &secEle);
    Int_t leadMu, secMu;
    passMuonID(data, &leadMu, &secMu);


    

    // determine which channel
    bool ee=false;
    bool mm=false;
    if(nEle>0 && nMu==0) ee=true;
    if(nEle==0 && nMu>0) mm=true;
    if(nEle>0 && nMu>0 && elePt[leadEle]>muPt[leadMu]) ee=true;
    if(nEle>0 && nMu>0 && elePt[leadEle]<muPt[leadMu]) mm=true;
    

    if(ee==true && !passElectronID(data, &leadEle, &secEle)) continue;
    if(mm==true && !passMuonID(data, &leadMu, &secMu)) continue;



    counter[0]++; // counter for lep cuts

    
    // Reco Z
    TLorentzVector l1(0,0,0,0);
    TLorentzVector l2(0,0,0,0);
    TLorentzVector recoZ(0,0,0,0);

    if(ee==true && nEle>1){
      
      l1.SetPtEtaPhiM(elePt[leadEle],eleEta[leadEle],elePhi[leadEle],eleM[leadEle]);
      l2.SetPtEtaPhiM(elePt[secEle],eleEta[secEle],elePhi[secEle],eleM[secEle]);
      recoZ=(l1+l2);
      
    } // ee channel


    if(mm==true && nMu>1){
    
      l1.SetPtEtaPhiM(muPt[leadMu],muEta[leadMu],muPhi[leadMu],muM[leadMu]);
      l2.SetPtEtaPhiM(muPt[secMu],muEta[secMu],muPhi[secMu],muM[secMu]);
      recoZ=(l1+l2);

    } // mm channel

    Float_t ZPt=recoZ.Pt();
    Float_t ZMass=recoZ.M();
    if(ZPt<80) continue;
    if(ZMass<70 || ZMass>110) continue;


    
    counter[1]++;  // counter for ZPt and mLL cut



    // Pass Jet ID and Basic Kinematic Cut
    if(!PassJet(data, leadjet)) continue;
    counter[2]++;

    
    

    // reco XMass                                                                                  
    TLorentzVector recoH(0,0,0,0);
    TLorentzVector recoX(0,0,0,0);
    
    if(CA8nJet==0 && leadjet<0) continue;
      
      recoH.SetPtEtaPhiM(CA8jetPt[leadjet],CA8jetEta[leadjet],CA8jetPhi[leadjet],CA8jetM[leadjet]);
      recoX = recoZ+recoH;
      
      
      Float_t HPt=recoH.Pt();
      Float_t prunedmass=CA8jetPrunedM[leadjet];
      Float_t tau21=(CA8jetTau2[leadjet]/CA8jetTau1[leadjet]);

      float XMass=recoX.M();      
      float upper_limit=masspoint*1.15;  
      float lower_limit=masspoint*0.85;  
      
      
      if(HPt<80) continue;
      counter[3]++;

      if(prunedmass<40) continue;
      counter[4]++;

      if(XMass>upper_limit || XMass<lower_limit)continue;  
      counter[5]++;
      
      if(tau21>0.5) continue;
      counter[6]++;
  
        


  } //entries 

    

  
  // calculate eff
  for(Int_t i=0; i<cut_number; i++){
    
    if(denom==0 || counter[i]==0)continue;
    
    eff[i]=(float)counter[i]/(float)denom;
    error[i]=eff[i]*sqrt( (1/((float)counter[i])) + ( 1/((float)denom))  );

    
    cout<<"which cut:"<<i<<" | counter:"<<counter[i]<<" | eff:"<<eff[i]<<" | err:"<<error[i]<<endl;

    h_CutEff->SetBinContent(i+1,eff[i]);
    h_CutEff->SetBinError(i+1,error[i]);
    h_CutEff->GetXaxis()->SetBinLabel(i+1, cut_name[i]);


    denom=counter[i];


  }
  


  
  gStyle->SetOptStat(0);  
  TCanvas* c1 = new TCanvas("c1", "", 0, 0, 800, 600);

  h_CutEff->GetYaxis()->SetRangeUser(0,1.3);
  h_CutEff->GetYaxis()->SetTitle("efficiency");
  h_CutEff->SetMarkerStyle(8);
  h_CutEff->SetMarkerSize(1);
  h_CutEff->GetXaxis()->SetLabelSize(0.05);

  h_CutEff->Draw();


  TLine* l2 = new TLine(0.,1.,7.,1.);
  l2->SetLineColor(4);
  l2->SetLineStyle(3);
  l2->Draw("same");


  
  gSystem->ProcessEvents();
  TImage *img1 = TImage::Create();
  img1->FromPad(c1);
  img1->WriteImage("h_CutEff.png");
  delete c1;
  delete img1;
  






} // void
