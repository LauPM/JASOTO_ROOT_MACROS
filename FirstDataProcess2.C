/*
Esta macro preprocesa los datos, convirtiendo los ficheros .txt recién copiados a pnfs en un fichero root para facilitar el análisis.
*/

#include"lib/FirstDataProcess.h"

void FirstDataProcess2()
{
{//May 2021 Cajita
	
	vector <int> runs;
	vector<int> channels={2,4,5};
	string t1,t2;

	//---------------------25 Mayo----------------------- (50 micras)
	t1="/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/May2021/25Mayo2021/";
	t2="/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/May2021/";

	//NormalRuns
	for(int r=1;r<3;r++) for (auto ch:channels) ReadAndDumpBinary(t1+Form("Run%02i/wave%i.dat",r,ch),t2+Form("ROOT/RUN%i_ch%i.root",r,ch)) ;
	
	//~//---------------------25a26 Mayo----------------------- (20 micras)
	//~t1="/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/May2021/25a26Mayo2021/";
	//~t2="/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/May2021/";

	//~//NormalRuns
	//~for(int r=3;r<4;r++) for (auto ch:channels) ReadAndDumpBinary(t1+Form("Run%02i/wave%i.dat",r,ch),t2+Form("ROOT/RUN%i_ch%i.root",r,ch)) ;
	
	
	//~//---------------------26 Mayo-----------------------
	//~t1="/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/May2021/26Mayo2021/";
	//~t2="/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/May2021/";

	//~//NormalRuns
	//~for(int r=5;r<16;r++) for (auto ch:channels) ReadAndDumpBinary(t1+Form("Run%02i/wave%i.dat",r,ch),t2+Form("ROOT/RUN%i_ch%i.root",r,ch)) ;
	 
	 //~//Laser
	//~for (int r=5; r<6; r++) for (int ch=4;ch<6;ch++) ReadAndDumpBinary(t1+Form("CAL%02i/wave%i.dat",r,ch),t2+Form("ROOT/RUN1001_ch%i.root",ch)) ;
	//~for (int r=12; r<13; r++) for (int ch=2;ch<3;ch++) ReadAndDumpBinary(t1+Form("CAL%02i/wave%i.dat",r,ch),t2+Form("ROOT/RUN1001_ch%i.root",ch)) ;

	//~//Calibration
	//~for (int r=1; r<5; r++) for (int ch=4; ch<6; ch++) ReadAndDumpBinary(t1+Form("CAL%02i/wave%i.dat",r,ch),t2+Form("ROOT/Calibration20210526_ch%i_%i.root",ch,r)) ;
	//~for (int r=6; r<12; r++) for (int ch=2; ch<3; ch++) ReadAndDumpBinary(t1+Form("CAL%02i/wave%i.dat",r,ch),t2+Form("ROOT/Calibration20210526_ch%i_%i.root",ch,r)) ;

	//~//---------------------27 Mayo-----------------------
	//~t1="/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/May2021/27Mayo2021/";
	//~t2="/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/May2021/";

	//~//NormalRuns
	//~for(int r=17;r<28;r++) for (auto ch:channels) ReadAndDumpBinary(t1+Form("Run%02i/wave%i.dat",r,ch),t2+Form("ROOT/RUN%i_ch%i.root",r,ch)) ;
	 
	 //~//Laser
	//~for (int r=5; r<6; r++) for (int ch=4;ch<6;ch++) ReadAndDumpBinary(t1+Form("CAL%02i/wave%i.dat",r,ch),t2+Form("ROOT/RUN1001_ch%i.root",ch)) ;
	//~for (int r=12; r<13; r++) for (int ch=2;ch<3;ch++) ReadAndDumpBinary(t1+Form("CAL%02i/wave%i.dat",r,ch),t2+Form("ROOT/RUN1001_ch%i.root",ch)) ;

	//~//Calibration
	//~for (int r=1; r<5; r++) for (int ch=4; ch<6; ch++) ReadAndDumpBinary(t1+Form("CAL%02i/wave%i.dat",r,ch),t2+Form("ROOT/Calibration20210526_ch%i_%i.root",ch,r)) ;
	//~for (int r=6; r<12; r++) for (int ch=2; ch<3; ch++) ReadAndDumpBinary(t1+Form("CAL%02i/wave%i.dat",r,ch),t2+Form("ROOT/Calibration20210526_ch%i_%i.root",ch,r)) ;

}

{// April/May 2021
		
	//~vector <int> runs;
	//~vector<int> channels={2,4,5};
	//---------------------Normal runs-----------------------
	//~//30 Abril
	//~runs={1,2,3,4,5,6,7,8,9,10,11,12,13};
	//~for(auto r:runs) for (auto ch:channels) ReadAndDumpBinary(Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Apr2021/30Abril2021/Run%02i/wave%i.dat",r,ch),Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Apr2021/ROOT/RUN%i_ch%i.root",r,ch)) ;
	
	//~//1Mayo
	//~runs={14,15,16,17,18,19,20,21,22,23,24,25,26,27};
	//~for(auto r:runs) for (auto ch:channels) ReadAndDumpBinary(Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Apr2021/1Mayo2021/Run%02i/wave%i.dat",r,ch),Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Apr2021/ROOT/RUN%i_ch%i.root",r,ch)) ;

	//~//2Mayo
	//~runs={28,29,30,31,32,33,34,35,36,37,38,39};
	//~for(auto r:runs) for (auto ch:channels) ReadAndDumpBinary(Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Apr2021/2Mayo2021/Run%02i/wave%i.dat",r,ch),Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Apr2021/ROOT/RUN%i_ch%i.root",r,ch)) ;

	//3Mayo
	//~runs={40,41,42,43,44,45,46,47,48,49,50,51};
	//~for(auto r:runs) for (auto ch:channels) ReadAndDumpBinary(Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Apr2021/3Mayo2021/Run%02i/wave%i.dat",r,ch),Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Apr2021/ROOT/RUN%i_ch%i.root",r,ch)) ;

	//4 Mayo
	//~runs={52,53,54,55,56,57,58,59,60,61,62};
	//~for(auto r:runs) for (auto ch:channels) ReadAndDumpBinary(Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Apr2021/4Mayo2021/Run%02i/wave%i.dat",r,ch),Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Apr2021/ROOT/RUN%i_ch%i.root",r,ch)) ;

	//---------------Laser-------------------------

	//~//1 Mayo
	//~for (int r=5; r<6; r++) for (int ch=4;ch<6;ch++) ReadAndDumpBinary(Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Apr2021/1Mayo2021/CAL%02i/wave%i.dat",r,ch),Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Apr2021/ROOT/RUN1001_ch%i.root",ch)) ;
	//~for (int r=12; r<13; r++) for (int ch=2;ch<3;ch++) ReadAndDumpBinary(Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Apr2021/1Mayo2021/CAL%02i/wave%i.dat",r,ch),Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Apr2021/ROOT/RUN1001_ch%i.root",ch)) ;

	//~//2 Mayo
	//~for (int r=5; r<6; r++) for (int ch=4;ch<6;ch++) ReadAndDumpBinary(Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Apr2021/2Mayo2021/CAL%02i/wave%i.dat",r,ch),Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Apr2021/ROOT/RUN1002_ch%i.root",ch)) ;
	//~for (int r=12; r<13; r++) for (int ch=2;ch<3;ch++) ReadAndDumpBinary(Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Apr2021/2Mayo2021/CAL%02i/wave%i.dat",r,ch),Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Apr2021/ROOT/RUN1002_ch%i.root",ch)) ;

	//~//3 Mayo
	//~for (int r=5; r<6; r++) for (int ch=4;ch<6;ch++) ReadAndDumpBinary(Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Apr2021/3Mayo2021/CAL%02i/wave%i.dat",r,ch),Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Apr2021/ROOT/RUN1003_ch%i.root",ch)) ;
	//~for (int r=12; r<13; r++) for (int ch=2;ch<3;ch++) ReadAndDumpBinary(Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Apr2021/3Mayo2021/CAL%02i/wave%i.dat",r,ch),Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Apr2021/ROOT/RUN1003_ch%i.root",ch)) ;
	
	//4 Mayo
	//~for (int r=5; r<6; r++) for (int ch=4;ch<6;ch++) ReadAndDumpBinary(Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Apr2021/4Mayo2021/CAL%02i/wave%i.dat",r,ch),Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Apr2021/ROOT/RUN1004_ch%i.root",ch)) ;
	//~for (int r=12; r<13; r++) for (int ch=2;ch<3;ch++) ReadAndDumpBinary(Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Apr2021/4Mayo2021/CAL%02i/wave%i.dat",r,ch),Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Apr2021/ROOT/RUN1004_ch%i.root",ch)) ;

	//---------------Calibrations--------------------
	
	//1Mayo
	//~for (int r=1; r<5; r++) for (int ch=4; ch<6; ch++) ReadAndDumpBinary(Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Apr2021/1Mayo2021/CAL%02i/wave%i.dat",r,ch),Form("ROOT/Calibration20210501_ch%i_%i.root",ch,r)) ;
	//~for (int r=6; r<12; r++) for (int ch=2; ch<3; ch++) ReadAndDumpBinary(Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Apr2021/1Mayo2021/CAL%02i/wave%i.dat",r,ch),Form("ROOT/Calibration20210501_ch%i_%i.root",ch,r)) ;

	//2Mayo
	//~for (int r=1; r<5; r++) for (int ch=4; ch<6; ch++) ReadAndDumpBinary(Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Apr2021/2Mayo2021/CAL%02i/wave%i.dat",r,ch),Form("ROOT/Calibration20210502_ch%i_%i.root",ch,r)) ;
	//~for (int r=6; r<12; r++) for (int ch=2; ch<3; ch++) ReadAndDumpBinary(Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Apr2021/2Mayo2021/CAL%02i/wave%i.dat",r,ch),Form("ROOT/Calibration20210502_ch%i_%i.root",ch,r)) ;

	//~//3Mayo
	//~for (int r=1; r<5; r++) for (int ch=4; ch<6; ch++) ReadAndDumpBinary(Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Apr2021/3Mayo2021/CAL%02i/wave%i.dat",r,ch),Form("ROOT/Calibration20210503_ch%i_%i.root",ch,r)) ;
	//~for (int r=6; r<12; r++) for (int ch=2; ch<3; ch++) ReadAndDumpBinary(Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Apr2021/3Mayo2021/CAL%02i/wave%i.dat",r,ch),Form("ROOT/Calibration20210503_ch%i_%i.root",ch,r)) ;

	//4Mayo
	//~for (int r=1; r<5; r++) for (int ch=4; ch<6; ch++) ReadAndDumpBinary(Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Apr2021/4Mayo2021/CAL%02i/wave%i.dat",r,ch),Form("ROOT/Calibration20210504_ch%i_%i.root",ch,r)) ;
	//~for (int r=6; r<12; r++) for (int ch=2; ch<3; ch++) ReadAndDumpBinary(Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Apr2021/4Mayo2021/CAL%02i/wave%i.dat",r,ch),Form("ROOT/Calibration20210504_ch%i_%i.root",ch,r)) ;

	
}//April/May2021	

	//-----------------------------------------------------feb stuff-------------------------------------------------------
{	
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
}

