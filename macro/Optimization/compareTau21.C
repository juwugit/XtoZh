// root
// [] .L plot_eff.cpp
// [] run()

void run()
{

  TFile* root1  = new TFile("results/norm_delpanj_v2_ZPrime_hZ_qqll_LHC8_M1000.root");
  TFile* root2  = new TFile("results/norm_delpanj_v2_ZPrime_ZH_llZZ_M1000.root");
  TFile* root3  = new TFile("results/norm_delpanj_v2_background_M1000.root");
  TFile* root4  = new TFile("results/norm_delpanj_v2_ZPrime_ZH_llWW_M900.root");


  TH1F* root1_tau21 = (TH1F*)root1->Get("h_CA8jetTau21cut");
  TH1F* root1_tau31 = (TH1F*)root1->Get("h_CA8jetTau31cut");
  TH1F* root1_tau41 = (TH1F*)root1->Get("h_CA8jetTau41cut");  
  TH1F* root1_tau42 = (TH1F*)root1->Get("h_CA8jetTau42cut");  

  TH1F* root2_tau21 = (TH1F*)root2->Get("h_CA8jetTau21cut");
  TH1F* root2_tau31 = (TH1F*)root2->Get("h_CA8jetTau31cut");
  TH1F* root2_tau41 = (TH1F*)root2->Get("h_CA8jetTau41cut");
  TH1F* root2_tau42 = (TH1F*)root2->Get("h_CA8jetTau42cut");  

  TH1F* root3_tau21 = (TH1F*)root3->Get("h_CA8jetTau21cut");
  TH1F* root3_tau31 = (TH1F*)root3->Get("h_CA8jetTau31cut");
  TH1F* root3_tau41 = (TH1F*)root3->Get("h_CA8jetTau41cut");
  TH1F* root3_tau42 = (TH1F*)root3->Get("h_CA8jetTau42cut");  

  TH1F* root4_tau21 = (TH1F*)root4->Get("h_CA8jetTau21cut");
  TH1F* root4_tau31 = (TH1F*)root4->Get("h_CA8jetTau31cut");
  TH1F* root4_tau41 = (TH1F*)root4->Get("h_CA8jetTau41cut");
  TH1F* root4_tau42 = (TH1F*)root4->Get("h_CA8jetTau42cut");




  root1_tau21->SetLineColor(38);
  root1_tau21->SetFillColor(38);
  root1_tau21->SetFillStyle(3018);
  root2_tau21->SetLineColor(8);
  root2_tau21->SetFillColor(8);
  root2_tau21->SetFillStyle(3313);
  root3_tau21->SetLineColor(1);
  root3_tau21->SetLineWidth(2);
  root3_tau21->SetMarkerColor(1);
  root3_tau21->SetMarkerStyle(20);
  root3_tau21->SetMarkerSize(1);
  root4_tau21->SetFillColor(2);
  root4_tau21->SetLineColor(2);
  root4_tau21->SetFillStyle(3004);


  root1_tau31->SetLineColor(38);
  root1_tau31->SetFillColor(38);
  root1_tau31->SetFillStyle(3018);
  root2_tau31->SetLineColor(8);
  root2_tau31->SetFillColor(8);
  root2_tau31->SetFillStyle(3313);
  root3_tau31->SetLineColor(1);
  root3_tau31->SetLineWidth(2);
  root3_tau31->SetMarkerColor(1);
  root3_tau31->SetMarkerStyle(20);
  root3_tau31->SetMarkerSize(1);
  root4_tau31->SetFillColor(6);
  root4_tau31->SetLineColor(6);
  root4_tau31->SetFillStyle(3003);



  root1_tau41->SetLineColor(38);
  root1_tau41->SetFillColor(38);
  root1_tau41->SetFillStyle(3018);
  root2_tau41->SetLineColor(8);
  root2_tau41->SetFillColor(8);
  root2_tau41->SetFillStyle(3313);
  root3_tau41->SetLineColor(1);
  root3_tau41->SetLineWidth(2);
  root3_tau41->SetMarkerColor(1);
  root3_tau41->SetMarkerStyle(20);
  root3_tau41->SetMarkerSize(1);
  root4_tau41->SetFillColor(6);
  root4_tau41->SetLineColor(6);
  root4_tau41->SetFillStyle(3003);


  root1_tau42->SetLineColor(38);
  root1_tau42->SetFillColor(38);
  root1_tau42->SetFillStyle(3018);
  root2_tau42->SetLineColor(8);
  root2_tau42->SetFillColor(8);
  root2_tau42->SetFillStyle(3313);
  root3_tau42->SetLineColor(1);
  root3_tau42->SetLineWidth(2);
  root3_tau42->SetMarkerColor(1);
  root3_tau42->SetMarkerStyle(20);
  root3_tau42->SetMarkerSize(1);
  root4_tau42->SetFillColor(6);
  root4_tau42->SetLineColor(6);
  root4_tau42->SetFillStyle(3003);




  
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0);
  gStyle->SetPadGridX(kTRUE);
  gStyle->SetPadGridY(kTRUE);



  TCanvas *c1= new TCanvas("c1","",200,10,1600,1600);
  c1->Divide(2,2);



  c1->cd(1);
  root4_tau21->GetXaxis()->SetTitle("#tau_{21}");
  root4_tau21->Draw("histe");
  root1_tau21->Draw("histesame");
  root3_tau21->Draw("histesame");
  root2_tau21->Draw("histesame");

  leg = new TLegend(0.15,0.78,0.35,0.88);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->AddEntry(root1_tau21,"llqq_M1000","F");
  leg->AddEntry(root2_tau21,"llZZ_M1000","F");
  leg->AddEntry(root3_tau21,"background","lep");
  leg->AddEntry(root4_tau21,"llWW_M900","F");
  leg->Draw("same");


  c1->cd(2);
  root4_tau31->GetXaxis()->SetTitle("#tau_{31}");
  root4_tau31->Draw("histe");
  root1_tau31->Draw("histesame");
  root3_tau31->Draw("histesame");
  root2_tau31->Draw("histesame");


  c1->cd(3);
  root4_tau41->GetXaxis()->SetTitle("#tau_{41}");
  root4_tau41->Draw("histe");
  root1_tau41->Draw("histesame");
  root3_tau41->Draw("histesame");
  root2_tau41->Draw("histesame");


  c1->cd(4);
  root3_tau42->GetXaxis()->SetTitle("#tau_{42}");
  root3_tau42->Draw("histe");
  root1_tau42->Draw("histesame");
  root2_tau42->Draw("histesame");
  root4_tau42->Draw("histesame");


  gSystem->ProcessEvents();
  TImage *img1 = TImage::Create();
  img1->FromPad(c1);
  img1->WriteImage("h_compareNsubj_M1000.png");
  delete c1;
  delete img1;





}
