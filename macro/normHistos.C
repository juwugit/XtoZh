// root
// [] .L plot_eff.cpp
// [] run()

void run()
{

   TFile* root = new TFile("/home/juwu/XtoZh/results/delpanj_DYJetsToLL_PtZ-70.root");


   TH1F* h_CA8jetTau21 = (TH1F*)root->Get("h_CA8jetTau21");
   TH1F* h_CA8jetTau21cut = (TH1F*)root->Get("h_CA8jetTau21cut");
   TH1F* h_tau21_ee = (TH1F*)root->Get("h_tau21_ee");
   TH1F* h_tau21_mm = (TH1F*)root->Get("h_tau21_mm");
   TH1F* h_tau21_eeC = (TH1F*)root->Get("h_tau21_eeC");
   TH1F* h_tau21_mmC = (TH1F*)root->Get("h_tau21_mmC");


 

   float temp1 = 1/(h_CA8jetTau21->Integral());
   h_CA8jetTau21->Sumw2();
   h_CA8jetTau21->Scale(temp1);

   float temp2 = 1/(h_CA8jetTau21cut->Integral());
   h_CA8jetTau21cut->Sumw2();
   h_CA8jetTau21cut->Scale(temp2);

   float temp3 = 1/(h_tau21_ee->Integral());
   h_tau21_ee->Sumw2();
   h_tau21_ee->Scale(temp3);

   float temp4 = 1/(h_tau21_mm->Integral());
   h_tau21_mm->Sumw2();
   h_tau21_mm->Scale(temp4);

   float temp5 = 1/(h_tau21_eeC->Integral());
   h_tau21_eeC->Sumw2();
   h_tau21_eeC->Scale(temp5);

   float temp6 = 1/(h_tau21_mmC->Integral());
   h_tau21_mmC->Sumw2();
   h_tau21_mmC->Scale(temp6);





   TFile* outFile = new TFile("delpanj_DYJetsToLL_PtZ-70_norm.root","recreate");

   h_CA8jetTau21->Write();
   h_CA8jetTau21cut->Write();
   h_tau21_ee->Write();
   h_tau21_eeC->Write();
   h_tau21_mm->Write();
   h_tau21_mmC->Write();


   outFile->Close();


}



