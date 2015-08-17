//root -q -b -l recoNVtx.C++\(\"inputFile\"\,\"outputFile\"\)

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
#include "/home/juwu/XtoZh/macro/untuplizer.h"
#include "/home/juwu/XtoZh/macro/passElectronID.h"
#include "/home/juwu/XtoZh/macro/passMuonID.h"
#include <standalone_LumiReWeighting.cc>


using namespace std;
void recoNVtx(std::string inputFile, std::string outputFile){


  // check if the file is data or not
  bool isData=false;
  if(inputFile.find("data")!= std::string::npos)
    isData=true;


  // check lepton channel
  bool isMuon=false;
  if(outputFile.find("Mu")!= std::string::npos)
    isMuon=true;

  bool isEle=false;
  if(outputFile.find("El")!= std::string::npos)
    isEle=true;



  // get TTree from file ...
  TreeReader data(inputFile.data());



  // declare histogram
  TH1F* h_nVtx         = new TH1F("h_nVtx","nVtx",50,0,50);
  TH1F* h_nVtx_central = new TH1F("h_nVtx_central","nVtx_central",50,0,50);
  TH1F* h_nVtx_down    = new TH1F("h_nVtx_down","nVtx_down",50,0,50);
  TH1F* h_nVtx_up      = new TH1F("h_nVtx_up","nVtx_up",50,0,50);
  
  h_nVtx->Sumw2();    
  h_nVtx_central->Sumw2();
  h_nVtx_down->Sumw2();
  h_nVtx_up->Sumw2();

  
  standalone_LumiReWeighting LumiWeights_central(2012,0);
  standalone_LumiReWeighting LumiWeights_down(2012,-1);
  standalone_LumiReWeighting LumiWeights_up(2012,1);

  Float_t  pu_nTrueInt       = -1;
  double   PU_weight_central = -1;
  double   PU_weight_up      = -1;
  double   PU_weight_down    = -1;
  
  Int_t    nLep;
  Float_t* lepPt;
  Float_t* lepEta;
  Float_t* lepPhi;
  Float_t* lepM; 


  //Event loop
  for(long jEntry=0; jEntry<data.GetEntriesFast() ;jEntry++){

    data.GetEntry(jEntry);
    
    Int_t nVtx = data.GetInt("info_nVtx");
    Int_t leadLep, secLep;

    // load lepton variables    
    if(isEle){
      
      nLep    = data.GetInt("nEle");
      lepPt   = data.GetPtrFloat("elePt");
      lepEta  = data.GetPtrFloat("eleEta");
      lepPhi  = data.GetPtrFloat("elePhi");
      lepM    = data.GetPtrFloat("eleM"); 
      
    }

    if(isMuon){
      
      nLep    = data.GetInt("nMu");
      lepPt   = data.GetPtrFloat("muPt");
      lepEta  = data.GetPtrFloat("muEta");
      lepPhi  = data.GetPtrFloat("muPhi");
      lepM    = data.GetPtrFloat("muM"); 
      
    }


    // pile up weights
    if(!isData){

      pu_nTrueInt       =  data.GetFloat("pu_nTrueInt");    
      PU_weight_central =  LumiWeights_central.weight(pu_nTrueInt);
      PU_weight_up      =  LumiWeights_up.weight(pu_nTrueInt);
      PU_weight_down    =  LumiWeights_down.weight(pu_nTrueInt);
      
    }


    // trigger
    std::string* trigName = data.GetPtrString("hlt_trigName");
    Int_t* trigResult = data.GetPtrInt("hlt_trigResult");
    const Int_t nsize = data.GetPtrStringSize();
    
    bool passTrigger=false;
    for(int it=0; it< nsize; it++)
      {
	std::string thisTrig= trigName[it];
	int results = trigResult[it];
     
	if(thisTrig.find("HLT_DoubleEle33")!= std::string::npos && results==1 && isEle)
	  {
	    passTrigger=true;
	    break;
	  }	
	
	if(thisTrig.find("HLT_Mu22_TkMu8")!= std::string::npos && results==1 && isMuon)
	  {
	    passTrigger=true;
	    break;
	  }	
      }
    
    if(isData && !passTrigger)continue;
    if(isEle && !passElectronID(data, &leadLep, &secLep)) continue;
    if(isMuon && !passMuonID(data, &leadLep, &secLep)) continue;
    if(nLep<=1) continue;

      

    // Reco mLL & mLL cuts
    TLorentzVector l1(0,0,0,0);
    TLorentzVector l2(0,0,0,0);
    TLorentzVector recoZ(0,0,0,0);
    
    l1.SetPtEtaPhiM(lepPt[leadLep],lepEta[leadLep],lepPhi[leadLep],lepM[leadLep]);
    l2.SetPtEtaPhiM(lepPt[secLep],lepEta[secLep],lepPhi[secLep],lepM[secLep]);
    recoZ=(l1+l2);

    Float_t ZPt=recoZ.Pt();
    
    if(ZPt<70) continue;



    
    
    // Fill nVtx
    h_nVtx->Fill(nVtx);
    h_nVtx_central->Fill(nVtx, PU_weight_central);
    h_nVtx_down->Fill(nVtx, PU_weight_down);
    h_nVtx_up->Fill(nVtx, PU_weight_up);


  } //entries 
  


  //save output
  TFile* outFile = new TFile(outputFile.data(),"recreate");

  h_nVtx->Write();
  h_nVtx_central->Write();
  h_nVtx_down->Write();
  h_nVtx_up->Write();


  outFile->Close();


}
