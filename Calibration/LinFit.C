#include"../lib/headers.h"

void FillTG(TGraphErrors* tg, std::vector<std::vector<float>> ch, string var)
{
  for (auto g : ch) {tg->SetPoint(tg->GetN(),g[0],g[1]);tg->SetPointError(tg->GetN()-1,0,g[2]); cout << "Adding point " << g[0] << " " << g[1] << endl;}
  tg->SetMarkerStyle(20);
  tg->SetTitle(Form(";Voltage (V); %s",var.c_str()));

}
const int color[5]={1,2,3,4,6};


TF1* MyTF1(int ch, float r1, float r2)
{
  TF1 *f = new TF1(Form("GainFit%i",ch),"[0]+x*[1]", r1,r2);
  f->SetTitle(";Voltage (V); SPE charge (pC)");
  f->SetParName(0,"n");
  f->SetParName(1,"m");
  f->SetLineWidth(3);
  f->SetLineColor(color[ch]);
  return f;
}
TF1* MyTF1Expo(int ch, float r1, float r2)
{
  TF1 *f = new TF1(Form("GainFit%i",ch),"pow(10,[0])*pow(x,[1])", r1,r2);
  f->SetTitle(";Voltage (V); SPE charge (pC)");
  f->SetParName(0,"A");
  f->SetParName(1,"B");
  f->SetLineWidth(3);
  f->SetLineColor(color[ch]);
  return f;
}

class Calib_t
{
 public:
 string name;
 TF1* f0 = NULL;
 TF1* f1 = NULL;
 TF1* f2 = NULL;
 TF1* f3 = NULL;
 TF1* f4 = NULL;
 TF1* fAmp0 = NULL;
 TF1* fAmp1 = NULL;
 TF1* fAmp2 = NULL;
 TF1* fAmp3 = NULL;
 TF1* fAmp4 = NULL;

 TGraphErrors tg0,tg1,tg2,tg3,tg4;
 TGraphErrors tgAmp0,tgAmp1,tgAmp2, tgAmp3,tgAmp4;

 TMultiGraph *m = new TMultiGraph();

 void PrintBreakVoltage()
 {
  if(f0) cout << "ADC0 V_{rupt} " << -f0->GetParameter(0)/f0->GetParameter(1) << "V." << endl;
  if(f1) cout << "ADC1 V_{rupt} " << -f1->GetParameter(0)/f1->GetParameter(1) << "V." << endl;
  if(f3) cout << "ADC3 V_{rupt} " << -f3->GetParameter(0)/f3->GetParameter(1) << "V." << endl;
  if(f4) cout << "ADC4 V_{rupt} " << -f4->GetParameter(0)/f4->GetParameter(1) << "V." << endl;
  if(fAmp0) cout << "ADC0 V_{rupt}_{Amp} " << -fAmp0->GetParameter(0)/fAmp0->GetParameter(1) << "V." << endl;
  if(fAmp1) cout << "ADC1 V_{rupt}_{Amp} " << -fAmp1->GetParameter(0)/fAmp1->GetParameter(1) << "V." << endl;
  if(fAmp3) cout << "ADC3 V_{rupt}_{Amp} " << -fAmp3->GetParameter(0)/fAmp3->GetParameter(1) << "V." << endl;
  if(fAmp4) cout << "ADC4 V_{rupt}_{Amp} " << -fAmp4->GetParameter(0)/fAmp4->GetParameter(1) << "V." << endl;
 }
 void PrintFitPars()
 {
  if(f0) cout << "Q0\t" << f0->GetParameter(0) << "\t" << f0->GetParError(0)  << "\t" << f0->GetParameter(1) << "\t" << f0->GetParError(1) << endl;
  if(f1) cout << "Q1\t" << f1->GetParameter(0) << "\t" << f1->GetParError(0)  << "\t" << f1->GetParameter(1) << "\t" << f1->GetParError(1) << endl;
  if(f2) cout << "Q2\t" << f2->GetParameter(0) << "\t" << f2->GetParError(0)  << "\t" << f2->GetParameter(1) << "\t" << f2->GetParError(1) << endl;
  if(f3) cout << "Q3\t" << f3->GetParameter(0) << "\t" << f3->GetParError(0)  << "\t" << f3->GetParameter(1) << "\t" << f3->GetParError(1) << endl;
  if(f4) cout << "Q4\t" << f4->GetParameter(0) << "\t" << f4->GetParError(0)  << "\t" << f4->GetParameter(1) << "\t" << f4->GetParError(1) << endl;
  if(fAmp0) cout << "A0\t" << fAmp0->GetParameter(0) << "\t" << fAmp0->GetParError(0)  << "\t" << fAmp0->GetParameter(1) << "\t" << fAmp0->GetParError(1) << endl;
  if(fAmp1) cout << "A1\t" << fAmp1->GetParameter(0) << "\t" << fAmp1->GetParError(0)  << "\t" << fAmp1->GetParameter(1) << "\t" << fAmp1->GetParError(1) << endl;
  if(fAmp2) cout << "A2\t" << fAmp2->GetParameter(0) << "\t" << fAmp2->GetParError(0)  << "\t" << fAmp2->GetParameter(1) << "\t" << fAmp2->GetParError(1) << endl;
  if(fAmp3) cout << "A3\t" << fAmp3->GetParameter(0) << "\t" << fAmp3->GetParError(0)  << "\t" << fAmp3->GetParameter(1) << "\t" << fAmp3->GetParError(1) << endl;
  if(fAmp4) cout << "A4\t" << fAmp4->GetParameter(0) << "\t" << fAmp4->GetParError(0)  << "\t" << fAmp4->GetParameter(1) << "\t" << fAmp4->GetParError(1) << endl;
 }


void Draw()
 {

  float x1=0.02;
  float y1=0.5;
  float x2=x1+0.4;//anchura
  float y2=0.97; //altura
  TLegend *leg = new TLegend(x1,y1,x2,y2);
  //leg->SetHeader(Form("%s (G=10^{A}V^{B})",picname.c_str()));   //<-- change
  leg->AddEntry(&tg1,Form("%s - ADC1",name.c_str()));
  leg->AddEntry(&tg2,Form("%s - ADC2",name.c_str()));

  TLegend *leg1 = new TLegend(x1,y1,x2,y2);
  //leg->SetHeader(Form("%s (G=10^{A}V^{B})",picname.c_str()));   //<-- change
  leg1->AddEntry(&tg3,Form("%s - ADC3",name.c_str()));

  m->Add(&tg1);
  m->Add(&tg2);
//  m->Add(&tg3);
  TMultiGraph *m2 = new TMultiGraph();
  m2->Add(&tgAmp1);
  m2->Add(&tgAmp2);  
  TCanvas *c3 = new TCanvas("c3");
  c3->Divide(2,2);
  c3->cd(1);
  m->Draw("AP"); 
  f1->Draw("SAME");
  f2->Draw("SAME");  leg->Draw();
  m->GetXaxis()->SetTitle("Voltage (V)");
  m->GetYaxis()->SetTitle("Charge (pC)");
  c3->cd(2);
  m2->Draw("AP");
  fAmp1->Draw("SAME");
  fAmp2->Draw("SAME");
  m2->GetXaxis()->SetTitle("Voltage (V)");
  m2->GetYaxis()->SetTitle("Amplitude (ADC)");
  c3->cd(3);
  tg3.Draw("AP"); 
  f3->Draw("SAME");
  setlogscale(c3->cd(3),&tg3);
  tg3.GetXaxis()->SetTitle("Voltage (V)");
  tg3.GetYaxis()->SetTitle("Charge (pC)");
  c3->cd(4);
  tgAmp3.Draw("AP");
  fAmp3->Draw("SAME");leg1->Draw();
  setlogscale(c3->cd(4),&tgAmp3);
  tgAmp3.GetXaxis()->SetTitle("Voltage (V)");
  tgAmp3.GetYaxis()->SetTitle("Amplitude (ADC)");

//  cout << "voltage of ch 3 at 100ADC  " << (100-fAmp3->GetParameter(0))/fAmp3->GetParameter(1) << endl;

  //m->GetXaxis()->SetRangeUser(0,49);
  


  lets_pause();
 }

