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
  const Float_t varBins[] = {680,720,760,800,840,920,1000,1100,1250,1400,1600,1800,2000,2400};
  Int_t nvarBins = sizeof(varBins)/sizeof(varBins[0])-1;

  TH1F* h_sbXMass[5];
  TH1F* h_sigXMass[5];
  TH1F* h_sbXMassCA8jet[5];
  TH1F* h_sigXMassCA8jet[5];

  for(int i=0; i<5; i++){

    h_sbXMass[i] = new TH1F(Form("h_sbXMass%d",i),"",nvarBins, varBins);
    h_sigXMass[i] = new TH1F(Form("h_sigXMass%d",i),"",nvarBins, varBins);
    h_sbXMassCA8jet[i] = new TH1F(Form("h_sbXMassCA8jet%d",i),"",nvarBins, varBins);
    h_sigXMassCA8jet[i] = new TH1F(Form("h_sigXMassCA8jet%d",i),"",nvarBins, varBins);

    h_sbXMass[i]->Sumw2();
    h_sigXMass[i]->Sumw2();
    h_sbXMassCA8jet[i]->Sumw2();
    h_sigXMassCA8jet[i]->Sumw2();    

  }

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
    Float_t prunedmass=CA8jetPrunedM[leadjet];

    if(CA8nJet>0 && leadjet>=0){
      
      //recoH.SetPtEtaPhiE(CA8jetPt[leadjet],CA8jetEta[leadjet],CA8jetPhi[leadjet],CA8jetEn[leadjet]);
      recoX = recoZ+recoH;
      XMass=recoX.M();

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
      if(prunedmass>70 && prunedmass<110){

	if(dRjj>0.3){

	  if(SubjetCSV[i]>0   && SubjetCSV[i]<0.2) h_sbXMass[0]->Fill(XMass, mcWeight);
	  if(SubjetCSV[i]>0.2 && SubjetCSV[i]<0.4) h_sbXMass[1]->Fill(XMass, mcWeight);
	  if(SubjetCSV[i]>0.4 && SubjetCSV[i]<0.6) h_sbXMass[2]->Fill(XMass, mcWeight);
	  if(SubjetCSV[i]>0.6 && SubjetCSV[i]<0.8) h_sbXMass[3]->Fill(XMass, mcWeight);
	  if(SubjetCSV[i]>0.8 && SubjetCSV[i]<1.0) h_sbXMass[4]->Fill(XMass, mcWeight);

	  if(SubjetCSV[i+1]>0   && SubjetCSV[i+1]<0.2) h_sbXMass[0]->Fill(XMass, mcWeight);
	  if(SubjetCSV[i+1]>0.2 && SubjetCSV[i+1]<0.4) h_sbXMass[1]->Fill(XMass, mcWeight);
	  if(SubjetCSV[i+1]>0.4 && SubjetCSV[i+1]<0.6) h_sbXMass[2]->Fill(XMass, mcWeight);
	  if(SubjetCSV[i+1]>0.6 && SubjetCSV[i+1]<0.8) h_sbXMass[3]->Fill(XMass, mcWeight);
	  if(SubjetCSV[i+1]>0.8 && SubjetCSV[i+1]<1.0) h_sbXMass[4]->Fill(XMass, mcWeight);
	    
	} // if

	if(dRjj<0.3 && CA8jetCSV[i]>0){

	  if(CA8jetCSV[i]>0   && CA8jetCSV[i]<0.2) h_sbXMassCA8jet[0]->Fill(XMass, mcWeight);
	  if(CA8jetCSV[i]>0.2 && CA8jetCSV[i]<0.4) h_sbXMassCA8jet[1]->Fill(XMass, mcWeight);
	  if(CA8jetCSV[i]>0.4 && CA8jetCSV[i]<0.6) h_sbXMassCA8jet[2]->Fill(XMass, mcWeight);
	  if(CA8jetCSV[i]>0.6 && CA8jetCSV[i]<0.8) h_sbXMassCA8jet[3]->Fill(XMass, mcWeight);
	  if(CA8jetCSV[i]>0.8 && CA8jetCSV[i]<1.0) h_sbXMassCA8jet[4]->Fill(XMass, mcWeight);

	} // if
      }

      // signal region                                           
      if(prunedmass>110 && prunedmass<140){
	
        if(dRjj>0.3){

	  if(SubjetCSV[i]>0   && SubjetCSV[i]<0.2) h_sigXMass[0]->Fill(XMass, mcWeight);
	  if(SubjetCSV[i]>0.2 && SubjetCSV[i]<0.4) h_sigXMass[1]->Fill(XMass, mcWeight);
	  if(SubjetCSV[i]>0.4 && SubjetCSV[i]<0.6) h_sigXMass[2]->Fill(XMass, mcWeight);
	  if(SubjetCSV[i]>0.6 && SubjetCSV[i]<0.8) h_sigXMass[3]->Fill(XMass, mcWeight);
	  if(SubjetCSV[i]>0.8 && SubjetCSV[i]<1.0) h_sigXMass[4]->Fill(XMass, mcWeight);

	  if(SubjetCSV[i+1]>0   && SubjetCSV[i+1]<0.2) h_sigXMass[0]->Fill(XMass, mcWeight);
	  if(SubjetCSV[i+1]>0.2 && SubjetCSV[i+1]<0.4) h_sigXMass[1]->Fill(XMass, mcWeight);
	  if(SubjetCSV[i+1]>0.4 && SubjetCSV[i+1]<0.6) h_sigXMass[2]->Fill(XMass, mcWeight);
	  if(SubjetCSV[i+1]>0.6 && SubjetCSV[i+1]<0.8) h_sigXMass[3]->Fill(XMass, mcWeight);
	  if(SubjetCSV[i+1]>0.8 && SubjetCSV[i+1]<1.0) h_sigXMass[4]->Fill(XMass, mcWeight);
	  
	}
	
	if(dRjj<0.3 && CA8jetCSV[i]>0){
	  
	  if(CA8jetCSV[i]>0   && CA8jetCSV[i]<0.2) h_sigXMassCA8jet[0]->Fill(XMass, mcWeight);
	  if(CA8jetCSV[i]>0.2 && CA8jetCSV[i]<0.4) h_sigXMassCA8jet[1]->Fill(XMass, mcWeight);
	  if(CA8jetCSV[i]>0.4 && CA8jetCSV[i]<0.6) h_sigXMassCA8jet[2]->Fill(XMass, mcWeight);
	  if(CA8jetCSV[i]>0.6 && CA8jetCSV[i]<0.8) h_sigXMassCA8jet[3]->Fill(XMass, mcWeight);
	  if(CA8jetCSV[i]>0.8 && CA8jetCSV[i]<1.0) h_sigXMassCA8jet[4]->Fill(XMass, mcWeight);
	  
	}// if
      }	
    } // jet loop                                                                    
    
    counter++;
    cout<<counter<<endl;
    
    
  } //entries 
  
  
  
  //save output
  TFile* outFile = new TFile("sherpa_Mu.root","recreate");

  for(int i=0; i<5; i++){

    h_sbXMass[i]->Scale(1/h_sbXMass[i]->Integral());
    h_sigXMass[i]->Scale(1/h_sigXMass[i]->Integral());
    h_sbXMassCA8jet[i]->Scale(1/h_sbXMassCA8jet[i]->Integral());
    h_sigXMassCA8jet[i]->Scale(1/h_sigXMassCA8jet[i]->Integral());

    h_sbXMass[i]->Write();
    h_sigXMass[i]->Write();
    h_sbXMassCA8jet[i]->Write();
    h_sigXMassCA8jet[i]->Write();    

  }

  outFile->Close();


}
