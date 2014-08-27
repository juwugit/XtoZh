// root
// [] .L plot_ROC_wtag.cpp
// [] run()


void run()
{
  

  TFile* BKD  = new TFile("results/norm_delpanj_v2_background_M900.root");  
  TFile* SIG  = new TFile("results/norm_delpanj_v2_ZPrime_ZH_llWW_M900.root");   

  TH1F* DENOM_BKD1  = (TH1F*)BKD->Get("h_CA8jetTau21cut"); 
  TH1F* NUMER_BKD1  = (TH1F*)BKD->Get("h_CA8jetTau21cut");
  TH1F* DENOM_BKD2  = (TH1F*)BKD->Get("h_CA8jetTau31cut");
  TH1F* NUMER_BKD2  = (TH1F*)BKD->Get("h_CA8jetTau31cut");
  TH1F* DENOM_BKD3  = (TH1F*)BKD->Get("h_CA8jetTau41cut");
  TH1F* NUMER_BKD3  = (TH1F*)BKD->Get("h_CA8jetTau41cut");

  TH1F* NUMER_SIG1  = (TH1F*)SIG->Get("h_CA8jetTau21cut");
  TH1F* DENOM_SIG1  = (TH1F*)SIG->Get("h_CA8jetTau21cut"); 
  TH1F* NUMER_SIG2  = (TH1F*)SIG->Get("h_CA8jetTau31cut");
  TH1F* DENOM_SIG2  = (TH1F*)SIG->Get("h_CA8jetTau31cut");
  TH1F* NUMER_SIG3  = (TH1F*)SIG->Get("h_CA8jetTau41cut");
  TH1F* DENOM_SIG3  = (TH1F*)SIG->Get("h_CA8jetTau41cut");





  TGraphErrors* ROC1 = SigIntegrateUp(NUMER_BKD1, DENOM_BKD1, NUMER_SIG1, DENOM_SIG1);
  TGraphErrors* ROC2 = SigIntegrateUp(NUMER_BKD2, DENOM_BKD2, NUMER_SIG2, DENOM_SIG2);
  TGraphErrors* ROC3 = SigIntegrateUp(NUMER_BKD3, DENOM_BKD3, NUMER_SIG3, DENOM_SIG3);



  ROC1->SetTitle("#tau_{21} Optimization cut-llWW_M900");
  ROC1->GetXaxis()->SetTitle("#tau_{21} upper threshold");
  ROC1->GetYaxis()->SetTitle("eff_sig/1+sqrt(B)");
  ROC1->GetYaxis()->SetTitleOffset(1.5);
  ROC1->SetLineColor(4);
  ROC1->SetLineWidth(2);
  ROC1->SetMarkerStyle(20);
  ROC1->SetMarkerSize(2);
  ROC1->SetMarkerColor(4);


  ROC2->SetTitle("#tau_{31} Optimization cut-llWW_M900");
  ROC2->GetXaxis()->SetTitle("#tau_{31} upper threshold");
  ROC2->GetYaxis()->SetTitle("eff_sig/1+sqrt(B)");
  ROC2->GetYaxis()->SetTitleOffset(1.5);
  ROC2->SetLineColor(4);
  ROC2->SetLineWidth(2);
  ROC2->SetMarkerStyle(20);
  ROC2->SetMarkerSize(2);
  ROC2->SetMarkerColor(4);


  ROC3->SetTitle("#tau_{41} Optimization cut-llWW_M900");
  ROC3->GetXaxis()->SetTitle("#tau_{41} upper threshold");
  ROC3->GetYaxis()->SetTitle("eff_sig/1+sqrt(B)");
  ROC3->GetYaxis()->SetTitleOffset(1.5);
  ROC3->SetLineColor(4);
  ROC3->SetLineWidth(2);
  ROC3->SetMarkerStyle(20);
  ROC3->SetMarkerSize(2);
  ROC3->SetMarkerColor(4);






  gROOT->SetStyle("Plain");
  gStyle->SetPadGridY(kTRUE);
  gStyle->SetPadGridX(kTRUE);

  TCanvas *c1= new TCanvas("c1","",200,10,1600,500);
  c1->Divide(3,1);

  c1->cd(1);
  ROC1->Draw("apc");
  
  c1->cd(2);
  ROC2->Draw("apc");

  c1->cd(3);
  ROC3->Draw("apc");


  gSystem->ProcessEvents();
  TImage *img1 = TImage::Create();
  img1->FromPad(c1);
  img1->WriteImage("h_Optimization_llWW_M900.png");
  delete c1;
  delete img1;





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


  TGraphErrors *g=new TGraphErrors(sig_nbinsx,sig_nbincontent,sign,sig_ex,sig_ey);
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

