/*0
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
  myrun.PlotPeakTimes();
//  myrun.Process(); 
  myrun.SetCutPedSTD();
  myrun.SetCutVariableVector("PreTriggerSTD",std::map<int,std::pair<double,double>>({{0,{0,4.5}},{1,{0,4.5}},{2,{0,4}}}) );
  if(mode=="1stGaussian") myrun.SetCutVariable("MaxAmplitudeRange", 7000,9000);
  if(mode=="2ndGaussian") myrun.SetCutVariable("MaxAmplitudeRange",13000,15000);
  myrun.SetCutMaxAmplitudeRange(0,16150);
  myrun.SetCutPeakTimeRange();
  myrun.SetCutTriggerWaveformCuts({2});
  myrun.LoopWaveformsPMT(2);
//  myrun.SetCutTriggerWaveformCuts({0,1});
//  myrun.SelectChannels({2});
 // if(NEvts!=-1)
  myrun.SetMaximumWaveformsToProcess(6000);
  myrun.Plot36("ScintProfFirstSignalBin",Form("AnalysisROOT/Run%i_ScintProfFirstSignalBin_%s_PMT2.root",r,mode.c_str()),0,0,"RECREATE",0,0,new std::vector<int>({2}));//Plot36(string mode, string dumpfile="", int logoption=0, bool pause=false, string fileoption="RECREATE", double range1=0,double range2=0,std::vector<int> *SelectedChannels=NULL)
  myrun.Close();
}

void AnalyseSPE(int r, double range1, double range2, std::vector<int> triggerchannels)
{

  std::vector<double> Gains={3.79,4.12,0.4};//0.76,0.67 //ganancias de los PM en pC
  std::vector<double> SPEAmp={25.1,26.5,25.3};//3.2,3.1 //Amplitud del SPE a este voltaje
  for(int i=0;i<3;i++) Gains[i]=Gains[i]/1.602e-7; //(1e-19+12)
  ana::Run_t myrun(r,{{Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/ROOT/RUN%i_ch1.root",r),"ADC0"},{Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/ROOT/RUN%i_ch2.root",r),"ADC1"},{Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/ROOT/RUN%i_ch3.root",r),"ADC2"}},"DT5725",range1, range2,30,3000);
  myrun.SetGains(Gains);
  myrun.SetSPEAmps(SPEAmp);
//  myrun.SelectChannels(triggerchannels);
  myrun.PlotPeakTimes();
//  myrun.Process(); 
  myrun.SetCutPedSTD();
  myrun.SetCutVariableVector("PreTriggerSTD",std::map<int,std::pair<double,double>>({{0,{0,4.5}},{1,{0,4.5}},{2,{0,4}}}) );
//  myrun.Plot36("Charge_MaxPeakRange","",2,1,"",-10,50);
//  myrun.Plot36("AmpRange","",2,1,"",-50,200);
//  myrun.Plot36("PreTriggerSTD","",2,1,"");
  myrun.SetCutMaxAmplitudeRange(15,40);
  myrun.SetCutPeakTimeRange();
  myrun.ParSet->setADCAmplitudeThreshold(20);
//  myrun.SetCutTriggerWaveformCuts({2});
//  myrun.LoopWaveformsPMT(2);
//  myrun.SetCutTriggerWaveformCuts({0,1});
//  myrun.SelectChannels({2});
 // if(NEvts!=-1)
  myrun.SetMaximumWaveformsToProcess(6000);
  myrun.Plot36("ScintProf",Form("AnalysisROOT/Run%i_ScintProf_SPE_PMT.root",r),0,1,"RECREATE",0,0,new std::vector<int>({2}));//Plot36(string mode, string dumpfile="", int logoption=0, bool pause=false, string fileoption="RECREATE", double range1=0,double range2=0,std::vector<int> *SelectedChannels=NULL)
  myrun.Close();
}

void AnalyseOsc(int r, double range1, double range2)
{

  std::vector<double> Gains={0.44};//0.76,0.67 //ganancias de los PM en pC
  std::vector<double> SPEAmp={3.4e-3};//3.2,3.1 //Amplitud del SPE a este voltaje
  for(int i=0;i<1;i++) Gains[i]=Gains[i]/1.602e-7; //(1e-19+12)
  ana::Run_t myrun(r,{{Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/ROOT/RUN%i_ch3.root",r),"ADC2"}},"Osc",range1, range2,30,3000);
  myrun.SetGains(Gains);
  myrun.SetSPEAmps(SPEAmp);
  myrun.ParSet->setADCAmplitudeThreshold(0.03);
  myrun.SelectChannels({0});
  myrun.Process(); 
  myrun.PlotPeakTimes();
  myrun.SetCutPedSTD();
  myrun.Plot36("AmpRange",Form(""),0,1);
  myrun.Plot36("Charge_Q3MaxPeakRange",Form(""),0,1);
  myrun.Plot36("Charge_MaxPeakRange",Form(""),0,1);
//  myrun.SetCutVariableVector("PreTriggerSTD",std::map<int,std::pair<double,double>>({{0,{0,4.5}},{1,{0,4.5}},{2,{0,4}}}) );
//  myrun.SetCutMaxAmplitudeRange(0,16150);
//  myrun.SetCutPeakTimeRange();
//  myrun.SetCutTriggerWaveformCuts({0});
  myrun.LoopWaveformsPMT(0,0,"aq");
//  myrun.SetCutTriggerWaveformCuts({0,1});
//  myrun.SelectChannels({2});
 // if(NEvts!=-1)
  myrun.SetMaximumWaveformsToProcess(6000);
  myrun.Plot36("ScintProfFirstSignalBin",Form("AnalysisROOT/Run%i_ScintProfFirstSignalBin_PMT.root",r),0,0,"RECREATE",0,0,new std::vector<int>({0}));//Plot36(string mode, string dumpfile="", int logoption=0, bool pause=false, string fileoption="RECREATE", double range1=0,double range2=0,std::vector<int> *SelectedChannels=NULL)
  myrun.Close();
}
void AnalyseOsc2(int r, double range1, double range2)
{

  std::vector<double> Gains={0.44};//0.76,0.67 //ganancias de los PM en pC
  std::vector<double> SPEAmp={3.4e-3};//3.2,3.1 //Amplitud del SPE a este voltaje
  for(int i=0;i<1;i++) Gains[i]=Gains[i]/1.602e-7; //(1e-19+12)
  ana::Run_t myrun(r,{{Form("ROOT/Calibration20210216OSC_ch3_0.root"),"ADC2"}},"Osc",range1, range2,30,3000);
  myrun.SetGains(Gains);
  myrun.SetSPEAmps(SPEAmp);
  myrun.ParSet->setADCAmplitudeThreshold(0.03);
  myrun.SelectChannels({0});
  myrun.Process(); 
  myrun.PlotPeakTimes();
  myrun.SetCutPedSTD();
//  myrun.SetCutVariableVector("PreTriggerSTD",std::map<int,std::pair<double,double>>({{0,{0,4.5}},{1,{0,4.5}},{2,{0,4}}}) );
//  myrun.SetCutMaxAmplitudeRange(0,16150);
//  myrun.SetCutPeakTimeRange();
//  myrun.SetCutTriggerWaveformCuts({0});

  myrun.SetCutMaxAmplitudeRange(2e-3,6e-3);
//  myrun.SetCutVariable("ChargeMaxPeakRange",2e-12,6e-12);
//  myrun.SetCutVariable("Q3MaxPeakRange",2e-12,6e-12);
  myrun.Plot36("AmpRange",Form(""),0,1);
  myrun.Plot36("Charge_Q3MaxPeakRange",Form(""),0,1);
  myrun.Plot36("Charge_MaxPeakRange",Form(""),0,1);

//  myrun.LoopWaveformsPMT(0,0,"");
//  myrun.SetCutTriggerWaveformCuts({0,1});
//  myrun.SelectChannels({2});
 // if(NEvts!=-1)
  myrun.SetMaximumWaveformsToProcess(6000);
  myrun.Plot36("ScintProf",Form("AnalysisROOT/RunCaliPMTOsci_ScintProf_PMT.root"),0,0,"RECREATE",0,0,new std::vector<int>({0}));//Plot36(string mode, string dumpfile="", int logoption=0, bool pause=false, string fileoption="RECREATE", double range1=0,double range2=0,std::vector<int> *SelectedChannels=NULL)
  myrun.Close();
}
void AverageWaveform_PMT()
{
//AnalyseOsc(2003, 0.2e-6,0.22e-6);
//AnalyseOsc(2002, 1.02e-6,1.1e-6);
//AnalyseOsc2(2002, 0.2e-6,0.25e-6);
//AnalyseOsc(2001,1.02e-6,1.1e-6);
//Analyse(11, 1.25e-6,1.47e-6,{2},"1stGaussian");
//Analyse(11, 1.25e-6,1.47e-6,{2},"2ndGaussian");

AnalyseSPE(9, 1.25e-6,1.47e-6,{2});
}
