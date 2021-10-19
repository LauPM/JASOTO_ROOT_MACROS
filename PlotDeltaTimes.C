/*
Esta macro dibuja el histograma de puntos que permite separar la corriente oscura de los afterpulses, corrigiendo previamente el overflow del timestamp del ADC
*/

#include"lib/headers.h"

void Analyse(int r, double range1, double range2, string adc="DT5725")
{

  std::vector<double> Gains={11,10,1,4,10};
  std::vector<double> SPEAmp={123,125,58,103};
  for(int i=0;i<5;i++) Gains[i]=Gains[i]/1.602e-7;
  ana::Run_t myrun(r,{{Form("ROOT/Data%i_ch0.root",r),"ADC0"},{Form("ROOT/Data%i_ch1.root",r),"ADC1"},{Form("ROOT/Data%i_ch0.root",r),"ADC2"},{Form("ROOT/Data%i_ch3.root",r),"ADC3"},{Form("ROOT/Data%i_ch4.root",r),"ADC4"}},adc,range1, range2,30,-1);
  myrun.SetGains(Gains);
  myrun.SetSPEAmps(SPEAmp);
  myrun.SelectChannels({0,1,3,4});
  myrun.ParSet->t3=500e-9;
  myrun.Process();

  TCanvas *c = new TCanvas("c");
  c->Divide(2,1);
  c->cd(1);
  myrun.TH1TimeStamps()->Draw("HIST");
  c->cd(2);double length;
  myrun.TH1PCTimeStampsCorrected(length)->Draw("HIST");
  lets_pause(); //pausamos la ejecución para comprobar que la corrección del timestamp tiene sentido.

  double pedcut, overshootcut, maxampr1, maxampr2;
  pedcut=12;
  overshootcut=40;
  maxampr1=40;
  maxampr2=80000;
  if(adc=="v1720")
  {
    pedcut=3;
    overshootcut=10;
    maxampr1=10;
    maxampr2=20000;
  }
  myrun.SetCutPedSTD(pedcut);
  myrun.SetCutOvershootingRange(overshootcut); //quitamos eventos de ruido

  myrun.Plot36("TH2DeltaTimes","",1,1);
}


void PlotDeltaTimes()
{

/*Argumentos:
1. numero de Run
2. tiempo inicial donde empezar a buscar la señal de trigger (s)
3. tiempo final donde dejar de buscar la señal de trigger (s)
*/
Analyse(108, 3.08e-6,3.16e-6);
}
