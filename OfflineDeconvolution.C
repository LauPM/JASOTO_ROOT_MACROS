/*
Macro para dibujar el perfil de centelleo de distintos runes superpuesto uno sobre otro.
Toma los perfiles ya generados a partir de la macro AverageWaveform.C, y los plotea juntos en el mismo canvas.
*/
#include"lib/headers.h"

    std::map<int,TH1D> SiPMResponse;
    void LoadSiPMResponse(int ch)
    {
       TFile *f = new TFile("AnalysisROOT/AvWf_SPE.root","READ"); 
       SiPMResponse[ch] = *((TH1D*)f->Get(Form("Run4_ch%i_ADC%i_0V_ScintProfFirstSignalBin_0_",ch,ch+1))->Clone(Form("SiPMResponse_ch%i",ch)));
//       SiPMResponse[ch].Draw("HIST"); lets_pause();
       //if(!SiPMResponse[ch]) { cout << "Error, SiPM response not found!!!" << std::endl;throw std::exception();}
       f->Close();
       
    }
    TH1D* GetSiPMResponse(int ch)
    {
       if(SiPMResponse.find(ch)== SiPMResponse.end()) LoadSiPMResponse(ch);
       return &SiPMResponse[ch];
    }


void Draw2(int n, int *runs, string* name, int* pm,int Rebin=1, string sfile="ScintProfFirstSignalBin")
{
ana::HistogramCollection_t mycol[n];
 for(int i=0;i<n;i++) mycol[i].GetFromFile(Form("AnalysisROOT/Run%i_%s.root",runs[i],sfile.c_str()));

 cout << "Hist loaded " << endl;
 TH1 *h[n];

 for(int i=0;i<n;i++)
 {
   h[i]=(TH1D*)(mycol[i].GetByOpChannel(pm[i]))[0];
   TSpectrum *s = new TSpectrum();
   int nbins=((TH1D*)h[i])->GetSize()-2; cout << nbins << endl;
   Double_t source[nbins];
   Double_t response[nbins];



//  int binmax = h[i]->GetMaximumBin();
//  double xmax = h[i]->GetXaxis()->GetBinCenter(binmax);
//  double ymax = h[i]->GetBinContent(binmax);

   TH1D * res= GetSiPMResponse(pm[i]); //res->Draw("HIST"); lets_pause();

//  int binmaxs = res->GetMaximumBin();
//  double xmaxs = res->GetXaxis()->GetBinCenter(binmax);
//  double ymaxs = res->GetBinContent(binmax);
  int maxbin2=res->FindFirstBinAbove(5); cout << maxbin2 << endl;
   for (int ii = 0; ii < nbins; ii++) response[ii]=0.0;
   for (int ii = 0; ii+maxbin2 < res->GetSize()-2; ii++) response[ii]=res->GetBinContent(maxbin2-1 + ii);
   for (int ii = 0; ii < nbins; ii++) if(response[ii]<0.1) response[ii]=0.1;
/*
   for (int ii = 0; ii < nbins; ii++)  source[ii]=0.0;
   for (int ii = 0; ii+maxbin2 < res->GetSize()-2; ii++) source[ii+200]=res->GetBinContent(maxbin2-2 + ii);
   for (int ii = 0; ii < nbins; ii++) if(source[ii]<0) source[ii]=0.0;
//*/
//*
   for (int ii = 0; ii < nbins; ii++) source[ii]=h[i]->GetBinContent(ii+1);
   for (int ii = 0; ii < nbins; ii++) if(source[ii]<0.1) source[ii]=0.1;
//*/
   TH1F *d1 = (TH1F*) h[i]->Clone("Signal"); d1->SetTitle("Signal");d1->SetLineColor(kBlue);
   for (int ii = 0; ii < nbins; ii++) {d1->SetBinContent(ii + 1,source[ii]);}
   auto result = s->Deconvolution(source,response,nbins,20000,2,1);
   //cout << "Result: " << result << endl;
   double sum=0;for (int ii = 0; ii < nbins; ii++) sum+=source[ii];
   cout << "SUM: " << sum << endl << endl << endl << endl;


   TH1F *d2 = (TH1F*) h[i]->Clone("Deconvolution"); d2->SetTitle("Deconvolution");d2->SetLineColor(kGreen);
   for (int ii = 0; ii < nbins; ii++) {d2->SetBinContent(ii + 1,source[ii]);}
   TH1F *dres = (TH1F*) h[i]->Clone("Response"); dres->SetTitle("Response");dres->SetLineColor(kRed);
   for (int ii = 0; ii < nbins; ii++) {dres->SetBinContent(ii + 1,response[ii]);}
//   h[i]->Draw("HIST L");
   d1->Draw("HIST L");
   d2->Draw("HIST SAME L");
   dres->Draw("HIST SAME L");
   gPad->BuildLegend();
   lets_pause();
 }
 cout << "Hist loaded " << endl;
 TCanvas *c = new TCanvas("c");gStyle->SetOptStat(0);gStyle->SetOptTitle(0);
 c->cd();
 for(int i=0;i<n;i++) h[i]->Draw("HIST SAME");
 gPad->BuildLegend();
 lets_pause();  
}

void OfflineDeconvolution()
{

   string name[2]={"Run 12 - 11/02","Run 13 - 11/02"};
   int runs[2]={13,13};
   int pms[2]={0,0};
   Draw2( 2,runs,name,pms,1,"ScintProfFirstSignalBin_NotNormalize");


}