 void Cal20210212()
 {

  name="20210212";
  std::vector<std::vector<float>> ch1,ch2,ch3;
  std::vector<std::vector<float>> Ach1,Ach2,Ach3;
  ch1={{45,2.24615,0.0159297},{46,3.74656,0.0225391},{47,5.31602,0.0246253},{48,6.96679,0.0374488}};
  ch2={{45,2.1335,0.0143904},{46,3.60907,0.0180366},{47,5.14079,0.0227454},{48,6.92577,0.0381905}};
  ch3={{1100,0.77402,0.0330003},{1200,1.90169,0.0207532},{1300,3.72615,0.0510583},{1400,6.18883,0.0687219}};
  Ach1={{45,18.6132,0.0781385},{46,24.8948,0.0859966},{47,31.8382,0.0906606},{48,38.4429,0.113609}};
  Ach2={{45,18.0389,0.0676213},{46,24.6747,0.0776424},{47,30.927,0.0939435},{48,37.6673,0.110713}};
  Ach3={{1100,55.3331,2.61207},{1200,126.216,2.08242},{1300,250.558,4.36328},{1400,436.023,6.56776}};
  for (int i=0;i< ch1.size();i++) ch1[i][1]*=(1.0e7/1.6);
  for (int i=0;i< ch2.size();i++) ch2[i][1]*=(1.0e7/1.6);
  for (int i=0;i< ch3.size();i++) ch3[i][1]*=(1.0e7/1.6);
  FillTG(&tg1,ch1,"SPE Gain"); tg1.SetMarkerColor(color[1]); tg1.SetDrawOption("P");tg1.SetMarkerStyle(28);
  FillTG(&tg2,ch2,"SPE Gain"); tg2.SetMarkerColor(color[2]); tg2.SetDrawOption("P");tg2.SetMarkerStyle(28);
  FillTG(&tg3,ch3,"SPE Gain"); tg3.SetMarkerColor(color[3]); tg3.SetDrawOption("P");tg3.SetMarkerStyle(28);cout << "2 " << endl;
  f1=MyTF1(1,ch1[0][0],ch1[3][0]);
  f2=MyTF1(2,ch2[0][0],ch2[3][0]);
  f3=MyTF1Expo(3,ch3[1][0],ch3[3][0]);
  TFitResultPtr r1 = tg1.Fit(f1,"ESR"); cout << gMinuit->fCstatu << endl;tg1.Draw("ALP E1");//lets_pause();
  TFitResultPtr r2 = tg2.Fit(f2,"ESR"); cout << gMinuit->fCstatu << endl;tg2.Draw("ALP E1");//lets_pause();
  TFitResultPtr r3 = tg3.Fit(f3,"ESR"); cout << gMinuit->fCstatu << endl;tg3.Draw("ALP E1");//lets_pause();
cout << "3 " << endl;
  FillTG(&tgAmp1,Ach1,"SPE Amplitude (ADC)"); tgAmp1.SetMarkerColor(color[1]); tgAmp1.SetDrawOption("P");tgAmp1.SetMarkerStyle(28);
  FillTG(&tgAmp2,Ach2,"SPE Amplitude (ADC)"); tgAmp2.SetMarkerColor(color[2]); tgAmp2.SetDrawOption("P");tgAmp2.SetMarkerStyle(28);
  FillTG(&tgAmp3,Ach3,"SPE Amplitude (ADC)"); tgAmp3.SetMarkerColor(color[3]); tgAmp3.SetDrawOption("P");tgAmp3.SetMarkerStyle(28);

  fAmp1=MyTF1(1,ch1[0][0],ch1[3][0]);
  fAmp2=MyTF1(2,ch2[0][0],ch2[3][0]);
  fAmp3=MyTF1Expo(3,ch3[1][0],ch3[3][0]); TCanvas *c = new TCanvas("c"); tgAmp1.Draw("ALP E1");
  TFitResultPtr rAmp1 = tgAmp1.Fit(fAmp1,"ESR"); cout << gMinuit->fCstatu << endl; tgAmp1.Draw("ALP E1");
  TFitResultPtr rAmp2 = tgAmp2.Fit(fAmp2,"ESR"); cout << gMinuit->fCstatu << endl; tgAmp2.Draw("ALP E1");
  TFitResultPtr rAmp3 = tgAmp3.Fit(fAmp3,"ESR"); cout << gMinuit->fCstatu << endl; 

  PrintBreakVoltage();
  PrintFitPars();
  return m;
 }
 
