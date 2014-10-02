//root -q -b -l genVariable.C++\(\"inputFile\"\,\"outputFile\"\)


#include <vector>
#include <iostream>
#include <algorithm>
#include <TH1D.h>
#include <TRandom.h>
#include <TLorentzVector.h>
#include <TFile.h>
#include "/home/mattwu/CMS_Corp/XtoZh/macro/untuplizer.h"


using namespace std;
void genVariable_p8(std::string inputFile, std::string outputFile){


  //get TTree from file ...
  TreeReader data(inputFile.data());


  //histogram anoucement
  TH1F* h_genXPt        = new TH1F("h_genXPt","",30,0,600);
  h_genXPt->Sumw2();
  h_genXPt->GetXaxis()->SetTitle("X P_{T} [GeV]");

  TH1F* h_genXY         = new TH1F("h_genXY","",30,-3,3);
  h_genXY->Sumw2();
  h_genXY->GetXaxis()->SetTitle("X Rapidity");

  TH1F* h_genXMass=new TH1F("h_genXMass","",1200,0,2400);
  h_genXMass->Sumw2();
  h_genXMass->GetXaxis()->SetTitle("X Mass [GeV]");

  TH1F* h_genHMass=new TH1F("h_genHMass","",75,0,300);
  h_genHMass->Sumw2();
  h_genHMass->GetXaxis()->SetTitle("Higgs Mass [GeV]");

  TH1F* h_genHPt        = new TH1F("h_genHPt","",60,0,1200);
  h_genHPt->Sumw2();
  h_genHPt->GetXaxis()->SetTitle("Higgs P_{T} [GeV]");

  TH1F* h_genHEta       = new TH1F("h_genHEta","",30,-3,3);
  h_genHEta->Sumw2();
  h_genHEta->GetXaxis()->SetTitle("Higgs #eta");

  TH1F* h_genDeltaRqq  = new TH1F("h_genDeltaRqq","",15,0,1.5);
  h_genDeltaRqq->Sumw2();
  h_genDeltaRqq->GetXaxis()->SetTitle("#DeltaR_{qq}");

  TH1F* h_genZMass=new TH1F("h_genZMass","",50,0,200);
  h_genZMass->Sumw2();
  h_genZMass->GetXaxis()->SetTitle("Z Mass [GeV]");

  TH1F* h_genZPt        = new TH1F("h_genZPt","",60,0,1200);
  h_genZPt->Sumw2();
  h_genZPt->GetXaxis()->SetTitle("Z P_{T} [GeV]");

  TH1F* h_genZEta       = new TH1F("h_genZEta","",30,-3,3);
  h_genZEta->Sumw2();
  h_genZEta->GetXaxis()->SetTitle("Z #eta");

  TH1F* h_genDeltaRll  = new TH1F("h_genDeltaRll","",15,0,1.5);
  h_genDeltaRll->Sumw2();
  h_genDeltaRll->GetXaxis()->SetTitle("#DeltaR_{ll}");








  //Event loop
  for(long jEntry=0; jEntry<data.GetEntriesFast() ;jEntry++){

    data.GetEntry(jEntry);

    Int_t    nGenPar     = data.GetInt("nGenPar");
    Float_t* genParE     = data.GetPtrFloat("genParE");
    Float_t* genParPt    = data.GetPtrFloat("genParPt");
    Float_t* genParEta   = data.GetPtrFloat("genParEta");
    Float_t* genParPhi   = data.GetPtrFloat("genParPhi");
    Float_t* genParM     = data.GetPtrFloat("genParM");
    Int_t*   genParQ     = data.GetPtrInt("genParQ");
    Int_t*   genParId    = data.GetPtrInt("genParId");
    Int_t*   genParSt    = data.GetPtrInt("genParSt");
    Int_t*   genMomParId = data.GetPtrInt("genMomParId");
    
    Int_t    nGenJet     = data.GetInt("nGenJet");
    Float_t* genJetE     = data.GetPtrFloat("genJetE");
    Float_t* genJetPt    = data.GetPtrFloat("genJetPt");
    Float_t* genJetEta   = data.GetPtrFloat("genJetEta");
    Float_t* genJetPhi   = data.GetPtrFloat("genJetPhi");




    TLorentzVector X(0,0,0,0);
    TLorentzVector l1(0,0,0,0);
    TLorentzVector l2(0,0,0,0);
    TLorentzVector q1(0,0,0,0);
    TLorentzVector q2(0,0,0,0);


    //9000001 for new LHE
    //1023 for old LHE
    for(int i=0; i<nGenPar; i++){
       for(int j=0; j<i; j++){

        if(genParId[i]==1023 && genParSt[i]==62){ 


	  cout<<"XPt"<<genParPt[i]<<endl;
          h_genXPt->Fill(genParPt[i]);
	  h_genXMass->Fill(genParM[i]);

          X.SetPtEtaPhiM(genParPt[i],genParEta[i],genParPhi[i],genParM[i]);
          double XY=0;
          XY=X.Rapidity();
          h_genXY->Fill(XY);
        }

        if(genParId[i]==25 && genMomParId[i]==1023){
          h_genHPt->Fill(genParPt[i]);
          h_genHEta->Fill(genParEta[i]);
	  h_genHMass->Fill(genParM[i]);
        }

        if(genParId[i]==23 && genMomParId[i]==1023){
          h_genZPt->Fill(genParPt[i]);
          h_genZEta->Fill(genParEta[i]);
	  h_genZMass->Fill(genParM[i]);
        }



        // Z->ll      
        if( (genParId[i]==11 || genParId[i]==13) && genMomParId[i]==23) 
          l1.SetPtEtaPhiM(genParPt[i],genParEta[i],genParPhi[i],genParM[i]);
       

        if( (genParId[j]==-11 || genParId[j]==-13) && genMomParId[j]==23){
          l2.SetPtEtaPhiM(genParPt[j],genParEta[j],genParPhi[j],genParM[j]);
          double dRll=0;
          dRll=l2.DeltaR(l1);
          h_genDeltaRll->Fill(dRll);
        }


       // H-> qq 
        if( (genParId[i]>=1 && genParId[i]<=5) && genMomParId[i]==25 ) 
          q1.SetPtEtaPhiM(genParPt[i],genParEta[i],genParPhi[i],genParM[i]);
   

        else if( (genParId[i]<=-1 && genParId[i]>=-5) && genMomParId[i]==25 ){
          q2.SetPtEtaPhiM(genParPt[i],genParEta[i],genParPhi[i],genParM[i]);
          double dRqq=0;
          dRqq=q2.DeltaR(q1);
          h_genDeltaRqq->Fill(dRqq);
        }


      } // for2
    } // for1






  } //entries 

    

  
  //normalization
  float temp1=0;
  temp1=h_genXPt->Integral();
  h_genXPt->Scale(1/temp1);

  float temp2=0;
  temp2=h_genXY->Integral();
  h_genXY->Scale(1/temp2);

  float temp3=0;
  temp3=h_genHPt->Integral();
  h_genHPt->Scale(1/temp3);

  float temp4=0;
  temp4=h_genHEta->Integral();
  h_genHEta->Scale(1/temp4);

  float temp5=0;
  temp5=h_genDeltaRqq->Integral();
  h_genDeltaRqq->Scale(1/temp5);

  float temp6=0;
  temp6=h_genZPt->Integral();
  h_genZPt->Scale(1/temp6);
  
  float temp7=0;
  temp7=h_genZEta->Integral();
  h_genZEta->Scale(1/temp7);

  float temp8=0;
  temp8=h_genDeltaRll->Integral();
  h_genDeltaRll->Scale(1/temp8);

  float temp9=0;
  temp9=h_genXMass->Integral();
  h_genXMass->Scale(1/temp9);
  
  float temp10=0;
  temp10=h_genHMass->Integral();
  h_genHMass->Scale(1/temp10);

  float temp11=0;
  temp11=h_genZMass->Integral();
  h_genZMass->Scale(1/temp11);




  //save output
  TFile* outFile = new TFile(outputFile.data(),"recreate");

  h_genXPt->Write();
  h_genXY->Write();       
  h_genXMass->Write();
  h_genHMass->Write();
  h_genHPt->Write();        
  h_genHEta->Write();    
  h_genDeltaRqq->Write(); 
  h_genZMass->Write();
  h_genZPt->Write();        
  h_genZEta->Write();     
  h_genDeltaRll->Write(); 


  outFile->Close();


}
