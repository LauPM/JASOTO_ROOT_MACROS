/*
Macro para obtener la waveform promedio de un run.
La macro lee los ficheros con los runes guardados en ROOT, y crea un fichero en AnalysisROOT con los perfiles de centelleo para todos los canales.
*/

#include"lib/headers.h"


void Analyse(int r, double range1, double range2, std::vector<int> triggerchannels,int NEvts=-1, string adc="DT5725")
{

  std::vector<double> Gains={0.56,3.61,3.83}; //ganancias en pC
  std::vector<double> SPEAmp={38.6,24.8,25.5};//Amplitud del SPE en cuentas de ADC
  for(int i=0;i<3;i++) Gains[i]=Gains[i]/1.602e-7; //(1e-19+12)
  ana::Run_t myrun(r,{{Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/May2021/ROOT/RUN%i_ch2.root",r),"ADC0"},{Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/May2021/ROOT/RUN%i_ch4.root",r),"ADC1"},{Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/May2021/ROOT/RUN%i_ch5.root",r),"ADC2"}},adc,range1, range2,250,1);
  myrun.SetGains(Gains);
  myrun.SetSPEAmps(SPEAmp);
  myrun.SelectChannels({0,1,2});
//  myrun.PlotPeakTimes();
//  myrun.Process(); 
  //~myrun.SetCutPedSTD();
  //~myrun.SetCutVariableVector("PreTriggerSTD",std::map<int,std::pair<double,double>>({{0,{0,4}},{1,{0,4.5}},{2,{0,4.5}}}) );
//  myrun.SetCutTriggerWaveformCuts(triggerchannels);
  //~myrun.SetCutMaxAmplitudeRange(30,2000000);
 //~myrun.SetCutPeakTimeRange();
 // if(NEvts!=-1)
 myrun.ParSet->setADCAmplitudeThreshold(-1000);

  myrun.SetMaximumWaveformsToProcess(1);
//  myrun.LoopWaveformsPMT(0);
  myrun.Plot36("ScintProfFirstSignalBin",Form("AnalysisROOT/Run%i_ScintProfFirstSignalBin.root",r),0,1);
  myrun.Plot36("ScintProf",Form("AnalysisROOT/Run%i_ScintProf.root",r),0,1);
//    myrun.Plot36("ScintProfFirstSignalBin_NotNormalize",Form("AnalysisROOT/Run%i_ScintProfFirstSignalBin_NotNormalize.root",r),0,0);
  myrun.Close();
}
void Analyse_min_max_given(int r, double range1, double range2, std::vector<int> triggerchannels,int NEvts=-1, string adc="DT5725",double amp1=30,double amp2=30000, TString t="")
{

  std::vector<double> Gains={0.56,3.61,3.83}; //ganancias en pC
  std::vector<double> SPEAmp={38.6,24.8,25.5};//Amplitud del SPE en cuentas de ADC
  for(int i=0;i<3;i++) Gains[i]=Gains[i]/1.602e-7; //(1e-19+12)
	
 ana::Run_t myrun(r,{{Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/May2021/ROOT/RUN%i_ch2.root",r),"ADC0"},{Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/May2021/ROOT/RUN%i_ch4.root",r),"ADC1"},{Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/May2021/ROOT/RUN%i_ch5.root",r),"ADC2"}},adc,range1, range2,250,200);
  //~ana::Run_t myrun(r,{{Form("ROOT/Calibration20210501_ch4_%i.root",r),"ADC2"}},adc,range1, range2,30,30000);//calibrations SiPM
  //~ana::Run_t myrun(r,{{Form("ROOT/Calibration20210501_ch2_%i.root",r),"ADC2"}},adc,range1, range2,30,30000);//calibrations PMT
  myrun.SetGains(Gains);
  myrun.SetSPEAmps(SPEAmp);
  myrun.SelectChannels({0});
  //~myrun.SelectChannels(triggerchannels);
//  myrun.PlotPeakTimes();
//  myrun.Process(); 
  //~myrun.SetCutPedSTD();
  //~myrun.SetCutVariableVector("PreTriggerSTD",std::map<int,std::pair<double,double>>({{0,{0,4}},{1,{0,4.5}},{2,{0,4.5}}}) );
//  myrun.SetCutTriggerWaveformCuts(triggerchannels);
  //~myrun.SetCutMaxAmplitudeRange(amp1,amp2);
  //~myrun.SetCutChargeRange(0.4e-12,1e-12);
 //~myrun.SetCutPeakTimeRange();
  myrun.SetCutVariable("TEndMaxPeakRange",amp1,amp2);

 // if(NEvts!=-1)
  myrun.SetMaximumWaveformsToProcess(NEvts);
//  myrun.LoopWaveformsPMT(0);
  myrun.ParSet->setADCAmplitudeThreshold(25);

  myrun.Plot36("ScintProfFirstSignalBin",Form("AnalysisROOT/Run%i_ScintProfFirstSignalBin_%s.root",r,t.Data()),0,0);
  myrun.Plot36("ScintProf",Form("AnalysisROOT/Run%i_ScintProf_%s.root",r,t.Data()),0,0);
//    myrun.Plot36("ScintProfFirstSignalBin_NotNormalize",Form("AnalysisROOT/Run%i_ScintProfFirstSignalBin_NotNormalize.root",r),0,0);
  myrun.Close();
}

void AnalyseOsc(int r, double range1, double range2, std::vector<int> triggerchannels,int NEvts=-1, string adc="Osc")
{

  std::vector<double> Gains={0.56,3.61,3.83}; //ganancias en pC
  std::vector<double> SPEAmp={38.6,24.8,25.5};//Amplitud del SPE en cuentas de ADC
  for(int i=0;i<3;i++) Gains[i]=Gains[i]/1.602e-7; //(1e-19+12)
  ana::Run_t myrun(r,{{Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/ROOT/RUN%i_ch1.root",r),"ADC0"},{Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/ROOT/RUN%i_ch2.root",r),"ADC1"},{Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/ROOT/RUN%i_ch3.root",r),"ADC2"}},adc,range1, range2,150,2000);
  myrun.SetGains(Gains);
  myrun.SetSPEAmps(SPEAmp);
  myrun.SelectChannels(triggerchannels);
//  myrun.PlotPeakTimes();
//  myrun.SetCutPedSTD();
//  myrun.SetCutVariableVector("PreTriggerSTD",std::map<int,std::pair<double,double>>({{0,{0,4.5}},{1,{0,4.5}},{2,{0,4}}}) );
//  myrun.SetCutTriggerWaveformCuts(triggerchannels);
//  myrun.SetCutMaxAmplitudeRange(20,2000000);
// myrun.SetCutPeakTimeRange();
 // if(NEvts!=-1)
//  myrun.SetMaximumWaveformsToProcess(6000);
  myrun.ParSet->setADCAmplitudeThreshold(0.03);
  myrun.Process(); 
//  myrun.PlotPedSTDs();
//  myrun.LoopWaveforms();
//  myrun.Plot36("AmpRange","",0,1,"",0,1);

myrun.LoopWaveformsPMT(0);
//  myrun.Plot36("ScintProfFirstSignalBin",Form("AnalysisROOT/Run%i_ScintProfFirstSignalBin.root",r),0,0);
//  myrun.Plot36("ScintProf",Form("AnalysisROOT/Run%i_ScintProf.root",r),0,0);
//    myrun.Plot36("ScintProfFirstSignalBin_NotNormalize",Form("AnalysisROOT/Run%i_ScintProfFirstSignalBin_NotNormalize.root",r),0,0);
  myrun.Close();
}
void AnalyseOsc12(int r, double range1, double range2, std::vector<int> triggerchannels,int NEvts=-1, string adc="Osc")
{

  std::vector<double> Gains={0.56,3.61,3.83}; //ganancias en pC
  std::vector<double> SPEAmp={38.6,24.8,25.5};//Amplitud del SPE en cuentas de ADC
  for(int i=0;i<3;i++) Gains[i]=Gains[i]/1.602e-7; //(1e-19+12)
  ana::Run_t myrun(r,{{Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/ROOT/RUN%i_ch1.root",r),"ADC0"},{Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/ROOT/RUN%i_ch2.root",r),"ADC1"}},adc,range1, range2,30,2000);
  myrun.SetGains(Gains);
  myrun.SetSPEAmps(SPEAmp);
//  myrun.SelectChannels(triggerchannels);
  //~myrun.PlotPeakTimes();
//  myrun.SetCutPedSTD();
//  myrun.SetCutVariableVector("PreTriggerSTD",std::map<int,std::pair<double,double>>({{0,{0,4.5}},{1,{0,4.5}},{2,{0,4}}}) );
//  myrun.SetCutTriggerWaveformCuts(triggerchannels);
//  myrun.SetCutMaxAmplitudeRange(20,2000000);
// myrun.SetCutPeakTimeRange();
 // if(NEvts!=-1)
//  myrun.SetMaximumWaveformsToProcess(6000);
  myrun.ParSet->setADCAmplitudeThreshold(0.03);
  myrun.Process(); 
//  myrun.PlotPedSTDs();
//  myrun.LoopWaveforms();
//  myrun.Plot36("AmpRange","",0,1,"",0,1);
  //~myrun.LoopWaveformsPMT(0,0,"q");
//  myrun.Plot36("ScintProfFirstSignalBin",Form("AnalysisROOT/Run%i_ScintProfFirstSignalBin.root",r),0,0);
//  myrun.Plot36("ScintProf",Form("AnalysisROOT/Run%i_ScintProf.root",r),0,0);
//    myrun.Plot36("ScintProfFirstSignalBin_NotNormalize",Form("AnalysisROOT/Run%i_ScintProfFirstSignalBin_NotNormalize.root",r),0,0);
  myrun.Close();
}
void AnalyseOsc3(int r, double range1, double range2, std::vector<int> triggerchannels,int NEvts=-1, string adc="Osc")
{

  std::vector<double> Gains={0.4};//0.76,0.67 //ganancias de los PM en pC
  std::vector<double> SPEAmp={25.3};//3.2,3.1 //Amplitud del SPE a este voltaje
  for(int i=0;i<3;i++) Gains[i]=Gains[i]/1.602e-7; //(1e-19+12)
  ana::Run_t myrun(r,{{Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/ROOT/RUN%i_ch3.root",r),"ADC2"}},adc,range1, range2,30,2000);
  myrun.SetGains(Gains);
  myrun.SetSPEAmps(SPEAmp);
//  myrun.SelectChannels(triggerchannels);
//  myrun.PlotPeakTimes();
//  myrun.SetCutPedSTD();
//  myrun.SetCutVariableVector("PreTriggerSTD",std::map<int,std::pair<double,double>>({{0,{0,4.5}},{1,{0,4.5}},{2,{0,4}}}) );
//  myrun.SetCutTriggerWaveformCuts(triggerchannels);
//  myrun.SetCutMaxAmplitudeRange(20,2000000);
// myrun.SetCutPeakTimeRange();
 // if(NEvts!=-1)
//  myrun.SetMaximumWaveformsToProcess(6000);
  myrun.ParSet->setADCAmplitudeThreshold(0.03);
  myrun.Process(); 
//  myrun.PlotPedSTDs();
//  myrun.LoopWaveforms();
//  myrun.Plot36("AmpRange","",0,1,"",0,1);
  myrun.Plot36("ScintProfFirstSignalBin",Form("AnalysisROOT/Run%i_ScintProfFirstSignalBin.root",r),0,0);
//  myrun.Plot36("ScintProf",Form("AnalysisROOT/Run%i_ScintProf.root",r),0,0);
//    myrun.Plot36("ScintProfFirstSignalBin_NotNormalize",Form("AnalysisROOT/Run%i_ScintProfFirstSignalBin_NotNormalize.root",r),0,0);
  myrun.Close();
}
void AverageWaveform()
{
Analyse(5,0.0,1.0,{0,1,2},1);
/*Argumentos:
1. numero de Run
2. tiempo inicial donde empezar a buscar la señal de trigger (s)
3. tiempo final donde dejar de buscar la señal de trigger (s)
4. Canales de trigger, para limpiar ruido.
5. Versión del ADC usada (v1720 o DT5725)
*/
// PMT Problemas:
//~Analyse_min_max_given(
		//~15, 						//run
		//~1.25e-6,1.45e-6,	//Peak_Range
		//~{0},					//channels to plot 
		//~5000,					// Max Nevents to process
		//~"DT5725",			//Readout
		//~1.55e-6,1,			// Max Amplitude 
		//~"PMT_segunda_gaussiana");		// Output title after: Run%i_ScintProf_%s.root


//~Analyse_min_max_given(
		//~15, 						//run
		//~1.25e-6,1.45e-6,	//Peak_Range
		//~{0},					//channels to plot 
		//~5000,					// Max Nevents to process
		//~"DT5725",			//Readout
		//~0,1.55e-6,			// Max Amplitude 
		//~"PMT_primera_gaussiana");		// Output title after: Run%i_ScintProf_%s.root


//~//SPE Calibration
//~vector<int> runs ={2};

//~for (auto r:runs) Analyse_min_max_given(
		//~r, 						//run
		//~0.33e-6,0.41e-6,	//Peak_Range
		//~{0},					//channels to plot 
		//~5000,					// Max Nevents to process
		//~"DT5725",			//Readout
		//~18,33,			// Max Amplitude 
		//~"SPE_cal");		// Output title after: Run%i_ScintProf_%s.root
/*
struct runprop
{
   int run;
   std::vector<int> triggerChannels;
   int Nevts;
};

runprop myvector[]={
//SiPMs coinc 200
 {39,{1,2},10000},
 {27,{1,2},10000},
 {15,{1,2},10000},
 //~{50,{1,2},10000}
 //Laser
 {1002,{0,1,2} },
 //~{1002,{0,1,2} },
 //~{1003,{0,1,2} },


//Normal Runs: 5120 samples x 4ns sampling frec
//~//26-05-2021
//~{2,{0},20000},
//~{3,{0},20000},
//~{4,{0},20000},
//~{5,{1},20000},
//~{6,{1},20000},
//~{7,{1},20000},
//~{8,{2},20000},
//~{9,{2},20000},
//~{10,{2},20000},
//~{11,{1,2},20000},
//~{12,{1,2},20000},
//~{13,{1,2},20000},

};
 for (auto r : myvector)
 {
   if(r.run>1000) Analyse(r.run, 1.6e-6,1.7e-6,r.triggerChannels, r.Nevts);
   else Analyse(r.run, 1.25e-6,1.47e-6,r.triggerChannels, r.Nevts);

 }
//*/
}
