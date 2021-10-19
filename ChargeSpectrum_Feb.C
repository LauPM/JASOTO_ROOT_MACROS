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
void Draw(std::vector<int> mych, std::vector<int> runs, std::vector<string> name, bool rate, std::vector<string> var, TVirtualPad *pad=NULL, float CustomMaxRange=0, int Rebin=2 )
{
  bool fit=false;
  std::vector<double> Gains={3.79,4.12,0.48}; //ganancias en pC
  std::vector<double> SPEAmp={25.1,26.5,28.0};//Amplitud del SPE en cuentas de ADC
 int n=runs.size(); 
 std::vector<variable> myvar(n);
 for(int i=0;i<n;i++)
 {
  if (var[i]=="Q3") myvar[i]={"Q3","Charge collected (pC)",0,5000,1.0};
  if (var[i]=="Amp" && mych[i]==2) myvar[i]={"Amp","Amplitude (ADC)",0,20000,1.0};
  if (var[i]=="Amp" && mych[i]!=2) myvar[i]={"Amp","Amplitude (ADC)",0,20000,1.0};

  if (var[i]=="Q3PE"&& mych[i]!=2) myvar[i]={"Q3","Charge collected (PE)",0,110,1.0/Gains[mych[i]]};
  if (var[i]=="Q3PE"&& mych[i]==2) myvar[i]={"Q3","Charge collected (PE)",0,2000,1.0/Gains[mych[i]]};

  if (var[i]=="QPeak"&& mych[i]==2) myvar[i]={"QPeak","Charge Peak",0,2000,1.0};
  if (var[i]=="QPeak"&& mych[i]!=2) myvar[i]={"QPeak","Charge Peak",0,2000,1.0};

  if (var[i]=="QPeakPE"&& mych[i]==2) myvar[i]={"QPeakPE","Charge Peak (PE)",0,6000*Rebin,1.0/Gains[mych[i]]};
  if (var[i]=="QPeakPE"&& mych[i]!=2) myvar[i]={"QPeakPE","Charge Peak (PE)",0,110*Rebin,1.0/Gains[mych[i]]};

  if (var[i]=="AmpPE"&& mych[i]!=2) myvar[i]={"Amp","Amplitude (PE)",0,200,1.0/SPEAmp[mych[i]]};
  if (var[i]=="AmpPE"&& mych[i]==2) myvar[i]={"Amp","Amplitude (PE)",0,1000,1.0/SPEAmp[mych[i]]};
 }
 if(CustomMaxRange!=0) for(int i=0;i<n;i++) myvar[i].limitup=CustomMaxRange;

 TFile *ifile[n];
 for(int i=0;i<n;i++) ifile[i]= new TFile(Form("AnalysisROOT_JASOTO_FEB/Run%i_NTuple.root",runs[i])); 
 TNtuple *nt[n];
 Float_t ch; 
 Float_t time; 
 Float_t _var; 
  TH1D *h[n];
 for(int i=0;i<n;i++)
 {
   nt[i]= (TNtuple*)ifile[i]->Get("ntuple");
   nt[i]->SetBranchAddress("ch",&ch);
   nt[i]->SetBranchAddress("time",&time);
   nt[i]->SetBranchAddress(myvar[i].var.c_str(),&_var);
   if(rate) h[i]=new TH1D(Form("h%i",i),Form("%s;%s; Events/s",name[i].c_str(),myvar[i].title.c_str()),400,myvar[i].limitdown,myvar[i].limitup);
   else h[i]=new TH1D(Form("h%i",i),Form("%s;%s; Probabilty",name[i].c_str(),myvar[i].title.c_str()),400,myvar[i].limitdown,myvar[i].limitup);
   h[i]->SetLineColor(i+1);
   h[i]->SetLineWidth(2);
 }
 cout << "Drawing " << n<< endl;
 for(int i=0;i<n;i++)
 {
  for(int j=0;j<nt[i]->GetEntries();j++)
  { 
   nt[i]->GetEntry(j);
   if(ch!=mych[i]) continue;
   //if (runs[i]==19 && ch==1) {cout << ch << " " << _var << " " << time << " " << mych[i] << " - " << _var*myvar[i].UnitConversion << endl; lets_pause();}
   h[i]->Fill(_var*myvar[i].UnitConversion);
	//~cout<<_var*myvar[i].UnitConversion<<endl;//debug
  }

  nt[i]->GetEntry(0);
  double firstime=time;
  nt[i]->GetEntry(nt[i]->GetEntries()-1);
  double lasttime=time; 
  Double_t duration = (lasttime - firstime)*8.e-9;
  //cout << duration << endl; lets_pause();
  if(rate) h[i]->Scale(1./duration/60.0);
  else h[i]->Scale(1./h[i]->GetEntries());
 }

 TCanvas *c;
 if(!pad){ c  = new TCanvas("c"); c->cd();}
 else {pad->cd();}
 gStyle->SetOptTitle(0); gStyle->SetOptStat(0);
 gPad->SetLogy();
 for(int i=0;i<n;i++){ /*h[i]->Rebin()*/;h[i]->Draw("HIST SAME"); 

	 h[i]->GetXaxis()->SetRange(h[i]->FindBin(550),h[i]->FindBin(1500));
	 gPad->Update();
	 cout<<h[i]->GetMean()<<endl; 
	 }
 gPad->BuildLegend();

	 
if (fit==true){
 //Patricia code
 ofstream ofs("Gaus_Results.txt",std::ofstream::out | std::ofstream::app);
 ofs <<"----------------------------------------------"<<endl;
	for(int i=0;i<n;++i){
			h[i]->GetYaxis()->SetRangeUser(1e-8,1e-2);
			double min=8,max=30;
		   TF1 *f = new TF1("f","gaus",min,max);  //ajuste a una gaussiana
		   h[i]->Fit(f,"R","SAME",min,max);
		   f->Draw("SAME");f->Print();gPad->Update();
		   lets_pause(); 
		   ofs << runs[i] << "\t"<< mych[i]<<"\t" << f->GetParameter(1) << "\t" << f->GetParError(1)<<"\t"<<var[i]<< endl;
       
    } 
}
}


