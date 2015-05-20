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
#include "/home/juwu/XtoZh/macro/untuplizer.h"
#include "/home/juwu/XtoZh/macro/passElectronID.h"
#include "/home/juwu/XtoZh/macro/passMuonID.h"
#include "/home/juwu/XtoZh/macro/passJetID_mod.h"


std::string unctext = "/home/juwu/XtoZh/macro/START53_V23_Uncertainty_AK7PFchs.txt";


// (integrated luminosity) = (number of events)/(cross-section)  
// (data lumi)/(MC lumi) = scale

const float scale1=(19671.225)/(11764538/63.5); //DY70To100 
const float scale2=(19671.225)/(12511326/39.4); //DY100                


using namespace std;
void recoXmass_bkd_Mu(Int_t scaleMode, std::string outputFile){


  // get TTree from file ...
  TreeReader data1("../delpanjTuple/delpanj_v4_DYJetsToLL_PtZ-70To100.root");
  TreeReader data2("../delpanjTuple/delpanj_v4_DYJetsToLL_PtZ-100.root");


  // declare histogram
  const Double_t varBins[] = {680,720,760,800,840,920,1000,1100,1250,1400,1600,1800,2000,2400};
  Int_t nvarBins = sizeof(varBins)/sizeof(varBins[0])-1;


  TH2F* h_sigXMCSV = new TH2F("h_sigXMCSV","signal region XMass vs CA8jet CSV",nvarBins,varBins,5,0,1);
  TH2F* h_sbXMCSV = new TH2F("h_sbXMCSV","sideband region XMass vs CA8jet CSV",nvarBins,varBins,5,0,1);

  TH2F* h_sigXMsCSV = new TH2F("h_sigXMsCSV","signal region XMass vs subjet CSV",nvarBins,varBins,5,0,1);
  TH2F* h_sbXMsCSV = new TH2F("h_sbXMsCSV","sideband region XMass vs subjet CSV",nvarBins,varBins,5,0,1);


  h_sigXMCSV->Sumw2();
  h_sbXMCSV->Sumw2();

  h_sigXMsCSV->Sumw2();
  h_sbXMsCSV->Sumw2();

  corrJetV corrJet(unctext);



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

    Int_t    nMu        = data1.GetInt("nMu");
    Float_t* muPt       = data1.GetPtrFloat("muPt");
    Float_t* muEta      = data1.GetPtrFloat("muEta");
    Float_t* muPhi      = data1.GetPtrFloat("muPhi");
    Float_t* muM        = data1.GetPtrFloat("muM");   

    Int_t leadMu, secMu;
    passMuonID(data1, &leadMu, &secMu);


    if(!passMuonID(data1, &leadMu, &secMu)) continue;
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
    Int_t csvlMode = 0;
    TLorentzVector tempVector(0,0,0,0);

    if(!passJetID(data1, corrJet, csvlMode, scaleMode, &leadjet, &tempVector)) continue;

    TLorentzVector recoH = tempVector;
    TLorentzVector recoX(0,0,0,0);
    Float_t XMass=-999;

    if(CA8nJet>0 && leadjet>=0){
      
      //recoH.SetPtEtaPhiE(CA8jetPt[leadjet],CA8jetEta[leadjet],CA8jetPhi[leadjet],CA8jetEn[leadjet]);
      recoX = recoZ+recoH;
      
      XMass=recoX.M();
      
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

	  if(SubjetCSV[i][0]>0) h_sbXMsCSV->Fill(XMass, SubjetCSV[i][0], scale1); //TH2        
	  if(SubjetCSV[i][1]>0) h_sbXMsCSV->Fill(XMass, SubjetCSV[i][1], scale1); //TH2

	} // subjet

	if(dRjj<0.3) h_sbXMCSV->Fill(XMass, CA8jetCSV[i], scale1); //TH2 

      }


      // signal region                                           
      if(CA8jetPrunedM[leadjet]>110 && CA8jetPrunedM[leadjet]<140){

        if(dRjj>0.3){

	  if(SubjetCSV[i][0]>0) h_sigXMsCSV->Fill(XMass, SubjetCSV[i][0], scale1); //TH2 
	  if(SubjetCSV[i][1]>0) h_sigXMsCSV->Fill(XMass, SubjetCSV[i][1], scale1); //TH2 
 
	} // subjet

	if(dRjj<0.3) h_sigXMCSV->Fill(XMass, CA8jetCSV[i], scale1); //TH2 

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

    Int_t    nMu        = data2.GetInt("nMu");
    Float_t* muPt       = data2.GetPtrFloat("muPt");
    Float_t* muEta      = data2.GetPtrFloat("muEta");
    Float_t* muPhi      = data2.GetPtrFloat("muPhi");
    Float_t* muM        = data2.GetPtrFloat("muM");   

    Int_t leadMu, secMu;
    passMuonID(data2, &leadMu, &secMu);


    if(!passMuonID(data2, &leadMu, &secMu)) continue;
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
    Int_t csvlMode = 0;
    TLorentzVector tempVector(0,0,0,0);

    if(!passJetID(data2, corrJet, csvlMode, scaleMode, &leadjet, &tempVector)) continue;

    TLorentzVector recoH = tempVector;
    TLorentzVector recoX(0,0,0,0);
    Float_t XMass=-999;

    if(CA8nJet>0 && leadjet>=0){
      
      //recoH.SetPtEtaPhiE(CA8jetPt[leadjet],CA8jetEta[leadjet],CA8jetPhi[leadjet],CA8jetEn[leadjet]);
      recoX = recoZ+recoH;
      
      XMass=recoX.M();
      
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

	  if(SubjetCSV[i][0]>0) h_sbXMsCSV->Fill(XMass, SubjetCSV[i][0], scale2); //TH2        
	  if(SubjetCSV[i][1]>0) h_sbXMsCSV->Fill(XMass, SubjetCSV[i][1], scale2); //TH2

	} // subjet

	if(dRjj<0.3) h_sbXMCSV->Fill(XMass, CA8jetCSV[i], scale2); //TH2 

      }


      // signal region                                           
      if(CA8jetPrunedM[leadjet]>110 && CA8jetPrunedM[leadjet]<140){

        if(dRjj>0.3){

	  if(SubjetCSV[i][0]>0) h_sigXMsCSV->Fill(XMass, SubjetCSV[i][0], scale2); //TH2 
	  if(SubjetCSV[i][1]>0) h_sigXMsCSV->Fill(XMass, SubjetCSV[i][1], scale2); //TH2 
 
	} // subjet

	if(dRjj<0.3) h_sigXMCSV->Fill(XMass, CA8jetCSV[i], scale2); //TH2 
	  
      }
      
    } // jet loop                                                                    

  } //entries data2

 
  
  //save output
  TFile* outFile = new TFile(outputFile.data(),"recreate");

  h_sigXMCSV->Write();
  h_sbXMCSV->Write();
  
  h_sigXMsCSV->Write();
  h_sbXMsCSV->Write();
  

  outFile->Close();


}
