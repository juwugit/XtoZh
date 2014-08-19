// root
// [] .L plot_eff.cpp
// [] run()

void run()
{

  TFile* root1  = new TFile("results/norm_delpanj_diboson_signal_ZPrime_hZ_qqll_LHC8_M1500.root");
  TFile* root2  = new TFile("results/norm_delpanj_diboson_signal_ZPrime_ZH_llZZ_M1500.root");
  TFile* root3  = new TFile("results/norm_delpanj_background_M1500.root");


  TH1F* root1_tau21 = (TH1F*)root1->Get("h_CA8jetTau21cut");
  TH1F* root1_tau31 = (TH1F*)root1->Get("h_CA8jetTau31cut");
  TH1F* root1_tau41 = (TH1F*)root1->Get("h_CA8jetTau41cut");  

  TH1F* root2_tau21 = (TH1F*)root2->Get("h_CA8jetTau21cut");
  TH1F* root2_tau31 = (TH1F*)root2->Get("h_CA8jetTau31cut");
  TH1F* root2_tau41 = (TH1F*)root2->Get("h_CA8jetTau41cut");

  TH1F* root3_tau21 = (TH1F*)root3->Get("h_CA8jetTau21cut");
  TH1F* root3_tau31 = (TH1F*)root3->Get("h_CA8jetTau31cut");
  TH1F* root3_tau41 = (TH1F*)root3->Get("h_CA8jetTau41cut");



  root1_tau21->SetLineColor(38);
  root1_tau21->SetFillColor(38);
  root1_tau21->SetFillStyle(3018);
  root2_tau21->SetLineColor(8);
  root2_tau21->SetFillColor(8);
  root2_tau21->SetFillStyle(3313);
  root3_tau21->SetFillColor(2);
  root3_tau21->SetLineColor(2);
  root3_tau21->SetFillStyle(3004);

  root1_tau31->SetLineColor(38);
  root1_tau31->SetFillColor(38);
  root1_tau31->SetFillStyle(3018);
  root2_tau31->SetLineColor(8);
  root2_tau31->SetFillColor(8);
  root2_tau31->SetFillStyle(3313);
  root3_tau31->SetFillColor(2);
  root3_tau31->SetLineColor(2);
  root3_tau31->SetFillStyle(3004);

  root1_tau41->SetLineColor(38);
  root1_tau41->SetFillColor(38);
  root1_tau41->SetFillStyle(3018);
  root2_tau41->SetLineColor(8);
  root2_tau41->SetFillColor(8);
  root2_tau41->SetFillStyle(3313);
  root3_tau41->SetFillColor(2);
  root3_tau41->SetLineColor(2);
  root3_tau41->SetFillStyle(3004);


  
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0);
  gStyle->SetPadGridX(kTRUE);
  gStyle->SetPadGridY(kTRUE);



  TCanvas *c1= new TCanvas("c1","",200,10,800,800);


  root2_tau21->GetXaxis()->SetTitle("#tau_{21}");
  root2_tau21->Draw("histe");
  root1_tau21->Draw("histesame");
  root3_tau21->Draw("histesame");

  leg = new TLegend(0.15,0.78,0.35,0.88);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->AddEntry(root1_tau21,"llqq_M1500","F");
  leg->AddEntry(root2_tau21,"llZZ_M1500","F");
  leg->AddEntry(root3_tau21,"background","F");
  leg->Draw("same");


  gSystem->ProcessEvents();
  TImage *img1 = TImage::Create();
  img1->FromPad(c1);
  img1->WriteImage("h_tau21_M1500.png");
  delete c1;
  delete img1;



  TCanvas *c2= new TCanvas("c2","",200,10,800,800);


  root2_tau31->GetXaxis()->SetTitle("#tau_{31}");
  root2_tau31->Draw("histe");
  root1_tau31->Draw("histesame");
  root3_tau31->Draw("histesame");

  leg = new TLegend(0.65,0.78,0.85,0.88);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->AddEntry(root1_tau31,"llqq_M1500","F");
  leg->AddEntry(root2_tau31,"llZZ_M1500","F");
  leg->AddEntry(root3_tau31,"background","F");
  leg->Draw("same");


  gSystem->ProcessEvents();
  TImage *img2 = TImage::Create();
  img2->FromPad(c2);
  img2->WriteImage("h_tau31_M1500.png");
  delete c2;
  delete img2;



  TCanvas *c3= new TCanvas("c3","",200,10,800,800);


  root2_tau41->GetXaxis()->SetTitle("#tau_{41}");
  root2_tau41->Draw("histe");
  root1_tau41->Draw("histesame");
  root3_tau41->Draw("histesame");

  leg = new TLegend(0.65,0.78,0.85,0.88);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->AddEntry(root1_tau41,"llqq_M1500","F");
  leg->AddEntry(root2_tau41,"llZZ_M1500","F");
  leg->AddEntry(root3_tau41,"background","F");
  leg->Draw("same");


  gSystem->ProcessEvents();
  TImage *img3 = TImage::Create();
  img3->FromPad(c3);
  img3->WriteImage("h_tau41_M1500.png");
  delete c3;
  delete img3;




}
