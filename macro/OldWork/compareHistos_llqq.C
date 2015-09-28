// root
// [] .L plot_eff.cpp
// [] run()

void run()
{

  TFile* root1  = new TFile("results/delpanj_diboson_signal_ZPrime_hZ_qqll_LHC8_M1000.root");
  TFile* root2  = new TFile("results/delpanj_diboson_signal_ZPrime_hZ_qqll_LHC8_M1500.root");
  TFile* root3  = new TFile("results/delpanj_diboson_signal_ZPrime_hZ_qqll_LHC8_M2000.root");

  TH1F* root1_genXPt       = (TH1F*)root1->Get("h_genXPt");
  TH1F* root1_genXY        = (TH1F*)root1->Get("h_genXY");
  TH1F* root1_genHPt       = (TH1F*)root1->Get("h_genHPt");  
  TH1F* root1_genHEta      = (TH1F*)root1->Get("h_genHEta");
  TH1F* root1_genHqqDeltaR = (TH1F*)root1->Get("h_genHqqDeltaR");
  TH1F* root1_genZPt       = (TH1F*)root1->Get("h_genZPt");
  TH1F* root1_genZEta      = (TH1F*)root1->Get("h_genZEta");
  TH1F* root1_genZllDeltaR = (TH1F*)root1->Get("h_genZllDeltaR");

  TH1F* root2_genXPt       = (TH1F*)root2->Get("h_genXPt");
  TH1F* root2_genXY        = (TH1F*)root2->Get("h_genXY");
  TH1F* root2_genHPt       = (TH1F*)root2->Get("h_genHPt");  
  TH1F* root2_genHEta      = (TH1F*)root2->Get("h_genHEta");
  TH1F* root2_genHqqDeltaR = (TH1F*)root2->Get("h_genHqqDeltaR");
  TH1F* root2_genZPt       = (TH1F*)root2->Get("h_genZPt");
  TH1F* root2_genZEta      = (TH1F*)root2->Get("h_genZEta");
  TH1F* root2_genZllDeltaR = (TH1F*)root2->Get("h_genZllDeltaR");

  TH1F* root3_genXPt       = (TH1F*)root3->Get("h_genXPt");
  TH1F* root3_genXY        = (TH1F*)root3->Get("h_genXY");
  TH1F* root3_genHPt       = (TH1F*)root3->Get("h_genHPt");  
  TH1F* root3_genHEta      = (TH1F*)root3->Get("h_genHEta");
  TH1F* root3_genHqqDeltaR = (TH1F*)root3->Get("h_genHqqDeltaR");
  TH1F* root3_genZPt       = (TH1F*)root3->Get("h_genZPt");
  TH1F* root3_genZEta      = (TH1F*)root3->Get("h_genZEta");
  TH1F* root3_genZllDeltaR = (TH1F*)root3->Get("h_genZllDeltaR");



  root1_genXPt->SetLineColor(2);
  root2_genXPt->SetLineColor(4);
  root3_genXPt->SetLineColor(8);

  root1_genXY->SetLineColor(2);
  root2_genXY->SetLineColor(4);
  root3_genXY->SetLineColor(8);

  root1_genHPt->SetLineColor(2);
  root2_genHPt->SetLineColor(4);
  root3_genHPt->SetLineColor(8);

  root1_genHEta->SetLineColor(2);
  root2_genHEta->SetLineColor(4);
  root3_genHEta->SetLineColor(8);

  root1_genHqqDeltaR->SetLineColor(2);
  root2_genHqqDeltaR->SetLineColor(4);
  root3_genHqqDeltaR->SetLineColor(8);

  root1_genZPt->SetLineColor(2);
  root2_genZPt->SetLineColor(4);
  root3_genZPt->SetLineColor(8);

  root1_genZEta->SetLineColor(2);
  root2_genZEta->SetLineColor(4);
  root3_genZEta->SetLineColor(8);

  root1_genZllDeltaR->SetLineColor(2);
  root2_genZllDeltaR->SetLineColor(4);
  root3_genZllDeltaR->SetLineColor(8);


  
  gROOT->SetStyle("Plain");




  TCanvas *c1= new TCanvas("c1","",200,10,800,800);

  gStyle->SetOptStat(0);
  root1_genXPt->GetXaxis()->SetTitle("X P_{T} [GeV]");
  root2_genXPt->GetXaxis()->SetTitle("X P_{T} [GeV]");
  root3_genXPt->GetXaxis()->SetTitle("X P_{T} [GeV]");
  root1_genXPt->Draw();
  root2_genXPt->Draw("same");
  root3_genXPt->Draw("same");

  leg = new TLegend(0.7,0.8,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->AddEntry(root1_genXPt,"llqq_M1000","L");
  leg->AddEntry(root2_genXPt,"llqq_M1500","L");
  leg->AddEntry(root3_genXPt,"llqq_M2000","L");
  leg->Draw("same");

  gSystem->ProcessEvents();
  TImage *img1 = TImage::Create();
  img1->FromPad(c1);
  img1->WriteImage("h_genXPt.png");
  delete c1;
  delete img1;


  TCanvas *c2= new TCanvas("c2","",200,10,800,800);

  gStyle->SetOptStat(0);
  root1_genXY->GetXaxis()->SetTitle("X Rapidity");
  root2_genXY->GetXaxis()->SetTitle("X Rapidity");
  root3_genXY->GetXaxis()->SetTitle("X Rapidity");
  root3_genXY->Draw();
  root2_genXY->Draw("same");
  root1_genXY->Draw("same");

  leg = new TLegend(0.7,0.8,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->AddEntry(root1_genXY,"llqq_M1000","L");
  leg->AddEntry(root2_genXY,"llqq_M1500","L");
  leg->AddEntry(root3_genXY,"llqq_M2000","L");
  leg->Draw("same");

  gSystem->ProcessEvents();
  TImage *img2 = TImage::Create();
  img2->FromPad(c2);
  img2->WriteImage("h_genXY.png");
  delete c2;
  delete img2;




  TCanvas *c3= new TCanvas("c3","",200,10,800,800);

  gStyle->SetOptStat(0);
  root1_genHPt->GetXaxis()->SetTitle("H P_{T} [GeV]");
  root2_genHPt->GetXaxis()->SetTitle("H P_{T} [GeV]");
  root3_genHPt->GetXaxis()->SetTitle("H P_{T} [GeV]");
  root1_genHPt->Draw();
  root2_genHPt->Draw("same");
  root3_genHPt->Draw("same");

  leg = new TLegend(0.7,0.8,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->AddEntry(root1_genHPt,"llqq_M1000","L");
  leg->AddEntry(root2_genHPt,"llqq_M1500","L");
  leg->AddEntry(root3_genHPt,"llqq_M2000","L");
  leg->Draw("same");

  gSystem->ProcessEvents();
  TImage *img3 = TImage::Create();
  img3->FromPad(c3);
  img3->WriteImage("h_genHPt.png");
  delete c3;
  delete img3;




  TCanvas *c4= new TCanvas("c4","",200,10,800,800);

  gStyle->SetOptStat(0);
  root1_genHEta->GetXaxis()->SetTitle("H #eta");
  root2_genHEta->GetXaxis()->SetTitle("H #eta");
  root3_genHEta->GetXaxis()->SetTitle("H #eta");
  root3_genHEta->Draw();
  root2_genHEta->Draw("same");
  root1_genHEta->Draw("same");

  leg = new TLegend(0.7,0.8,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->AddEntry(root1_genHEta,"llqq_M1000","L");
  leg->AddEntry(root2_genHEta,"llqq_M1500","L");
  leg->AddEntry(root3_genHEta,"llqq_M2000","L");
  leg->Draw("same");

  gSystem->ProcessEvents();
  TImage *img4 = TImage::Create();
  img4->FromPad(c4);
  img4->WriteImage("h_genHEta.png");
  delete c4;
  delete img4;



  TCanvas *c5= new TCanvas("c5","",200,10,800,800);

  gStyle->SetOptStat(0);
  root1_genHqqDeltaR->GetXaxis()->SetTitle("#DeltaR_{qq}");
  root2_genHqqDeltaR->GetXaxis()->SetTitle("#DeltaR_{qq}");
  root3_genHqqDeltaR->GetXaxis()->SetTitle("#DeltaR_{qq}");
  root3_genHqqDeltaR->Draw();
  root2_genHqqDeltaR->Draw("same");
  root1_genHqqDeltaR->Draw("same");

  leg = new TLegend(0.7,0.8,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->AddEntry(root1_genHqqDeltaR,"llqq_M1000","L");
  leg->AddEntry(root2_genHqqDeltaR,"llqq_M1500","L");
  leg->AddEntry(root3_genHqqDeltaR,"llqq_M2000","L");
  leg->Draw("same");

  gSystem->ProcessEvents();
  TImage *img5 = TImage::Create();
  img5->FromPad(c5);
  img5->WriteImage("h_genHqqDeltaR.png");
  delete c5;
  delete img5;




  TCanvas *c6= new TCanvas("c6","",200,10,800,800);

  gStyle->SetOptStat(0);
  root1_genZPt->GetXaxis()->SetTitle("Z P_{T} [GeV]");
  root2_genZPt->GetXaxis()->SetTitle("Z P_{T} [GeV]");
  root3_genZPt->GetXaxis()->SetTitle("Z P_{T} [GeV]");
  root1_genZPt->Draw();
  root2_genZPt->Draw("same");
  root3_genZPt->Draw("same");

  leg = new TLegend(0.7,0.8,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->AddEntry(root1_genZPt,"llqq_M1000","L");
  leg->AddEntry(root2_genZPt,"llqq_M1500","L");
  leg->AddEntry(root3_genZPt,"llqq_M2000","L");
  leg->Draw("same");

  gSystem->ProcessEvents();
  TImage *img6 = TImage::Create();
  img6->FromPad(c6);
  img6->WriteImage("h_genZPt.png");
  delete c6;
  delete img6;




  TCanvas *c7= new TCanvas("c7","",200,10,800,800);

  gStyle->SetOptStat(0);
  root1_genZEta->GetXaxis()->SetTitle("Z #eta");
  root2_genZEta->GetXaxis()->SetTitle("Z #eta");
  root3_genZEta->GetXaxis()->SetTitle("Z #eta");
  root3_genZEta->Draw();
  root2_genZEta->Draw("same");
  root1_genZEta->Draw("same");

  leg = new TLegend(0.7,0.8,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->AddEntry(root1_genZEta,"llqq_M1000","L");
  leg->AddEntry(root2_genZEta,"llqq_M1500","L");
  leg->AddEntry(root3_genZEta,"llqq_M2000","L");
  leg->Draw("same");

  gSystem->ProcessEvents();
  TImage *img7 = TImage::Create();
  img7->FromPad(c7);
  img7->WriteImage("h_genZEta.png");
  delete c7;
  delete img7;



  TCanvas *c8= new TCanvas("c8","",200,10,800,800);

  gStyle->SetOptStat(0);
  root1_genZllDeltaR->GetXaxis()->SetTitle("#DeltaR_{ll}");
  root2_genZllDeltaR->GetXaxis()->SetTitle("#DeltaR_{ll}");
  root3_genZllDeltaR->GetXaxis()->SetTitle("#DeltaR_{ll}");
  root3_genZllDeltaR->Draw();
  root2_genZllDeltaR->Draw("same");
  root1_genZllDeltaR->Draw("same");

  leg = new TLegend(0.7,0.8,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->AddEntry(root1_genZllDeltaR,"llqq_M1000","L");
  leg->AddEntry(root2_genZllDeltaR,"llqq_M1500","L");
  leg->AddEntry(root3_genZllDeltaR,"llqq_M2000","L");
  leg->Draw("same");

  gSystem->ProcessEvents();
  TImage *img8 = TImage::Create();
  img8->FromPad(c8);
  img8->WriteImage("h_genZllDeltaR.png");
  delete c8;
  delete img8;

}