 void Cal20210215()
 {


  name="20210215";
  std::vector<std::vector<float>> ch1,ch2,ch3;
  std::vector<std::vector<float>> Ach1,Ach2,Ach3; 

Ach1={{45,18.6034,0.0749122},{46,25.1924,0.0869342},{47,31.754,0.101139},{48,38.1675,0.103401}};
Ach2={{45,18.1232,0.0686229},{46,24.6519,0.082517},{47,30.6655,0.111313},{48,37.572,0.111301}};
Ach3={{1100,55.4524,1.78146},{1200,117.579,3.30377},{1300,249.989,4.82195},{1400,439.589,7.94586}};
ch1={{45,2.24842,0.0161103},{46,3.72633,0.0216005},{47,5.31664,0.0302808},{48,6.96472,0.0382221}};
ch2={{45,2.14416,0.0163935},{46,3.61642,0.0176297},{47,5.11063,0.0255372},{48,6.8588,0.0314165}};
ch3={{1100,0.71297,0.0304376},{1200,1.82096,0.0337917},{1300,3.61629,0.0493193},{1400,6.12898,0.0757137}};
  for (int i=0;i< ch1.size();i++) ch1[i][1]*=(1.0e7/1.6);
  for (int i=0;i< ch2.size();i++) ch2[i][1]*=(1.0e7/1.6);
  for (int i=0;i< ch3.size();i++) ch3[i][1]*=(1.0e7/1.6);

  FillTG(&tg1,ch1,"Gain"); tg1.SetMarkerColor(color[1]); tg1.SetDrawOption("P");tg1.SetMarkerStyle(20);
  FillTG(&tg2,ch2,"Gain"); tg2.SetMarkerColor(color[2]); tg2.SetDrawOption("P");tg2.SetMarkerStyle(20);
  FillTG(&tg3,ch3,"Gain"); tg3.SetMarkerColor(color[3]); tg3.SetDrawOption("P");tg3.SetMarkerStyle(20);

  f1=MyTF1(1,ch1[0][0],ch1[3][0]); f1->SetLineStyle(2);
  f2=MyTF1(2,ch2[0][0],ch2[3][0]);f2->SetLineStyle(2);
  f3=MyTF1Expo(3,ch3[0][0],ch3[3][0]);f3->SetLineStyle(2);
  TFitResultPtr r1 = tg1.Fit(f1,"ESR"); cout << gMinuit->fCstatu << endl;//tg1.Draw("ALP E1");lets_pause();
  TFitResultPtr r2 = tg2.Fit(f2,"ESR"); cout << gMinuit->fCstatu << endl;//tg2.Draw("ALP E1");lets_pause();
  TFitResultPtr r3 = tg3.Fit(f3,"ESR"); cout << gMinuit->fCstatu << endl;//tg3.Draw("ALP E1");lets_pause();
  FillTG(&tgAmp1,Ach1,"SPE Amplitude (ADC)"); tgAmp1.SetMarkerColor(color[1]); tgAmp1.SetDrawOption("P");tgAmp1.SetMarkerStyle(20);
  FillTG(&tgAmp2,Ach2,"SPE Amplitude (ADC)"); tgAmp2.SetMarkerColor(color[2]); tgAmp2.SetDrawOption("P");tgAmp2.SetMarkerStyle(20);
  FillTG(&tgAmp3,Ach3,"SPE Amplitude (ADC)"); tgAmp3.SetMarkerColor(color[3]); tgAmp3.SetDrawOption("P");tgAmp3.SetMarkerStyle(20);

  fAmp1=MyTF1(1,ch1[0][0],ch1[3][0]);fAmp1->SetLineStyle(2);
  fAmp2=MyTF1(2,ch2[0][0],ch2[3][0]);fAmp2->SetLineStyle(2);
  fAmp3=MyTF1Expo(3,ch3[0][0],ch3[3][0]); fAmp3->SetLineStyle(2);
  TCanvas *c = new TCanvas("c"); tgAmp1.Draw("ALP E1");
  TFitResultPtr rAmp1 = tgAmp1.Fit(fAmp1,"ESR"); cout << gMinuit->fCstatu << endl; tgAmp1.Draw("ALP E1");
  TFitResultPtr rAmp2 = tgAmp2.Fit(fAmp2,"ESR"); cout << gMinuit->fCstatu << endl; tgAmp2.Draw("ALP E1");
  TFitResultPtr rAmp3 = tgAmp3.Fit(fAmp3,"ESR"); cout << gMinuit->fCstatu << endl; 

  PrintBreakVoltage();
  PrintFitPars();
  return m;
 }

