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


const float scale1=0.00472913; //DY70To100
const float scale2=0.00275936; //DY100


using namespace std;
void correlated_MC_El(){


  //get TTree from file ...
  TreeReader data1("../delpanjTuple/delpanj_v4_DYJetsToLL_PtZ-70To100.root");
  TreeReader data2("../delpanjTuple/delpanj_v4_DYJetsToLL_PtZ-100.root");


  // declare histogram
  TH2F* pruned_tau21 = new TH2F("pruned_tau21","", 50,0,150,20,0,1);
  TH2F* pruned_CSV = new TH2F("pruned_CSV","", 50,0,150,20,0,1);
  TH2F* tau21_CSV = new TH2F("tau21_CSV","", 20,0,1,20,0,1);
  TH2F* tau21_CSV_sb = new TH2F("tau21_CSV_sb","", 20,0,1,20,0,1);

  TH1F* tau21_sig = new TH1F("tau21_sig","",20,0,1);
  TH1F* tau21_sb = new TH1F("tau21_sb","",20,0,1);
  TH1F* CSV_sig = new TH1F("CSV_sig","",20,0,1);
  TH1F* CSV_sb = new TH1F("CSV_sb","",20,0,1);

  TH1F* CSV_sig_sub = new TH1F("CSV_sig_sub","",20,0,1);
  TH1F* CSV_sb_sub = new TH1F("CSV_sb_sub","",20,0,1);
  TH1F* alpha = new TH1F("alpha","",20,0,1);
  TH1F* alpha_sub = new TH1F("alpha_sub","",20,0,1);

  TH1F* CSV_sig_test = new TH1F("CSV_sig_test","",20,0,1);
  TH1F* CSV_sb_test = new TH1F("CSV_sb_test","",20,0,1);




  pruned_tau21->Sumw2();
  pruned_CSV->Sumw2();
  tau21_CSV->Sumw2();
  tau21_CSV_sb->Sumw2();

  tau21_sig->Sumw2();
  tau21_sb->Sumw2();
  CSV_sig->Sumw2();
  CSV_sb->Sumw2();

  CSV_sig_sub->Sumw2();
  CSV_sb_sub->Sumw2();

  alpha->Sumw2();
  alpha_sub->Sumw2();


  CSV_sig_test->Sumw2();
  CSV_sb_test->Sumw2();





  //Event loop data1
  for(long jEntry=0; jEntry<data1.GetEntriesFast() ;jEntry++){

    data1.GetEntry(jEntry);


    Int_t    CA8nJet     = data1.GetInt("CA8nJet");
    Float_t* CA8jetPrunedM = data1.GetPtrFloat("CA8jetPrunedMass");
    Float_t* CA8jetTau1 = data1.GetPtrFloat("CA8jetTau1");
    Float_t* CA8jetTau2 = data1.GetPtrFloat("CA8jetTau2");
    Float_t* CA8jetCSV = data1.GetPtrFloat("CA8jetCSV");

    Int_t*   nSubjet = data1.GetPtrInt("CA8nSubPrunedJet");
    vector<Float_t>* SubjetCSV = data1.GetPtrVectorFloat("CA8subjetPrunedCSV");
    vector<Float_t>* SubjetPt  = data1.GetPtrVectorFloat("CA8subjetPrunedPt");
    vector<Float_t>* SubjetEta = data1.GetPtrVectorFloat("CA8subjetPrunedEta");
    vector<Float_t>* SubjetPhi = data1.GetPtrVectorFloat("CA8subjetPrunedPhi");
    vector<Float_t>* SubjetM   = data1.GetPtrVectorFloat("CA8subjetPrunedMass");


    Int_t    nEle        = data1.GetInt("nEle");
    Float_t* elePt       = data1.GetPtrFloat("elePt");
    Float_t* eleEta      = data1.GetPtrFloat("eleEta");
    Float_t* elePhi      = data1.GetPtrFloat("elePhi");
    Float_t* eleM        = data1.GetPtrFloat("eleM");   




    Int_t leadjet;
    PassJet(5, data1, leadjet);
    
    Int_t leadEle, secEle;
    passElectronID(data1, &leadEle, &secEle);



    if(!passElectronID(data1, &leadEle, &secEle)) continue;
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
    if(!PassJet(5, data1, leadjet)) continue;



    // jet loop
    TLorentzVector subjet1(0,0,0,0);
    TLorentzVector subjet2(0,0,0,0);
    Float_t dRjj=-999;


    for(int i=0; i<CA8nJet; i++){

      float tau21=CA8jetTau2[i]/CA8jetTau1[i];

      pruned_tau21->Fill(CA8jetPrunedM[i],tau21,scale1);
      pruned_CSV->Fill(CA8jetPrunedM[i],CA8jetCSV[i],scale1);
      tau21_CSV->Fill(tau21,CA8jetCSV[i],scale1);

      if(nSubjet[i]>=2){

	subjet1.SetPtEtaPhiM(SubjetPt[i][0],SubjetEta[i][0],SubjetPhi[i][0],SubjetM[i][0]);
	subjet2.SetPtEtaPhiM(SubjetPt[i][1],SubjetEta[i][1],SubjetPhi[i][1],SubjetM[i][1]);
	dRjj=subjet1.DeltaR(subjet2);

      }
      
      
      if(CA8jetPrunedM[i]>50 && CA8jetPrunedM[i]<110){
	
	tau21_CSV_sb->Fill(tau21,CA8jetCSV[i], scale1);
	tau21_sb->Fill(tau21, scale1);
    
	if(dRjj>0.3){

          CSV_sb_sub->Fill(SubjetCSV[i][0], scale1);
          CSV_sb_sub->Fill(SubjetCSV[i][1], scale1);

          CSV_sb_test->Fill(CA8jetCSV[i], scale1);

        }


        if(dRjj<0.3 && dRjj!=-999) CSV_sb->Fill(CA8jetCSV[i], scale1);

	
      } // sideband                                   

      if(CA8jetPrunedM[i]>110 && CA8jetPrunedM[i]<140){

	tau21_sig->Fill(tau21, scale1);



        if(dRjj>0.3){

          CSV_sig_sub->Fill(SubjetCSV[i][0], scale1);
          CSV_sig_sub->Fill(SubjetCSV[i][1], scale1);


          CSV_sig_test->Fill(CA8jetCSV[i], scale1);


        }


	if(dRjj<0.3 && dRjj!=-999) CSV_sig->Fill(CA8jetCSV[i], scale1);


      } // signal



    }
      



  } //entries 

    



  //Event loop data2
  for(long jEntry=0; jEntry<data2.GetEntriesFast() ;jEntry++){

    data2.GetEntry(jEntry);


    Int_t    CA8nJet     = data2.GetInt("CA8nJet");
    Float_t* CA8jetPrunedM = data2.GetPtrFloat("CA8jetPrunedMass");
    Float_t* CA8jetTau1 = data2.GetPtrFloat("CA8jetTau1");
    Float_t* CA8jetTau2 = data2.GetPtrFloat("CA8jetTau2");
    Float_t* CA8jetCSV = data2.GetPtrFloat("CA8jetCSV");

    Int_t*   nSubjet = data2.GetPtrInt("CA8nSubPrunedJet");
    vector<Float_t>* SubjetCSV = data2.GetPtrVectorFloat("CA8subjetPrunedCSV");
    vector<Float_t>* SubjetPt  = data2.GetPtrVectorFloat("CA8subjetPrunedPt");
    vector<Float_t>* SubjetEta = data2.GetPtrVectorFloat("CA8subjetPrunedEta");
    vector<Float_t>* SubjetPhi = data2.GetPtrVectorFloat("CA8subjetPrunedPhi");
    vector<Float_t>* SubjetM   = data2.GetPtrVectorFloat("CA8subjetPrunedMass");


    Int_t    nEle        = data2.GetInt("nEle");
    Float_t* elePt       = data2.GetPtrFloat("elePt");
    Float_t* eleEta      = data2.GetPtrFloat("eleEta");
    Float_t* elePhi      = data2.GetPtrFloat("elePhi");
    Float_t* eleM        = data2.GetPtrFloat("eleM");   




    Int_t leadjet;
    PassJet(5, data2, leadjet);
    
    Int_t leadEle, secEle;
    passElectronID(data2, &leadEle, &secEle);



    if(!passElectronID(data2, &leadEle, &secEle)) continue;
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
    if(!PassJet(5, data2, leadjet)) continue;



    // jet loop
    TLorentzVector subjet1(0,0,0,0);
    TLorentzVector subjet2(0,0,0,0);
    Float_t dRjj=-999;

    for(int i=0; i<CA8nJet; i++){

      float tau21=CA8jetTau2[i]/CA8jetTau1[i];

      pruned_tau21->Fill(CA8jetPrunedM[i],tau21,scale2);
      pruned_CSV->Fill(CA8jetPrunedM[i],CA8jetCSV[i],scale2);
      tau21_CSV->Fill(tau21,CA8jetCSV[i],scale2);


      if(nSubjet[i]>=2){

	subjet1.SetPtEtaPhiM(SubjetPt[i][0],SubjetEta[i][0],SubjetPhi[i][0],SubjetM[i][0]);
        subjet2.SetPtEtaPhiM(SubjetPt[i][1],SubjetEta[i][1],SubjetPhi[i][1],SubjetM[i][1]);
        dRjj=subjet1.DeltaR(subjet2);

      }



      if(CA8jetPrunedM[i]>50 && CA8jetPrunedM[i]<110){

	tau21_CSV_sb->Fill(tau21,CA8jetCSV[i], scale2);
	tau21_sb->Fill(tau21, scale2);

        if(dRjj>0.3){

          CSV_sb_sub->Fill(SubjetCSV[i][0], scale1);
          CSV_sb_sub->Fill(SubjetCSV[i][1], scale1);

          CSV_sb_test->Fill(CA8jetCSV[i], scale1);

	}


        if(dRjj<0.3 && dRjj!=-999) CSV_sb->Fill(CA8jetCSV[i], scale1);


      } // sideband                                   



      if(CA8jetPrunedM[i]>110 && CA8jetPrunedM[i]<140){

	tau21_sig->Fill(tau21, scale2);

        if(dRjj>0.3){

          CSV_sig_sub->Fill(SubjetCSV[i][0], scale2);
          CSV_sig_sub->Fill(SubjetCSV[i][1], scale2);


          CSV_sig_test->Fill(CA8jetCSV[i], scale2);


	}


        if(dRjj<0.3 && dRjj!=-999) CSV_sig->Fill(CA8jetCSV[i], scale2);


      } // signal                                     

    }
      



  } //entries 



  alpha->Divide(CSV_sig, CSV_sb);
  alpha_sub->Divide(CSV_sig_sub, CSV_sb_sub);


  



  //save output
  TFile* outFile = new TFile("MC_El.root","recreate");

  pruned_tau21->Write();
  pruned_CSV->Write();
  tau21_CSV->Write();
  tau21_CSV_sb->Write();

  tau21_sig->Write();
  tau21_sb->Write();
  CSV_sig->Write();
  CSV_sb->Write();


  CSV_sig_sub->Write();
  CSV_sb_sub->Write();


  alpha->Write();
  alpha_sub->Write();


  CSV_sig_test->Write();
  CSV_sb_test->Write();






  outFile->Close();


}
