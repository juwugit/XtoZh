#include <TStopwatch.h>
#include <TROOT.h>
#include <string>
#include <iostream>

using namespace std;

void runPDF(Int_t scaleMode,std::string inputFile,std::string outputFile){

  TStopwatch* myWatch = new TStopwatch();
  myWatch->Start();
  gROOT->ProcessLine(".L /afs/cern.ch/work/j/juwu/workspace/CMSSW_5_3_20/src/test_pdf/LHAPDF/lib/libLHAPDF.so");

  //gROOT->ProcessLine(".L Main_analyzer/myLHAPDF_reweighing.C++");
  //gROOT->ProcessLine(Form("myLHAPDF_reweighing(\"%s\")",filename.data()));

  gROOT->ProcessLine(".L Main_analyzer/recoXMassCSV_pdf.C++");
  gROOT->ProcessLine(Form("recoXMassCSV_pdf(%d,\"%s\",\"%s\")",scaleMode,inputFile.data(),outputFile.data()));


  myWatch->Stop();
  cout << myWatch->RealTime() << " seconds has passed! " << endl; 

}