 void Cal20210216()
 {


  name="20210216";
  std::vector<std::vector<float>> ch1,ch2,ch3;
  std::vector<std::vector<float>> Ach1,Ach2,Ach3; 
ch1={{45,2.23016,0.0136772},{46,3.69683,0.0161983},{47,5.27684,0.0193267},{48,6.98636,0.0279531},};
ch2={{45,2.15006,0.012449},{46,3.60241,0.0131172},{47,5.13327,0.0187997},{48,6.87449,0.028354},};
ch3={{1100,0.765655,0.0219627},{1200,1.84988,0.0280648},{1300,3.53901,0.0481454},{1400,6.16519,0.0699183}};
Ach1={{45,18.6589,0.0551159},{46,25.1341,0.0670424},{47,31.6418,0.0679015},{48,38.2795,0.083996},};
Ach2={{45,18.2713,0.0526176},{46,24.5033,0.0656979},{47,30.6546,0.0767901},{48,37.59,0.0920228},};
Ach3={{1100,54.6949,1.74782},{1200,122.298,2.81316},{1300,242.413,4.05588},{1400,441.228,6.74651}};
  for (int i=0;i< ch1.size();i++) ch1[i][1]*=(1.0e7/1.6);
  for (int i=0;i< ch2.size();i++) ch2[i][1]*=(1.0e7/1.6);
  for (int i=0;i< ch3.size();i++) ch3[i][1]*=(1.0e7/1.6);


  FillTG(&tg1,ch1,"Gain"); tg1.SetMarkerColor(color[1]); tg1.SetDrawOption("P");tg1.SetMarkerStyle(22);
  FillTG(&tg2,ch2,"Gain"); tg2.SetMarkerColor(color[2]); tg2.SetDrawOption("P");tg2.SetMarkerStyle(22);
  FillTG(&tg3,ch3,"Gain"); tg3.SetMarkerColor(color[3]); tg3.SetDrawOption("P");tg3.SetMarkerStyle(22);

  f1=MyTF1(1,ch1[0][0],ch1[3][0]); f1->SetLineStyle(2);
  f2=MyTF1(2,ch2[0][0],ch2[3][0]);f2->SetLineStyle(2);
  f3=MyTF1Expo(3,ch3[0][0],ch3[3][0]);f3->SetLineStyle(2);
  TFitResultPtr r1 = tg1.Fit(f1,"ESR"); cout << gMinuit->fCstatu << endl;//tg1.Draw("ALP E1");lets_pause();
  TFitResultPtr r2 = tg2.Fit(f2,"ESR"); cout << gMinuit->fCstatu << endl;//tg2.Draw("ALP E1");lets_pause();
  TFitResultPtr r3 = tg3.Fit(f3,"ESR"); cout << gMinuit->fCstatu << endl;//tg3.Draw("ALP E1");lets_pause();
  FillTG(&tgAmp1,Ach1,"SPE Amplitude (ADC)"); tgAmp1.SetMarkerColor(color[1]); tgAmp1.SetDrawOption("P");tgAmp1.SetMarkerStyle(22);
  FillTG(&tgAmp2,Ach2,"SPE Amplitude (ADC)"); tgAmp2.SetMarkerColor(color[2]); tgAmp2.SetDrawOption("P");tgAmp2.SetMarkerStyle(22);
  FillTG(&tgAmp3,Ach3,"SPE Amplitude (ADC)"); tgAmp3.SetMarkerColor(color[3]); tgAmp3.SetDrawOption("P");tgAmp3.SetMarkerStyle(22);

  fAmp1=MyTF1(1,ch1[0][0],ch1[3][0]);fAmp1->SetLineStyle(3);
  fAmp2=MyTF1(2,ch2[0][0],ch2[3][0]);fAmp2->SetLineStyle(3);
  fAmp3=MyTF1Expo(3,ch3[0][0],ch3[3][0]); fAmp3->SetLineStyle(3);
  TCanvas *c = new TCanvas("c"); tgAmp1.Draw("ALP E1");
  TFitResultPtr rAmp1 = tgAmp1.Fit(fAmp1,"ESR"); cout << gMinuit->fCstatu << endl; tgAmp1.Draw("ALP E1");
  TFitResultPtr rAmp2 = tgAmp2.Fit(fAmp2,"ESR"); cout << gMinuit->fCstatu << endl; tgAmp2.Draw("ALP E1");
  TFitResultPtr rAmp3 = tgAmp3.Fit(fAmp3,"ESR"); cout << gMinuit->fCstatu << endl; 

  PrintBreakVoltage();
  PrintFitPars();
  return m;
 };

 void Cal20210501()
 {


  name="20210501";
  std::vector<std::vector<float>> ch1,ch2,ch3;
  std::vector<std::vector<float>> Ach1,Ach2,Ach3; 
//Charges
ch1={{45,2.10781,0.0178119},{46,3.56051,0.0187669},{47,5.1149,0.0223854},{48,6.76723,0.0225476},};
ch2={{45,2.2629,0.0160918},{46,3.77216,0.021465},{47,5.35632,0.0222116},{48,7.11033,0.0236675},};
ch3={{1100,1.15452,0.00964702},{1200,2.28481,0.0248644},{1300,4.22588,0.0434149},{1400,7.23779,0.057841},{1500,10.5925,0.285062},};
//Amplitudes
Ach1={{45,17.9938,0.100398},{46,24.9689,0.0756164},{47,31.5924,0.0677493},{48,38.0598,0.0623465},};
Ach2={{45,18.444,0.0994035},{46,25.6826,0.0768262},{47,32.2975,0.074082},{48,39.127,0.082714},};
Ach3={{1100,79.5131,0.862395},{1200,167.805,2.10495},{1300,331.378,3.2587},{1400,527.326,5.6386},{1500,850.406,40.0678},};

  for (int i=0;i< ch1.size();i++) ch1[i][1]*=(1.0e7/1.6);
  for (int i=0;i< ch2.size();i++) ch2[i][1]*=(1.0e7/1.6);
  for (int i=0;i< ch3.size();i++) ch3[i][1]*=(1.0e7/1.6);
  FillTG(&tg1,ch1,"SPE Gain"); tg1.SetMarkerColor(color[1]); tg1.SetDrawOption("P");tg1.SetMarkerStyle(22);
  FillTG(&tg2,ch2,"SPE Gain"); tg2.SetMarkerColor(color[2]); tg2.SetDrawOption("P");tg2.SetMarkerStyle(22);
  FillTG(&tg3,ch3,"SPE Gain"); tg3.SetMarkerColor(color[3]); tg3.SetDrawOption("P");tg3.SetMarkerStyle(22);
  
	cout<<ch1[0][0]<<endl;
	cout<<ch1[3][0]<<endl;
	lets_pause();
  f1=MyTF1(1,ch1[0][0],ch1[3][0]); f1->SetLineStyle(2);
  f2=MyTF1(2,ch2[0][0],ch2[3][0]);f2->SetLineStyle(2);
  f3=MyTF1Expo(3,ch3[1][0],ch3[3][0]);f3->SetLineStyle(2);
  TFitResultPtr r1 = tg1.Fit(f1,"ESR"); cout << gMinuit->fCstatu << endl;//tg1.Draw("ALP E1");lets_pause();
  TFitResultPtr r2 = tg2.Fit(f2,"ESR"); cout << gMinuit->fCstatu << endl;//tg2.Draw("ALP E1");lets_pause();
  TFitResultPtr r3 = tg3.Fit(f3,"ESR"); cout << gMinuit->fCstatu << endl;//tg3.Draw("ALP E1");lets_pause();
  FillTG(&tgAmp1,Ach1,"SPE Amplitude (ADC)"); tgAmp1.SetMarkerColor(color[1]); tgAmp1.SetDrawOption("P");tgAmp1.SetMarkerStyle(22);
  FillTG(&tgAmp2,Ach2,"SPE Amplitude (ADC)"); tgAmp2.SetMarkerColor(color[2]); tgAmp2.SetDrawOption("P");tgAmp2.SetMarkerStyle(22);
  FillTG(&tgAmp3,Ach3,"SPE Amplitude (ADC)"); tgAmp3.SetMarkerColor(color[3]); tgAmp3.SetDrawOption("P");tgAmp3.SetMarkerStyle(22);

  fAmp1=MyTF1(1,ch1[0][0],ch1[3][0]);fAmp1->SetLineStyle(2);
  fAmp2=MyTF1(2,ch2[0][0],ch2[3][0]);fAmp2->SetLineStyle(2);
  fAmp3=MyTF1Expo(3,ch3[1][0],ch3[3][0]); fAmp3->SetLineStyle(2);
  TCanvas *c = new TCanvas("c"); tgAmp1.Draw("ALP E1");
  TFitResultPtr rAmp1 = tgAmp1.Fit(fAmp1,"ESR"); cout << gMinuit->fCstatu << endl; tgAmp1.Draw("ALP E1");
  TFitResultPtr rAmp2 = tgAmp2.Fit(fAmp2,"ESR"); cout << gMinuit->fCstatu << endl; tgAmp2.Draw("ALP E1");
  TFitResultPtr rAmp3 = tgAmp3.Fit(fAmp3,"ESR"); cout << gMinuit->fCstatu << endl; 

  //~PrintBreakVoltage();
  PrintFitPars();
  return m;
 }

