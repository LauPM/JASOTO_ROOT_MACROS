
#include"lib/headers.h"


TGraphErrors * Divide(TGraphErrors* tp1, TGraphErrors *tp2)
{
   TGraphErrors *Res =  new TGraphErrors();
   for (int i=0; i<tp1->GetN(); i++)
   {
     double v1=tp1->GetY()[i];
     double v2=tp2->GetY()[i];
     double ratio=v1/v2;
     if (v2==0) continue;
     double e1=tp1->GetErrorY(i);
     double e2=tp2->GetErrorY(i);
     double error=ratio*TMath::Sqrt((e1/v1)*(e1/v1)+(e2/v2)*(e2/v2));
     Res->SetPoint(Res->GetN(),tp1->GetX()[i], ratio);
     Res->SetPointError(Res->GetN()-1,0,error );

   }
   Res->GetXaxis()->SetTimeFormat("%d-%b");
   Res->GetXaxis()->SetTimeDisplay(1); 
   Res->GetXaxis()->SetTitle("Date");
   return Res;
}
TGraphErrors * Relative(TGraphErrors* tp1)
{

   double v1=tp1->GetY()[0];
   double e1=tp1->GetErrorY(0);

   TGraphErrors *Res =  new TGraphErrors();
   for (int i=0; i<tp1->GetN(); i++)
   {
     double v2=tp1->GetY()[i];
     double e2=tp1->GetErrorY(i);
     double ratio=v2/v1;
     double error=ratio*TMath::Sqrt((e1/v1)*(e1/v1)+(e2/v2)*(e2/v2));
     Res->SetPoint(Res->GetN(),tp1->GetX()[i], ratio);
     Res->SetPointError(Res->GetN()-1,0,error );

   }
   Res->GetXaxis()->SetTimeFormat("%d-%b");
   Res->GetXaxis()->SetTimeDisplay(1); 
   Res->GetXaxis()->SetTitle("Date");
   return Res;
}

void RatioPE()
{
//  TFile *f = new TFile("Q3PE_Gaussian.root");
//  TFile *f = new TFile("Amp_Gaussian.root");
  TFile *f = new TFile("QPeak_Gaussian.root");
  f->ls();
  TGraphErrors* tg2 = (TGraphErrors*)f->Get("trigger10_treshold35_channel1");
  TGraphErrors* tg1 = (TGraphErrors*)f->Get("trigger10_treshold35_channel0");
  TGraphErrors* tg2N = Relative(tg2);
  TGraphErrors* tg1N = Relative(tg1);
  TGraphErrors* tgratio = Divide(tg2,tg1);
  TMultiGraph *m = new TMultiGraph();
  m->Add(tg1);
  m->Add(tg2);
   m->GetXaxis()->SetTimeFormat("%d-%b");
   m->GetXaxis()->SetTimeDisplay(1); 
   m->GetXaxis()->SetTitle("Date");
  TMultiGraph *m2 = new TMultiGraph();
  m2->Add(tg1N);
  m2->Add(tg2N);
   m2->GetXaxis()->SetTimeFormat("%d-%b");
   m2->GetXaxis()->SetTimeDisplay(1); 
   m2->GetXaxis()->SetTitle("Date");
  TCanvas * c = new TCanvas("c");
  c->Divide(1,3);
  c->cd(1);
  m->Draw("ALP");//m->GetXaxis()->SetRangeUser();
  c->cd(2);
  m2->Draw("ALP");//m2->GetXaxis()->SetRangeUser();
  c->cd(3);
  tgratio->Draw("ALP");
  lets_pause();  
}
