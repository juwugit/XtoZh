//root -q -b -l recoXmass_El.C++\(\"inputFile\"\,\"outputFile\"\)

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
#include "/home/juwu/XtoZh/macro/JetSelections.h"


using namespace std;
void recoXmass_Mu(std::string inputFile, std::string outputFile){


  // check if the file is data or not
  bool isData=false;
  if(inputFile.find("data")!= std::string::npos)
    isData=true;


  // get TTree from file ...
  TreeReader data(inputFile.data());



  // declare histogram
  TH1F* h_sbCA8jetCSV = new TH1F("h_sbCA8jetCSV","sideband region CA8jet CSV",20,0,1);
  TH1F* h_sigCA8jetCSV = new TH1F("h_sigCA8jetCSV","signal region CA8jet CSV",20,0,1);
  TH1F* h_sbSubjetCSV = new TH1F("h_sbSubjetCSV","sideband region subjet CSV",20,0,1);
  TH1F* h_sigSubjetCSV = new TH1F("h_sigSubjetCSV","signal region subjet CSV",20,0,1);

  
  h_sbCA8jetCSV->Sumw2();
  h_sigCA8jetCSV->Sumw2();
  h_sbSubjetCSV->Sumw2();
  h_sigSubjetCSV->Sumw2();



  //Event loop
  for(long jEntry=0; jEntry<data.GetEntriesFast() ;jEntry++){

    data.GetEntry(jEntry);

    Int_t    CA8nJet     = data.GetInt("CA8nJet");
    Float_t* CA8jetPt    = data.GetPtrFloat("CA8jetPt");
    Float_t* CA8jetEta   = data.GetPtrFloat("CA8jetEta");
    Float_t* CA8jetPhi   = data.GetPtrFloat("CA8jetPhi");
    Float_t* CA8jetEn    = data.GetPtrFloat("CA8jetEn");
    Float_t* CA8jetPrunedM = data.GetPtrFloat("CA8jetPrunedMass");
    Float_t* CA8jetCSV   = data.GetPtrFloat("CA8jetCSV");

    Int_t*   nSubjet = data.GetPtrInt("CA8nSubPrunedJet");
    vector<Float_t>* SubjetCSV = data.GetPtrVectorFloat("CA8subjetPrunedCSV");
    vector<Float_t>* SubjetPt  = data.GetPtrVectorFloat("CA8subjetPrunedPt");
    vector<Float_t>* SubjetEta = data.GetPtrVectorFloat("CA8subjetPrunedEta");
    vector<Float_t>* SubjetPhi = data.GetPtrVectorFloat("CA8subjetPrunedPhi");
    vector<Float_t>* SubjetEn  = data.GetPtrVectorFloat("CA8subjetPrunedEn");

    Int_t    nMu        = data.GetInt("nMu");
    Float_t* muPt       = data.GetPtrFloat("muPt");
    Float_t* muEta      = data.GetPtrFloat("muEta");
    Float_t* muPhi      = data.GetPtrFloat("muPhi");
    Float_t* muM        = data.GetPtrFloat("muM");   

    Int_t leadjet;    
    Int_t leadMu, secMu;


    // trigger
    std::string* trigName = data.GetPtrString("hlt_trigName");
    Int_t* trigResult = data.GetPtrInt("hlt_trigResult");
    const Int_t nsize = data.GetPtrStringSize();
    
    bool passTrigger=false;
    for(int it=0; it< nsize; it++)
      {
	std::string thisTrig= trigName[it];
	int results = trigResult[it];
	/*
	if(thisTrig.find("HLT_DoubleEle33")!= std::string::npos && results==1)
	  {
	    passTrigger=true;
	    break;
	  }
	*/
	
	if(thisTrig.find("HLT_Mu22_TkMu8")!= std::string::npos && results==1)
	  {
	    passTrigger=true;
	    break;
	  }
	
      }
   
    if(isData && !passTrigger)continue;
    if(!passMuonID(data, &leadMu, &secMu)) continue;
    if(nMu<=1) continue;

      
    // Reco mLL & mLL cuts
    TLorentzVector l1(0,0,0,0);
    TLorentzVector l2(0,0,0,0);
    TLorentzVector recoZ(0,0,0,0);
    
    l1.SetPtEtaPhiM(muPt[leadMu],muEta[leadMu],muPhi[leadMu],muM[leadMu]);
    l2.SetPtEtaPhiM(muPt[secMu],muEta[secMu],muPhi[secMu],muM[secMu]);
    recoZ=(l1+l2);

    Float_t ZMass=recoZ.M();
    Float_t ZPt=recoZ.Pt();
    
    if(ZMass<70 || ZMass>110) continue;
    if(ZPt<80) continue;



    // reco XMass
    if(!PassJet(3, data, leadjet)) continue;

    TLorentzVector recoH(0,0,0,0);
    TLorentzVector recoX(0,0,0,0);
    Float_t XMass;
    Float_t prunedmass=CA8jetPrunedM[leadjet];
    
    if(CA8nJet>0 && leadjet>=0){
      
      recoH.SetPtEtaPhiE(CA8jetPt[leadjet],CA8jetEta[leadjet],CA8jetPhi[leadjet],CA8jetEn[leadjet]);
      recoX = recoZ+recoH;
      
      XMass = recoX.M();

    }      



    // reco CSV
    TLorentzVector subjet1(0,0,0,0);
    TLorentzVector subjet2(0,0,0,0);
    Float_t dRjj=-999;


    for(int i=0; i<CA8nJet; i++){


      //check subjet deltaR
      if(nSubjet[i]>=2){

	subjet1.SetPtEtaPhiE(SubjetPt[i][0],SubjetEta[i][0],SubjetPhi[i][0],SubjetEn[i][0]);
	subjet2.SetPtEtaPhiE(SubjetPt[i][1],SubjetEta[i][1],SubjetPhi[i][1],SubjetEn[i][1]);
	dRjj=subjet1.DeltaR(subjet2);

      }


      // sideband region
      if(prunedmass>70 && prunedmass<110){

	if(dRjj>0.3){

	  if(SubjetCSV[i][0]>0) h_sbSubjetCSV->Fill(SubjetCSV[i][0]);
	  if(SubjetCSV[i][1]>0) h_sbSubjetCSV->Fill(SubjetCSV[i][1]);

	}

	if(dRjj<0.3 && CA8jetCSV[i]>0) h_sbCA8jetCSV->Fill(CA8jetCSV[i]);
		
      }

      // signal region                                           
      if(prunedmass>110 && prunedmass<140){

        if(dRjj>0.3){

	  if(SubjetCSV[i][0]>0) h_sigSubjetCSV->Fill(SubjetCSV[i][0]);
	  if(SubjetCSV[i][1]>0) h_sigSubjetCSV->Fill(SubjetCSV[i][1]);

	}

	if(dRjj<0.3 && CA8jetCSV[i]>0) h_sigCA8jetCSV->Fill(CA8jetCSV[i]);
	
      }
      
    } // jet loop                                                                    


  } //entries 
  


  //save output
  TFile* outFile = new TFile(outputFile.data(),"recreate");

  h_sbCA8jetCSV->Write();
  h_sigCA8jetCSV->Write();
  h_sbSubjetCSV->Write();
  h_sigSubjetCSV->Write();



  outFile->Close();


}
