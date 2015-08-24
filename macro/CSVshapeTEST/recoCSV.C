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
#include "JetSelections.h"
#include "/home/juwu/XtoZh/macro/standalone_LumiReWeighting.cc"


using namespace std;
void recoCSV(float masspoint, std::string inputFile, std::string outputFile){


  // check if the file is data or not
  bool isData=false;
  if(inputFile.find("data")!= std::string::npos)
    isData=true;



  // get TTree from file ...
  TreeReader data(inputFile.data());



  // declare histogram
  TH1F* h_CA8jetCSV = new TH1F("h_CA8jetCSV","CA8jetCSV",20,0,1);
  TH1F* h_SubjetCSV = new TH1F("h_SubjetCSV","SubjetCSV",20,0,1);

  
  h_CA8jetCSV->Sumw2();
  h_SubjetCSV->Sumw2();



  // PU reweight
  standalone_LumiReWeighting LumiWeights_central(2012,0);
  standalone_LumiReWeighting LumiWeights_down(2012,-1);
  standalone_LumiReWeighting LumiWeights_up(2012,1);

  Float_t  pu_nTrueInt       = 1;
  double   PU_weight_central = 1;



  //Event loop
  for(long jEntry=0; jEntry<data.GetEntriesFast() ;jEntry++){

    data.GetEntry(jEntry);

    Int_t    CA8nJet     = data.GetInt("CA8nJet");
    Float_t* CA8jetPt    = data.GetPtrFloat("CA8jetPt");
    Float_t* CA8jetEta   = data.GetPtrFloat("CA8jetEta");
    Float_t* CA8jetPhi   = data.GetPtrFloat("CA8jetPhi");
    Float_t* CA8jetEn    = data.GetPtrFloat("CA8jetEn");
    Float_t* CA8jetCSV   = data.GetPtrFloat("CA8jetCSV");

    Int_t*   nSubjet = data.GetPtrInt("CA8nSubPrunedJet");
    vector<Float_t>* SubjetCSV = data.GetPtrVectorFloat("CA8subjetPrunedCSV");
    vector<Float_t>* SubjetPt  = data.GetPtrVectorFloat("CA8subjetPrunedPt");
    vector<Float_t>* SubjetEta = data.GetPtrVectorFloat("CA8subjetPrunedEta");
    vector<Float_t>* SubjetPhi = data.GetPtrVectorFloat("CA8subjetPrunedPhi");
    vector<Float_t>* SubjetEn  = data.GetPtrVectorFloat("CA8subjetPrunedEn");

    Int_t nEle      = data.GetInt("nEle");  
    Float_t* elePt  = data.GetPtrFloat("elePt");  
    Float_t* eleEta = data.GetPtrFloat("eleEta");
    Float_t* elePhi = data.GetPtrFloat("elePhi");
    Float_t* eleM   = data.GetPtrFloat("eleM");

    Int_t nMu       = data.GetInt("nMu");  
    Float_t*  muPt  = data.GetPtrFloat("muPt");  
    Float_t*  muEta = data.GetPtrFloat("muEta");
    Float_t*  muPhi = data.GetPtrFloat("muPhi");
    Float_t*  muM   = data.GetPtrFloat("muM");


    Int_t leadEle, secEle;
    passElectronID(data, &leadEle, &secEle);
    Int_t leadMu, secMu;
    passMuonID(data, &leadMu, &secMu);



    // determine which channel
    bool isEle  = false;
    bool isMuon = false;
    if(nEle>0 && nMu==0) isEle  = true;
    if(nEle==0 && nMu>0) isMuon = true;
    if(nEle>0 && nMu>0 && elePt[leadEle]>muPt[leadMu]) isEle  = true;
    if(nEle>0 && nMu>0 && elePt[leadEle]<muPt[leadMu]) isMuon = true;


    // pile up weights 
    if(!isData){

      pu_nTrueInt       =  data.GetFloat("pu_nTrueInt");
      PU_weight_central =  LumiWeights_central.weight(pu_nTrueInt);

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
   

    // passLeptonID
    if(isData && !passTrigger)continue;
    if(isEle && !passElectronID(data, &leadEle, &secEle)) continue;
    if(isMuon && !passMuonID(data, &leadMu, &secMu)) continue;
    if( (isEle && nEle<=1) || (isMuon && nMu<=1) ) continue;


      
    // Reco mLL & mLL cuts
    TLorentzVector l1(0,0,0,0);
    TLorentzVector l2(0,0,0,0);
    TLorentzVector recoZ(0,0,0,0);
    
    if(isEle){

      l1.SetPtEtaPhiM(elePt[leadEle],eleEta[leadEle],elePhi[leadEle],eleM[leadEle]);
      l2.SetPtEtaPhiM(elePt[secEle],eleEta[secEle],elePhi[secEle],eleM[secEle]);
    }

    if(isMuon){

      l1.SetPtEtaPhiM(muPt[leadMu],muEta[leadMu],muPhi[leadMu],muM[leadMu]);
      l2.SetPtEtaPhiM(muPt[secMu],muEta[secMu],muPhi[secMu],muM[secMu]);
    }

    recoZ=(l1+l2);

    Float_t ZMass=recoZ.M();
    Float_t ZPt=recoZ.Pt();
    
    if(ZMass<70 || ZMass>110) continue;
    if(ZPt<80) continue;



    // reco XMass
    Int_t leadjet;
    if(!PassJet(3, data, leadjet)) continue;

    TLorentzVector recoH(0,0,0,0);
    TLorentzVector recoX(0,0,0,0);
    Float_t XMass=-999;

    if(CA8nJet>0 && leadjet>=0){
      
      recoH.SetPtEtaPhiE(CA8jetPt[leadjet],CA8jetEta[leadjet],CA8jetPhi[leadjet],CA8jetEn[leadjet]);
      recoX = recoZ+recoH;
      XMass = recoX.M();

    }      

    float upper_limit = masspoint*1.15;
    float lower_limit = masspoint*0.85;

    if(XMass>upper_limit || XMass<lower_limit || XMass==-999) continue;



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


      if(dRjj>0.3){
	
	if(SubjetCSV[i][0]>0) h_SubjetCSV->Fill(SubjetCSV[i][0], PU_weight_central);
	if(SubjetCSV[i][1]>0) h_SubjetCSV->Fill(SubjetCSV[i][1], PU_weight_central);
	
      }
      
      if(dRjj<0.3 && CA8jetCSV[i]>0) h_CA8jetCSV->Fill(CA8jetCSV[i], PU_weight_central);
      
      
    } // jet loop                                                                    


  } //entries 
  


  //save output
  TFile* outFile = new TFile(outputFile.data(),"recreate");


  h_CA8jetCSV->Write();
  h_SubjetCSV->Write();

  outFile->Close();


}
