

#include"lib/headers.h"

void RatesBrutovsCortes()
{
	auto mg=new TMultiGraph;
	
	const Int_t n=5;
	
	TDatime da1(2021,04,30,0,0,0);
    TDatime da2(2021,05,01,0,0,0);
    TDatime da3(2021,05,02,0,0,0);
    TDatime da4(2021,05,03,0,0,0);
    TDatime da5(2021,05,04,0,0,0);
    Double_t _x[n];
    _x[0]=da1.Convert();
    _x[1]=da2.Convert();
    _x[2]=da3.Convert();
    _x[3]=da4.Convert();
    _x[4]=da5.Convert();
    Double_t _xe[n]={0,0,0,0,0};
	Double_t y[n]={23.2643,24.399,24.6997,24.7112,24.4749};
	Double_t ye[n];for (int i=0;i<n;i++) ye[i]=sqrt(y[i]);
	
	
	Double_t y1[n]={24.3011,24.8061,24.7743,24.6668,24.5028};
	Double_t y1e[n];for (int i=0;i<n;i++) y1e[i]=sqrt(y1[i]);
	
	TCanvas *c1 = new TCanvas("c1","",10,10,1000,500);
        c1->SetGrid();
	auto sc= new TGraphErrors(n, _x, y, _xe, ye);
	sc->SetLineColor(kBlack);
	sc->SetMarkerStyle(kFullSquare);
	sc->SetMarkerColor(kBlack);
	
	auto cc= new TGraphErrors(n, _x, y1, _xe, y1e);
	cc->SetLineColor(kRed);
	cc->SetMarkerStyle(kFullCircle);
	cc->SetMarkerColor(kRed);
	

    mg->Add(sc);
    mg->Add(cc);
    
    mg->Draw("APL");
    
    mg->SetTitle("Rate from #alpha source;Date;Rate(Hz)");
    mg->GetXaxis()->SetTimeDisplay(1);
    mg->GetXaxis()->SetTimeFormat("%d-%m");
    mg->GetXaxis()->SetTimeOffset(0,"gmt");
    mg->GetYaxis()->SetRangeUser(0,40);
    mg->GetXaxis()->SetNdivisions(5);
    
   auto legend=new TLegend(0.7, 0.7, 0.9, 0.9);
   legend->AddEntry(sc,"Single Trigger Rate");
   legend->AddEntry(cc,"Coincidence Trigger Rate");
   
   
   legend->Draw();
	
	
	
	
	
	
	
	
}

