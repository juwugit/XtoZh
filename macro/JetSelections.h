/*

This macro does following selections:

tau21<0.5 for leading jet
jetPt>30 , fabs(Eta)<2.4
PrunedJetMass>40 , PrunedJetPt>80 (at least one jet passes this selection)
jetID>0 (at least one jet passes ID cut)

return leading jet index


*/




Bool_t PassJet(TreeReader &data, Int_t &accepted){

  accepted=0;

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

  Int_t    nMu         = data.GetInt("nMu");
  Float_t* muPt        = data.GetPtrFloat("muPt");
  Float_t* muEta       = data.GetPtrFloat("muEta");
  Float_t* muPhi       = data.GetPtrFloat("muPhi");
  Float_t* muM         = data.GetPtrFloat("muM");




  // define Map and MapIter
  typedef map<double, int, std::greater<double> > Map;
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
  Int_t sortJetIndex;

  for(Int_t i=0; i<CA8nJet; i++){
    sortJetPt.insert(std::pair<Float_t, Int_t>(CA8jetPt[i], i));
  }



  // remove overlape for ee channel
  bool overlape=false;

  for(MapIter it_part=sortJetPt.begin(); it_part!=sortJetPt.end(); ++it_part){
    sortJetIndex=it_part->second;

    TLorentzVector lep(0,0,0,0);
    TLorentzVector alljets(0,0,0,0);

    if(ee==true) lep.SetPtEtaPhiM(elePt[sortEleIndex[0]],
				  eleEta[sortEleIndex[0]],
				  elePhi[sortEleIndex[0]],
				  eleM[sortEleIndex[0]]);

    if(mm==true) lep.SetPtEtaPhiM(muPt[sortMuIndex[0]],
				  muEta[sortMuIndex[0]],
				  muPhi[sortMuIndex[0]],
				  muM[sortMuIndex[0]]);
	
    alljets.SetPtEtaPhiM(CA8jetPt[sortJetIndex],
			 CA8jetEta[sortJetIndex],
			 CA8jetPhi[sortJetIndex],
			 CA8jetM[sortJetIndex]);


    float dRjl=-999;
    dRjl=lep.DeltaR(alljets);

    if(dRjl<0.5 && dRjl!=-999) overlape=true;

    break;

  } // overlape





  if(overlape==false){
  

    // push back leading-jet index
    float leadjetTau21=-999;

    for(MapIter it_part=sortJetPt.begin(); it_part!=sortJetPt.end(); ++it_part){
      sortJetIndex=it_part->second;

      leadjetTau21=CA8jetTau2[sortJetIndex]/CA8jetTau1[sortJetIndex];
      accepted=sortJetIndex;

      break;

    }

  
    // Jet selections                                                                               
    bool basicCuts=true;
    bool IDcut=false;
    bool prunedJetCuts=false;


    for(MapIter it_part=sortJetPt.begin(); it_part!=sortJetPt.end(); ++it_part){
      sortJetIndex=it_part->second;

      if(CA8jetPt[sortJetIndex]<30 || fabs(CA8jetEta[sortJetIndex])>2.4) basicCuts=false;
      if(CA8jetID[sortJetIndex]>0) IDcut=true;
      if(CA8jetPrunedPt[sortJetIndex]>80 || CA8jetPrunedM[sortJetIndex]>40) prunedJetCuts=true;

    }
  
    
    if(basicCuts==true && IDcut==true && prunedJetCuts==true) return true;
    else return false;


  } // overlape==false




  // overlape==true
  else {

    return false;
    accepted=-1;

  }




} // function brace
