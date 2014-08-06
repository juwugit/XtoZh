// root
// [] .L plot_ROC_wtag.cpp
// [] run()


void run()
{
  
  TFile * SIG  = new TFile("/home/juwu/XtoZh/results/delpanj_diboson_signal_ZPrime_hZ_qqll_LHC8_M1500_norm.root");   
  TFile * BKD  = new TFile("/home/juwu/XtoZh/results/delpanj_DYJetsToLL_PtZ-70_norm.root");  

  TH1F * DENOM_BKD  = (TH1F*)BKD->Get("h_CA8jetTau21cut"); 
  TH1F * DENOM_SIG  = (TH1F*)SIG->Get("h_CA8jetTau21cut"); 
  TH1F * NUMER_BKD  = (TH1F*)BKD->Get("h_CA8jetTau21cut");
  TH1F * NUMER_SIG  = (TH1F*)SIG->Get("h_CA8jetTau21cut");

  TGraphErrors * ROC1 = SigIntegrateUp(NUMER_BKD, DENOM_BKD, NUMER_SIG, DENOM_SIG);
  TGraphErrors * ROC2 = BkdIntegrateUp(NUMER_BKD, DENOM_BKD, NUMER_SIG, DENOM_SIG);


  ROC1->SetTitle("");
  ROC2->SetTitle("");
  ROC1->GetYaxis()->SetTitle("Efficiency");
  //ROC1->GetYaxis()->SetTitle("eff_sig/1+sqrt(B)");
  ROC1->GetYaxis()->SetTitleOffset(1.5);
  ROC1->SetLineColor(2);
  ROC2->SetLineColor(4);
  ROC1->SetMarkerStyle(20);
  ROC2->SetMarkerStyle(20);
  ROC1->SetLineWidth(2);
  ROC2->SetLineWidth(2);
  ROC1->GetXaxis()->SetTitle("#tau_{21} upper threshold");
  ROC2->GetXaxis()->SetTitle("#tau_{21} upper threshold");


  gROOT->SetStyle("Plain");
  TCanvas *c1= new TCanvas("c1","",200,10,800,800);

  ROC1->SetMarkerSize(2);
  ROC1->SetMarkerColor(2);
  ROC2->SetMarkerSize(2);
  ROC2->SetMarkerColor(4);
  ROC1->Draw("apc");
  ROC2->Draw("pc");

  
  leg = new TLegend(0.15,0.67,0.4,0.85);
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->AddEntry(ROC1,"Zprime_M1500","L");
  leg->AddEntry(ROC2,"Drell-Yan","L");
  leg->Draw("same");
  



}


TGraphErrors * SigIntegrateDown(TH1 * Numer_bkd, TH1 * Denom_bkd, TH1 * Numer_sig, TH1 * Denom_sig)
{
  double denom_sig = Denom_sig->Integral();
  int sig_nbinsx = Numer_sig->GetNbinsX();
  double *sig_eff = new double[sig_nbinsx];
  double *sig_nbincontent = new double[sig_nbinsx];
  double *sign = new double[sig_nbinsx];
  double *sig_ey = new double[sig_nbinsx] = 0;
  double *sig_ex = new double[sig_nbinsx] = 0;
  

  for (int i=1; i<=sig_nbinsx; i++ )
  {
    double numer_sig = Numer_sig->Integral(i,sig_nbinsx);
    double numer_bkd = Numer_bkd->Integral(i,sig_nbinsx);
    sig_nbincontent[i] = Numer_sig->GetXaxis()->GetBinCenter(i);

    if (denom_sig !=0 ) sig_eff[i]=numer_sig/denom_sig;
    sign[i]=sig_eff[i]/(1.0+sqrt(numer_bkd));

//    sig_ey[i] = pow(denom_sig,-1)*sqrt(pow(numer_sig,2)*(1-2/denom_sig)+numer_sig);
//    cout<<"sig_error:"<<sig_ey[i]<<endl;

  }


  TGraphErrors *g=new TGraphErrors(sig_nbinsx,sig_nbincontent,sign,sig_ex,sig_ey);
  return g;
}



