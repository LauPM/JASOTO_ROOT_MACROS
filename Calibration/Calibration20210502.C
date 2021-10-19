#include"../lib/headers.h"
string folder="";

 struct myrun
 {
   int number;
   int channel;
   string channelName;
   float voltage;
   string file;
   float speamp;
 };

TH1F* Analyze( myrun r)
{

  ana::Run_t myrun1(r.number,{{r.file,r.channelName}},"DT5725",0.47e-6,0.55e-6,30,-1);
  myrun1.SetPMTs({r.channelName}); //Manually set the PTMs of interest
  myrun1.SetVoltages({r.voltage});
//  myrun1.PlotPeakTimes();
//  myrun1.LoopWaveforms();

  myrun1.SetCutPedestalStatus();
  //myrun1.SetCutPeakTimeRange(0.33e-6,0.41e-6);
  TF1 fped("fped","gaus",myrun1.getPedestal(0)-10,myrun1.getPedestal(0)+10);
  TF1 fpedstd("fpedstd","gaus",0,20);
  TH1F * hpeaktime = myrun1.TH1PeakTime(0); hpeaktime->SetTitle(Form("%s_%.1fV_PeakTime",r.channelName.c_str(),r.voltage));
  TH1F * hped = myrun1.TH1Pedestal(0); hped->SetTitle(Form("%s_%.1fV_Pedestal",r.channelName.c_str(),r.voltage)); hped->Fit(&fped,"MER+","SAME");
  TH1F * hpedstd = myrun1.TH1PedSTD(0); hpedstd->SetTitle(Form("%s_%.1fV_PedestalSTD",r.channelName.c_str(),r.voltage));hpedstd->Fit(&fpedstd,"MER+","SAME");

  TCanvas *c = new TCanvas();
  gStyle->SetOptFit(1);
  c->Divide(1,3);
  c->cd(1);
  hpeaktime->Draw("HIST"); 
  c->cd(2);
  hped->Draw("HIST");fped.Draw("SAME");
  c->cd(3);
  hpedstd->Draw("HIST");fpedstd.Draw("SAME");
  //lets_pause();
  c->Print(Form("%s/Run%i_Channel%s_Baseline.pdf",folder.c_str(),r.number,r.channelName.c_str()),"pdf");

  myrun1.SetCutPedSTD();
  myrun1.SetCutOvershootingRange(40);
  myrun1.SetCutVariableVector("PreTriggerSTD",std::map<int,std::pair<double,double>>({{0,{0,12}},{1,{0,20}},{2,{0,12}},{3,{0,12}},{4,{0,12}}}) );

  TH1F* h0 = myrun1.TH1Charge(r.channel,"MaxPeakRange","pC",-50,100); h0->SetTitle(Form("%s_%.1fV_Charge",r.channelName.c_str(),r.voltage));// h0->Draw("HIST"); lets_pause();
  TH1F* h1 = myrun1.TH1AmpRange(0); h1->SetTitle(Form("%s_%.1fV_Amplitude",r.channelName.c_str(),r.voltage)); //h0->Draw("HIST"); lets_pause();
  h0->GetXaxis()->SetRange(autorangemin(h0)*0.9,autorangemax(h0)*1.1);
  h1->GetXaxis()->SetRange(autorangemin(h1)*0.9,autorangemax(h1)*1.1);
  TCanvas *c2 = new TCanvas();
  c2->Divide(2,1);
  c2->cd(1);gPad->SetLogy();
  h0->Draw("HIST");
  c2->cd(2);gPad->SetLogy();
  h1->Draw("HIST"); //lets_pause();
  c2->Print(Form("%s/Run%i_Channel%s_TH1.pdf",folder.c_str(),r.number,r.channelName.c_str()),"pdf");
  //lets_pause();

  TFile *ofile = new TFile(Form("%s/Run%i_Channel%s_hist.root",folder.c_str(),r.number,r.channelName.c_str()), "RECREATE");

  ofile->cd();
  hpeaktime->Write(Form("Run%i_%s_PeakTime",r.number,r.channelName.c_str()));
  hped->Write(Form("Run%i_%s_Ped",r.number,r.channelName.c_str()));
  hpedstd->Write(Form("Run%i_%s_PedSTD",r.number,r.channelName.c_str()));
  h0->Write(Form("Run%i_%s_Charge",r.number,r.channelName.c_str()));
  h1->Write(Form("Run%i_%s_Amplitude",r.number,r.channelName.c_str()));
  ofile->Close();
//  myrun1.SetCutMaxAmplitude(r.speamp*0.5,r.speamp*1.5);
//  TH1D* h=myrun1.TH1ScintProf(0);
//  h->SetTitle(Form("%s_%.1fV",r.channelName.c_str(),r.voltage));
  delete c;
  delete c2;
  return h0;
}

