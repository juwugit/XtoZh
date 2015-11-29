#include <TStopwatch.h>
#include <TROOT.h>
#include <string>
#include <iostream>

using namespace std;

void runPDF_CT10(Int_t scaleMode,std::string inputFile,std::string outputFile){

  TStopwatch* myWatch = new TStopwatch();
  myWatch->Start();
  gROOT->ProcessLine(".L /data4/juwu/CMSSW_5_3_20/src/test_pdf/LHAPDF/lib/libLHAPDF.so");

  //gROOT->ProcessLine(".L Main_analyzer/myLHAPDF_reweighing.C++");
  //gROOT->ProcessLine(Form("myLHAPDF_reweighing(\"%s\")",filename.data()));

  gROOT->ProcessLine(".L Main_analyzer/recoXMassCSV_pdf_CT10.C++");
  gROOT->ProcessLine(Form("recoXMassCSV_pdf_CT10(%d,\"%s\",\"%s\")",scaleMode,inputFile.data(),outputFile.data()));


  myWatch->Stop();
  cout << myWatch->RealTime() << " seconds has passed! " << endl; 

}
