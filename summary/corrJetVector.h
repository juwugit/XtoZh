#include <iostream>
#include <fstream>
#include <TH1F.h>
#include <TSystem.h>

class corrJetV{

public:

  corrJetV(std::string);
  ~corrJetV(){};
  
  Double_t scaleUnc(Int_t, Double_t, Double_t);
  
protected:

  Int_t nPtBins;
  Int_t nEtaBins;
  Double_t dummy;
  Double_t etaDw[999];
  Double_t etaUp[999];
  Double_t ptDw[999];
  Double_t unc[999][999];
  
};

corrJetV::corrJetV(std::string textFile){

  TString nCol_temp = gSystem->GetFromPipe(Form("awk 'NR==2 {print NF}' %s", textFile.data()));
  TString nRow_temp = gSystem->GetFromPipe(Form("awk '{print NR}' %s | tail -n 1", textFile.data()));

  Int_t nCol = atoi(nCol_temp.Data());
  Int_t nRow = atoi(nRow_temp.Data());

  nPtBins = (nCol-3)/3;
  nEtaBins = nRow;

  if( nPtBins > 999 || nEtaBins > 999 ) return;

  ifstream fin;
  fin.open(textFile.data());

  while(!fin.eof()){

    for(Int_t ieta = 0; ieta < nEtaBins; ieta++){
      fin >> etaDw[ieta] >> etaUp[ieta] >> dummy;

      for(Int_t ipt = 0; ipt < nPtBins; ipt++){
	fin >> ptDw[ipt] >> unc[ieta][ipt] >> dummy;

      }
    }
  }

  fin.close();

}

Double_t corrJetV::scaleUnc(Int_t mode, Double_t myPt, Double_t myEta){

  TH1F* hPt = new TH1F("hPt", "", nPtBins-1, ptDw);
  TH1F* hEta = new TH1F("hEta", "", nEtaBins-1, etaDw);

  // myPt = jet_original.Pt();
  // myEta = jet_original.Eta();

  Int_t myPtId = hPt->FindBin(myPt)-1;
  Int_t myEtaId = hEta->FindBin(myEta)-1;

  hPt->Delete();
  hEta->Delete();

  // Doing interpolation
  
  Double_t a = (unc[myEtaId][myPtId+1]-unc[myEtaId][myPtId])/(ptDw[myPtId+1]-ptDw[myPtId]);
  Double_t b = (unc[myEtaId][myPtId]*ptDw[myPtId+1]-unc[myEtaId][myPtId+1]*ptDw[myPtId])/(ptDw[myPtId+1]-ptDw[myPtId]);
  Double_t corrUnc = (1+mode*fabs(a*myPt+b));

  if( mode > 1 || mode < -1 ) return 0;
  else return corrUnc;
  
}
