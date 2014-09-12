// root
// [] .L plot_eff.cpp
// [] run()

void run()
{

   TFile* root = new TFile("delpanj_v2_background.root");


   TH1F* h_CA8jetTau21    = (TH1F*)root->Get("h_CA8jetTau21");
   TH1F* h_CA8jetTau21cut = (TH1F*)root->Get("h_CA8jetTau21cut");
   TH1F* h_CA8jetTau31    = (TH1F*)root->Get("h_CA8jetTau31");
   TH1F* h_CA8jetTau31cut = (TH1F*)root->Get("h_CA8jetTau31cut");
   TH1F* h_CA8jetTau41    = (TH1F*)root->Get("h_CA8jetTau41");
   TH1F* h_CA8jetTau41cut = (TH1F*)root->Get("h_CA8jetTau41cut");
   TH1F* h_CA8jetTau42    = (TH1F*)root->Get("h_CA8jetTau42");
   TH1F* h_CA8jetTau42cut = (TH1F*)root->Get("h_CA8jetTau42cut");




   float temp1 = 1/(h_CA8jetTau21->Integral());
   h_CA8jetTau21->Sumw2();
   h_CA8jetTau21->Scale(temp1);

   float temp2 = 1/(h_CA8jetTau21cut->Integral());
   h_CA8jetTau21cut->Sumw2();
   h_CA8jetTau21cut->Scale(temp2);

   float temp3 = 1/(h_CA8jetTau31->Integral());
   h_CA8jetTau31->Sumw2();
   h_CA8jetTau31->Scale(temp3);

   float temp4 = 1/(h_CA8jetTau31cut->Integral());
   h_CA8jetTau31cut->Sumw2();
   h_CA8jetTau31cut->Scale(temp4);

   float temp5 = 1/(h_CA8jetTau41->Integral());
   h_CA8jetTau41->Sumw2();
   h_CA8jetTau41->Scale(temp5);

   float temp6 = 1/(h_CA8jetTau41cut->Integral());
   h_CA8jetTau41cut->Sumw2();
   h_CA8jetTau41cut->Scale(temp6);

   float temp7 = 1/(h_CA8jetTau42->Integral());
   h_CA8jetTau42->Sumw2();
   h_CA8jetTau42->Scale(temp7);

   float temp8 = 1/(h_CA8jetTau42cut->Integral());
   h_CA8jetTau42cut->Sumw2();
   h_CA8jetTau42cut->Scale(temp8);






   TFile* outFile = new TFile("norm_delpanj_v2_background.root","recreate");

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



