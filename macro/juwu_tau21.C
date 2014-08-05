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
void juwu_tau21(std::string inputFile, std::string outputFile){


  //get TTree from file ...
  TreeReader data(inputFile.data());


  //histogram anoucement
  TH1F* h_CA8jetTau21   = new TH1F("h_CA8jetTau21","",20,0,1);
  TH1F* h_CA8jetTau21cut= (TH1F*)h_CA8jetTau21->Clone("h_CA8jetTau21cut");
  TH1F* h_tau21_ee      = (TH1F*)h_CA8jetTau21->Clone("h_tau21_ee");
  TH1F* h_tau21_mm      = (TH1F*)h_CA8jetTau21->Clone("h_tau21_mm");
  TH1F* h_tau21_eeC     = (TH1F*)h_CA8jetTau21->Clone("h_tau21_eeC");
  TH1F* h_tau21_mmC     = (TH1F*)h_CA8jetTau21->Clone("h_tau21_mmC");




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
    
    for(int k=0; k<GoodnJet; k++){
      recoJet.SetPtEtaPhiM(GoodjetPt[k],GoodjetEta[k],GoodjetPhi[k],GoodjetM[k]);

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



  h_CA8jetTau21->Write();
  h_CA8jetTau21cut->Write();
  h_tau21_ee->Write();
  h_tau21_mm->Write();
  h_tau21_eeC->Write();
  h_tau21_mmC->Write();


  outFile->Close();


}
