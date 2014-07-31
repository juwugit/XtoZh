// root
// [] .L plot_eff.cpp
// [] run()

void run()
{

   TFile* root1 = new TFile("/home/juwu/XtoZh/results/scaled_delpanj_DYJetsToLL_PtZ-70To100.root");
   TFile* root2 = new TFile("/home/juwu/XtoZh/results/delpanj_DYJetsToLL_PtZ-100.root");

   TH1F* h1_CA8jetTau21 = (TH1F*)root1->Get("h_CA8jetTau21");
   TH1F* h2_CA8jetTau21 = (TH1F*)root2->Get("h_CA8jetTau21");
   TH1F* h1_CA8jetTau21cut = (TH1F*)root1->Get("h_CA8jetTau21cut");
   TH1F* h2_CA8jetTau21cut = (TH1F*)root2->Get("h_CA8jetTau21cut");
   TH1F* h1_tau21_ee = (TH1F*)root1->Get("h_tau21_ee");
   TH1F* h2_tau21_ee = (TH1F*)root2->Get("h_tau21_ee");
   TH1F* h1_tau21_mm = (TH1F*)root1->Get("h_tau21_mm");
   TH1F* h2_tau21_mm = (TH1F*)root2->Get("h_tau21_mm");
   TH1F* h1_tau21_eeC = (TH1F*)root1->Get("h_tau21_eeC");
   TH1F* h2_tau21_eeC = (TH1F*)root2->Get("h_tau21_eeC");
   TH1F* h1_tau21_mmC = (TH1F*)root1->Get("h_tau21_mmC");
   TH1F* h2_tau21_mmC = (TH1F*)root2->Get("h_tau21_mmC");


   TH1F* h_CA8jetTau21    = new TH1F("h_CA8jetTau21","",20,0,1);
   TH1F* h_CA8jetTau21cut = new TH1F("h_CA8jetTau21cut","",20,0,1);
   TH1F* h_tau21_ee       = new TH1F("h_tau21_ee","",20,0,1);
   TH1F* h_tau21_eeC      = new TH1F("h_tau21_eeC","",20,0,1);
   TH1F* h_tau21_mm       = new TH1F("h_tau21_mm","",20,0,1);
   TH1F* h_tau21_mmC      = new TH1F("h_tau21_mmC","",20,0,1);


   h_CA8jetTau21->Add(h1_CA8jetTau21,h2_CA8jetTau21,1,1);
   h_CA8jetTau21cut->Add(h1_CA8jetTau21cut,h2_CA8jetTau21cut,1,1);
   h_tau21_ee->Add(h1_tau21_ee,h2_tau21_ee,1,1);
   h_tau21_mm->Add(h1_tau21_mm,h2_tau21_mm,1,1);
   h_tau21_eeC->Add(h1_tau21_eeC,h2_tau21_eeC,1,1);
   h_tau21_mmC->Add(h1_tau21_mmC,h2_tau21_mmC,1,1);




   TFile* outFile = new TFile("delpanj_DYJetsToLL_PtZ-70.root","recreate");

   h_CA8jetTau21->Write();
   h_CA8jetTau21cut->Write();
   h_tau21_ee->Write();
   h_tau21_eeC->Write();
   h_tau21_mm->Write();
   h_tau21_mmC->Write();


   outFile->Close();


}



