// root
// [] .L plot_eff.cpp
// [] run()

void run()
{

   TFile* root1 = new TFile("/home/juwu/XtoZh/results/scaled_delpanj_DYJetsToLL_PtZ-70To100.root");
   TFile* root2 = new TFile("/home/juwu/XtoZh/results/delpanj_DYJetsToLL_PtZ-100.root");

   TH1F* h1_CA8jetTau21 = (TH1F*)root1->Get("h_CA8jetTau21");
   TH1F* h2_CA8jetTau21 = (TH1F*)root2->Get("h_CA8jetTau21");

   TH1F* h_CA8jetTau21  = new TH1F("h_CA8jetTau21","",20,0,1);

   h_CA8jetTau21->Add(h1_CA8jetTau21,h2_CA8jetTau21,1,1);


   TFile* outFile = new TFile("mergedHistos.root","recreate");

   h_CA8jetTau21->Write();


   outFile->Close();


}



