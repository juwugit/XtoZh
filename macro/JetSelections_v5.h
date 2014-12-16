/*

v5: vector sorting version

This macro does following selections:

1. tau21<0.5 for leading jet (optional)
2. b-tagging CSVL cut on subjet or CA8jet (optional)

3.
   remove overlap between jet and leptons
   jetPt>30 , fabs(Eta)<2.4
   PrunedJetMass>40 , PrunedJetPt>80 (at least one jet passes this selection)
   jetID>0 (at least one jet passes ID cut)

4. return leading jet index

*/


struct myMap
{
  Int_t index;
  Float_t pt;
};

Bool_t PtGreater (myMap i,myMap j) { return (i.pt>j.pt); }
Bool_t PassJet(TreeReader &data, Int_t &accepted){

  accepted=-1;

  Int_t    CA8nJet     = data.GetInt("CA8nJet");
  Float_t* CA8jetPt    = data.GetPtrFloat("CA8jetPt");
  Float_t* CA8jetEta   = data.GetPtrFloat("CA8jetEta");
  Float_t* CA8jetPhi   = data.GetPtrFloat("CA8jetPhi");
  Float_t* CA8jetM     = data.GetPtrFloat("CA8jetMass");
  Int_t*   CA8jetID    = data.GetPtrInt("CA8jetPassID");
  Float_t* CA8jetTau1  = data.GetPtrFloat("CA8jetTau1");
  Float_t* CA8jetTau2  = data.GetPtrFloat("CA8jetTau2");
  Float_t* CA8jetPrunedM  = data.GetPtrFloat("CA8jetPrunedMass");

  // b-tagging
  Float_t* CA8jetCSV   = data.GetPtrFloat("CA8jetCSV");
  Int_t*   nSubjet = data.GetPtrInt("CA8nSubPrunedJet");
  vector<Float_t>* SubjetCSV = data.GetPtrVectorFloat("CA8subjetPrunedCSV");
  vector<Float_t>* SubjetPt  = data.GetPtrVectorFloat("CA8subjetPrunedPt");
  vector<Float_t>* SubjetEta = data.GetPtrVectorFloat("CA8subjetPrunedEta");
  vector<Float_t>* SubjetPhi = data.GetPtrVectorFloat("CA8subjetPrunedPhi");
  vector<Float_t>* SubjetM   = data.GetPtrVectorFloat("CA8subjetPrunedMass");

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

  std::vector<Int_t> sortEleIndex;
  for(Int_t i=0; i<nEle; i++){
    sortEleIndex.push_back(sortElePt[i].index);
  }

  
  // Sorting Muon
  vector<myMap> sortMuPt;
  for(Int_t i=0; i<nMu; i++){

    myMap temp;
    temp.index = i;
    temp.pt = muPt[i];
    sortMuPt.push_back(temp);

  }
  std::sort(sortMuPt.begin(),sortMuPt.end(),PtGreater);

  std::vector<Int_t> sortMuIndex;
  for(Int_t i=0; i<nMu; i++){
    sortMuIndex.push_back(sortMuPt[i].index);
  }

   
  // determine which channel                                                                                        
  bool El=false;
  bool Mu=false;
  if(nEle>0 && nMu==0) El=true;
  if(nEle==0 && nMu>0) Mu=true;
  if(sortEleIndex.size()>0 && sortMuIndex.size()>0 && elePt[sortEleIndex[0]]>muPt[sortMuIndex[0]]) El=true;
  if(sortEleIndex.size()>0 && sortMuIndex.size()>0 && elePt[sortEleIndex[0]]<muPt[sortMuIndex[0]]) Mu=true;
  

  // Sorting Jet
  vector<myMap> sortJetPt;
  for(Int_t i=0; i<CA8nJet; i++){

    myMap temp;
    temp.index = i;
    temp.pt = CA8jetPt[i];
    sortJetPt.push_back(temp);

  }
  std::sort(sortJetPt.begin(),sortJetPt.end(),PtGreater);

  std::vector<Int_t> sortJetIndex;
  for(Int_t i=0; i<CA8nJet; i++){
    sortJetIndex.push_back(sortJetPt[i].index);
  }


  // remove overlap
  vector<Int_t> goodJetIndex;
  goodJetIndex.clear();

  TLorentzVector lep(0,0,0,0);
  TLorentzVector alljets(0,0,0,0);
  Float_t dRjl=-999;

  Int_t nSortJet=sortJetIndex.size();
  Int_t nSortEle=sortEleIndex.size();
  Int_t nSortMu=sortMuIndex.size();

  
  for(Int_t k=0; k<nSortJet; k++){

    Int_t jIndex=sortJetIndex[k];

    bool overlap=false;
    bool basicCuts=(CA8jetPt[jIndex]>30)&&(fabs(CA8jetEta[jIndex])<2.4);
    bool IDcut=(CA8jetID[jIndex]>0);
    bool prunedJetCuts=(CA8jetPt[jIndex]>80)&&(CA8jetPrunedM[jIndex]>40);
    bool Tau21Cut=((CA8jetTau2[jIndex]/CA8jetTau1[jIndex])<0.5);
    bool fatjetCSV=(CA8jetCSV[jIndex]>0.244);


    alljets.SetPtEtaPhiM(CA8jetPt[jIndex],
                         CA8jetEta[jIndex],
			 CA8jetPhi[jIndex],
			 CA8jetM[jIndex]);


    if(El==true){

      for(Int_t i=0; i<nSortEle; i++){

	if(eleID[sortEleIndex[i]]>0){
	 
	  lep.SetPtEtaPhiM(elePt[sortEleIndex[i]],
			   eleEta[sortEleIndex[i]],
			   elePhi[sortEleIndex[i]],
			   eleM[sortEleIndex[i]]);
	  
	  dRjl=alljets.DeltaR(lep);
	  
	  if(dRjl<0.5 && dRjl!=-999){
	    overlap=true;
	    break;
	  }

	} // eleID
      } // loop ele
    } // ee


    if(Mu==true){

      for(Int_t i=0; i<nSortMu; i++){

        if(muID[sortMuIndex[i]]>0){

          lep.SetPtEtaPhiM(muPt[sortMuIndex[i]],
                           muEta[sortMuIndex[i]],
                           muPhi[sortMuIndex[i]],
                           muM[sortMuIndex[i]]);

          dRjl=alljets.DeltaR(lep);

          if(dRjl<0.5 && dRjl!=-999){
	    overlap=true;
	    break;
	  }

	} // muID                                                                       
      } // loop muon                                                                             
    } // mm                               




    if(overlap==true) continue;
    if(!basicCuts) continue;
    if(!IDcut) continue;
    if(!prunedJetCuts) continue;
    //if(!Tau21Cut) continue;

    
    // b-tagging CSVL cut
    TLorentzVector subjet1(0,0,0,0);
    TLorentzVector subjet2(0,0,0,0);
    Float_t dRjj=-999;
    bool subjetbtag=false;

    if(nSubjet[jIndex]==2){

      subjet1.SetPtEtaPhiM(SubjetPt[jIndex][0],SubjetEta[jIndex][0],SubjetPhi[jIndex][0],SubjetM[jIndex][0]);
      subjet2.SetPtEtaPhiM(SubjetPt[jIndex][1],SubjetEta[jIndex][1],SubjetPhi[jIndex][1],SubjetM[jIndex][1]);
      Float_t dRjj=subjet1.DeltaR(subjet2);

      if(SubjetCSV[jIndex][0]>0.244 && SubjetCSV[jIndex][1]>0.244) subjetbtag=true;

    }

    if(dRjj<0.3 && !fatjetCSV) continue;
    if(dRjj>0.3 && subjetbtag==false) continue;

    

    goodJetIndex.push_back(jIndex);    
    
    

  } // loop jets
 

  if(sortJetIndex.size()>0){
    accepted=sortJetIndex[0];
    return true;
  }
  
  else return false;





} // function brace

