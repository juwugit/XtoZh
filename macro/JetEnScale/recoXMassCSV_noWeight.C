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
#include "/home/juwu/XtoZh/macro/untuplizer.h"
#include "/home/juwu/XtoZh/macro/passElectronID.h"
#include "/home/juwu/XtoZh/macro/passMuonID.h"
#include "/home/juwu/XtoZh/macro/JetSelections.h"
#include "/home/juwu/XtoZh/macro/standalone_LumiReWeighting.cc"


const float data_lumi = 19671.225; // El:19712.225 ; Mu:19671.225

//const float weight = 1; //Data
//const float weight = (data_lumi)/(11765438/63.5); //DY70to100
//const float weight = (data_lumi)/(12511326/39.4); //DY100
//const float weight = (data_lumi)/(10783509/25.8); //TTbar 
//const float weight = (data_lumi)/(9959752/56.0); //WW
//const float weight = (data_lumi)/(9910267/22.4); //WZ  
const float weight = (data_lumi)/(9769891/7.6); //ZZ       


using namespace std;
void recoXMassCSV_noWeight(std::string inputFile, std::string outputFile){


  // check if the file is data or not
  bool isData=false;
  if(inputFile.find("data")!= std::string::npos)
    isData=true;



  // check lepton channel                                                        
  bool isMuon=false;
  if(outputFile.find("Mu")!= std::string::npos)
    isMuon=true;

  bool isEle=false;
  if(outputFile.find("El")!= std::string::npos)
    isEle=true;



  // get TTree from file ...
  TreeReader data(inputFile.data());



  // declare histogram
  const Float_t varBins[] = {680,720,760,800,840,920,1000,1100,1250,1400,1600,1800,2000,2400};
  Int_t nvarBins = sizeof(varBins)/sizeof(varBins[0])-1;

  TH1F* h_sbXMass = new TH1F("h_sbXMass","sideband region XMass",nvarBins, varBins);
  TH1F* h_sigXMass = new TH1F("h_sigXMass","signal region XMass",nvarBins, varBins);
  TH1F* h_sbCA8jetCSV = new TH1F("h_sbCA8jetCSV","sideband region CA8jet CSV",20,0,1);
  TH1F* h_sigCA8jetCSV = new TH1F("h_sigCA8jetCSV","signal region CA8jet CSV",20,0,1);
  TH1F* h_sbSubjetCSV = new TH1F("h_sbSubjetCSV","sideband region subjet CSV",20,0,1);
  TH1F* h_sigSubjetCSV = new TH1F("h_sigSubjetCSV","signal region subjet CSV",20,0,1);

  
  h_sbXMass->Sumw2();
  h_sigXMass->Sumw2();
  h_sbCA8jetCSV->Sumw2();
  h_sigCA8jetCSV->Sumw2();
  h_sbSubjetCSV->Sumw2();
  h_sigSubjetCSV->Sumw2();



  // PU reweight
  standalone_LumiReWeighting LumiWeights_central(2012,0);
  standalone_LumiReWeighting LumiWeights_down(2012,-1);
  standalone_LumiReWeighting LumiWeights_up(2012,1);

  Float_t  pu_nTrueInt       = 1;
  double   PU_weight_central = 1;
  double   PU_weight_up      = 1;
  double   PU_weight_down    = 1;


  // lepton var
  Int_t    nLep;
  Float_t* lepPt;
  Float_t* lepEta;
  Float_t* lepPhi;
  Float_t* lepM;
  
  Int_t leadjet;    
  Int_t leadLep, secLep;


  //Event loop
  for(long jEntry=0; jEntry<data.GetEntriesFast() ;jEntry++){

    data.GetEntry(jEntry);

    Int_t    CA8nJet     = data.GetInt("CA8nJet");
    Float_t* CA8jetPt    = data.GetPtrFloat("CA8jetPt");
    Float_t* CA8jetEta   = data.GetPtrFloat("CA8jetEta");
    Float_t* CA8jetPhi   = data.GetPtrFloat("CA8jetPhi");
    Float_t* CA8jetEn    = data.GetPtrFloat("CA8jetEn");
    Float_t* CA8jetPrunedM = data.GetPtrFloat("CA8jetPrunedMass");
    Float_t* CA8jetCSV   = data.GetPtrFloat("CA8jetCSV");

    Int_t*   nSubjet = data.GetPtrInt("CA8nSubPrunedJet");
    vector<Float_t>* SubjetCSV = data.GetPtrVectorFloat("CA8subjetPrunedCSV");
    vector<Float_t>* SubjetPt  = data.GetPtrVectorFloat("CA8subjetPrunedPt");
    vector<Float_t>* SubjetEta = data.GetPtrVectorFloat("CA8subjetPrunedEta");
    vector<Float_t>* SubjetPhi = data.GetPtrVectorFloat("CA8subjetPrunedPhi");
    vector<Float_t>* SubjetEn  = data.GetPtrVectorFloat("CA8subjetPrunedEn");


    // load lepton variables
    if(isEle){

      nLep    = data.GetInt("nEle");  
      lepPt   = data.GetPtrFloat("elePt");  
      lepEta  = data.GetPtrFloat("eleEta");
      lepPhi  = data.GetPtrFloat("elePhi");
      lepM    = data.GetPtrFloat("eleM");

    }               

    if(isMuon){

      nLep    = data.GetInt("nMu");  
      lepPt   = data.GetPtrFloat("muPt");  
      lepEta  = data.GetPtrFloat("muEta");
      lepPhi  = data.GetPtrFloat("muPhi");
      lepM    = data.GetPtrFloat("muM");

    }               


    // pile up weights 
    if(!isData){

      pu_nTrueInt       =  data.GetFloat("pu_nTrueInt");
      PU_weight_central =  LumiWeights_central.weight(pu_nTrueInt);
      PU_weight_up      =  LumiWeights_up.weight(pu_nTrueInt);
      PU_weight_down    =  LumiWeights_down.weight(pu_nTrueInt);

    }


    // trigger
    std::string* trigName = data.GetPtrString("hlt_trigName");
    Int_t* trigResult = data.GetPtrInt("hlt_trigResult");
    const Int_t nsize = data.GetPtrStringSize();
    
    bool passTrigger=false;
    for(int it=0; it< nsize; it++)
      {
	std::string thisTrig= trigName[it];
	int results = trigResult[it];
     
	if(thisTrig.find("HLT_DoubleEle33")!= std::string::npos && results==1 && isEle)
	  {
	    passTrigger=true;
	    break;
	  }
	
	if(thisTrig.find("HLT_Mu22_TkMu8")!= std::string::npos && results==1 && isMuon)
	  {
	    passTrigger=true;
	    break;
	  }
      }
   

    // passLeptonID
    if(isData && !passTrigger)continue;
    if(isEle && !passElectronID(data, &leadLep, &secLep)) continue;
    if(isMuon && !passMuonID(data, &leadLep, &secLep)) continue;
    if(nLep<=1) continue;
    if(isEle) passElectronID(data, &leadLep, &secLep);
    if(isMuon) passMuonID(data, &leadLep, &secLep);


      
    // Reco mLL & mLL cuts
    TLorentzVector l1(0,0,0,0);
    TLorentzVector l2(0,0,0,0);
    TLorentzVector recoZ(0,0,0,0);
    
    l1.SetPtEtaPhiM(lepPt[leadLep],lepEta[leadLep],lepPhi[leadLep],lepM[leadLep]);
    l2.SetPtEtaPhiM(lepPt[secLep],lepEta[secLep],lepPhi[secLep],lepM[secLep]);
    recoZ=(l1+l2);

    Float_t ZMass=recoZ.M();
    Float_t ZPt=recoZ.Pt();
    
    if(ZMass<70 || ZMass>110) continue;
    if(ZPt<80) continue;



    // reco XMass
    if(!PassJet(3, data, leadjet)) continue;

    TLorentzVector recoH(0,0,0,0);
    TLorentzVector recoX(0,0,0,0);
    Float_t XMass;
    Float_t prunedmass=CA8jetPrunedM[leadjet];
    
    if(CA8nJet>0 && leadjet>=0){
      
      recoH.SetPtEtaPhiE(CA8jetPt[leadjet],CA8jetEta[leadjet],CA8jetPhi[leadjet],CA8jetEn[leadjet]);
      recoX = recoZ+recoH;
      XMass = recoX.M();

      if(prunedmass>70 && prunedmass<110) h_sbXMass->Fill(XMass, PU_weight_central*weight); 
      if(prunedmass>110 && prunedmass<140) h_sigXMass->Fill(XMass, PU_weight_central*weight); 

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
      if(prunedmass>70 && prunedmass<110){

	if(dRjj>0.3){

	  if(SubjetCSV[i][0]>0) h_sbSubjetCSV->Fill(SubjetCSV[i][0], PU_weight_central*weight);
	  if(SubjetCSV[i][1]>0) h_sbSubjetCSV->Fill(SubjetCSV[i][1], PU_weight_central*weight);

	}

	if(dRjj<0.3 && CA8jetCSV[i]>0) h_sbCA8jetCSV->Fill(CA8jetCSV[i], PU_weight_central*weight);
		
      }

      // signal region                                           
      if(prunedmass>110 && prunedmass<140){

        if(dRjj>0.3){

	  if(SubjetCSV[i][0]>0) h_sigSubjetCSV->Fill(SubjetCSV[i][0], PU_weight_central*weight);
	  if(SubjetCSV[i][1]>0) h_sigSubjetCSV->Fill(SubjetCSV[i][1], PU_weight_central*weight);

	}

	if(dRjj<0.3 && CA8jetCSV[i]>0) h_sigCA8jetCSV->Fill(CA8jetCSV[i], PU_weight_central*weight);
	
      }
      
    } // jet loop                                                                    


  } //entries 
  


  //save output
  TFile* outFile = new TFile(outputFile.data(),"recreate");

  h_sbXMass->Write();
  h_sigXMass->Write();
  h_sbCA8jetCSV->Write();
  h_sigCA8jetCSV->Write();
  h_sbSubjetCSV->Write();
  h_sigSubjetCSV->Write();


  outFile->Close();


}
