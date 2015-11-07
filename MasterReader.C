#include<iostream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TLorentzVector.h"
#include<vector>
#include "TTree.h"
#include "ClassReadTree.cc"
#include "tdrstyle.C"

using namespace std;


void MasterReader(){
 setTDRStyle();


int Bin[1] = { 50 };
int Min[1] = { 0 };
int Max[1] = { 50 };

Bool_t weight = true;
//float PUWeight[40] = {0, 0, 0, 2.21325, 1.62305, 4.42651, 5.07037, 3.05832, 3.29775, 3.67892, 2.80104, 2.8437, 2.11017, 1.84711, 1.28861, 0.895968, 0.784445, 0.868598, 0.442651, 0.376724, 0.311052, 0.286421, 0.210786, 0, 0.0491834, 0.17706, 0.14755, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//float PUWeight[35] = {1, 1, 1, 1.43654, 1.05346, 2.87307, 3.29097, 1.98503, 2.14044, 2.38784, 1.81804, 1.84573, 1.36963, 1.19889, 0.836383, 0.581537, 0.509152, 0.563772, 0.287307, 0.244517, 0.201891, 0.185905, 0.136813, 1, 0.031923, 0.114923, 0.095769, 1, 1, 1, 1, 1, 1, 1, 1};
float PUWeight[50] = {1, 1, 1, 1.43939, 1.05556, 2.87879, 3.29752, 1.98898, 2.1447, 2.39259, 1.82166, 1.8494, 1.37235, 1.20127, 0.838047, 0.582694, 0.510165, 0.564894, 0.287879, 0.245003, 0.202293, 0.186274, 0.137085, 1, 0.0319865, 0.115152, 0.0959596, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
int NumPV;
int j=0;	//for bins
int k=2;	//reseting the color of backgrounds
	TCanvas * c1 = new TCanvas("c1","",500,500);

	THStack** hs = new THStack*[1];
	TPad** pad = new TPad*[1];
	TPad** padB = new TPad*[1];
	TH1F**hRatio = new TH1F*[1];
	double eps = 0.005;
	for(int i=0; i<1;i++){
		hs[i] = new THStack(Form("hs%i",i),"");
		
		pad[i] = new TPad(Form("pad%i",i),"",0.0,0.5,1.0,1.0,0);pad[i]->Draw();
		padB[i] = new TPad(Form("padB%i",i),"",0.0,0.0,1.0,0.05,0);//padB[i]->Draw();
		hRatio[i] = new TH1F(Form("hRatio%i",i),"Ratio",Bin[i],Min[i],Max[i]);
	}

	TH1F** SigHist = new TH1F*[1];
	for(int i=0; i<1;i++){
		SigHist[i] = new TH1F(Form("SigHist%i",i),"",Bin[i],Min[i],Max[i]);
		SigHist[i]->SetLineColor(1);
		//SigHist[i]->SetFillColor(1);
	}

	TH1F** t0_BkgHist = new TH1F*[1];
	for(int i=0; i<1;i++){
		if (i%1==0)     {j=0;	//for reset bins
				k++;}	// for line & Fill color
		else j++;
		t0_BkgHist[i] = new TH1F(Form("t0_BkgHist%i",i),"",Bin[j],Min[j],Max[j]);
		t0_BkgHist[i]->SetLineColor(k);
		t0_BkgHist[i]->SetFillColor(k);
	}

	TH1F** DataHist = new TH1F*[1];
	for(int i=0; i<1;i++){
		DataHist[i] = new TH1F(Form("DataHist%i",i),"",Bin[i],Min[i],Max[i]);
		DataHist[i]->SetLineColor(2);
	}

	TChain* t0_mc_sig = new TChain("otree");
		t0_mc_sig->Add("/home/rksharma/TEMP/AnalysisWWTrees/output_mu/WLWL_ele_FullData.root");
		ClassReadTree mc_sig_0(t0_mc_sig);
		for(int iEv_0_mc_sig=0;iEv_0_mc_sig < t0_mc_sig->GetEntries();iEv_0_mc_sig++){
			t0_mc_sig->GetEntry(iEv_0_mc_sig);
			SigHist[0]->Fill(mc_sig_0.nPV);
		}


	TChain* t0_mc_bkg = new TChain("otree");
		t0_mc_bkg->Add("/home/rksharma/TEMP/AnalysisWWTrees/output_mu/WJets_FullData.root");
		ClassReadTree mc_bkg_0(t0_mc_bkg);
		for(int iEv_0_mc_bkg=0;iEv_0_mc_bkg < t0_mc_bkg->GetEntries();iEv_0_mc_bkg++){
			t0_mc_bkg->GetEntry(iEv_0_mc_bkg);
			NumPV=mc_bkg_0.nPV;
			#if 1
				//t0_BkgHist[0]->Fill(mc_bkg_0.nPV);
				cout<<"NumPV = "<<NumPV<<"\t weight = "<<PUWeight[NumPV-1]<<endl;
				t0_BkgHist[0]->Fill(mc_bkg_0.nPV * PUWeight[NumPV-1]);
			#else
				t0_BkgHist[0]->Fill(mc_bkg_0.nPV * PUWeight[NumPV]);
			#endif
		}


	TChain* t0_data = new TChain("otree");
		t0_data->Add("/home/rksharma/TEMP/AnalysisWWTrees/output_mu/data_mu_prompt_25ns_runD_v3_FullData.root");
		ClassReadTree mc_data_0(t0_data);
		for(int iEv_0_data=0;iEv_0_data < t0_data->GetEntries();iEv_0_data++){
			t0_data->GetEntry(iEv_0_data);
			DataHist[0]->Fill(mc_data_0.nPV);
		}


	TLegend *leg = new TLegend(0.70,0.80,0.85,0.90,NULL,"brNDC");

double yMax=0.;
double HistMax=0.0;
c1->cd();
pad[0]->SetBottomMargin(0.05555562);
//pad[0]->SetLogy(1);
pad[0]->Draw();
pad[0]->cd();
	#if 1
		SigHist[0]->Scale(1./SigHist[0]->Integral());
		cout<<"signal normalized to unity"<<endl;
	#else
		SigHist[0]->Scale((0.0413*442.264)/499600.);
	#endif
	HistMax = SigHist[0]->GetMaximum()*2.15;
	SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(SigHist[0],"Signal","l");
	yMax=HistMax;

	#if 1
		t0_BkgHist[0]->Scale(1./t0_BkgHist[0]->Integral());
	#else
		t0_BkgHist[0]->Scale(1.129558);
	#endif
	HistMax = t0_BkgHist[0]->GetMaximum()*2.15;
	SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_BkgHist[0],"WJets","l");
	yMax=HistMax;

	#if 1
		DataHist[0]->Scale(1./DataHist[0]->Integral());
	#else
		DataHist[0]->Sumw2();
	#endif
	HistMax = DataHist[0]->GetMaximum()*2.15;
	SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(DataHist[0],"Data","l");
	yMax=HistMax;

	hs[0]->Add(t0_BkgHist[0]);
	#if 1
		hs[0]->SetMaximum(0.13);
	#else
		hs[0]->SetMaximum(230.);
	#endif
	hs[0]->SetMinimum(0.);
	//hs[0]->GetYaxis()->SetLimit(0,230);
	//hs[0]->GetYaxis()->SetRangeUser(0,230);
	hs[0]->Draw();
	DataHist[0]->Draw("same");
	SigHist[0]->Draw("same");
	leg->Draw("same");
TH1F *h2 = (TH1F*)DataHist[0]->Clone();
hRatio[0]->Add(t0_BkgHist[0]);


padB[0]->SetGridy(1);
padB[0]->SetTopMargin(0.1);
padB[0]->SetBottomMargin(0.30);
//padB[0]->Draw();
//padB[0]->cd();

float yscale = (1.0-0.2)/(0.18-0);
h2->Divide(hRatio[0]);
for(int i= 1; i<=50;i++)
	if (h2->GetBinContent(i) ==0)
		cout<<1<<", ";
	else
		cout<<h2->GetBinContent(i)<<", ";
	cout<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("nPV");
h2->SetMinimum(-0.2);
h2->SetMaximum(3.2);
h2->GetXaxis()->SetTitleOffset(0.8);
h2->GetXaxis()->SetLabelSize(0.033*yscale);
h2->GetXaxis()->SetTitleSize(0.036*yscale);
h2->GetXaxis()->SetTickLength(0.03*yscale);
h2->GetYaxis()->SetTitleOffset(0.3);
h2->GetYaxis()->SetNdivisions(5);
h2->GetYaxis()->SetLabelSize(0.033*yscale);
h2->GetYaxis()->SetTitleSize(0.036*yscale);
//h2->Draw("");
	c1->SaveAs("nPV.pdf");
	leg->Clear();
	c1->Clear();
	//###########################################################




}