 void Cal20210502()
 {


  name="20210502";
  std::vector<std::vector<float>> ch1,ch2,ch3;
  std::vector<std::vector<float>> Ach1,Ach2,Ach3; 
//Charges
ch1={{45,2.08713,0.0156108},{46,3.56487,0.014766},{47,5.12267,0.0191123},{48,6.82311,0.0235435},};
ch2={{45,2.30322,0.0152932},{46,3.7866,0.0157693},{47,5.35517,0.0191343},{48,7.12648,0.0256922},};
ch3={{1100,1.1891,0.00803337},{1200,2.33115,0.0151224},{1300,4.36851,0.036433},{1400,7.95116,0.0463323},{1500,11.8049,0.180578},};
//Amplitudes
Ach1={{45,17.8835,0.0890486},{46,24.8051,0.0506335},{47,31.5576,0.0592266},{48,38.0568,0.0640311},};
Ach2={{45,18.4475,0.0856994},{46,25.6111,0.0529604},{47,32.2409,0.0653649},{48,39.0177,0.0812471},};
Ach3={{1100,81.5217,0.692857},{1200,171.675,1.36804},{1300,338.603,2.46078},{1400,604.964,6.38093},{1500,955.03,13.1644},};

  for (int i=0;i< ch1.size();i++) ch1[i][1]*=(1.0e7/1.6);
  for (int i=0;i< ch2.size();i++) ch2[i][1]*=(1.0e7/1.6);
  for (int i=0;i< ch3.size();i++) ch3[i][1]*=(1.0e7/1.6);

  FillTG(&tg1,ch1,"Gain"); tg1.SetMarkerColor(color[1]); tg1.SetDrawOption("P");tg1.SetMarkerStyle(22);
  FillTG(&tg2,ch2,"Gain"); tg2.SetMarkerColor(color[2]); tg2.SetDrawOption("P");tg2.SetMarkerStyle(22);
  FillTG(&tg3,ch3,"Gain"); tg3.SetMarkerColor(color[3]); tg3.SetDrawOption("P");tg3.SetMarkerStyle(22);

	cout<<ch1[0][0]<<endl;
	cout<<ch1[3][0]<<endl;
	lets_pause();
  f1=MyTF1(1,ch1[0][0],ch1[3][0]); f1->SetLineStyle(2);
  f2=MyTF1(2,ch2[0][0],ch2[3][0]);f2->SetLineStyle(2);
  f3=MyTF1Expo(3,ch3[0][0],ch3[3][0]);f3->SetLineStyle(2);
  TFitResultPtr r1 = tg1.Fit(f1,"ESR"); cout << gMinuit->fCstatu << endl;//tg1.Draw("ALP E1");lets_pause();
  TFitResultPtr r2 = tg2.Fit(f2,"ESR"); cout << gMinuit->fCstatu << endl;//tg2.Draw("ALP E1");lets_pause();
  TFitResultPtr r3 = tg3.Fit(f3,"ESR"); cout << gMinuit->fCstatu << endl;//tg3.Draw("ALP E1");lets_pause();
  FillTG(&tgAmp1,Ach1,"SPE Amplitude (ADC)"); tgAmp1.SetMarkerColor(color[1]); tgAmp1.SetDrawOption("P");tgAmp1.SetMarkerStyle(22);
  FillTG(&tgAmp2,Ach2,"SPE Amplitude (ADC)"); tgAmp2.SetMarkerColor(color[2]); tgAmp2.SetDrawOption("P");tgAmp2.SetMarkerStyle(22);
  FillTG(&tgAmp3,Ach3,"SPE Amplitude (ADC)"); tgAmp3.SetMarkerColor(color[3]); tgAmp3.SetDrawOption("P");tgAmp3.SetMarkerStyle(22);

  fAmp1=MyTF1(1,ch1[0][0],ch1[3][0]);fAmp1->SetLineStyle(3);
  fAmp2=MyTF1(2,ch2[0][0],ch2[3][0]);fAmp2->SetLineStyle(3);
  fAmp3=MyTF1Expo(3,ch3[0][0],ch3[3][0]); fAmp3->SetLineStyle(3);
  TCanvas *c = new TCanvas("c"); tgAmp1.Draw("ALP E1");
  TFitResultPtr rAmp1 = tgAmp1.Fit(fAmp1,"ESR"); cout << gMinuit->fCstatu << endl; tgAmp1.Draw("ALP E1");
  TFitResultPtr rAmp2 = tgAmp2.Fit(fAmp2,"ESR"); cout << gMinuit->fCstatu << endl; tgAmp2.Draw("ALP E1");
  TFitResultPtr rAmp3 = tgAmp3.Fit(fAmp3,"ESR"); cout << gMinuit->fCstatu << endl; 

  //~PrintBreakVoltage();
  PrintFitPars();
  return m;
 }

