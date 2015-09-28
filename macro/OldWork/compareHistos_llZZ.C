// root
// [] .L plot_eff.cpp
// [] run()

void run()
{

  TFile* root1  = new TFile("results/delpanj_diboson_signal_ZPrime_ZH_llZZ_M1000.root");
  TFile* root2  = new TFile("results/delpanj_diboson_signal_ZPrime_ZH_llZZ_M1100.root");
  TFile* root3  = new TFile("results/delpanj_diboson_signal_ZPrime_ZH_llZZ_M1200.root");
  TFile* root4  = new TFile("results/delpanj_diboson_signal_ZPrime_ZH_llZZ_M1300.root");
  TFile* root5  = new TFile("results/delpanj_diboson_signal_ZPrime_ZH_llZZ_M1400.root");
  TFile* root6  = new TFile("results/delpanj_diboson_signal_ZPrime_ZH_llZZ_M1500.root");
  TFile* root7  = new TFile("results/delpanj_diboson_signal_ZPrime_ZH_llZZ_M1600.root");
  TFile* root8  = new TFile("results/delpanj_diboson_signal_ZPrime_ZH_llZZ_M1700.root");
  TFile* root9  = new TFile("results/delpanj_diboson_signal_ZPrime_ZH_llZZ_M1800.root");
  TFile* root10 = new TFile("results/delpanj_diboson_signal_ZPrime_ZH_llZZ_M1900.root");



  TH1F* root1_XPt       = (TH1F*)root1->Get("h_XPt");
  TH1F* root1_XY        = (TH1F*)root1->Get("h_XY");
  TH1F* root1_HPt       = (TH1F*)root1->Get("h_HPt");  
  TH1F* root1_HEta      = (TH1F*)root1->Get("h_HEta");
  TH1F* root1_HdddeltaR = (TH1F*)root1->Get("h_HdddeltaR");
  TH1F* root1_ZPt       = (TH1F*)root1->Get("h_ZPt");
  TH1F* root1_ZEta      = (TH1F*)root1->Get("h_ZEta");
  TH1F* root1_ZlldeltaR = (TH1F*)root1->Get("h_ZlldeltaR");

  TH1F* root2_XPt       = (TH1F*)root2->Get("h_XPt");
  TH1F* root2_XY        = (TH1F*)root2->Get("h_XY");
  TH1F* root2_HPt       = (TH1F*)root2->Get("h_HPt");  
  TH1F* root2_HEta      = (TH1F*)root2->Get("h_HEta");
  TH1F* root2_HdddeltaR = (TH1F*)root2->Get("h_HdddeltaR");
  TH1F* root2_ZPt       = (TH1F*)root2->Get("h_ZPt");
  TH1F* root2_ZEta      = (TH1F*)root2->Get("h_ZEta");
  TH1F* root2_ZlldeltaR = (TH1F*)root2->Get("h_ZlldeltaR");

  TH1F* root3_XPt       = (TH1F*)root3->Get("h_XPt");
  TH1F* root3_XY        = (TH1F*)root3->Get("h_XY");
  TH1F* root3_HPt       = (TH1F*)root3->Get("h_HPt");  
  TH1F* root3_HEta      = (TH1F*)root3->Get("h_HEta");
  TH1F* root3_HdddeltaR = (TH1F*)root3->Get("h_HdddeltaR");
  TH1F* root3_ZPt       = (TH1F*)root3->Get("h_ZPt");
  TH1F* root3_ZEta      = (TH1F*)root3->Get("h_ZEta");
  TH1F* root3_ZlldeltaR = (TH1F*)root3->Get("h_ZlldeltaR");

  TH1F* root4_XPt       = (TH1F*)root4->Get("h_XPt");
  TH1F* root4_XY        = (TH1F*)root4->Get("h_XY");
  TH1F* root4_HPt       = (TH1F*)root4->Get("h_HPt");  
  TH1F* root4_HEta      = (TH1F*)root4->Get("h_HEta");
  TH1F* root4_HdddeltaR = (TH1F*)root4->Get("h_HdddeltaR");
  TH1F* root4_ZPt       = (TH1F*)root4->Get("h_ZPt");
  TH1F* root4_ZEta      = (TH1F*)root4->Get("h_ZEta");
  TH1F* root4_ZlldeltaR = (TH1F*)root4->Get("h_ZlldeltaR");

  TH1F* root5_XPt       = (TH1F*)root5->Get("h_XPt");
  TH1F* root5_XY        = (TH1F*)root5->Get("h_XY");
  TH1F* root5_HPt       = (TH1F*)root5->Get("h_HPt");  
  TH1F* root5_HEta      = (TH1F*)root5->Get("h_HEta");
  TH1F* root5_HdddeltaR = (TH1F*)root5->Get("h_HdddeltaR");
  TH1F* root5_ZPt       = (TH1F*)root5->Get("h_ZPt");
  TH1F* root5_ZEta      = (TH1F*)root5->Get("h_ZEta");
  TH1F* root5_ZlldeltaR = (TH1F*)root5->Get("h_ZlldeltaR");

  TH1F* root6_XPt       = (TH1F*)root6->Get("h_XPt");
  TH1F* root6_XY        = (TH1F*)root6->Get("h_XY");
  TH1F* root6_HPt       = (TH1F*)root6->Get("h_HPt");  
  TH1F* root6_HEta      = (TH1F*)root6->Get("h_HEta");
  TH1F* root6_HdddeltaR = (TH1F*)root6->Get("h_HdddeltaR");
  TH1F* root6_ZPt       = (TH1F*)root6->Get("h_ZPt");
  TH1F* root6_ZEta      = (TH1F*)root6->Get("h_ZEta");
  TH1F* root6_ZlldeltaR = (TH1F*)root6->Get("h_ZlldeltaR");

  TH1F* root7_XPt       = (TH1F*)root7->Get("h_XPt");
  TH1F* root7_XY        = (TH1F*)root7->Get("h_XY");
  TH1F* root7_HPt       = (TH1F*)root7->Get("h_HPt");  
  TH1F* root7_HEta      = (TH1F*)root7->Get("h_HEta");
  TH1F* root7_HdddeltaR = (TH1F*)root7->Get("h_HdddeltaR");
  TH1F* root7_ZPt       = (TH1F*)root7->Get("h_ZPt");
  TH1F* root7_ZEta      = (TH1F*)root7->Get("h_ZEta");
  TH1F* root7_ZlldeltaR = (TH1F*)root7->Get("h_ZlldeltaR");

  TH1F* root8_XPt       = (TH1F*)root8->Get("h_XPt");
  TH1F* root8_XY        = (TH1F*)root8->Get("h_XY");
  TH1F* root8_HPt       = (TH1F*)root8->Get("h_HPt");  
  TH1F* root8_HEta      = (TH1F*)root8->Get("h_HEta");
  TH1F* root8_HdddeltaR = (TH1F*)root8->Get("h_HdddeltaR");
  TH1F* root8_ZPt       = (TH1F*)root8->Get("h_ZPt");
  TH1F* root8_ZEta      = (TH1F*)root8->Get("h_ZEta");
  TH1F* root8_ZlldeltaR = (TH1F*)root8->Get("h_ZlldeltaR");

  TH1F* root9_XPt       = (TH1F*)root9->Get("h_XPt");
  TH1F* root9_XY        = (TH1F*)root9->Get("h_XY");
  TH1F* root9_HPt       = (TH1F*)root9->Get("h_HPt");  
  TH1F* root9_HEta      = (TH1F*)root9->Get("h_HEta");
  TH1F* root9_HdddeltaR = (TH1F*)root9->Get("h_HdddeltaR");
  TH1F* root9_ZPt       = (TH1F*)root9->Get("h_ZPt");
  TH1F* root9_ZEta      = (TH1F*)root9->Get("h_ZEta");
  TH1F* root9_ZlldeltaR = (TH1F*)root9->Get("h_ZlldeltaR");

  TH1F* root10_XPt       = (TH1F*)root10->Get("h_XPt");
  TH1F* root10_XY        = (TH1F*)root10->Get("h_XY");
  TH1F* root10_HPt       = (TH1F*)root10->Get("h_HPt");  
  TH1F* root10_HEta      = (TH1F*)root10->Get("h_HEta");
  TH1F* root10_HdddeltaR = (TH1F*)root10->Get("h_HdddeltaR");
  TH1F* root10_ZPt       = (TH1F*)root10->Get("h_ZPt");
  TH1F* root10_ZEta      = (TH1F*)root10->Get("h_ZEta");
  TH1F* root10_ZlldeltaR = (TH1F*)root10->Get("h_ZlldeltaR");




  root1_XPt->SetLineColor(2);
  root2_XPt->SetLineColor(3);
  root3_XPt->SetLineColor(4);
  root4_XPt->SetLineColor(5);
  root5_XPt->SetLineColor(6);
  root6_XPt->SetLineColor(7);
  root7_XPt->SetLineColor(43);
  root8_XPt->SetLineColor(9);
  root9_XPt->SetLineColor(40);
  root10_XPt->SetLineColor(32);
 

  root1_XY->SetLineColor(2);
  root2_XY->SetLineColor(3);
  root3_XY->SetLineColor(4);
  root4_XY->SetLineColor(5);
  root5_XY->SetLineColor(6);
  root6_XY->SetLineColor(7);
  root7_XY->SetLineColor(43);
  root8_XY->SetLineColor(9);
  root9_XY->SetLineColor(40);
  root10_XY->SetLineColor(32);



  root1_HPt->SetLineColor(2);
  root2_HPt->SetLineColor(3);
  root3_HPt->SetLineColor(4);
  root4_HPt->SetLineColor(5);
  root5_HPt->SetLineColor(6);
  root6_HPt->SetLineColor(7);
  root7_HPt->SetLineColor(43);
  root8_HPt->SetLineColor(9);
  root9_HPt->SetLineColor(40);
  root10_HPt->SetLineColor(32);


  root1_HEta->SetLineColor(2);
  root2_HEta->SetLineColor(3);
  root3_HEta->SetLineColor(4);
  root4_HEta->SetLineColor(5);
  root5_HEta->SetLineColor(6);
  root6_HEta->SetLineColor(7);
  root7_HEta->SetLineColor(43);
  root8_HEta->SetLineColor(9);
  root9_HEta->SetLineColor(40);
  root10_HEta->SetLineColor(32);
 

  root1_HdddeltaR->SetLineColor(2);
  root2_HdddeltaR->SetLineColor(3);
  root3_HdddeltaR->SetLineColor(4);
  root4_HdddeltaR->SetLineColor(5);
  root5_HdddeltaR->SetLineColor(6);
  root6_HdddeltaR->SetLineColor(7);
  root7_HdddeltaR->SetLineColor(43);
  root8_HdddeltaR->SetLineColor(9);
  root9_HdddeltaR->SetLineColor(40);
  root10_HdddeltaR->SetLineColor(32);

  root1_ZPt->SetLineColor(2);
  root2_ZPt->SetLineColor(3);
  root3_ZPt->SetLineColor(4);
  root4_ZPt->SetLineColor(5);
  root5_ZPt->SetLineColor(6);
  root6_ZPt->SetLineColor(7);
  root7_ZPt->SetLineColor(43);
  root8_ZPt->SetLineColor(9);
  root9_ZPt->SetLineColor(40);
  root10_ZPt->SetLineColor(32);


  root1_ZEta->SetLineColor(2);
  root2_ZEta->SetLineColor(3);
  root3_ZEta->SetLineColor(4);
  root4_ZEta->SetLineColor(5);
  root5_ZEta->SetLineColor(6);
  root6_ZEta->SetLineColor(7);
  root7_ZEta->SetLineColor(43);
  root8_ZEta->SetLineColor(9);
  root9_ZEta->SetLineColor(40);
  root10_ZEta->SetLineColor(32);
 

  root1_ZlldeltaR->SetLineColor(2);
  root2_ZlldeltaR->SetLineColor(3);
  root3_ZlldeltaR->SetLineColor(4);
  root4_ZlldeltaR->SetLineColor(5);
  root5_ZlldeltaR->SetLineColor(6);
  root6_ZlldeltaR->SetLineColor(7);
  root7_ZlldeltaR->SetLineColor(43);
  root8_ZlldeltaR->SetLineColor(9);
  root9_ZlldeltaR->SetLineColor(40);
  root10_ZlldeltaR->SetLineColor(32);

  
  gROOT->SetStyle("Plain");




  TCanvas *c1= new TCanvas("c1","",200,10,800,800);

  gStyle->SetOptStat(0);
  root1_XPt->GetXaxis()->SetTitle("X P_{T} [GeV]");
  root1_XPt->Draw();
  root2_XPt->Draw("same");
  root3_XPt->Draw("same");
  root4_XPt->Draw("same");
  root5_XPt->Draw("same");
  root6_XPt->Draw("same");
  root7_XPt->Draw("same");
  root8_XPt->Draw("same");
  root9_XPt->Draw("same");
  root10_XPt->Draw("same");
 

  leg = new TLegend(0.7,0.67,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->AddEntry(root1_XPt,"llZZ_M1000","L");
  leg->AddEntry(root2_XPt,"llZZ_M1100","L");
  leg->AddEntry(root3_XPt,"llZZ_M1200","L");
  leg->AddEntry(root4_XPt,"llZZ_M1300","L");
  leg->AddEntry(root5_XPt,"llZZ_M1400","L");
  leg->AddEntry(root6_XPt,"llZZ_M1500","L");
  leg->AddEntry(root7_XPt,"llZZ_M1600","L");
  leg->AddEntry(root8_XPt,"llZZ_M1700","L");
  leg->AddEntry(root9_XPt,"llZZ_M1800","L");
  leg->AddEntry(root10_XPt,"llZZ_M1900","L");
  leg->Draw("same");


  gSystem->ProcessEvents();
  TImage *img1 = TImage::Create();
  img1->FromPad(c1);
  img1->WriteImage("canvas1.png");
  delete c1;
  delete img1;



  TCanvas *c2= new TCanvas("c2","",200,10,800,800);

  gStyle->SetOptStat(0);
  root10_XY->GetXaxis()->SetTitle("X Rapidity");
  root10_XY->Draw();
  root2_XY->Draw("same");
  root3_XY->Draw("same");
  root4_XY->Draw("same");
  root5_XY->Draw("same");
  root6_XY->Draw("same");
  root7_XY->Draw("same");
  root8_XY->Draw("same");
  root9_XY->Draw("same");
  root1_XY->Draw("same");



  leg = new TLegend(0.7,0.67,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->AddEntry(root1_XY,"llZZ_M1000","L");
  leg->AddEntry(root2_XY,"llZZ_M1100","L");
  leg->AddEntry(root3_XY,"llZZ_M1200","L");
  leg->AddEntry(root4_XY,"llZZ_M1300","L");
  leg->AddEntry(root5_XY,"llZZ_M1400","L");
  leg->AddEntry(root6_XY,"llZZ_M1500","L");
  leg->AddEntry(root7_XY,"llZZ_M1600","L");
  leg->AddEntry(root8_XY,"llZZ_M1700","L");
  leg->AddEntry(root9_XY,"llZZ_M1800","L");
  leg->AddEntry(root10_XY,"llZZ_M1900","L");
  leg->Draw("same");


  gSystem->ProcessEvents();
  TImage *img2 = TImage::Create();
  img2->FromPad(c2);
  img2->WriteImage("canvas2.png");
  delete c2;
  delete img2;




  TCanvas *c3= new TCanvas("c3","",200,10,800,800);

  gStyle->SetOptStat(0);
  root2_HPt->GetXaxis()->SetTitle("H P_{T} [GeV]");
  root2_HPt->Draw();
  root1_HPt->Draw("same");
  root3_HPt->Draw("same");
  root4_HPt->Draw("same");
  root5_HPt->Draw("same");
  root6_HPt->Draw("same");
  root7_HPt->Draw("same");
  root8_HPt->Draw("same");
  root9_HPt->Draw("same");
  root10_HPt->Draw("same");
 

  leg = new TLegend(0.7,0.67,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->AddEntry(root1_HPt,"llZZ_M1000","L");
  leg->AddEntry(root2_HPt,"llZZ_M1100","L");
  leg->AddEntry(root3_HPt,"llZZ_M1200","L");
  leg->AddEntry(root4_HPt,"llZZ_M1300","L");
  leg->AddEntry(root5_HPt,"llZZ_M1400","L");
  leg->AddEntry(root6_HPt,"llZZ_M1500","L");
  leg->AddEntry(root7_HPt,"llZZ_M1600","L");
  leg->AddEntry(root8_HPt,"llZZ_M1700","L");
  leg->AddEntry(root9_HPt,"llZZ_M1800","L");
  leg->AddEntry(root10_HPt,"llZZ_M1900","L");
  leg->Draw("same");

  gSystem->ProcessEvents();
  TImage *img3 = TImage::Create();
  img3->FromPad(c3);
  img3->WriteImage("canvas3.png");
  delete c3;
  delete img3;




  TCanvas *c4= new TCanvas("c4","",200,10,800,800);

  gStyle->SetOptStat(0);
  root10_HEta->GetXaxis()->SetTitle("H #eta");
  root10_HEta->Draw();
  root2_HEta->Draw("same");
  root3_HEta->Draw("same");
  root4_HEta->Draw("same");
  root5_HEta->Draw("same");
  root6_HEta->Draw("same");
  root7_HEta->Draw("same");
  root8_HEta->Draw("same");
  root9_HEta->Draw("same");
  root1_HEta->Draw("same");


 

  leg = new TLegend(0.7,0.67,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->AddEntry(root1_HEta,"llZZ_M1000","L");
  leg->AddEntry(root2_HEta,"llZZ_M1100","L");
  leg->AddEntry(root3_HEta,"llZZ_M1200","L");
  leg->AddEntry(root4_HEta,"llZZ_M1300","L");
  leg->AddEntry(root5_HEta,"llZZ_M1400","L");
  leg->AddEntry(root6_HEta,"llZZ_M1500","L");
  leg->AddEntry(root7_HEta,"llZZ_M1600","L");
  leg->AddEntry(root8_HEta,"llZZ_M1700","L");
  leg->AddEntry(root9_HEta,"llZZ_M1800","L");
  leg->AddEntry(root10_HEta,"llZZ_M1900","L");
  leg->Draw("same");

  gSystem->ProcessEvents();
  TImage *img4 = TImage::Create();
  img4->FromPad(c4);
  img4->WriteImage("canvas4.png");
  delete c4;
  delete img4;




  TCanvas *c5= new TCanvas("c5","",200,10,800,800);

  gStyle->SetOptStat(0);
  root10_HdddeltaR->GetXaxis()->SetTitle("#DeltaR_{ZZ}");
  root10_HdddeltaR->Draw();
  root2_HdddeltaR->Draw("same");
  root3_HdddeltaR->Draw("same");
  root4_HdddeltaR->Draw("same");
  root5_HdddeltaR->Draw("same");
  root6_HdddeltaR->Draw("same");
  root7_HdddeltaR->Draw("same");
  root8_HdddeltaR->Draw("same");
  root9_HdddeltaR->Draw("same");
  root1_HdddeltaR->Draw("same");
 


  leg = new TLegend(0.7,0.67,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->AddEntry(root1_HdddeltaR,"llZZ_M1000","L");
  leg->AddEntry(root2_HdddeltaR,"llZZ_M1100","L");
  leg->AddEntry(root3_HdddeltaR,"llZZ_M1200","L");
  leg->AddEntry(root4_HdddeltaR,"llZZ_M1300","L");
  leg->AddEntry(root5_HdddeltaR,"llZZ_M1400","L");
  leg->AddEntry(root6_HdddeltaR,"llZZ_M1500","L");
  leg->AddEntry(root7_HdddeltaR,"llZZ_M1600","L");
  leg->AddEntry(root8_HdddeltaR,"llZZ_M1700","L");
  leg->AddEntry(root9_HdddeltaR,"llZZ_M1800","L");
  leg->AddEntry(root10_HdddeltaR,"llZZ_M1900","L");
  leg->Draw("same");

  gSystem->ProcessEvents();
  TImage *img5 = TImage::Create();
  img5->FromPad(c5);
  img5->WriteImage("canvas5.png");
  delete c5;
  delete img5;


  TCanvas *c6= new TCanvas("c6","",200,10,800,800);

  gStyle->SetOptStat(0);
  root2_ZPt->GetXaxis()->SetTitle("Z P_{T} [GeV]");
  root2_ZPt->Draw();
  root1_ZPt->Draw("same");
  root3_ZPt->Draw("same");
  root4_ZPt->Draw("same");
  root5_ZPt->Draw("same");
  root6_ZPt->Draw("same");
  root7_ZPt->Draw("same");
  root8_ZPt->Draw("same");
  root9_ZPt->Draw("same");
  root10_ZPt->Draw("same");
 

  leg = new TLegend(0.7,0.67,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->AddEntry(root1_ZPt,"llZZ_M1000","L");
  leg->AddEntry(root2_ZPt,"llZZ_M1100","L");
  leg->AddEntry(root3_ZPt,"llZZ_M1200","L");
  leg->AddEntry(root4_ZPt,"llZZ_M1300","L");
  leg->AddEntry(root5_ZPt,"llZZ_M1400","L");
  leg->AddEntry(root6_ZPt,"llZZ_M1500","L");
  leg->AddEntry(root7_ZPt,"llZZ_M1600","L");
  leg->AddEntry(root8_ZPt,"llZZ_M1700","L");
  leg->AddEntry(root9_ZPt,"llZZ_M1800","L");
  leg->AddEntry(root10_ZPt,"llZZ_M1900","L");
  leg->Draw("same");

  gSystem->ProcessEvents();
  TImage *img6 = TImage::Create();
  img6->FromPad(c6);
  img6->WriteImage("canvas6.png");
  delete c6;
  delete img6;




  TCanvas *c7= new TCanvas("c7","",200,10,800,800);

  gStyle->SetOptStat(0);
  root9_ZEta->GetXaxis()->SetTitle("Z #eta");
  root9_ZEta->Draw();
  root2_ZEta->Draw("same");
  root3_ZEta->Draw("same");
  root4_ZEta->Draw("same");
  root5_ZEta->Draw("same");
  root6_ZEta->Draw("same");
  root7_ZEta->Draw("same");
  root8_ZEta->Draw("same");
  root10_ZEta->Draw("same");
  root1_ZEta->Draw("same");


 

  leg = new TLegend(0.7,0.67,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->AddEntry(root1_ZEta,"llZZ_M1000","L");
  leg->AddEntry(root2_ZEta,"llZZ_M1100","L");
  leg->AddEntry(root3_ZEta,"llZZ_M1200","L");
  leg->AddEntry(root4_ZEta,"llZZ_M1300","L");
  leg->AddEntry(root5_ZEta,"llZZ_M1400","L");
  leg->AddEntry(root6_ZEta,"llZZ_M1500","L");
  leg->AddEntry(root7_ZEta,"llZZ_M1600","L");
  leg->AddEntry(root8_ZEta,"llZZ_M1700","L");
  leg->AddEntry(root9_ZEta,"llZZ_M1800","L");
  leg->AddEntry(root10_ZEta,"llZZ_M1900","L");
  leg->Draw("same");

  gSystem->ProcessEvents();
  TImage *img7 = TImage::Create();
  img7->FromPad(c7);
  img7->WriteImage("canvas7.png");
  delete c7;
  delete img7;




  TCanvas *c8= new TCanvas("c8","",200,10,800,800);

  gStyle->SetOptStat(0);
  root9_ZlldeltaR->GetXaxis()->SetTitle("#DeltaR_{ll}");
  root9_ZlldeltaR->Draw();
  root2_ZlldeltaR->Draw("same");
  root3_ZlldeltaR->Draw("same");
  root4_ZlldeltaR->Draw("same");
  root5_ZlldeltaR->Draw("same");
  root6_ZlldeltaR->Draw("same");
  root7_ZlldeltaR->Draw("same");
  root8_ZlldeltaR->Draw("same");
  root10_ZlldeltaR->Draw("same");
  root1_ZlldeltaR->Draw("same");
 


  leg = new TLegend(0.7,0.67,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->AddEntry(root1_ZlldeltaR,"llZZ_M1000","L");
  leg->AddEntry(root2_ZlldeltaR,"llZZ_M1100","L");
  leg->AddEntry(root3_ZlldeltaR,"llZZ_M1200","L");
  leg->AddEntry(root4_ZlldeltaR,"llZZ_M1300","L");
  leg->AddEntry(root5_ZlldeltaR,"llZZ_M1400","L");
  leg->AddEntry(root6_ZlldeltaR,"llZZ_M1500","L");
  leg->AddEntry(root7_ZlldeltaR,"llZZ_M1600","L");
  leg->AddEntry(root8_ZlldeltaR,"llZZ_M1700","L");
  leg->AddEntry(root9_ZlldeltaR,"llZZ_M1800","L");
  leg->AddEntry(root10_ZlldeltaR,"llZZ_M1900","L");
  leg->Draw("same");

  gSystem->ProcessEvents();
  TImage *img8 = TImage::Create();
  img8->FromPad(c8);
  img8->WriteImage("canvas8.png");
  delete c8;
  delete img8;

 

}
