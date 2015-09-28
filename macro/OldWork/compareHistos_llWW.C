// root
// [] .L plot_eff.cpp
// [] run()

void run()
{

  TFile* root1  = new TFile("results/delpanj_diboson_signal_ZPrime_ZH_llWW_M800.root");
  TFile* root2  = new TFile("results/delpanj_diboson_signal_ZPrime_ZH_llWW_M900.root");
  TFile* root3  = new TFile("results/delpanj_diboson_signal_ZPrime_ZH_llWW_M1100.root");
  TFile* root4  = new TFile("results/delpanj_diboson_signal_ZPrime_ZH_llWW_M1200.root");
  TFile* root5  = new TFile("results/delpanj_diboson_signal_ZPrime_ZH_llWW_M1300.root");
  TFile* root6  = new TFile("results/delpanj_diboson_signal_ZPrime_ZH_llWW_M1400.root");
  TFile* root7  = new TFile("results/delpanj_diboson_signal_ZPrime_ZH_llWW_M1600.root");
  TFile* root8  = new TFile("results/delpanj_diboson_signal_ZPrime_ZH_llWW_M1700.root");
  TFile* root9  = new TFile("results/delpanj_diboson_signal_ZPrime_ZH_llWW_M1800.root");
  TFile* root10 = new TFile("results/delpanj_diboson_signal_ZPrime_ZH_llWW_M1900.root");



  TH1F* root1_genXPt       = (TH1F*)root1->Get("h_genXPt");
  TH1F* root1_genXY        = (TH1F*)root1->Get("h_genXY");
  TH1F* root1_genHPt       = (TH1F*)root1->Get("h_genHPt");  
  TH1F* root1_genHEta      = (TH1F*)root1->Get("h_genHEta");
  TH1F* root1_genZPt       = (TH1F*)root1->Get("h_genZPt");
  TH1F* root1_genZEta      = (TH1F*)root1->Get("h_genZEta");
  TH1F* root1_genZllDeltaR = (TH1F*)root1->Get("h_genZllDeltaR");

  TH1F* root2_genXPt       = (TH1F*)root2->Get("h_genXPt");
  TH1F* root2_genXY        = (TH1F*)root2->Get("h_genXY");
  TH1F* root2_genHPt       = (TH1F*)root2->Get("h_genHPt");  
  TH1F* root2_genHEta      = (TH1F*)root2->Get("h_genHEta");
  TH1F* root2_genZPt       = (TH1F*)root2->Get("h_genZPt");
  TH1F* root2_genZEta      = (TH1F*)root2->Get("h_genZEta");
  TH1F* root2_genZllDeltaR = (TH1F*)root2->Get("h_genZllDeltaR");

  TH1F* root3_genXPt       = (TH1F*)root3->Get("h_genXPt");
  TH1F* root3_genXY        = (TH1F*)root3->Get("h_genXY");
  TH1F* root3_genHPt       = (TH1F*)root3->Get("h_genHPt");  
  TH1F* root3_genHEta      = (TH1F*)root3->Get("h_genHEta");
  TH1F* root3_genZPt       = (TH1F*)root3->Get("h_genZPt");
  TH1F* root3_genZEta      = (TH1F*)root3->Get("h_genZEta");
  TH1F* root3_genZllDeltaR = (TH1F*)root3->Get("h_genZllDeltaR");

  TH1F* root4_genXPt       = (TH1F*)root4->Get("h_genXPt");
  TH1F* root4_genXY        = (TH1F*)root4->Get("h_genXY");
  TH1F* root4_genHPt       = (TH1F*)root4->Get("h_genHPt");  
  TH1F* root4_genHEta      = (TH1F*)root4->Get("h_genHEta");
  TH1F* root4_genZPt       = (TH1F*)root4->Get("h_genZPt");
  TH1F* root4_genZEta      = (TH1F*)root4->Get("h_genZEta");
  TH1F* root4_genZllDeltaR = (TH1F*)root4->Get("h_genZllDeltaR");

  TH1F* root5_genXPt       = (TH1F*)root5->Get("h_genXPt");
  TH1F* root5_genXY        = (TH1F*)root5->Get("h_genXY");
  TH1F* root5_genHPt       = (TH1F*)root5->Get("h_genHPt");  
  TH1F* root5_genHEta      = (TH1F*)root5->Get("h_genHEta");
  TH1F* root5_genZPt       = (TH1F*)root5->Get("h_genZPt");
  TH1F* root5_genZEta      = (TH1F*)root5->Get("h_genZEta");
  TH1F* root5_genZllDeltaR = (TH1F*)root5->Get("h_genZllDeltaR");

  TH1F* root6_genXPt       = (TH1F*)root6->Get("h_genXPt");
  TH1F* root6_genXY        = (TH1F*)root6->Get("h_genXY");
  TH1F* root6_genHPt       = (TH1F*)root6->Get("h_genHPt");  
  TH1F* root6_genHEta      = (TH1F*)root6->Get("h_genHEta");
  TH1F* root6_genZPt       = (TH1F*)root6->Get("h_genZPt");
  TH1F* root6_genZEta      = (TH1F*)root6->Get("h_genZEta");
  TH1F* root6_genZllDeltaR = (TH1F*)root6->Get("h_genZllDeltaR");

  TH1F* root7_genXPt       = (TH1F*)root7->Get("h_genXPt");
  TH1F* root7_genXY        = (TH1F*)root7->Get("h_genXY");
  TH1F* root7_genHPt       = (TH1F*)root7->Get("h_genHPt");  
  TH1F* root7_genHEta      = (TH1F*)root7->Get("h_genHEta");
  TH1F* root7_genZPt       = (TH1F*)root7->Get("h_genZPt");
  TH1F* root7_genZEta      = (TH1F*)root7->Get("h_genZEta");
  TH1F* root7_genZllDeltaR = (TH1F*)root7->Get("h_genZllDeltaR");

  TH1F* root8_genXPt       = (TH1F*)root8->Get("h_genXPt");
  TH1F* root8_genXY        = (TH1F*)root8->Get("h_genXY");
  TH1F* root8_genHPt       = (TH1F*)root8->Get("h_genHPt");  
  TH1F* root8_genHEta      = (TH1F*)root8->Get("h_genHEta");
  TH1F* root8_genZPt       = (TH1F*)root8->Get("h_genZPt");
  TH1F* root8_genZEta      = (TH1F*)root8->Get("h_genZEta");
  TH1F* root8_genZllDeltaR = (TH1F*)root8->Get("h_genZllDeltaR");

  TH1F* root9_genXPt       = (TH1F*)root9->Get("h_genXPt");
  TH1F* root9_genXY        = (TH1F*)root9->Get("h_genXY");
  TH1F* root9_genHPt       = (TH1F*)root9->Get("h_genHPt");  
  TH1F* root9_genHEta      = (TH1F*)root9->Get("h_genHEta");
  TH1F* root9_genZPt       = (TH1F*)root9->Get("h_genZPt");
  TH1F* root9_genZEta      = (TH1F*)root9->Get("h_genZEta");
  TH1F* root9_genZllDeltaR = (TH1F*)root9->Get("h_genZllDeltaR");

  TH1F* root10_genXPt       = (TH1F*)root10->Get("h_genXPt");
  TH1F* root10_genXY        = (TH1F*)root10->Get("h_genXY");
  TH1F* root10_genHPt       = (TH1F*)root10->Get("h_genHPt");  
  TH1F* root10_genHEta      = (TH1F*)root10->Get("h_genHEta");
  TH1F* root10_genZPt       = (TH1F*)root10->Get("h_genZPt");
  TH1F* root10_genZEta      = (TH1F*)root10->Get("h_genZEta");
  TH1F* root10_genZllDeltaR = (TH1F*)root10->Get("h_genZllDeltaR");




  root1_genXPt->SetLineColor(2);
  root2_genXPt->SetLineColor(3);
  root3_genXPt->SetLineColor(4);
  root4_genXPt->SetLineColor(5);
  root5_genXPt->SetLineColor(6);
  root6_genXPt->SetLineColor(7);
  root7_genXPt->SetLineColor(43);
  root8_genXPt->SetLineColor(9);
  root9_genXPt->SetLineColor(40);
  root10_genXPt->SetLineColor(32);
 

  root1_genXY->SetLineColor(2);
  root2_genXY->SetLineColor(3);
  root3_genXY->SetLineColor(4);
  root4_genXY->SetLineColor(5);
  root5_genXY->SetLineColor(6);
  root6_genXY->SetLineColor(7);
  root7_genXY->SetLineColor(43);
  root8_genXY->SetLineColor(9);
  root9_genXY->SetLineColor(40);
  root10_genXY->SetLineColor(32);



  root1_genHPt->SetLineColor(2);
  root2_genHPt->SetLineColor(3);
  root3_genHPt->SetLineColor(4);
  root4_genHPt->SetLineColor(5);
  root5_genHPt->SetLineColor(6);
  root6_genHPt->SetLineColor(7);
  root7_genHPt->SetLineColor(43);
  root8_genHPt->SetLineColor(9);
  root9_genHPt->SetLineColor(40);
  root10_genHPt->SetLineColor(32);


  root1_genHEta->SetLineColor(2);
  root2_genHEta->SetLineColor(3);
  root3_genHEta->SetLineColor(4);
  root4_genHEta->SetLineColor(5);
  root5_genHEta->SetLineColor(6);
  root6_genHEta->SetLineColor(7);
  root7_genHEta->SetLineColor(43);
  root8_genHEta->SetLineColor(9);
  root9_genHEta->SetLineColor(40);
  root10_genHEta->SetLineColor(32);


  root1_genZPt->SetLineColor(2);
  root2_genZPt->SetLineColor(3);
  root3_genZPt->SetLineColor(4);
  root4_genZPt->SetLineColor(5);
  root5_genZPt->SetLineColor(6);
  root6_genZPt->SetLineColor(7);
  root7_genZPt->SetLineColor(43);
  root8_genZPt->SetLineColor(9);
  root9_genZPt->SetLineColor(40);
  root10_genZPt->SetLineColor(32);


  root1_genZEta->SetLineColor(2);
  root2_genZEta->SetLineColor(3);
  root3_genZEta->SetLineColor(4);
  root4_genZEta->SetLineColor(5);
  root5_genZEta->SetLineColor(6);
  root6_genZEta->SetLineColor(7);
  root7_genZEta->SetLineColor(43);
  root8_genZEta->SetLineColor(9);
  root9_genZEta->SetLineColor(40);
  root10_genZEta->SetLineColor(32);
 

  root1_genZllDeltaR->SetLineColor(2);
  root2_genZllDeltaR->SetLineColor(3);
  root3_genZllDeltaR->SetLineColor(4);
  root4_genZllDeltaR->SetLineColor(5);
  root5_genZllDeltaR->SetLineColor(6);
  root6_genZllDeltaR->SetLineColor(7);
  root7_genZllDeltaR->SetLineColor(43);
  root8_genZllDeltaR->SetLineColor(9);
  root9_genZllDeltaR->SetLineColor(40);
  root10_genZllDeltaR->SetLineColor(32);

  
  gROOT->SetStyle("Plain");




  TCanvas *c1= new TCanvas("c1","",200,10,800,800);

  gStyle->SetOptStat(0);
  root1_genXPt->GetXaxis()->SetTitle("X P_{T} [GeV]");
  root1_genXPt->Draw();
  root2_genXPt->Draw("same");
  root3_genXPt->Draw("same");
  root4_genXPt->Draw("same");
  root5_genXPt->Draw("same");
  root6_genXPt->Draw("same");
  root7_genXPt->Draw("same");
  root8_genXPt->Draw("same");
  root9_genXPt->Draw("same");
  root10_genXPt->Draw("same");
 

  leg = new TLegend(0.7,0.67,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->AddEntry(root1_genXPt,"llWW_M800","L");
  leg->AddEntry(root2_genXPt,"llWW_M900","L");
  leg->AddEntry(root3_genXPt,"llWW_M1100","L");
  leg->AddEntry(root4_genXPt,"llWW_M1200","L");
  leg->AddEntry(root5_genXPt,"llWW_M1300","L");
  leg->AddEntry(root6_genXPt,"llWW_M14000","L");
  leg->AddEntry(root7_genXPt,"llWW_M1600","L");
  leg->AddEntry(root8_genXPt,"llWW_M1700","L");
  leg->AddEntry(root9_genXPt,"llWW_M1800","L");
  leg->AddEntry(root10_genXPt,"llWW_M1900","L");
  leg->Draw("same");


  gSystem->ProcessEvents();
  TImage *img1 = TImage::Create();
  img1->FromPad(c1);
  img1->WriteImage("h_genXPt.png");
  delete c1;
  delete img1;



  TCanvas *c2= new TCanvas("c2","",200,10,800,800);

  gStyle->SetOptStat(0);
  root10_genXY->GetXaxis()->SetTitle("X Rapidity");
  root10_genXY->Draw();
  root2_genXY->Draw("same");
  root3_genXY->Draw("same");
  root4_genXY->Draw("same");
  root5_genXY->Draw("same");
  root6_genXY->Draw("same");
  root7_genXY->Draw("same");
  root8_genXY->Draw("same");
  root9_genXY->Draw("same");
  root1_genXY->Draw("same");



  leg = new TLegend(0.7,0.67,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->AddEntry(root1_genXY,"llWW_M800","L");
  leg->AddEntry(root2_genXY,"llWW_M900","L");
  leg->AddEntry(root3_genXY,"llWW_M1100","L");
  leg->AddEntry(root4_genXY,"llWW_M1200","L");
  leg->AddEntry(root5_genXY,"llWW_M1300","L");
  leg->AddEntry(root6_genXY,"llWW_M14000","L");
  leg->AddEntry(root7_genXY,"llWW_M1600","L");
  leg->AddEntry(root8_genXY,"llWW_M1700","L");
  leg->AddEntry(root9_genXY,"llWW_M1800","L");
  leg->AddEntry(root10_genXY,"llWW_M1900","L");
  leg->Draw("same");


  gSystem->ProcessEvents();
  TImage *img2 = TImage::Create();
  img2->FromPad(c2);
  img2->WriteImage("h_genXY.png");
  delete c2;
  delete img2;




  TCanvas *c3= new TCanvas("c3","",200,10,800,800);

  gStyle->SetOptStat(0);
  root2_genHPt->GetXaxis()->SetTitle("H P_{T} [GeV]");
  root2_genHPt->Draw();
  root1_genHPt->Draw("same");
  root3_genHPt->Draw("same");
  root4_genHPt->Draw("same");
  root5_genHPt->Draw("same");
  root6_genHPt->Draw("same");
  root7_genHPt->Draw("same");
  root8_genHPt->Draw("same");
  root9_genHPt->Draw("same");
  root10_genHPt->Draw("same");
 

  leg = new TLegend(0.7,0.67,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->AddEntry(root1_genHPt,"llWW_M800","L");
  leg->AddEntry(root2_genHPt,"llWW_M900","L");
  leg->AddEntry(root3_genHPt,"llWW_M1100","L");
  leg->AddEntry(root4_genHPt,"llWW_M1200","L");
  leg->AddEntry(root5_genHPt,"llWW_M1300","L");
  leg->AddEntry(root6_genHPt,"llWW_M14000","L");
  leg->AddEntry(root7_genHPt,"llWW_M1600","L");
  leg->AddEntry(root8_genHPt,"llWW_M1700","L");
  leg->AddEntry(root9_genHPt,"llWW_M1800","L");
  leg->AddEntry(root10_genHPt,"llWW_M1900","L");
  leg->Draw("same");

  gSystem->ProcessEvents();
  TImage *img3 = TImage::Create();
  img3->FromPad(c3);
  img3->WriteImage("h_genHPt.png");
  delete c3;
  delete img3;




  TCanvas *c4= new TCanvas("c4","",200,10,800,800);

  gStyle->SetOptStat(0);
  root10_genHEta->GetXaxis()->SetTitle("H #eta");
  root10_genHEta->Draw();
  root2_genHEta->Draw("same");
  root3_genHEta->Draw("same");
  root4_genHEta->Draw("same");
  root5_genHEta->Draw("same");
  root6_genHEta->Draw("same");
  root7_genHEta->Draw("same");
  root8_genHEta->Draw("same");
  root9_genHEta->Draw("same");
  root1_genHEta->Draw("same");


 

  leg = new TLegend(0.7,0.67,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->AddEntry(root1_genHEta,"llWW_M800","L");
  leg->AddEntry(root2_genHEta,"llWW_M900","L");
  leg->AddEntry(root3_genHEta,"llWW_M1100","L");
  leg->AddEntry(root4_genHEta,"llWW_M1200","L");
  leg->AddEntry(root5_genHEta,"llWW_M1300","L");
  leg->AddEntry(root6_genHEta,"llWW_M14000","L");
  leg->AddEntry(root7_genHEta,"llWW_M1600","L");
  leg->AddEntry(root8_genHEta,"llWW_M1700","L");
  leg->AddEntry(root9_genHEta,"llWW_M1800","L");
  leg->AddEntry(root10_genHEta,"llWW_M1900","L");
  leg->Draw("same");

  gSystem->ProcessEvents();
  TImage *img4 = TImage::Create();
  img4->FromPad(c4);
  img4->WriteImage("h_genHEta.png");
  delete c4;
  delete img4;




  TCanvas *c5= new TCanvas("c5","",200,10,800,800);

  gStyle->SetOptStat(0);
  root2_genZPt->GetXaxis()->SetTitle("Z P_{T} [GeV]");
  root2_genZPt->Draw();
  root1_genZPt->Draw("same");
  root3_genZPt->Draw("same");
  root4_genZPt->Draw("same");
  root5_genZPt->Draw("same");
  root6_genZPt->Draw("same");
  root7_genZPt->Draw("same");
  root8_genZPt->Draw("same");
  root9_genZPt->Draw("same");
  root10_genZPt->Draw("same");
 

  leg = new TLegend(0.7,0.67,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->AddEntry(root1_genZPt,"llWW_M800","L");
  leg->AddEntry(root2_genZPt,"llWW_M900","L");
  leg->AddEntry(root3_genZPt,"llWW_M1100","L");
  leg->AddEntry(root4_genZPt,"llWW_M1200","L");
  leg->AddEntry(root5_genZPt,"llWW_M1300","L");
  leg->AddEntry(root6_genZPt,"llWW_M14000","L");
  leg->AddEntry(root7_genZPt,"llWW_M1600","L");
  leg->AddEntry(root8_genZPt,"llWW_M1700","L");
  leg->AddEntry(root9_genZPt,"llWW_M1800","L");
  leg->AddEntry(root10_genZPt,"llWW_M1900","L");
  leg->Draw("same");

  gSystem->ProcessEvents();
  TImage *img5 = TImage::Create();
  img5->FromPad(c5);
  img5->WriteImage("h_genZPt.png");
  delete c5;
  delete img5;




  TCanvas *c6= new TCanvas("c6","",200,10,800,800);

  gStyle->SetOptStat(0);
  root10_genZEta->GetXaxis()->SetTitle("Z #eta");
  root10_genZEta->Draw();
  root2_genZEta->Draw("same");
  root3_genZEta->Draw("same");
  root4_genZEta->Draw("same");
  root5_genZEta->Draw("same");
  root6_genZEta->Draw("same");
  root7_genZEta->Draw("same");
  root8_genZEta->Draw("same");
  root9_genZEta->Draw("same");
  root1_genZEta->Draw("same");


 

  leg = new TLegend(0.7,0.67,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->AddEntry(root1_genZEta,"llWW_M800","L");
  leg->AddEntry(root2_genZEta,"llWW_M900","L");
  leg->AddEntry(root3_genZEta,"llWW_M1100","L");
  leg->AddEntry(root4_genZEta,"llWW_M1200","L");
  leg->AddEntry(root5_genZEta,"llWW_M1300","L");
  leg->AddEntry(root6_genZEta,"llWW_M14000","L");
  leg->AddEntry(root7_genZEta,"llWW_M1600","L");
  leg->AddEntry(root8_genZEta,"llWW_M1700","L");
  leg->AddEntry(root9_genZEta,"llWW_M1800","L");
  leg->AddEntry(root10_genZEta,"llWW_M1900","L");
  leg->Draw("same");

  gSystem->ProcessEvents();
  TImage *img6 = TImage::Create();
  img6->FromPad(c6);
  img6->WriteImage("h_genZEta.png");
  delete c6;
  delete img6;




  TCanvas *c7= new TCanvas("c7","",200,10,800,800);

  gStyle->SetOptStat(0);
  root9_genZllDeltaR->GetXaxis()->SetTitle("#DeltaR_{ll}");
  root9_genZllDeltaR->Draw();
  root2_genZllDeltaR->Draw("same");
  root3_genZllDeltaR->Draw("same");
  root4_genZllDeltaR->Draw("same");
  root5_genZllDeltaR->Draw("same");
  root6_genZllDeltaR->Draw("same");
  root7_genZllDeltaR->Draw("same");
  root8_genZllDeltaR->Draw("same");
  root10_genZllDeltaR->Draw("same");
  root1_genZllDeltaR->Draw("same");
 


  leg = new TLegend(0.7,0.67,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->AddEntry(root1_genZllDeltaR,"llWW_M800","L");
  leg->AddEntry(root2_genZllDeltaR,"llWW_M900","L");
  leg->AddEntry(root3_genZllDeltaR,"llWW_M1100","L");
  leg->AddEntry(root4_genZllDeltaR,"llWW_M1200","L");
  leg->AddEntry(root5_genZllDeltaR,"llWW_M1300","L");
  leg->AddEntry(root6_genZllDeltaR,"llWW_M14000","L");
  leg->AddEntry(root7_genZllDeltaR,"llWW_M1600","L");
  leg->AddEntry(root8_genZllDeltaR,"llWW_M1700","L");
  leg->AddEntry(root9_genZllDeltaR,"llWW_M1800","L");
  leg->AddEntry(root10_genZllDeltaR,"llWW_M1900","L");
  leg->Draw("same");

  gSystem->ProcessEvents();
  TImage *img7 = TImage::Create();
  img7->FromPad(c7);
  img7->WriteImage("h_genZllDeltaR.png");
  delete c7;
  delete img7;

 

}
