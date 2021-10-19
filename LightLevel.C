
/*
Macro para monitorizar el nivel de luz.
Usa como input las ntuplas generadas con la macro SimpleAnalysis.C, obtiene el promedio de luz en PE y lo plotea por run
*/
#include"lib/headers.h"

void Draw( int n, int runs[5])
{
TFile *ifile[5];
 for(int i=0;i<n;i++) ifile[i]= new TFile(Form("AnalysisROOT/Run%i_NTuple.root",runs[i])); 
 TNtuple *nt[n];
 Float_t ch; 
 Float_t Q3PE; 
  TH1D *h[n];
 for(int i=0;i<n;i++)
 {
   nt[i]= (TNtuple*)ifile[i]->Get("ntuple");
   nt[i]->SetBranchAddress("ch",&ch);
   nt[i]->SetBranchAddress("Q3PE",&Q3PE);
   h[i]=new TH1D(Form("h%i",i),Form("Run %i;Charge collected on ch0 (PE); # evts",runs[i]),500,0,150);
   h[i]->SetLineColor(i+1);
   h[i]->SetLineWidth(2);
 }
 for(int i=0;i<n;i++)
 {
  for(int j=0;j<nt[i]->GetEntries();j++)
  {
   nt[i]->GetEntry(j);
   if(ch!=1) continue;
   h[i]->Fill(Q3PE);
  }
  cout << h[i]->GetMean() << " " << h[i]->GetStdDev() << endl;
 }

 TCanvas *c = new TCanvas("c");
 c->cd();
 for(int i=0;i<4;i++) h[i]->Draw("HIST SAME");
 gPad->BuildLegend();
 lets_pause();

  
}

void LightLevel()
{

/*Argumentos:
1. numero de runes a plotear
2. vector de enteros con los runes a plotear
*/
int runs[5]={4,15,26,37,48};
/*
4	1	35 11/02
15	1	35 12/02
26	1	35 13/02
37	1	35 14/02
48	1	35 15/02};
*/Draw(5,runs);


}
