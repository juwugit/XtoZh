
Bool_t passMuonID(TreeReader &data, 
		  Int_t *stRecoMuIndex, Int_t *ndRecoMuIndex){


  Int_t    nMu   = data.GetInt("nMu"); 
  Int_t*   muPassID = data.GetPtrInt("muPassID");
  Float_t* muPt  = data.GetPtrFloat("muPt");
  Float_t* muCorrTrkIso = data.GetPtrFloat("muCorrTrkIso");

  // sorting muon and pass the muon ID

  vector<Int_t> howManyMu;
  vector<Int_t> basicMuIndex;
  vector<Int_t> onlyGlobalIndex;
  vector<Int_t> onlyTightPtIdex;
  vector<Int_t> globalTightPtIndex;

  typedef map<double, int, std::greater<double> > muMap;
  muMap sortMuPt;
  typedef muMap::iterator mapMuIter;

  for(Int_t i = 0; i < nMu; i++){

    sortMuPt.insert(std::pair<Float_t, Int_t>(muPt[i], i));

  }

  for(mapMuIter it_part = sortMuPt.begin(); it_part != sortMuPt.end(); ++it_part){

    // at least two muons
    // must be tracker mu, at least one is global mu
    // pt must greater than 20, one must greater than 40

    Int_t sortMuIndex = it_part->second;

    if( !(muPassID[sortMuIndex] & 4) ) continue;
    if( muPt[sortMuIndex] <= 20 ) continue; 
    if( (muCorrTrkIso[sortMuIndex] / muPt[sortMuIndex]) >= 0.1 ) continue;

    howManyMu.push_back(sortMuIndex);

    if( !(muPassID[sortMuIndex] & 2) && muPt[sortMuIndex] < 40 )
      basicMuIndex.push_back(sortMuIndex);

    if( (muPassID[sortMuIndex] & 2) && muPt[sortMuIndex] < 40 )
      onlyGlobalIndex.push_back(sortMuIndex);

    if( !(muPassID[sortMuIndex] & 2) && muPt[sortMuIndex] > 40 )
      onlyTightPtIdex.push_back(sortMuIndex);

    if( (muPassID[sortMuIndex] & 2) && muPt[sortMuIndex] > 40 )
      globalTightPtIndex.push_back(sortMuIndex);

  }

  if( howManyMu.size() < 2 ) return false;

  if( onlyGlobalIndex.size() < 1 && 
      onlyTightPtIdex.size() < 1 && 
      globalTightPtIndex.size() < 1 ) return false;

  if( globalTightPtIndex.size() < 1 && 
      onlyGlobalIndex.size() < 1 ) return false;

  if( globalTightPtIndex.size() < 1 && 
      onlyTightPtIdex.size() < 1 ) return false;
    

  //-----------------------------------------------------------------------------------//


  // filling index 

  *stRecoMuIndex = -1;
  *ndRecoMuIndex = -1;

  if( globalTightPtIndex.size() > 0 ){

    *stRecoMuIndex = globalTightPtIndex[0];

    if( globalTightPtIndex.size() > 1 )
      *ndRecoMuIndex = globalTightPtIndex[1];

    else if( onlyGlobalIndex.size() > 1 )
      *ndRecoMuIndex = onlyGlobalIndex[0];

    else if( onlyTightPtIdex.size() > 1 )
      *ndRecoMuIndex = onlyTightPtIdex[0];

    else if( basicMuIndex.size() > 0 )
      *ndRecoMuIndex = basicMuIndex[0];

  }   

  if( globalTightPtIndex.size() < 1 ){

    *stRecoMuIndex = onlyGlobalIndex[0];
    *ndRecoMuIndex = onlyTightPtIdex[0];
       
  } 

  if( *stRecoMuIndex < 0 || *ndRecoMuIndex < 0 ) return false;

  return true;

}