 void Cal20210503()
 {


  name="20210503";
  std::vector<std::vector<float>> ch1,ch2,ch3;
  std::vector<std::vector<float>> Ach1,Ach2,Ach3; 
//Charges
ch1={{45,2.09574,0.014872},{46,3.55074,0.0150978},{47,5.1196,0.0200447},{48,6.84564,0.0224433},};
ch2={{45,2.30488,0.0148347},{46,3.76664,0.016244},{47,5.39083,0.0189743},{48,7.06121,0.0217488},};
ch3={{1100,1.19176,0.00605415},{1200,2.33659,0.0135166},{1300,4.34747,0.0296154},{1400,8.00513,0.0362133},{1500,13.6383,0.362472},};
//Amplitudes
Ach1={{45,17.7126,0.087969},{46,24.9261,0.0558584},{47,31.4916,0.0585325},{48,37.9531,0.0593345},};
Ach2={{45,18.0632,0.0949144},{46,25.7033,0.0546881},{47,32.3135,0.0637175},{48,39.0113,0.0737652},};
Ach3={{1100,82.0633,0.549848},{1200,167.552,1.07369},{1300,332.813,1.8939},{1400,590.517,4.30593},{1500,956.98,9.73374},};
  for (int i=0;i< ch1.size();i++) ch1[i][1]*=(1.0e7/1.6);
  for (int i=0;i< ch2.size();i++) ch2[i][1]*=(1.0e7/1.6);
  for (int i=0;i< ch3.size();i++) ch3[i][1]*=(1.0e7/1.6);

  FillTG(&tg1,ch1,"Gain"); tg1.SetMarkerColor(color[1]); tg1.SetDrawOption("P");tg1.SetMarkerStyle(22);
  FillTG(&tg2,ch2,"Gain"); tg2.SetMarkerColor(color[2]); tg2.SetDrawOption("P");tg2.SetMarkerStyle(22);
  FillTG(&tg3,ch3,"Gain"); tg3.SetMarkerColor(color[3]); tg3.SetDrawOption("P");tg3.SetMarkerStyle(22);

	cout<<ch1[0][0]<<endl;
	cout<<ch1[3][0]<<endl;
	lets_pause();
  f1=MyTF1(1,ch1[0][0],ch1[3][0]); f1->SetLineStyle(2);
  f2=MyTF1(2,ch2[0][0],ch2[3][0]);f2->SetLineStyle(2);
  f3=MyTF1Expo(3,ch3[0][0],ch3[3][0]);f3->SetLineStyle(2);
  TFitResultPtr r1 = tg1.Fit(f1,"ESR"); cout << gMinuit->fCstatu << endl;//tg1.Draw("ALP E1");lets_pause();
  TFitResultPtr r2 = tg2.Fit(f2,"ESR"); cout << gMinuit->fCstatu << endl;//tg2.Draw("ALP E1");lets_pause();
  TFitResultPtr r3 = tg3.Fit(f3,"ESR"); cout << gMinuit->fCstatu << endl;//tg3.Draw("ALP E1");lets_pause();
  FillTG(&tgAmp1,Ach1,"SPE Amplitude (ADC)"); tgAmp1.SetMarkerColor(color[1]); tgAmp1.SetDrawOption("P");tgAmp1.SetMarkerStyle(22);
  FillTG(&tgAmp2,Ach2,"SPE Amplitude (ADC)"); tgAmp2.SetMarkerColor(color[2]); tgAmp2.SetDrawOption("P");tgAmp2.SetMarkerStyle(22);
  FillTG(&tgAmp3,Ach3,"SPE Amplitude (ADC)"); tgAmp3.SetMarkerColor(color[3]); tgAmp3.SetDrawOption("P");tgAmp3.SetMarkerStyle(22);

  fAmp1=MyTF1(1,ch1[0][0],ch1[3][0]);fAmp1->SetLineStyle(3);
  fAmp2=MyTF1(2,ch2[0][0],ch2[3][0]);fAmp2->SetLineStyle(3);
  fAmp3=MyTF1Expo(3,ch3[0][0],ch3[3][0]); fAmp3->SetLineStyle(3);
  TCanvas *c = new TCanvas("c"); tgAmp1.Draw("ALP E1");
  TFitResultPtr rAmp1 = tgAmp1.Fit(fAmp1,"ESR"); cout << gMinuit->fCstatu << endl; tgAmp1.Draw("ALP E1");
  TFitResultPtr rAmp2 = tgAmp2.Fit(fAmp2,"ESR"); cout << gMinuit->fCstatu << endl; tgAmp2.Draw("ALP E1");
  TFitResultPtr rAmp3 = tgAmp3.Fit(fAmp3,"ESR"); cout << gMinuit->fCstatu << endl; 

  //~PrintBreakVoltage();
  PrintFitPars();
  return m;
 }

