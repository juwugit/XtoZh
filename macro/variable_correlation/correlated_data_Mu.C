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
#include "../macro/untuplizer.h"
#include "../macro/passElectronID.h"
#include "../macro/passMuonID.h"
#include "../macro/JetSelections_v5.h"


using namespace std;
void correlated_data_Mu(){



  //get TTree from file ...
  TreeReader data("../delpanjTuple/delpanj_v4_data_DoubleMu.root");


  // declare histogram
  TH2F* pruned_tau21 = new TH2F("pruned_tau21","", 50,0,150,20,0,1);
  TH2F* pruned_CSV = new TH2F("pruned_CSV","", 50,0,150,20,0,1);
  TH2F* tau21_CSV = new TH2F("tau21_CSV","", 20,0,1,20,0,1);
  TH2F* tau21_CSV_sb = new TH2F("tau21_CSV_sb","", 20,0,1,20,0,1);

  TH1F* tau21_sig = new TH1F("tau21_sig","",20,0,1);
  TH1F* tau21_sb = new TH1F("tau21_sb","",20,0,1);
  TH1F* CSV_sig = new TH1F("CSV_sig","",20,0,1);
  TH1F* CSV_sb = new TH1F("CSV_sb","",20,0,1);


  pruned_tau21->Sumw2();
  pruned_CSV->Sumw2();
  tau21_CSV->Sumw2();
  tau21_CSV_sb->Sumw2();

  tau21_sig->Sumw2();
  tau21_sb->Sumw2();
  CSV_sig->Sumw2();
  CSV_sb->Sumw2();




  //Event loop
  for(long jEntry=0; jEntry<data.GetEntriesFast() ;jEntry++){

    data.GetEntry(jEntry);


    Int_t    CA8nJet     = data.GetInt("CA8nJet");
    Float_t* CA8jetPrunedM = data.GetPtrFloat("CA8jetPrunedMass");
    Float_t* CA8jetTau1 = data.GetPtrFloat("CA8jetTau1");
    Float_t* CA8jetTau2 = data.GetPtrFloat("CA8jetTau2");
    Float_t* CA8jetCSV = data.GetPtrFloat("CA8jetCSV");


    Int_t    nEle        = data.GetInt("nMu");
    Float_t* elePt       = data.GetPtrFloat("muPt");
    Float_t* eleEta      = data.GetPtrFloat("muEta");
    Float_t* elePhi      = data.GetPtrFloat("muPhi");
    Float_t* eleM        = data.GetPtrFloat("muM");   




    Int_t leadjet;
    PassJet(5, data, leadjet);
    
    Int_t leadEle, secEle;
    passMuonID(data, &leadEle, &secEle);





    // trigger
    std::string* trigName = data.GetPtrString("hlt_trigName");
    Int_t* trigResult = data.GetPtrInt("hlt_trigResult");
    const Int_t nsize = data.GetPtrStringSize();

    bool passTrigger=false;
    for(int it=0; it< nsize; it++)
      {
	std::string thisTrig= trigName[it];
	int results = trigResult[it];
        /*
	if(thisTrig.find("HLT_DoubleEle33")!= std::string::npos && results==1)
	  {
	    passTrigger=true;
	    break;
	  }
	*/
	
	if(thisTrig.find("HLT_Mu22_TkMu8")!= std::string::npos && results==1)
	  {
	    passTrigger=true;
	    break;
	  }
	
      }

      
   
    if(!passTrigger)continue;
    if(!passMuonID(data, &leadEle, &secEle)) continue;
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

      if(CA8jetPrunedM[i]>50 && CA8jetPrunedM[i]<110){

        tau21_CSV_sb->Fill(tau21,CA8jetCSV[i]);
        tau21_sb->Fill(tau21);
	CSV_sb->Fill(CA8jetCSV[i]);

      } // sideband                                                                                              

      if(CA8jetPrunedM[i]>110 && CA8jetPrunedM[i]<140){

        tau21_sig->Fill(tau21);
        CSV_sig->Fill(CA8jetCSV[i]);

      } // sideband                                                                                             



    }
      



  } //entries 

    
  



  //save output
  TFile* outFile = new TFile("data_Mu.root","recreate");

  pruned_tau21->Write();
  pruned_CSV->Write();
  tau21_CSV->Write();
  tau21_CSV_sb->Write();

  tau21_sig->Write();
  tau21_sb->Write();
  CSV_sig->Write();
  CSV_sb->Write();




  outFile->Close();


}
