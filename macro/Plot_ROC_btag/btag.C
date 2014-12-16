//root -q -b -l btag.C++\(masspoint\,\"inputFile\"\,\"outputFile\"\)

#include <map>
#include <vector>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <TH1F.h>
#include <TH2F.h>
#include <TRandom.h>
#include <TLorentzVector.h>
#include <TFile.h>
#include "/home/mattwu/CMS_Corp/XtoZh/macro/untuplizer.h"
#include "/home/mattwu/CMS_Corp/XtoZh/macro/passElectronID.h"
#include "/home/mattwu/CMS_Corp/XtoZh/macro/passMuonID.h"
#include "/home/mattwu/CMS_Corp/XtoZh/macro/JetSelections_v4.h"


using namespace std;
void btag(float masspoint, std::string inputFile, std::string outputFile){


  //get TTree from file ...
  TreeReader data(inputFile.data());


  //histogram anoucement
  TH1F* h_CA8jetCSV   = new TH1F("h_CA8jetCSV","",20,0,1);
  TH2F* h_CA8subjetCSV = new TH2F("h_CA8subjetCSV","",20,0,1,20,0,1);

  TH1F* h_COMjetCSV = new TH1F("h_COMjetCSV","",20,0,1);
  TH1F* h_SubjetCSV = new TH1F("h_SubjetCSV","",20,0,1);

  TH1F* h_Tau21         = new TH1F("h_Tau21","",20,0,1);


  h_CA8jetCSV->Sumw2();
  h_CA8subjetCSV->Sumw2();
  h_COMjetCSV->Sumw2();
  h_SubjetCSV->Sumw2();
  h_Tau21->Sumw2();

  

  //Event loop
  for(long jEntry=0; jEntry<data.GetEntriesFast() ;jEntry++){

    data.GetEntry(jEntry);


    Int_t    CA8nJet     = data.GetInt("CA8nJet");
    Float_t* CA8jetPt    = data.GetPtrFloat("CA8jetPt");
    Float_t* CA8jetEta   = data.GetPtrFloat("CA8jetEta");
    Float_t* CA8jetPhi   = data.GetPtrFloat("CA8jetPhi");
    Float_t* CA8jetM     = data.GetPtrFloat("CA8jetMass");
    Int_t*   CA8jetID    = data.GetPtrInt("CA8jetPassID");
    Float_t* CA8jetTau1  = data.GetPtrFloat("CA8jetTau1");
    Float_t* CA8jetTau2  = data.GetPtrFloat("CA8jetTau2");
    Float_t* CA8jetPrunedM = data.GetPtrFloat("CA8jetPrunedMass");


    // b-taging variables
    Float_t* CA8jetCSV   = data.GetPtrFloat("CA8jetCSV");

    // subjet b-tagging
    Int_t*   nSubjet = data.GetPtrInt("CA8nSubPrunedJet");
    vector<Float_t>* SubjetCSV = data.GetPtrVectorFloat("CA8subjetPrunedCSV");
    vector<Float_t>* SubjetPt  = data.GetPtrVectorFloat("CA8subjetPrunedPt");
    vector<Float_t>* SubjetEta = data.GetPtrVectorFloat("CA8subjetPrunedEta");
    vector<Float_t>* SubjetPhi = data.GetPtrVectorFloat("CA8subjetPrunedPhi");
    vector<Float_t>* SubjetM   = data.GetPtrVectorFloat("CA8subjetPrunedMass");


    Int_t    nEle        = data.GetInt("nEle");
    Float_t* elePt       = data.GetPtrFloat("elePt");
    Float_t* eleEta      = data.GetPtrFloat("eleEta");
    Float_t* elePhi      = data.GetPtrFloat("elePhi");
    Float_t* eleM        = data.GetPtrFloat("eleM");
   
    Int_t    nMu         = data.GetInt("nMu");
    Float_t* muPt        = data.GetPtrFloat("muPt");
    Float_t* muEta       = data.GetPtrFloat("muEta");
    Float_t* muPhi       = data.GetPtrFloat("muPhi");
    Float_t* muM         = data.GetPtrFloat("muM");
   


    // get lep and jet index from header file
    Int_t leadjet;
    PassJet(data, leadjet);
    Int_t leadEle, secEle;
    passElectronID(data, &leadEle, &secEle);
    Int_t leadMu, secMu;
    passMuonID(data, &leadMu, &secMu);


    // determine which channel
    bool El=false;
    bool Mu=false;
    if(nEle>0 && nMu==0) El=true;
    if(nEle==0 && nMu>0) Mu=true;
    if(nEle>0 && nMu>0 && elePt[leadEle]>muPt[leadMu]) El=true;
    if(nEle>0 && nMu>0 && elePt[leadEle]<muPt[leadMu]) Mu=true;


    // pass lepton ID
    if(El==true && !passElectronID(data, &leadEle, &secEle)) continue;
    if(Mu==true && !passMuonID(data, &leadMu, &secMu)) continue;



    // Reco mLL
    TLorentzVector l1(0,0,0,0);
    TLorentzVector l2(0,0,0,0);
    TLorentzVector recoZ(0,0,0,0);
    
    if(El==true && nEle<2) continue;
    if(Mu==true && nMu<2) continue;
    
    if(El==true){
      l1.SetPtEtaPhiM(elePt[leadEle],eleEta[leadEle],elePhi[leadEle],eleM[leadEle]);
      l2.SetPtEtaPhiM(elePt[secEle],eleEta[secEle],elePhi[secEle],eleM[secEle]);
    }

    if(Mu==true){
      l1.SetPtEtaPhiM(muPt[leadMu],muEta[leadMu],muPhi[leadMu],muM[leadMu]);
      l2.SetPtEtaPhiM(muPt[secMu],muEta[secMu],muPhi[secMu],muM[secMu]);
    }

    recoZ=(l1+l2);
    float zpt=recoZ.Pt();
    float zmass=recoZ.M();

    if(zpt<80) continue;
    if(zmass<70 || zmass>110) continue;

    
    // Reco Xmass
    TLorentzVector recoH(0,0,0,0);
    TLorentzVector recoX(0,0,0,0);
    
    float upper_limit=masspoint*1.15;
    float lower_limit=masspoint*0.85;

    if(!PassJet(data, leadjet)) continue;
    if(leadjet<0) continue;



    
    recoH.SetPtEtaPhiM(CA8jetPt[leadjet],CA8jetEta[leadjet],CA8jetPhi[leadjet],CA8jetM[leadjet]);
    recoX = recoZ+recoH;
    float xmass=recoX.M();
    
    if(xmass>upper_limit || xmass<lower_limit)continue;


    // Tau21
    float tau21=CA8jetTau2[leadjet]/CA8jetTau1[leadjet];
    h_Tau21->Fill(tau21);



    // fatjet CSV
    h_CA8jetCSV->Fill(CA8jetCSV[leadjet]);
    

    
    // subjet CSV 
    if(nSubjet[leadjet]>=2){
      
      TLorentzVector subjet1(0,0,0,0);
      TLorentzVector subjet2(0,0,0,0);
      
      subjet1.SetPtEtaPhiM(SubjetPt[leadjet][0],SubjetEta[leadjet][0],SubjetPhi[leadjet][0],SubjetM[leadjet][0]);
      subjet2.SetPtEtaPhiM(SubjetPt[leadjet][1],SubjetEta[leadjet][1],SubjetPhi[leadjet][1],SubjetM[leadjet][1]);
      
      Float_t dRjj=subjet1.DeltaR(subjet2);
      
      if(dRjj>0.3){

	h_CA8subjetCSV->Fill(SubjetCSV[leadjet][0],SubjetCSV[leadjet][1]);
	h_SubjetCSV->Fill(SubjetCSV[leadjet][1]);
	h_SubjetCSV->Fill(SubjetCSV[leadjet][0]);


      } // if


      else{
	
	h_COMjetCSV->Fill(CA8jetCSV[leadjet]);
	
      }


    } // nSubjet
    

    else{
      
      h_COMjetCSV->Fill(CA8jetCSV[leadjet]);
      
    }
    



  } //entries 
  
  


  //save output
  TFile* outFile = new TFile(outputFile.data(),"recreate");

  h_CA8jetCSV->Write();
  h_CA8subjetCSV->Write();
  h_SubjetCSV->Write();
  h_COMjetCSV->Write();
  h_Tau21->Write();

  outFile->Close();


}
