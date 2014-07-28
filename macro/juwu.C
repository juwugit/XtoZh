//root -q -b -l juwu.C++\(\"inputFile\"\,\"outputFile\"\)


#include <vector>
#include <iostream>
#include <algorithm>
#include <TH1D.h>
#include <TRandom.h>
#include <TLorentzVector.h>
#include <TFile.h>
#include "macro/untuplizer.h"


using namespace std;
void juwu(std::string inputFile, std::string outputFile){


  //get TTree from file ...
  TreeReader data(inputFile.data());


  //histogram anoucement
  TH1F* h_genXPt        = new TH1F("h_genXPt","",30,0,600);
  TH1F* h_genXY         = new TH1F("h_genXY","",30,-3,3); 
  TH1F* h_genHPt        = new TH1F("h_genHPt","",60,0,1200); 
  TH1F* h_genHEta       = new TH1F("h_genHEta","",30,-3,3);
  TH1F* h_genHqqDeltaR  = new TH1F("h_genHqqDeltaR","",20,0,1);
  TH1F* h_genZPt        = new TH1F("h_genZPt","",60,0,1200);
  TH1F* h_genZEta       = new TH1F("h_genZEta","",30,-3,3);
  TH1F* h_genZllDeltaR  = new TH1F("h_genZllDeltaR","",20,0,1);

  TH1F* h_CA8jetPt      = new TH1F("h_CA8jetPt","",100,0,1200);
  TH1F* h_CA8jetPt_ID   = (TH1F*)h_CA8jetPt->Clone("h_CA8jetPt_ID");
  TH1F* h_CA8jetEta     = new TH1F("h_CA8jetEta","",10,-3,3);
  TH1F* h_CA8jetEta_ID  = (TH1F*)h_CA8jetEta->Clone("h_CA8jetEta_ID");
  TH1F* h_CA8jetTau21   = new TH1F("h_CA8jetTau21","",20,0,1);

  TH1F* h_elePt         = new TH1F("h_elePt","",100,0,1200);
  TH1F* h_eleSecPt      = (TH1F*)h_elePt->Clone("h_eleSecPt");
  TH1F* h_elePt_ID      = (TH1F*)h_elePt->Clone("h_elePt_ID");
  TH1F* h_eleSecPt_ID   = (TH1F*)h_elePt->Clone("h_eleSecPt_ID");
  TH1F* h_eleEta        = new TH1F("h_eleEta","",10,-3,3);
  TH1F* h_eleEta_ID     = (TH1F*)h_eleEta->Clone("h_eleEta_ID");

  TH1F* h_muPt          = new TH1F("h_muPt","",100,0,1200);
  TH1F* h_muSecPt       = (TH1F*)h_muPt->Clone("h_muSecPt");
  TH1F* h_muPt_track    = (TH1F*)h_muPt->Clone("h_muPt_track");
  TH1F* h_muSecPt_track = (TH1F*)h_muPt->Clone("h_muSecPt_track");
  TH1F* h_muPt_globe    = (TH1F*)h_muPt->Clone("h_muPt_globe");
  TH1F* h_muSecPt_globe = (TH1F*)h_muPt->Clone("h_muSecPt_globe");
  TH1F* h_muEta         = new TH1F("h_muEta","",10,-3,3);
  TH1F* h_muEta_track   = (TH1F*)h_muEta->Clone("h_muEta_track");
  TH1F* h_muEta_globe   = (TH1F*)h_muEta->Clone("h_muEta_globe");



  //Event loop
  for(long jEntry=0; jEntry<data.GetEntriesFast() ;jEntry++){

    data.GetEntry(jEntry);

    Int_t    nGenPar     = data.GetInt("nGenPar");
    Float_t* genParE     = data.GetPtrFloat("genParE");
    Float_t* genParPt    = data.GetPtrFloat("genParPt");
    Float_t* genParEta   = data.GetPtrFloat("genParEta");
    Float_t* genParPhi   = data.GetPtrFloat("genParPhi");
    Float_t* genParM     = data.GetPtrFloat("genParM");
    Int_t*   genParQ     = data.GetPtrInt("genParQ");
    Int_t*   genParId    = data.GetPtrInt("genParId");
    Int_t*   genParSt    = data.GetPtrInt("genParSt");
    Int_t*   genMomParId = data.GetPtrInt("genMomParId");
    Int_t*   genNMo      = data.GetPtrInt("genNMo");
    Int_t*   genNDa      = data.GetPtrInt("genNDa");
    Int_t*   genMo1      = data.GetPtrInt("genMo1");
    Int_t*   genMo2      = data.GetPtrInt("genMo2");
    Int_t*   genDa1      = data.GetPtrInt("genDa1");
    Int_t*   genDa2      = data.GetPtrInt("genDa2");
    
    Int_t    nGenJet     = data.GetInt("nGenJet");
    Float_t* genJetE     = data.GetPtrFloat("genJetE");
    Float_t* genJetPt    = data.GetPtrFloat("genJetPt");
    Float_t* genJetEta   = data.GetPtrFloat("genJetEta");
    Float_t* genJetPhi   = data.GetPtrFloat("genJetPhi");


    Int_t    CA8nJet     = data.GetInt("CA8nJet");
    Float_t* CA8jetPt    = data.GetPtrFloat("CA8jetPt");
    Float_t* CA8jetEta   = data.GetPtrFloat("CA8jetEta");
    Float_t* CA8jetPhi   = data.GetPtrFloat("CA8jetPhi");
    Float_t* CA8jetMass  = data.GetPtrFloat("CA8jetMass");
    Int_t*   CA8jetID    = data.GetPtrInt("CA8jetPassID");
    Float_t* CA8jetTau1  = data.GetPtrFloat("CA8jetTau1");
    Float_t* CA8jetTau2  = data.GetPtrFloat("CA8jetTau2");
    
    Int_t    nEle        = data.GetInt("nEle");
    Float_t* elePt       = data.GetPtrFloat("elePt");
    Float_t* eleEta      = data.GetPtrFloat("eleEta");
    Int_t*   eleID       = data.GetPtrInt("elePassID");

    Int_t    nMu         = data.GetInt("nMu");
    Float_t* muPt        = data.GetPtrFloat("muPt");
    Float_t* muEta       = data.GetPtrFloat("muEta");
    Int_t*   muID        = data.GetPtrInt("muPassID");



//----------------------------------Gen Level------------------------------


    TLorentzVector Zp(0,0,0,0);
    TLorentzVector l1(0,0,0,0);
    TLorentzVector l2(0,0,0,0);
    TLorentzVector hd1(0,0,0,0);
    TLorentzVector hd2(0,0,0,0);


    for(int i=0; i<nGenPar; i++){
       for(int j=0; j<i; j++){

        if(genParId[i]==1023){ 

          h_genXPt->Fill(genParPt[i]);

          Zp.SetPtEtaPhiM(genParPt[i],genParEta[i],genParPhi[i],genParM[i]);
          double XY=0;
          XY=Zp.Rapidity();
          h_genXY->Fill(XY);
        }

        if(genParId[i]==25 && genMomParId[i]==1023){
          h_genHPt->Fill(genParPt[i]);
          h_genHEta->Fill(genParEta[i]);
        }

        if(genParId[i]==23 && genMomParId[i]==1023){
          h_genZPt->Fill(genParPt[i]);
          h_genZEta->Fill(genParEta[i]);
        }



        // Z->ll      
        if( (genParId[i]==11 || genParId[i]==13) && genMomParId[i]==23 && genParSt[i]==3) 
          l1.SetPtEtaPhiM(genParPt[i],genParEta[i],genParPhi[i],genParM[i]);
       

        if( (genParId[j]==-11 || genParId[j]==-13) && genMomParId[j]==23 && genParSt[j]==3){
          l2.SetPtEtaPhiM(genParPt[j],genParEta[j],genParPhi[j],genParM[j]);
          double dll=0;
          dll=l2.DeltaR(l1);
          h_genZllDeltaR->Fill(dll);
        }


       // H-> qq 
        if( (genParId[i]>=1 && genParId[i]<=5) && genMomParId[i]==25 && genParSt[i]==3 ) 
          hd1.SetPtEtaPhiM(genParPt[i],genParEta[i],genParPhi[i],genParM[i]);
   

        else if( (genParId[i]<=-1 && genParId[i]>=-5) && genMomParId[i]==25 && genParSt[i]==3 ){
          hd2.SetPtEtaPhiM(genParPt[i],genParEta[i],genParPhi[i],genParM[i]);
          double dhdd=0;
          dhdd=hd2.DeltaR(hd1);
          h_genHqqDeltaR->Fill(dhdd);
        }


      } // for2
    } // for1


//--------------------------------------Gen Level End--------------------------------------------



    // Ordering array by Pt
    for(int i=0; i<nEle; i++){
      for(int j=0; j<i; j++){
	if(elePt[i] > elePt[j]){
	  swap(elePt[i], elePt[j]);
	  swap(eleEta[i], eleEta[j]);
	}
      }
    } // ele
    for(int i=0; i<nMu; i++){
      for(int j=0; j<i; j++){
	if(muPt[i] > muPt[j]){
	  swap(muPt[i], muPt[j]);
          swap(muEta[i], muEta[j]);
        }
      }
    } // mu
    for(int i=0; i<CA8nJet; i++){
      for(int j=0; j<i; j++){
        if(CA8jetPt[i] > CA8jetPt[j]){
          swap(CA8jetPt[i], CA8jetPt[j]);
          swap(CA8jetEta[i], CA8jetEta[j]);
	  swap(CA8jetPhi[i], CA8jetPhi[j]);
	  swap(CA8jetMass[i], CA8jetMass[j]);
	  swap(CA8jetTau1[i], CA8jetTau1[j]);
	  swap(CA8jetTau2[i], CA8jetTau2[j]);
        }
      }
    } // jet




    // basic ele cut
    bool elePtCut=false;
    bool eleEtaCut=false;
    for(int i=0; i<nEle; i++){
      if(elePt[i]>35)elePtCut=true;
      if(fabs(eleEta[i])<2.5)eleEtaCut=true;
    }
    if(elePtCut==false || eleEtaCut==false)continue;


    // basic mu cut                                                           
    bool muPtCut=false;
    bool muEtaCut=false;
    for(int i=0; i<nMu; i++){
      if(muPt[i]>20)muPtCut=true;
      if(fabs(muEta[i])<2.4)muEtaCut=true;
    }
    if(muPtCut==false || muEtaCut==false)continue;


    // basic jet cut                                                           
    bool jetPtCut=false;
    bool jetEtaCut=false;
    for(int i=0; i<CA8nJet; i++){
      if(CA8jetPt[i]>30)jetPtCut=true;
      if(fabs(CA8jetEta[i])<2.4)jetEtaCut=true;
    }
    if(jetPtCut==false || jetEtaCut==false)continue;



    // plot ele histos                                                                                                     
    if(nEle>=1)h_elePt->Fill(elePt[0]);
    if(nEle>=2)h_eleSecPt->Fill(elePt[1]);
    if(nEle>=1 && eleID[0]>0)h_elePt_ID->Fill(elePt[0]);
    if(nEle>=2 && eleID[1]>0)h_eleSecPt_ID->Fill(elePt[1]);

    for(int i=0; i<nEle; i++){
      h_eleEta->Fill(eleEta[i]);
      if(eleID[i]>0)h_eleEta_ID->Fill(eleEta[i]);
    }


    // plot mu histos                                                                                                      
    if(nMu>=1)h_muPt->Fill(muPt[0]);
    if(nMu>=2)h_muSecPt->Fill(muPt[1]);
    if(nMu>=1 && muID[0]&4)h_muPt_track->Fill(muPt[0]);
    if(nMu>=2 && muID[1]&4)h_muSecPt_track->Fill(muPt[1]);
    if(nMu>=1 && muID[0]&2)h_muPt_globe->Fill(muPt[0]);
    if(nMu>=2 && muID[1]&2)h_muSecPt_globe->Fill(muPt[1]);

    for(int i=0; i<nMu; i++){
      h_muEta->Fill(muEta[i]);

      if(muID[i]&4)h_muEta_track->Fill(muEta[i]);
      if(muID[i]&2)h_muEta_globe->Fill(muEta[i]);
    }


    // plot jet histos                                                                                                     
    if(CA8nJet>=1)h_CA8jetPt->Fill(CA8jetPt[0]);
    if(CA8nJet>=1 && CA8jetID[0]>0){
      h_CA8jetPt_ID->Fill(CA8jetPt[0]);
      //      h_CA8jetTau21->Fill(CA8jetTau2[0]/CA8jetTau1[0]);
    }

    for(int i=0; i<CA8nJet; i++){
      h_CA8jetEta->Fill(CA8jetEta[i]);

      if(CA8jetID[i]>0){
        h_CA8jetEta_ID->Fill(CA8jetEta[i]);
      }
    }



    // genjet matching
    TLorentzVector mcJet;
    for(int i=0; i<nGenPar; i++){
      if(fabs(genParId[i])==5 && genMomParId[i]==25)mcJet.SetPtEtaPhiE(genParPt[i],genParEta[i],genParPhi[i],genParE[i]);
    }
    

    // eleID 
    bool eleIDcut=false;
    for(int i=0; i<nEle; i++){
      if(eleID[i]<=0)eleIDcut=true;
    }
    if(eleIDcut==true)continue;

    /*
    // muID
    bool muIDcut=false;
    for(int i=0; i<nMu; i++){
      if(muID[i]&4 || muID[i]&2)muIDcut=true;
    }
    if(muIDcut==false)continue;
    */

    // jetID
    bool jetIDcut=false;
    for(int i=0; i<CA8nJet; i++){
      if(CA8jetID[i]<=0)jetIDcut=true;
    }
    if(jetIDcut==true)continue;

  
    // recojet
    TLorentzVector recoJet;
    float dRjj=-999;
    for(int i=0; i<CA8nJet; i++){
      recoJet.SetPtEtaPhiM(CA8jetPt[i],CA8jetEta[i],CA8jetPhi[i],CA8jetMass[i]);
      dRjj=recoJet.DeltaR(mcJet);

    }


    // plot Tau21
    if(CA8nJet>=1 && dRjj<0.8 && dRjj!=-999)h_CA8jetTau21->Fill(CA8jetTau2[0]/CA8jetTau1[0]);

    
    




  } //entries 

    


  //normalization




  //save output
  TFile* outFile = new TFile(outputFile.data(),"recreate");

  h_genXPt->Write();
  h_genXY->Write();       
  h_genHPt->Write();        
  h_genHEta->Write();    
  h_genHqqDeltaR->Write(); 
  h_genZPt->Write();        
  h_genZEta->Write();     
  h_genZllDeltaR->Write(); 

  h_CA8jetPt->Write();
  h_CA8jetPt_ID->Write();
  h_CA8jetEta->Write();
  h_CA8jetEta_ID->Write();
  h_CA8jetTau21->Write();

  h_elePt->Write();
  h_eleSecPt->Write();
  h_elePt_ID->Write();
  h_eleSecPt_ID->Write();
  h_eleEta->Write();
  h_eleEta_ID->Write();

  h_muPt->Write();
  h_muSecPt->Write();
  h_muPt_track->Write();
  h_muSecPt_track->Write();
  h_muPt_globe->Write();
  h_muSecPt_globe->Write();
  h_muEta->Write();
  h_muEta_track->Write();
  h_muEta_globe->Write();



  outFile->Close();


}