TGraphErrors * BkdIntegrateDown(TH1 * Numer_bkd, TH1 * Denom_bkd, TH1 * Numer_sig, TH1 * Denom_sig)
{
  double denom_bkd = Denom_bkd->Integral();
  int bkd_nbinsx = Numer_bkd->GetNbinsX();
  double *bkd_eff = new double[bkd_nbinsx];
  double *bkd_nbincontent = new double[bkd_nbinsx];
  double *bkd_ey = new double[bkd_nbinsx] = 0;
  double *bkd_ex = new double[bkd_nbinsx] = 0;


  for (int i=1; i<=bkd_nbinsx; i++ )
  {
    double numer_bkd = Numer_bkd->Integral(i,bkd_nbinsx);
    bkd_nbincontent[i] = Numer_bkd->GetXaxis()->GetBinCenter(i);

    if (denom_bkd !=0 ) bkd_eff[i]=numer_bkd/denom_bkd;

  }


  TGraphErrors *g=new TGraphErrors(bkd_nbinsx,bkd_nbincontent,bkd_eff,bkd_ex,bkd_ey);
  return g;
}



TGraphErrors * SigIntegrateUp(TH1 * Numer_bkd, TH1 * Denom_bkd, TH1 * Numer_sig, TH1 * Denom_sig)
{

  double denom_sig = Denom_sig->Integral();
  int sig_nbinsx = Numer_sig->GetNbinsX();
  double *sig_eff = new double[sig_nbinsx];
  double *sig_nbincontent = new double[sig_nbinsx];
  double *sign = new double[sig_nbinsx];
  double *sig_ey = new double[sig_nbinsx] = 0;
  double *sig_ex = new double[sig_nbinsx] = 0;


  for (int i=1; i<=sig_nbinsx; i++ )
  {
    double numer_sig = Numer_sig->Integral(1,i);
    double numer_bkd = Numer_bkd->Integral(1,i);
    sig_nbincontent[i] = Numer_sig->GetXaxis()->GetBinCenter(i);

    if (denom_sig !=0 ) sig_eff[i]=numer_sig/denom_sig;
    sign[i]=sig_eff[i]/(1.0+sqrt(numer_bkd));

//    sig_ey[i] = pow(denom_sig,-1)*sqrt(pow(numer_sig,2)*(1-2/denom_sig)+numer_sig);
//    cout<<"sig_error:"<<sig_ey[i]<<endl;


  }


  TGraphErrors *g=new TGraphErrors(sig_nbinsx,sig_nbincontent,sig_eff,sig_ex,sig_ey);
  return g;
}


TGraphErrors * BkdIntegrateUp(TH1 * Numer_bkd, TH1 * Denom_bkd, TH1 * Numer_sig, TH1 * Denom_sig)
{

  double denom_bkd = Denom_bkd->Integral();
  int bkd_nbinsx = Numer_bkd->GetNbinsX();
  double *bkd_eff = new double[bkd_nbinsx];
  double *bkd_nbincontent = new double[bkd_nbinsx];
  double *bkd_ey = new double[bkd_nbinsx] = 0;
  double *bkd_ex = new double[bkd_nbinsx] = 0;


  for (int i=1; i<=bkd_nbinsx; i++ )
  {
    double numer_bkd = Numer_bkd->Integral(1,i);
    bkd_nbincontent[i] = Numer_bkd->GetXaxis()->GetBinCenter(i);

    if (denom_bkd !=0 ) bkd_eff[i]=numer_bkd/denom_bkd;

  }


  TGraphErrors *g=new TGraphErrors(bkd_nbinsx,bkd_nbincontent,bkd_eff,bkd_ex,bkd_ey);
  return g;
}

