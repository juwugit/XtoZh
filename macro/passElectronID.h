



Bool_t passElectronID(TreeReader &data, 
		      Int_t *stRecoEleIndex, Int_t *ndRecoEleIndex){


  Int_t    nEle   = data.GetInt("nEle"); 
  Int_t*   elePassID = data.GetPtrInt("elePassID");
  Float_t  eleRho = data.GetFloat("eleRho");
  Float_t* eleEt  = data.GetPtrFloat("eleEt");
  Float_t* eleScEta = data.GetPtrFloat("eleScEta");
  Float_t* eleUserTrkIso = data.GetPtrFloat("eleUserTrkIso");
  Float_t* eleUserCalIso = data.GetPtrFloat("eleUserCalIso");

  // sorting electron and pass the electron ID

  vector<Int_t> tightEleIndex;

  typedef map<double, int, std::greater<double> > eleMap;
  eleMap sortEleEt;
  typedef eleMap::iterator mapEleIter;

  for(Int_t i = 0; i < nEle; i++){

    sortEleEt.insert(std::pair<Float_t, Int_t>(eleEt[i], i));

  }

  for(mapEleIter it_part = sortEleEt.begin(); it_part != sortEleEt.end(); ++it_part){

    // at least two electrons
    // pt of these electrons must greater than 40

    Int_t sortEleIndex = it_part->second;

    Double_t isoCutValue = 2+(0.03*eleEt[sortEleIndex]);

    if( elePassID[sortEleIndex] <= 0 ) continue;
    if( eleEt[sortEleIndex] <= 40 ) continue;
    if( eleUserTrkIso[sortEleIndex] >= 5 ) continue;

    // barrel selection
    if( fabs(eleScEta[sortEleIndex]) > 0 && fabs(eleScEta[sortEleIndex]) < 1.4442 ){

      if( (eleUserCalIso[sortEleIndex]-(0.06205*eleRho)) >= isoCutValue ) 
	continue;

    }

    // endcap selection
    if( fabs(eleScEta[sortEleIndex]) > 1.566 && fabs(eleScEta[sortEleIndex]) < 2.5 ){

      if( eleEt[sortEleIndex] < 50 ){
	if( (eleUserCalIso[sortEleIndex]-(0.06205*eleRho)) >= 2.5 ) 
	  continue;
      }

      if( eleEt[sortEleIndex] > 50 ){
	if( (eleUserCalIso[sortEleIndex]-(0.06205*eleRho)) >= (isoCutValue+0.5) ) 
	  continue;
      }
    
    }
    
    tightEleIndex.push_back(sortEleIndex);

  }

  if( tightEleIndex.size() < 2 ) return false;
    

  //-----------------------------------------------------------------------------------//


  // filling index 

  *stRecoEleIndex = -1;
  *ndRecoEleIndex = -1;

  if( tightEleIndex.size() > 0 ){

    *stRecoEleIndex = tightEleIndex[0];
    *ndRecoEleIndex = tightEleIndex[1];

  }   

  if( *stRecoEleIndex < 0 || *ndRecoEleIndex < 0 ) return false;

  return true;

}
