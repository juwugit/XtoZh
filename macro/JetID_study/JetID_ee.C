//root -q -b -l JetID_ee.C++\(\"inputFile\"\,\"outputFile\"\)

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
#include "/home/mattwu/CMS_Corp/XtoZh/macro/untuplizer.h"
#include "/home/mattwu/CMS_Corp/XtoZh/macro/passElectronID.h"
#include "/home/mattwu/CMS_Corp/XtoZh/macro/passMuonID.h"
#include "/home/mattwu/CMS_Corp/XtoZh/macro/JetSelections_onlyBasic.h"


using namespace std;
void JetID_ee(std::string inputFile, std::string outputFile){



  //check the inputfile is data or not
  bool isData=false;
  if(inputFile.find("data")!= std::string::npos)
    isData=true;


  //get TTree from file ...
  TreeReader data(inputFile.data());


  //histogram anoucement
  TH1F* h_CA8jetMuEF  = new TH1F("h_CA8jetMuEF","",10,0,1);
  TH1F* h_CA8jetPhoEF = new TH1F("h_CA8jetPhoEF","",10,0,1);
  TH1F* h_CA8jetCEmEF = new TH1F("h_CA8jetCEmEF","",10,0,1);
  TH1F* h_CA8jetCHadEF= new TH1F("h_CA8jetCHadEF","",10,0,1);
  TH1F* h_CA8jetNEmEF = new TH1F("h_CA8jetNEmEF","",10,0,1);
  TH1F* h_CA8jetNHadEF= new TH1F("h_CA8jetNHadEF","",10,0,1);
  TH1F* h_CA8jetCMulti= new TH1F("h_CA8jetCMulti","",25,0,250);
  TH1F* h_CA8jetTau21 = new TH1F("h_CA8jetTau21","",20,0,1);
  TH1F* h_PrunedjetM  = new TH1F("h_PrunedjetM","",50,0,150);
  TH1F* h_CA8jetCSV   = new TH1F("h_CA8jetCSV","",20,0,1);
  TH1F* h_CA8nSubPrunedJet = new TH1F("h_CA8nSubPrunedJet","",5,0,5);
  TH1F* h_CA8subjetPrunedCSV = new TH1F("h_CA8subjetPrunedCSV","",20,0,1);


  h_CA8jetMuEF->Sumw2();
  h_CA8jetPhoEF->Sumw2();
  h_CA8jetCEmEF->Sumw2();
  h_CA8jetCHadEF->Sumw2();
  h_CA8jetNEmEF->Sumw2();
  h_CA8jetNHadEF->Sumw2();
  h_CA8jetCMulti->Sumw2();
  h_CA8jetTau21->Sumw2();
  h_PrunedjetM->Sumw2();
  h_CA8jetCSV->Sumw2();
  h_CA8nSubPrunedJet->Sumw2();
  h_CA8subjetPrunedCSV->Sumw2();



  h_CA8jetMuEF->GetXaxis()->SetTitle("MuonEnergyFraction-ele channel");
  h_CA8jetPhoEF->GetXaxis()->SetTitle("PhotonEnergyFraction-ele channel");
  h_CA8jetCEmEF->GetXaxis()->SetTitle("ChargedEmEnergyFraction-ele channel");
  h_CA8jetCHadEF->GetXaxis()->SetTitle("ChargedHadronEnergyFraction-ele channel");
  h_CA8jetNEmEF->GetXaxis()->SetTitle("NeutralEmEnergyFraction-ele channel");
  h_CA8jetNHadEF->GetXaxis()->SetTitle("NeutralHadronEnergyFraction-ele channel");
  h_CA8jetCMulti->GetXaxis()->SetTitle("ChargedMultiplicity-ele channel");
  h_CA8jetTau21->GetXaxis()->SetTitle("#tau_{21} electron channel");
  h_PrunedjetM->GetXaxis()->SetTitle("Prunedjet Mass electron channel");
  h_CA8jetCSV->GetXaxis()->SetTitle("CA8jetCSV-ele channel");
  h_CA8nSubPrunedJet->GetXaxis()->SetTitle("CA8nSubPrunedJet-ele channel");
  h_CA8subjetPrunedCSV->GetXaxis()->SetTitle("CA8subjetPrunedCSV-ele channel");

  


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
    Float_t* CA8jetTau3  = data.GetPtrFloat("CA8jetTau3");
    Float_t* CA8jetTau4  = data.GetPtrFloat("CA8jetTau4");
    Float_t* CA8jetPrunedM = data.GetPtrFloat("CA8jetPrunedMass");


    // jet id variables
    Float_t* CA8jetMuEF  = data.GetPtrFloat("CA8jetMuEF");
    Float_t* CA8jetPhoEF = data.GetPtrFloat("CA8jetPhoEF");
    Float_t* CA8jetCEmEF = data.GetPtrFloat("CA8jetCEmEF");
    Float_t* CA8jetCHadEF= data.GetPtrFloat("CA8jetCHadEF");
    Float_t* CA8jetNEmEF = data.GetPtrFloat("CA8jetNEmEF");
    Float_t* CA8jetNHadEF= data.GetPtrFloat("CA8jetNHadEF");
    Float_t* CA8jetCMulti= data.GetPtrFloat("CA8jetCMulti");

    // b-taging variables
    Float_t* CA8jetCSV   = data.GetPtrFloat("CA8jetCSV");
    Int_t nSubjet = data.GetInt("CA8nSubPrunedJet");
    Float_t* SubjetCSV = data.GetPtrFloat("CA8subjetPrunedCSV");
    Float_t* SubjetPt = data.GetPtrFloat("CA8subjetPrunedPt");
    Float_t* SubjetEta = data.GetPtrFloat("CA8subjetPrunedEta");
    Float_t* SubjetPhi = data.GetPtrFloat("CA8subjetPrunedPhi");
    Float_t* SubjetM = data.GetPtrFloat("CA8subjetPrunedMass");


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
   


    // get lep and jet index from header
    vector<Int_t> goodjet;
    PassJet(data, goodjet);
    Int_t leadEle, secEle;
    passElectronID(data, &leadEle, &secEle);
    Int_t leadMu, secMu;
    passMuonID(data, &leadMu, &secMu);




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



      
    // Reco mLL
    TLorentzVector l1(0,0,0,0);
    TLorentzVector l2(0,0,0,0);
    TLorentzVector recoZ(0,0,0,0);
    
    if(nEle<2) continue;
    l1.SetPtEtaPhiM(elePt[leadEle],eleEta[leadEle],elePhi[leadEle],eleM[leadEle]);
    l2.SetPtEtaPhiM(elePt[secEle],eleEta[secEle],elePhi[secEle],eleM[secEle]);
    recoZ=(l1+l2);
    float zpt=recoZ.Pt();
    float zmass=recoZ.M();

    if(zpt<80) continue;
    if(zmass<70 || zmass>110) continue;
    if(!PassJet(data, goodjet)) continue; // pass basic jet selection and get hardest jet index

    


    // plot n-1 cut     
    Int_t counter[6]={0};

    for(Int_t i=0; i<goodjet.size(); i++){
      for(Int_t flag=0; flag<=6; flag++){

        Int_t index=goodjet[i];

        if(CA8jetMuEF[index]   >0.99 && flag!=0) continue;
        if(CA8jetPhoEF[index]  >0.99 && flag!=1) continue;
        if(CA8jetCEmEF[index]  >0.99 && flag!=2) continue;
        if(CA8jetCHadEF[index] <0.0  && flag!=3) continue;
        if(CA8jetNEmEF[index]  >0.99 && flag!=4) continue;
        if(CA8jetNHadEF[index] >0.99 && flag!=5) continue;
        if(CA8jetCMulti[index] <0.0  && flag!=6) continue;


        switch(flag){

        case 0: 

	  if(counter[0]==0){
	    h_CA8jetMuEF->Fill(CA8jetMuEF[index]);
	    counter[0]++;
	  }

	  
        case 1: 
	  
	  if(counter[1]==0){
	    h_CA8jetPhoEF->Fill(CA8jetPhoEF[index]);
	    counter[1]++;
	  }      

	  
	case 2: 

	  if(counter[2]==0){
	    h_CA8jetCEmEF->Fill(CA8jetCEmEF[index]);
	    counter[2]++;
	  }
	  
   
        case 3: 

	  if(counter[3]==0){
	    h_CA8jetCHadEF->Fill(CA8jetCHadEF[index]);
	    counter[3]++;
	  }

        case 4: 

	  if(counter[4]==0){
	    h_CA8jetNEmEF->Fill(CA8jetNEmEF[index]);
	    counter[4]++;
	  }


        case 5: 

	  if(counter[5]==0){
	    h_CA8jetNHadEF->Fill(CA8jetCHadEF[index]);
	    counter[5]++;
	  }

        case 6: 

	  if(counter[6]==0){
	    h_CA8jetCMulti->Fill(CA8jetCMulti[index]);
	    counter[6]++;
	  }
	  

	} // switch
      } // flag
    } // loop jets



    // pass all ID 
    bool IDcut=false;
    for(Int_t i=0; i<goodjet.size(); i++){

      Int_t index=goodjet[i];      
      if(CA8jetID[index]>0)IDcut=true;

    }
    if(IDcut==false) continue;




    // Fill prunedjetMass and Tau21
    
    if(goodjet.size()<=0) continue;
    Int_t index=goodjet[0];
    Float_t tau21=CA8jetTau2[index]/CA8jetTau1[index];
    Float_t prunedmass=CA8jetPrunedM[index];
    
    h_CA8jetTau21->Fill(tau21);
    h_PrunedjetM->Fill(prunedmass);
    


    

    // fill nsubjets and b-tag variables
    h_CA8nSubPrunedJet->Fill(nSubjet);

    if(CA8nJet==0 || goodjet.size()==0) continue;
    if(nSubjet==2){

      TLorentzVector subjet1(0,0,0,0);
      TLorentzVector subjet2(0,0,0,0);

      subjet1.SetPtEtaPhiM(SubjetPt[0],SubjetEta[0],SubjetPhi[0],SubjetM[0]);
      subjet2.SetPtEtaPhiM(SubjetPt[1],SubjetEta[1],SubjetPhi[1],SubjetM[1]);

      Float_t dRjj=subjet1.DeltaR(subjet2);

      if(dRjj>0.3){
	h_CA8subjetPrunedCSV->Fill(SubjetCSV[0]);
	h_CA8subjetPrunedCSV->Fill(SubjetCSV[1]);
      }
      
      else h_CA8jetCSV->Fill(CA8jetCSV[0]);
      
    } // nSubjet
    
    else h_CA8jetCSV->Fill(CA8jetCSV[0]);
    
    
    
  } //entries 
  
  


  //save output
  TFile* outFile = new TFile(outputFile.data(),"recreate");

  h_CA8jetMuEF->Write();
  h_CA8jetPhoEF->Write();
  h_CA8jetCEmEF->Write();
  h_CA8jetCHadEF->Write();
  h_CA8jetNEmEF->Write();
  h_CA8jetNHadEF->Write();
  h_CA8jetCMulti->Write();
  h_CA8jetTau21->Write();
  h_PrunedjetM->Write();
  h_CA8jetCSV->Write();
  h_CA8nSubPrunedJet->Write();
  h_CA8subjetPrunedCSV->Write();


  outFile->Close();


}