void DrawSum(std::vector<int> mych, int n, int runs[], string name[], bool rate=true, string var="Q3PE")
{
 TFile *ifile[n];
 for(int i=0;i<n;i++) ifile[i]= new TFile(Form("AnalysisROOT_JASOTO_FEB/Run%i_NTuple.root",runs[i])); 
 TNtuple *nt[n];
 Double_t duration[n];
 Float_t evt;
 Float_t ch; 
 Float_t time; 
 Float_t Q3; 
 std::vector<std::map<int,double>> EvtToCharge(n); 
  TH1D *h[n];
 for(int i=0;i<n;i++)
 {
   nt[i]= (TNtuple*)ifile[i]->Get("ntuple");
   nt[i]->SetBranchAddress("time",&time);
   nt[i]->SetBranchAddress("evt",&evt);
   nt[i]->SetBranchAddress("ch",&ch);
   nt[i]->SetBranchAddress(var.c_str(),&Q3);
   if(rate) h[i]=new TH1D(Form("h%i",i),Form("%s;Charge collected on ch0 and 1 (PE); Events/s ",name[i].c_str()),500,0,100);
   else h[i]=new TH1D(Form("h%i",i),Form("%s;Charge collected on ch0 and 1 (PE); Events",name[i].c_str()),500,0,100);
   h[i]->SetLineColor(i+1);
   h[i]->SetLineWidth(2);
   //EvtToCharge[i]=std::map<int,double>();
 }
 cout << "Drawing " << n<< endl;
 for(int i=0;i<n;i++)
 {
// cout << "Drawing " << i<< endl;
  for(int j=0;j<nt[i]->GetEntries();j++)
  { 
//   cout << "Drawing " << j<< endl;
   nt[i]->GetEntry(j);
   if(find(mych.begin(),mych.end(),(int)ch)==mych.end()) continue;
   if(EvtToCharge[i].find((int)evt) == EvtToCharge[i].end() )
   {
     EvtToCharge[i].emplace((int)evt,Q3);
   }
   else
   {
     EvtToCharge[i][(int)evt]+=(Q3);
   }
  }

  float firstime=time;
  nt[i]->GetEntry(nt[i]->GetEntries()-1);
  float lasttime=time;
  duration[i] = (lasttime - firstime)*8.e-9;
 }
 for(int i=0;i<n;i++)
 {
   for (auto e : EvtToCharge[i]){h[i]->Fill(e.second);}
   if(rate) h[i]->Scale(1./duration[i]);
   //else h[i]->Scale(1./h[i]->GetEntries());
 }

 cout << "Drawing4 " << n<< endl;

 TCanvas *c = new TCanvas("c");
 c->cd();
 for(int i=0;i<n;i++){h[i]->Rebin();h[i]->Draw("HIST SAME");}
 gPad->BuildLegend();
 lets_pause();
 
 //Patricia code
 ofstream ofs("Gaus_Results.txt");
	for(int i=0;i<n;++i){
			h[i]->GetYaxis()->SetRangeUser(1e-8,1e-2);
			double min=30,max=90;
		   TF1 *f = new TF1("f","gaus",min,max);  //ajuste a una gaussiana
		   h[i]->Fit(f,"R","SAME",min,max);
		   f->Draw("SAME");f->Print();
		   lets_pause(); 
		   ofs << runs[i] << "\t" << f->GetParameter(1) << "\t" << f->GetParError(1)<< endl;
       
    } 
}

