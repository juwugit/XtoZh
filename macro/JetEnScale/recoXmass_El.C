//root -q -b -l recoXmass_El.C++\(\"0\"\,\"inputFile\"\,\"outputFile\"\)

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
#include "/home/juwu/XtoZh/macro/passJetID_mod.h"


std::string unctext = "/home/juwu/XtoZh/macro/START53_V23_Uncertainty_AK7PFchs.txt";


using namespace std;
void recoXmass_El(Int_t scaleMode, std::string inputFile, std::string outputFile){


  // check if the file is data or not
  bool isData=false;
  if(inputFile.find("data")!= std::string::npos)
    isData=true;


  // get TTree from file ...
  TreeReader data(inputFile.data());



  // declare histogram
  //const Float_t varBins[] = {680,720,760,800,840,920,1000,1100,1250,1400,1600,1800,2000,2400};
  //Int_t nvarBins = sizeof(varBins)/sizeof(varBins[0])-1;

  TH1F* h_sigXMass = new TH1F("h_sigXMass","signal region XMass",100,680,2400);
  TH1F* h_sbXMass = new TH1F("h_sbXMass","sideband region XMass",100,680,2400);

  
  h_sigXMass->Sumw2();
  h_sbXMass->Sumw2();  


  corrJetV corrJet(unctext);


  //Event loop
  for(long jEntry=0; jEntry<data.GetEntriesFast() ;jEntry++){

    data.GetEntry(jEntry);


    Int_t    CA8nJet     = data.GetInt("CA8nJet");
    Float_t* CA8jetPt    = data.GetPtrFloat("CA8jetPt");
    Float_t* CA8jetEta   = data.GetPtrFloat("CA8jetEta");
    Float_t* CA8jetPhi   = data.GetPtrFloat("CA8jetPhi");
    Float_t* CA8jetEn    = data.GetPtrFloat("CA8jetEn");
    Float_t* CA8jetPrunedM = data.GetPtrFloat("CA8jetPrunedMass");

    Int_t    nMu        = data.GetInt("nEle");
    Float_t* muPt       = data.GetPtrFloat("elePt");
    Float_t* muEta      = data.GetPtrFloat("eleEta");
    Float_t* muPhi      = data.GetPtrFloat("elePhi");
    Float_t* muM        = data.GetPtrFloat("eleM");   

    
    Int_t leadMu, secMu;
    passElectronID(data, &leadMu, &secMu);


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
    if(!passElectronID(data, &leadMu, &secMu)) continue;
    if(nMu<=1) continue;

      
    // Reco mLL & mLL cuts
    TLorentzVector l1(0,0,0,0);
    TLorentzVector l2(0,0,0,0);
    TLorentzVector recoZ(0,0,0,0);
    
    l1.SetPtEtaPhiM(muPt[leadMu],muEta[leadMu],muPhi[leadMu],muM[leadMu]);
    l2.SetPtEtaPhiM(muPt[secMu],muEta[secMu],muPhi[secMu],muM[secMu]);
    recoZ=(l1+l2);

    Float_t ZMass=recoZ.M();
    Float_t ZPt=recoZ.Pt();
    
    if(ZMass<70 || ZMass>110) continue;
    if(ZPt<80) continue;




    // reco XMass
    Int_t leadjet;
    Int_t csvlMode = 2; // 1:b-tagging only, 2:tau21 only
    TLorentzVector tempVector(0,0,0,0);

    passJetID(data, corrJet, csvlMode, scaleMode, &leadjet, &tempVector);
    if(!passJetID(data, corrJet, csvlMode, scaleMode, &leadjet, &tempVector))continue;

    TLorentzVector recoH = tempVector;
    TLorentzVector recoX(0,0,0,0);
    
    if(CA8nJet>0 && leadjet>=0){
      
      //recoH.SetPtEtaPhiE(CA8jetPt[leadjet],CA8jetEta[leadjet],CA8jetPhi[leadjet],CA8jetEn[leadjet]);
      recoX = recoZ+recoH;
      
      Float_t XMass=recoX.M();
      Float_t prunedmass=CA8jetPrunedM[leadjet];

            
      if(prunedmass>70 && prunedmass<110){

	h_sbXMass->Fill(XMass);

      }


      if(prunedmass>110 && prunedmass<140){
	
	h_sigXMass->Fill(XMass);

      }
      
    } // recoXMass

  } //entries 
  



  TFile* outFile = new TFile(outputFile.data(),"recreate");


  h_sigXMass->Write();
  h_sbXMass->Write();


  outFile->Close();

}
