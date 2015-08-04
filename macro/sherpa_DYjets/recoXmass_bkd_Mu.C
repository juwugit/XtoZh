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
#include "/home/juwu/XtoZh/macro/passJetID.h"

std::string unctext = "/home/juwu/XtoZh/macro/START53_V23_Uncertainty_AK7PFchs.txt";


// (integrated luminosity) = (number of events)/(cross-section)   
// (data lumi)/(MC lumi) = scale     

const float scale1=(19712.225)/(11764538/63.5); //DY70To100    
const float scale2=(19712.225)/(12511326/39.4); //DY100                


using namespace std;
void recoXmass_bkd_Mu(Int_t scaleMode=0){


  // get TTree from file ...
  TreeReader data1("../delpanjTuple/delpanj_v4_DYJetsToLL_PtZ-70To100.root");
  TreeReader data2("../delpanjTuple/delpanj_v4_DYJetsToLL_PtZ-100.root");


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


  corrJetV corrJet(unctext);

  int counter=0;

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

    Int_t    nEle        = data1.GetInt("nMu");
    Float_t* elePt       = data1.GetPtrFloat("muPt");
    Float_t* eleEta      = data1.GetPtrFloat("muEta");
    Float_t* elePhi      = data1.GetPtrFloat("muPhi");
    Float_t* eleM        = data1.GetPtrFloat("muM");   


    Int_t leadEle, secEle;
    passMuonID(data1, &leadEle, &secEle);


    if(!passMuonID(data1, &leadEle, &secEle)) continue;
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
    Float_t prunedmass=CA8jetPrunedM[leadjet];

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
      if(prunedmass>70 && prunedmass<110){

	if(dRjj>0.3){

          if(SubjetCSV[i][0]>0   && SubjetCSV[i][0]<0.2) h_sbXMass[0]->Fill(XMass, scale1);
          if(SubjetCSV[i][0]>0.2 && SubjetCSV[i][0]<0.4) h_sbXMass[1]->Fill(XMass, scale1);
          if(SubjetCSV[i][0]>0.4 && SubjetCSV[i][0]<0.6) h_sbXMass[2]->Fill(XMass, scale1);
          if(SubjetCSV[i][0]>0.6 && SubjetCSV[i][0]<0.8) h_sbXMass[3]->Fill(XMass, scale1);
          if(SubjetCSV[i][0]>0.8 && SubjetCSV[i][0]<1.0) h_sbXMass[4]->Fill(XMass, scale1);
	  
          if(SubjetCSV[i][1]>0   && SubjetCSV[i][1]<0.2) h_sbXMass[0]->Fill(XMass, scale1);
          if(SubjetCSV[i][1]>0.2 && SubjetCSV[i][1]<0.4) h_sbXMass[1]->Fill(XMass, scale1);
          if(SubjetCSV[i][1]>0.4 && SubjetCSV[i][1]<0.6) h_sbXMass[2]->Fill(XMass, scale1);
          if(SubjetCSV[i][1]>0.6 && SubjetCSV[i][1]<0.8) h_sbXMass[3]->Fill(XMass, scale1);
          if(SubjetCSV[i][1]>0.8 && SubjetCSV[i][1]<1.0) h_sbXMass[4]->Fill(XMass, scale1);

	}
	
	if(dRjj<0.3){
	  
          if(CA8jetCSV[i]>0   && CA8jetCSV[i]<0.2) h_sbXMassCA8jet[0]->Fill(XMass, scale1);
	  if(CA8jetCSV[i]>0.2 && CA8jetCSV[i]<0.4) h_sbXMassCA8jet[1]->Fill(XMass, scale1);
	  if(CA8jetCSV[i]>0.4 && CA8jetCSV[i]<0.6) h_sbXMassCA8jet[2]->Fill(XMass, scale1);
	  if(CA8jetCSV[i]>0.6 && CA8jetCSV[i]<0.8) h_sbXMassCA8jet[3]->Fill(XMass, scale1);
	  if(CA8jetCSV[i]>0.8 && CA8jetCSV[i]<1.0) h_sbXMassCA8jet[4]->Fill(XMass, scale1);

	}
      }

      // signal region                                           
      if(prunedmass>110 && prunedmass<140){

        if(dRjj>0.3){

          if(SubjetCSV[i][0]>0   && SubjetCSV[i][0]<0.2) h_sigXMass[0]->Fill(XMass, scale1);
          if(SubjetCSV[i][0]>0.2 && SubjetCSV[i][0]<0.4) h_sigXMass[1]->Fill(XMass, scale1);
          if(SubjetCSV[i][0]>0.4 && SubjetCSV[i][0]<0.6) h_sigXMass[2]->Fill(XMass, scale1);
          if(SubjetCSV[i][0]>0.6 && SubjetCSV[i][0]<0.8) h_sigXMass[3]->Fill(XMass, scale1);
          if(SubjetCSV[i][0]>0.8 && SubjetCSV[i][0]<1.0) h_sigXMass[4]->Fill(XMass, scale1);
	  
          if(SubjetCSV[i][1]>0   && SubjetCSV[i][1]<0.2) h_sigXMass[0]->Fill(XMass, scale1);
          if(SubjetCSV[i][1]>0.2 && SubjetCSV[i][1]<0.4) h_sigXMass[1]->Fill(XMass, scale1);
          if(SubjetCSV[i][1]>0.4 && SubjetCSV[i][1]<0.6) h_sigXMass[2]->Fill(XMass, scale1);
          if(SubjetCSV[i][1]>0.6 && SubjetCSV[i][1]<0.8) h_sigXMass[3]->Fill(XMass, scale1);
          if(SubjetCSV[i][1]>0.8 && SubjetCSV[i][1]<1.0) h_sigXMass[4]->Fill(XMass, scale1);

	}

	if(dRjj<0.3){

	  if(CA8jetCSV[i]>0   && CA8jetCSV[i]<0.2) h_sigXMassCA8jet[0]->Fill(XMass, scale1);
	  if(CA8jetCSV[i]>0.2 && CA8jetCSV[i]<0.4) h_sigXMassCA8jet[1]->Fill(XMass, scale1);
	  if(CA8jetCSV[i]>0.4 && CA8jetCSV[i]<0.6) h_sigXMassCA8jet[2]->Fill(XMass, scale1);
	  if(CA8jetCSV[i]>0.6 && CA8jetCSV[i]<0.8) h_sigXMassCA8jet[3]->Fill(XMass, scale1);
	  if(CA8jetCSV[i]>0.8 && CA8jetCSV[i]<1.0) h_sigXMassCA8jet[4]->Fill(XMass, scale1);

	}
      }
      
    } // jet loop                                                                    

    counter++;
    cout<<counter<<endl;

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

    Int_t    nEle        = data2.GetInt("nMu");
    Float_t* elePt       = data2.GetPtrFloat("muPt");
    Float_t* eleEta      = data2.GetPtrFloat("muEta");
    Float_t* elePhi      = data2.GetPtrFloat("muPhi");
    Float_t* eleM        = data2.GetPtrFloat("muM");   


    Int_t leadEle, secEle;
    passMuonID(data2, &leadEle, &secEle);


    if(!passMuonID(data2, &leadEle, &secEle)) continue;
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

    if(!passJetID(data2,corrJet, csvlMode, scaleMode, &leadjet, &tempVector)) continue;

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


    for(int i=0; i<CA8nJet; i++){


      //check subjet deltaR
      if(nSubjet[i]>=2){

	subjet1.SetPtEtaPhiE(SubjetPt[i][0],SubjetEta[i][0],SubjetPhi[i][0],SubjetEn[i][0]);
	subjet2.SetPtEtaPhiE(SubjetPt[i][1],SubjetEta[i][1],SubjetPhi[i][1],SubjetEn[i][1]);
	dRjj=subjet1.DeltaR(subjet2);

      }


      // sideband region
      if(prunedmass>70 && prunedmass<110){

	if(dRjj>0.3){

          if(SubjetCSV[i][0]>0   && SubjetCSV[i][0]<0.2) h_sbXMass[0]->Fill(XMass, scale2);
          if(SubjetCSV[i][0]>0.2 && SubjetCSV[i][0]<0.4) h_sbXMass[1]->Fill(XMass, scale2);
          if(SubjetCSV[i][0]>0.4 && SubjetCSV[i][0]<0.6) h_sbXMass[2]->Fill(XMass, scale2);
          if(SubjetCSV[i][0]>0.6 && SubjetCSV[i][0]<0.8) h_sbXMass[3]->Fill(XMass, scale2);
          if(SubjetCSV[i][0]>0.8 && SubjetCSV[i][0]<1.0) h_sbXMass[4]->Fill(XMass, scale2);
	  
          if(SubjetCSV[i][1]>0   && SubjetCSV[i][1]<0.2) h_sbXMass[0]->Fill(XMass, scale2);
          if(SubjetCSV[i][1]>0.2 && SubjetCSV[i][1]<0.4) h_sbXMass[1]->Fill(XMass, scale2);
          if(SubjetCSV[i][1]>0.4 && SubjetCSV[i][1]<0.6) h_sbXMass[2]->Fill(XMass, scale2);
          if(SubjetCSV[i][1]>0.6 && SubjetCSV[i][1]<0.8) h_sbXMass[3]->Fill(XMass, scale2);
          if(SubjetCSV[i][1]>0.8 && SubjetCSV[i][1]<1.0) h_sbXMass[4]->Fill(XMass, scale2);

	}

	if(dRjj<0.3){
	
	  if(CA8jetCSV[i]>0   && CA8jetCSV[i]<0.2) h_sbXMassCA8jet[0]->Fill(XMass, scale2);
	  if(CA8jetCSV[i]>0.2 && CA8jetCSV[i]<0.4) h_sbXMassCA8jet[1]->Fill(XMass, scale2);
	  if(CA8jetCSV[i]>0.4 && CA8jetCSV[i]<0.6) h_sbXMassCA8jet[2]->Fill(XMass, scale2);
	  if(CA8jetCSV[i]>0.6 && CA8jetCSV[i]<0.8) h_sbXMassCA8jet[3]->Fill(XMass, scale2);
	  if(CA8jetCSV[i]>0.8 && CA8jetCSV[i]<1.0) h_sbXMassCA8jet[4]->Fill(XMass, scale2);	  
	
	}
      }

      // signal region                                           
      if(prunedmass>110 && prunedmass<140){

        if(dRjj>0.3){

          if(SubjetCSV[i][0]>0   && SubjetCSV[i][0]<0.2) h_sigXMass[0]->Fill(XMass, scale2);
          if(SubjetCSV[i][0]>0.2 && SubjetCSV[i][0]<0.4) h_sigXMass[1]->Fill(XMass, scale2);
          if(SubjetCSV[i][0]>0.4 && SubjetCSV[i][0]<0.6) h_sigXMass[2]->Fill(XMass, scale2);
          if(SubjetCSV[i][0]>0.6 && SubjetCSV[i][0]<0.8) h_sigXMass[3]->Fill(XMass, scale2);
          if(SubjetCSV[i][0]>0.8 && SubjetCSV[i][0]<1.0) h_sigXMass[4]->Fill(XMass, scale2);
	  
          if(SubjetCSV[i][1]>0   && SubjetCSV[i][1]<0.2) h_sigXMass[0]->Fill(XMass, scale2);
          if(SubjetCSV[i][1]>0.2 && SubjetCSV[i][1]<0.4) h_sigXMass[1]->Fill(XMass, scale2);
          if(SubjetCSV[i][1]>0.4 && SubjetCSV[i][1]<0.6) h_sigXMass[2]->Fill(XMass, scale2);
          if(SubjetCSV[i][1]>0.6 && SubjetCSV[i][1]<0.8) h_sigXMass[3]->Fill(XMass, scale2);
          if(SubjetCSV[i][1]>0.8 && SubjetCSV[i][1]<1.0) h_sigXMass[4]->Fill(XMass, scale2);

	}

	if(dRjj<0.3){

	  if(CA8jetCSV[i]>0   && CA8jetCSV[i]<0.2) h_sigXMassCA8jet[0]->Fill(XMass, scale2);
	  if(CA8jetCSV[i]>0.2 && CA8jetCSV[i]<0.4) h_sigXMassCA8jet[1]->Fill(XMass, scale2);
	  if(CA8jetCSV[i]>0.4 && CA8jetCSV[i]<0.6) h_sigXMassCA8jet[2]->Fill(XMass, scale2);
	  if(CA8jetCSV[i]>0.6 && CA8jetCSV[i]<0.8) h_sigXMassCA8jet[3]->Fill(XMass, scale2);
	  if(CA8jetCSV[i]>0.8 && CA8jetCSV[i]<1.0) h_sigXMassCA8jet[4]->Fill(XMass, scale2);	

	}
      }
      
    } // jet loop                                                                    



    counter++;
    cout<<counter<<endl;
    
    

  } //entries data2

  
  //save output
  TFile* outFile = new TFile("MC_bkd_Mu.root","recreate");

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
