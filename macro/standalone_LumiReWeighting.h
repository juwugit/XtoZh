#ifndef standalone_LumiReWeighting_h
#define standalone_LumiReWeighting_h


/**
  \class    standalone_LumiReWeighting standalone_LumiReWeighting.h "PhysicsTools/Utilities/interface/standalone_LumiReWeighting.h"
  \brief    Class to provide lumi weighting for analyzers to weight "flat-to-N" MC samples to data

  This class will trivially take two histograms:
  1. The generated "flat-to-N" distributions from a given processing
  2. A histogram generated from the "estimatePileup" macro here:

  https://twiki.cern.ch/twiki/bin/view/CMS/LumiCalc#How_to_use_script_estimatePileup

  \author Salvatore Rappoccio
*/

#include "TH1.h"
#include "TFile.h"
#include <string>
#include <vector>
#include <TROOT.h>
#include <string>
#include <iostream>

using namespace std;

class standalone_LumiReWeighting {
 public:
    
  standalone_LumiReWeighting(int year=2012,int mode=0); // 0: central, -1: down, +1: up
  virtual ~standalone_LumiReWeighting();
  double weight( double npv) ; 

 protected:

  TH1D*      weights_;


};


#endif

