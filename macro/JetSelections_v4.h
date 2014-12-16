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




  // determine which channel                                                                                        
  bool ee=true;
  bool mm=false;
  if(nEle>0 && nMu==0) ee=true;   
  else if(nEle==0 && nMu>0) mm=true;
  else if(nEle>0 && nMu>0 && elePt[0]>muPt[0]) ee=true; 
  else if(nEle>0 && nMu>0 && elePt[0]<muPt[0]) mm=true; 
  

  
  // remove overlape for ee channel
  vector<Int_t> goodJetIndex;
  goodJetIndex.clear();



  for(Int_t jIndex=0; jIndex<CA8nJet; jIndex++){


    bool overlap=false;
    bool basicCuts=(CA8jetPt[jIndex]>30)&&(fabs(CA8jetEta[jIndex])<2.4);
    if(!basicCuts) continue;

    bool IDcut=(CA8jetID[jIndex]>0);
    if(!IDcut) continue;

    bool prunedJetCuts= CA8jetPt[jIndex]>80 && 
      CA8jetPrunedM[jIndex]>110 && CA8jetPrunedM[jIndex]<140;
    if(!prunedJetCuts) continue;

    if(CA8jetTau2[jIndex]/CA8jetTau1[jIndex]>0.5)continue;

    TLorentzVector alljets(0,0,0,0);


    alljets.SetPtEtaPhiM(CA8jetPt[jIndex],
                         CA8jetEta[jIndex],
			 CA8jetPhi[jIndex],
			 CA8jetM[jIndex]);



    if(ee){

      for(Int_t i=0; i<nEle; i++){


	if(eleID[i]>0){

	  TLorentzVector lep(0,0,0,0);
	  lep.SetPtEtaPhiM(elePt[i],
			   eleEta[i],
			   elePhi[i],
			   eleM[i]);
	  
	  Float_t dRjl=alljets.DeltaR(lep);
	  
	  if(dRjl<1.0 && dRjl!=-999){
	    overlap=true;
	    break;
	  }

	} // eleID
      } // loop ele
    } // ee



    else if(mm){
      
      for(Int_t i=0; i<nMu; i++){


        if(muID[i]>0){

	  TLorentzVector lep(0,0,0,0);
          lep.SetPtEtaPhiM(muPt[i],
                           muEta[i],
                           muPhi[i],
                           muM[i]);

	  Float_t dRjl=alljets.DeltaR(lep);

          if(dRjl<1.0 && dRjl!=-999){
	    overlap=true;
	    break;
	  }

	} // muID                                                                       
      } // loop muon                                                                             
    } // mm                               




    if(overlap) continue;


    goodJetIndex.push_back(jIndex);    
    
    

  } // overlap


  
  if(goodJetIndex.size()>0){
    accepted=goodJetIndex[0];
    return true;
  }
  else return false;





} // function brace
