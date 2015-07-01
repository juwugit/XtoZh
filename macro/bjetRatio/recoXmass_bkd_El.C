//root -q -b -l recoXmass_El.C++\(\"inputFile\"\,\"outputFile\"\)

#include <map>
#include <vector>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <TH1.h>
#include <TH2.h>
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

const float scale1 = (19712.225)/(11764538/63.5); //DY70To100 
const float scale2 = (19712.225)/(12511326/39.4); //DY100     

const float bscale = 1.0;
const float bsigma = 0.05;


using namespace std;
void recoXmass_bkd_El(Int_t bjetscale, std::string outputFile){


  // get TTree from file ...
  TreeReader data1("../delpanjTuple/delpanj_v4_DYJetsToLL_PtZ-70To100.root");
  TreeReader data2("../delpanjTuple/delpanj_v4_DYJetsToLL_PtZ-100.root");


  // declare histogram
  const Double_t varBins[] = {680,720,760,800,840,920,1000,1100,1250,1400,1600,1800,2000,2400};
  Int_t nvarBins = sizeof(varBins)/sizeof(varBins[0])-1;


  TH2F* h_sigXMCSV = new TH2F("h_sigXMCSV","signal region XMass vs CA8jet CSV",nvarBins,varBins,5,0,1);
  TH2F* h_sbXMCSV = new TH2F("h_sbXMCSV","sideband region XMass vs CA8jet CSV",nvarBins,varBins,5,0,1);
  TH2F* h_alphaXMCSV = new TH2F("h_alphaXMCSV","alpha ratio of XMass vs CA8jet CSV",nvarBins,varBins,5,0,1);

  TH2F* h_sigXMsCSV = new TH2F("h_sigXMsCSV","signal region XMass vs subjet CSV",nvarBins,varBins,5,0,1);
  TH2F* h_sbXMsCSV = new TH2F("h_sbXMsCSV","sideband region XMass vs subjet CSV",nvarBins,varBins,5,0,1);
  TH2F* h_alphaXMsCSV = new TH2F("h_alphaXMsCSV","alpha ratio of XMass vs subjet CSV",nvarBins,varBins,5,0,1);

  
  h_sigXMCSV->Sumw2();
  h_sbXMCSV->Sumw2();
  h_alphaXMCSV->Sumw2();

  h_sigXMsCSV->Sumw2();
  h_sbXMsCSV->Sumw2();
  h_alphaXMsCSV->Sumw2();

  corrJetV corrJet(unctext);


  int counter70=0;
  int counter70b=0;


  //Event loop data1
  for(long jEntry=0; jEntry<data1.GetEntriesFast() ;jEntry++){

    data1.GetEntry(jEntry);

    Int_t    nGenPar     = data1.GetInt("nGenPar");
    Int_t*   genParId    = data1.GetPtrInt("genParId");
    Int_t*   genParSt    = data1.GetPtrInt("genParSt");
    Int_t*   genMomParId = data1.GetPtrInt("genMomParId");
    Int_t*   genMo1      = data1.GetPtrInt("genMo1");
    Int_t*   genMo2      = data1.GetPtrInt("genMo2");

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

    Int_t    nEle        = data1.GetInt("nEle");
    Float_t* elePt       = data1.GetPtrFloat("elePt");
    Float_t* eleEta      = data1.GetPtrFloat("eleEta");
    Float_t* elePhi      = data1.GetPtrFloat("elePhi");
    Float_t* eleM        = data1.GetPtrFloat("eleM");   

    Int_t leadEle, secEle;
    passElectronID(data1, &leadEle, &secEle);


    // gen level
    Int_t ZMo1=0;
    Int_t ZMo2=0;
    for(int i=0; i<nGenPar; i++){
      
      if(genParId[i]==23 && genParSt[i]==3){
	
	ZMo1=genMo1[i];
	ZMo2=genMo2[i];
	
      }
    }

    bool DYbjet=false;
    bool alljet=false;
    for(int i=0; i<nGenPar; i++){

      if( fabs(genParId[i])==5 && genMo1[i]==ZMo1 && genMo2[i]==ZMo2) DYbjet=true;
      if( (fabs(genParId[i])<=6 || fabs(genParId[i])>=1) && genMo1[i]==ZMo1 && genMo2[i]==ZMo2 )
	alljet=true;
    }


    if(alljet==true) counter70++;
    if(DYbjet==true) counter70b++;

    cout<<"counter70:"<<counter70<<" | counter70b:"<<counter70b<<endl;


    // EleID
    if(!passElectronID(data1, &leadEle, &secEle)) continue;
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
    Int_t scaleMode = 0;
    TLorentzVector tempVector(0,0,0,0);

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
      if(CA8jetPrunedM[leadjet]>70 && CA8jetPrunedM[leadjet]<110){

	if(dRjj>0.3){

	  if(SubjetCSV[i][0]>0 && DYbjet==true) h_sbXMsCSV->Fill(XMass, SubjetCSV[i][0], scale1*(bscale+bjetscale*bsigma));
	  else if(SubjetCSV[i][0]>0) h_sbXMsCSV->Fill(XMass, SubjetCSV[i][0], scale1);

	  if(SubjetCSV[i][1]>0 && DYbjet==true) h_sbXMsCSV->Fill(XMass, SubjetCSV[i][1], scale1*(bscale+bjetscale*bsigma));
	  else if(SubjetCSV[i][1]>0) h_sbXMsCSV->Fill(XMass, SubjetCSV[i][1], scale1);


	} // subjet

	if(dRjj<0.3){

	  if(DYbjet==true) h_sbXMCSV->Fill(XMass, CA8jetCSV[i], scale1*(bscale+bjetscale*bsigma));
	  else h_sbXMCSV->Fill(XMass, CA8jetCSV[i], scale1);

	} // fatjet

      }

      // signal region                                           
      if(CA8jetPrunedM[leadjet]>110 && CA8jetPrunedM[leadjet]<140){

        if(dRjj>0.3){

	  if(SubjetCSV[i][0]>0 && DYbjet==true) h_sigXMsCSV->Fill(XMass, SubjetCSV[i][0], scale1*(bscale+bjetscale*bsigma));
	  else if(SubjetCSV[i][0]>0) h_sigXMsCSV->Fill(XMass, SubjetCSV[i][0], scale1);

	  if(SubjetCSV[i][1]>0 && DYbjet==true) h_sigXMsCSV->Fill(XMass, SubjetCSV[i][1], scale1*(bscale+bjetscale*bsigma));
	  else if(SubjetCSV[i][1]>0) h_sigXMsCSV->Fill(XMass, SubjetCSV[i][1], scale1);

	} // subjet

	if(dRjj<0.3){

	  if(DYbjet==true) h_sigXMCSV->Fill(XMass, CA8jetCSV[i], scale1*(bscale+bjetscale*bsigma));
	  else h_sigXMCSV->Fill(XMass, CA8jetCSV[i], scale1);
	  
	} // fatjet

      }
      
    } // jet loop                                                                    


  } //entries data1
  


  //Event loop data2
  for(long jEntry=0; jEntry<data2.GetEntriesFast() ;jEntry++){

    data2.GetEntry(jEntry);

    Int_t    nGenPar     = data2.GetInt("nGenPar");
    Int_t*   genParId    = data2.GetPtrInt("genParId");
    Int_t*   genParSt    = data2.GetPtrInt("genParSt");
    Int_t*   genMomParId = data2.GetPtrInt("genMomParId");
    Int_t*   genMo1      = data2.GetPtrInt("genMo1");
    Int_t*   genMo2      = data2.GetPtrInt("genMo2");

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
    vector<Float_t>* SubjetEn   = data2.GetPtrVectorFloat("CA8subjetPrunedEn");

    Int_t    nEle        = data2.GetInt("nEle");
    Float_t* elePt       = data2.GetPtrFloat("elePt");
    Float_t* eleEta      = data2.GetPtrFloat("eleEta");
    Float_t* elePhi      = data2.GetPtrFloat("elePhi");
    Float_t* eleM        = data2.GetPtrFloat("eleM");   

    Int_t leadEle, secEle;
    passElectronID(data2, &leadEle, &secEle);

    
    // gen level
    Int_t ZMo1=0;
    Int_t ZMo2=0;
    for(int i=0; i<nGenPar; i++){
      
      if(genParId[i]==23 && genParSt[i]==3){
	
	ZMo1=genMo1[i];
	ZMo2=genMo2[i];
	
      }
    }

    bool DYbjet=false;
    bool alljet=false;
    for(int i=0; i<nGenPar; i++){

      if( fabs(genParId[i])==5 && genMo1[i]==ZMo1 && genMo2[i]==ZMo2) DYbjet=true;
      if( (fabs(genParId[i])<=6 || fabs(genParId[i])>=1) && genMo1[i]==ZMo1 && genMo2[i]==ZMo2 )
	alljet=true;
    }

    /*
    if(alljet==true) counter100++;
    if(DYbjet==true) counter100b++;

    cout<<"counter100:"<<counter100<<" | counter100b:"<<counter100b<<endl;
    */


    // eleID
    if(!passElectronID(data2, &leadEle, &secEle)) continue;
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
    Int_t scaleMode = 0;
    TLorentzVector tempVector(0,0,0,0);

    if(!passJetID(data2, corrJet, csvlMode, scaleMode, &leadjet, &tempVector)) continue;

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
      if(CA8jetPrunedM[leadjet]>70 && CA8jetPrunedM[leadjet]<110){

	if(dRjj>0.3){

	  if(SubjetCSV[i][0]>0 && DYbjet==true) h_sbXMsCSV->Fill(XMass, SubjetCSV[i][0], scale2*(bscale+bjetscale*bsigma));
	  else if(SubjetCSV[i][0]>0) h_sbXMsCSV->Fill(XMass, SubjetCSV[i][0], scale2);

	  if(SubjetCSV[i][1]>0 && DYbjet==true) h_sbXMsCSV->Fill(XMass, SubjetCSV[i][1], scale2*(bscale+bjetscale*bsigma));
	  else if(SubjetCSV[i][1]>0) h_sbXMsCSV->Fill(XMass, SubjetCSV[i][1], scale2);


	} // subjet

	if(dRjj<0.3){

	  if(DYbjet==true) h_sbXMCSV->Fill(XMass, CA8jetCSV[i], scale2*(bscale+bjetscale*bsigma));
	  else h_sbXMCSV->Fill(XMass, CA8jetCSV[i], scale2);

	} // fatjet

      }

      // signal region                                           
      if(CA8jetPrunedM[leadjet]>110 && CA8jetPrunedM[leadjet]<140){

        if(dRjj>0.3){

	  if(SubjetCSV[i][0]>0 && DYbjet==true) h_sigXMsCSV->Fill(XMass, SubjetCSV[i][0], scale2*(bscale+bjetscale*bsigma));
	  else if(SubjetCSV[i][0]>0) h_sigXMsCSV->Fill(XMass, SubjetCSV[i][0], scale2);

	  if(SubjetCSV[i][1]>0 && DYbjet==true) h_sigXMsCSV->Fill(XMass, SubjetCSV[i][1], scale2*(bscale+bjetscale*bsigma));
	  else if(SubjetCSV[i][1]>0) h_sigXMsCSV->Fill(XMass, SubjetCSV[i][1], scale2);

	} // subjet

	if(dRjj<0.3){

	  if(DYbjet==true) h_sigXMCSV->Fill(XMass, CA8jetCSV[i], scale2*(bscale+bjetscale*bsigma));
	  else h_sigXMCSV->Fill(XMass, CA8jetCSV[i], scale2);
	  
	} // fatjet
	
      }
      
    } // jet loop                                                                    

  } //entries data2

  
  h_alphaXMCSV->Divide(h_sigXMCSV, h_sbXMCSV);
  h_alphaXMsCSV->Divide(h_sigXMsCSV, h_sbXMsCSV);
  

  //save output
  TFile* outFile = new TFile(outputFile.data(),"recreate");

  h_sigXMCSV->Write();
  h_sbXMCSV->Write();
  h_alphaXMCSV->Write();

  h_sigXMsCSV->Write();
  h_sbXMsCSV->Write();
  h_alphaXMsCSV->Write();



  outFile->Close();


}
