//root -q -b -l JetVariables.C++\(\"inputFile\"\,\"outputFile\"\)

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
#include "/home/mattwu/CMS_Corp/XtoZh/macro/JetSelections_cd.h"


using namespace std;
void JetVariables_ee(std::string inputFile, std::string outputFile){


  bool isData=false;
  if(inputFile.find("data")!= std::string::npos)
    isData=true;


  //get TTree from file ...
  TreeReader data(inputFile.data());


  //histogram anoucement
  TH1F* h_mLL         = new TH1F("h_mLL","",100,0,200);
  TH1F* h_CA8jetTau21 = new TH1F("h_CA8jetTau21","",20,0,1);
  TH1F* h_HPt         = new TH1F("h_HPt","",100,0,400);
  TH1F* h_PrunedjetM  = new TH1F("h_PrunedjetM","",50,0,150);


  h_mLL->Sumw2();
  h_CA8jetTau21->Sumw2();
  h_HPt->Sumw2();
  h_PrunedjetM->Sumw2();

  h_mLL->GetXaxis()->SetTitle("mLL electron channel");
  h_CA8jetTau21->GetXaxis()->SetTitle("#tau_{21} electron channel");
  h_HPt->GetXaxis()->SetTitle("Higgs P_{T} electron channel");
  h_PrunedjetM->GetXaxis()->SetTitle("Prunedjet Mass electron channel");


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
    Float_t* CA8jetPrunedM = data.GetPtrFloat("CA8jetPrunedMass");

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
    TLorentzVector e1(0,0,0,0);
    TLorentzVector e2(0,0,0,0);
    TLorentzVector recoZ(0,0,0,0);


    if(nEle>1){

	e1.SetPtEtaPhiM(elePt[leadEle],eleEta[leadEle],elePhi[leadEle],eleM[leadEle]);
	e2.SetPtEtaPhiM(elePt[secEle],eleEta[secEle],elePhi[secEle],eleM[secEle]);
	recoZ=(e1+e2);
	if(recoZ.Pt()<80) continue;
        h_mLL->Fill(recoZ.M());

      } // ee channel             


   
      counter++;
      cout<<"counter:"<<counter<<endl;


      if(!PassJet(data, leadjet)) continue;


    // plot tau21
      if(CA8nJet>0 && leadjet>=0){
	h_CA8jetTau21->Fill(CA8jetTau2[leadjet]/CA8jetTau1[leadjet]);
	h_HPt->Fill(CA8jetPt[leadjet]);
	h_PrunedjetM->Fill(CA8jetPrunedM[leadjet]);

      }
      

  } //entries 

    
  



  //save output
  TFile* outFile = new TFile(outputFile.data(),"recreate");


  h_mLL->Write();
  h_CA8jetTau21->Write();
  h_HPt->Write();
  h_PrunedjetM->Write();



  outFile->Close();


}
