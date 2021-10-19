/*
Macro para obtener el espectro de carga de por canal y run.
Usa como input las ntuplas generadas con la macro SimpleAnalysis.C
*/
#include"lib/headers.h"


struct variable
{
  string var;
  string title;
  int limitdown;
  int limitup;
  double UnitConversion;
};
std::pair<float,float> DoGaussFit(TH1D * h, double r1, double r2)
{
 h->Draw("HIST");
 TF1 *f = new TF1("f","gaus",r1,r2);
 h->Fit(f,"LEMR");
 f->Draw("SAME");
 lets_pause();
 return std::pair<float,float>(f->GetParameter(1),f->GetParError(1));
}


std::pair<float,float> GetRate(int run,int mych, string var, bool Gauss)
{
  variable myvar;
  std::vector<double> Gains={3.79,4.12,0.4};
  std::vector<double> SPEAmp={25.1,26.5,25.3};
  if (var=="Q3") myvar={"Q3","Charge collected (pC)",0,5000,1.0};
  if (var=="Amp" && mych==2) myvar={"Amp","Amplitude (ADC)",0,20000,1.0};
  if (var=="Amp" && mych!=2) myvar={"Amp","Amplitude (ADC)",0,2000,1.0};
  if (var=="Q3PE"&& mych!=2) myvar={"Q3","Charge collected (PE)",0,110,1.0/Gains[mych]};
  if (var=="Q3PE"&& mych==2) myvar={"Q3","Charge collected (PE)",0,2000,1.0/Gains[mych]};
  if (var=="AmpPE") myvar={"Amp","Amplitude (PE)",0,200,1.0/SPEAmp[mych]};
  if (var=="QPeakPE"&& mych!=2) myvar={"QPeak","Charge collected (PE)",0,110,1.0/Gains[mych]};

 TFile *ifile= new TFile(Form("AnalysisROOT/Run%i_NTuple.root",run)); 
 TNtuple *nt;
 Float_t evt;
 Float_t ch; 
 Float_t _var; 
 Float_t time; 
 TH1D *h;
 nt= (TNtuple*)ifile->Get("ntuple");
 nt->SetBranchAddress("time",&time);
 nt->SetBranchAddress("evt",&evt);
 nt->SetBranchAddress("ch",&ch);
 if(var!="rate") nt->SetBranchAddress(myvar.var.c_str(),&_var);
 else  nt->SetBranchAddress("Amp",&_var);
 h=new TH1D(Form("h%i",run),Form("%i;%s",run,myvar.title.c_str()),1000,myvar.limitdown,myvar.limitup);
 h->SetLineWidth(2);
 int counter=0;
 for(int j=0;j<nt->GetEntries();j++)
 { 
   nt->GetEntry(j);
   if((int)ch!=mych) continue;
//   if(rate) if(_var>1100 || _var <250) continue; //alphas
   if(var=="rate") if(_var<1100) continue; //muons
   h->Fill(_var*myvar.UnitConversion);
   counter++;
 }
 nt->GetEntry(0);
 float firstime=time;
 nt->GetEntry(nt->GetEntries()-1);
 float lasttime=time;
 float duration = (lasttime - firstime)*8.e-9;
// TCanvas *c = new TCanvas("c");
// c->cd();
// h->Draw("HIST SAME");
// gPad->BuildLegend();
 float rate=1.0*counter/duration;
 float error=TMath::Sqrt(counter)/duration;
 if (var=="rate") return std::pair<float,float>(rate,error);

 if (Gauss && var=="Q3PE") return DoGaussFit(h,30,100);
 if (Gauss && var=="QPeakPE") return DoGaussFit(h,30,100);
 if (Gauss && var=="Amp") return DoGaussFit(h,250,1100);
 else return std::pair<float,float>(h->GetMean(),h->GetMeanError());
}
std::pair<float,float> GetRateRaw(int run,int mych, string var, bool Gauss)
{
  variable myvar;
  std::vector<double> Gains={3.79,4.12,0.4};
  std::vector<double> SPEAmp={25.1,26.5,25.3};
  if (var!="rate") {cout << "Option not implemented. " << endl; throw std::exception();}
  ana::Run_t r(run,{{Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/ROOT/RUN%i_ch1.root",run),"ADC0"},{Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/ROOT/RUN%i_ch2.root",run),"ADC1"},{Form("/pnfs/ciemat.es/data/neutrinos/SiPM_dune_IR02/Feb2021/ROOT/RUN%i_ch3.root",run),"ADC2"}},"DT5725",0,1,30,10);
  float counter= r.GetNEvents();
  float duration = r.getRunDuration();
  float rate=1.0*counter/duration;
  float error=TMath::Sqrt(counter)/duration;
  cout << "RATE RAW: " << run << " - "<<  rate << " " << error << endl;
  return std::pair<float,float>(rate,error);
}