void Channel( int ch, std::vector<int> run, std::vector<float> volt)
{
  std::vector<myrun> r;
  for(int i=0; i<run.size(); i++)
  {
    r.push_back({i,0,Form("ADC%i",ch),volt[i],Form("../ROOT/Calibration%s_ch%i_%i.root",folder.c_str(),ch,run[i]),18});
  }
  std::vector<TH1F*> h; h.resize(run.size());

  for(int i=0; i<run.size(); i++)
  {
    h[i] = Analyze(r[i]); h[i]->SetLineColor(1+i); h[i]->SetLineWidth(2);

  }
  TCanvas *c = new TCanvas("c");h[0]->Draw("HIST");
  for(int i=1; i<run.size(); i++) h[i]->Draw("HIST SAME");
  gPad->BuildLegend();
  lets_pause();
}

void FitChannel(int mych, std::vector<int> runlist, std::vector<std::pair<float,float>> limits, string var="Charge")
{
  std::vector<TFile*> file; file.resize(runlist.size());
  std::vector<TH1F*> h;h.resize(runlist.size());
  cout << "Analyzing channel " << mych << endl;
  for (auto run : runlist)
  {
    file[run]= new TFile(Form("%s/Run%i_ChannelADC%i_hist.root",folder.c_str(),run,mych), "READ");
    if(!file[run]) {cout << "file " << Form("%s/Run%i_ChannelADC%i_hist.root",folder.c_str(),run,mych) << " NOT FOUND!" << endl;}
    else file[run]->ls();
    h[run]=(TH1F*)file[run]->Get(Form("Run%i_ADC%i_%s",run,mych,var.c_str()));
    if(!h[run]) {cout << "histogram " << Form("Run%i_ADC%i_%s",run,mych,var.c_str()) << " NOT FOUND!" << endl;}
     gStyle->SetOptFit(1);
    if(limits[run].first!=limits[run].second){ h[run]->Fit("gaus","QMER+","SAME",limits[run].first,limits[run].second);}
    h[run]->Draw(); gPad->SetLogy();gPad->Update();
    lets_pause();
  }
  cout << " Let's dump fit results " << endl;
  TFile *ofile = new TFile(Form("%s/ChannelADC%i_Fits_%s.root",folder.c_str(),mych,var.c_str()),"RECREATE");
  ofile->cd();
  for (auto run : runlist) h[run]->Write(Form("Run%i_ADC%i_%s",run,mych,var.c_str()));
  ofile->Close();
  cout << "Dumped to " <<Form("%s/ChannelADC%i_Fits_%s.root",folder.c_str(),mych,var.c_str()) << endl;
}
void SetNiceOpStat(TH1F *h)
{
 TPaveStats *st =
 (TPaveStats*)h->GetListOfFunctions()->FindObject("stats");
 if(!st) return 0;
 st->SetX1NDC(0.5); 
 st->SetX2NDC(0.9); 
 st->SetY1NDC(0.5); 
 st->SetY2NDC(0.9); 
}
void PlotHistograms()
{

  ofstream ofa(Form("%s/Amplitudes.txt",folder.c_str()));
  ofstream ofc(Form("%s/Charges.txt",folder.c_str()));
  std::map<int,std::vector<int>> ChannelRunMap = {{4,{0,1,2,3}},{5,{0,1,2,3}},{2,{0,1,2,3,4,5}}};
  std::map<int,std::vector<float>>ChannelVoltageMap = {{4,{45,46,47,48}},{5,{45,46,47,48}},{2,{1000,1100,1200,1300,1400,1500}}};

  const int channels[3]={4,5,2};
  TFile *fcharge[3];
  TFile *famp[3];

  TH1F* hcharge[6][3];
  TH1F* hamp[6][3];
  for (int i=0; i< 3; i++)
  {
    fcharge[i] = new TFile(Form("%s/ChannelADC%i_Fits_Charge.root",folder.c_str(),channels[i]),"READ");// fcharge[i]->ls();
    famp[i] = new TFile(Form("%s/ChannelADC%i_Fits_Amplitude.root",folder.c_str(),channels[i]),"READ");// famp[i]->ls();
    for (int run=0; run<ChannelRunMap[channels[i]].size(); run++) hcharge[run][i]=(TH1F*)fcharge[i]->Get(Form("Run%i_ADC%i_Charge",run,channels[i]));
    for (int run=0; run<ChannelRunMap[channels[i]].size(); run++) hamp[run][i]=(TH1F*)famp[i]->Get(Form("Run%i_ADC%i_Amplitude",run,channels[i]));
  }

  ofstream ofsQ(Form("%s/QVector.txt",folder.c_str()));
  ofstream ofsA(Form("%s/AVector.txt",folder.c_str()));
  for (int i=0; i< 3; i++)
  {
   ofsQ << "Qch" << channels[i] << "={";
   ofsA << "Ach" << channels[i] << "={";
   for (int run=0; run<ChannelRunMap[channels[i]].size(); run++)
   {

     cout << "Ch " << channels[i] << " - Run " << run << endl;
     TCanvas *c2 = new TCanvas(); if(!hamp[run][i]) cout << "Warning, hamp not found" << endl; if(!hcharge[run][i]) cout << "Warning, hcharge not found" << endl;
     SetNiceOpStat(hamp[run][i]);
     SetNiceOpStat(hcharge[run][i]);

// Set stat options
gStyle->SetStatY(0.5);                
// Set y-position (fraction of pad size)
gStyle->SetStatX(0.5);                
// Set x-position (fraction of pad size)
gStyle->SetStatW(0.5);                
// Set width of stat-box (fraction of pad size)
gStyle->SetStatH(0.5);                

    c2->Divide(2,1); gStyle->SetOptFit(1);
    c2->cd(1);gPad->SetLogy();
    hcharge[run][i]->Draw(""); //if(hcharge[run][i]->GetListOfFunctions()->FindObject("gaus")) cout << hcharge[run][i]->GetTitle() << " " << ((TF1*)(hcharge[run][i]->GetListOfFunctions()->FindObject("gaus")))->GetParameter(1) << endl;
    c2->cd(2);gPad->SetLogy();
    hamp[run][i]->Draw("");
    if(hamp[run][i]->GetListOfFunctions()->FindObject("gaus")) cout << hamp[run][i]->GetTitle() << " " << ((TF1*)(hamp[run][i]->GetListOfFunctions()->FindObject("gaus")))->GetParameter(1) << endl;
    if(hamp[run][i]->GetListOfFunctions()->FindObject("gaus")) ofa << hamp[run][i]->GetTitle() << " " << ((TF1*)(hamp[run][i]->GetListOfFunctions()->FindObject("gaus")))->GetParameter(1) << endl;
    if(hcharge[run][i]->GetListOfFunctions()->FindObject("gaus")) ofc << hcharge[run][i]->GetTitle() << " " << ((TF1*)(hcharge[run][i]->GetListOfFunctions()->FindObject("gaus")))->GetParameter(1) << endl;
    lets_pause();
    if(run==0) c2->Print(Form("%s/%s_Fits_Channel%i.pdf(",folder.c_str(),folder.c_str(),channels[i]));
    else if(run==ChannelRunMap[channels[i]].size()-1) c2->Print(Form("%s/%s_Fits_Channel%i.pdf)",folder.c_str(),folder.c_str(),channels[i]));
    else c2->Print(Form("%s/%s_Fits_Channel%i.pdf",folder.c_str(),folder.c_str(),channels[i]));
    if((TF1*)(hcharge[run][i]->GetListOfFunctions()->FindObject("gaus")))
    { 
     ofsQ << "{" << ChannelVoltageMap[channels[i]][run] << "," 
         << ((TF1*)(hcharge[run][i]->GetListOfFunctions()->FindObject("gaus")))->GetParameter(1) << ","
         << ((TF1*)(hcharge[run][i]->GetListOfFunctions()->FindObject("gaus")))->GetParError(1) << "},";
    }
    if(((TF1*)(hamp[run][i]->GetListOfFunctions()->FindObject("gaus"))))
    {
      ofsA << "{" << ChannelVoltageMap[channels[i]][run] << "," 
         << ((TF1*)(hamp[run][i]->GetListOfFunctions()->FindObject("gaus")))->GetParameter(1) << ","
         << ((TF1*)(hamp[run][i]->GetListOfFunctions()->FindObject("gaus")))->GetParError(1) << "},";
    }
   }
   
   ofsQ << "};" << endl;;
   ofsA << "};" << endl;;
  }

}
void Calibration20210502()
{
//Macro ejecutable de forma escalada, se puede comentar un paso una vez ha terminado, y descomentar el siguiente. El output de un paso es usado como input en el siguiente.

  folder="20210502"; //directorio donde se volcarán todos los outputs.
  /*
  Los archivos procesados deben tener el formato de nombre chX_Y.root, con X el número de canal de ADC, y Y 1,2,3,4,5 en función del número de run de calibración. Si no fuera el caso, se puede adaptar cambiando la función Channel, que lee 
  */

/*
CALIBRACIÓN
CAL01 – SiPM 45V PMT Off LASER 380%
CAL02 – SiPM 46V PMT Off LASER 380%
CAL03 – SiPM 47V PMT Off LASER 380%
CAL04 – SiPM 48V PMT Off LASER 380%

CAL05 – SiPM 46V PMT Off LASER 1000%

CAL06 – PMT 1000 SiPMs Off LASER 380%
CAL07 – PMT 1100 SiPMs Off LASER 380%
CAL08 – PMT 1200 SiPMs Off LASER 380%
CAL09 – PMT 1300 SiPMs Off LASER 380%
CAL10 – PMT 1400 SiPMs Off LASER 380%
CAL11 – PMT 1500 SiPMs Off LASER 380%

CAL12 – PMT 1000 SiPMs Off LASER 1000%
*/

/*
// Paso 1:Genero los histogramas del SPE
//Hay que adaptar la función GetChannelHVVector si el mapping de HV channel -> ADC channel ha cambiado!!!
//Hay que adaptar la función Channel si número de runes no es 5!!!
  Channel(4,{1,2,3,4},{45,46,47,48}); 
  Channel(5,{1,2,3,4},{45,46,47,48});
  Channel(2,{6,7,8,9,10,11},{1000,1100,1200,1300,1400,1500});
//*/
// tras ejecutar este paso, puedes echar un vistazo en folder, los pdf generados con los histogramas generados.

/*
  //Paso 2, hago el fit en el SPE en carga y amplitud 

  std::vector<std::pair<float,float>> limitsch4 = { {1,3.5}, {2,5}, {3.5,7}, {4.5,9.5} };
  FitChannel(4,{0,1,2,3},limitsch4,"Charge");
  std::vector<std::pair<float,float>> limitsch5 = { {1,3.5}, {2,5}, {3.5,7}, {4.5,9.5} };
  FitChannel(5,{0,1,2,3},limitsch5,"Charge");
  std::vector<std::pair<float,float>> limitsch2 = { {0,0}, {0.2,2}, {0.8,3.5}, {1.5,6}, {3,12},{5,14} };
  FitChannel(2,{0,1,2,3,4,5},limitsch2,"Charge");


  std::vector<std::pair<float,float>> limitsAch4 = { {14,24}, {18,33}, {22,40}, {29,48} };
  FitChannel(4,{0,1,2,3},limitsAch4,"Amplitude");
  std::vector<std::pair<float,float>> limitsAch5 = { {13,24}, {18,33}, {25,40}, {30,45} };
  FitChannel(5,{0,1,2,3},limitsAch5,"Amplitude");
  std::vector<std::pair<float,float>> limitsAch2 = { {0,0}, {30,120}, {60,250}, {100,500} , {200,800}, {300,1200} };
  FitChannel(2,{0,1,2,3,4,5},limitsAch2,"Amplitude");
//*/

// Dibujo el resutlado de los fits.
  PlotHistograms();
}
