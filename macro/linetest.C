#include <TH1.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <iostream>

void linetest(){

   TCanvas *can = new TCanvas("can", "can", 1000, 800);

   // TGraph line
   TGraph *graph = new TGraph(10);
   graph->SetPoint(0,100,13);
   graph->SetPoint(1,200,12);
   graph->SetPoint(2,300,11.1);
   graph->SetPoint(3,400,9.4);
   graph->SetPoint(4,500,2.3);
   graph->SetPoint(5,600,0.632);
   graph->SetPoint(6,700,0.16);
   graph->SetPoint(7,800,0.05);
   graph->SetPoint(8,900,0.02);
   graph->SetPoint(9,1000,0.007);
   
   
   // TGraph line (red)
   TGraph *graphc = new TGraph(15);
   graphc->SetName("c");
   graphc->SetTitle("c");
   graphc->SetFillColor(2);
   graphc->SetLineColor(2);
   
   graphc->SetPoint(0,100, 0.007);
   graphc->SetPoint(1,200, 0.02);
   graphc->SetPoint(2,300, 0.05);
   graphc->SetPoint(3,400, 0.16);
   graphc->SetPoint(4,500, 0.632);
   graphc->SetPoint(5,600, 2.3);
   graphc->SetPoint(6,700, 9.4);
   graphc->SetPoint(7,800, 11.1);
   graphc->SetPoint(8,900, 12);
   graphc->SetPoint(9,1000,13);
   graphc->SetPoint(10,1100, 14);
   graphc->SetPoint(11,1200, 15);
   graphc->SetPoint(12,1300, 16);
   graphc->SetPoint(13,1400, 17);
   graphc->SetPoint(14,1500, 18);


   graphc->Draw("ALP");
   graph->Draw("LP");
   

}
