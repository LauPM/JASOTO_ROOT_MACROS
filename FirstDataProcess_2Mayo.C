/*
Esta macro preprocesa los datos, convirtiendo los ficheros .txt recién copiados a pnfs en un fichero root para facilitar el análisis.
*/

#include"lib/FirstDataProcess.h"

void FirstDataProcess_2Mayo()
{
	vector <int> runs;
	vector<int> channels={2,4,5};

	//~//30 Abril
	//~runs={1,2,3,4,5,6,7,8,9,10,11,12,13};
	//~for(auto r:runs) for (auto ch:channels) ReadAndDumpBinary(Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Apr2021/30Abril2021/Run%02i/wave%i.dat",r,ch),Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Apr2021/ROOT/RUN%i_ch%i.root",r,ch)) ;
	
	//~//1Mayo
	//~runs={14,15,16,17,18,19,20,21,22,23,24,25,26,27};
	//~for(auto r:runs) for (auto ch:channels) ReadAndDumpBinary(Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Apr2021/1Mayo2021/Run%02i/wave%i.dat",r,ch),Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Apr2021/ROOT/RUN%i_ch%i.root",r,ch)) ;

	//2Mayo
	runs={28,29,30,31,32,33,34,35,36,37,38,39};
	for(auto r:runs) for (auto ch:channels) ReadAndDumpBinary(Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Apr2021/2Mayo2021/Run%02i/wave%i.dat",r,ch),Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Apr2021/ROOT/RUN%i_ch%i.root",r,ch)) ;


	
	
	
	
	
	//-----------------------------------------------------feb stuff-------------------------------------------------------
/* LASER
 for (int r=5; r<6; r++) for (int ch=1; ch<3; ch++) ReadAndDumpBinary(Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/12Febrero2021/Calibracion_12_02/CAL%02i/wave%i.dat",r,ch),Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/ROOT/RUN1001_ch%i.root",ch)) ;
 for (int r=12; r<13; r++) for (int ch=3; ch<4; ch++) ReadAndDumpBinary(Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/12Febrero2021/Calibracion_12_02/CAL%02i/wave%i.dat",r,ch),Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/ROOT/RUN1001_ch%i.root",ch)) ;

 for (int r=5; r<6; r++) for (int ch=1; ch<3; ch++) ReadAndDumpBinary(Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/15Febrero2021/Calibracion_15_02/CAL%02i/wave%i.dat",r,ch),Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/ROOT/RUN1002_ch%i.root",ch)) ;
 for (int r=12; r<13; r++) for (int ch=3; ch<4; ch++) ReadAndDumpBinary(Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/15Febrero2021/Calibracion_15_02/CAL%02i/wave%i.dat",r,ch),Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/ROOT/RUN1002_ch%i.root",ch)) ;
*/

/*
 for (int r=1; r<6; r++) for (int ch=1; ch<3; ch++) ReadAndDumpBinary(Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/12Febrero2021/Calibracion_12_02/CAL%02i/wave%i.dat",r,ch),Form("ROOT/Calibration20210212_ch%i_%i.root",ch,r)) ;
 for (int r=6; r<13; r++) for (int ch=3; ch<4; ch++) ReadAndDumpBinary(Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/12Febrero2021/Calibracion_12_02/CAL%02i/wave%i.dat",r,ch),Form("ROOT/Calibration20210212_ch%i_%i.root",ch,r)) ;


 for (int r=1; r<6; r++) for (int ch=1; ch<3; ch++) ReadAndDumpBinary(Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/15Febrero2021/Calibracion_15_02/CAL%02i/wave%i.dat",r,ch),Form("ROOT/Calibration20210215_ch%i_%i.root",ch,r)) ;
 for (int r=6; r<13; r++) for (int ch=3; ch<4; ch++) ReadAndDumpBinary(Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/15Febrero2021/Calibracion_15_02/CAL%02i/wave%i.dat",r,ch),Form("ROOT/Calibration20210215_ch%i_%i.root",ch,r)) ;
*/

///*
/*
  for (int ch=1; ch<=3; ch++) ReadAndDumpBinaryLight(Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/10Febrero2021/RUN00/wave%i.dat",ch),Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/ROOT/RUN0_ch%i.root",ch)) ;
  for(int r=1; r<=1; r++) for (int ch=1; ch<=3; ch++) ReadAndDumpBinaryLight(Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/10Febrero2021/RUN%02i/wave%i.dat",r,ch),Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/ROOT/RUN%i_ch%i.root",r,ch)) ;
  for(int r=2; r<=13; r++) for (int ch=1; ch<=3; ch++) ReadAndDumpBinaryLight(Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/11Febrero2021/RUN%02i/wave%i.dat",r,ch),Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/ROOT/RUN%i_ch%i.root",r,ch)) ;
  for(int r=14; r<=24; r++) for (int ch=1; ch<=3; ch++) ReadAndDumpBinaryLight(Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/12Febrero2021/RUN%02i/wave%i.dat",r,ch),Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/ROOT/RUN%i_ch%i.root",r,ch)) ;
  for(int r=25; r<=35; r++) for (int ch=1; ch<=3; ch++) ReadAndDumpBinaryLight(Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/13Febrero2021/RUN%02i/wave%i.dat",r,ch),Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/ROOT/RUN%i_ch%i.root",r,ch)) ;
  for(int r=36; r<=46; r++) for (int ch=1; ch<=3; ch++) ReadAndDumpBinaryLight(Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/14Febrero2021/RUN%02i/wave%i.dat",r,ch),Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/ROOT/RUN%i_ch%i.root",r,ch)) ;
  for(int r=47; r<=56; r++) for (int ch=1; ch<=3; ch++) ReadAndDumpBinaryLight(Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/15Febrero2021/RUN%02i/wave%i.dat",r,ch),Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/ROOT/RUN%i_ch%i.root",r,ch)) ;
  for(int r=57; r<=57; r++) for (int ch=1; ch<=3; ch++) ReadAndDumpBinaryLight(Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/15Febrero2021/RUN%02i/wave%i.dat",r,ch),Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/ROOT/RUN%i_ch%i.root",r,ch)) ;
*/
//~vector <int> channels={2,4,5};
  //~for(int r=11; r<=12; r++) for (auto ch:channels) ReadAndDumpBinary(Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Apr2021/30Abril2021/Run%02i/wave%i.dat",r,ch),Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Apr2021/ROOT/RUN%i_ch%i.root",r,ch)) ;

