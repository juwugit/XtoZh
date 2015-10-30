//root -q -b recoXMassCSV.C++\(scaleMode\,\"inputFile\"\,\"outputFile\"\)

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
#include "untuplizer.h"
#include "passElectronID.h"
#include "passMuonID.h"
#include "passJetID.h"
#include "standalone_LumiReWeighting.cc"


std::string unctext = "START53_V23_Uncertainty_AK7PFchs.txt";
std::string unctext_data = "FT_53_V21_AN4_Uncertainty_AK7PFchs.txt";


using namespace std;

void recoXMassCSV(Int_t scaleMode, std::string inputFile, std::string outputFile){


  // check if the file is data or not
  bool isData=false;
  if(inputFile.find("Double")!= std::string::npos)
  isData=true;

  string jecfilename;
  
  if(isData)
  jecfilename=unctext_data;
  else
  jecfilename=unctext;

  corrJetV corrJet(jecfilename);



  // check lepton channel
  bool isMuon=false;
  if(outputFile.find("Mu")!= std::string::npos)
    isMuon=true;

  bool isEle=false;
  if(outputFile.find("El")!= std::string::npos)
    isEle=true;



  // weights for each ntuple
  float data_lumi = -1;
  if(isEle) data_lumi =19712.225;
  if(isMuon) data_lumi=19671.225;
  if(data_lumi<0) cout<<">>>>>>>>>>>>>>lepton channel choosing is fail<<<<<<<<<<<<<<"<<endl;

  float weightttbar = (data_lumi)/(10783509/25.8); //ttbar
  float weightww    = (data_lumi)/(9959752/56.0); //WW
  float weightwz    = (data_lumi)/(9910267/22.4); //WZ
  float weightzz    = (data_lumi)/(9769891/7.6); //ZZ
  float weightdy70  = (data_lumi)/(11764538/63.5); //DYJets70To100
  float weightdy100 = (data_lumi)/(12511326/39.4); //DYJets100
  
  float weightXM800 = (data_lumi)/(10710/0.00685367);
  float weightXM900 = (data_lumi)/(10209/0.00485861);
  float weightXM1000= (data_lumi)/(19997/0.003263);
  float weightXM1100= (data_lumi)/(9370/0.00217483);
  float weightXM1200= (data_lumi)/(10710/0.00145484);
  float weightXM1300= (data_lumi)/(9369/0.000979745);
  float weightXM1400= (data_lumi)/(10497/0.000664783);
  float weightXM1500= (data_lumi)/(19999/0.000454339);
  float weightXM1600= (data_lumi)/(8950/0.000312541);
  float weightXM1700= (data_lumi)/(9369/0.000216282);
  float weightXM1800= (data_lumi)/(10708/0.000150398);
  float weightXM1900= (data_lumi)/(10498/0.000105039);
  float weightXM2000= (data_lumi)/(19999/7.36377e-05);


  float weight=999999;
  if(inputFile.find("Double")!= std::string::npos)
  weight=1;
  else if(inputFile.find("WW_pythia")!= std::string::npos)
  weight=weightww;
  else if(inputFile.find("WZ_pythia")!= std::string::npos)
  weight=weightwz;
  else if(inputFile.find("ZZ_pythia")!= std::string::npos)
  weight=weightzz;
  else if(inputFile.find("TTTo2L2Nu2B")!= std::string::npos)
  weight=weightttbar;
  else if(inputFile.find("DYJetsToLL_PtZ-70To100")!= std::string::npos)
  weight=weightdy70;
  else if(inputFile.find("DYJetsToLL_PtZ-100")!= std::string::npos)
  weight=weightdy100;
  else if(inputFile.find("AbelianZPrime_ZH_lljj_M800")!= std::string::npos)
  weight=weightXM800;
  else if(inputFile.find("AbelianZPrime_ZH_lljj_M900")!= std::string::npos)
  weight=weightXM900;
  else if(inputFile.find("AbelianZPrime_ZH_lljj_M1000")!= std::string::npos)
  weight=weightXM1000;
  else if(inputFile.find("AbelianZPrime_ZH_lljj_M1100")!= std::string::npos)
  weight=weightXM1100;
  else if(inputFile.find("AbelianZPrime_ZH_lljj_M1200")!= std::string::npos)
  weight=weightXM1200;
  else if(inputFile.find("AbelianZPrime_ZH_lljj_M1300")!= std::string::npos)
  weight=weightXM1300;
  else if(inputFile.find("AbelianZPrime_ZH_lljj_M1400")!= std::string::npos)
  weight=weightXM1400;
  else if(inputFile.find("AbelianZPrime_ZH_lljj_M1500")!= std::string::npos)
  weight=weightXM1500;
  else if(inputFile.find("AbelianZPrime_ZH_lljj_M1600")!= std::string::npos)
  weight=weightXM1600;
  else if(inputFile.find("AbelianZPrime_ZH_lljj_M1700")!= std::string::npos)
  weight=weightXM1700;
  else if(inputFile.find("AbelianZPrime_ZH_lljj_M1800")!= std::string::npos)
  weight=weightXM1800;
  else if(inputFile.find("AbelianZPrime_ZH_lljj_M1900")!= std::string::npos)
  weight=weightXM1900;
  else if(inputFile.find("AbelianZPrime_ZH_lljj_M2000")!= std::string::npos)
  weight=weightXM2000;



  cout<<"# run"<<inputFile.data()<<"  weight:"<<weight<<" jec file:"<<jecfilename<<endl;  



  // get TTree from file ...
  TreeReader data(inputFile.data());



  // declare histogram
  const Double_t varBins[] = {680,720,760,800,840,920,1000,1100,1250,1400,1600,1800,2000,2400};
  Int_t nvarBins = sizeof(varBins)/sizeof(varBins[0])-1;

  TH2F* h_sigMxCA8jetCSV = new TH2F("h_sigMxCA8jetCSV","signal region XMass vs CA8jet CSV",nvarBins,varBins,5,0,1);
  TH2F* h_sbMxCA8jetCSV  = new TH2F("h_sbMxCA8jetCSV","sideband region XMass vs CA8jet CSV",nvarBins,varBins,5,0,1);
  TH2F* h_sigMxSubjetCSV = new TH2F("h_sigMxSubjetCSV","signal region XMass vs subjet CSV",nvarBins,varBins,5,0,1);
  TH2F* h_sbMxSubjetCSV  = new TH2F("h_sbMxSubjetCSV","sideband region XMass vs subjet CSV",nvarBins,varBins,5,0,1);
  TH1F* h_sigXMass       = new TH1F("h_sigXMass","signal region XMass",nvarBins,varBins);
  TH1F* h_sigSubjetCSV   = new TH1F("h_sigSubjetCSV","signal region SubjetCSV",20,0,1);

  h_sigMxCA8jetCSV->Sumw2();
  h_sbMxCA8jetCSV->Sumw2();
  h_sigMxSubjetCSV->Sumw2();
  h_sbMxSubjetCSV->Sumw2();
  h_sigXMass->Sumw2();
  h_sigSubjetCSV->Sumw2();

  
  // PU weight
  standalone_LumiReWeighting LumiWeights(2012, scaleMode);  
  Float_t pu_nTrueInt = 1;
  double  PU_weight = 1;



  // lepton var 
  Int_t    nLep;
  Float_t* lepPt;
  Float_t* lepEta;
  Float_t* lepPhi;
  Float_t* lepM;
  Int_t leadLep, secLep;



  //Event loop
  for(long jEntry=0; jEntry<data.GetEntriesFast() ;jEntry++){

    data.GetEntry(jEntry);

    Int_t    CA8nJet     = data.GetInt("CA8nJet");
    Float_t* CA8jetPrunedM = data.GetPtrFloat("CA8jetPrunedMass");
    Float_t* CA8jetCSV   = data.GetPtrFloat("CA8jetCSV");

    Int_t*   nSubjet = data.GetPtrInt("CA8nSubPrunedJet");
    vector<Float_t>* SubjetCSV = data.GetPtrVectorFloat("CA8subjetPrunedCSV");
    vector<Float_t>* SubjetPt  = data.GetPtrVectorFloat("CA8subjetPrunedPt");
    vector<Float_t>* SubjetEta = data.GetPtrVectorFloat("CA8subjetPrunedEta");
    vector<Float_t>* SubjetPhi = data.GetPtrVectorFloat("CA8subjetPrunedPhi");
    vector<Float_t>* SubjetEn   = data.GetPtrVectorFloat("CA8subjetPrunedEn");


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


    // pile up weight variable
    if(!isData){
      pu_nTrueInt = data.GetFloat("pu_nTrueInt");
      PU_weight = LumiWeights.weight(pu_nTrueInt);
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

   
    // passLeptonID and trigger cut
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



    // reco XMass and jet cuts
    Int_t leadjet;
    Int_t csvlMode = 0;
    TLorentzVector tempVector(0,0,0,0);

    if(!passJetID(data, corrJet, csvlMode, scaleMode, &leadjet, &tempVector)) continue;

    TLorentzVector recoH = tempVector;
    TLorentzVector recoX(0,0,0,0);
    Float_t XMass=-999;
    Float_t prunedmass=CA8jetPrunedM[leadjet];

    if(CA8nJet>0 && leadjet>=0){

      recoX = recoZ+recoH;
      XMass = recoX.M();
    }

    if(XMass<0) continue;
    if(prunedmass>110 && prunedmass<140) h_sigXMass->Fill(XMass,weight*PU_weight);



    // reco CSV
    TLorentzVector subjet1(0,0,0,0);
    TLorentzVector subjet2(0,0,0,0);
    Float_t dRjj=-999;


    //check subjet deltaR
    if(nSubjet[leadjet]>=2){
      
      subjet1.SetPtEtaPhiE(SubjetPt[leadjet][0],SubjetEta[leadjet][0],SubjetPhi[leadjet][0],SubjetEn[leadjet][0]);
      subjet2.SetPtEtaPhiE(SubjetPt[leadjet][1],SubjetEta[leadjet][1],SubjetPhi[leadjet][1],SubjetEn[leadjet][1]);
      dRjj=subjet1.DeltaR(subjet2);  
    }
    
    if(dRjj==-999) continue;
      
      
    // Fill CSV
    if(dRjj>0.3){
      
      if(SubjetCSV[leadjet][0]>0){

	if(prunedmass>70 && prunedmass<110) h_sbMxSubjetCSV->Fill(XMass, SubjetCSV[leadjet][0],weight*PU_weight);
	if(prunedmass>110 && prunedmass<140){
	  h_sigMxSubjetCSV->Fill(XMass, SubjetCSV[leadjet][0],weight*PU_weight);
	  h_sigSubjetCSV->Fill(SubjetCSV[leadjet][0],weight*PU_weight);
	}      
      } //subjet1
      
      if(SubjetCSV[leadjet][1]>0){

	if(prunedmass>70 && prunedmass<110) h_sbMxSubjetCSV->Fill(XMass, SubjetCSV[leadjet][1],weight*PU_weight);
	if(prunedmass>110 && prunedmass<140){
	  h_sigMxSubjetCSV->Fill(XMass, SubjetCSV[leadjet][1],weight*PU_weight);
	  h_sigSubjetCSV->Fill(SubjetCSV[leadjet][1],weight*PU_weight);
	}
      } //subjet2

    } //dRjj>0.3
    

    if(dRjj<0.3 && CA8jetCSV[leadjet]>0){

      if(prunedmass>70 && prunedmass<110) h_sbMxCA8jetCSV->Fill(XMass, CA8jetCSV[leadjet],weight*PU_weight);
      if(prunedmass>110 && prunedmass<140) h_sigMxCA8jetCSV->Fill(XMass, CA8jetCSV[leadjet],weight*PU_weight);

    } //dRjj<0.3 
    


  } //entries 
  
  

  //save output
  TFile* outFile = new TFile(outputFile.data(),"recreate");

  h_sigMxCA8jetCSV->Write();
  h_sbMxCA8jetCSV->Write();
  h_sigMxSubjetCSV->Write();
  h_sbMxSubjetCSV->Write();
  h_sigXMass->Write();
  h_sigSubjetCSV->Write();

  outFile->Close();


}
