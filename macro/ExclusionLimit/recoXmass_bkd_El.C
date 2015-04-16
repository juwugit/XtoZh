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
#include "/home/juwu/XtoZh/macro/JetSelections.h"


// (integrated luminosity) = (number of events)/(cross-section)   
// (data lumi)/(MC lumi) = scale     

const float scale1=(19712.225)/(11764538/63.5); //DY70To100    
const float scale2=(19712.225)/(12511326/39.4); //DY100                


using namespace std;
void recoXmass_bkd_El(){


  // get TTree from file ...
  TreeReader data1("../delpanjTuple/delpanj_v4_DYJetsToLL_PtZ-70To100.root");
  TreeReader data2("../delpanjTuple/delpanj_v4_DYJetsToLL_PtZ-100.root");


  // declare histogram
  const Float_t varBins[] = {680,720,760,800,840,920,1000,1100,1250,1400,1600,1800,2000,2400};
  Int_t nvarBins = sizeof(varBins)/sizeof(varBins[0])-1;

  TH1F* h_sbXMass = new TH1F("h_sbXMass","sideband region X mass", nvarBins, varBins);
  TH1F* h_sigXMass = new TH1F("h_sigXMass","signal region X mass", nvarBins, varBins);
  TH1F* h_alphaXMass = new TH1F("h_alphaXMass","alpha ratio of X mass", nvarBins, varBins);

  TH1F* h_sbCA8CSV = new TH1F("h_sbCA8CSV","sideband region CA8jet CSV",20,0,1);
  TH1F* h_sigCA8CSV = new TH1F("h_sigCA8CSV","signal region CA8jet CSV",20,0,1);
  TH1F* h_alphaCA8CSV = new TH1F("h_alphaCA8CSV","alpha ratio of CA8jet CSV",20,0,1);

  TH1F* h_sbSubCSV = new TH1F("h_sbSubCSV","sideband region subjet CSV",20,0,1);
  TH1F* h_sigSubCSV = new TH1F("h_sigSubCSV","signal region subjet CSV",20,0,1);
  TH1F* h_alphaSubCSV = new TH1F("h_alphaSubCSV","alpha ratio of subjet CSV",20,0,1);

  
  h_sbXMass->Sumw2();
  h_sigXMass->Sumw2();
  h_alphaXMass->Sumw2();

  h_sbCA8CSV->Sumw2();
  h_sigCA8CSV->Sumw2();
  h_alphaCA8CSV->Sumw2();

  h_sbSubCSV->Sumw2();
  h_sigSubCSV->Sumw2();
  h_alphaSubCSV->Sumw2();



  //Event loop data1
  for(long jEntry=0; jEntry<data1.GetEntriesFast() ;jEntry++){

    data1.GetEntry(jEntry);


    Int_t    CA8nJet     = data1.GetInt("CA8nJet");
    Float_t* CA8jetPt    = data1.GetPtrFloat("CA8jetPt");
    Float_t* CA8jetEta   = data1.GetPtrFloat("CA8jetEta");
    Float_t* CA8jetPhi   = data1.GetPtrFloat("CA8jetPhi");
    Float_t* CA8jetEn    = data1.GetPtrFloat("CA8jetEn");
    Float_t* CA8jetPrunedM = data1.GetPtrFloat("CA8jetPrunedMass");
    Float_t* CA8jetCSV   = data1.GetPtrFloat("CA8jetCSV");

    Int_t*   nSubjet = data1.GetPtrInt("CA8nSubPrunedJet");
    vector<Float_t>* SubjetCSV = data1.GetPtrVectorFloat("CA8subjetPrunedCSV");
    vector<Float_t>* SubjetPt  = data1.GetPtrVectorFloat("CA8subjetPrunedPt");
    vector<Float_t>* SubjetEta = data1.GetPtrVectorFloat("CA8subjetPrunedEta");
    vector<Float_t>* SubjetPhi = data1.GetPtrVectorFloat("CA8subjetPrunedPhi");
    vector<Float_t>* SubjetEn  = data1.GetPtrVectorFloat("CA8subjetPrunedEn");

    Int_t    nEle        = data1.GetInt("nEle");
    Float_t* elePt       = data1.GetPtrFloat("elePt");
    Float_t* eleEta      = data1.GetPtrFloat("eleEta");
    Float_t* elePhi      = data1.GetPtrFloat("elePhi");
    Float_t* eleM        = data1.GetPtrFloat("eleM");   

    Int_t leadjet;    
    Int_t leadEle, secEle;
    passElectronID(data1, &leadEle, &secEle);


    if(!passElectronID(data1, &leadEle, &secEle)) continue;
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
    PassJet(3, data1, leadjet);
    if(!PassJet(3, data1, leadjet)) continue;

    TLorentzVector recoH(0,0,0,0);
    TLorentzVector recoX(0,0,0,0);
    
    if(CA8nJet>0 && leadjet>=0){
      
      recoH.SetPtEtaPhiE(CA8jetPt[leadjet],CA8jetEta[leadjet],CA8jetPhi[leadjet],CA8jetEn[leadjet]);
      recoX = recoZ+recoH;
      
      Float_t XMass=recoX.M();
      Float_t prunedmass=CA8jetPrunedM[leadjet];
      
      if(prunedmass>70 && prunedmass<110) h_sbXMass->Fill(XMass, scale1);
      if(prunedmass>110 && prunedmass<140) h_sigXMass->Fill(XMass, scale1);
      
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


      // sideband region
      if(CA8jetPrunedM[leadjet]>70 && CA8jetPrunedM[leadjet]<110){

	if(dRjj>0.3){

          if(SubjetCSV[i][0]>0) h_sbSubCSV->Fill(SubjetCSV[i][0], scale1);
	  if(SubjetCSV[i][1]>0) h_sbSubCSV->Fill(SubjetCSV[i][1], scale1);

	}

	if(dRjj<0.3) h_sbCA8CSV->Fill(CA8jetCSV[i], scale1);
		
      }

      // signal region                                           
      if(CA8jetPrunedM[leadjet]>110 && CA8jetPrunedM[leadjet]<140){

        if(dRjj>0.3){

	  if(SubjetCSV[i][0]>0) h_sigSubCSV->Fill(SubjetCSV[i][0], scale1);
	  if(SubjetCSV[i][1]>0) h_sigSubCSV->Fill(SubjetCSV[i][1], scale1);

	}

	if(dRjj<0.3) h_sigCA8CSV->Fill(CA8jetCSV[i], scale1);
	
      }
      
    } // jet loop                                                                    

  } //entries data1
  


  //Event loop data2
  for(long jEntry=0; jEntry<data2.GetEntriesFast() ;jEntry++){

    data2.GetEntry(jEntry);


    Int_t    CA8nJet     = data2.GetInt("CA8nJet");
    Float_t* CA8jetPt    = data2.GetPtrFloat("CA8jetPt");
    Float_t* CA8jetEta   = data2.GetPtrFloat("CA8jetEta");
    Float_t* CA8jetPhi   = data2.GetPtrFloat("CA8jetPhi");
    Float_t* CA8jetEn    = data2.GetPtrFloat("CA8jetEn");
    Float_t* CA8jetPrunedM = data2.GetPtrFloat("CA8jetPrunedMass");
    Float_t* CA8jetCSV   = data2.GetPtrFloat("CA8jetCSV");

    Int_t*   nSubjet = data2.GetPtrInt("CA8nSubPrunedJet");
    vector<Float_t>* SubjetCSV = data2.GetPtrVectorFloat("CA8subjetPrunedCSV");
    vector<Float_t>* SubjetPt  = data2.GetPtrVectorFloat("CA8subjetPrunedPt");
    vector<Float_t>* SubjetEta = data2.GetPtrVectorFloat("CA8subjetPrunedEta");
    vector<Float_t>* SubjetPhi = data2.GetPtrVectorFloat("CA8subjetPrunedPhi");
    vector<Float_t>* SubjetEn  = data2.GetPtrVectorFloat("CA8subjetPrunedEn");

    Int_t    nEle        = data2.GetInt("nEle");
    Float_t* elePt       = data2.GetPtrFloat("elePt");
    Float_t* eleEta      = data2.GetPtrFloat("eleEta");
    Float_t* elePhi      = data2.GetPtrFloat("elePhi");
    Float_t* eleM        = data2.GetPtrFloat("eleM");   

    Int_t leadjet;    
    Int_t leadEle, secEle;
    passElectronID(data2, &leadEle, &secEle);


    if(!passElectronID(data2, &leadEle, &secEle)) continue;
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
    PassJet(3, data2, leadjet);
    if(!PassJet(3, data2, leadjet)) continue;

    TLorentzVector recoH(0,0,0,0);
    TLorentzVector recoX(0,0,0,0);
    
    if(CA8nJet>0 && leadjet>=0){
      
      recoH.SetPtEtaPhiE(CA8jetPt[leadjet],CA8jetEta[leadjet],CA8jetPhi[leadjet],CA8jetEn[leadjet]);
      recoX = recoZ+recoH;
      
      Float_t XMass=recoX.M();
      Float_t prunedmass=CA8jetPrunedM[leadjet];
      
      if(prunedmass>70 && prunedmass<110) h_sbXMass->Fill(XMass, scale2);
      if(prunedmass>110 && prunedmass<140) h_sigXMass->Fill(XMass, scale2);
      
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


      // sideband region
      if(CA8jetPrunedM[leadjet]>70 && CA8jetPrunedM[leadjet]<110){

	if(dRjj>0.3){

	  if(SubjetCSV[i][0]>0) h_sbSubCSV->Fill(SubjetCSV[i][0], scale2);
	  if(SubjetCSV[i][1]>0) h_sbSubCSV->Fill(SubjetCSV[i][1], scale2);

	}

	if(dRjj<0.3) h_sbCA8CSV->Fill(CA8jetCSV[i], scale2);
		
      }

      // signal region                                           
      if(CA8jetPrunedM[leadjet]>110 && CA8jetPrunedM[leadjet]<140){

        if(dRjj>0.3){

	  if(SubjetCSV[i][0]>0) h_sigSubCSV->Fill(SubjetCSV[i][0], scale2);
	  if(SubjetCSV[i][1]>0) h_sigSubCSV->Fill(SubjetCSV[i][1], scale2);          

	}

	if(dRjj<0.3) h_sigCA8CSV->Fill(CA8jetCSV[i], scale2);
	
      }
      
    } // jet loop                                                                    




    

  } //entries data2

  
  h_alphaXMass->Divide(h_sigXMass, h_sbXMass);
  h_alphaCA8CSV->Divide(h_sigCA8CSV, h_sbCA8CSV);
  h_alphaSubCSV->Divide(h_sigSubCSV, h_sbSubCSV);

  

  //save output
  TFile* outFile = new TFile("MC_bkd_El.root","recreate");

  h_sbXMass->Write();
  h_sigXMass->Write();
  h_alphaXMass->Write();

  h_sbCA8CSV->Write();
  h_sigCA8CSV->Write();
  h_alphaCA8CSV->Write();

  h_sbSubCSV->Write();
  h_sigSubCSV->Write();
  h_alphaSubCSV->Write();


  outFile->Close();


}
