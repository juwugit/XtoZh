//root -q -b -l recoXmass_El.C++\(\"inputFile\"\,\"outputFile\"\)

#include <map>
#include <vector>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <TH1.h>
#include <TRandom.h>
#include <TLorentzVector.h>
#include <TFile.h>
#include "/home/juwu/XtoZh/macro/untuplizer.h"
#include "/home/juwu/XtoZh/macro/passElectronID.h"
#include "/home/juwu/XtoZh/macro/passMuonID.h"
#include "/home/juwu/XtoZh/macro/passJetID_sherpa.h"


std::string unctext = "/home/juwu/XtoZh/macro/START53_V23_Uncertainty_AK7PFchs.txt";


using namespace std;
void recoXmass_sherpa_Mu(Int_t scaleMode=0){


  // get TTree from file ...
  TreeReader data("../delpanjTuple/delpanj_v4_DYJetsToLL_sherpa.root");
  corrJetV corrJet(unctext);


  // declare histogram
  //const Float_t varBins[] = {680,720,760,800,840,920,1000,1100,1250,1400,1600,1800,2000,2400};
  //Int_t nvarBins = sizeof(varBins)/sizeof(varBins[0])-1;

  TH1F* h_sbXMass = new TH1F("h_sbXMass","sideband region X mass", 60,0,2400);
  TH1F* h_sigXMass = new TH1F("h_sigXMass","signal region X mass", 60,0,2400);
  TH1F* h_sbCA8CSV = new TH1F("h_sbCA8CSV","sideband region CA8jet CSV",20,0,1);
  TH1F* h_sigCA8CSV = new TH1F("h_sigCA8CSV","signal region CA8jet CSV",20,0,1);
  TH1F* h_sbSubCSV = new TH1F("h_sbSubCSV","sideband region subjet CSV",20,0,1);
  TH1F* h_sigSubCSV = new TH1F("h_sigSubCSV","signal region subjet CSV",20,0,1);

  
  h_sbXMass->Sumw2();
  h_sigXMass->Sumw2();
  h_sbCA8CSV->Sumw2();
  h_sigCA8CSV->Sumw2();
  h_sbSubCSV->Sumw2();
  h_sigSubCSV->Sumw2();

  int counter = 0;


  //Event loop
  for(long jEntry=0; jEntry<data.GetEntriesFast() ;jEntry++){

    data.GetEntry(jEntry);

    Float_t  mcWeight    = data.GetFloat("mcWeight");
    Int_t    CA8nJet     = data.GetInt("CA8nJet");
    Float_t* CA8jetPt    = data.GetPtrFloat("CA8jetPt");
    Float_t* CA8jetEta   = data.GetPtrFloat("CA8jetEta");
    Float_t* CA8jetPhi   = data.GetPtrFloat("CA8jetPhi");
    Float_t* CA8jetEn    = data.GetPtrFloat("CA8jetEn");
    Float_t* CA8jetPrunedM = data.GetPtrFloat("CA8jetPrunedMass");
    Float_t* CA8jetCSV   = data.GetPtrFloat("CA8jetCSV");

    Int_t    nSubjet = data.GetInt("CA8nSubPrunedJet");
    Float_t* SubjetCSV = data.GetPtrFloat("CA8subjetPrunedCSV");
    Float_t* SubjetPt  = data.GetPtrFloat("CA8subjetPrunedPt");
    Float_t* SubjetEta = data.GetPtrFloat("CA8subjetPrunedEta");
    Float_t* SubjetPhi = data.GetPtrFloat("CA8subjetPrunedPhi");
    Float_t* SubjetEn  = data.GetPtrFloat("CA8subjetPrunedEn");

    Int_t    nEle        = data.GetInt("nMu");
    Float_t* elePt       = data.GetPtrFloat("muPt");
    Float_t* eleEta      = data.GetPtrFloat("muEta");
    Float_t* elePhi      = data.GetPtrFloat("muPhi");
    Float_t* eleM        = data.GetPtrFloat("muM");   

    //Int_t leadjet;    
    Int_t leadEle, secEle;
    passMuonID(data, &leadEle, &secEle);


    if(!passMuonID(data, &leadEle, &secEle)) continue;
    if(nEle<=1) continue;

      
    // Reco mLL & mLL cuts
    TLorentzVector l1(0,0,0,0);
    TLorentzVector l2(0,0,0,0);
    TLorentzVector recoZ(0,0,0,0);
    
    l1.SetPtEtaPhiM(elePt[leadEle],eleEta[leadEle],elePhi[leadEle],eleM[leadEle]);
    l2.SetPtEtaPhiM(elePt[secEle],eleEta[secEle],elePhi[secEle],eleM[secEle]);
    recoZ=(l1+l2);

    Float_t ZMass=recoZ.M();
    Float_t ZPt=recoZ.Pt();
    
    if(ZMass<70 || ZMass>110) continue;
    if(ZPt<80) continue;



    // reco XMass
    Int_t leadjet;
    Int_t csvlMode = 0;
    TLorentzVector tempVector(0,0,0,0);

    if(!passJetID(data, corrJet, csvlMode, scaleMode, &leadjet, &tempVector)) continue;

    TLorentzVector recoH = tempVector;
    TLorentzVector recoX(0,0,0,0);
    Float_t XMass=-999;

    if(CA8nJet>0 && leadjet>=0){
      
      //recoH.SetPtEtaPhiE(CA8jetPt[leadjet],CA8jetEta[leadjet],CA8jetPhi[leadjet],CA8jetEn[leadjet]);
      recoX = recoZ+recoH;
      
      XMass=recoX.M();
      Float_t prunedmass=CA8jetPrunedM[leadjet];
      
      if(prunedmass>70 && prunedmass<110) h_sbXMass->Fill(XMass, mcWeight);
      if(prunedmass>110 && prunedmass<140) h_sigXMass->Fill(XMass, mcWeight);
      
    }      



    // reco CSV
    TLorentzVector subjet1(0,0,0,0);
    TLorentzVector subjet2(0,0,0,0);
    Float_t dRjj=-999;
    Int_t maxjet = CA8nJet*nSubjet;

    for(Int_t i=0; i<maxjet; i=i+2){

      if( (i+1)>maxjet ) continue;

      //check subjet deltaR
      if(nSubjet>=2){

	subjet1.SetPtEtaPhiE(SubjetPt[i],SubjetEta[i],SubjetPhi[i],SubjetEn[i]);
	subjet2.SetPtEtaPhiE(SubjetPt[i+1],SubjetEta[i+1],SubjetPhi[i+1],SubjetEn[i+1]);
	dRjj=subjet1.DeltaR(subjet2);

      }

      // sideband region
      if(CA8jetPrunedM[leadjet]>70 && CA8jetPrunedM[leadjet]<110){

	if(dRjj>0.3){

	  if(SubjetCSV[i]>0) h_sbSubCSV->Fill(SubjetCSV[i], mcWeight);
	  if(SubjetCSV[i+1]>0) h_sbSubCSV->Fill(SubjetCSV[i+1], mcWeight);

	}

	if(dRjj<0.3 && CA8jetCSV[i]>0) h_sbCA8CSV->Fill(CA8jetCSV[i], mcWeight);
		
      }

      // signal region                                           
      if(CA8jetPrunedM[leadjet]>110 && CA8jetPrunedM[leadjet]<140){

        if(dRjj>0.3){

	  if(SubjetCSV[i]>0) h_sigSubCSV->Fill(SubjetCSV[i], mcWeight);
	  if(SubjetCSV[i+1]>0) h_sigSubCSV->Fill(SubjetCSV[i+1], mcWeight);

	}

	if(dRjj<0.3 && CA8jetCSV[i]>0) h_sigCA8CSV->Fill(CA8jetCSV[i], mcWeight);
	
      }
      
    } // jet loop                                                                    

    counter++;
    cout<<counter<<endl;
    

  } //entries 
  


  //save output
  TFile* outFile = new TFile("sherpa_Mu.root","recreate");

  h_sbXMass->Write();
  h_sigXMass->Write();
  h_sbCA8CSV->Write();
  h_sigCA8CSV->Write();
  h_sbSubCSV->Write();
  h_sigSubCSV->Write();



  outFile->Close();


}
