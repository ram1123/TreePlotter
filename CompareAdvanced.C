/*
 *
 * this program plots one branch from different root files on the same histogram 
 * 
 * var1 is the variable that we want to plot
 * 
 * n is the number of input rootfiles 
 * 
 * var2 :: presently Not in use
 * format to enter
 * 
 * 	$root -l
 * 	root[].L CompareAdvanced.C
 * 	root[]compareQuantities(1, 0, 0, "branch_name","", "x-axis Title",10,0,200,Cut,2,"abc.root","abc","xyz.root","xyz");
 * 
 * abc.root is the name of root file  --->>> abc is the legend of abc.root;   similarly others.
 * 
 * void compareQuantities(bool NormUnity, bool NormLumi, bool ShowEvents, string var1, string var2, string xtitle, int nbins, float min, float max, string cut, int n , ... ){
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

void compareQuantities(bool NormUnity, bool NormLumi, bool ShowEvents, string var1, string var2, string xtitle, int nbins, float min, float max, TString cut, int n , ... ){
	
    //============= START:: This sets the legend position ============================
	float a1=0.29;
	float a2;
		if (n<=3) a2=0.59;
		else 
		if (n==4) a2=0.42;
		else
		{
		cout<<"Please Enter the Correct value of size of legend"<<endl;
		a2=0.42;
		}
    //============= END:: This sets the legend position ============================

    //============= Define few parameters   ========================================
	int color[9] = {2,4,3,1,5,1,7,8,9};
	int style[9] = {1,2,3,4,1,4};
	double yMax = 0.0;	// Initialize Maximum value of y-axis
	double histMax = 0.0;	

	float xSec=0.0; 		// Cross-section
	float Lumi=0.075;	// Luminosity

	TLatex* cmsprem = new TLatex(0,0.45,"CMS Preliminary");
	cmsprem->SetTextSize(0.04);

	if (var2 == "") var2 = var1;
	if (xtitle == "") xtitle = var1;
	

	gStyle->SetOptStat(0);
	gROOT->ForceStyle(kTRUE);
	TGaxis::SetMaxDigits(3);

	va_list list;
	va_start(list, n);
	char** fname=new char*[n];
	TFile** tf = new TFile*[n];
	TTree** tt = new TTree*[n];
	TH1F** th = new TH1F*[n];
	TPaveStats** tp = new TPaveStats*[n];
	TLegend** leg = new TLegend*[n];
	
	TString cut1;
	for (int i=0;i<n;i++)
	{


		fname[i]=va_arg(list, char*);
		tf[i] = new TFile(fname[i]);
		//tt[i] = (TTree*) tf[i]->Get("demo/tree");
		tt[i] = (TTree*) tf[i]->Get("otree");
		//tt[i] = (TTree*) tf[i]->Get("TreeMaker2/PreSelection");
		th[i] = new TH1F(Form("th%i",i),"",nbins,min,max);
		//if (i==1) 
		//cut1 = "eff_and_pu_Weight"+TString(cut);
		cut1=cut;
		tt[i]->Draw(Form("%s>>th%i",var1.c_str(),i), cut1, "goff");
		cut1 = "";
		
		th[i]->SetStats(0);
		th[i]->SetLineWidth(2);
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

		histMax = th[i]->GetMaximum()*1.15;
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
		th[0]->SetMaximum(TMath::Max(th[i]->GetMaximum()*1.10,yMax));
		yMax = TMath::Max(th[i]->GetMaximum()*1.10,yMax);
		 
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

		if (ShowEvents)
		{
		if (n==2) leg[i] = new TLegend(a1,0.89,a2,0.99);
		else leg[i] = new TLegend(a1,0.82,a2,0.99);
		leg[i]->AddEntry(th[i],tmp_str.c_str(),"l");

		int entries = th[i]->GetEntries();
		char c[20];
		sprintf(c,"%d",entries);

		leg[i]->AddEntry(th[i],TString(c),"l");
		}
		else
		{
		if (n==2) leg[i] = new TLegend(a1,0.89,a2,0.95);
		else leg[i] = new TLegend(a1,0.89,a2,0.95);
		leg[i]->AddEntry(th[i],tmp_str.c_str(),"l");
		}
		//leg[i]->AddEntry(th[i],va_arg(list, char*),"l");
		if (n==2) leg[i]->SetTextSize(0.05);

		leg[i]->Draw("sames");
		//cmsprem->Draw();

		a1 = a2;
		if (n==2) a2=a2+0.30;
		else a2 = a2+0.16;
//		cout<<"histogram  "<<Form("th%i",i)<<"  entries = "<<th[i]->GetEntries()<<endl;

	}
	va_end(list);


}
