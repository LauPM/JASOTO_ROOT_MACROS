/*
Macro para obtener la waveform promedio de un run.
La macro lee los ficheros con los runes guardados en ROOT, y crea un fichero en AnalysisROOT con los perfiles de centelleo para todos los canales.
*/

#include"lib/headers.h"

void Analyse(int r, double range1, double range2, std::vector<int> triggerchannels, string adc="DT5725")
{

  std::vector<double> Gains={3.76,4.0};//0.76,0.67 //ganancias de los PM en pC
  std::vector<double> SPEAmp={25.1,26.5};//3.2,3.1 //Amplitud del SPE a este voltaje
  for(int i=0;i<5;i++) Gains[i]=Gains[i]/1.602e-7; //conversión de ganancias a /e/
  ana::Run_t myrun(r,{{Form("ROOT/Calibration20210216_ch1_14.root"),"ADC1"},{Form("ROOT/Calibration20210216_ch2_14.root"),"ADC2"},{Form("ROOT/Calibration20210216_ch3_6.root"),"ADC1"}},adc,range1, range2,30,-1);
  myrun.ParSet->setADCAmplitudeThreshold(12);
  myrun.SetGains(Gains);
  myrun.SetSPEAmps(SPEAmp);
//  myrun.PlotPeakTimes();
  myrun.Process();
  myrun.SetCutPedSTD(5);
  myrun.SetCutVariable("PreTriggerSTD",0,5);
  myrun.SetCutTriggerWaveformCuts(triggerchannels);
  myrun.SelectChannels(triggerchannels);
  myrun.Plot36("Charge_MaxPeakRange","",2,1,"",-10,50);
  myrun.Plot36("AmpRange","",2,1,"",-50,200);
  myrun.Plot36("PreTriggerSTD","",2,1,"");
  myrun.SetCutMaxAmplitudeRange(24,26);
  myrun.SetCutVariableVector("MaxAmplitudeRange",std::map<int,std::pair<double,double>>({{0,{20,30}},{1,{20,32}} }) );
  myrun.LoopWaveformsPMT(0);
//  myrun.Plot36("ScintProfFirstSignalBin",Form("AnalysisROOT/AvWf_SPE_%s.root",adc.c_str()),0,1);
  myrun.Close();
}
void AnalysePMT(int r, double range1, double range2, std::vector<int> triggerchannels, string adc="DT5725")
{

  std::vector<double> Gains={3.76,4.0,0.44};//0.76,0.67 //ganancias de los PM en pC
  std::vector<double> SPEAmp={25.1,26.5,25};//3.2,3.1 //Amplitud del SPE a este voltaje
  for(int i=0;i<4;i++) Gains[i]=Gains[i]/1.602e-7; //conversión de ganancias a /e/
  ana::Run_t myrun(r,{{Form("ROOT/Calibration20210216_ch1_14.root"),"ADC1"},{Form("ROOT/Calibration20210216_ch2_14.root"),"ADC2"},{Form("ROOT/Calibration20210216_ch3_6.root"),"ADC1"}},adc,range1, range2,30,5000);
  myrun.ParSet->setADCAmplitudeThreshold(12);
  myrun.SetGains(Gains);
  myrun.SetSPEAmps(SPEAmp);
//  myrun.PlotPeakTimes();
  myrun.Process();
  myrun.SetCutPedSTD(5);
  myrun.SetCutVariable("PreTriggerSTD",0,5);
  myrun.SetCutTriggerWaveformCuts(triggerchannels);
  myrun.SelectChannels(triggerchannels);
  myrun.Plot36("Charge_MaxPeakRange","",2,1,"",-10,50);
  myrun.Plot36("AmpRange","",2,1,"",-50,200);
  myrun.Plot36("PreTriggerSTD","",2,1,"");
  myrun.SetCutMaxAmplitudeRange(15,40);
  myrun.SetCutVariableVector("MaxAmplitudeRange",std::map<int,std::pair<double,double>>({{2,{15,40}} }) );
  //myrun.LoopWaveformsPMT(2);
  myrun.Plot36("ScintProfFirstSignalBin","AnalysisROOT/AvWf_SPE_PMT_ADC.root",0,1,"RECREATE",0,0,new std::vector<int>({2}));
  myrun.Close();
}
void AnalyseCustom(int r, double range1, double range2, std::vector<int> triggerchannels, string adc="DT5725")
{

  std::vector<double> Gains={3.76,4.0};//0.76,0.67 //ganancias de los PM en pC
  std::vector<double> SPEAmp={0.0031,0.0032};//3.2,3.1 //Amplitud del SPE a este voltaje
  for(int i=0;i<5;i++) Gains[i]=Gains[i]/1.602e-7; //conversión de ganancias a /e/
  ana::Run_t myrun(r,{{Form("ROOT/Calibration20210216OSC_ch1_1.root"),"ADC1"},{Form("ROOT/Calibration20210216OSC_ch2_1.root"),"ADC2"}},adc,range1, range2,30,-1);
  myrun.ParSet->setADCAmplitudeThreshold(12);
  myrun.SetGains(Gains);
  myrun.SetSPEAmps(SPEAmp);
//  myrun.PlotPeakTimes();
//  myrun.PlotPedestals();
//  myrun.PlotPedSTDs();
  myrun.Process();
  myrun.SetCutPedSTD(0.001);
  myrun.ParSet->setADCAmplitudeThreshold(0.0015);
//  myrun.SetCutVariable("PreTriggerSTD",0,5);
//  myrun.SetCutTriggerWaveformCuts(triggerchannels);
//  myrun.SelectChannels(triggerchannels);
//  myrun.Plot36("Charge_MaxPeakRange","",2,1,"",-10e-12,30e-12);
  myrun.Plot36("AmpRange","",2,1,"",-0.01,0.04);
//  myrun.Plot36("PreTriggerSTD","",2,1,"",-0.001,0.01);
//  myrun.SetCutMaxAmplitudeRange(24,26);
  myrun.SetCutVariableVector("MaxAmplitudeRange",std::map<int,std::pair<double,double>>({{0,{2e-3,4e-3}},{1,{2.5e-3,4.5e-3}} }) );
myrun.LoopWaveformsPMT(0);
//  myrun.Plot36("ScintProfFirstSignalBin",Form("AnalysisROOT/AvWf_SPE_%s.root",adc.c_str()),0,1);
  myrun.Close();
}