/*
 for (int r=1; r<6; r++) for (int ch=1; ch<3; ch++) ReadAndDumpBinary(Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/16Febrero2021/Calibracion_16_02_2021/CAL%02i/wave%i.dat",r,ch),Form("ROOT/Calibration20210216_ch%i_%i.root",ch,r)) ;
 for (int r=6; r<13; r++) for (int ch=3; ch<4; ch++) ReadAndDumpBinary(Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/16Febrero2021/Calibracion_16_02_2021/CAL%02i/wave%i.dat",r,ch),Form("ROOT/Calibration20210216_ch%i_%i.root",ch,r)) ;
 for (int r=13; r<15; r++) for (int ch=1; ch<3; ch++) ReadAndDumpBinary(Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/16Febrero2021/Calibracion_16_02_2021/CAL%02i/wave%i.dat",r,ch),Form("ROOT/Calibration20210216_ch%i_%i.root",ch,r)) ;
*/


//Oscilloscope:
/*
bash-4.2$ ls 
ALFA/: (C1 2 y 3) Run 2001 2002
3mV  60mV

CAL_PMT/:
1000  1100  1200  1300	1400  1500

CAL_SIPMS/:
45  460-463  47  48

LUZ_PMT/: 2003 //LED
1000 (C3)

LUZ_SIPMS/: 2004 //LASER
460-463 (C1 y C2)

*/

//~for (int ch=1; ch<=3; ch++) ReadAndDumpOscilloscope(Form("/scratch/jasoto/SiPM_dune_IR02_analysis/Feb2021/OscData/IR02/ALFA/3mV/C%i--3mV--",ch), Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/ROOT/RUN2001_ch%i.root",ch));
//for (int ch=1; ch<=3; ch++) ReadAndDumpOscilloscope(Form("/scratch/jasoto/SiPM_dune_IR02_analysis/Feb2021/OscData/IR02/ALFA/60mV/C%i--60mV--",ch),Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/ROOT/RUN2002_ch%i.root",ch));
//ReadAndDumpOscilloscope("/scratch/jasoto/SiPM_dune_IR02_analysis/Feb2021/OscData/IR02/LUZ_PMT/1000/C3--1000--","/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/ROOT/RUN2003_ch3.root");
//for (int ch=1; ch<=2; ch++) ReadAndDumpOscilloscope(Form("/scratch/jasoto/SiPM_dune_IR02_analysis/Feb2021/OscData/IR02/LUZ_SIPMS/460-463/C%i--460-463--",ch), Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/ROOT/RUN2004_ch%i.root",ch));

// for (int ch=1; ch<3; ch++) ReadAndDumpOscilloscope(Form("/scratch/jasoto/SiPM_dune_IR02_analysis/Feb2021/OscData/IR02/CAL_SIPMS/45/C%i--45--",ch),Form("ROOT/Calibration20210216OSC_ch%i_0.root",ch)) ;
// for (int ch=1; ch<3; ch++) ReadAndDumpOscilloscope(Form("/scratch/jasoto/SiPM_dune_IR02_analysis/Feb2021/OscData/IR02/CAL_SIPMS/460-463/C%i--460-463--",ch),Form("ROOT/Calibration20210216OSC_ch%i_1.root",ch)) ;
// for (int ch=1; ch<3; ch++) ReadAndDumpOscilloscope(Form("/scratch/jasoto/SiPM_dune_IR02_analysis/Feb2021/OscData/IR02/CAL_SIPMS/47/C%i--47--",ch),Form("ROOT/Calibration20210216OSC_ch%i_2.root",ch)) ;
// for (int ch=1; ch<3; ch++) ReadAndDumpOscilloscope(Form("/scratch/jasoto/SiPM_dune_IR02_analysis/Feb2021/OscData/IR02/CAL_SIPMS/48/C%i--48--",ch),Form("ROOT/Calibration20210216OSC_ch%i_3.root",ch)) ;


// ReadAndDumpOscilloscope(Form("/scratch/jasoto/SiPM_dune_IR02_analysis/Feb2021/OscData/IR02/CAL_PMT/1000/C3--1000--"),Form("ROOT/Calibration20210216OSC_ch3_0.root")) ;

}

