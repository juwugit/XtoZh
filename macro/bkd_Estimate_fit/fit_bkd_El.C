#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <TF1.h>
#include <TPad.h>
#include <TH1D.h>
#include <TMath.h>
#include <TFile.h>
#include <TList.h>
#include <TGraph.h>
#include <TLegend.h>
#include <TStyle.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TBranch.h>
#include <TRandom.h>
#include <TVectorT.h>
#include <TProfile.h>
#include <TLorentzVector.h>
#include <TSystemDirectory.h>
#include <TGraphAsymmErrors.h>

const Int_t totalNEvent_dy70 = 11764538;
const Int_t totalNEvent_dy100 = 12511326;
const Double_t crossSection_dy70 = 63.5;
const Double_t crossSection_dy100 = 39.4;
const Double_t dataLumi_totalDEle = 19712.225;

// formula: scale = data_luminosity / bkg_luminosity
const Double_t scale_dy70 = dataLumi_totalDEle / (totalNEvent_dy70 / crossSection_dy70);
const Double_t scale_dy100 = dataLumi_totalDEle / (totalNEvent_dy100 / crossSection_dy100);
Double_t fitFunc(Double_t*, Double_t*);


void fit_bkd_El(){

  TFile *f_data  = TFile::Open("rootfile/delpanj_v4_data_DoubleEl.root");
  TFile *f_dy70  = TFile::Open("rootfile/delpanj_v4_DYJetsToLL_PtZ-70To100_El.root");
  TFile *f_dy100 = TFile::Open("rootfile/delpanj_v4_DYJetsToLL_PtZ-100_El.root");


  TH1D* h_dy70side = (TH1D*)(f_dy70->Get("h_sbXMass"));
  TH1D* h_dy70sign = (TH1D*)(f_dy70->Get("h_sigXMass"));
  TH1D* h_dy100side = (TH1D*)(f_dy100->Get("h_sbXMass"));
  TH1D* h_dy100sign = (TH1D*)(f_dy100->Get("h_sigXMass"));
  TH1D* h_dataEleside = (TH1D*)(f_data->Get("h_sbXMass"));
  TH1D* h_dataElesign = (TH1D*)(f_data->Get("h_sigXMass"));

  // [side][signal]
  TH1D* h_target[2][3] = {{h_dy70side, h_dy100side, h_dataEleside},
			  {h_dy70sign, h_dy100sign, h_dataElesign}};
  
  const Double_t varBins[] = {680,720,760,800,840,920,1000,1100,
			      1250,1400,1600,1800,2000,2400};

  Int_t nvarBins = sizeof(varBins)/sizeof(varBins[0])-1;

  // fixing the discontinuous of bin content
  Int_t smallestBin = varBins[1] - varBins[0];
  vector<Int_t> binRatio;
  
  for(Int_t i = 0; i < 2; i++){
    for(Int_t j = 0; j < 3; j++){

      for(Int_t nb = 0; nb < nvarBins; nb++){

	binRatio.push_back((varBins[nb+1]-varBins[nb])/smallestBin);
	h_target[i][j]->SetBinContent(nb+1, (h_target[i][j]->GetBinContent(nb+1)/binRatio[nb]));

      }

    }
  }

  TF1* fitCurve[2][2]; // [bkg,data][side,signal]
  TH1D* h_combine[2][2]; // [bkg,data][side,signal]
  TH1D* h_alpha = new TH1D("h_alpha", "", nvarBins, varBins); // bkg only
  TH1D* h_numbkgData = new TH1D("h_numbkgData", "", nvarBins, varBins);
  TCanvas* c = new TCanvas("c", "", 0, 0, 1360, 800);

  Int_t hcount = 1;
  Double_t scale[3] = {scale_dy70, scale_dy100, 1};
  std::string htitle[2][2] = {{"Background: Sideband region","Background: Signal region"},
			      {"Data: Sideband region","Data: Signal region"}};

  c->Divide(3,2);

  gStyle->SetOptFit(1111);

  for(Int_t i = 0; i < 2; i++){
    for(Int_t j = 0; j < 2; j++){

      fitCurve[i][j] = new TF1(Form("fitCurve%d%d",i,j), fitFunc, 680, 2400, 3);
      h_combine[i][j] = new TH1D(Form("h_combine%d%d",i,j), "", nvarBins, varBins);

      c->cd(hcount);

      h_combine[i][j]->Sumw2();
      h_combine[i][j]->SetMarkerStyle(8);
      h_combine[i][j]->SetMarkerSize(0.7);
      h_combine[i][j]->SetMarkerColor(1);
      h_combine[i][j]->SetTitle(htitle[i][j].data());
      h_combine[i][j]->GetXaxis()->SetTitle("Zprime mass");
      //h_combine[i][j]->GetYaxis()->SetTitle("Event Number");
      
      if( i < 1 ){

	h_combine[i][j]->Add(h_target[j][0], scale[0]);
	h_combine[i][j]->Add(h_target[j][1], scale[1]);
	fitCurve[i][j]->SetParameters(80,-0.005,5);


      }else if( i > 0 ){

	h_combine[i][j]->Add(h_target[j][2], scale[2]);
	fitCurve[i][j]->SetParameters(80,-0.005,5);


      }

      h_combine[i][j]->Fit(Form("fitCurve%d%d",i,j), "", "", 680, 2400);
      h_combine[i][j]->Draw();

      hcount++;

    }

  }

  c->cd(hcount);

  h_alpha->Sumw2();
  h_alpha->SetMarkerColor(1);
  h_alpha->SetMarkerStyle(8);
  h_alpha->SetMarkerSize(0.8);
  h_alpha->Divide(h_combine[0][1], h_combine[0][0]); // signal/side

  TF1* f_alphaFit = new TF1("f_alphaFit", 
			    "([0]*TMath::Exp([1]*x+[2]/x))/([3]*TMath::Exp([4]*x+[5]/x))", 680, 2400);

  f_alphaFit->SetParameter(0, fitCurve[0][1]->GetParameter(0));
  f_alphaFit->SetParameter(1, fitCurve[0][1]->GetParameter(1));
  f_alphaFit->SetParameter(2, fitCurve[0][1]->GetParameter(2));
  f_alphaFit->SetParameter(3, fitCurve[0][0]->GetParameter(0));
  f_alphaFit->SetParameter(4, fitCurve[0][0]->GetParameter(1));
  f_alphaFit->SetParameter(5, fitCurve[0][0]->GetParameter(2));
  f_alphaFit->SetMinimum(0);
  f_alphaFit->SetMaximum(1);
  f_alphaFit->SetTitle("Alpha ratio");
  f_alphaFit->GetXaxis()->SetTitle("Zprime mass");
  //f_alphaFit->GetYaxis()->SetTitle("Alpha Ratio");
  f_alphaFit->Draw();
  h_alpha->Draw("same");

  c->cd(hcount+1);

  Double_t alphaRatio, sidebandData, numbkgData;
  Double_t alphaRatioError, sidebandDataError, numbkgDataError;

  for(Int_t i = 1; i <= nvarBins; i++){

    alphaRatio = h_alpha->GetBinContent(i);
    sidebandData = h_combine[1][0]->GetBinContent(i);
    numbkgData = alphaRatio*sidebandData;
      
    alphaRatioError = h_alpha->GetBinError(i);
    sidebandDataError = h_combine[1][0]->GetBinError(i);

    if( alphaRatio == 0 || sidebandData == 0 ) continue;
    numbkgDataError = numbkgData*TMath::Sqrt(pow((alphaRatioError/alphaRatio),2)+pow((sidebandDataError/sidebandData),2));

    h_numbkgData->SetBinContent(i,numbkgData);
    h_numbkgData->SetBinError(i,numbkgDataError);

  }

  h_numbkgData->SetMarkerColor(1);
  h_numbkgData->SetMarkerStyle(8);
  h_numbkgData->SetMarkerSize(0.8);
  h_numbkgData->SetTitle("Number of estimated background in data");
  h_numbkgData->GetXaxis()->SetTitle("Zprime mass");
  //h_numbkgData->GetYaxis()->SetTitle("Number of Bkg of Data");
  h_numbkgData->Draw();

  c->Print("fit_bkd_El.png");

}

Double_t fitFunc(Double_t* v, Double_t* par){
  
  Double_t x = v[0];
  return par[0]*TMath::Exp(par[1]*x + par[2]/x);
  
}