void AnalyseOsc(int r, double range1, double range2, std::vector<int> triggerchannels, string adc="DT5725")
{

  std::vector<double> Gains={3.76,4.0};//0.76,0.67 //ganancias de los PM en pC
  std::vector<double> SPEAmp={0.0031,0.0032};//3.2,3.1 //Amplitud del SPE a este voltaje
  for(int i=0;i<5;i++) Gains[i]=Gains[i]/1.602e-7; //conversión de ganancias a /e/
  ana::Run_t myrun(r,{{Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/ROOT/RUN%i_ch1.root",r),"ADC1"},{Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/ROOT/RUN%i_ch1.root",r),"ADC2"}},adc,range1, range2,30,5000);
  myrun.ParSet->setADCAmplitudeThreshold(12);
  myrun.SetGains(Gains);
  myrun.SetSPEAmps(SPEAmp);
//  myrun.PlotPeakTimes();
//  myrun.PlotPedestals();
//  myrun.PlotPedSTDs();
  myrun.Process();
  myrun.SetCutPedSTD(0.001);
  myrun.ParSet->setADCAmplitudeThreshold(0.0015);
//  myrun.LoopWaveforms();
//  myrun.SetCutVariable("PreTriggerSTD",0,5);
//  myrun.SetCutTriggerWaveformCuts(triggerchannels);
//  myrun.SelectChannels(triggerchannels);
//  myrun.Plot36("Charge_MaxPeakRange","",2,1,"");
//  myrun.Plot36("AmpRange","",2,1,"",-0.01,0.4);
//  myrun.Plot36("PreTriggerSTD","",2,1,"",-0.001,0.01);
//  myrun.SetCutMaxAmplitudeRange(24,26);
  myrun.SetCutVariableVector("MaxAmplitudeRange",std::map<int,std::pair<double,double>>({{0,{2e-3,5e-3}},{1,{2.5e-3,5.5e-3}} }) );
  myrun.LoopWaveformsPMT(0);
  myrun.Plot36("ScintProfFirstSignalBin",Form("AnalysisROOT/Run%i_AvWf_SPE_%s.root",r,adc.c_str()),0,1);
  myrun.Close();
}

void AnalyseRun(int r, double range1, double range2, std::vector<int> triggerchannels, string adc="DT5725")
{

  std::vector<double> Gains={3.76,4.0};//0.76,0.67 //ganancias de los PM en pC
  std::vector<double> SPEAmp={25.1,26.5};//3.2,3.1 //Amplitud del SPE a este voltaje
  for(int i=0;i<5;i++) Gains[i]=Gains[i]/1.602e-7; //conversión de ganancias a /e/
  ana::Run_t myrun(r,{{Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/ROOT/RUN%i_ch1.root",r),"ADC1"},{Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/ROOT/RUN%i_ch1.root",r),"ADC2"}},adc,range1, range2,30,5000);
  myrun.ParSet->setADCAmplitudeThreshold(12);
  myrun.SetGains(Gains);
  myrun.SetSPEAmps(SPEAmp);
//  myrun.PlotPeakTimes();
//  myrun.PlotPedestals();
//  myrun.PlotPedSTDs();
  myrun.Process();
  myrun.SetCutPedSTD(5);
  myrun.SetCutVariable("PreTriggerSTD",0,5);

//  myrun.LoopWaveforms();
//  myrun.SetCutVariable("PreTriggerSTD",0,5);
//  myrun.SetCutTriggerWaveformCuts(triggerchannels);
//  myrun.SelectChannels(triggerchannels);
//  myrun.Plot36("Charge_MaxPeakRange","",2,1,"");
//  myrun.Plot36("AmpRange","",2,1,"",-0.01,0.4);
//  myrun.Plot36("PreTriggerSTD","",2,1,"",-0.001,0.01);
//  myrun.SetCutMaxAmplitudeRange(24,26);
  myrun.SetCutVariableVector("MaxAmplitudeRange",std::map<int,std::pair<double,double>>({{0,{2e-3,5e-3}},{1,{2.5e-3,5.5e-3}} }) );
  myrun.LoopWaveformsPMT(0);
  myrun.Plot36("ScintProfFirstSignalBin",Form("AnalysisROOT/Run%i_AvWf_SPE_%s.root",r,adc.c_str()),0,1);
  myrun.Close();
}
void AverageWaveform_SPE()
{

/*Argumentos:
1. numero de Run
2. tiempo inicial donde empezar a buscar la señal de trigger (s)
3. tiempo final donde dejar de buscar la señal de trigger (s)
4. Canales de trigger, para limpiar ruido.
5. Versión del ADC usada (v1720 o DT5725)
*/
//Analyse(4, 0.32e-6,0.4e-6,{0,1});
AnalysePMT(4, 0.32e-6,0.4e-6,{2});
//AnalyseCustom(4, 0.2e-6,0.23e-6,{0,1},"Osc");
//AnalyseOsc(2001, 1.05e-6,1.15e-6,{0,1},"Osc");

//AnalyseRun(3, 1.25e-6,1.47e-6,{0}); 
}