void ChargeSpectrum_Feb()
{
//(std::vector<int> mych, std::vector<int> runs, std::vector<string> name, bool rate=true, string var="Q3", TVirtualPad *pad=NULL, float CustomMaxRange=0 )

//SiPM Solo trigger vs coincidencias 25 y 200, ambos canales
//~Draw({1,2,1,2,1,2}, {5,5,11,11,12,12}, {"Th25-Ch4 SingleTrigger","Th25-Ch5 SingleTrigger","Th25-Ch4 Coincidencias ","Th25-Ch5 Coincidencias","Th200-Ch4 Coincidencias","Th200-Ch5 Coincidencias"}, true,{"Q3PE","Q3PE","Q3PE","Q3PE","Q3PE","Q3PE"}); lets_pause();

//SiPM coin 200, charge
//~Draw({1,1,1,1,1,2,2,2,2,2}, {12,26,38,50,62,12,26,38,50,62}, {"","","","","","","","","",""}, false,{"Q3PE","Q3PE","Q3PE","Q3PE","Q3PE","Q3PE","Q3PE","Q3PE","Q3PE","Q3PE"}); lets_pause();
//~Draw({1,1,1,1,1,2,2,2,2,2}, {6,20,32,44,56,9,23,35,47,59}, {"","","","","","","","","",""}, false,{"Q3PE","Q3PE","Q3PE","Q3PE","Q3PE","Q3PE","Q3PE","Q3PE","Q3PE","Q3PE"}); lets_pause();

//~//SiPM coin 35, 
//~Draw({0}, {12}, {"PMT"}, true,{"Q3"});gPad->SetGrid(1,1); lets_pause();
//~Draw({0}, {12}, {"PMT"}, true,{"Amp"});gPad->SetGrid(1,1); lets_pause();
//~Draw({0}, {12}, {"PMT"}, true,{"Q3PE"}); gPad->SetGrid(1,1);lets_pause();
//~Draw({0}, {12}, {"PMT"}, true,{"AmpPE"}); gPad->SetGrid(1,1);lets_pause();

Draw({2}, {12}, {""}, true,{"Q3PE"}); gPad->SetGrid(1,1);lets_pause();

//~Draw({0,0,0,0,0}, {12,26,38,50,62}, {"","","","",""}, false,{"Amp","Amp","Amp","Amp","Amp"}); lets_pause();
//~Draw({0,0,0,0,0}, {12,26,38,50,62}, {"","","","",""}, false,{"AmpPE","AmpPE","AmpPE","AmpPE","AmpPE"}); lets_pause();
//~Draw({0,0,0,0,0}, {12,26,38,50,62}, {"","","","",""}, false,{"Q3","Q3","Q3","Q3","Q3"}); lets_pause();
//~Draw({0,0,0,0,0}, {2,3,4,11,12}, {"PMT-25Thr","PMT-200 Thr","PMT-600 Thr","Coincidencias-25 Thr","Coincidencias-200 Thr"}, true,{"Q3PE","Q3PE","Q3PE","Q3PE","Q3PE"}); lets_pause();

//SiPM coin 200, Amp
//~Draw({1,1,1,1,1,2,2,2,2,2}, {12,26,38,50,62,12,26,38,50,62}, {"","","","","","","","","",""}, false,{"AmpPE","AmpPE","AmpPE","AmpPE","AmpPE","AmpPE","AmpPE","AmpPE","AmpPE","AmpPE"}); lets_pause();
//~Draw({1,1,1,1,1,2,2,2,2,2}, {6,20,32,44,56,9,23,35,47,59}, {"","","","","","","","","",""}, false,{"AmpPE","AmpPE","AmpPE","AmpPE","AmpPE","AmpPE","AmpPE","AmpPE","AmpPE","AmpPE"}); lets_pause();

//PMT 900
//~Draw({0,0,0,0}, {4,18,30,42}, {"PMT 30Abr","PMT 1 Mayo","PMT 2Mayo","PMT 3Mayo"}, true,{"Amp", "Amp", "Amp", "Amp"}); lets_pause();

//~Draw({2}, {11}, {"Amp"}, true,{"Amp"}); lets_pause();
/*
   string var="Amp";//"Q3PE"
   RunCollection_t rc;
   std::vector<TGraphErrors*> Vtg; bool first = true;bool last = false;
   for(int day=11;day<=15;day++)
   {
     TCanvas * c= new TCanvas("c");
     c->Divide(2,2);
     for(int trigger=0; trigger<=2; trigger++)
     {
       std::vector<std::pair<int, string>> RunList = rc.GetByTriggerDate(trigger, TDatime(2021,02,day,0,0,0)); //returns a run,threshold list
       std::vector<string> names(RunList.size());
       std::vector<int> runs(RunList.size());
       std::vector<int> channels(RunList.size(),trigger);
       for(int i=0; i<RunList.size(); i++)
       {
         names[i]=Form("Run %i - Trigger %s %sADC - %02i/02",RunList[i].first,rc.TriggerToString(trigger).c_str(),RunList[i].second.c_str(), day);
         runs[i]=RunList[i].first;
         cout << "Reading Run" << runs[i] << " - " << names[i] << endl;
       }
       float CustomMaxRange=5000;
       if(channels[0]==2)CustomMaxRange=16500;
       Draw(channels, runs, names,1,var,c->cd(trigger+1),CustomMaxRange);
     }
     if(day==15) last=true;
     lets_pause();
     if(first) c->Print(Form("%s_perDay.pdf(",var.c_str()),"pdf");
     else if (last) c->Print(Form("%s_perDay.pdf)",var.c_str()),"pdf");
     else c->Print(Form("%s_perDay.pdf",var.c_str()),"pdf");
     first=false;
  }
//*/
/*
   string var="Amp";//"Q3PE"
   RunCollection_t rc;
   std::vector<TGraphErrors*> Vtg; bool first = true;bool last = false;
   std::vector<string> thresholdV={"25","35","750"}; int cc=1;
   for(int trigger=0; trigger<=2; trigger++)
   {
     TCanvas * c= new TCanvas("c");
     c->Divide(2,2);
     for(auto threshold : thresholdV)
     {
       std::vector<std::pair<int, TDatime>> RunList = rc.GetByTriggerThreshold(trigger, threshold); //returns a run,TDatime
       std::vector<string> names(RunList.size());
       std::vector<int> runs(RunList.size());
       std::vector<int> channels(RunList.size(),trigger);
       for(int i=0; i<RunList.size(); i++)
       {
         names[i]=Form("Run %i - Trigger %s %sADC - %02i/02",RunList[i].first,rc.TriggerToString(trigger).c_str(),threshold.c_str(), RunList[i].second.GetDay());
         runs[i]=RunList[i].first;
         cout << "Reading " << runs[i] << " " << names[i] << endl;
       }
       Draw(channels, runs, names,1,var,c->cd(cc));cc++;
     }
     cc=1;
     if(trigger==2) last=true;
     lets_pause();
     if(first) c->Print(Form("%s_perTriggerChannel.pdf(",var.c_str()),"pdf");
     else if (last) c->Print(Form("%s_perTriggerChannel.pdf)",var.c_str()),"pdf");
     else c->Print(Form("%s_perTriggerChannel.pdf",var.c_str()),"pdf");
     first=false;
  }
//*/
/*
   string var="Q3PE";//"Q3PE"
   RunCollection_t rc;
   std::vector<TGraphErrors*> Vtg; bool first = true;bool last = false;
   std::vector<string> thresholdV={"25","35","750"}; int cc=1;
   for(int day=11;day<=15;day++)
   {
     TCanvas * c= new TCanvas("c");
     c->Divide(2,2);
     for(auto threshold : thresholdV)
     {
       std::vector<std::pair<int, int>> RunList = rc.GetByThresholdDate(threshold, TDatime(2021,02,day,0,0,0)); //returns a run,trigger channel
       std::vector<string> names;
       std::vector<int> runs;
       std::vector<int> channels;
       for(int i=0; i<RunList.size(); i++)
       {
         if(RunList[i].second==2) continue;
         names.push_back(Form("Run %i - Trigger %s %sADC - %02i/02",RunList[i].first,rc.TriggerToString(RunList[i].second).c_str(),threshold.c_str(), day));
         runs.push_back(RunList[i].first);
         channels.push_back(RunList[i].second);
         cout << "Reading " << runs[runs.size()-1] << " " << names[runs.size()-1] << endl;
       }
       Draw(channels, runs, names,1,var,c->cd(cc));cc++;
     }
     cc=1;
     if(day==15) last=true;
     lets_pause();
     if(first) c->Print(Form("%s_ComparingChannels.pdf(",var.c_str()),"pdf");
     else if (last) c->Print(Form("%s_ComparingChannels.pdf)",var.c_str()),"pdf");
     else c->Print(Form("%s_ComparingChannels.pdf",var.c_str()),"pdf");
     first=false;
  }
//*/

/*

   string var="Amp";//"Q3PE"
   RunCollection_t rc;
   std::vector<TGraphErrors*> Vtg; bool first = true;bool last = false;
   std::vector<string> thresholdV={"25","35","750"}; int cc=1;
   for(int day=11;day<=15;day++)
   {
     TCanvas * c= new TCanvas("c");
     c->Divide(2,2);
     for(auto threshold : thresholdV)
     {
       std::vector<std::pair<int, int>> RunList = rc.GetByThresholdDate(threshold, TDatime(2021,02,day,0,0,0)); //returns a run,trigger channel
       std::vector<string> names;
       std::vector<int> runs;
       std::vector<int> channels;
       for(int i=0; i<RunList.size(); i++)
       {
         if(RunList[i].second!=10) continue; //trigger only on the PMT - ch2
         names.push_back(Form("Run %i - ch0 - Trigger %s %sADC - %02i/02",RunList[i].first,rc.TriggerToString(RunList[i].second).c_str(),threshold.c_str(), day));
         runs.push_back(RunList[i].first);
         channels.push_back(0);
         cout << "Reading " << runs[runs.size()-1] << " " << names[runs.size()-1] << endl;

         names.push_back(Form("Run %i - ch1 - Trigger %s %sADC - %02i/02",RunList[i].first,rc.TriggerToString(RunList[i].second).c_str(),threshold.c_str(), day));
         runs.push_back(RunList[i].first);
         channels.push_back(1);
         cout << "Reading " << runs[runs.size()-1] << " " << names[runs.size()-1] << endl;

//         names.push_back(Form("Run %i - ch2 - Trigger %s %sADC - %02i/02",RunList[i].first,rc.TriggerToString(RunList[i].second).c_str(),threshold.c_str(), day));
//         runs.push_back(RunList[i].first);
//         channels.push_back(2);
         cout << "Reading " << runs[runs.size()-1] << " " << names[runs.size()-1] << endl;
       }
       Draw(channels, runs, names,1,var,c->cd(cc));cc++;
     }
     cc=1;
     if(day==15) last=true;
     lets_pause();
     if(first) c->Print(Form("%s_ComparingChannels.pdf(",var.c_str()),"pdf");
     else if (last) c->Print(Form("%s_ComparingChannels.pdf)",var.c_str()),"pdf");
     else c->Print(Form("%s_ComparingChannels.pdf",var.c_str()),"pdf");
     first=false;
  }
//*/

/*
   string var="Q3PE";//"Q3PE"
   RunCollection_t rc;
   std::vector<TGraphErrors*> Vtg; bool first = true;bool last = false;
   std::vector<string> thresholdV={"35","750"}; int cc=1;
   for(int trigger=10; trigger<=10; trigger++)
   {
     TCanvas * c= new TCanvas("c");
     c->Divide(2);
     for(auto threshold : thresholdV)
     {
       std::vector<std::pair<int, TDatime>> RunList = rc.GetByTriggerThreshold(trigger, threshold); //returns a run,TDatime
       std::vector<string> names;
       std::vector<int> runs;
       std::vector<int> channels;
       for(int i=0; i<RunList.size(); i++)
       {
         if(RunList[i].first==2) continue;
         cout << i << " " << RunList[i].first << " " << RunList[i].second.GetDay() << endl;
         names.push_back(Form("Run %i - Trigger %s %sADC - %02i/02",RunList[i].first,rc.TriggerToString(trigger).c_str(),threshold.c_str(), RunList[i].second.GetDay()));
         channels.push_back(1);
         runs.push_back(RunList[i].first);
         cout << "Reading " << runs[runs.size()-1] << " " << names[runs.size()-1] << endl;
       }
       float CustomMaxRange=300;
       if(threshold=="750")CustomMaxRange=300;
       Draw(channels, runs, names,1,var,c->cd(cc),CustomMaxRange);cc++;
     }
     cc=1;
     if(trigger==2) last=true;
     lets_pause();
     if(first) c->Print(Form("%s_perTriggerChannel.pdf(",var.c_str()),"pdf");
     else if (last) c->Print(Form("%s_perTriggerChannel.pdf)",var.c_str()),"pdf");
     else c->Print(Form("%s_perTriggerChannel.pdf",var.c_str()),"pdf");
     first=false;
  }
*/
/*
  string var="Amp";//"Q3PE"
   RunCollection_t rc;
   std::vector<TGraphErrors*> Vtg; bool first = true;bool last = false;
   std::vector<string> thresholdV={"35","750"}; int cc=1;
   for(int trigger=10; trigger<=10; trigger++)
   {
     TCanvas * c= new TCanvas("c");
     c->Divide(2);
     for(int ch=0;ch<=1;ch++)
     {
       std::vector<std::pair<int, string>> RunList = rc.GetByTriggerDate(trigger, TDatime(2021,02,11,0,0,0)); //returns a run,threshold
       std::vector<string> names;
       std::vector<int> runs;
       std::vector<int> channels;
       for(int i=0; i<RunList.size(); i++)
       {
//         if(RunList[i].first==2) continue;
         cout << i << " " << RunList[i].first << " " << RunList[i].second << endl;
         names.push_back(Form("Run %i - ch%i Trigger %s %sADC - %02i/02",RunList[i].first,ch,rc.TriggerToString(trigger).c_str(),RunList[i].second.c_str(), 11));
         channels.push_back(ch);
         runs.push_back(RunList[i].first);
         cout << "Reading " << runs[runs.size()-1] << " " << names[runs.size()-1] << endl;
       }
       float CustomMaxRange=5000;
//       if(threshold=="750")CustomMaxRange=300;
       Draw(channels, runs, names,1,var,c->cd(cc),CustomMaxRange);cc++;
     }
     cc=1;
     if(trigger==2) last=true;
     lets_pause();
     if(first) c->Print(Form("%s_perTriggerChannel.pdf(",var.c_str()),"pdf");
     else if (last) c->Print(Form("%s_perTriggerChannel.pdf)",var.c_str()),"pdf");
     else c->Print(Form("%s_perTriggerChannel.pdf",var.c_str()),"pdf");
     first=false;
  }
*/

/*
   string var="QPeakPE";//"Q3PE"
   RunCollection_t rc;
   std::vector<TGraphErrors*> Vtg; bool first = true;bool last = false;
   std::vector<string> thresholdV={"750"}; int cc=1;
   for(int trigger=2; trigger<=2; trigger++)
   {
     TCanvas * c= new TCanvas("c");
     c->Divide(2);
     for(auto threshold : thresholdV)
     {
       std::vector<std::pair<int, TDatime>> RunList = rc.GetByTriggerThreshold(trigger, threshold); //returns a run,TDatime
       std::vector<string> names;
       std::vector<int> runs;
       std::vector<int> channels;
       for(int i=0; i<RunList.size(); i++)
       {
         if(RunList[i].first!=11) continue;

         cout << i << " " << RunList[i].first << " " << RunList[i].second.GetDay() << endl;
         names.push_back(Form("Run %i - Trigger %s %sADC - %02i/02",RunList[i].first,rc.TriggerToString(trigger).c_str(),threshold.c_str(), RunList[i].second.GetDay()));
         channels.push_back(2);
         runs.push_back(RunList[i].first);
         cout << "Reading " << runs[runs.size()-1] << " " << names[runs.size()-1] << endl;
       }
       float CustomMaxRange=0;
       Draw(channels, runs, names,1,var,c->cd(cc),CustomMaxRange);cc++; lets_pause();
     }
     cc=1;
     if(trigger==2) last=true;
     lets_pause();
     if(first) c->Print(Form("%s_perTriggerChannel.pdf(",var.c_str()),"pdf");
     else if (last) c->Print(Form("%s_perTriggerChannel.pdf)",var.c_str()),"pdf");
     else c->Print(Form("%s_perTriggerChannel.pdf",var.c_str()),"pdf");
     first=false;
  }
*/
}
