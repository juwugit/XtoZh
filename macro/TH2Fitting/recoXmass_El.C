//root -q -b -l recoXmass_El.C++\(\"inputFile\"\,\"outputFile\"\)

#include <map>
#include <vector>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <TH1.h>
#include <TH2.h>
#include <TRandom.h>
#include <TLorentzVector.h>
#include <TFile.h>
#include "../macro/untuplizer.h"
#include "../macro/passElectronID.h"
#include "../macro/passMuonID.h"
#include "../macro/JetSelections.h"


using namespace std;
void recoXmass_El(std::string inputFile, std::string outputFile){


  // check if the file is data or not
  bool isData=false;
  if(inputFile.find("data")!= std::string::npos)
    isData=true;


  // get TTree from file ...
  TreeReader data(inputFile.data());



  // declare histogram
  const Double_t varBins[] = {680,720,760,800,840,920,1000,1100,1250,1400,1600,1800,2000,2400};
  Int_t nvarBins = sizeof(varBins)/sizeof(varBins[0])-1;

  TH1F* h_sbXMass = new TH1F("h_sbXMass","sideband region X mass", nvarBins, varBins);
  TH1F* h_sigXMass = new TH1F("h_sigXMass","signal region X mass", nvarBins, varBins);
  TH1F* h_sbCA8CSV = new TH1F("h_sbCA8CSV","sideband region CA8jet CSV",20,0,1);
  TH1F* h_sigCA8CSV = new TH1F("h_sigCA8CSV","signal region CA8jet CSV",20,0,1);
  TH1F* h_sbSubCSV = new TH1F("h_sbSubCSV","sideband region subjet CSV",20,0,1);
  TH1F* h_sigSubCSV = new TH1F("h_sigSubCSV","signal region subjet CSV",20,0,1);

  TH2F* h_sigXMCSV = new TH2F("h_sigXMCSV","signal region XMass vs CA8jet CSV",nvarBins,varBins,20,0,1);
  TH2F* h_sbXMCSV = new TH2F("h_sbXMCSV","sideband region XMass vs CA8jet CSV",nvarBins,varBins,20,0,1);
  TH2F* h_sigXMsCSV = new TH2F("h_sigXMsCSV","signal region XMass vs subjet CSV",nvarBins,varBins,20,0,1);
  TH2F* h_sbXMsCSV = new TH2F("h_sbXMsCSV","sideband region XMass vs subjet CSV",nvarBins,varBins,20,0,1);


  
  h_sbXMass->Sumw2();
  h_sigXMass->Sumw2();
  h_sbCA8CSV->Sumw2();
  h_sigCA8CSV->Sumw2();
  h_sbSubCSV->Sumw2();
  h_sigSubCSV->Sumw2();

  h_sigXMCSV->Sumw2();
  h_sbXMCSV->Sumw2();
  h_sigXMsCSV->Sumw2();
  h_sbXMsCSV->Sumw2();




  //Event loop
  for(long jEntry=0; jEntry<data.GetEntriesFast() ;jEntry++){

    data.GetEntry(jEntry);


    Int_t    CA8nJet     = data.GetInt("CA8nJet");
    Float_t* CA8jetPt    = data.GetPtrFloat("CA8jetPt");
    Float_t* CA8jetEta   = data.GetPtrFloat("CA8jetEta");
    Float_t* CA8jetPhi   = data.GetPtrFloat("CA8jetPhi");
    Float_t* CA8jetEn     = data.GetPtrFloat("CA8jetEn");
    Float_t* CA8jetPrunedM = data.GetPtrFloat("CA8jetPrunedMass");
    Float_t* CA8jetCSV   = data.GetPtrFloat("CA8jetCSV");

    Int_t*   nSubjet = data.GetPtrInt("CA8nSubPrunedJet");
    vector<Float_t>* SubjetCSV = data.GetPtrVectorFloat("CA8subjetPrunedCSV");
    vector<Float_t>* SubjetPt  = data.GetPtrVectorFloat("CA8subjetPrunedPt");
    vector<Float_t>* SubjetEta = data.GetPtrVectorFloat("CA8subjetPrunedEta");
    vector<Float_t>* SubjetPhi = data.GetPtrVectorFloat("CA8subjetPrunedPhi");
    vector<Float_t>* SubjetEn   = data.GetPtrVectorFloat("CA8subjetPrunedEn");

    Int_t    nEle        = data.GetInt("nEle");
    Float_t* elePt       = data.GetPtrFloat("elePt");
    Float_t* eleEta      = data.GetPtrFloat("eleEta");
    Float_t* elePhi      = data.GetPtrFloat("elePhi");
    Float_t* eleM        = data.GetPtrFloat("eleM");   

    Int_t leadjet;    
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
    PassJet(3, data, leadjet);
    if(!PassJet(3, data, leadjet)) continue;

    TLorentzVector recoH(0,0,0,0);
    TLorentzVector recoX(0,0,0,0);
    Float_t XMass=-999;

    if(CA8nJet>0 && leadjet>=0){
      
      recoH.SetPtEtaPhiE(CA8jetPt[leadjet],CA8jetEta[leadjet],CA8jetPhi[leadjet],CA8jetEn[leadjet]);
      recoX = recoZ+recoH;
      
      XMass=recoX.M();
      Float_t prunedmass=CA8jetPrunedM[leadjet];
      
      if(prunedmass>70 && prunedmass<110) h_sbXMass->Fill(XMass);
      if(prunedmass>110 && prunedmass<140) h_sigXMass->Fill(XMass);
      
    }



    // reco CSV
    TLorentzVector subjet1(0,0,0,0);
    TLorentzVector subjet2(0,0,0,0);
    Float_t dRjj=-999;

    for(int i=0; i<CA8nJet; i++){

      //check subjet deltaR
      if(nSubjet[i]>=2){

	subjet1.SetPtEtaPhiE(SubjetPt[i][0],SubjetEta[i][0],SubjetPhi[i][0],SubjetEn[i][0]);
	subjet2.SetPtEtaPhiE(SubjetPt[i][1],SubjetEta[i][1],SubjetPhi[i][1],SubjetEn[i][1]);
	dRjj=subjet1.DeltaR(subjet2);

      }

      if(dRjj==-999) continue;


      // sideband region
      if(CA8jetPrunedM[leadjet]>70 && CA8jetPrunedM[leadjet]<110){

	if(dRjj>0.3){

	  if(SubjetCSV[i][0]>0) h_sbSubCSV->Fill(SubjetCSV[i][0]);
	  if(SubjetCSV[i][1]>0) h_sbSubCSV->Fill(SubjetCSV[i][1]);
	  if(SubjetCSV[i][0]>0) h_sbXMsCSV->Fill(XMass, SubjetCSV[i][0]); //TH2
	  if(SubjetCSV[i][1]>0) h_sbXMsCSV->Fill(XMass, SubjetCSV[i][1]); //TH2

	  
	} // subjet

	if(dRjj<0.3){
	  
	  h_sbCA8CSV->Fill(CA8jetCSV[i]);
	  h_sbXMCSV->Fill(XMass, CA8jetCSV[i]); //TH2

	} // fatjet
      }


      // signal region                                           
      if(CA8jetPrunedM[leadjet]>110 && CA8jetPrunedM[leadjet]<140){

        if(dRjj>0.3){

	  if(SubjetCSV[i][0]>0) h_sigSubCSV->Fill(SubjetCSV[i][0]);
	  if(SubjetCSV[i][1]>0) h_sigSubCSV->Fill(SubjetCSV[i][1]);
	  if(SubjetCSV[i][0]>0) h_sigXMsCSV->Fill(XMass, SubjetCSV[i][0]); //TH2
	  if(SubjetCSV[i][1]>0) h_sigXMsCSV->Fill(XMass, SubjetCSV[i][1]); //TH2



	} // subjet

	if(dRjj<0.3){
   
	  h_sigCA8CSV->Fill(CA8jetCSV[i]);
	  h_sigXMCSV->Fill(XMass, CA8jetCSV[i]); //TH2

	} // fatjet
      }
      

    } // jet loop                                                                    
  } //entries 
  
  

  //save output
  TFile* outFile = new TFile(outputFile.data(),"recreate");

  h_sbXMass->Write();
  h_sigXMass->Write();
  h_sbCA8CSV->Write();
  h_sigCA8CSV->Write();
  h_sbSubCSV->Write();
  h_sigSubCSV->Write();

  h_sigXMCSV->Write();
  h_sbXMCSV->Write();
  h_sigXMsCSV->Write();
  h_sbXMsCSV->Write();


  outFile->Close();


}
