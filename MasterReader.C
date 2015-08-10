#include<iostream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TLorentzVector.h"
#include<vector>
#include "TTree.h"
#include "ClassReadTree.cc"
using namespace std;


void MasterReader(){
 
int Bin[3] = { 40 , 20 , 30 };
int Min[3] = { 0 , 0 , 50 };
int Max[3] = { 40 , 20 , 500 };

	TH1F** SigHist = new TH1F*[3];
	for(int i=0; i<3;i++){
		SigHist[i] = new TH1F(Form("SigHist%i",i),"",Bin[i],Min[i],Max[i]);
		SigHist[i]->SetLineColor(1);
	}

	TH1F** BkgHist = new TH1F*[3];
	for(int i=0; i<3;i++){
		BkgHist[i] = new TH1F(Form("BkgHist%i",i),"",Bin[i],Min[i],Max[i]);
		BkgHist[i]->SetLineColor(2);
	}

	TH1F** DataHist = new TH1F*[3];
	for(int i=0; i<3;i++){
		DataHist[i] = new TH1F(Form("DataHist%i",i),"",Bin[i],Min[i],Max[i]);
		DataHist[i]->SetLineColor(3);
	}

	TChain* t0_mc_sig = new TChain("otree");
		t0_mc_sig->Add("/home/ramkrishna/TEMP/AnalysisWWTrees/WWTree_el/WWTree_WW.root");
		ClassReadTree mc_sig_0(t0_mc_sig);
		for(int iEv_0_mc_sig=0;iEv_0_mc_sig < t0_mc_sig->GetEntries();iEv_0_mc_sig++){
			t0_mc_sig->GetEntry(iEv_0_mc_sig);
			SigHist[0]->Fill(mc_sig_0.nPV);
			SigHist[1]->Fill(mc_sig_0.eff_and_pu_Weight);
			SigHist[2]->Fill(mc_sig_0.pfMET);
		}


	TChain* t0_mc_bkg = new TChain("otree");
		t0_mc_bkg->Add("/home/ramkrishna/TEMP/AnalysisWWTrees/WWTree_el/WWTree_WJets.root");
		ClassReadTree mc_bkg_0(t0_mc_bkg);
		for(int iEv_0_mc_bkg=0;iEv_0_mc_bkg < t0_mc_bkg->GetEntries();iEv_0_mc_bkg++){
			t0_mc_bkg->GetEntry(iEv_0_mc_bkg);
			BkgHist[0]->Fill(mc_bkg_0.nPV);
			BkgHist[1]->Fill(mc_bkg_0.eff_and_pu_Weight);
			BkgHist[2]->Fill(mc_bkg_0.pfMET);
		}


	TChain* t0_data = new TChain("otree");
		t0_data->Add("/home/ramkrishna/TEMP/AnalysisWWTrees/WWTree_el/WWTree_data.root");
		ClassReadTree mc_data_0(t0_data);
		for(int iEv_0_data=0;iEv_0_data < t0_data->GetEntries();iEv_0_data++){
			t0_data->GetEntry(iEv_0_data);
			DataHist[0]->Fill(mc_data_0.nPV);
			DataHist[1]->Fill(mc_data_0.eff_and_pu_Weight);
			DataHist[2]->Fill(mc_data_0.pfMET);
		}


	TCanvas * c1 = new TCanvas("c1","",1);

double yMax=0.;
double HistMax;
	SigHist[0]->Scale(1/SigHist[0]->Integral());
	HistMax = SigHist[0]->GetMaximum()*1.15;
	SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	yMax=HistMax;
	SigHist[0]->Draw();
	BkgHist[0]->Scale(1/BkgHist[0]->Integral());
	HistMax = BkgHist[0]->GetMaximum()*1.15;
	SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	yMax=HistMax;
	BkgHist[0]->Draw("same");
	DataHist[0]->Scale(1/DataHist[0]->Integral());
	HistMax = DataHist[0]->GetMaximum()*1.15;
	SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	yMax=HistMax;
	DataHist[0]->Draw("same");
	c1->SaveAs("nPV.pdf");
	c1->Clear();
	SigHist[1]->Scale(1/SigHist[1]->Integral());
	HistMax = SigHist[1]->GetMaximum()*1.15;
	SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	yMax=HistMax;
	SigHist[1]->Draw();
	BkgHist[1]->Scale(1/BkgHist[1]->Integral());
	HistMax = BkgHist[1]->GetMaximum()*1.15;
	SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	yMax=HistMax;
	BkgHist[1]->Draw("same");
	DataHist[1]->Scale(1/DataHist[1]->Integral());
	HistMax = DataHist[1]->GetMaximum()*1.15;
	SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	yMax=HistMax;
	DataHist[1]->Draw("same");
	c1->SaveAs("eff_and_pu_Weight.pdf");
	c1->Clear();
	SigHist[2]->Scale(1/SigHist[2]->Integral());
	HistMax = SigHist[2]->GetMaximum()*1.15;
	SigHist[2]->SetMaximum(TMath::Max(HistMax,yMax));
	yMax=HistMax;
	SigHist[2]->Draw();
	BkgHist[2]->Scale(1/BkgHist[2]->Integral());
	HistMax = BkgHist[2]->GetMaximum()*1.15;
	SigHist[2]->SetMaximum(TMath::Max(HistMax,yMax));
	yMax=HistMax;
	BkgHist[2]->Draw("same");
	DataHist[2]->Scale(1/DataHist[2]->Integral());
	HistMax = DataHist[2]->GetMaximum()*1.15;
	SigHist[2]->SetMaximum(TMath::Max(HistMax,yMax));
	yMax=HistMax;
	DataHist[2]->Draw("same");
	c1->SaveAs("pfMET.pdf");
	c1->Clear();


}
