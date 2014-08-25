// root
// [] .L plot_eff.cpp
// [] run()

void run()
{

   TFile* root1 = new TFile("scaled_delpanj_DYJetsToLL_PtZ-70To100.root");
   TFile* root2 = new TFile("delpanj_DYJetsToLL_PtZ-100.root");

   TH1F* h1_CA8jetTau21 = (TH1F*)root1->Get("h_CA8jetTau21");
   TH1F* h2_CA8jetTau21 = (TH1F*)root2->Get("h_CA8jetTau21");
   TH1F* h1_CA8jetTau21cut = (TH1F*)root1->Get("h_CA8jetTau21cut");
   TH1F* h2_CA8jetTau21cut = (TH1F*)root2->Get("h_CA8jetTau21cut");
   TH1F* h1_CA8jetTau31 = (TH1F*)root1->Get("h_CA8jetTau31");
   TH1F* h2_CA8jetTau31 = (TH1F*)root2->Get("h_CA8jetTau31");
   TH1F* h1_CA8jetTau31cut = (TH1F*)root1->Get("h_CA8jetTau31cut");
   TH1F* h2_CA8jetTau31cut = (TH1F*)root2->Get("h_CA8jetTau31cut");
   TH1F* h1_CA8jetTau41 = (TH1F*)root1->Get("h_CA8jetTau41");
   TH1F* h2_CA8jetTau41 = (TH1F*)root2->Get("h_CA8jetTau41");
   TH1F* h1_CA8jetTau41cut = (TH1F*)root1->Get("h_CA8jetTau41cut");
   TH1F* h2_CA8jetTau41cut = (TH1F*)root2->Get("h_CA8jetTau41cut");
   TH1F* h1_CA8jetTau42 = (TH1F*)root1->Get("h_CA8jetTau42");
   TH1F* h2_CA8jetTau42 = (TH1F*)root2->Get("h_CA8jetTau42");
   TH1F* h1_CA8jetTau42cut = (TH1F*)root1->Get("h_CA8jetTau42cut");
   TH1F* h2_CA8jetTau42cut = (TH1F*)root2->Get("h_CA8jetTau42cut");




   TH1F* h_CA8jetTau21    = new TH1F("h_CA8jetTau21","",20,0,1);
   TH1F* h_CA8jetTau21cut = new TH1F("h_CA8jetTau21cut","",20,0,1);   
   TH1F* h_CA8jetTau31    = new TH1F("h_CA8jetTau31","",20,0,1);
   TH1F* h_CA8jetTau31cut = new TH1F("h_CA8jetTau31cut","",20,0,1);
   TH1F* h_CA8jetTau41    = new TH1F("h_CA8jetTau41","",20,0,1);
   TH1F* h_CA8jetTau41cut = new TH1F("h_CA8jetTau41cut","",20,0,1);
   TH1F* h_CA8jetTau42    = new TH1F("h_CA8jetTau42","",20,0,1);
   TH1F* h_CA8jetTau42cut = new TH1F("h_CA8jetTau42cut","",20,0,1);




   h_CA8jetTau21->Add(h1_CA8jetTau21,h2_CA8jetTau21,1,1);
   h_CA8jetTau21cut->Add(h1_CA8jetTau21cut,h2_CA8jetTau21cut,1,1);

   h_CA8jetTau31->Add(h1_CA8jetTau31,h2_CA8jetTau31,1,1);
   h_CA8jetTau31cut->Add(h1_CA8jetTau31cut,h2_CA8jetTau31cut,1,1);

   h_CA8jetTau41->Add(h1_CA8jetTau41,h2_CA8jetTau41,1,1);
   h_CA8jetTau41cut->Add(h1_CA8jetTau41cut,h2_CA8jetTau41cut,1,1);

   h_CA8jetTau42->Add(h1_CA8jetTau42,h2_CA8jetTau42,1,1);
   h_CA8jetTau42cut->Add(h1_CA8jetTau42cut,h2_CA8jetTau42cut,1,1);




   TFile* outFile = new TFile("delpanj_DYJetsToLL_PtZ-70.root","recreate");

   h_CA8jetTau21->Write();
   h_CA8jetTau21cut->Write();
   h_CA8jetTau31->Write();
   h_CA8jetTau31cut->Write();
   h_CA8jetTau41->Write();
   h_CA8jetTau41cut->Write();
   h_CA8jetTau42->Write();
   h_CA8jetTau42cut->Write();



   outFile->Close();


}