 void Cal20210504()
 {


  name="20210504";
  std::vector<std::vector<float>> ch1,ch2,ch3;
  std::vector<std::vector<float>> Ach1,Ach2,Ach3; 
//Charges
ch1={{45,2.07835,0.0143776},{46,3.53995,0.0141587},{47,5.07659,0.018794},{48,6.82622,0.0240273},};
ch2={{45,2.26124,0.0139564},{46,3.75287,0.014938},{47,5.35272,0.0187285},{48,7.11479,0.0251364},};
ch3={{1100,1.18658,0.00621453},{1200,2.38523,0.0131373},{1300,4.4137,0.0323527},{1400,8.11474,0.0393471},{1500,11.829,0.146371},};
//Amplitudes
Ach1={{45,17.7027,0.0847763},{46,24.8451,0.0486359},{47,31.4336,0.0494612},{48,38.0023,0.0626966},};
Ach2={{45,18.1485,0.0914899},{46,25.7056,0.0524287},{47,32.2514,0.0567262},{48,38.9435,0.0793863},};
Ach3={{1100,83.7492,0.641069},{1200,173.849,1.13833},{1300,339.706,2.03086},{1400,603.047,5.02138},{1500,907.05,7.9987},};
  for (int i=0;i< ch1.size();i++) ch1[i][1]*=(1.0e7/1.6);
  for (int i=0;i< ch2.size();i++) ch2[i][1]*=(1.0e7/1.6);
  for (int i=0;i< ch3.size();i++) ch3[i][1]*=(1.0e7/1.6);

  FillTG(&tg1,ch1,"Gain"); tg1.SetMarkerColor(color[1]); tg1.SetDrawOption("P");tg1.SetMarkerStyle(28);
  FillTG(&tg2,ch2,"Gain"); tg2.SetMarkerColor(color[2]); tg2.SetDrawOption("P");tg2.SetMarkerStyle(28);
  FillTG(&tg3,ch3,"Gain"); tg3.SetMarkerColor(color[3]); tg3.SetDrawOption("P");tg3.SetMarkerStyle(28);

	cout<<ch1[0][0]<<endl;
	cout<<ch1[3][0]<<endl;
	lets_pause();
  f1=MyTF1(1,ch1[0][0],ch1[3][0]); f1->SetLineStyle(3);
  f2=MyTF1(2,ch2[0][0],ch2[3][0]);f2->SetLineStyle(3);
  f3=MyTF1Expo(3,ch3[0][0],ch3[3][0]);f3->SetLineStyle(3);
  TFitResultPtr r1 = tg1.Fit(f1,"ESR"); cout << gMinuit->fCstatu << endl;//tg1.Draw("ALP E1");lets_pause();
  TFitResultPtr r2 = tg2.Fit(f2,"ESR"); cout << gMinuit->fCstatu << endl;//tg2.Draw("ALP E1");lets_pause();
  TFitResultPtr r3 = tg3.Fit(f3,"ESR"); cout << gMinuit->fCstatu << endl;//tg3.Draw("ALP E1");lets_pause();
  FillTG(&tgAmp1,Ach1,"SPE Amplitude (ADC)"); tgAmp1.SetMarkerColor(color[1]); tgAmp1.SetDrawOption("P");tgAmp1.SetMarkerStyle(22);
  FillTG(&tgAmp2,Ach2,"SPE Amplitude (ADC)"); tgAmp2.SetMarkerColor(color[2]); tgAmp2.SetDrawOption("P");tgAmp2.SetMarkerStyle(22);
  FillTG(&tgAmp3,Ach3,"SPE Amplitude (ADC)"); tgAmp3.SetMarkerColor(color[3]); tgAmp3.SetDrawOption("P");tgAmp3.SetMarkerStyle(22);

  fAmp1=MyTF1(1,ch1[0][0],ch1[3][0]);fAmp1->SetLineStyle(3);
  fAmp2=MyTF1(2,ch2[0][0],ch2[3][0]);fAmp2->SetLineStyle(3);
  fAmp3=MyTF1Expo(3,ch3[0][0],ch3[3][0]); fAmp3->SetLineStyle(3);
  TCanvas *c = new TCanvas("c"); tgAmp1.Draw("ALP E1");
  TFitResultPtr rAmp1 = tgAmp1.Fit(fAmp1,"ESR"); cout << gMinuit->fCstatu << endl; tgAmp1.Draw("ALP E1");
  TFitResultPtr rAmp2 = tgAmp2.Fit(fAmp2,"ESR"); cout << gMinuit->fCstatu << endl; tgAmp2.Draw("ALP E1");
  TFitResultPtr rAmp3 = tgAmp3.Fit(fAmp3,"ESR"); cout << gMinuit->fCstatu << endl; 

  //~PrintBreakVoltage();
  PrintFitPars();
  return m;
 }

