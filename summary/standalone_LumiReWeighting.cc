/**
   \class    standalone_LumiReWeighting standalone_LumiReWeighting.h "PhysicsTools/Utilities/interface/standalone_LumiReWeighting.h"
   \brief    Class to provide lumi weighting for analyzers to weight "flat-to-N" MC samples to data

   This class will trivially take two histograms:
   1. The generated "flat-to-N" distributions from a given processing (or any other generated input)
   2. A histogram generated from the "estimatePileup" macro here:

   https://twiki.cern.ch/twiki/bin/view/CMS/LumiCalc#How_to_use_script_estimatePileup

   and produce weights to convert the input distribution (1) to the latter (2).

   \author Shin-Shan Eiko Yu, Salvatore Rappoccio, modified by Mike Hildreth
  
*/
#ifndef standalone_LumiReWeighting_cxx
#define standalone_LumiReWeighting_cxx
#include "TH1.h"
#include "TFile.h"
#include <string>
#include "standalone_LumiReWeighting.h"

//=======================================================
// For 2012 Data and MC
//=======================================================

Double_t Summer2012_S10[60] = {
  2.560E-06,
  5.239E-06,
  1.420E-05,
  5.005E-05,
  1.001E-04,
  2.705E-04,
  1.999E-03,
  6.097E-03,
  1.046E-02,
  1.383E-02,
  1.685E-02,
  2.055E-02,
  2.572E-02,
  3.262E-02,
  4.121E-02,
  4.977E-02,
  5.539E-02,
  5.725E-02,
  5.607E-02,
  5.312E-02,
  5.008E-02,
  4.763E-02,
  4.558E-02,
  4.363E-02,
  4.159E-02,
  3.933E-02,
  3.681E-02,
  3.406E-02,
  3.116E-02,
  2.818E-02,
  2.519E-02,
  2.226E-02,
  1.946E-02,
  1.682E-02,
  1.437E-02,
  1.215E-02,
  1.016E-02,
  8.400E-03,
  6.873E-03,
  5.564E-03,
  4.457E-03,
  3.533E-03,
  2.772E-03,
  2.154E-03,
  1.656E-03,
  1.261E-03,
  9.513E-04,
  7.107E-04,
  5.259E-04,
  3.856E-04,
  2.801E-04,
  2.017E-04,
  1.439E-04,
  1.017E-04,
  7.126E-05,
  4.948E-05,
  3.405E-05,
  2.322E-05,
  1.570E-05,
  5.005E-06};



double Data2012[60]={
  12260.7,
  32609.6,
  89739.5,
  336842,
  618396,
  3.04729e+06,
  1.75097e+07,
  5.16022e+07,
  1.21965e+08,
  2.46902e+08,
  4.34886e+08,
  6.77275e+08,
  8.77747e+08,
  9.97468e+08,
  1.07691e+09,
  1.1357e+09,
  1.16941e+09,
  1.179e+09,
  1.17346e+09,
  1.15656e+09,
  1.12984e+09,
  1.09611e+09,
  1.05651e+09,
  1.00685e+09,
  9.39763e+08,
  8.51592e+08,
  7.4576e+08,
  6.29626e+08,
  5.10817e+08,
  3.96846e+08,
  2.94762e+08,
  2.09334e+08,
  1.42052e+08,
  9.1881e+07,
  5.64547e+07,
  3.28699e+07,
  1.81328e+07,
  9.50469e+06,
  4.76127e+06,
  2.29855e+06,
  1.08096e+06,
  501851,
  233697,
  111098,
  54823.3,
  28402.2,
  15490.4,
  8845.67,
  5236.46,
  3180.19,
  1964.07,
  1225.16,
  767.781,
  481.28,
  300.644,
  186.558,
  114.687,
  69.6938,
  41.7929,
  24.6979
};


double Data2012Up[60]={
  11531,
  22746.3,
  80818.1,
  257427,
  551101,
  1.60586e+06,
  1.05708e+07,
  3.47816e+07,
  8.30211e+07,
  1.7458e+08,
  3.15538e+08,
  5.16568e+08,
  7.32305e+08,
  8.84232e+08,
  9.75842e+08,
  1.04236e+09,
  1.09075e+09,
  1.11673e+09,
  1.12289e+09,
  1.11683e+09,
  1.10102e+09,
  1.07676e+09,
  1.0464e+09,
  1.01109e+09,
  9.67817e+08,
  9.10458e+08,
  8.34969e+08,
  7.42891e+08,
  6.39826e+08,
  5.32137e+08,
  4.2599e+08,
  3.27511e+08,
  2.41734e+08,
  1.71295e+08,
  1.16391e+08,
  7.56342e+07,
  4.687e+07,
  2.76521e+07,
  1.55392e+07,
  8.34238e+06,
  4.30163e+06,
  2.14631e+06,
  1.04607e+06,
  503782,
  243034,
  119245,
  60389.8,
  31915.8,
  17676.4,
  10228.9,
  6136.55,
  3781.67,
  2374.1,
  1508.26,
  964.619,
  618.47,
  396.12,
  252.669,
  160.084,
  100.52
};

