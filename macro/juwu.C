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
  TH1F* h_CA8jetTau21cut= (TH1F*)h_CA8jetTau21->Clone("h_CA8jetTau21cut");
  TH1F* h_tau21_ee      = (TH1F*)h_CA8jetTau21->Clone("h_tau21_ee");
  TH1F* h_tau21_mm      = (TH1F*)h_CA8jetTau21->Clone("h_tau21_mm");
  TH1F* h_tau21_eeC     = (TH1F*)h_CA8jetTau21->Clone("h_tau21_eeC");
  TH1F* h_tau21_mmC     = (TH1F*)h_CA8jetTau21->Clone("h_tau21_mmC");


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


  int counter=0;


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
    Float_t* CA8jetM     = data.GetPtrFloat("CA8jetMass");
    Int_t*   CA8jetID    = data.GetPtrInt("CA8jetPassID");
    Float_t* CA8jetTau1  = data.GetPtrFloat("CA8jetTau1");
    Float_t* CA8jetTau2  = data.GetPtrFloat("CA8jetTau2");
    Float_t* CA8jetPrunedPt = data.GetPtrFloat("CA8jetPrunedPt");
    Float_t* CA8jetPrunedM  = data.GetPtrFloat("CA8jetPrunedMass");
    
    Int_t    nEle        = data.GetInt("nEle");
    Float_t* elePt       = data.GetPtrFloat("elePt");
    Float_t* eleEta      = data.GetPtrFloat("eleEta");
    Float_t* elePhi      = data.GetPtrFloat("elePhi");
    Float_t* eleM        = data.GetPtrFloat("eleM");
    Int_t*   eleID       = data.GetPtrInt("elePassID");

    Int_t    nMu         = data.GetInt("nMu");
    Float_t* muPt        = data.GetPtrFloat("muPt");
    Float_t* muEta       = data.GetPtrFloat("muEta");
    Float_t* muPhi       = data.GetPtrFloat("muPhi");
    Float_t* muM         = data.GetPtrFloat("muM");
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



    // remove jet-lepton overlape                                                                                          
    vector<int> GoodjetIndex;

    for(int i=0; i<CA8nJet; i++){
      bool overlape=false;

      for(int j=0; j<nEle; j++){
        for(int k=0; k<nMu; k++){

          TLorentzVector lep1(0,0,0,0);
          TLorentzVector lep2(0,0,0,0);
          TLorentzVector alljets(0,0,0,0);

          lep1.SetPtEtaPhiM(elePt[j],eleEta[j],elePhi[j],eleM[j]);
          lep2.SetPtEtaPhiM(muPt[k],muEta[k],muPhi[k],muM[k]);
          alljets.SetPtEtaPhiM(CA8jetPt[i],
                               CA8jetEta[i],
                               CA8jetPhi[i],
                               CA8jetM[i]);

          float dRjl1=-999;
          dRjl1=lep1.DeltaR(alljets);
          float dRjl2=-999;
          dRjl2=lep2.DeltaR(alljets);

          if( (dRjl1<0.5 && dRjl1!=-999) || (dRjl2<0.5 && dRjl2!=-999) ) overlape=true;
   

        } // mu                                                                                                            
      } // ele                                                                                                             

      if(overlape==true)continue;
      GoodjetIndex.push_back(i);

    } // jet                          



    // Put GoodjetIndex into new Jet variables
    Int_t GoodnJet=GoodjetIndex.size();
    vector<float> GoodjetPt;
    vector<float> GoodjetEta;
    vector<float> GoodjetPhi;
    vector<float> GoodjetM;
    vector<int> GoodjetID;
    vector<float> GoodjetTau1;
    vector<float> GoodjetTau2;
    vector<float> GoodjetPrunedPt;
    vector<float> GoodjetPrunedM;

    for(int i=0; i<GoodnJet; i++){

      int index=GoodjetIndex[i];
      
      GoodjetPt.push_back(CA8jetPt[index]);
      GoodjetEta.push_back(CA8jetEta[index]);
      GoodjetPhi.push_back(CA8jetPhi[index]);
      GoodjetM.push_back(CA8jetM[index]);
      GoodjetID.push_back(CA8jetID[index]);
      GoodjetTau1.push_back(CA8jetTau1[index]);
      GoodjetTau2.push_back(CA8jetTau2[index]);
      GoodjetPrunedPt.push_back(CA8jetPrunedPt[index]);
      GoodjetPrunedM.push_back(CA8jetPrunedM[index]);

    }



 

    // Ordering array by Pt
    for(int i=0; i<nEle; i++){
      for(int j=0; j<i; j++){
	if(elePt[i] > elePt[j]){
	  swap(elePt[i], elePt[j]);
	  swap(eleEta[i], eleEta[j]);
	  swap(elePhi[i], elePhi[j]);
	  swap(eleM[i], eleM[j]);
	}
      }
    } // ele
    for(int i=0; i<nMu; i++){
      for(int j=0; j<i; j++){
	if(muPt[i] > muPt[j]){
	  swap(muPt[i], muPt[j]);
          swap(muEta[i], muEta[j]);
	  swap(muPhi[i], muPhi[j]);
          swap(muM[i], muM[j]);
        }
      }
    } // mu
    for(int i=0; i<GoodnJet; i++){
      for(int j=0; j<i; j++){
        if(GoodjetPt[i] > GoodjetPt[j]){
          swap(GoodjetPt[i], GoodjetPt[j]);
          swap(GoodjetEta[i], GoodjetEta[j]);
	  swap(GoodjetPhi[i], GoodjetPhi[j]);
	  swap(GoodjetM[i], GoodjetM[j]);
	  swap(GoodjetTau1[i], GoodjetTau1[j]);
	  swap(GoodjetTau2[i], GoodjetTau2[j]);
	  swap(GoodjetPrunedPt[i], GoodjetPrunedPt[j]);
	  swap(GoodjetPrunedM[i], GoodjetPrunedM[j]);
        }
      }
    } // jet





    // determine which channel                                                                                             
    bool ee=false;
    bool mm=false;
    if(nEle>0 && nMu==0) ee=true;
    if(nEle==0 && nMu>0) mm=true;
    if(nEle>0 && nMu>0 && elePt[0]>muPt[0]) ee=true;
    if(nEle>0 && nMu>0 && elePt[0]<muPt[0]) mm=true;




    // basic ele cut                                                                                                      
    bool eleBasicCut=false;

    for(int i=0; i<nEle; i++){
      if(elePt[i]>35 || fabs(eleEta[i])<2.5) eleBasicCut=true;
    }
    if(eleBasicCut==false && ee==true)continue;



    // basic mu cut                                                                                                        
    bool muBasicCut=false;

    for(int i=0; i<nMu; i++){
      if(muPt[i]>20 || fabs(muEta[i])<2.4) muBasicCut=true;
     }
    if(muBasicCut==false && mm==true)continue;
      
    

    // basic jet cut                                                                                                       
    bool jetBasicCut=false;
    for(int i=0; i<GoodnJet; i++){
      if(GoodjetPt[i]>30 || fabs(GoodjetEta[i])<2.4) jetBasicCut=true;
    }
    if(jetBasicCut==false)continue;








    /*
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
    if(CA8nJet>=1 && CA8jetID[0]>0)h_CA8jetPt_ID->Fill(CA8jetPt[0]);


    for(int i=0; i<CA8nJet; i++){
      h_CA8jetEta->Fill(CA8jetEta[i]);

      if(CA8jetID[i]>0){
        h_CA8jetEta_ID->Fill(CA8jetEta[i]);
      }
    }
    */


    // check overlape
    for(int i=0; i<GoodnJet; i++){
      for(int j=0; j<nEle; j++){
	for(int k=0; k<nMu; k++){

	  TLorentzVector gjet(0,0,0,0);
	  TLorentzVector ele(0,0,0,0);
	  TLorentzVector mu(0,0,0,0);
	  
	  gjet.SetPtEtaPhiM(GoodjetPt[i],GoodjetEta[i],GoodjetPhi[i],GoodjetM[i]);
	  ele.SetPtEtaPhiM(elePt[j],eleEta[j],elePhi[j],eleM[j]);
	  mu.SetPtEtaPhiM(muPt[k],muEta[k],muPhi[k],muM[k]);

	  float dRje=gjet.DeltaR(ele);
	  float dRjm=gjet.DeltaR(mu);
	  if(dRje<0.5 || dRjm<0.5) cout<<"overlape"<<endl;

	} // mu
      } // ele
    } // jet



    
    // plot tau21 with only basic cuts
    for(int i=0; i<GoodnJet; i++){

      h_CA8jetTau21->Fill(GoodjetTau2[i]/GoodjetTau1[i]);
      if(ee==true) h_tau21_ee->Fill(GoodjetTau2[i]/GoodjetTau1[i]);
      if(mm==true) h_tau21_mm->Fill(GoodjetTau2[i]/GoodjetTau1[i]);

    }
        


    
    
    // ee channel cuts 
    bool eleIDcut=false;
    bool eeCut=false;

    for(int i=0; i<nEle; i++){
      for(int j=0; j<i; j++){
	
	if(eleID[i]>0)eleIDcut=true;

	TLorentzVector e1(0,0,0,0);
	TLorentzVector e2(0,0,0,0);
	  
	e1.SetPtEtaPhiM(elePt[i],eleEta[i],elePhi[i],eleM[i]);
	e2.SetPtEtaPhiM(elePt[j],eleEta[j],elePhi[j],eleM[j]);

	float eePt=-999;
	float eeM=-999;
	eePt=(e1+e2).Pt();
	eeM=(e1+e2).M();
	
	if(eePt>80 || (eeM>70 && eeM<110) )eeCut=true;
	  
      }
    }
    if(ee==true && eleIDcut==false)continue;
    if(ee==true && eeCut==false)continue;
    if(ee==true && nEle>0 && elePt[0]<40)continue;
    if(ee==true && nEle>1 && elePt[1]<40)continue;


    
    
    // mumu channel cuts
    bool muIDcut=false;
    bool mumuCut=false;

    for(int i=0; i<nMu; i++){
      for(int j=0; j<i; j++){

	if(muID[i]&4 || muID[i]&2)muIDcut=true;
	
	TLorentzVector mu1(0,0,0,0);
	TLorentzVector mu2(0,0,0,0);

	mu1.SetPtEtaPhiM(muPt[i],muEta[i],muPhi[i],muM[i]);
	mu2.SetPtEtaPhiM(muPt[j],muEta[j],muPhi[j],muM[j]);

        float mumuPt=-999;
	float mumuM=-999;
	mumuPt=(mu1+mu2).Pt();
	mumuM=(mu1+mu2).M();
	
	if(mumuPt>80 || (mumuM>70 && mumuM<110) )mumuCut=true;


      } 
    }
    if(mm==true && muIDcut==false)continue;
    if(mm==true && mumuCut==false)continue;
    if(mm==true && nMu>0 && muPt[0]<40)continue;
    if(mm==true && nMu>1 && muPt[1]<20)continue;
    

    
 

    
    // jetID
    bool jetIDcut=false;
    for(int i=0; i<GoodnJet; i++){
      if(GoodjetID[i]>0)jetIDcut=true;
    }
    if(jetIDcut==false)continue;
    



    // prunedjet cut
    bool pjetcut=false;
    for(int i=0; i<GoodnJet; i++){
      if(GoodjetPrunedM[i]>40 || GoodjetPrunedPt[i]>80)pjetcut=true;
    }
    if(pjetcut==false)continue;



    
    // Xmass cut
    float Xmass=-999;
    TLorentzVector e1(0,0,0,0);
    TLorentzVector e2(0,0,0,0);
    TLorentzVector mu1(0,0,0,0);
    TLorentzVector mu2(0,0,0,0);
    TLorentzVector recoZ(0,0,0,0);
    TLorentzVector recoJet(0,0,0,0);
    
    for(int i=0; i<GoodnJet; i++){
      recoJet.SetPtEtaPhiM(GoodjetPt[i],GoodjetEta[i],GoodjetPhi[i],GoodjetM[i]);

      if(ee==true){

	for(int i=0; i<nEle; i++){
	  for(int j=0; j<i; j++){

	    e1.SetPtEtaPhiM(elePt[i],eleEta[i],elePhi[i],eleM[i]);
	    e2.SetPtEtaPhiM(elePt[j],eleEta[j],elePhi[j],eleM[j]);
	    recoZ=(e1+e2);

	  } // e2                                                                                                         
	} // e1                                                                                                            

      } // ee channel             


      if(mm==true){

	for(int i=0; i<nMu; i++){
	  for(int j=0; j<i; j++){

	    mu1.SetPtEtaPhiM(muPt[i],muEta[i],muPhi[i],muM[i]);
	    mu2.SetPtEtaPhiM(muPt[j],muEta[j],muPhi[j],muM[j]);
	    recoZ=(mu1+mu2);

	  } // mu2                                                                                                        
	} // mu1                                                                                                          

      } // mumu channel                  

    Xmass=(recoJet+recoZ).M();

    } // jet

    if( (Xmass>1725 || Xmass<1275) && Xmass!=-999 )continue;





    // plot tau21 with all cuts
    for(int i=0; i<GoodnJet; i++){

      h_CA8jetTau21cut->Fill(GoodjetTau2[i]/GoodjetTau1[i]);
      if(ee==true) h_tau21_eeC->Fill(GoodjetTau2[i]/GoodjetTau1[i]);
      if(mm==true) h_tau21_mmC->Fill(GoodjetTau2[i]/GoodjetTau1[i]);

    }





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
  h_CA8jetTau21cut->Write();
  h_tau21_ee->Write();
  h_tau21_mm->Write();
  h_tau21_eeC->Write();
  h_tau21_mmC->Write();


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
