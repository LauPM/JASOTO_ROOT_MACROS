/*Macro de ejemplo para visualizar eventos y como afectan los cortes que queremos establecer a la selección de eventos*/

#include"lib/headers.h"



void Analyse(int r, double range1, double range2, std::vector<int> triggerchannels, string adc="DT5725",string m="May")
{

  std::vector<double> Gains={0.56,3.61,3.83}; //ganancias en pC
  std::vector<double> SPEAmp={38.6,24.8,25.5};//Amplitud del SPE en cuentas de ADC
  for(int i=0;i<3;i++) Gains[i]=Gains[i]/1.602e-7; //(1e-19+12)

  ana::Run_t myrun(r,{{Form("/pc/choozdsk01/palomare/SiPM/SC_Fuente_Alpha_Oct/ROOT/run%i_ch4.root",r),"ADC2"}},adc,range1, range2,250,10000);
  myrun.SetGains(Gains);
  myrun.SetSPEAmps(SPEAmp);
  
  myrun.SelectChannels({0});
  myrun.Process();
  myrun.ParSet->t3=500e-9; //Fijamos el rango de integración de Q3 como 500ns tras el pico.
	
  // myrun.PlotPedestals();
  // myrun.PlotPeakTimes();
  
  //myrun.ParSet->range3=-10.e-9; 
  //myrun.ParSet->range4=70e-9; 
  //myrun.ParSet->range5=1.e-9; 
  //myrun.ParSet->range6=4.e-6; 
  //myrun.TH2Range34vsRange56(0);

  //F90:
  //myrun.ParSet->range3=-10.e-9; 
  //myrun.ParSet->range4=80e-9; 
  //myrun.ParSet->range5=-10.e-9; 
  //myrun.ParSet->range6=4.e-6; 
  //myrun.ParSet->Peak_ranges={-0.1e-6,0.1e-6,3e-6,4e-6,5e-6};
  //myrun.ParSet->Fixed_ranges={1.2e-6,1.4e-6,6.3e-6,7.3e-6,8.3e-6};

  // TH1F* h0 =myrun.TH1Charge(0,"Range","pC");
  TH1F* h0 =myrun.TH1Amp(0);

  h0->Draw();
  lets_pause();


  //myrun.TH2F90(0);

 
  // myrun.PlotPedSTDs();
  // myrun.TPVariableVsTime("MaxAmplitudeRange",0)->Draw("HIST"); lets_pause();
  // myrun.TH2VariableVsEvent("MaxAmplitudeRange",0)->Draw(); lets_pause();

  //CUTS
  //myrun.SetCutPedSTD(); //Cortamos señales con Pedestal STD > pedcut en ADC
  //myrun.SetCutOvershootingRange(overshootcut);//Cortamos señales con overshoot por encima de overshootcut (40ADC en el DT5725), para quitar ruido.
  //myrun.SetCutVariable("TEndMaxPeakRange",0,1.55e-6);
  //myrun.SetCutVariableVector("PreTriggerSTD",std::map<int,std::pair<double,double>>({{0,{0,12}},{1,{0,20}},{2,{0,12}},{3,{0,12}},{4,{0,12}}}) );
  //myrun.SetCutTriggerWaveformCuts(triggerchannels); //Cortamos los eventos que no pasan los cortes en los PM de trigger.
  //myrun.SetCutMaxAmplitudeRange(50,700); //Pedimos una amplitud mínima de maxampr1, y una máxima de maxampr2.

  //  myrun.LoopWaveformsPMT(2,0,"paqr");
  myrun.LoopWaveforms(0,"paqr",NULL);//, string BoxOption="", std::vector<double> *ranges=NULL, int Rebin=1, int CutOption=-1, //este loop nos muestra las waveforms evento a evento, marcando cuales nos estaríamos quitando con nuestros cortes.
  myrun.Close();
}

void EventDisplay()
{
  /*Argumentos:
  1. numero de Run
  2. tiempo inicial donde empezar a buscar la señal de trigger (s)
  3. tiempo final donde dejar de buscar la señal de trigger (s)
  4. Vector con los canales de trigger, para limpiar ruido.
  5. Versión del ADC usada (v1720 o DT5725)
  */
  Analyse(10, 1e-6,4e-6,{0},"DT5725","");//random trigger
}
