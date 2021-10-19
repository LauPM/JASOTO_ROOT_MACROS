/*
Macro para obtener la waveform promedio de un run.
La macro lee los ficheros con los runes guardados en ROOT, y crea un fichero en AnalysisROOT con los perfiles de centelleo para todos los canales.
*/

#include"lib/headers.h"


void Analyse(int r, double range1, double range2, std::vector<int> triggerchannels,int NEvts=-1, string adc="DT5725")
{

  std::vector<double> Gains={3.79,4.12,0.4};//0.76,0.67 //ganancias de los PM en pC
  std::vector<double> SPEAmp={25.1,26.5,25.3};//3.2,3.1 //Amplitud del SPE a este voltaje
  for(int i=0;i<3;i++) Gains[i]=Gains[i]/1.602e-7; //(1e-19+12)
  ana::Run_t myrun(r,{{Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/ROOT/RUN%i_ch1.root",r),"ADC0"},{Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/ROOT/RUN%i_ch2.root",r),"ADC1"},{Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/ROOT/RUN%i_ch3.root",r),"ADC2"}},adc,range1, range2,30,2000);
  myrun.SetGains(Gains);
  myrun.SetSPEAmps(SPEAmp);
  myrun.SelectChannels(triggerchannels);
  myrun.SetCutPedestalStatus();
  myrun.SetCutPedSTD();
  myrun.ParSet->setADCAmplitudeThreshold(12);
  myrun.ParSet->t3=500e-9;
//  myrun.Plot36("PreTriggerSTD","",0,1);
  myrun.SetCutVariableVector("PreTriggerSTD",std::map<int,std::pair<double,double>>({{0,{0,myrun.PedestalSTDCUT[0]}},{1,{0,myrun.PedestalSTDCUT[1]}},{2,{0,myrun.PedestalSTDCUT[2]}}}) );
//  myrun.SetCutOvershootingRange(10);
  myrun.SetCutMaxAmplitudeRange(20,32);
  myrun.SetCutVariable("ChargeMaxPeakRange",2e-12,6e-12);
  myrun.SetCutVariable("Q3MaxPeakRange",2e-12,6e-12);
  myrun.Plot36("AmpRange",Form(""),0,1);
  myrun.Plot36("Charge_Q3MaxPeakRange",Form(""),0,1);
  myrun.Plot36("Charge_MaxPeakRange",Form(""),0,1);
  myrun.LoopWaveformsPMT(0,0,"paq");

//  myrun.SetCutTriggerWaveformCuts(triggerchannels);
//  myrun.LoopWaveforms();
  myrun.SetMaximumWaveformsToProcess(NEvts);
  myrun.Plot36("ScintProf",Form("AnalysisROOT/Run%i_SPE_ScintProf.root",r),0,1);
//  myrun.Plot36("ScintProfFirstSignalBin",Form("AnalysisROOT/Run%i_SPE_ScintProfFirstSignalBin.root",r),0,1);
  myrun.Plot36("ScintProfBeginPeak",Form("AnalysisROOT/Run%i_SPE_ScintProfBeginPeak.root",r),0,1);
  myrun.Close();
}

void AverageWaveform_SPEScint()
{

/*Argumentos:
1. numero de Run
2. tiempo inicial donde empezar a buscar la señal de trigger (s)
3. tiempo final donde dejar de buscar la señal de trigger (s)
4. Canales de trigger, para limpiar ruido.
5. Versión del ADC usada (v1720 o DT5725)
*/


struct runprop
{
   int run;
   std::vector<int> triggerChannels;
   int Nevts;
};

runprop myvector[]={
//{1001,{0,1,2},-1},
//{1002,{0,1,2},-1},
//{0,{0,1},-1},
//{1,{0,1},-1},
//{2,{0,1},-1},
//{3,{0},-1},
//{4,{0},-1},
//{5,{0},10552},
//{6,{1},-1},
//{7,{1},-1},
//{8,{1},-1},
//{9,{2},-1},
//{10,{2},-1},
//{11,{2},-1},
//{12,{0,1},-1},
{13,{0,1},-1}/*,
{14,{0},-1},
{15,{0},-1},
{16,{0},-1},
{17,{1},-1},
{18,{1},-1},
{19,{1},6326},
{20,{2},-1},
{21,{2},-1},
{22,{2},-1},
{23,{0,1},-1},
{24,{0,1},-1},
{25,{0},-1},
{26,{0},-1},
{27,{0},-1},
{28,{1},-1},
{29,{1},-1},
{30,{1},4837},
{31,{2},-1},
{32,{2},-1},
{33,{2},-1},
{34,{0,1},-1},
{35,{0,1},-1},
{36,{0},-1},
{37,{0},-1},
{38,{0},-1},
{39,{1},-1},
{40,{1},-1},
{41,{1},3321},
{42,{2},-1},
{43,{2},-1},
{44,{2},-1},
{45,{0,1},-1},
{46,{0,1},-1},
{47,{0},-1},
{48,{0},-1},
{49,{0},-1},
{50,{1},-1},
{51,{1},-1},
{52,{1},-1},
{53,{2},-1},
{54,{2},-1},
{55,{2},-1},
{56,{0,1},-1},
{57,{0,1},-1}*/
};
 for (auto r : myvector)
 {
    Analyse(r.run, 4.0e-6,9.5e-6,r.triggerChannels, r.Nevts);

 }

//AnalyseOsc(2001, 1.02e-6,1.13e-6,{0,1,2},-1,"Osc");
//AnalyseOsc(2002, 1.02e-6,1.13e-6,{0,1,2},-1,"Osc");
//AnalyseOsc3(2003, 0.205e-6,0.220e-6,{2},-1,"Osc");
//AnalyseOsc12(2004, 1.04e-6,1.13e-6,{0,1},-1,"Osc");

}
