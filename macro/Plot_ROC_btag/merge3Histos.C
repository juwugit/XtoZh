// root
// [] .L plot_eff.cpp
// [] run()

#include <map>
#include <vector>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <TH1F.h>
#include <TH2F.h>
#include <TRandom.h>
#include <TLorentzVector.h>
#include <TFile.h>



void merge3Histos()
{

   TFile* root1 = new TFile("scaled_delpanj_v4_DYJetsToLL_PtZ-70To100.root");
   TFile* root2 = new TFile("scaled_delpanj_v4_DYJetsToLL_PtZ-100.root");
   TFile* root3 = new TFile("scaled_delpanj_v4_TTTo2L2Nu2B.root");

   TH1F* h1_CA8jetCSV = (TH1F*)root1->Get("h_CA8jetCSV");
   TH1F* h2_CA8jetCSV = (TH1F*)root2->Get("h_CA8jetCSV");
   TH1F* h3_CA8jetCSV = (TH1F*)root3->Get("h_CA8jetCSV");

   TH2F* h1_CA8subjetCSV = (TH2F*)root1->Get("h_CA8subjetCSV");
   TH2F* h2_CA8subjetCSV = (TH2F*)root2->Get("h_CA8subjetCSV");
   TH2F* h3_CA8subjetCSV = (TH2F*)root3->Get("h_CA8subjetCSV");

   /*
   TH1F* h1_CA8jetCSVL = (TH1F*)root1->Get("h_CA8jetCSVL");
   TH1F* h2_CA8jetCSVL = (TH1F*)root2->Get("h_CA8jetCSVL");
   TH1F* h3_CA8jetCSVL = (TH1F*)root3->Get("h_CA8jetCSVL");
   TH1F* h1_CA8jetCSVM = (TH1F*)root1->Get("h_CA8jetCSVM");
   TH1F* h2_CA8jetCSVM = (TH1F*)root2->Get("h_CA8jetCSVM");
   TH1F* h3_CA8jetCSVM = (TH1F*)root3->Get("h_CA8jetCSVM");
   TH1F* h1_CA8jetCSVT = (TH1F*)root1->Get("h_CA8jetCSVT");
   TH1F* h2_CA8jetCSVT = (TH1F*)root2->Get("h_CA8jetCSVT");
   TH1F* h3_CA8jetCSVT = (TH1F*)root3->Get("h_CA8jetCSVT");

   TH2F* h1_CA8subjetCSVL = (TH2F*)root1->Get("h_CA8subjetCSVL");
   TH2F* h2_CA8subjetCSVL = (TH2F*)root2->Get("h_CA8subjetCSVL");
   TH2F* h3_CA8subjetCSVL = (TH2F*)root3->Get("h_CA8subjetCSVL");
   TH2F* h1_CA8subjetCSVM = (TH2F*)root1->Get("h_CA8subjetCSVM");
   TH2F* h2_CA8subjetCSVM = (TH2F*)root2->Get("h_CA8subjetCSVM");
   TH2F* h3_CA8subjetCSVM = (TH2F*)root3->Get("h_CA8subjetCSVM");
   TH2F* h1_CA8subjetCSVT = (TH2F*)root1->Get("h_CA8subjetCSVT");
   TH2F* h2_CA8subjetCSVT = (TH2F*)root2->Get("h_CA8subjetCSVT");
   TH2F* h3_CA8subjetCSVT = (TH2F*)root3->Get("h_CA8subjetCSVT");
   */

   TH1F* h1_Tau21 = (TH1F*)root1->Get("h_Tau21");
   TH1F* h2_Tau21 = (TH1F*)root2->Get("h_Tau21");
   TH1F* h3_Tau21 = (TH1F*)root3->Get("h_Tau21");
   TH1F* h1_COMjetCSV = (TH1F*)root1->Get("h_COMjetCSV");
   TH1F* h2_COMjetCSV = (TH1F*)root2->Get("h_COMjetCSV");
   TH1F* h3_COMjetCSV = (TH1F*)root3->Get("h_COMjetCSV");


   TH1F* h1_SubjetCSV = (TH1F*)root1->Get("h_SubjetCSV");
   TH1F* h2_SubjetCSV = (TH1F*)root2->Get("h_SubjetCSV");
   TH1F* h3_SubjetCSV = (TH1F*)root3->Get("h_SubjetCSV");

   //h3_COMsubjetCSV->Draw();



   TH1F* h_CA8jetCSV    = new TH1F("h_CA8jetCSV","",20,0,1);
   TH2F* h_CA8subjetCSV = new TH2F("h_CA8subjetCSV","",20,0,1,20,0,1);   

   /*
   TH1F* h_CA8jetCSVL    = new TH1F("h_CA8jetCSVL","",20,0,1);
   TH2F* h_CA8subjetCSVL = new TH2F("h_CA8subjetCSVL","",20,0,1,20,0,1);   

   TH1F* h_CA8jetCSVM    = new TH1F("h_CA8jetCSVM","",20,0,1);

   TH2F* h_CA8subjetCSVM = new TH2F("h_CA8subjetCSVM","",20,0,1,20,0,1);   

   TH1F* h_CA8jetCSVT    = new TH1F("h_CA8jetCSVT","",20,0,1);
   TH2F* h_CA8subjetCSVT = new TH2F("h_CA8subjetCSVT","",20,0,1,20,0,1);   
   */

   TH1F* h_Tau21    = new TH1F("h_Tau21","",20,0,1);

   TH1F* h_COMjetCSV    = new TH1F("h_COMjetCSV","",20,0,1);
   TH1F* h_SubjetCSV = new TH1F("h_SubjetCSV","",20,0,1);   



   h_CA8jetCSV->Add(h1_CA8jetCSV,1);
   h_CA8jetCSV->Add(h2_CA8jetCSV,1);
   h_CA8jetCSV->Add(h3_CA8jetCSV,1);
   /*
   h_CA8jetCSVL->Add(h1_CA8jetCSVL,1);
   h_CA8jetCSVL->Add(h2_CA8jetCSVL,1);
   h_CA8jetCSVL->Add(h3_CA8jetCSVL,1);
   h_CA8jetCSVM->Add(h1_CA8jetCSVM,1);
   h_CA8jetCSVM->Add(h2_CA8jetCSVM,1);
   h_CA8jetCSVM->Add(h3_CA8jetCSVM,1);
   h_CA8jetCSVT->Add(h1_CA8jetCSVT,1.0);
   h_CA8jetCSVT->Add(h2_CA8jetCSVT,1.0);
   h_CA8jetCSVT->Add(h3_CA8jetCSVT,1.0);
   */



   h_CA8subjetCSV->Add(h1_CA8subjetCSV,1);
   h_CA8subjetCSV->Add(h2_CA8subjetCSV,1);
   h_CA8subjetCSV->Add(h3_CA8subjetCSV,1);
   /*
   h_CA8subjetCSVL->Add(h1_CA8subjetCSVL,1);
   h_CA8subjetCSVL->Add(h2_CA8subjetCSVL,1);
   h_CA8subjetCSVL->Add(h3_CA8subjetCSVL,1);
   h_CA8subjetCSVM->Add(h1_CA8subjetCSVM,1);
   h_CA8subjetCSVM->Add(h2_CA8subjetCSVM,1);
   h_CA8subjetCSVM->Add(h3_CA8subjetCSVM,1);
   h_CA8subjetCSVT->Add(h1_CA8subjetCSVT,1);
   h_CA8subjetCSVT->Add(h2_CA8subjetCSVT,1);
   h_CA8subjetCSVT->Add(h3_CA8subjetCSVT,1);
   */

   h_Tau21->Add(h1_Tau21,1);
   h_Tau21->Add(h2_Tau21,1);
   h_Tau21->Add(h3_Tau21,1);


   h_COMjetCSV->Add(h1_COMjetCSV,1);
   h_COMjetCSV->Add(h2_COMjetCSV,1);
   h_COMjetCSV->Add(h3_COMjetCSV,1);

   
   h_SubjetCSV->Add(h1_SubjetCSV,1);
   h_SubjetCSV->Add(h2_SubjetCSV,1);
   h_SubjetCSV->Add(h3_SubjetCSV,1);
   




   TFile* outFile = new TFile("delpanj_v4_background.root","recreate");

   h_CA8jetCSV->Write();
   h_CA8subjetCSV->Write();
   /*
   h_CA8jetCSVL->Write();
   h_CA8subjetCSVL->Write();
   h_CA8jetCSVM->Write();
   h_CA8subjetCSVM->Write();
   h_CA8jetCSVT->Write();
   h_CA8subjetCSVT->Write();
   */
   h_COMjetCSV->Write();
   h_SubjetCSV->Write();
   h_Tau21->Write();



   outFile->Close();


}