double Data2012Down[60]={
  13087.1,
  44709.1,
  105071,
  434061,
  777846,
  5.88724e+06,
  2.81053e+07,
  7.76129e+07,
  1.80256e+08,
  3.49441e+08,
  5.97234e+08,
  8.5111e+08,
  1.01382e+09,
  1.11158e+09,
  1.18288e+09,
  1.22641e+09,
  1.24076e+09,
  1.23607e+09,
  1.218e+09,
  1.18842e+09,
  1.15072e+09,
  1.10595e+09,
  1.04833e+09,
  9.69128e+08,
  8.6569e+08,
  7.4396e+08,
  6.133e+08,
  4.82968e+08,
  3.62118e+08,
  2.58323e+08,
  1.75314e+08,
  1.12969e+08,
  6.88589e+07,
  3.95678e+07,
  2.14131e+07,
  1.09417e+07,
  5.31179e+06,
  2.47309e+06,
  1.11807e+06,
  498486,
  223306,
  102602,
  49265.8,
  25003.5,
  13419.9,
  7553.03,
  4403.74,
  2629.36,
  1593.07,
  972.62,
  595.086,
  363.198,
  220.258,
  132.285,
  78.4722,
  45.8806,
  26.3971,
  14.9274,
  8.28971,
  4.51816
};


//=======================================================
// For 2011 Data and MC
//=======================================================

Double_t Fall2011[50] = {
  0.003388501,
  0.010357558,
  0.024724258,
  0.042348605,
  0.058279812,
  0.068851751,
  0.072914824,
  0.071579609,
  0.066811668,
  0.060672356,
  0.054528356,
  0.04919354,
  0.044886042,
  0.041341896,
  0.0384679,
  0.035871463,
  0.03341952,
  0.030915649,
  0.028395374,
  0.025798107,
  0.023237445,
  0.020602754,
  0.0180688,
  0.015559693,
  0.013211063,
  0.010964293,
  0.008920993,
  0.007080504,
  0.005499239,
  0.004187022,
  0.003096474,
  0.002237361,
  0.001566428,
  0.001074149,
  0.000721755,
  0.000470838,
  0.00030268,
  0.000184665,
  0.000112883,
  6.74043E-05,
  3.82178E-05,
  2.22847E-05,
  1.20933E-05,
  6.96173E-06,
  3.4689E-06,
  1.96172E-06,
  8.49283E-07,
  5.02393E-07,
  2.15311E-07,
  9.56938E-08
};


double Data2011[50]={
  5.07024e+06,
  1.25241e+06,
  9.03288e+06,
  1.15106e+08,
  3.56113e+08,
  5.05445e+08,
  5.15838e+08,
  4.69266e+08,
  4.24162e+08,
  3.98722e+08,
  3.71911e+08,
  3.46841e+08,
  3.27692e+08,
  3.01809e+08,
  2.58952e+08,
  1.98323e+08,
  1.31701e+08,
  7.46387e+07,
  3.57587e+07,
  1.44475e+07,
  4.97014e+06,
  1.4923e+06,
  405908,
  104272,
  26235.1,
  6600.02,
  1659.27,
  415.404,
  109.906,
  41.2309,
  33.2132,
  43.8802,
  63.9808,
  91.6263,
  126.102,
  166.165,
  209.506,
  252.713,
  291.616,
  321.941,
  340.153,
  343.94,
  332.511,
  307.736,
  272.51,
  230.858,
  187.096,
  145.067,
  107.618,
  76.3918
};

double Data2011Up[50]={
  5.01089e+06,
  1.15407e+06,
  5.97158e+06,
  7.88451e+07,
  2.90835e+08,
  4.60041e+08,
  4.98014e+08,
  4.64675e+08,
  4.19087e+08,
  3.89226e+08,
  3.67961e+08,
  3.42229e+08,
  3.22879e+08,
  3.0469e+08,
  2.7688e+08,
  2.32927e+08,
  1.75234e+08,
  1.15356e+08,
  6.56347e+07,
  3.20356e+07,
  1.33956e+07,
  4.84198e+06,
  1.54594e+06,
  450181,
  123968,
  33354.9,
  8955.57,
  2407.16,
  643.666,
  174.949,
  56.3123,
  31.9003,
  34.8057,
  48.5878,
  69.5207,
  96.7445,
  129.626,
  166.92,
  206.5,
  245.404,
  280.142,
  307.214,
  323.747,
  327.857,
  318.729,
  297.838,
  267.405,
  230.625,
  191.063,
  152.057
};

double Data2011Down[50]={
  5.13071e+06,
  1.41095e+06,
  1.4471e+07,
  1.64152e+08,
  4.268e+08,
  5.46143e+08,
  5.288e+08,
  4.73097e+08,
  4.32847e+08,
  4.06601e+08,
  3.75696e+08,
  3.52948e+08,
  3.28549e+08,
  2.87695e+08,
  2.2503e+08,
  1.51263e+08,
  8.55545e+07,
  4.02287e+07,
  1.5665e+07,
  5.10339e+06,
  1.43125e+06,
  360929,
  85884.8,
  20077,
  4699.5,
  1096.48,
  256.996,
  69.7713,
  35.4979,
  39.7273,
  58.0342,
  85.6779,
  121.581,
  164.519,
  212.022,
  260.171,
  303.964,
  338.138,
  358.297,
  361.584,
  347.27,
  317.767,
  276.884,
  229.704,
  181.44,
  136.467,
  97.7427,
  66.6703,
  43.3105,
  26.7966
};


