//root -q -b -l recoXmass_El.C++\(\"inputFile\"\,\"outputFile\"\)

#include <map>
#include <vector>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <TH1D.h>
#include <TH2F.h>
#include <TRandom.h>
#include <TLorentzVector.h>
#include <TFile.h>
#include "/home/juwu/XtoZh/macro/untuplizer.h"
#include "/home/juwu/XtoZh/macro/passElectronID.h"
#include "/home/juwu/XtoZh/macro/passMuonID.h"
#include "/home/juwu/XtoZh/macro/JetSelections_v5.h"


using namespace std;
void correlated_data_El(){



  //get TTree from file ...
  TreeReader data("/home/juwu/XtoZh/delpanjTuple/delpanj_v4_data_DoubleEl.root");


  // declare histogram
  TH2F* pruned_tau21 = new TH2F("pruned_tau21","", 50,0,150,20,0,1);
  TH2F* pruned_CSV = new TH2F("pruned_CSV","", 50,0,150,20,0,1);
  TH2F* tau21_CSV = new TH2F("tau21_CSV","", 20,0,1,20,0,1);

  pruned_tau21->Sumw2();
  pruned_CSV->Sumw2();
  tau21_CSV->Sumw2();



  //Event loop
  for(long jEntry=0; jEntry<data.GetEntriesFast() ;jEntry++){

    data.GetEntry(jEntry);


    Int_t    CA8nJet     = data.GetInt("CA8nJet");
    Float_t* CA8jetPrunedM = data.GetPtrFloat("CA8jetPrunedMass");
    Float_t* CA8jetTau1 = data.GetPtrFloat("CA8jetTau1");
    Float_t* CA8jetTau2 = data.GetPtrFloat("CA8jetTau2");
    Float_t* CA8jetCSV = data.GetPtrFloat("CA8jetCSV");


    Int_t    nEle        = data.GetInt("nEle");
    Float_t* elePt       = data.GetPtrFloat("elePt");
    Float_t* eleEta      = data.GetPtrFloat("eleEta");
    Float_t* elePhi      = data.GetPtrFloat("elePhi");
    Float_t* eleM        = data.GetPtrFloat("eleM");   




    Int_t leadjet;
    PassJet(5, data, leadjet);
    
    Int_t leadEle, secEle;
    passElectronID(data, &leadEle, &secEle);





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

      
   
    if(!passTrigger)continue;
    if(!passElectronID(data, &leadEle, &secEle)) continue;
    if(nEle<=1) continue;



      
    // Reco mLL
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
    if(!PassJet(5, data, leadjet)) continue;



    // jet loop
    for(int i=0; i<CA8nJet; i++){

      float tau21=CA8jetTau2[i]/CA8jetTau1[i];

      pruned_tau21->Fill(CA8jetPrunedM[i],tau21);
      pruned_CSV->Fill(CA8jetPrunedM[i],CA8jetCSV[i]);
      tau21_CSV->Fill(tau21,CA8jetCSV[i]);

    }
      



  } //entries 

    
  



  //save output
  TFile* outFile = new TFile("data_El.root","recreate");

  pruned_tau21->Write();
  pruned_CSV->Write();
  tau21_CSV->Write();


  outFile->Close();


}
