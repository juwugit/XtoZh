// example code to run Bulk Graviton->ZZ->ZlepZhad selections on electron-channel

#include <vector>
#include <iostream>
#include <algorithm>
#include <TString.h>
#include <TH1.h>
#include <TFile.h>
#include "untuplizer.h"
#include <TClonesArray.h>
#include <TLorentzVector.h>
#include "LHAPDF/LHAPDF.h"

using namespace std;

// maximum number of PDFs allowed is 5
const int NPDFS=5;
const int defaultIndex=1;

class MyPDF {
 public:
  int nIndex;
  MyPDF(const char* pdfname, int n) {
    nIndex = n;	
    // always set the first one to CTEQ6L1 PDF, the one used by madgraph MC
    LHAPDF::initPDFSet(defaultIndex,"cteq6ll.LHpdf"); 
    LHAPDF::initPDFSet(nIndex,pdfname);
  }
  virtual ~MyPDF(){};

  float weight(float* Info_, unsigned int member)
  {
    int id1 = Info_[0]; 
    int id2 = Info_[1]; 
    float x1 = Info_[2]; 
    float x2 = Info_[3]; 
    float Q = Info_[6]; 

    LHAPDF::usePDFMember(nIndex,member);
    //  double xfx(int nset, double x, double Q, int fl);
    float pdf1 = LHAPDF::xfx(nIndex,x1,Q,id1)*LHAPDF::xfx(nIndex,x2,Q,id2);

    LHAPDF::usePDFMember(defaultIndex,member);
    float pdf_default = LHAPDF::xfx(defaultIndex,x1,Q,id1)*LHAPDF::xfx(defaultIndex,x2,Q,id2);

    if (pdf_default>0) {
      // return the ratio of other PDF weights to CTEQ6L1 PDF weight
      return pdf1/pdf_default;
    } else {
      printf ("pdf1 = %e, pdf_default = %e\n", pdf1, pdf_default);
      return 1.;
    }

  }
}; // end of myPDF definitions


void myLHAPDF_reweighing(std::string inputFile){

  //get TTree from file ...
  TreeReader data(inputFile.data());

  Long64_t nTotal=0;
  Long64_t nPass[20]={0};

  TH1F* hy = new TH1F("hy","",60,-3,3);
  hy->Sumw2();
  hy->SetXTitle("Rapidity of generator-level Zprime");
  TH1F* hzy[NPDFS];
  
  for(int i=0;i<NPDFS ;i++)
    hzy[i]=(TH1F*)hy->Clone(Form("hzy%d",i));


  // all LO PDFs, don't use defaultIndex
  MyPDF* mstw2008lo = new MyPDF("MSTW2008lo68cl.LHgrid",2);
  MyPDF* nnpdf21lo = new MyPDF("NNPDF21_lo_as_0119_100.LHgrid",3);
  //MyPDF* a02mlo = new MyPDF("a02m_lo.LHgrid",4);
  //MyPDF* heralo = new MyPDF("HERAPDF1.5LO_EIG.LHgrid",5);
  //MyPDF* ct10nlo = new MyPDF("CT10.LHgrid",2);
  MyPDF* mstw2008nlo = new MyPDF("MSTW2008nlo68cl.LHgrid",4);
  MyPDF* nnpdf23nlo = new MyPDF("NNPDF23_nlo_collider_as_0118.LHgrid",5);

  //Event loop
  for(Long64_t jEntry=0; jEntry<data.GetEntriesFast() ;jEntry++){

    if (jEntry % 100 == 0)
      fprintf(stderr, "Processing event %lli of %lli\n", jEntry + 1, data.GetEntriesFast());

    data.GetEntry(jEntry);
    nTotal ++;

    // 0. check the generator-level information and make sure there is a Z->e+e-
    Int_t nGenPar        = data.GetInt("nGenPar");
    Int_t* genParId      = data.GetPtrInt("genParId");
    Int_t* genParSt      = data.GetPtrInt("genParSt");
    Float_t* genParPt    = data.GetPtrFloat("genParPt");
    Float_t* genParEta   = data.GetPtrFloat("genParEta");
    Float_t* genParPhi   = data.GetPtrFloat("genParPhi");
    Float_t* genParM     = data.GetPtrFloat("genParM");
    
    Float_t* pdfInfo     = data.GetPtrFloat("pdf");
    

    bool findZprime=false;
    TLorentzVector zprime_l4(0,0,0,0);

    for(int ig=0; ig < nGenPar; ig++){

      if(genParId[ig]!=1023)continue;
      findZprime=true;
      zprime_l4.SetPtEtaPhiM(
			     genParPt[ig],
			     genParEta[ig],
			     genParPhi[ig],
			     genParM[ig]);
      break;
    }

    if(!findZprime)continue;

    float zy = zprime_l4.Rapidity();
    double weight_pdf[NPDFS]={
      1.0,      
      mstw2008lo->weight(pdfInfo,0),
      nnpdf21lo->weight(pdfInfo,0),
      //ct10nlo->weight(pdfInfo,0),
      mstw2008nlo->weight(pdfInfo,0),
      nnpdf23nlo->weight(pdfInfo,0)
    };

    for(int i=0;i<NPDFS;i++)
      hzy[i]->Fill(zy,weight_pdf[i]); // original 

  } // end of loop over entries

  std::cout << "nTotal    = " << nTotal << std::endl;
  
  TFile* outFile = new TFile("zy_pdf.root","recreate");
  
  for(int i=0;i<NPDFS;i++)
    hzy[i]->Write(); 

  outFile->Close();
    
}
