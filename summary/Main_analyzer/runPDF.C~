#include <TStopwatch.h>
#include <TROOT.h>
#include <string>
#include <iostream>

using namespace std;

void runPDF(std::string filename)
{
  TStopwatch* myWatch = new TStopwatch();
  myWatch->Start();
  gROOT->ProcessLine(".L ${LHAPDFDIR}/lib/libLHAPDF.so");

  gROOT->ProcessLine(".L myLHAPDF_reweighing.C++");

  gROOT->ProcessLine(Form("myLHAPDF_reweighing(\"%s\")",filename.data()));

  myWatch->Stop();
  cout << myWatch->RealTime() << " seconds has passed! " << endl; 

}
