/*
 *
 * this program plots one branch from different root files on the same histogram 
 * 
 * var1 is the variable that we want to plot
 * var2 :: presently Not in use
 * 
 * n is the number of input rootfiles 
 * 
 * format to enter
 * 
 * 	$root -l
 * 	root[].L CompareAdvanced.C
 * 	root[]compareQuantities(1, 0, 0, "branch_name","", "x-axis Title",10,0,200,Cut,2,"abc.root","abc","xyz.root","xyz");
 * 
 * abc.root is the name of root file  --->>> abc is the legend of abc.root;   similarly others.
 * 
 * void compareQuantities(bool NormUnity, bool NormLumi, bool ShowEvents, string treeName, string var1, string var2, string xtitle, int nbins, float min, float max, string cut, int n , ... ){
 * 
*/
#include <string>
#include <iostream>
#include <fstream>
#include "TFile.h"
#include "TNtuple.h"
#include <vector>
#include "TCanvas.h"
#include "TPad.h"
#include "TH1F.h"
#include "TGaxis.h"
#include "TFrame.h"
#include "TLegend.h"
#include "TMath.h"
#include "TLatex.h"
#include "TPaveStats.h"
#include "TROOT.h"
#include "TStyle.h"
//#include "CrossSection.h"

void compareQuantities(bool NormUnity, bool NormLumi, bool ShowEventsLeg, bool legDraw, int GetStatBox, const char* treeName, string var1, string var2, string xtitle, int nbins, float min, float max, TString cut, int n , ... ){
	
    //============= Define few parameters   ========================================
	int color[9] = {2,2,3,4,4,1,7,8,9};
	int style[9] = {1,2,1,1,2,1};
	double yMax = 0.0;	// Initialize Maximum value of y-axis
	double histMax = 0.0;	

	float xSec=0.0; 		// Cross-section
	float Lumi=0.075;	// Luminosity

	TLatex* cmsprem = new TLatex(0,0.45,"CMS Preliminary");
	cmsprem->SetTextSize(0.04);

	if (var2 == "") var2 = var1;
	if (xtitle == "") xtitle = var1;
	

	gStyle->SetOptStat(GetStatBox);
	gROOT->ForceStyle(kTRUE);
	TGaxis::SetMaxDigits(4);

	va_list list;
	va_start(list, n);
	char** fname=new char*[n];
	TFile** tf = new TFile*[n];
	TTree** tt = new TTree*[n];
	TH1F** th = new TH1F*[n];
	TPaveStats** tp = new TPaveStats*[n];

	TLegend * legi = new TLegend(0.1,0.8,0.90,0.9);
	legi->SetTextSize(0.04);
	legi-> SetNColumns(3);

	
	TString cut1;
	for (int i=0;i<n;i++)
	{


		fname[i]=va_arg(list, char*);
		tf[i] = new TFile(fname[i]);
		tt[i] = (TTree*) tf[i]->Get(treeName);
		th[i] = new TH1F(Form("th%i",i),"",nbins,min,max);
		cut1=cut;
		tt[i]->Draw(Form("%s>>th%i",var1.c_str(),i), cut1, "goff");
		cut1 = "";
		
		th[i]->SetStats(GetStatBox);
		th[i]->SetLineWidth(3);
		th[i]->SetLineStyle(style[i]);
		th[i]->SetLineColor(color[i]);
		
		th[i]->GetYaxis()->CenterTitle();
		th[i]->GetYaxis()->SetTitleOffset(1.30);
		th[i]->GetXaxis()->SetTitle(xtitle.c_str());
		th[i]->GetXaxis()->CenterTitle();

		string tmp_str=va_arg(list,char*);

		if (NormLumi)
		{
		if (tmp_str.find("TT")==0) xSec= 0.0653247402978 ;
		if (tmp_str.find("LL")==0) xSec= 0.00602216848487 ;
		if (tmp_str.find("LT")==0) xSec= 0.0383084772305 ;
		if (tmp_str.find("TOT")==0) xSec= 0.109528995006 ;
		if (tmp_str.find("LL_nn23lo1")==0) xSec=0.0060286880679;
		if (tmp_str.find("LL_cteq6l1")==0) xSec=0.00617863847773;

		if (i==0) th[i]->Scale((Lumi*xSec)/th[i]->Integral());
		th[i]->Scale((Lumi*xSec)/th[i]->Integral());

		histMax = th[i]->GetMaximum()*1.20;
		th[0]->SetMaximum(TMath::Max(histMax,yMax));
		yMax = TMath::Max(histMax,yMax);

		th[i]->GetYaxis()->SetTitle("Normalized to Lumi");
		}


		if (NormUnity)
		{
		/*
		 *Normalized to Unity Part
		 */
		if (i==0) th[i]->Scale(1./th[i]->Integral());
		th[i]->Scale(1./th[i]->Integral());
		th[i]->GetYaxis()->SetTitle("Fraction of Events");
		th[0]->SetMaximum(TMath::Max(th[i]->GetMaximum()*1.20,yMax));
		yMax = TMath::Max(th[i]->GetMaximum()*1.20,yMax);
		 
		/*
		 * Normalized one histogram with another
		 */
		/* 
		if (i==0) float num = th[i]->Integral();
		if (i==1) th[i]->Scale(num/(th[i]->Integral()));
		th[i]->GetYaxis()->SetTitle("Number of Events");
		th[0]->SetMaximum(TMath::Max(th[i]->GetMaximum()*1.10,yMax));
		yMax = TMath::Max(th[i]->GetMaximum()*1.10,yMax);
		*/
		}
		
		if (i==0) th[i]->Draw(); else th[i]->Draw("sames");

		if (ShowEventsLeg)
		{
		int entries = th[i]->GetEntries();
		char c[20];
		sprintf(c," (%d)",(entries));
		//sprintf(c,"%d Events",entries);

		TString p = TString(tmp_str) + TString(c);

		legi->AddEntry(th[i],TString(p),"l");
		}
		else
		{
		legi->AddEntry(th[i],tmp_str.c_str(),"l");
		}

		if (legDraw)
		    legi->Draw("sames");
	}
	va_end(list);


}
