



//const float Sf_[2][3] = {1.0043, 1.0074, 1.022, 1.0012, 1.0043, 1.014};
//const float sigma_[2][3] = {0.0004, 0.0005, 0.001, 0.0004, 0.0004, 0.001};


//using namespace std;
void Uncor_eff(TreeReader &data,float &uncor_eff, int &l, int &m){


  uncor_eff=0.0;

  
  float Sf_[2][3] = {1.0043, 1.0074, 1.022, 1.0012, 1.0043, 1.014};
  float sigma_[2][3] = {0.0004, 0.0005, 0.001, 0.0004, 0.0004, 0.001};



  // declare histogram
  TH1F* h_muPt = new TH1F("h_muPt","",40,0,1200);
  TH1F* h_muPtID[2][3];

  for(int i=0; i<2; i++){
    for(int j=0; j<3; j++){

      h_muPtID[i][j] = new TH1F(Form("h_muPtID%d%d",i,j),"",40,0,1200);
      h_muPtID[i][j]->Sumw2();

    } // eta section
  } // pt section



  //100% uncorrelated Sf+1sigma
  Sf_[l][m] = Sf_[l][m] + sigma_[l][m];



  //Event loop
  for(long jEntry=0; jEntry<data.GetEntriesFast() ;jEntry++){

    data.GetEntry(jEntry);


    Int_t    nMu        = data.GetInt("nMu");
    Float_t* muPt       = data.GetPtrFloat("muPt");
    Float_t* muEta      = data.GetPtrFloat("muEta"); 
    Int_t*   muID       = data.GetPtrInt("muPassID");


    for(int i=0; i<nMu; i++){

      
      if(muPt[i]<20) continue;
      h_muPt->Fill(muPt[i]);


      if(muID[i]<=0) continue;

      if(muPt[i]<40){

	if(fabs(muEta[i])<0.8) h_muPtID[0][0]->Fill(muPt[i], Sf_[0][0]);
	if(0.8<fabs(muEta[i]) && fabs(muEta[i])<2.1) h_muPtID[0][1]->Fill(muPt[i], Sf_[0][1]);
   	if(2.1<fabs(muEta[i]) && fabs(muEta[i])<2.4) h_muPtID[0][2]->Fill(muPt[i], Sf_[0][2]);
	
      } //pt 20~40


      if(muPt[i]>40){

	if(fabs(muEta[i])<0.8) h_muPtID[1][0]->Fill(muPt[i], Sf_[1][0]);
	if(0.8<fabs(muEta[i]) && fabs(muEta[i])<2.1) h_muPtID[1][1]->Fill(muPt[i], Sf_[1][1]);
   	if(2.1<fabs(muEta[i]) && fabs(muEta[i])<2.4) h_muPtID[1][2]->Fill(muPt[i], Sf_[1][2]);
	
      } //pt 40~100+
     
    } //loop muon


  } //entries 


  
  float denom = h_muPt->Integral();
  float numer = 0.0;

  for(int i=0; i<2; i++){
    for(int j=0; j<3; j++){
      
      numer = numer + h_muPtID[i][j]->Integral();

    } // index j
  } // index i
  
  
  uncor_eff = numer/denom;




  // Clear TH1
  h_muPt->Clear();

  for(int i=0; i<2; i++){
    for(int j=0; j<3; j++){

      h_muPtID[i][j]->Clear();
      
    } // eta section
  } // pt section
  

} //function brace