 void Cal20210527()
 {


  name="20210527";
  std::vector<std::vector<float>> ch1,ch2,ch3;
  std::vector<std::vector<float>> Ach1,Ach2,Ach3; 
//Charges
ch1={{45,1.41808,0.0847416},{46,3.50149,0.0196416},{47,5.0769,0.0190195},{48,6.80827,0.0220524},};
ch2={{45,1.74845,0.030561},{46,3.54021,0.0197394},{47,5.24343,0.0182747},{48,6.98434,0.0209997},};
ch3={{1100,1.89666,0.0299478},{1200,4.1437,0.0365805},{1300,7.90191,0.0611942},{1400,13.6004,0.125641},{1500,20.9763,0.157678},};
//Amplitudes
Ach1={{45,18.1024,0.0820235},{46,25.1585,0.057104},{47,31.7485,0.0511961},{48,38.4748,0.0555488},};
Ach2={{45,19.0023,0.0634801},{46,25.843,0.050201},{47,32.3873,0.0550602},{48,39.0022,0.0655927},};
Ach3={{1100,300.747,58.162},{1200,665.105,141.3},{1300,2225,225.22},{1400,4071.78,385.35},{1500,1876.08,757.409},};  for (int i=0;i< ch1.size();i++) ch1[i][1]*=(1.0e7/1.6);
  for (int i=0;i< ch2.size();i++) ch2[i][1]*=(1.0e7/1.6);
  for (int i=0;i< ch3.size();i++) ch3[i][1]*=(1.0e7/1.6);

  FillTG(&tg1,ch1,"Gain"); tg1.SetMarkerColor(color[1]); tg1.SetDrawOption("P");tg1.SetMarkerStyle(28);
  FillTG(&tg2,ch2,"Gain"); tg2.SetMarkerColor(color[2]); tg2.SetDrawOption("P");tg2.SetMarkerStyle(28);
  FillTG(&tg3,ch3,"Gain"); tg3.SetMarkerColor(color[3]); tg3.SetDrawOption("P");tg3.SetMarkerStyle(28);

	cout<<ch1[0][0]<<endl;
	cout<<ch1[3][0]<<endl;
	lets_pause();
  f1=MyTF1(1,ch1[0][0],ch1[3][0]); f1->SetLineStyle(3);
  f2=MyTF1(2,ch2[0][0],ch2[3][0]);f2->SetLineStyle(3);
  f3=MyTF1Expo(3,ch3[0][0],ch3[3][0]);f3->SetLineStyle(3);
  TFitResultPtr r1 = tg1.Fit(f1,"ESR"); cout << gMinuit->fCstatu << endl;//tg1.Draw("ALP E1");lets_pause();
  TFitResultPtr r2 = tg2.Fit(f2,"ESR"); cout << gMinuit->fCstatu << endl;//tg2.Draw("ALP E1");lets_pause();
  TFitResultPtr r3 = tg3.Fit(f3,"ESR"); cout << gMinuit->fCstatu << endl;//tg3.Draw("ALP E1");lets_pause();
  FillTG(&tgAmp1,Ach1,"SPE Amplitude (ADC)"); tgAmp1.SetMarkerColor(color[1]); tgAmp1.SetDrawOption("P");tgAmp1.SetMarkerStyle(22);
  FillTG(&tgAmp2,Ach2,"SPE Amplitude (ADC)"); tgAmp2.SetMarkerColor(color[2]); tgAmp2.SetDrawOption("P");tgAmp2.SetMarkerStyle(22);
  FillTG(&tgAmp3,Ach3,"SPE Amplitude (ADC)"); tgAmp3.SetMarkerColor(color[3]); tgAmp3.SetDrawOption("P");tgAmp3.SetMarkerStyle(22);

  fAmp1=MyTF1(1,ch1[0][0],ch1[3][0]);fAmp1->SetLineStyle(3);
  fAmp2=MyTF1(2,ch2[0][0],ch2[3][0]);fAmp2->SetLineStyle(3);
  fAmp3=MyTF1Expo(3,ch3[0][0],ch3[3][0]); fAmp3->SetLineStyle(3);
  TCanvas *c = new TCanvas("c"); tgAmp1.Draw("ALP E1");
  TFitResultPtr rAmp1 = tgAmp1.Fit(fAmp1,"ESR"); cout << gMinuit->fCstatu << endl; tgAmp1.Draw("ALP E1");
  TFitResultPtr rAmp2 = tgAmp2.Fit(fAmp2,"ESR"); cout << gMinuit->fCstatu << endl; tgAmp2.Draw("ALP E1");
  TFitResultPtr rAmp3 = tgAmp3.Fit(fAmp3,"ESR"); cout << gMinuit->fCstatu << endl; 

  //~PrintBreakVoltage();
  PrintFitPars();
  return m;
 }

};
void LinFit()
{
  Calib_t m0, m1, m5,m6,m7, myc;

 m0.Cal20210527();
m0.tg1.Draw("ALP"); lets_pause();

 m1.Cal20210501();
 m5.Cal20210502();
 m6.Cal20210503();
 m7.Cal20210504();

 //~m1.Cal20210502();
 //~m5.Cal20210503();
 //~m6.Cal20210504();
 
//~myc.Draw();
//~m1.tg1.Draw("ALP"); lets_pause();
//~m6.tg1.Draw("ALP");

  float x1=0.02;
  float y1=0.5;
  float x2=x1+0.4;//anchura
  float y2=0.97; //altura
  TLegend *leg = new TLegend(x1,y1,x2,y2);
  leg->AddEntry(&(m1.tg1),"May 01- SiPM1");
  //~leg->AddEntry(&(m1.tg2),"May 01 - SiPM2");
  //~leg->AddEntry(&(m5.tg1),"May 02- SiPM1");
  //~leg->AddEntry(&(m5.tg2),"May 02 - SiPM2");
  //~leg->AddEntry(&(m6.tg1),"May 03 - SiPM1");
  //~leg->AddEntry(&(m6.tg2),"May 03 - SiPM2");
  leg->AddEntry(&(m7.tg1),"May 04 - SiPM1");
  //~leg->AddEntry(&(m7.tg2),"May 04 - SiPM2");

  TLegend *leg1 = new TLegend(x1,y1,x2,y2);
  leg1->AddEntry(&m0.tg3,"Feb - PMT");
  leg1->AddEntry(&m1.tg3,"Apr - PMT");

  TMultiGraph *m = new TMultiGraph();
  //~m->Add(&m0.tg1);
  //~m->Add(&(m0.tg2));
  m->Add(&(m1.tg1));
  //~m->Add(&(m1.tg2));
  //~m->Add(&(m5.tg1));
  //~m->Add(&(m5.tg2));
  //~m->Add(&(m6.tg1));
  //~m->Add(&(m6.tg2));
  m->Add(&(m7.tg1));
  //~m->Add(&(m7.tg2));
  
//  m->Add(&tg3);
  TMultiGraph *m2 = new TMultiGraph();
  m2->Add(&m0.tgAmp1);
  m2->Add(&m0.tgAmp2); 
  m2->Add(&m1.tgAmp1);
  m2->Add(&m1.tgAmp2); 
  TMultiGraph *m3 = new TMultiGraph();
  m3->Add(&m0.tg3);
  m3->Add(&m1.tg3); 
  TMultiGraph *m4 = new TMultiGraph();
  m4->Add(&m0.tgAmp3);
  m4->Add(&m1.tgAmp3); 

  TCanvas *c3 = new TCanvas("c3");
  c3->Divide(2,2);
  c3->cd(1);
  m->Draw("AP"); 
  m7.f1->Draw("SAME");
  //~m7.f2->Draw("SAME");
  m1.f1->Draw("SAME");
  //~m1.f2->Draw("SAME");  leg->Draw();
  m->GetXaxis()->SetTitle("Voltage (V)");
  m->GetYaxis()->SetTitle("Gain");
  c3->cd(2);
  m2->Draw("AP");
  m0.fAmp1->Draw("SAME");
  m0.fAmp2->Draw("SAME");
  m1.fAmp1->Draw("SAME");
  m1.fAmp2->Draw("SAME");
  m2->GetXaxis()->SetTitle("Voltage (V)");
  m2->GetYaxis()->SetTitle("Amplitude (ADC)");
  c3->cd(3);
  m3->Draw("AP");
  m0.f3->Draw("SAME");
  m1.f3->Draw("SAME");
  setlogscale(c3->cd(3),m3);
  m3->GetXaxis()->SetTitle("Voltage (V)");
  m3->GetYaxis()->SetTitle("Charge (pC)");
  c3->cd(4);
  m4->Draw("AP");
  m0.fAmp3->Draw("SAME");
  m1.fAmp3->Draw("SAME");leg1->Draw();
  setlogscale(c3->cd(4),m4);
  m4->GetXaxis()->SetTitle("Voltage (V)");
  m4->GetYaxis()->SetTitle("Amplitude (ADC)");

//  cout << "voltage of ch 3 at 100ADC  " << (100-fAmp3->GetParameter(0))/fAmp3->GetParameter(1) << endl;

  //m->GetXaxis()->SetRangeUser(0,49);
  lets_pause();
}

