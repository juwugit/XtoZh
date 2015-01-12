//root -q -b -l recoXmass_El.C++\(\"inputFile\"\,\"outputFile\"\)

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
#include "/home/juwu/XtoZh/macro/JetSelections_v5.h"


using namespace std;
void recoXmass_El(std::string inputFile, std::string outputFile){


  bool isData=false;
  if(inputFile.find("data")!= std::string::npos)
    isData=true;


  //get TTree from file ...
  TreeReader data(inputFile.data());



  // declare histogram
  const Float_t varBins[] = {840,920,1000,1100,1250,1400,1600,1800,2000,2200,2400};
  
  Int_t nvarBins = sizeof(varBins)/sizeof(varBins[0])-1;


  TH1F* h_sbXMass = new TH1F("h_sbXMass","sideband region X mass", nvarBins, varBins);
  TH1F* h_sigXMass = new TH1F("h_sigXMass","signal resion X mass", nvarBins, varBins);
  
  
  h_sbXMass->Sumw2();
  h_sigXMass->Sumw2();
  


  //Event loop
  for(long jEntry=0; jEntry<data.GetEntriesFast() ;jEntry++){

    data.GetEntry(jEntry);


    Int_t    CA8nJet     = data.GetInt("CA8nJet");
    Float_t* CA8jetPt    = data.GetPtrFloat("CA8jetPt");
    Float_t* CA8jetEta   = data.GetPtrFloat("CA8jetEta");
    Float_t* CA8jetPhi   = data.GetPtrFloat("CA8jetPhi");
    Float_t* CA8jetM     = data.GetPtrFloat("CA8jetMass");
    Float_t* CA8jetPrunedM = data.GetPtrFloat("CA8jetPrunedMass");

    Int_t    nEle        = data.GetInt("nEle");
    Float_t* elePt       = data.GetPtrFloat("elePt");
    Float_t* eleEta      = data.GetPtrFloat("eleEta");
    Float_t* elePhi      = data.GetPtrFloat("elePhi");
    Float_t* eleM        = data.GetPtrFloat("eleM");   




    Int_t leadjet;
    PassJet(1, data, leadjet);
    
    Int_t leadEle, secEle;
    passElectronID(data, &leadEle, &secEle);





    // trigger
    std::string* trigName = data.GetPtrString("hlt_trigName");
    Int_t* trigResult = data.GetPtrInt("hlt_trigResult");
    const Int_t nsize = data.GetPtrStringSize();

    bool passTrigger=false;
    for(int it=0; it< nsize; it++)
      {
	std::string thisTrig= trigName[it];
	int results = trigResult[it];
     
	if(thisTrig.find("HLT_DoubleEle33")!= std::string::npos && results==1)
	  {
	    passTrigger=true;
	    break;
	  }
	
	/*
	if(thisTrig.find("HLT_Mu22_TkMu8")!= std::string::npos && results==1)
	  {
	    passTrigger=true;
	    break;
	  }
	*/
      }
   
    if(isData && !passTrigger)continue;
    if(!passElectronID(data, &leadEle, &secEle)) continue;
    if(nEle<=1) continue;


      
    // Reco mLL
    TLorentzVector l1(0,0,0,0);
    TLorentzVector l2(0,0,0,0);
    TLorentzVector recoZ(0,0,0,0);

    l1.SetPtEtaPhiM(elePt[leadEle],eleEta[leadEle],elePhi[leadEle],eleM[leadEle]);
    l2.SetPtEtaPhiM(elePt[secEle],eleEta[secEle],elePhi[secEle],eleM[secEle]);
    recoZ=(l1+l2);
    



    if(!PassJet(1, data, leadjet)) continue;


    // reco XMass
    TLorentzVector recoH(0,0,0,0);
    TLorentzVector recoX(0,0,0,0);
    
    if(CA8nJet>0 && leadjet>=0){
      
      recoH.SetPtEtaPhiM(CA8jetPt[leadjet],CA8jetEta[leadjet],CA8jetPhi[leadjet],CA8jetM[leadjet]);
      recoX = recoZ+recoH;

      Float_t XMass=recoX.M();
      Float_t ZMass=recoZ.M();
      Float_t ZPt=recoZ.Pt();
      Float_t prunedmass=CA8jetPrunedM[leadjet];

      if(ZMass<70 || ZMass>110) continue;
      if(ZPt<80) continue;
      
      if(prunedmass>50 && prunedmass<110) h_sbXMass->Fill(XMass);
      if(prunedmass>110 && prunedmass<140) h_sigXMass->Fill(XMass);
      
    }
      

  } //entries 

    
  



  //save output
  TFile* outFile = new TFile(outputFile.data(),"recreate");

  h_sbXMass->Write();
  h_sigXMass->Write();


  outFile->Close();


}
