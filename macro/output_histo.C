#include <string>
#include <iostream>
#include "TH1.h"
#include "TKey.h"
#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TCanvas.h"

void output_histo(string inputFile, char folderName[]){

  gSystem->mkdir(folderName);
  TFile::Open(inputFile.data());
  TCanvas *c = new TCanvas("c","",0,0,600,600);
  TDirectory *current_sourcedir = gDirectory;
  TIter nextkey(current_sourcedir->GetListOfKeys());
  TKey *key;

  while((key = (TKey*)nextkey())){

    TObject *obj = key->ReadObj();

    if(obj->IsA()->InheritsFrom("TH1")){

      TH1 *h = (TH1*)obj;
      h->Draw();  

    }

    c->Print(Form("%s/%s.gif", folderName, obj->GetName()));

  }

}