standalone_LumiReWeighting::standalone_LumiReWeighting(int year,int mode) {

  std::cout << "=======================================================================" << std::endl;
  
  std::vector<double> MC_distr;
  std::vector<double> Lumi_distr;

  MC_distr.clear();
  Lumi_distr.clear();
  std::cout << "Year " << year << std::endl;
  if(year!=2011 && year!=2012)
    {
      std::cout << "The year is not correct!! Reset to year 2012." << 
	std::endl;
      year=2012;
      std::cout << "Year " << year << std::endl;
    }
  switch (mode)
    {
    case 0:
      std::cout << "Using central value " << std::endl;
      break;
    case 1:
      std::cout << "Using +1 sigma 5% value " << std::endl;
      break;
    case -1:
      std::cout << "Using -1 sigma 5% value " << std::endl;
      break;
    default:
      std::cout << "Using central value " << std::endl;
      break;
    } // end of switch

  Int_t NBins = 60;
  if(year==2011) NBins = 50;
  
  for( int i=0; i< NBins; ++i) {
    if(year==2011)
      {
	switch (mode){
	case 0:
	  Lumi_distr.push_back(Data2011[i]);
	  break;
	case 1:
	  Lumi_distr.push_back(Data2011Up[i]);
	  break;
	case -1:
	  Lumi_distr.push_back(Data2011Down[i]);
	  break;
	default:
	  Lumi_distr.push_back(Data2011[i]);
	  break;
	} // end of switch
	MC_distr.push_back(Fall2011[i]);
      }

    else if(year==2012)
      {
	switch (mode){
	case 0:
	  Lumi_distr.push_back(Data2012[i]);
	  break;
	case 1:
	  Lumi_distr.push_back(Data2012Up[i]);
	  break;
	case -1:
	  Lumi_distr.push_back(Data2012Down[i]);
	  break;
	default:
	  Lumi_distr.push_back(Data2012[i]);
	  break;
	} // end of switch
	MC_distr.push_back(Summer2012_S10[i]);
      }

  } // end of loop over bins

  // no histograms for input: use vectors
  
  // now, make histograms out of them:

  // first, check they are the same size...

  if( MC_distr.size() != Lumi_distr.size() ){   
    std::cout << "MC_distr.size() = " << MC_distr.size() << std::endl;
    std::cout << "Lumi_distr.size() = " << Lumi_distr.size() << std::endl;
    std::cerr <<"ERROR: standalone_LumiReWeighting: input vectors have different sizes. Quitting... \n";

  }


  weights_ = new TH1D(Form("luminumer_%d",mode),
 		      Form("luminumer_%d",mode),
 		      NBins,0.0, double(NBins));

  TH1D* den = new TH1D(Form("lumidenom_%d",mode),
 		       Form("lumidenom_%d",mode),
 		       NBins,0.0, double(NBins));


  
  for(int ibin = 1; ibin<NBins+1; ++ibin ) {
    weights_->SetBinContent(ibin, Lumi_distr[ibin-1]);
    den->SetBinContent(ibin,MC_distr[ibin-1]);
  }

  std::cout << "Data Input " << std::endl;
  for(int ibin = 1; ibin<NBins+1; ++ibin){
    std::cout << "   " << ibin-1 << " " << weights_->GetBinContent(ibin) << std::endl;
  }
  std::cout << "MC Input " << std::endl;
  for(int ibin = 1; ibin<NBins+1; ++ibin){
    std::cout << "   " << ibin-1 << " " << den->GetBinContent(ibin) << std::endl;
  }

  // check integrals, make sure things are normalized

  double deltaH = weights_->Integral();
  if(fabs(1.0 - deltaH) > 0.02 ) { //*OOPS*...
    weights_->Scale( 1.0/ weights_->Integral() );
  }
  double deltaMC = den->Integral();
  if(fabs(1.0 - deltaMC) > 0.02 ) {
    den->Scale(1.0/ den->Integral());
  }

  weights_->Divide( den );  // so now the average weight should be 1.0    

  std::cout << "Reweighting: Computed Weights per In-Time Nint " << "integral :"<<weights_->Integral()<<std::endl;


  for(int ibin = 1; ibin<NBins+1; ++ibin){
    std::cout << "   " << ibin-1 << " " << weights_->GetBinContent(ibin) << std::endl;
  }

  std::cout << "=======================================================================" << std::endl;

}

standalone_LumiReWeighting::~standalone_LumiReWeighting()
{
}



double standalone_LumiReWeighting::weight( double npv ) {
  int bin = weights_->GetXaxis()->FindBin( npv );
  //std::cout << "weights his integral :"<<weights_->Integral()<<std::endl;
  return weights_->GetBinContent( bin );
}


#endif
