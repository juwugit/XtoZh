// note that this macro do only two things
// remove overlape and make cut on tau21<0.5
// no basic kinematic cut and jetID cut



void GoodJetIndex(TreeReader &data, vector<int> &accepted){

  accepted.clear();

  Int_t    CA8nJet     = data.GetInt("CA8nJet");
  Float_t* CA8jetPt    = data.GetPtrFloat("CA8jetPt");
  Float_t* CA8jetEta   = data.GetPtrFloat("CA8jetEta");
  Float_t* CA8jetPhi   = data.GetPtrFloat("CA8jetPhi");
  Float_t* CA8jetM     = data.GetPtrFloat("CA8jetMass");
  Int_t*   CA8jetID    = data.GetPtrInt("CA8jetPassID");
  Float_t* CA8jetTau1  = data.GetPtrFloat("CA8jetTau1");
  Float_t* CA8jetTau2  = data.GetPtrFloat("CA8jetTau2");
  Float_t* CA8jetTau3  = data.GetPtrFloat("CA8jetTau3");
  Float_t* CA8jetTau4  = data.GetPtrFloat("CA8jetTau4");
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


  // Ordering lepton array by Pt                                                                                          
  for(int i=0; i<nEle; i++){
    for(int j=0; j<i; j++){
      if(elePt[i] > elePt[j]){
	swap(elePt[i], elePt[j]);
	swap(eleEta[i], eleEta[j]);
	swap(elePhi[i], elePhi[j]);
	swap(eleM[i], eleM[j]);
      }
    }
  } // ele                                                                                                                
  for(int i=0; i<nMu; i++){
    for(int j=0; j<i; j++){
      if(muPt[i] > muPt[j]){
	swap(muPt[i], muPt[j]);
	swap(muEta[i], muEta[j]);
	swap(muPhi[i], muPhi[j]);
	swap(muM[i], muM[j]);
      }
    }
  } // mu                                                                                                                 



    // determine which channel                                                                                             
  bool ee=false;
  bool mm=false;
  if(nEle>0 && nMu==0) ee=true;
  if(nEle==0 && nMu>0) mm=true;
  if(nEle>0 && nMu>0 && elePt[0]>muPt[0]) ee=true;
  if(nEle>0 && nMu>0 && elePt[0]<muPt[0]) mm=true;
  



  // remove overlape and make cut on Tau21
  for(int i=0; i<CA8nJet; i++){

    TLorentzVector lep(0,0,0,0);
    TLorentzVector alljets(0,0,0,0);

    if(ee==true) lep.SetPtEtaPhiM(elePt[0],eleEta[0],elePhi[0],eleM[0]);
    if(mm==true) lep.SetPtEtaPhiM(muPt[0],muEta[0],muPhi[0],muM[0]);

    alljets.SetPtEtaPhiM(CA8jetPt[i],
			 CA8jetEta[i],
			 CA8jetPhi[i],
			 CA8jetM[i]);

    float dRjl=-999;
    dRjl=lep.DeltaR(alljets);

    float Tau21=-999;
    Tau21=CA8jetTau2[i]/CA8jetTau1[i];

    if(dRjl<0.5 && dRjl!=-999) continue;
    if(Tau21>0.5 && Tau21!=-999) continue;
    accepted.push_back(i);

  } // loop jet                                     







}// void
