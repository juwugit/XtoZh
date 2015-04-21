/*

v6: vector sorting version

This macro does following selections:

1. b-tagging CSVL cut on subjet or CA8jet (optional, insert mode==1)

2. tau21<0.5 for leading jet (optional, insert mode==2)

3. insert other number will only cut on basic selection

4. remove overlap between jet and leptons if deltaR<1.0
   jetPt>30 , fabs(Eta)<2.4
   PrunedJetPt>200
   jetID>0 

5. return leading jet index

*/



struct myMap
{
  Int_t index;
  Float_t pt;
};

Bool_t PtGreater (myMap i,myMap j) { return (i.pt>j.pt); }
Bool_t PassJet(int mode, TreeReader &data, Int_t &accepted){

  accepted=-1;

  Int_t    CA8nJet     = data.GetInt("CA8nJet");
  Float_t* CA8jetPt    = data.GetPtrFloat("CA8jetPt");
  Float_t* CA8jetEta   = data.GetPtrFloat("CA8jetEta");
  Float_t* CA8jetPhi   = data.GetPtrFloat("CA8jetPhi");
  Float_t* CA8jetEn    = data.GetPtrFloat("CA8jetEn");
  Int_t*   CA8jetID    = data.GetPtrInt("CA8jetPassID");
  Float_t* CA8jetTau1  = data.GetPtrFloat("CA8jetTau1");
  Float_t* CA8jetTau2  = data.GetPtrFloat("CA8jetTau2");

  // b-tagging variables
  Float_t* CA8jetCSV   = data.GetPtrFloat("CA8jetCSV");
  Int_t*   nSubjet = data.GetPtrInt("CA8nSubPrunedJet");
  vector<Float_t>* SubjetCSV = data.GetPtrVectorFloat("CA8subjetPrunedCSV");
  vector<Float_t>* SubjetPt  = data.GetPtrVectorFloat("CA8subjetPrunedPt");
  vector<Float_t>* SubjetEta = data.GetPtrVectorFloat("CA8subjetPrunedEta");
  vector<Float_t>* SubjetPhi = data.GetPtrVectorFloat("CA8subjetPrunedPhi");
  vector<Float_t>* SubjetEn  = data.GetPtrVectorFloat("CA8subjetPrunedEn");

  Int_t    nEle        = data.GetInt("nEle");
  Float_t* elePt       = data.GetPtrFloat("elePt");
  Float_t* eleEta      = data.GetPtrFloat("eleEta");
  Float_t* elePhi      = data.GetPtrFloat("elePhi");
  Float_t* eleM        = data.GetPtrFloat("eleM");
  Int_t*   eleID       = data.GetPtrInt("elePassID");

  Int_t    nMu         = data.GetInt("nMu");
  Float_t* muPt        = data.GetPtrFloat("muPt");
  Float_t* muEta       = data.GetPtrFloat("muEta");
  Float_t* muPhi       = data.GetPtrFloat("muPhi");
  Float_t* muM         = data.GetPtrFloat("muM");
  Int_t*   muID        = data.GetPtrInt("muPassID");


  // Sorting Electron
  vector<myMap> sortElePt;
  for(Int_t i=0; i<nEle; i++){

    myMap temp;
    temp.index = i;
    temp.pt = elePt[i];
    sortElePt.push_back(temp);

  }
  std::sort(sortElePt.begin(),sortElePt.end(),PtGreater);

  
  // Sorting Muon
  vector<myMap> sortMuPt;
  for(Int_t i=0; i<nMu; i++){

    myMap temp;
    temp.index = i;
    temp.pt = muPt[i];
    sortMuPt.push_back(temp);

  }
  std::sort(sortMuPt.begin(),sortMuPt.end(),PtGreater);

   
  // determine which channel                                                                                        
  bool El=false;
  bool Mu=false;
  if(nEle>0 && nMu==0) El=true;
  if(nEle==0 && nMu>0) Mu=true;
  if(sortElePt.size()>0 && sortMuPt.size()>0 && elePt[sortElePt[0].index]>muPt[sortMuPt[0].index]) El=true;
  if(sortElePt.size()>0 && sortMuPt.size()>0 && elePt[sortElePt[0].index]<muPt[sortMuPt[0].index]) Mu=true;
  

  // Sorting Jet
  vector<myMap> sortJetPt;
  for(Int_t i=0; i<CA8nJet; i++){

    myMap temp;
    temp.index = i;
    temp.pt = CA8jetPt[i];
    sortJetPt.push_back(temp);

  }
  std::sort(sortJetPt.begin(),sortJetPt.end(),PtGreater);


  // remove overlap
  vector<Int_t> goodJetIndex;
  goodJetIndex.clear();

  TLorentzVector lep(0,0,0,0);
  TLorentzVector alljets(0,0,0,0);
  Float_t dRjl=-999;

  Int_t nSortJet=sortJetPt.size();
  Int_t nSortEle=sortElePt.size();
  Int_t nSortMu=sortMuPt.size();

  
  for(Int_t k=0; k<nSortJet; k++){

    Int_t jIndex=sortJetPt[k].index;

    bool overlap=false;
    bool basicCuts=(CA8jetPt[jIndex]>30)&&(fabs(CA8jetEta[jIndex])<2.4);
    bool IDcut=(CA8jetID[jIndex]>0);
    bool prunedJetCuts=(CA8jetPt[jIndex]>200);
    bool Tau21Cut=((CA8jetTau2[jIndex]/CA8jetTau1[jIndex])<0.5);


    alljets.SetPtEtaPhiE(CA8jetPt[jIndex],
                         CA8jetEta[jIndex],
			 CA8jetPhi[jIndex],
			 CA8jetEn[jIndex]);

    if(!basicCuts) continue;
    if(!IDcut) continue;
    if(!prunedJetCuts) continue;
    if(mode==2 && !Tau21Cut) continue;


    if(El==true){

      for(Int_t i=0; i<nSortEle; i++){

	Int_t eIndex=sortElePt[i].index;

	if(eleID[eIndex]>0){
	 
	  lep.SetPtEtaPhiM(elePt[eIndex],eleEta[eIndex],elePhi[eIndex],eleM[eIndex]);
	  dRjl=alljets.DeltaR(lep);
	  
	  if(dRjl<1.0 && dRjl!=-999){
	    overlap=true;
	    break;
	  }

	} // eleID
      } // loop ele
    } // El


    if(Mu==true){

      for(Int_t i=0; i<nSortMu; i++){

	Int_t muIndex=sortMuPt[i].index;

        if(muID[muIndex]>0){

          lep.SetPtEtaPhiM(muPt[muIndex],muEta[muIndex],muPhi[muIndex],muM[muIndex]);
          dRjl=alljets.DeltaR(lep);

          if(dRjl<1.0 && dRjl!=-999){
	    overlap=true;
	    break;
	  }

	} // muID                                                                       
      } // loop muon                                                                             
    } // Mu                               

    if(overlap) continue;


    
    // b-tagging CSVL cut
    TLorentzVector subjet1(0,0,0,0);
    TLorentzVector subjet2(0,0,0,0);
    Float_t dRjj=-999;
    bool subjetbtag=false;
    bool fatjetCSV=(CA8jetCSV[jIndex]>0.244);

    if(nSubjet[jIndex]==2){

      subjet1.SetPtEtaPhiE(SubjetPt[jIndex][0],SubjetEta[jIndex][0],SubjetPhi[jIndex][0],SubjetEn[jIndex][0]);
      subjet2.SetPtEtaPhiE(SubjetPt[jIndex][1],SubjetEta[jIndex][1],SubjetPhi[jIndex][1],SubjetEn[jIndex][1]);
      dRjj=subjet1.DeltaR(subjet2);

      if(SubjetCSV[jIndex][0]>0.244 && SubjetCSV[jIndex][1]>0.244) subjetbtag=true;

    }


    if(mode==1 && dRjj<0.3 && !fatjetCSV) continue;
    if(mode==1 && dRjj>0.3 && subjetbtag==false) continue;
    
    

    goodJetIndex.push_back(jIndex);    
    
    

  } // loop jets
 

  if(goodJetIndex.size()>0){
    accepted=goodJetIndex[0];
    return true;
  }
  
  else return false;





} // function brace

