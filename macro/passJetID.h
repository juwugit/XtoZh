/*
  v5: vector sorting version

  This macro does following selections:

  1. b-tagging CSVL cut on subjet or CA8jet (optional, insert mode==1)
  2. tau21<0.5 for leading jet (optional, insert mode==2)
  3. remove overlap between jet and leptons if deltaR<1.0
  jetPt>30 , fabs(Eta)<2.4
  PrunedJetMass>40 , PrunedJetPt>80
  jetID>0 
  4. return leading jet index
*/

#include <map>
#include <vector>
#include <iostream>
#include <TLorentzVector.h>
#include "untuplizer.h"
#include "corrJetVector.h"

struct gMap{
  Int_t index;
  Float_t pt;
};

struct l4Map{
  Int_t index;
  TLorentzVector l4;
};

Bool_t gPtGreater(gMap i, gMap j){ 
  return (i.pt > j.pt); 
}

Bool_t jetPtGreater(l4Map i, l4Map j){ 
  return (i.l4.Pt() > j.l4.Pt()); 
}

Bool_t passJetID(TreeReader &data,
		 corrJetV &obj,
		 Int_t &csvlMode,
		 Int_t &scaleMode,
		 Int_t *accepted,
		 TLorentzVector *goodJetVector){
  

  if( csvlMode < 0 || csvlMode > 2 ) return false;
  if( scaleMode < -1 || scaleMode > 1 ) return false;

  *accepted = -1;

  Int_t    nEle   = data.GetInt("nEle");
  Float_t* elePt  = data.GetPtrFloat("elePt");
  Float_t* eleEta = data.GetPtrFloat("eleEta");
  Float_t* elePhi = data.GetPtrFloat("elePhi");
  Float_t* eleM   = data.GetPtrFloat("eleM");
  Int_t*   eleID  = data.GetPtrInt("elePassID");

  Int_t    nMu   = data.GetInt("nMu");
  Float_t* muPt  = data.GetPtrFloat("muPt");
  Float_t* muEta = data.GetPtrFloat("muEta");
  Float_t* muPhi = data.GetPtrFloat("muPhi");
  Float_t* muM   = data.GetPtrFloat("muM");
  Int_t*   muID  = data.GetPtrInt("muPassID");

  Int_t    CA8nJet    = data.GetInt("CA8nJet");
  Float_t* CA8jetPt   = data.GetPtrFloat("CA8jetPt");
  Float_t* CA8jetEta  = data.GetPtrFloat("CA8jetEta");
  Float_t* CA8jetPhi  = data.GetPtrFloat("CA8jetPhi");
  Float_t* CA8jetEn   = data.GetPtrFloat("CA8jetEn");
  Int_t*   CA8jetID   = data.GetPtrInt("CA8jetPassID");
  Float_t* CA8jetTau1 = data.GetPtrFloat("CA8jetTau1");
  Float_t* CA8jetTau2 = data.GetPtrFloat("CA8jetTau2");
  Float_t* CA8jetPrunedM = data.GetPtrFloat("CA8jetPrunedMass");

  // b-tagging
  Int_t*   nSubjet   = data.GetPtrInt("CA8nSubPrunedJet");
  Float_t* CA8jetCSV = data.GetPtrFloat("CA8jetCSV");
  vector<Float_t>* SubjetCSV = data.GetPtrVectorFloat("CA8subjetPrunedCSV");
  vector<Float_t>* SubjetPt  = data.GetPtrVectorFloat("CA8subjetPrunedPt");
  vector<Float_t>* SubjetEta = data.GetPtrVectorFloat("CA8subjetPrunedEta");
  vector<Float_t>* SubjetPhi = data.GetPtrVectorFloat("CA8subjetPrunedPhi");
  vector<Float_t>* SubjetEn  = data.GetPtrVectorFloat("CA8subjetPrunedEn");

  // sorting electron
  vector<gMap> sortElePt;
  for(Int_t i = 0; i < nEle; i++){

    gMap temp;
    temp.index = i;
    temp.pt = elePt[i];
    sortElePt.push_back(temp);

  }
  
  std::sort(sortElePt.begin(), sortElePt.end(), gPtGreater);

  // sorting muon
  vector<gMap> sortMuPt;
  for(Int_t i = 0; i < nMu; i++){

    gMap temp;
    temp.index = i;
    temp.pt = muPt[i];
    sortMuPt.push_back(temp);

  }
  
  std::sort(sortMuPt.begin(), sortMuPt.end(), gPtGreater);

  // determine which channel     
  Bool_t El = false;
  Bool_t Mu = false;
  if(nEle > 0 && nMu == 0) El = true;
  if(nEle == 0 && nMu > 0) Mu = true;
  if(sortElePt.size()>0 && sortMuPt.size()>0 && elePt[sortElePt[0].index]>muPt[sortMuPt[0].index]) El = true;
  if(sortElePt.size()>0 && sortMuPt.size()>0 && elePt[sortElePt[0].index]<muPt[sortMuPt[0].index]) Mu = true;
  
  vector<l4Map> goodJets;
  
  TLorentzVector lep(0,0,0,0);
  Float_t dRjl = -999;
  Int_t nSortEle = sortElePt.size();
  Int_t nSortMu = sortMuPt.size();

  // loop jets
  for(Int_t jIndex = 0; jIndex < CA8nJet; jIndex++){
    
    TLorentzVector tmpJets(0,0,0,0);
    TLorentzVector allJets(0,0,0,0);
  
    tmpJets.SetPtEtaPhiE(CA8jetPt[jIndex],
			 CA8jetEta[jIndex],
			 CA8jetPhi[jIndex],
			 CA8jetEn[jIndex]);

    allJets = obj.scaleUnc(scaleMode, tmpJets.Pt(), tmpJets.Eta()) * tmpJets;

    Bool_t overlap = false;
    Bool_t ptCut = (CA8jetPt[jIndex]>30);
    Bool_t etaCut = (fabs(CA8jetEta[jIndex])<2.4);
    Bool_t IDcut = (CA8jetID[jIndex]>0);
    Bool_t prunedJetCut = (CA8jetPt[jIndex]>80)&&(CA8jetPrunedM[jIndex]>40);
    Bool_t Tau21Cut = ((CA8jetTau2[jIndex]/CA8jetTau1[jIndex])<0.5);

    if( !ptCut ) continue;
    if( !etaCut ) continue;
    if( !IDcut ) continue;
    if( !prunedJetCut ) continue;
    if( csvlMode==2 && !Tau21Cut ) continue;

    if( El ){
      for(Int_t i = 0; i < nSortEle; i++){
	Int_t eIndex = sortElePt[i].index;
	if(eleID[eIndex]>0){
	  lep.SetPtEtaPhiM(elePt[eIndex],eleEta[eIndex],elePhi[eIndex],eleM[eIndex]);
	  dRjl = allJets.DeltaR(lep);
	  if(dRjl<1.0 && dRjl!=-999){
	    overlap = true;
	    break;
	  }
	} // eleID
      } // loop ele
    } // El
    
    if( Mu ){
      for(Int_t i = 0; i < nSortMu; i++){
	Int_t muIndex = sortMuPt[i].index;
        if(muID[muIndex]>0){
          lep.SetPtEtaPhiM(muPt[muIndex],muEta[muIndex],muPhi[muIndex],muM[muIndex]);
          dRjl = allJets.DeltaR(lep);
          if(dRjl<1.0 && dRjl!=-999){
	    overlap = true;
	    break;
	  }
	} // muID                                                                       
      } // loop muon                                                                             
    } // Mu                               

    // remove overlap
    if( overlap ) continue;
 
    // b-tagging CSVL cut
    TLorentzVector subjet1(0,0,0,0);
    TLorentzVector subjet2(0,0,0,0);
    Float_t dRjj = -999;
    Bool_t subjetbtag = false;
    Bool_t fatjetCSV = (CA8jetCSV[jIndex]>0.244);

    if( nSubjet[jIndex] == 2 ){

      subjet1.SetPtEtaPhiE(SubjetPt[jIndex][0],SubjetEta[jIndex][0],SubjetPhi[jIndex][0],SubjetEn[jIndex][0]);
      subjet2.SetPtEtaPhiE(SubjetPt[jIndex][1],SubjetEta[jIndex][1],SubjetPhi[jIndex][1],SubjetEn[jIndex][1]);
      dRjj = subjet1.DeltaR(subjet2);

      if(SubjetCSV[jIndex][0]>0.244 && SubjetCSV[jIndex][1]>0.244) subjetbtag = true;

    }

    if(csvlMode==1 && dRjj<0.3 && !fatjetCSV) continue;
    if(csvlMode==1 && dRjj>0.3 && !subjetbtag) continue;

    l4Map tempMap;
    tempMap.index = jIndex;
    tempMap.l4 = allJets;
    goodJets.push_back(tempMap);

  } // loop jets

  std::sort(goodJets.begin(),goodJets.end(),jetPtGreater);

  if( goodJets.size() > 0 ){
    
    *accepted = goodJets[0].index;
    *goodJetVector = goodJets[0].l4;

    return true;
    
  }

  else return false;
 
} // function brace
