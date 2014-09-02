//root -q -b -l juwu.C++\(\"inputFile\"\,\"outputFile\"\)

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
#include "macro/untuplizer.h"
#include "macro/passElectronID.h"
#include "macro/passMuonID.h"
#include "macro/JetSelections.h"


using namespace std;
void juwu_tau21(std::string inputFile, std::string outputFile){


  //get TTree from file ...
  TreeReader data(inputFile.data());


  //histogram anoucement
  TH1F* h_CA8jetTau21    = new TH1F("h_CA8jetTau21","",20,0,1);
  TH1F* h_CA8jetTau21cut = (TH1F*)h_CA8jetTau21->Clone("h_CA8jetTau21cut");
  TH1F* h_CA8jetTau31    = (TH1F*)h_CA8jetTau21->Clone("h_CA8jetTau31");
  TH1F* h_CA8jetTau31cut = (TH1F*)h_CA8jetTau21->Clone("h_CA8jetTau31cut");
  TH1F* h_CA8jetTau41    = (TH1F*)h_CA8jetTau21->Clone("h_CA8jetTau41");
  TH1F* h_CA8jetTau41cut = (TH1F*)h_CA8jetTau21->Clone("h_CA8jetTau41cut");
  TH1F* h_CA8jetTau42    = (TH1F*)h_CA8jetTau21->Clone("h_CA8jetTau42");
  TH1F* h_CA8jetTau42cut = (TH1F*)h_CA8jetTau21->Clone("h_CA8jetTau42cut");

    int counter=0;


  //Event loop
  for(long jEntry=0; jEntry<data.GetEntriesFast() ;jEntry++){

    data.GetEntry(jEntry);

    Int_t    CA8nJet     = data.GetInt("CA8nJet");
    Float_t* CA8jetPt    = data.GetPtrFloat("CA8jetPt");
    Float_t* CA8jetEta   = data.GetPtrFloat("CA8jetEta");
    Float_t* CA8jetPhi   = data.GetPtrFloat("CA8jetPhi");
    Float_t* CA8jetM     = data.GetPtrFloat("CA8jetMass");
    Float_t* CA8jetTau1  = data.GetPtrFloat("CA8jetTau1");
    Float_t* CA8jetTau2  = data.GetPtrFloat("CA8jetTau2");
    Float_t* CA8jetTau3  = data.GetPtrFloat("CA8jetTau3");
    Float_t* CA8jetTau4  = data.GetPtrFloat("CA8jetTau4");
    
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
   



    Int_t leadjet;
    PassJet(data, leadjet);
    
    Int_t leadEle, secEle;
    passElectronID(data, &leadEle, &secEle);

    Int_t leadMu, secMu;
    passMuonID(data, &leadMu, &secMu);





    
    bool ee=false;
    bool mm=false;
    if(nEle>0 && nMu==0) ee=true;
    if(nEle==0 && nMu>0) mm=true;
    if(nEle>0 && nMu>0 && elePt[leadEle]>muPt[leadMu]) ee=true;
    if(nEle>0 && nMu>0 && elePt[leadEle]<muPt[leadMu]) mm=true;
    

    if(ee==true && !passElectronID(data, &leadEle, &secEle)) continue;
    if(mm==true && !passMuonID(data, &leadMu, &secMu)) continue;


    //counter++;
    //cout<<counter<<endl;

    if(CA8nJet>0 && leadjet>=0){

      h_CA8jetTau21->Fill(CA8jetTau2[leadjet]/CA8jetTau1[leadjet]);
      h_CA8jetTau31->Fill(CA8jetTau3[leadjet]/CA8jetTau1[leadjet]);
      h_CA8jetTau41->Fill(CA8jetTau4[leadjet]/CA8jetTau1[leadjet]);
      h_CA8jetTau42->Fill(CA8jetTau4[leadjet]/CA8jetTau2[leadjet]);

    }
    



      
    // Xmass cut
    float Xmass=-999;
    TLorentzVector e1(0,0,0,0);
    TLorentzVector e2(0,0,0,0);
    TLorentzVector mu1(0,0,0,0);
    TLorentzVector mu2(0,0,0,0);
    TLorentzVector recoZ(0,0,0,0);
    TLorentzVector recoJet(0,0,0,0);
    
    if(CA8nJet>0 && leadjet>=0){
      recoJet.SetPtEtaPhiM(CA8jetPt[leadjet],CA8jetEta[leadjet],CA8jetPhi[leadjet],CA8jetM[leadjet]);

      if(ee==true && nEle>1){


	e1.SetPtEtaPhiM(elePt[leadEle],eleEta[leadEle],elePhi[leadEle],eleM[leadEle]);
	e2.SetPtEtaPhiM(elePt[secEle],eleEta[secEle],elePhi[secEle],eleM[secEle]);
	recoZ=(e1+e2);
       
      
      } // ee channel             


      if(mm==true && nMu>1){

	mu1.SetPtEtaPhiM(muPt[leadMu],muEta[leadMu],muPhi[leadMu],muM[leadMu]);
	mu2.SetPtEtaPhiM(muPt[secMu],muEta[secMu],muPhi[secMu],muM[secMu]);
	recoZ=(mu1+mu2);

      } // mumu channel                  


    Xmass=(recoJet+recoZ).M();

    } // jet

    if( (Xmass>1725 || Xmass<1275) && Xmass!=-999 )continue;
    
    //counter++;
    //cout<<counter<<endl;



    if(!PassJet(data, leadjet)) continue;


    counter++;
    cout<<counter<<endl;




    // plot tau21 tau31 tau41 with all cuts
    if(CA8nJet>0 && leadjet>=0){

      h_CA8jetTau21cut->Fill(CA8jetTau2[leadjet]/CA8jetTau1[leadjet]);
      h_CA8jetTau31cut->Fill(CA8jetTau3[leadjet]/CA8jetTau1[leadjet]);
      h_CA8jetTau41cut->Fill(CA8jetTau4[leadjet]/CA8jetTau1[leadjet]);
      h_CA8jetTau42cut->Fill(CA8jetTau4[leadjet]/CA8jetTau2[leadjet]);
      
    }

    


  } //entries 

    




  //save output
  TFile* outFile = new TFile(outputFile.data(),"recreate");


  h_CA8jetTau21->Write();
  h_CA8jetTau21cut->Write();
  h_CA8jetTau31->Write();
  h_CA8jetTau31cut->Write();
  h_CA8jetTau41->Write();
  h_CA8jetTau41cut->Write();
  h_CA8jetTau42->Write();
  h_CA8jetTau42cut->Write();



  outFile->Close();


}