TGraphErrors* GetTGraph(std::vector<std::pair<int,TDatime>> runs, int mych, string var, bool Gauss, bool Raw)
{

   TGraphErrors *tg = new TGraphErrors();
   for(auto r : runs)
   {
//       if (r.first==2) continue;
       std::pair<float,float> rate;
       if(Raw) rate = GetRateRaw(r.first,mych, var, Gauss);
       else    rate = GetRate   (r.first,mych, var, Gauss);
       tg->SetPoint(tg->GetN(),r.second.Convert(),rate.first);
       tg->SetPointError(tg->GetN()-1,0,rate.second); cout << r.second.GetDay() << " " << rate.first << endl;
   }
   tg->GetXaxis()->SetTimeFormat("%d-%b");
   tg->GetXaxis()->SetTimeDisplay(1);
   return tg;
}
void Draw(std::vector<int> ch, std::vector<string> th, string var, bool Gauss=false, bool Raw=false)
{
   RunCollection_t rc;
   std::vector<TGraphErrors*> Vtg;
   for(auto c : ch) for ( auto t : th)
   {
     cout << "Producing TGraph for " << c << " " << t << endl;
     std::vector<std::pair<int, TDatime>> v = rc.GetByTriggerThreshold(c,t); 
     TGraphErrors *tg=GetTGraph(v,c,var,Gauss,Raw);
     tg->SetLineColor(c+1);
     tg->SetMarkerColor(c+1);
     if(t=="25") tg->SetMarkerStyle(20);
     if(t=="35") tg->SetMarkerStyle(21);
     if(t=="750") tg->SetMarkerStyle(22);
     if(c==0)tg->SetTitle(Form("SiPM1 - Threshold %sADC",t.c_str()));
     if(c==1)tg->SetTitle(Form("SiPM2- Threshold %sADC",t.c_str()));
     if(c==2)tg->SetTitle(Form("PMT- Threshold %sADC",t.c_str()));
     Vtg.push_back(tg);
   }

   TCanvas *c = new TCanvas("c");
   TMultiGraph *m = new TMultiGraph(); for(int i=0; i<Vtg.size();i++) m->Add(Vtg[i]);
   m->Draw("ALP");
   m->GetXaxis()->SetTimeFormat("%d-%b");
   m->GetXaxis()->SetTimeDisplay(1); 
   m->GetXaxis()->SetTitle("Date");
   if(var=="rate") m->GetYaxis()->SetTitle("Rate (Hz)");
   if(var=="Q3PE") m->GetYaxis()->SetTitle("Charge (PE)"); gPad->BuildLegend(); lets_pause();
}
void DrawList(std::vector<int> ch, std::vector<string> th, std::vector<int> trig, string var, bool Gauss=false, string ofname="", bool Raw=false)
{
   RunCollection_t rc;
   std::vector<TGraphErrors*> Vtg;
   for(auto tr : trig)  for ( auto t : th) for(auto c : ch)
   {
     std::vector<std::pair<int, TDatime>> v = rc.GetByTriggerThreshold(tr,t); 
     cout << "Producing TGraph for " << c << " " << t << " " << v.size() <<  endl;
     for(auto i : v) cout << "\t" << i.first << " " << i.second.GetDay() << endl;
     TGraphErrors *tg=GetTGraph(v,c,var,Gauss,Raw); cout << tg->GetN() << endl;
     tg->SetLineColor(c+1);
     tg->SetMarkerColor(c+1);
     if(t=="25") tg->SetMarkerStyle(20);
     if(t=="35") tg->SetMarkerStyle(21);
     if(t=="750") tg->SetMarkerStyle(22);

     if(tr==0) tg->SetMarkerStyle(23);
     if(tr==10) tg->SetMarkerStyle(24);
     if(tr==1) tg->SetMarkerStyle(25);
     string triggerS;
     if(tr==0) triggerS="(0)";
     if(tr==1) triggerS="(1)";
     if(tr==10) triggerS="(0,1)";
     if(tr==2) triggerS="(2)";
     string channelS;

     if(c==0)channelS="SiPM1";
     if(c==1)channelS="SiPM2";
     if(c==2)channelS="PMT";
     tg->SetTitle(Form("%s - Trigger %s at %sADC",channelS.c_str(),triggerS.c_str(),t.c_str()));
     tg->SetName(Form("trigger%i_treshold%s_channel%i",tr,t.c_str(),c));
     Vtg.push_back(tg);
   }

   TCanvas *c = new TCanvas("c");
   TMultiGraph *m = new TMultiGraph(); for(int i=0; i<Vtg.size();i++) m->Add(Vtg[i]);
   m->Draw("ALP");
   m->GetXaxis()->SetTimeFormat("%d-%b");
   m->GetXaxis()->SetTimeDisplay(1); 
   m->GetXaxis()->SetTitle("Date");
   if(var=="rate") m->GetYaxis()->SetTitle("Rate (Hz)");
   if(var=="Q3PE") m->GetYaxis()->SetTitle("Charge (PE)"); gPad->BuildLegend(); lets_pause();
   if(ofname!="")
   {
     TFile ofile(ofname.c_str(),"RECREATE");
     ofile.cd();
     for(int i=0;i< Vtg.size();i++) Vtg[i]->Write(Vtg[i]->GetName());
     ofile.Close();
   }
}
void DrawRatesVsTime()
{
/* Self-triggering
   std::vector<string> th={"25","35","750"};
   std::vector<int> ch={0,1};
   Draw(ch,th,"rate");
   Draw(ch,th,"Q3PE");
   Draw(ch,th,"Q3PE",true);
//*/
/* //Separated trigger
   std::vector<string> th={"25","35","750"};
   std::vector<int> ch={0,1};
   std::vector<int> tr={2};
   DrawList(ch,th,tr,"rate");
   DrawList(ch,th,tr,"Q3PE",true);
//*/
//*
   std::vector<string> th={"25"};
   std::vector<int> ch={0,1};
   std::vector<int> tr={10};
//   DrawList(ch,th,tr,"rate",false,"",false);
//   DrawList(ch,th,tr,"Q3PE",true,"Q3PE_Gaussian.root");
//   DrawList(ch,th,tr,"Amp",true,"Amp_Gaussian.root");
   DrawList(ch,th,tr,"Q3PE",true,"QPeak_Gaussian.root");
//*/

}
