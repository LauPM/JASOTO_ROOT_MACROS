/*
Macro para obtener la waveform promedio de un run.
La macro lee los ficheros con los runes guardados en ROOT, y crea un fichero en AnalysisROOT con los perfiles de centelleo para todos los canales.
*/

#include"lib/headers.h"


void Analyse(int r, double range1, double range2, std::vector<int> triggerchannels, string mode)
{

  std::vector<double> Gains={3.79,4.12,0.4};//0.76,0.67 //ganancias de los PM en pC
  std::vector<double> SPEAmp={25.1,26.5,25.3};//3.2,3.1 //Amplitud del SPE a este voltaje
  for(int i=0;i<3;i++) Gains[i]=Gains[i]/1.602e-7; //(1e-19+12)
  ana::Run_t myrun(r,{{Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/ROOT/RUN%i_ch1.root",r),"ADC0"},{Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/ROOT/RUN%i_ch2.root",r),"ADC1"},{Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/ROOT/RUN%i_ch3.root",r),"ADC2"}},"DT5725",range1, range2,30,3000);
  myrun.SetGains(Gains);
  myrun.SetSPEAmps(SPEAmp);
//  myrun.SelectChannels(triggerchannels);
//  myrun.PlotPeakTimes();
//  myrun.Process(); 
  myrun.SetCutPedSTD();
  myrun.SetCutVariableVector("PreTriggerSTD",std::map<int,std::pair<double,double>>({{0,{0,4.5}},{1,{0,4.5}},{2,{0,4}}}) );
  if(mode=="alpha") myrun.SetCutTriggerAmplitudeRange(250,1100,{0,1});
  if(mode=="muon") myrun.SetCutTriggerAmplitudeRange(1100,20000,{0,1});
  myrun.SetCutMaxAmplitudeRange(0,16150);
  myrun.SetCutPeakTimeRange();
//  myrun.SetCutTriggerWaveformCuts({0,1});
//  myrun.SelectChannels({2});
 // if(NEvts!=-1)
  myrun.SetMaximumWaveformsToProcess(6000);
  myrun.Plot36("ScintProfFirstSignalBin",Form("AnalysisROOT/Run%i_ScintProfFirstSignalBin_%s_PMT.root",r,mode.c_str()),0,0,"",0,0,new std::vector<int>({2}));//Plot36(string mode, string dumpfile="", int logoption=0, bool pause=false, string fileoption="RECREATE", double range1=0,double range2=0,std::vector<int> *SelectedChannels=NULL)
  myrun.Close();
}

void AverageWaveform_alphamuon()
{

Analyse(12, 1.25e-6,1.47e-6,{2},"alpha");
Analyse(13, 1.25e-6,1.47e-6,{2},"muon");

Analyse(23, 1.25e-6,1.47e-6,{2},"alpha");
Analyse(24, 1.25e-6,1.47e-6,{2},"muon");

Analyse(34, 1.25e-6,1.47e-6,{2},"alpha");
Analyse(35, 1.25e-6,1.47e-6,{2},"muon");

Analyse(45, 1.25e-6,1.47e-6,{2},"alpha");
Analyse(46, 1.25e-6,1.47e-6,{2},"muon");

Analyse(56, 1.25e-6,1.47e-6,{2},"alpha");
Analyse(57, 1.25e-6,1.47e-6,{2},"muon");

}
