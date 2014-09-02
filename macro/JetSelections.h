/*

This macro does following selections:

tau21<0.5 for leading jet
jetPt>30 , fabs(Eta)<2.4
PrunedJetMass>40 , PrunedJetPt>80 (at least one jet passes this selection)
jetID>0 (at least one jet passes ID cut)

return leading jet index


*/




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
  Float_t* CA8jetPrunedPt = data.GetPtrFloat("CA8jetPrunedPt");
  Float_t* CA8jetPrunedM  = data.GetPtrFloat("CA8jetPrunedMass");

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




  // define Map and MapIter
  typedef map<Float_t, Int_t, std::greater<Float_t> > Map;
  typedef Map::iterator MapIter;



  // Sorting electron
  Map sortElePt;
  vector<Int_t> sortEleIndex;
  sortEleIndex.clear();

  for(Int_t i=0; i<nEle; i++){
    sortElePt.insert(std::pair<Float_t, Int_t>(elePt[i], i));
  }

  for(MapIter it_part=sortElePt.begin(); it_part!=sortElePt.end(); ++it_part){
    sortEleIndex.push_back(it_part->second);
  }



  // Sorting muon
  Map sortMuPt;
  vector<Int_t> sortMuIndex;
  sortMuIndex.clear();

  for(Int_t i=0; i<nMu; i++){
    sortMuPt.insert(std::pair<Float_t, Int_t>(muPt[i], i));
  }

  for(MapIter it_part=sortMuPt.begin(); it_part!=sortMuPt.end(); ++it_part){
    sortMuIndex.push_back(it_part->second);
  }





  // determine which channel                                                                                        
  bool ee=false;
  bool mm=false;
  if(nEle>0 && nMu==0) ee=true;
  if(nEle==0 && nMu>0) mm=true;
  if(sortEleIndex.size()>0 && sortMuIndex.size()>0 && elePt[sortEleIndex[0]]>muPt[sortMuIndex[0]]) ee=true;
  if(sortEleIndex.size()>0 && sortMuIndex.size()>0 && elePt[sortEleIndex[0]]<muPt[sortMuIndex[0]]) mm=true;
  


  // declare Map for jets and do sorting
  Map sortJetPt;
  vector<Int_t> sortJetIndex;
  sortJetIndex.clear();
  
  for(Int_t i=0; i<CA8nJet; i++){
    sortJetPt.insert(std::pair<Float_t, Int_t>(CA8jetPt[i], i));
  }

  for(MapIter it_part=sortJetPt.begin(); it_part!=sortJetPt.end(); ++it_part){
    sortJetIndex.push_back(it_part->second);
  }


  
  // remove overlape for ee channel
  vector<Int_t> goodJetIndex;
  goodJetIndex.clear();

  TLorentzVector lep(0,0,0,0);
  TLorentzVector alljets(0,0,0,0);
  Float_t dRjl=-999;

  Int_t nSortJet=sortJetIndex.size();
  Int_t nSortEle=sortEleIndex.size();
  Int_t nSortMu=sortMuIndex.size();


  for(Int_t k=0; k<nSortJet; k++){


    alljets.SetPtEtaPhiM(CA8jetPt[sortJetIndex[k]],
                         CA8jetEta[sortJetIndex[k]],
			 CA8jetPhi[sortJetIndex[k]],
			 CA8jetM[sortJetIndex[k]]);


    if(ee==true){

      for(Int_t i=0; i<nSortEle; i++){


	if(eleID[sortEleIndex[i]]){
	 
	  lep.SetPtEtaPhiM(elePt[sortEleIndex[i]],
			   eleEta[sortEleIndex[i]],
			   elePhi[sortEleIndex[i]],
			   eleM[sortEleIndex[i]]);
	  
	  dRjl=alljets.DeltaR(lep);
	  if(dRjl<0.5 && dRjl!=-999) continue;

	  goodJetIndex.push_back(sortJetIndex[k]);

	} // eleID
      } // loop ele
    } // ee



    if(mm==true){

      for(Int_t i=0; i<nSortMu; i++){


        if(muID[sortMuIndex[i]]){

          lep.SetPtEtaPhiM(muPt[sortMuIndex[i]],
                           muEta[sortMuIndex[i]],
                           muPhi[sortMuIndex[i]],
                           muM[sortMuIndex[i]]);

          dRjl=alljets.DeltaR(lep);
          if(dRjl<0.5 && dRjl!=-999) continue;

          goodJetIndex.push_back(sortJetIndex[k]);

	} // muID                                                                       
      } // loop muon                                                                             
    } // mm                               

    

  } // overlape
  

  
  
  
  // push back leading-jet index
  Int_t nGoodJet=goodJetIndex.size();
  if(nGoodJet>0) accepted=goodJetIndex[0];



  
  
  // Jet selections                                                                               
  bool basicCuts=true;
  bool IDcut=false;
  bool prunedJetCuts=false;

  
  for(Int_t i=0; i<nGoodJet; i++){
    
    if(CA8jetPt[goodJetIndex[i]]<30 || fabs(CA8jetEta[goodJetIndex[i]])>2.4) basicCuts=false;
    if(CA8jetID[goodJetIndex[i]]>0) IDcut=true;
    if(CA8jetPrunedPt[goodJetIndex[i]]>80 || CA8jetPrunedM[goodJetIndex[i]]>40) prunedJetCuts=true;

  }
  
  
  if(basicCuts==true && IDcut==true && prunedJetCuts==true) return true;
  else return false;
  
  
  
  

  

  

} // function brace
