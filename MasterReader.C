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


int Bin[33] = { 50 , 40 , 40 , 40 , 40 , 40 , 40 , 40 , 40 , 40 , 40 , 40 , 40 , 40 , 40 , 40 , 40 , 40 , 40 , 40 , 40 , 40 , 40 , 40 , 40 , 40 , 40 , 40 , 40 , 40 , 40 , 40 , 40 };
double Min[33] = { 0 , 0 , -2.6 , -3.4 , 0 , 0 , -3.5 , 0 , 0 , -5.5 , -3.5 , 0 , 0 , -5.5 , -3.5 , 0 , 0 , -5.5 , -3.5 , 400 , 0 , -5.5 , -3.5 , 0 , 0 , -5.5 , -3.5 , 0 , 0 , -6.0 , -3.5 , 0 , 0 };
double Max[33] = { 50 , 300 , 3.7 , 4.1 , 1500 , 300 , 4.1 , 400 , 1500 , 5.5 , 3.5 , 2500 , 500 , 5.5 , 3.5 , 2500 , 600 , 5.5 , 3.5 , 2500 , 300 , 5.0 , 3.5 , 2000 , 250 , 5.5 , 3.5 , 1500 , 400 , 6.0 , 3.5 , 3000 , 1500 };

int NumPV;
int j=0;	//for bins
int k=1;	//reseting the color of backgrounds
	TCanvas * c1 = new TCanvas("c1","",500,500);

	TFile f("/tmp/PileUpHisto.root");
	TH1F *h = (TH1F*)f.Get("j1_1");
	int binidx;
	float Nvtx_weight;

	TH1F *hPUWeight = new TH1F("hPUWeight","",40,0,5);
	THStack** hs = new THStack*[33];
	TPad** pad = new TPad*[33];
	TPad** padB = new TPad*[33];
	TH1F**hRatio = new TH1F*[33];
	for(int i=0; i<33;i++){
		hs[i] = new THStack(Form("hs%i",i),"");
		pad[i] = new TPad(Form("pad%i",i),"",0,0.30,1,1);
		padB[i] = new TPad(Form("padB%i",i),"",0,0,1,0.30);
		hRatio[i] = new TH1F(Form("hRatio%i",i),"Ratio",Bin[i],Min[i],Max[i]);
	}

	TH1F** t0_SigHist = new TH1F*[33];
	TH1F** t1_SigHist = new TH1F*[33];
	for(int i=0; i<33;i++){
		if (i%33==0)     {k++;}	// for line & Fill color
		t0_SigHist[i] = new TH1F(Form("t0_SigHist%i",i),"",Bin[i],Min[i],Max[i]);
		t0_SigHist[i]->SetMarkerColor(k);
		t0_SigHist[i]->SetLineWidth(k);
		t0_SigHist[i]->SetLineColor(k);
	}

	for(int i=0; i<33;i++){
		if (i%33==0)     {k++;}	// for line & Fill color
		t1_SigHist[i] = new TH1F(Form("t1_SigHist%i",i),"",Bin[i],Min[i],Max[i]);
		t1_SigHist[i]->SetMarkerColor(k);
		t1_SigHist[i]->SetLineWidth(k);
		t1_SigHist[i]->SetLineColor(k);
	}

	TH1F** t0_BkgHist = new TH1F*[66];
	TH1F** t1_BkgHist = new TH1F*[66];
	for(int i=0; i<33;i++){
		if (i%33==0)     {j=0;	//for reset bins
				k++;}	// for line & Fill color
		else j++;
		t0_BkgHist[i] = new TH1F(Form("t0_BkgHist%i",i),"",Bin[j],Min[j],Max[j]);
		t0_BkgHist[i]->SetLineColor(k);
		t0_BkgHist[i]->SetMarkerColor(k);
		t0_BkgHist[i]->SetFillColor(k);
	}

	for(int i=0; i<33;i++){
		if (i%33==0)     {j=0;	//for reset bins
				k++;}	// for line & Fill color
		else j++;
		t1_BkgHist[i] = new TH1F(Form("t1_BkgHist%i",i),"",Bin[j],Min[j],Max[j]);
		t1_BkgHist[i]->SetLineColor(k);
		t1_BkgHist[i]->SetMarkerColor(k);
		t1_BkgHist[i]->SetFillColor(k);
	}

	TH1F** DataHist = new TH1F*[33];
	for(int i=0; i<33;i++){
		DataHist[i] = new TH1F(Form("DataHist%i",i),"",Bin[i],Min[i],Max[i]);
		DataHist[i]->SetLineColor(1);
		DataHist[i]->SetMarkerColor(1);
		//DataHist[i]->Sumw2();
	}

	TChain* t0_mc_sig = new TChain("otree");
		t0_mc_sig->Add("/home/rksharma/TEMP/WWScattering/OutputData/WLWL_mu_FullData_1Dec.root");
		ClassReadTree mc_sig_0(t0_mc_sig);
		for(int iEv_0_mc_sig=0;iEv_0_mc_sig < t0_mc_sig->GetEntries();iEv_0_mc_sig++){
			t0_mc_sig->GetEntry(iEv_0_mc_sig);
			NumPV=mc_sig_0.nPV;
			binidx = h->FindBin(NumPV);
			Nvtx_weight = h->GetBinContent(binidx);
			if(Nvtx_weight ==0) Nvtx_weight = 1 ;
			t0_SigHist[0]->Fill(mc_sig_0.nPV);
			t0_SigHist[1]->Fill(mc_sig_0.l_pt);
			t0_SigHist[2]->Fill(mc_sig_0.l_eta);
			t0_SigHist[3]->Fill(mc_sig_0.l_phi);
			t0_SigHist[4]->Fill(mc_sig_0.l_e);
			t0_SigHist[5]->Fill(mc_sig_0.pfMET);
			t0_SigHist[6]->Fill(mc_sig_0.pfMET_Phi);
			t0_SigHist[7]->Fill(mc_sig_0.Met_pt);
			t0_SigHist[8]->Fill(mc_sig_0.vbf_AK4_j1_pt);
			t0_SigHist[9]->Fill(mc_sig_0.vbf_AK4_j1_eta);
			t0_SigHist[10]->Fill(mc_sig_0.vbf_AK4_j1_phi);
			t0_SigHist[11]->Fill(mc_sig_0.vbf_AK4_j1_e);
			t0_SigHist[12]->Fill(mc_sig_0.vbf_AK4_j2_pt);
			t0_SigHist[13]->Fill(mc_sig_0.vbf_AK4_j2_eta);
			t0_SigHist[14]->Fill(mc_sig_0.vbf_AK4_j2_phi);
			t0_SigHist[15]->Fill(mc_sig_0.vbf_AK4_j2_e);
			t0_SigHist[16]->Fill(mc_sig_0.vbf_AK4_jj_pt);
			t0_SigHist[17]->Fill(mc_sig_0.vbf_AK4_jj_eta);
			t0_SigHist[18]->Fill(mc_sig_0.vbf_AK4_jj_phi);
			t0_SigHist[19]->Fill(mc_sig_0.vbf_AK4_jj_m);
			t0_SigHist[20]->Fill(mc_sig_0.Wjets_AK4_j1_pt);
			t0_SigHist[21]->Fill(mc_sig_0.Wjets_AK4_j1_eta);
			t0_SigHist[22]->Fill(mc_sig_0.Wjets_AK4_j1_phi);
			t0_SigHist[23]->Fill(mc_sig_0.Wjets_AK4_j1_e);
			t0_SigHist[24]->Fill(mc_sig_0.Wjets_AK4_j2_pt);
			t0_SigHist[25]->Fill(mc_sig_0.Wjets_AK4_j2_eta);
			t0_SigHist[26]->Fill(mc_sig_0.Wjets_AK4_j2_phi);
			t0_SigHist[27]->Fill(mc_sig_0.Wjets_AK4_j2_e);
			t0_SigHist[28]->Fill(mc_sig_0.Wjets_AK4_jj_pt);
			t0_SigHist[29]->Fill(mc_sig_0.Wjets_AK4_jj_eta);
			t0_SigHist[30]->Fill(mc_sig_0.Wjets_AK4_jj_phi);
			t0_SigHist[31]->Fill(mc_sig_0.Wjets_AK4_jj_e);
			t0_SigHist[32]->Fill(mc_sig_0.Wjets_AK4_jj_m);
		}


	TChain* t1_mc_sig = new TChain("otree");
		t1_mc_sig->Add("/home/rksharma/TEMP/WWScattering/OutputData/WTWT_Mu_FullData_1Dec.root");
		ClassReadTree mc_sig_1(t1_mc_sig);
		for(int iEv_1_mc_sig=0;iEv_1_mc_sig < t1_mc_sig->GetEntries();iEv_1_mc_sig++){
			t1_mc_sig->GetEntry(iEv_1_mc_sig);
			NumPV=mc_sig_1.nPV;
			binidx = h->FindBin(NumPV);
			Nvtx_weight = h->GetBinContent(binidx);
			if(Nvtx_weight ==0) Nvtx_weight = 1 ;
			t1_SigHist[0]->Fill(mc_sig_1.nPV);
			t1_SigHist[1]->Fill(mc_sig_1.l_pt);
			t1_SigHist[2]->Fill(mc_sig_1.l_eta);
			t1_SigHist[3]->Fill(mc_sig_1.l_phi);
			t1_SigHist[4]->Fill(mc_sig_1.l_e);
			t1_SigHist[5]->Fill(mc_sig_1.pfMET);
			t1_SigHist[6]->Fill(mc_sig_1.pfMET_Phi);
			t1_SigHist[7]->Fill(mc_sig_1.Met_pt);
			t1_SigHist[8]->Fill(mc_sig_1.vbf_AK4_j1_pt);
			t1_SigHist[9]->Fill(mc_sig_1.vbf_AK4_j1_eta);
			t1_SigHist[10]->Fill(mc_sig_1.vbf_AK4_j1_phi);
			t1_SigHist[11]->Fill(mc_sig_1.vbf_AK4_j1_e);
			t1_SigHist[12]->Fill(mc_sig_1.vbf_AK4_j2_pt);
			t1_SigHist[13]->Fill(mc_sig_1.vbf_AK4_j2_eta);
			t1_SigHist[14]->Fill(mc_sig_1.vbf_AK4_j2_phi);
			t1_SigHist[15]->Fill(mc_sig_1.vbf_AK4_j2_e);
			t1_SigHist[16]->Fill(mc_sig_1.vbf_AK4_jj_pt);
			t1_SigHist[17]->Fill(mc_sig_1.vbf_AK4_jj_eta);
			t1_SigHist[18]->Fill(mc_sig_1.vbf_AK4_jj_phi);
			t1_SigHist[19]->Fill(mc_sig_1.vbf_AK4_jj_m);
			t1_SigHist[20]->Fill(mc_sig_1.Wjets_AK4_j1_pt);
			t1_SigHist[21]->Fill(mc_sig_1.Wjets_AK4_j1_eta);
			t1_SigHist[22]->Fill(mc_sig_1.Wjets_AK4_j1_phi);
			t1_SigHist[23]->Fill(mc_sig_1.Wjets_AK4_j1_e);
			t1_SigHist[24]->Fill(mc_sig_1.Wjets_AK4_j2_pt);
			t1_SigHist[25]->Fill(mc_sig_1.Wjets_AK4_j2_eta);
			t1_SigHist[26]->Fill(mc_sig_1.Wjets_AK4_j2_phi);
			t1_SigHist[27]->Fill(mc_sig_1.Wjets_AK4_j2_e);
			t1_SigHist[28]->Fill(mc_sig_1.Wjets_AK4_jj_pt);
			t1_SigHist[29]->Fill(mc_sig_1.Wjets_AK4_jj_eta);
			t1_SigHist[30]->Fill(mc_sig_1.Wjets_AK4_jj_phi);
			t1_SigHist[31]->Fill(mc_sig_1.Wjets_AK4_jj_e);
			t1_SigHist[32]->Fill(mc_sig_1.Wjets_AK4_jj_m);
		}


	TChain* t0_mc_bkg = new TChain("otree");
		t0_mc_bkg->Add("/home/rksharma/TEMP/WWScattering/OutputData/WJets_FullData_1Dec.root");
		ClassReadTree mc_bkg_0(t0_mc_bkg);
		for(int iEv_0_mc_bkg=0;iEv_0_mc_bkg < t0_mc_bkg->GetEntries();iEv_0_mc_bkg++){
			t0_mc_bkg->GetEntry(iEv_0_mc_bkg);
			NumPV=mc_bkg_0.nPV;
			binidx = h->FindBin(NumPV);
			Nvtx_weight = h->GetBinContent(binidx);
			if(Nvtx_weight ==0) Nvtx_weight = 1 ;
			t0_BkgHist[0]->Fill(mc_bkg_0.nPV,Nvtx_weight);
			t0_BkgHist[1]->Fill(mc_bkg_0.l_pt,Nvtx_weight);
			t0_BkgHist[2]->Fill(mc_bkg_0.l_eta,Nvtx_weight);
			t0_BkgHist[3]->Fill(mc_bkg_0.l_phi,Nvtx_weight);
			t0_BkgHist[4]->Fill(mc_bkg_0.l_e,Nvtx_weight);
			t0_BkgHist[5]->Fill(mc_bkg_0.pfMET,Nvtx_weight);
			t0_BkgHist[6]->Fill(mc_bkg_0.pfMET_Phi,Nvtx_weight);
			t0_BkgHist[7]->Fill(mc_bkg_0.Met_pt,Nvtx_weight);
			t0_BkgHist[8]->Fill(mc_bkg_0.vbf_AK4_j1_pt,Nvtx_weight);
			t0_BkgHist[9]->Fill(mc_bkg_0.vbf_AK4_j1_eta,Nvtx_weight);
			t0_BkgHist[10]->Fill(mc_bkg_0.vbf_AK4_j1_phi,Nvtx_weight);
			t0_BkgHist[11]->Fill(mc_bkg_0.vbf_AK4_j1_e,Nvtx_weight);
			t0_BkgHist[12]->Fill(mc_bkg_0.vbf_AK4_j2_pt,Nvtx_weight);
			t0_BkgHist[13]->Fill(mc_bkg_0.vbf_AK4_j2_eta,Nvtx_weight);
			t0_BkgHist[14]->Fill(mc_bkg_0.vbf_AK4_j2_phi,Nvtx_weight);
			t0_BkgHist[15]->Fill(mc_bkg_0.vbf_AK4_j2_e,Nvtx_weight);
			t0_BkgHist[16]->Fill(mc_bkg_0.vbf_AK4_jj_pt,Nvtx_weight);
			t0_BkgHist[17]->Fill(mc_bkg_0.vbf_AK4_jj_eta,Nvtx_weight);
			t0_BkgHist[18]->Fill(mc_bkg_0.vbf_AK4_jj_phi,Nvtx_weight);
			t0_BkgHist[19]->Fill(mc_bkg_0.vbf_AK4_jj_m,Nvtx_weight);
			t0_BkgHist[20]->Fill(mc_bkg_0.Wjets_AK4_j1_pt,Nvtx_weight);
			t0_BkgHist[21]->Fill(mc_bkg_0.Wjets_AK4_j1_eta,Nvtx_weight);
			t0_BkgHist[22]->Fill(mc_bkg_0.Wjets_AK4_j1_phi,Nvtx_weight);
			t0_BkgHist[23]->Fill(mc_bkg_0.Wjets_AK4_j1_e,Nvtx_weight);
			t0_BkgHist[24]->Fill(mc_bkg_0.Wjets_AK4_j2_pt,Nvtx_weight);
			t0_BkgHist[25]->Fill(mc_bkg_0.Wjets_AK4_j2_eta,Nvtx_weight);
			t0_BkgHist[26]->Fill(mc_bkg_0.Wjets_AK4_j2_phi,Nvtx_weight);
			t0_BkgHist[27]->Fill(mc_bkg_0.Wjets_AK4_j2_e,Nvtx_weight);
			t0_BkgHist[28]->Fill(mc_bkg_0.Wjets_AK4_jj_pt,Nvtx_weight);
			t0_BkgHist[29]->Fill(mc_bkg_0.Wjets_AK4_jj_eta,Nvtx_weight);
			t0_BkgHist[30]->Fill(mc_bkg_0.Wjets_AK4_jj_phi,Nvtx_weight);
			t0_BkgHist[31]->Fill(mc_bkg_0.Wjets_AK4_jj_e,Nvtx_weight);
			t0_BkgHist[32]->Fill(mc_bkg_0.Wjets_AK4_jj_m,Nvtx_weight);
		}


	TChain* t1_mc_bkg = new TChain("otree");
		t1_mc_bkg->Add("/home/rksharma/TEMP/WWScattering/OutputData/TTbar_powheg_FullData_mu_1Dec.root");
		ClassReadTree mc_bkg_1(t1_mc_bkg);
		for(int iEv_1_mc_bkg=0;iEv_1_mc_bkg < t1_mc_bkg->GetEntries();iEv_1_mc_bkg++){
			t1_mc_bkg->GetEntry(iEv_1_mc_bkg);
			NumPV=mc_bkg_1.nPV;
			binidx = h->FindBin(NumPV);
			Nvtx_weight = h->GetBinContent(binidx);
			if(Nvtx_weight ==0) Nvtx_weight = 1 ;
			t1_BkgHist[0]->Fill(mc_bkg_1.nPV,Nvtx_weight);
			t1_BkgHist[1]->Fill(mc_bkg_1.l_pt,Nvtx_weight);
			t1_BkgHist[2]->Fill(mc_bkg_1.l_eta,Nvtx_weight);
			t1_BkgHist[3]->Fill(mc_bkg_1.l_phi,Nvtx_weight);
			t1_BkgHist[4]->Fill(mc_bkg_1.l_e,Nvtx_weight);
			t1_BkgHist[5]->Fill(mc_bkg_1.pfMET,Nvtx_weight);
			t1_BkgHist[6]->Fill(mc_bkg_1.pfMET_Phi,Nvtx_weight);
			t1_BkgHist[7]->Fill(mc_bkg_1.Met_pt,Nvtx_weight);
			t1_BkgHist[8]->Fill(mc_bkg_1.vbf_AK4_j1_pt,Nvtx_weight);
			t1_BkgHist[9]->Fill(mc_bkg_1.vbf_AK4_j1_eta,Nvtx_weight);
			t1_BkgHist[10]->Fill(mc_bkg_1.vbf_AK4_j1_phi,Nvtx_weight);
			t1_BkgHist[11]->Fill(mc_bkg_1.vbf_AK4_j1_e,Nvtx_weight);
			t1_BkgHist[12]->Fill(mc_bkg_1.vbf_AK4_j2_pt,Nvtx_weight);
			t1_BkgHist[13]->Fill(mc_bkg_1.vbf_AK4_j2_eta,Nvtx_weight);
			t1_BkgHist[14]->Fill(mc_bkg_1.vbf_AK4_j2_phi,Nvtx_weight);
			t1_BkgHist[15]->Fill(mc_bkg_1.vbf_AK4_j2_e,Nvtx_weight);
			t1_BkgHist[16]->Fill(mc_bkg_1.vbf_AK4_jj_pt,Nvtx_weight);
			t1_BkgHist[17]->Fill(mc_bkg_1.vbf_AK4_jj_eta,Nvtx_weight);
			t1_BkgHist[18]->Fill(mc_bkg_1.vbf_AK4_jj_phi,Nvtx_weight);
			t1_BkgHist[19]->Fill(mc_bkg_1.vbf_AK4_jj_m,Nvtx_weight);
			t1_BkgHist[20]->Fill(mc_bkg_1.Wjets_AK4_j1_pt,Nvtx_weight);
			t1_BkgHist[21]->Fill(mc_bkg_1.Wjets_AK4_j1_eta,Nvtx_weight);
			t1_BkgHist[22]->Fill(mc_bkg_1.Wjets_AK4_j1_phi,Nvtx_weight);
			t1_BkgHist[23]->Fill(mc_bkg_1.Wjets_AK4_j1_e,Nvtx_weight);
			t1_BkgHist[24]->Fill(mc_bkg_1.Wjets_AK4_j2_pt,Nvtx_weight);
			t1_BkgHist[25]->Fill(mc_bkg_1.Wjets_AK4_j2_eta,Nvtx_weight);
			t1_BkgHist[26]->Fill(mc_bkg_1.Wjets_AK4_j2_phi,Nvtx_weight);
			t1_BkgHist[27]->Fill(mc_bkg_1.Wjets_AK4_j2_e,Nvtx_weight);
			t1_BkgHist[28]->Fill(mc_bkg_1.Wjets_AK4_jj_pt,Nvtx_weight);
			t1_BkgHist[29]->Fill(mc_bkg_1.Wjets_AK4_jj_eta,Nvtx_weight);
			t1_BkgHist[30]->Fill(mc_bkg_1.Wjets_AK4_jj_phi,Nvtx_weight);
			t1_BkgHist[31]->Fill(mc_bkg_1.Wjets_AK4_jj_e,Nvtx_weight);
			t1_BkgHist[32]->Fill(mc_bkg_1.Wjets_AK4_jj_m,Nvtx_weight);
		}


	TChain* t0_data = new TChain("otree");
		t0_data->Add("/home/rksharma/TEMP/WWScattering/OutputData/data_mu_prompt_25ns_runD.root");
		ClassReadTree mc_data_0(t0_data);
		for(int iEv_0_data=0;iEv_0_data < t0_data->GetEntries();iEv_0_data++){
			t0_data->GetEntry(iEv_0_data);
			DataHist[0]->Fill(mc_data_0.nPV);
			DataHist[1]->Fill(mc_data_0.l_pt);
			DataHist[2]->Fill(mc_data_0.l_eta);
			DataHist[3]->Fill(mc_data_0.l_phi);
			DataHist[4]->Fill(mc_data_0.l_e);
			DataHist[5]->Fill(mc_data_0.pfMET);
			DataHist[6]->Fill(mc_data_0.pfMET_Phi);
			DataHist[7]->Fill(mc_data_0.Met_pt);
			DataHist[8]->Fill(mc_data_0.vbf_AK4_j1_pt);
			DataHist[9]->Fill(mc_data_0.vbf_AK4_j1_eta);
			DataHist[10]->Fill(mc_data_0.vbf_AK4_j1_phi);
			DataHist[11]->Fill(mc_data_0.vbf_AK4_j1_e);
			DataHist[12]->Fill(mc_data_0.vbf_AK4_j2_pt);
			DataHist[13]->Fill(mc_data_0.vbf_AK4_j2_eta);
			DataHist[14]->Fill(mc_data_0.vbf_AK4_j2_phi);
			DataHist[15]->Fill(mc_data_0.vbf_AK4_j2_e);
			DataHist[16]->Fill(mc_data_0.vbf_AK4_jj_pt);
			DataHist[17]->Fill(mc_data_0.vbf_AK4_jj_eta);
			DataHist[18]->Fill(mc_data_0.vbf_AK4_jj_phi);
			DataHist[19]->Fill(mc_data_0.vbf_AK4_jj_m);
			DataHist[20]->Fill(mc_data_0.Wjets_AK4_j1_pt);
			DataHist[21]->Fill(mc_data_0.Wjets_AK4_j1_eta);
			DataHist[22]->Fill(mc_data_0.Wjets_AK4_j1_phi);
			DataHist[23]->Fill(mc_data_0.Wjets_AK4_j1_e);
			DataHist[24]->Fill(mc_data_0.Wjets_AK4_j2_pt);
			DataHist[25]->Fill(mc_data_0.Wjets_AK4_j2_eta);
			DataHist[26]->Fill(mc_data_0.Wjets_AK4_j2_phi);
			DataHist[27]->Fill(mc_data_0.Wjets_AK4_j2_e);
			DataHist[28]->Fill(mc_data_0.Wjets_AK4_jj_pt);
			DataHist[29]->Fill(mc_data_0.Wjets_AK4_jj_eta);
			DataHist[30]->Fill(mc_data_0.Wjets_AK4_jj_phi);
			DataHist[31]->Fill(mc_data_0.Wjets_AK4_jj_e);
			DataHist[32]->Fill(mc_data_0.Wjets_AK4_jj_m);
		}


	TLegend *leg = new TLegend(0.70,0.65,0.89,0.89,NULL,"brNDC");

double yMax=0.;
double HistMax=0.0;
c1->cd();

pad[0]->SetBottomMargin(0.05287462);
pad[0]->SetLogy(1);
pad[0]->Draw();
pad[0]->cd();

	t0_SigHist[0]->Scale(0.001730);
	HistMax = t0_SigHist[0]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_SigHist[0],"Signal*10","l");
	yMax=HistMax;

	t1_SigHist[0]->Scale(0.001870);
	HistMax = t1_SigHist[0]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_SigHist[0],"WTWT*10","l");
	yMax=HistMax;

	t0_BkgHist[0]->Scale(5.340000);
	HistMax = t0_BkgHist[0]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_BkgHist[0],"WJets","f");
	yMax=HistMax;

	t1_BkgHist[0]->Scale(0.087600);
	HistMax = t1_BkgHist[0]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_BkgHist[0],"TTbar","f");
	yMax=HistMax;

	DataHist[0]->Sumw2();
	HistMax = DataHist[0]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(DataHist[0],"Data","pe");
	yMax=HistMax;

	hs[0]->Add(t0_BkgHist[0],"hist");
	hs[0]->Add(t1_BkgHist[0],"hist");
	hs[0]->Draw();
	DataHist[0]->Draw("same");
	t0_SigHist[0]->Draw("same");
	t1_SigHist[0]->Draw("same");
	leg->Draw("same");
TH1F *h2 = (TH1F*)DataHist[0]->Clone();
hRatio[0]->Add(t0_BkgHist[0]);
hRatio[0]->Add(t1_BkgHist[0]);


c1->cd();
padB[0]->SetGridy(1);
padB[0]->SetTopMargin(0.0);
padB[0]->SetBottomMargin(0.30);
padB[0]->Draw();
padB[0]->cd();

float yscale = (1.0-0.2)/(0.18-0);
h2->Divide(hRatio[0]);
cout<<"Total Number of Events in Data = "<<DataHist[0]->Integral()<<endl;
cout<<"Total Number of Events in MC   = "<<hRatio[0]->Integral()<<endl;
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
h2->Draw("");
	c1->SaveAs("nPV.pdf");
	c1->SaveAs("nPV.png");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[1]->SetBottomMargin(0.05287462);
pad[1]->SetLogy(1);
pad[1]->Draw();
pad[1]->cd();

	t0_SigHist[1]->Scale(0.001730);
	HistMax = t0_SigHist[1]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_SigHist[1],"Signal*10","l");
	yMax=HistMax;

	t1_SigHist[1]->Scale(0.001870);
	HistMax = t1_SigHist[1]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_SigHist[1],"WTWT*10","l");
	yMax=HistMax;

	t0_BkgHist[1]->Scale(5.340000);
	HistMax = t0_BkgHist[1]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_BkgHist[1],"WJets","f");
	yMax=HistMax;

	t1_BkgHist[1]->Scale(0.087600);
	HistMax = t1_BkgHist[1]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_BkgHist[1],"TTbar","f");
	yMax=HistMax;

	DataHist[1]->Sumw2();
	HistMax = DataHist[1]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(DataHist[1],"Data","pe");
	yMax=HistMax;

	hs[1]->Add(t0_BkgHist[1],"hist");
	hs[1]->Add(t1_BkgHist[1],"hist");
	hs[1]->Draw();
	DataHist[1]->Draw("same");
	t0_SigHist[1]->Draw("same");
	t1_SigHist[1]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[1]->Clone();
hRatio[1]->Add(t0_BkgHist[1]);
hRatio[1]->Add(t1_BkgHist[1]);


c1->cd();
padB[1]->SetGridy(1);
padB[1]->SetTopMargin(0.0);
padB[1]->SetBottomMargin(0.30);
padB[1]->Draw();
padB[1]->cd();

yscale = (1.0-0.2)/(0.18-0);
h2->Divide(hRatio[1]);
cout<<"Total Number of Events in Data = "<<DataHist[1]->Integral()<<endl;
cout<<"Total Number of Events in MC   = "<<hRatio[1]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("l_pt");
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
h2->Draw("");
	c1->SaveAs("l_pt.pdf");
	c1->SaveAs("l_pt.png");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[2]->SetBottomMargin(0.05287462);
pad[2]->SetLogy(1);
pad[2]->Draw();
pad[2]->cd();

	t0_SigHist[2]->Scale(0.001730);
	HistMax = t0_SigHist[2]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_SigHist[2],"Signal*10","l");
	yMax=HistMax;

	t1_SigHist[2]->Scale(0.001870);
	HistMax = t1_SigHist[2]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_SigHist[2],"WTWT*10","l");
	yMax=HistMax;

	t0_BkgHist[2]->Scale(5.340000);
	HistMax = t0_BkgHist[2]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_BkgHist[2],"WJets","f");
	yMax=HistMax;

	t1_BkgHist[2]->Scale(0.087600);
	HistMax = t1_BkgHist[2]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_BkgHist[2],"TTbar","f");
	yMax=HistMax;

	DataHist[2]->Sumw2();
	HistMax = DataHist[2]->GetMaximum()*1.15;
	t0_SigHist[2]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(DataHist[2],"Data","pe");
	yMax=HistMax;

	hs[2]->Add(t0_BkgHist[2],"hist");
	hs[2]->Add(t1_BkgHist[2],"hist");
	hs[2]->Draw();
	DataHist[2]->Draw("same");
	t0_SigHist[2]->Draw("same");
	t1_SigHist[2]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[2]->Clone();
hRatio[2]->Add(t0_BkgHist[2]);
hRatio[2]->Add(t1_BkgHist[2]);


c1->cd();
padB[2]->SetGridy(1);
padB[2]->SetTopMargin(0.0);
padB[2]->SetBottomMargin(0.30);
padB[2]->Draw();
padB[2]->cd();

yscale = (1.0-0.2)/(0.18-0);
h2->Divide(hRatio[2]);
cout<<"Total Number of Events in Data = "<<DataHist[2]->Integral()<<endl;
cout<<"Total Number of Events in MC   = "<<hRatio[2]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("l_eta");
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
h2->Draw("");
	c1->SaveAs("l_eta.pdf");
	c1->SaveAs("l_eta.png");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[3]->SetBottomMargin(0.05287462);
pad[3]->SetLogy(1);
pad[3]->Draw();
pad[3]->cd();

	t0_SigHist[3]->Scale(0.001730);
	HistMax = t0_SigHist[3]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_SigHist[3],"Signal*10","l");
	yMax=HistMax;

	t1_SigHist[3]->Scale(0.001870);
	HistMax = t1_SigHist[3]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_SigHist[3],"WTWT*10","l");
	yMax=HistMax;

	t0_BkgHist[3]->Scale(5.340000);
	HistMax = t0_BkgHist[3]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_BkgHist[3],"WJets","f");
	yMax=HistMax;

	t1_BkgHist[3]->Scale(0.087600);
	HistMax = t1_BkgHist[3]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_BkgHist[3],"TTbar","f");
	yMax=HistMax;

	DataHist[3]->Sumw2();
	HistMax = DataHist[3]->GetMaximum()*1.15;
	t0_SigHist[3]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(DataHist[3],"Data","pe");
	yMax=HistMax;

	hs[3]->Add(t0_BkgHist[3],"hist");
	hs[3]->Add(t1_BkgHist[3],"hist");
	hs[3]->Draw();
	DataHist[3]->Draw("same");
	t0_SigHist[3]->Draw("same");
	t1_SigHist[3]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[3]->Clone();
hRatio[3]->Add(t0_BkgHist[3]);
hRatio[3]->Add(t1_BkgHist[3]);


c1->cd();
padB[3]->SetGridy(1);
padB[3]->SetTopMargin(0.0);
padB[3]->SetBottomMargin(0.30);
padB[3]->Draw();
padB[3]->cd();

yscale = (1.0-0.2)/(0.18-0);
h2->Divide(hRatio[3]);
cout<<"Total Number of Events in Data = "<<DataHist[3]->Integral()<<endl;
cout<<"Total Number of Events in MC   = "<<hRatio[3]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("l_phi");
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
h2->Draw("");
	c1->SaveAs("l_phi.pdf");
	c1->SaveAs("l_phi.png");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[4]->SetBottomMargin(0.05287462);
pad[4]->SetLogy(1);
pad[4]->Draw();
pad[4]->cd();

	t0_SigHist[4]->Scale(0.001730);
	HistMax = t0_SigHist[4]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_SigHist[4],"Signal*10","l");
	yMax=HistMax;

	t1_SigHist[4]->Scale(0.001870);
	HistMax = t1_SigHist[4]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_SigHist[4],"WTWT*10","l");
	yMax=HistMax;

	t0_BkgHist[4]->Scale(5.340000);
	HistMax = t0_BkgHist[4]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_BkgHist[4],"WJets","f");
	yMax=HistMax;

	t1_BkgHist[4]->Scale(0.087600);
	HistMax = t1_BkgHist[4]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_BkgHist[4],"TTbar","f");
	yMax=HistMax;

	DataHist[4]->Sumw2();
	HistMax = DataHist[4]->GetMaximum()*1.15;
	t0_SigHist[4]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(DataHist[4],"Data","pe");
	yMax=HistMax;

	hs[4]->Add(t0_BkgHist[4],"hist");
	hs[4]->Add(t1_BkgHist[4],"hist");
	hs[4]->Draw();
	DataHist[4]->Draw("same");
	t0_SigHist[4]->Draw("same");
	t1_SigHist[4]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[4]->Clone();
hRatio[4]->Add(t0_BkgHist[4]);
hRatio[4]->Add(t1_BkgHist[4]);


c1->cd();
padB[4]->SetGridy(1);
padB[4]->SetTopMargin(0.0);
padB[4]->SetBottomMargin(0.30);
padB[4]->Draw();
padB[4]->cd();

yscale = (1.0-0.2)/(0.18-0);
h2->Divide(hRatio[4]);
cout<<"Total Number of Events in Data = "<<DataHist[4]->Integral()<<endl;
cout<<"Total Number of Events in MC   = "<<hRatio[4]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("l_e");
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
h2->Draw("");
	c1->SaveAs("l_e.pdf");
	c1->SaveAs("l_e.png");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[5]->SetBottomMargin(0.05287462);
pad[5]->SetLogy(1);
pad[5]->Draw();
pad[5]->cd();

	t0_SigHist[5]->Scale(0.001730);
	HistMax = t0_SigHist[5]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_SigHist[5],"Signal*10","l");
	yMax=HistMax;

	t1_SigHist[5]->Scale(0.001870);
	HistMax = t1_SigHist[5]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_SigHist[5],"WTWT*10","l");
	yMax=HistMax;

	t0_BkgHist[5]->Scale(5.340000);
	HistMax = t0_BkgHist[5]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_BkgHist[5],"WJets","f");
	yMax=HistMax;

	t1_BkgHist[5]->Scale(0.087600);
	HistMax = t1_BkgHist[5]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_BkgHist[5],"TTbar","f");
	yMax=HistMax;

	DataHist[5]->Sumw2();
	HistMax = DataHist[5]->GetMaximum()*1.15;
	t0_SigHist[5]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(DataHist[5],"Data","pe");
	yMax=HistMax;

	hs[5]->Add(t0_BkgHist[5],"hist");
	hs[5]->Add(t1_BkgHist[5],"hist");
	hs[5]->Draw();
	DataHist[5]->Draw("same");
	t0_SigHist[5]->Draw("same");
	t1_SigHist[5]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[5]->Clone();
hRatio[5]->Add(t0_BkgHist[5]);
hRatio[5]->Add(t1_BkgHist[5]);


c1->cd();
padB[5]->SetGridy(1);
padB[5]->SetTopMargin(0.0);
padB[5]->SetBottomMargin(0.30);
padB[5]->Draw();
padB[5]->cd();

yscale = (1.0-0.2)/(0.18-0);
h2->Divide(hRatio[5]);
cout<<"Total Number of Events in Data = "<<DataHist[5]->Integral()<<endl;
cout<<"Total Number of Events in MC   = "<<hRatio[5]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("pfMET");
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
h2->Draw("");
	c1->SaveAs("pfMET.pdf");
	c1->SaveAs("pfMET.png");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[6]->SetBottomMargin(0.05287462);
pad[6]->SetLogy(1);
pad[6]->Draw();
pad[6]->cd();

	t0_SigHist[6]->Scale(0.001730);
	HistMax = t0_SigHist[6]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_SigHist[6],"Signal*10","l");
	yMax=HistMax;

	t1_SigHist[6]->Scale(0.001870);
	HistMax = t1_SigHist[6]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_SigHist[6],"WTWT*10","l");
	yMax=HistMax;

	t0_BkgHist[6]->Scale(5.340000);
	HistMax = t0_BkgHist[6]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_BkgHist[6],"WJets","f");
	yMax=HistMax;

	t1_BkgHist[6]->Scale(0.087600);
	HistMax = t1_BkgHist[6]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_BkgHist[6],"TTbar","f");
	yMax=HistMax;

	DataHist[6]->Sumw2();
	HistMax = DataHist[6]->GetMaximum()*1.15;
	t0_SigHist[6]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(DataHist[6],"Data","pe");
	yMax=HistMax;

	hs[6]->Add(t0_BkgHist[6],"hist");
	hs[6]->Add(t1_BkgHist[6],"hist");
	hs[6]->Draw();
	DataHist[6]->Draw("same");
	t0_SigHist[6]->Draw("same");
	t1_SigHist[6]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[6]->Clone();
hRatio[6]->Add(t0_BkgHist[6]);
hRatio[6]->Add(t1_BkgHist[6]);


c1->cd();
padB[6]->SetGridy(1);
padB[6]->SetTopMargin(0.0);
padB[6]->SetBottomMargin(0.30);
padB[6]->Draw();
padB[6]->cd();

yscale = (1.0-0.2)/(0.18-0);
h2->Divide(hRatio[6]);
cout<<"Total Number of Events in Data = "<<DataHist[6]->Integral()<<endl;
cout<<"Total Number of Events in MC   = "<<hRatio[6]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("pfMET_Phi");
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
h2->Draw("");
	c1->SaveAs("pfMET_Phi.pdf");
	c1->SaveAs("pfMET_Phi.png");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[7]->SetBottomMargin(0.05287462);
pad[7]->SetLogy(1);
pad[7]->Draw();
pad[7]->cd();

	t0_SigHist[7]->Scale(0.001730);
	HistMax = t0_SigHist[7]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_SigHist[7],"Signal*10","l");
	yMax=HistMax;

	t1_SigHist[7]->Scale(0.001870);
	HistMax = t1_SigHist[7]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_SigHist[7],"WTWT*10","l");
	yMax=HistMax;

	t0_BkgHist[7]->Scale(5.340000);
	HistMax = t0_BkgHist[7]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_BkgHist[7],"WJets","f");
	yMax=HistMax;

	t1_BkgHist[7]->Scale(0.087600);
	HistMax = t1_BkgHist[7]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_BkgHist[7],"TTbar","f");
	yMax=HistMax;

	DataHist[7]->Sumw2();
	HistMax = DataHist[7]->GetMaximum()*1.15;
	t0_SigHist[7]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(DataHist[7],"Data","pe");
	yMax=HistMax;

	hs[7]->Add(t0_BkgHist[7],"hist");
	hs[7]->Add(t1_BkgHist[7],"hist");
	hs[7]->Draw();
	DataHist[7]->Draw("same");
	t0_SigHist[7]->Draw("same");
	t1_SigHist[7]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[7]->Clone();
hRatio[7]->Add(t0_BkgHist[7]);
hRatio[7]->Add(t1_BkgHist[7]);


c1->cd();
padB[7]->SetGridy(1);
padB[7]->SetTopMargin(0.0);
padB[7]->SetBottomMargin(0.30);
padB[7]->Draw();
padB[7]->cd();

yscale = (1.0-0.2)/(0.18-0);
h2->Divide(hRatio[7]);
cout<<"Total Number of Events in Data = "<<DataHist[7]->Integral()<<endl;
cout<<"Total Number of Events in MC   = "<<hRatio[7]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("Met_pt");
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
h2->Draw("");
	c1->SaveAs("Met_pt.pdf");
	c1->SaveAs("Met_pt.png");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[8]->SetBottomMargin(0.05287462);
pad[8]->SetLogy(1);
pad[8]->Draw();
pad[8]->cd();

	t0_SigHist[8]->Scale(0.001730);
	HistMax = t0_SigHist[8]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_SigHist[8],"Signal*10","l");
	yMax=HistMax;

	t1_SigHist[8]->Scale(0.001870);
	HistMax = t1_SigHist[8]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_SigHist[8],"WTWT*10","l");
	yMax=HistMax;

	t0_BkgHist[8]->Scale(5.340000);
	HistMax = t0_BkgHist[8]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_BkgHist[8],"WJets","f");
	yMax=HistMax;

	t1_BkgHist[8]->Scale(0.087600);
	HistMax = t1_BkgHist[8]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_BkgHist[8],"TTbar","f");
	yMax=HistMax;

	DataHist[8]->Sumw2();
	HistMax = DataHist[8]->GetMaximum()*1.15;
	t0_SigHist[8]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(DataHist[8],"Data","pe");
	yMax=HistMax;

	hs[8]->Add(t0_BkgHist[8],"hist");
	hs[8]->Add(t1_BkgHist[8],"hist");
	hs[8]->Draw();
	DataHist[8]->Draw("same");
	t0_SigHist[8]->Draw("same");
	t1_SigHist[8]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[8]->Clone();
hRatio[8]->Add(t0_BkgHist[8]);
hRatio[8]->Add(t1_BkgHist[8]);


c1->cd();
padB[8]->SetGridy(1);
padB[8]->SetTopMargin(0.0);
padB[8]->SetBottomMargin(0.30);
padB[8]->Draw();
padB[8]->cd();

yscale = (1.0-0.2)/(0.18-0);
h2->Divide(hRatio[8]);
cout<<"Total Number of Events in Data = "<<DataHist[8]->Integral()<<endl;
cout<<"Total Number of Events in MC   = "<<hRatio[8]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("vbf_AK4_j1_pt");
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
h2->Draw("");
	c1->SaveAs("vbf_AK4_j1_pt.pdf");
	c1->SaveAs("vbf_AK4_j1_pt.png");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[9]->SetBottomMargin(0.05287462);
pad[9]->SetLogy(1);
pad[9]->Draw();
pad[9]->cd();

	t0_SigHist[9]->Scale(0.001730);
	HistMax = t0_SigHist[9]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_SigHist[9],"Signal*10","l");
	yMax=HistMax;

	t1_SigHist[9]->Scale(0.001870);
	HistMax = t1_SigHist[9]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_SigHist[9],"WTWT*10","l");
	yMax=HistMax;

	t0_BkgHist[9]->Scale(5.340000);
	HistMax = t0_BkgHist[9]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_BkgHist[9],"WJets","f");
	yMax=HistMax;

	t1_BkgHist[9]->Scale(0.087600);
	HistMax = t1_BkgHist[9]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_BkgHist[9],"TTbar","f");
	yMax=HistMax;

	DataHist[9]->Sumw2();
	HistMax = DataHist[9]->GetMaximum()*1.15;
	t0_SigHist[9]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(DataHist[9],"Data","pe");
	yMax=HistMax;

	hs[9]->Add(t0_BkgHist[9],"hist");
	hs[9]->Add(t1_BkgHist[9],"hist");
	hs[9]->Draw();
	DataHist[9]->Draw("same");
	t0_SigHist[9]->Draw("same");
	t1_SigHist[9]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[9]->Clone();
hRatio[9]->Add(t0_BkgHist[9]);
hRatio[9]->Add(t1_BkgHist[9]);


c1->cd();
padB[9]->SetGridy(1);
padB[9]->SetTopMargin(0.0);
padB[9]->SetBottomMargin(0.30);
padB[9]->Draw();
padB[9]->cd();

yscale = (1.0-0.2)/(0.18-0);
h2->Divide(hRatio[9]);
cout<<"Total Number of Events in Data = "<<DataHist[9]->Integral()<<endl;
cout<<"Total Number of Events in MC   = "<<hRatio[9]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("vbf_AK4_j1_eta");
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
h2->Draw("");
	c1->SaveAs("vbf_AK4_j1_eta.pdf");
	c1->SaveAs("vbf_AK4_j1_eta.png");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[10]->SetBottomMargin(0.05287462);
pad[10]->SetLogy(1);
pad[10]->Draw();
pad[10]->cd();

	t0_SigHist[10]->Scale(0.001730);
	HistMax = t0_SigHist[10]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_SigHist[10],"Signal*10","l");
	yMax=HistMax;

	t1_SigHist[10]->Scale(0.001870);
	HistMax = t1_SigHist[10]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_SigHist[10],"WTWT*10","l");
	yMax=HistMax;

	t0_BkgHist[10]->Scale(5.340000);
	HistMax = t0_BkgHist[10]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_BkgHist[10],"WJets","f");
	yMax=HistMax;

	t1_BkgHist[10]->Scale(0.087600);
	HistMax = t1_BkgHist[10]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_BkgHist[10],"TTbar","f");
	yMax=HistMax;

	DataHist[10]->Sumw2();
	HistMax = DataHist[10]->GetMaximum()*1.15;
	t0_SigHist[10]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(DataHist[10],"Data","pe");
	yMax=HistMax;

	hs[10]->Add(t0_BkgHist[10],"hist");
	hs[10]->Add(t1_BkgHist[10],"hist");
	hs[10]->Draw();
	DataHist[10]->Draw("same");
	t0_SigHist[10]->Draw("same");
	t1_SigHist[10]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[10]->Clone();
hRatio[10]->Add(t0_BkgHist[10]);
hRatio[10]->Add(t1_BkgHist[10]);


c1->cd();
padB[10]->SetGridy(1);
padB[10]->SetTopMargin(0.0);
padB[10]->SetBottomMargin(0.30);
padB[10]->Draw();
padB[10]->cd();

yscale = (1.0-0.2)/(0.18-0);
h2->Divide(hRatio[10]);
cout<<"Total Number of Events in Data = "<<DataHist[10]->Integral()<<endl;
cout<<"Total Number of Events in MC   = "<<hRatio[10]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("vbf_AK4_j1_phi");
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
h2->Draw("");
	c1->SaveAs("vbf_AK4_j1_phi.pdf");
	c1->SaveAs("vbf_AK4_j1_phi.png");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[11]->SetBottomMargin(0.05287462);
pad[11]->SetLogy(1);
pad[11]->Draw();
pad[11]->cd();

	t0_SigHist[11]->Scale(0.001730);
	HistMax = t0_SigHist[11]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_SigHist[11],"Signal*10","l");
	yMax=HistMax;

	t1_SigHist[11]->Scale(0.001870);
	HistMax = t1_SigHist[11]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_SigHist[11],"WTWT*10","l");
	yMax=HistMax;

	t0_BkgHist[11]->Scale(5.340000);
	HistMax = t0_BkgHist[11]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_BkgHist[11],"WJets","f");
	yMax=HistMax;

	t1_BkgHist[11]->Scale(0.087600);
	HistMax = t1_BkgHist[11]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_BkgHist[11],"TTbar","f");
	yMax=HistMax;

	DataHist[11]->Sumw2();
	HistMax = DataHist[11]->GetMaximum()*1.15;
	t0_SigHist[11]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(DataHist[11],"Data","pe");
	yMax=HistMax;

	hs[11]->Add(t0_BkgHist[11],"hist");
	hs[11]->Add(t1_BkgHist[11],"hist");
	hs[11]->Draw();
	DataHist[11]->Draw("same");
	t0_SigHist[11]->Draw("same");
	t1_SigHist[11]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[11]->Clone();
hRatio[11]->Add(t0_BkgHist[11]);
hRatio[11]->Add(t1_BkgHist[11]);


c1->cd();
padB[11]->SetGridy(1);
padB[11]->SetTopMargin(0.0);
padB[11]->SetBottomMargin(0.30);
padB[11]->Draw();
padB[11]->cd();

yscale = (1.0-0.2)/(0.18-0);
h2->Divide(hRatio[11]);
cout<<"Total Number of Events in Data = "<<DataHist[11]->Integral()<<endl;
cout<<"Total Number of Events in MC   = "<<hRatio[11]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("vbf_AK4_j1_e");
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
h2->Draw("");
	c1->SaveAs("vbf_AK4_j1_e.pdf");
	c1->SaveAs("vbf_AK4_j1_e.png");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[12]->SetBottomMargin(0.05287462);
pad[12]->SetLogy(1);
pad[12]->Draw();
pad[12]->cd();

	t0_SigHist[12]->Scale(0.001730);
	HistMax = t0_SigHist[12]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_SigHist[12],"Signal*10","l");
	yMax=HistMax;

	t1_SigHist[12]->Scale(0.001870);
	HistMax = t1_SigHist[12]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_SigHist[12],"WTWT*10","l");
	yMax=HistMax;

	t0_BkgHist[12]->Scale(5.340000);
	HistMax = t0_BkgHist[12]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_BkgHist[12],"WJets","f");
	yMax=HistMax;

	t1_BkgHist[12]->Scale(0.087600);
	HistMax = t1_BkgHist[12]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_BkgHist[12],"TTbar","f");
	yMax=HistMax;

	DataHist[12]->Sumw2();
	HistMax = DataHist[12]->GetMaximum()*1.15;
	t0_SigHist[12]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(DataHist[12],"Data","pe");
	yMax=HistMax;

	hs[12]->Add(t0_BkgHist[12],"hist");
	hs[12]->Add(t1_BkgHist[12],"hist");
	hs[12]->Draw();
	DataHist[12]->Draw("same");
	t0_SigHist[12]->Draw("same");
	t1_SigHist[12]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[12]->Clone();
hRatio[12]->Add(t0_BkgHist[12]);
hRatio[12]->Add(t1_BkgHist[12]);


c1->cd();
padB[12]->SetGridy(1);
padB[12]->SetTopMargin(0.0);
padB[12]->SetBottomMargin(0.30);
padB[12]->Draw();
padB[12]->cd();

yscale = (1.0-0.2)/(0.18-0);
h2->Divide(hRatio[12]);
cout<<"Total Number of Events in Data = "<<DataHist[12]->Integral()<<endl;
cout<<"Total Number of Events in MC   = "<<hRatio[12]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("vbf_AK4_j2_pt");
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
h2->Draw("");
	c1->SaveAs("vbf_AK4_j2_pt.pdf");
	c1->SaveAs("vbf_AK4_j2_pt.png");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[13]->SetBottomMargin(0.05287462);
pad[13]->SetLogy(1);
pad[13]->Draw();
pad[13]->cd();

	t0_SigHist[13]->Scale(0.001730);
	HistMax = t0_SigHist[13]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_SigHist[13],"Signal*10","l");
	yMax=HistMax;

	t1_SigHist[13]->Scale(0.001870);
	HistMax = t1_SigHist[13]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_SigHist[13],"WTWT*10","l");
	yMax=HistMax;

	t0_BkgHist[13]->Scale(5.340000);
	HistMax = t0_BkgHist[13]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_BkgHist[13],"WJets","f");
	yMax=HistMax;

	t1_BkgHist[13]->Scale(0.087600);
	HistMax = t1_BkgHist[13]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_BkgHist[13],"TTbar","f");
	yMax=HistMax;

	DataHist[13]->Sumw2();
	HistMax = DataHist[13]->GetMaximum()*1.15;
	t0_SigHist[13]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(DataHist[13],"Data","pe");
	yMax=HistMax;

	hs[13]->Add(t0_BkgHist[13],"hist");
	hs[13]->Add(t1_BkgHist[13],"hist");
	hs[13]->Draw();
	DataHist[13]->Draw("same");
	t0_SigHist[13]->Draw("same");
	t1_SigHist[13]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[13]->Clone();
hRatio[13]->Add(t0_BkgHist[13]);
hRatio[13]->Add(t1_BkgHist[13]);


c1->cd();
padB[13]->SetGridy(1);
padB[13]->SetTopMargin(0.0);
padB[13]->SetBottomMargin(0.30);
padB[13]->Draw();
padB[13]->cd();

yscale = (1.0-0.2)/(0.18-0);
h2->Divide(hRatio[13]);
cout<<"Total Number of Events in Data = "<<DataHist[13]->Integral()<<endl;
cout<<"Total Number of Events in MC   = "<<hRatio[13]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("vbf_AK4_j2_eta");
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
h2->Draw("");
	c1->SaveAs("vbf_AK4_j2_eta.pdf");
	c1->SaveAs("vbf_AK4_j2_eta.png");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[14]->SetBottomMargin(0.05287462);
pad[14]->SetLogy(1);
pad[14]->Draw();
pad[14]->cd();

	t0_SigHist[14]->Scale(0.001730);
	HistMax = t0_SigHist[14]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_SigHist[14],"Signal*10","l");
	yMax=HistMax;

	t1_SigHist[14]->Scale(0.001870);
	HistMax = t1_SigHist[14]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_SigHist[14],"WTWT*10","l");
	yMax=HistMax;

	t0_BkgHist[14]->Scale(5.340000);
	HistMax = t0_BkgHist[14]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_BkgHist[14],"WJets","f");
	yMax=HistMax;

	t1_BkgHist[14]->Scale(0.087600);
	HistMax = t1_BkgHist[14]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_BkgHist[14],"TTbar","f");
	yMax=HistMax;

	DataHist[14]->Sumw2();
	HistMax = DataHist[14]->GetMaximum()*1.15;
	t0_SigHist[14]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(DataHist[14],"Data","pe");
	yMax=HistMax;

	hs[14]->Add(t0_BkgHist[14],"hist");
	hs[14]->Add(t1_BkgHist[14],"hist");
	hs[14]->Draw();
	DataHist[14]->Draw("same");
	t0_SigHist[14]->Draw("same");
	t1_SigHist[14]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[14]->Clone();
hRatio[14]->Add(t0_BkgHist[14]);
hRatio[14]->Add(t1_BkgHist[14]);


c1->cd();
padB[14]->SetGridy(1);
padB[14]->SetTopMargin(0.0);
padB[14]->SetBottomMargin(0.30);
padB[14]->Draw();
padB[14]->cd();

yscale = (1.0-0.2)/(0.18-0);
h2->Divide(hRatio[14]);
cout<<"Total Number of Events in Data = "<<DataHist[14]->Integral()<<endl;
cout<<"Total Number of Events in MC   = "<<hRatio[14]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("vbf_AK4_j2_phi");
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
h2->Draw("");
	c1->SaveAs("vbf_AK4_j2_phi.pdf");
	c1->SaveAs("vbf_AK4_j2_phi.png");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[15]->SetBottomMargin(0.05287462);
pad[15]->SetLogy(1);
pad[15]->Draw();
pad[15]->cd();

	t0_SigHist[15]->Scale(0.001730);
	HistMax = t0_SigHist[15]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_SigHist[15],"Signal*10","l");
	yMax=HistMax;

	t1_SigHist[15]->Scale(0.001870);
	HistMax = t1_SigHist[15]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_SigHist[15],"WTWT*10","l");
	yMax=HistMax;

	t0_BkgHist[15]->Scale(5.340000);
	HistMax = t0_BkgHist[15]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_BkgHist[15],"WJets","f");
	yMax=HistMax;

	t1_BkgHist[15]->Scale(0.087600);
	HistMax = t1_BkgHist[15]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_BkgHist[15],"TTbar","f");
	yMax=HistMax;

	DataHist[15]->Sumw2();
	HistMax = DataHist[15]->GetMaximum()*1.15;
	t0_SigHist[15]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(DataHist[15],"Data","pe");
	yMax=HistMax;

	hs[15]->Add(t0_BkgHist[15],"hist");
	hs[15]->Add(t1_BkgHist[15],"hist");
	hs[15]->Draw();
	DataHist[15]->Draw("same");
	t0_SigHist[15]->Draw("same");
	t1_SigHist[15]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[15]->Clone();
hRatio[15]->Add(t0_BkgHist[15]);
hRatio[15]->Add(t1_BkgHist[15]);


c1->cd();
padB[15]->SetGridy(1);
padB[15]->SetTopMargin(0.0);
padB[15]->SetBottomMargin(0.30);
padB[15]->Draw();
padB[15]->cd();

yscale = (1.0-0.2)/(0.18-0);
h2->Divide(hRatio[15]);
cout<<"Total Number of Events in Data = "<<DataHist[15]->Integral()<<endl;
cout<<"Total Number of Events in MC   = "<<hRatio[15]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("vbf_AK4_j2_e");
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
h2->Draw("");
	c1->SaveAs("vbf_AK4_j2_e.pdf");
	c1->SaveAs("vbf_AK4_j2_e.png");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[16]->SetBottomMargin(0.05287462);
pad[16]->SetLogy(1);
pad[16]->Draw();
pad[16]->cd();

	t0_SigHist[16]->Scale(0.001730);
	HistMax = t0_SigHist[16]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_SigHist[16],"Signal*10","l");
	yMax=HistMax;

	t1_SigHist[16]->Scale(0.001870);
	HistMax = t1_SigHist[16]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_SigHist[16],"WTWT*10","l");
	yMax=HistMax;

	t0_BkgHist[16]->Scale(5.340000);
	HistMax = t0_BkgHist[16]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_BkgHist[16],"WJets","f");
	yMax=HistMax;

	t1_BkgHist[16]->Scale(0.087600);
	HistMax = t1_BkgHist[16]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_BkgHist[16],"TTbar","f");
	yMax=HistMax;

	DataHist[16]->Sumw2();
	HistMax = DataHist[16]->GetMaximum()*1.15;
	t0_SigHist[16]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(DataHist[16],"Data","pe");
	yMax=HistMax;

	hs[16]->Add(t0_BkgHist[16],"hist");
	hs[16]->Add(t1_BkgHist[16],"hist");
	hs[16]->Draw();
	DataHist[16]->Draw("same");
	t0_SigHist[16]->Draw("same");
	t1_SigHist[16]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[16]->Clone();
hRatio[16]->Add(t0_BkgHist[16]);
hRatio[16]->Add(t1_BkgHist[16]);


c1->cd();
padB[16]->SetGridy(1);
padB[16]->SetTopMargin(0.0);
padB[16]->SetBottomMargin(0.30);
padB[16]->Draw();
padB[16]->cd();

yscale = (1.0-0.2)/(0.18-0);
h2->Divide(hRatio[16]);
cout<<"Total Number of Events in Data = "<<DataHist[16]->Integral()<<endl;
cout<<"Total Number of Events in MC   = "<<hRatio[16]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("vbf_AK4_jj_pt");
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
h2->Draw("");
	c1->SaveAs("vbf_AK4_jj_pt.pdf");
	c1->SaveAs("vbf_AK4_jj_pt.png");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[17]->SetBottomMargin(0.05287462);
pad[17]->SetLogy(1);
pad[17]->Draw();
pad[17]->cd();

	t0_SigHist[17]->Scale(0.001730);
	HistMax = t0_SigHist[17]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_SigHist[17],"Signal*10","l");
	yMax=HistMax;

	t1_SigHist[17]->Scale(0.001870);
	HistMax = t1_SigHist[17]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_SigHist[17],"WTWT*10","l");
	yMax=HistMax;

	t0_BkgHist[17]->Scale(5.340000);
	HistMax = t0_BkgHist[17]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_BkgHist[17],"WJets","f");
	yMax=HistMax;

	t1_BkgHist[17]->Scale(0.087600);
	HistMax = t1_BkgHist[17]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_BkgHist[17],"TTbar","f");
	yMax=HistMax;

	DataHist[17]->Sumw2();
	HistMax = DataHist[17]->GetMaximum()*1.15;
	t0_SigHist[17]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(DataHist[17],"Data","pe");
	yMax=HistMax;

	hs[17]->Add(t0_BkgHist[17],"hist");
	hs[17]->Add(t1_BkgHist[17],"hist");
	hs[17]->Draw();
	DataHist[17]->Draw("same");
	t0_SigHist[17]->Draw("same");
	t1_SigHist[17]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[17]->Clone();
hRatio[17]->Add(t0_BkgHist[17]);
hRatio[17]->Add(t1_BkgHist[17]);


c1->cd();
padB[17]->SetGridy(1);
padB[17]->SetTopMargin(0.0);
padB[17]->SetBottomMargin(0.30);
padB[17]->Draw();
padB[17]->cd();

yscale = (1.0-0.2)/(0.18-0);
h2->Divide(hRatio[17]);
cout<<"Total Number of Events in Data = "<<DataHist[17]->Integral()<<endl;
cout<<"Total Number of Events in MC   = "<<hRatio[17]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("vbf_AK4_jj_eta");
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
h2->Draw("");
	c1->SaveAs("vbf_AK4_jj_eta.pdf");
	c1->SaveAs("vbf_AK4_jj_eta.png");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[18]->SetBottomMargin(0.05287462);
pad[18]->SetLogy(1);
pad[18]->Draw();
pad[18]->cd();

	t0_SigHist[18]->Scale(0.001730);
	HistMax = t0_SigHist[18]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_SigHist[18],"Signal*10","l");
	yMax=HistMax;

	t1_SigHist[18]->Scale(0.001870);
	HistMax = t1_SigHist[18]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_SigHist[18],"WTWT*10","l");
	yMax=HistMax;

	t0_BkgHist[18]->Scale(5.340000);
	HistMax = t0_BkgHist[18]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_BkgHist[18],"WJets","f");
	yMax=HistMax;

	t1_BkgHist[18]->Scale(0.087600);
	HistMax = t1_BkgHist[18]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_BkgHist[18],"TTbar","f");
	yMax=HistMax;

	DataHist[18]->Sumw2();
	HistMax = DataHist[18]->GetMaximum()*1.15;
	t0_SigHist[18]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(DataHist[18],"Data","pe");
	yMax=HistMax;

	hs[18]->Add(t0_BkgHist[18],"hist");
	hs[18]->Add(t1_BkgHist[18],"hist");
	hs[18]->Draw();
	DataHist[18]->Draw("same");
	t0_SigHist[18]->Draw("same");
	t1_SigHist[18]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[18]->Clone();
hRatio[18]->Add(t0_BkgHist[18]);
hRatio[18]->Add(t1_BkgHist[18]);


c1->cd();
padB[18]->SetGridy(1);
padB[18]->SetTopMargin(0.0);
padB[18]->SetBottomMargin(0.30);
padB[18]->Draw();
padB[18]->cd();

yscale = (1.0-0.2)/(0.18-0);
h2->Divide(hRatio[18]);
cout<<"Total Number of Events in Data = "<<DataHist[18]->Integral()<<endl;
cout<<"Total Number of Events in MC   = "<<hRatio[18]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("vbf_AK4_jj_phi");
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
h2->Draw("");
	c1->SaveAs("vbf_AK4_jj_phi.pdf");
	c1->SaveAs("vbf_AK4_jj_phi.png");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[19]->SetBottomMargin(0.05287462);
pad[19]->SetLogy(1);
pad[19]->Draw();
pad[19]->cd();

	t0_SigHist[19]->Scale(0.001730);
	HistMax = t0_SigHist[19]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_SigHist[19],"Signal*10","l");
	yMax=HistMax;

	t1_SigHist[19]->Scale(0.001870);
	HistMax = t1_SigHist[19]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_SigHist[19],"WTWT*10","l");
	yMax=HistMax;

	t0_BkgHist[19]->Scale(5.340000);
	HistMax = t0_BkgHist[19]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_BkgHist[19],"WJets","f");
	yMax=HistMax;

	t1_BkgHist[19]->Scale(0.087600);
	HistMax = t1_BkgHist[19]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_BkgHist[19],"TTbar","f");
	yMax=HistMax;

	DataHist[19]->Sumw2();
	HistMax = DataHist[19]->GetMaximum()*1.15;
	t0_SigHist[19]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(DataHist[19],"Data","pe");
	yMax=HistMax;

	hs[19]->Add(t0_BkgHist[19],"hist");
	hs[19]->Add(t1_BkgHist[19],"hist");
	hs[19]->Draw();
	DataHist[19]->Draw("same");
	t0_SigHist[19]->Draw("same");
	t1_SigHist[19]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[19]->Clone();
hRatio[19]->Add(t0_BkgHist[19]);
hRatio[19]->Add(t1_BkgHist[19]);


c1->cd();
padB[19]->SetGridy(1);
padB[19]->SetTopMargin(0.0);
padB[19]->SetBottomMargin(0.30);
padB[19]->Draw();
padB[19]->cd();

yscale = (1.0-0.2)/(0.18-0);
h2->Divide(hRatio[19]);
cout<<"Total Number of Events in Data = "<<DataHist[19]->Integral()<<endl;
cout<<"Total Number of Events in MC   = "<<hRatio[19]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("vbf_AK4_jj_m");
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
h2->Draw("");
	c1->SaveAs("vbf_AK4_jj_m.pdf");
	c1->SaveAs("vbf_AK4_jj_m.png");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[20]->SetBottomMargin(0.05287462);
pad[20]->SetLogy(1);
pad[20]->Draw();
pad[20]->cd();

	t0_SigHist[20]->Scale(0.001730);
	HistMax = t0_SigHist[20]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_SigHist[20],"Signal*10","l");
	yMax=HistMax;

	t1_SigHist[20]->Scale(0.001870);
	HistMax = t1_SigHist[20]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_SigHist[20],"WTWT*10","l");
	yMax=HistMax;

	t0_BkgHist[20]->Scale(5.340000);
	HistMax = t0_BkgHist[20]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_BkgHist[20],"WJets","f");
	yMax=HistMax;

	t1_BkgHist[20]->Scale(0.087600);
	HistMax = t1_BkgHist[20]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_BkgHist[20],"TTbar","f");
	yMax=HistMax;

	DataHist[20]->Sumw2();
	HistMax = DataHist[20]->GetMaximum()*1.15;
	t0_SigHist[20]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(DataHist[20],"Data","pe");
	yMax=HistMax;

	hs[20]->Add(t0_BkgHist[20],"hist");
	hs[20]->Add(t1_BkgHist[20],"hist");
	hs[20]->Draw();
	DataHist[20]->Draw("same");
	t0_SigHist[20]->Draw("same");
	t1_SigHist[20]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[20]->Clone();
hRatio[20]->Add(t0_BkgHist[20]);
hRatio[20]->Add(t1_BkgHist[20]);


c1->cd();
padB[20]->SetGridy(1);
padB[20]->SetTopMargin(0.0);
padB[20]->SetBottomMargin(0.30);
padB[20]->Draw();
padB[20]->cd();

yscale = (1.0-0.2)/(0.18-0);
h2->Divide(hRatio[20]);
cout<<"Total Number of Events in Data = "<<DataHist[20]->Integral()<<endl;
cout<<"Total Number of Events in MC   = "<<hRatio[20]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("Wjets_AK4_j1_pt");
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
h2->Draw("");
	c1->SaveAs("Wjets_AK4_j1_pt.pdf");
	c1->SaveAs("Wjets_AK4_j1_pt.png");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[21]->SetBottomMargin(0.05287462);
pad[21]->SetLogy(1);
pad[21]->Draw();
pad[21]->cd();

	t0_SigHist[21]->Scale(0.001730);
	HistMax = t0_SigHist[21]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_SigHist[21],"Signal*10","l");
	yMax=HistMax;

	t1_SigHist[21]->Scale(0.001870);
	HistMax = t1_SigHist[21]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_SigHist[21],"WTWT*10","l");
	yMax=HistMax;

	t0_BkgHist[21]->Scale(5.340000);
	HistMax = t0_BkgHist[21]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_BkgHist[21],"WJets","f");
	yMax=HistMax;

	t1_BkgHist[21]->Scale(0.087600);
	HistMax = t1_BkgHist[21]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_BkgHist[21],"TTbar","f");
	yMax=HistMax;

	DataHist[21]->Sumw2();
	HistMax = DataHist[21]->GetMaximum()*1.15;
	t0_SigHist[21]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(DataHist[21],"Data","pe");
	yMax=HistMax;

	hs[21]->Add(t0_BkgHist[21],"hist");
	hs[21]->Add(t1_BkgHist[21],"hist");
	hs[21]->Draw();
	DataHist[21]->Draw("same");
	t0_SigHist[21]->Draw("same");
	t1_SigHist[21]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[21]->Clone();
hRatio[21]->Add(t0_BkgHist[21]);
hRatio[21]->Add(t1_BkgHist[21]);


c1->cd();
padB[21]->SetGridy(1);
padB[21]->SetTopMargin(0.0);
padB[21]->SetBottomMargin(0.30);
padB[21]->Draw();
padB[21]->cd();

yscale = (1.0-0.2)/(0.18-0);
h2->Divide(hRatio[21]);
cout<<"Total Number of Events in Data = "<<DataHist[21]->Integral()<<endl;
cout<<"Total Number of Events in MC   = "<<hRatio[21]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("Wjets_AK4_j1_eta");
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
h2->Draw("");
	c1->SaveAs("Wjets_AK4_j1_eta.pdf");
	c1->SaveAs("Wjets_AK4_j1_eta.png");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[22]->SetBottomMargin(0.05287462);
pad[22]->SetLogy(1);
pad[22]->Draw();
pad[22]->cd();

	t0_SigHist[22]->Scale(0.001730);
	HistMax = t0_SigHist[22]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_SigHist[22],"Signal*10","l");
	yMax=HistMax;

	t1_SigHist[22]->Scale(0.001870);
	HistMax = t1_SigHist[22]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_SigHist[22],"WTWT*10","l");
	yMax=HistMax;

	t0_BkgHist[22]->Scale(5.340000);
	HistMax = t0_BkgHist[22]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_BkgHist[22],"WJets","f");
	yMax=HistMax;

	t1_BkgHist[22]->Scale(0.087600);
	HistMax = t1_BkgHist[22]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_BkgHist[22],"TTbar","f");
	yMax=HistMax;

	DataHist[22]->Sumw2();
	HistMax = DataHist[22]->GetMaximum()*1.15;
	t0_SigHist[22]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(DataHist[22],"Data","pe");
	yMax=HistMax;

	hs[22]->Add(t0_BkgHist[22],"hist");
	hs[22]->Add(t1_BkgHist[22],"hist");
	hs[22]->Draw();
	DataHist[22]->Draw("same");
	t0_SigHist[22]->Draw("same");
	t1_SigHist[22]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[22]->Clone();
hRatio[22]->Add(t0_BkgHist[22]);
hRatio[22]->Add(t1_BkgHist[22]);


c1->cd();
padB[22]->SetGridy(1);
padB[22]->SetTopMargin(0.0);
padB[22]->SetBottomMargin(0.30);
padB[22]->Draw();
padB[22]->cd();

yscale = (1.0-0.2)/(0.18-0);
h2->Divide(hRatio[22]);
cout<<"Total Number of Events in Data = "<<DataHist[22]->Integral()<<endl;
cout<<"Total Number of Events in MC   = "<<hRatio[22]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("Wjets_AK4_j1_phi");
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
h2->Draw("");
	c1->SaveAs("Wjets_AK4_j1_phi.pdf");
	c1->SaveAs("Wjets_AK4_j1_phi.png");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[23]->SetBottomMargin(0.05287462);
pad[23]->SetLogy(1);
pad[23]->Draw();
pad[23]->cd();

	t0_SigHist[23]->Scale(0.001730);
	HistMax = t0_SigHist[23]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_SigHist[23],"Signal*10","l");
	yMax=HistMax;

	t1_SigHist[23]->Scale(0.001870);
	HistMax = t1_SigHist[23]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_SigHist[23],"WTWT*10","l");
	yMax=HistMax;

	t0_BkgHist[23]->Scale(5.340000);
	HistMax = t0_BkgHist[23]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_BkgHist[23],"WJets","f");
	yMax=HistMax;

	t1_BkgHist[23]->Scale(0.087600);
	HistMax = t1_BkgHist[23]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_BkgHist[23],"TTbar","f");
	yMax=HistMax;

	DataHist[23]->Sumw2();
	HistMax = DataHist[23]->GetMaximum()*1.15;
	t0_SigHist[23]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(DataHist[23],"Data","pe");
	yMax=HistMax;

	hs[23]->Add(t0_BkgHist[23],"hist");
	hs[23]->Add(t1_BkgHist[23],"hist");
	hs[23]->Draw();
	DataHist[23]->Draw("same");
	t0_SigHist[23]->Draw("same");
	t1_SigHist[23]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[23]->Clone();
hRatio[23]->Add(t0_BkgHist[23]);
hRatio[23]->Add(t1_BkgHist[23]);


c1->cd();
padB[23]->SetGridy(1);
padB[23]->SetTopMargin(0.0);
padB[23]->SetBottomMargin(0.30);
padB[23]->Draw();
padB[23]->cd();

yscale = (1.0-0.2)/(0.18-0);
h2->Divide(hRatio[23]);
cout<<"Total Number of Events in Data = "<<DataHist[23]->Integral()<<endl;
cout<<"Total Number of Events in MC   = "<<hRatio[23]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("Wjets_AK4_j1_e");
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
h2->Draw("");
	c1->SaveAs("Wjets_AK4_j1_e.pdf");
	c1->SaveAs("Wjets_AK4_j1_e.png");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[24]->SetBottomMargin(0.05287462);
pad[24]->SetLogy(1);
pad[24]->Draw();
pad[24]->cd();

	t0_SigHist[24]->Scale(0.001730);
	HistMax = t0_SigHist[24]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_SigHist[24],"Signal*10","l");
	yMax=HistMax;

	t1_SigHist[24]->Scale(0.001870);
	HistMax = t1_SigHist[24]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_SigHist[24],"WTWT*10","l");
	yMax=HistMax;

	t0_BkgHist[24]->Scale(5.340000);
	HistMax = t0_BkgHist[24]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_BkgHist[24],"WJets","f");
	yMax=HistMax;

	t1_BkgHist[24]->Scale(0.087600);
	HistMax = t1_BkgHist[24]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_BkgHist[24],"TTbar","f");
	yMax=HistMax;

	DataHist[24]->Sumw2();
	HistMax = DataHist[24]->GetMaximum()*1.15;
	t0_SigHist[24]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(DataHist[24],"Data","pe");
	yMax=HistMax;

	hs[24]->Add(t0_BkgHist[24],"hist");
	hs[24]->Add(t1_BkgHist[24],"hist");
	hs[24]->Draw();
	DataHist[24]->Draw("same");
	t0_SigHist[24]->Draw("same");
	t1_SigHist[24]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[24]->Clone();
hRatio[24]->Add(t0_BkgHist[24]);
hRatio[24]->Add(t1_BkgHist[24]);


c1->cd();
padB[24]->SetGridy(1);
padB[24]->SetTopMargin(0.0);
padB[24]->SetBottomMargin(0.30);
padB[24]->Draw();
padB[24]->cd();

yscale = (1.0-0.2)/(0.18-0);
h2->Divide(hRatio[24]);
cout<<"Total Number of Events in Data = "<<DataHist[24]->Integral()<<endl;
cout<<"Total Number of Events in MC   = "<<hRatio[24]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("Wjets_AK4_j2_pt");
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
h2->Draw("");
	c1->SaveAs("Wjets_AK4_j2_pt.pdf");
	c1->SaveAs("Wjets_AK4_j2_pt.png");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[25]->SetBottomMargin(0.05287462);
pad[25]->SetLogy(1);
pad[25]->Draw();
pad[25]->cd();

	t0_SigHist[25]->Scale(0.001730);
	HistMax = t0_SigHist[25]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_SigHist[25],"Signal*10","l");
	yMax=HistMax;

	t1_SigHist[25]->Scale(0.001870);
	HistMax = t1_SigHist[25]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_SigHist[25],"WTWT*10","l");
	yMax=HistMax;

	t0_BkgHist[25]->Scale(5.340000);
	HistMax = t0_BkgHist[25]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_BkgHist[25],"WJets","f");
	yMax=HistMax;

	t1_BkgHist[25]->Scale(0.087600);
	HistMax = t1_BkgHist[25]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_BkgHist[25],"TTbar","f");
	yMax=HistMax;

	DataHist[25]->Sumw2();
	HistMax = DataHist[25]->GetMaximum()*1.15;
	t0_SigHist[25]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(DataHist[25],"Data","pe");
	yMax=HistMax;

	hs[25]->Add(t0_BkgHist[25],"hist");
	hs[25]->Add(t1_BkgHist[25],"hist");
	hs[25]->Draw();
	DataHist[25]->Draw("same");
	t0_SigHist[25]->Draw("same");
	t1_SigHist[25]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[25]->Clone();
hRatio[25]->Add(t0_BkgHist[25]);
hRatio[25]->Add(t1_BkgHist[25]);


c1->cd();
padB[25]->SetGridy(1);
padB[25]->SetTopMargin(0.0);
padB[25]->SetBottomMargin(0.30);
padB[25]->Draw();
padB[25]->cd();

yscale = (1.0-0.2)/(0.18-0);
h2->Divide(hRatio[25]);
cout<<"Total Number of Events in Data = "<<DataHist[25]->Integral()<<endl;
cout<<"Total Number of Events in MC   = "<<hRatio[25]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("Wjets_AK4_j2_eta");
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
h2->Draw("");
	c1->SaveAs("Wjets_AK4_j2_eta.pdf");
	c1->SaveAs("Wjets_AK4_j2_eta.png");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[26]->SetBottomMargin(0.05287462);
pad[26]->SetLogy(1);
pad[26]->Draw();
pad[26]->cd();

	t0_SigHist[26]->Scale(0.001730);
	HistMax = t0_SigHist[26]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_SigHist[26],"Signal*10","l");
	yMax=HistMax;

	t1_SigHist[26]->Scale(0.001870);
	HistMax = t1_SigHist[26]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_SigHist[26],"WTWT*10","l");
	yMax=HistMax;

	t0_BkgHist[26]->Scale(5.340000);
	HistMax = t0_BkgHist[26]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_BkgHist[26],"WJets","f");
	yMax=HistMax;

	t1_BkgHist[26]->Scale(0.087600);
	HistMax = t1_BkgHist[26]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_BkgHist[26],"TTbar","f");
	yMax=HistMax;

	DataHist[26]->Sumw2();
	HistMax = DataHist[26]->GetMaximum()*1.15;
	t0_SigHist[26]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(DataHist[26],"Data","pe");
	yMax=HistMax;

	hs[26]->Add(t0_BkgHist[26],"hist");
	hs[26]->Add(t1_BkgHist[26],"hist");
	hs[26]->Draw();
	DataHist[26]->Draw("same");
	t0_SigHist[26]->Draw("same");
	t1_SigHist[26]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[26]->Clone();
hRatio[26]->Add(t0_BkgHist[26]);
hRatio[26]->Add(t1_BkgHist[26]);


c1->cd();
padB[26]->SetGridy(1);
padB[26]->SetTopMargin(0.0);
padB[26]->SetBottomMargin(0.30);
padB[26]->Draw();
padB[26]->cd();

yscale = (1.0-0.2)/(0.18-0);
h2->Divide(hRatio[26]);
cout<<"Total Number of Events in Data = "<<DataHist[26]->Integral()<<endl;
cout<<"Total Number of Events in MC   = "<<hRatio[26]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("Wjets_AK4_j2_phi");
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
h2->Draw("");
	c1->SaveAs("Wjets_AK4_j2_phi.pdf");
	c1->SaveAs("Wjets_AK4_j2_phi.png");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[27]->SetBottomMargin(0.05287462);
pad[27]->SetLogy(1);
pad[27]->Draw();
pad[27]->cd();

	t0_SigHist[27]->Scale(0.001730);
	HistMax = t0_SigHist[27]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_SigHist[27],"Signal*10","l");
	yMax=HistMax;

	t1_SigHist[27]->Scale(0.001870);
	HistMax = t1_SigHist[27]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_SigHist[27],"WTWT*10","l");
	yMax=HistMax;

	t0_BkgHist[27]->Scale(5.340000);
	HistMax = t0_BkgHist[27]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_BkgHist[27],"WJets","f");
	yMax=HistMax;

	t1_BkgHist[27]->Scale(0.087600);
	HistMax = t1_BkgHist[27]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_BkgHist[27],"TTbar","f");
	yMax=HistMax;

	DataHist[27]->Sumw2();
	HistMax = DataHist[27]->GetMaximum()*1.15;
	t0_SigHist[27]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(DataHist[27],"Data","pe");
	yMax=HistMax;

	hs[27]->Add(t0_BkgHist[27],"hist");
	hs[27]->Add(t1_BkgHist[27],"hist");
	hs[27]->Draw();
	DataHist[27]->Draw("same");
	t0_SigHist[27]->Draw("same");
	t1_SigHist[27]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[27]->Clone();
hRatio[27]->Add(t0_BkgHist[27]);
hRatio[27]->Add(t1_BkgHist[27]);


c1->cd();
padB[27]->SetGridy(1);
padB[27]->SetTopMargin(0.0);
padB[27]->SetBottomMargin(0.30);
padB[27]->Draw();
padB[27]->cd();

yscale = (1.0-0.2)/(0.18-0);
h2->Divide(hRatio[27]);
cout<<"Total Number of Events in Data = "<<DataHist[27]->Integral()<<endl;
cout<<"Total Number of Events in MC   = "<<hRatio[27]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("Wjets_AK4_j2_e");
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
h2->Draw("");
	c1->SaveAs("Wjets_AK4_j2_e.pdf");
	c1->SaveAs("Wjets_AK4_j2_e.png");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[28]->SetBottomMargin(0.05287462);
pad[28]->SetLogy(1);
pad[28]->Draw();
pad[28]->cd();

	t0_SigHist[28]->Scale(0.001730);
	HistMax = t0_SigHist[28]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_SigHist[28],"Signal*10","l");
	yMax=HistMax;

	t1_SigHist[28]->Scale(0.001870);
	HistMax = t1_SigHist[28]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_SigHist[28],"WTWT*10","l");
	yMax=HistMax;

	t0_BkgHist[28]->Scale(5.340000);
	HistMax = t0_BkgHist[28]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_BkgHist[28],"WJets","f");
	yMax=HistMax;

	t1_BkgHist[28]->Scale(0.087600);
	HistMax = t1_BkgHist[28]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_BkgHist[28],"TTbar","f");
	yMax=HistMax;

	DataHist[28]->Sumw2();
	HistMax = DataHist[28]->GetMaximum()*1.15;
	t0_SigHist[28]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(DataHist[28],"Data","pe");
	yMax=HistMax;

	hs[28]->Add(t0_BkgHist[28],"hist");
	hs[28]->Add(t1_BkgHist[28],"hist");
	hs[28]->Draw();
	DataHist[28]->Draw("same");
	t0_SigHist[28]->Draw("same");
	t1_SigHist[28]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[28]->Clone();
hRatio[28]->Add(t0_BkgHist[28]);
hRatio[28]->Add(t1_BkgHist[28]);


c1->cd();
padB[28]->SetGridy(1);
padB[28]->SetTopMargin(0.0);
padB[28]->SetBottomMargin(0.30);
padB[28]->Draw();
padB[28]->cd();

yscale = (1.0-0.2)/(0.18-0);
h2->Divide(hRatio[28]);
cout<<"Total Number of Events in Data = "<<DataHist[28]->Integral()<<endl;
cout<<"Total Number of Events in MC   = "<<hRatio[28]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("Wjets_AK4_jj_pt");
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
h2->Draw("");
	c1->SaveAs("Wjets_AK4_jj_pt.pdf");
	c1->SaveAs("Wjets_AK4_jj_pt.png");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[29]->SetBottomMargin(0.05287462);
pad[29]->SetLogy(1);
pad[29]->Draw();
pad[29]->cd();

	t0_SigHist[29]->Scale(0.001730);
	HistMax = t0_SigHist[29]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_SigHist[29],"Signal*10","l");
	yMax=HistMax;

	t1_SigHist[29]->Scale(0.001870);
	HistMax = t1_SigHist[29]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_SigHist[29],"WTWT*10","l");
	yMax=HistMax;

	t0_BkgHist[29]->Scale(5.340000);
	HistMax = t0_BkgHist[29]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_BkgHist[29],"WJets","f");
	yMax=HistMax;

	t1_BkgHist[29]->Scale(0.087600);
	HistMax = t1_BkgHist[29]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_BkgHist[29],"TTbar","f");
	yMax=HistMax;

	DataHist[29]->Sumw2();
	HistMax = DataHist[29]->GetMaximum()*1.15;
	t0_SigHist[29]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(DataHist[29],"Data","pe");
	yMax=HistMax;

	hs[29]->Add(t0_BkgHist[29],"hist");
	hs[29]->Add(t1_BkgHist[29],"hist");
	hs[29]->Draw();
	DataHist[29]->Draw("same");
	t0_SigHist[29]->Draw("same");
	t1_SigHist[29]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[29]->Clone();
hRatio[29]->Add(t0_BkgHist[29]);
hRatio[29]->Add(t1_BkgHist[29]);


c1->cd();
padB[29]->SetGridy(1);
padB[29]->SetTopMargin(0.0);
padB[29]->SetBottomMargin(0.30);
padB[29]->Draw();
padB[29]->cd();

yscale = (1.0-0.2)/(0.18-0);
h2->Divide(hRatio[29]);
cout<<"Total Number of Events in Data = "<<DataHist[29]->Integral()<<endl;
cout<<"Total Number of Events in MC   = "<<hRatio[29]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("Wjets_AK4_jj_eta");
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
h2->Draw("");
	c1->SaveAs("Wjets_AK4_jj_eta.pdf");
	c1->SaveAs("Wjets_AK4_jj_eta.png");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[30]->SetBottomMargin(0.05287462);
pad[30]->SetLogy(1);
pad[30]->Draw();
pad[30]->cd();

	t0_SigHist[30]->Scale(0.001730);
	HistMax = t0_SigHist[30]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_SigHist[30],"Signal*10","l");
	yMax=HistMax;

	t1_SigHist[30]->Scale(0.001870);
	HistMax = t1_SigHist[30]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_SigHist[30],"WTWT*10","l");
	yMax=HistMax;

	t0_BkgHist[30]->Scale(5.340000);
	HistMax = t0_BkgHist[30]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_BkgHist[30],"WJets","f");
	yMax=HistMax;

	t1_BkgHist[30]->Scale(0.087600);
	HistMax = t1_BkgHist[30]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_BkgHist[30],"TTbar","f");
	yMax=HistMax;

	DataHist[30]->Sumw2();
	HistMax = DataHist[30]->GetMaximum()*1.15;
	t0_SigHist[30]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(DataHist[30],"Data","pe");
	yMax=HistMax;

	hs[30]->Add(t0_BkgHist[30],"hist");
	hs[30]->Add(t1_BkgHist[30],"hist");
	hs[30]->Draw();
	DataHist[30]->Draw("same");
	t0_SigHist[30]->Draw("same");
	t1_SigHist[30]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[30]->Clone();
hRatio[30]->Add(t0_BkgHist[30]);
hRatio[30]->Add(t1_BkgHist[30]);


c1->cd();
padB[30]->SetGridy(1);
padB[30]->SetTopMargin(0.0);
padB[30]->SetBottomMargin(0.30);
padB[30]->Draw();
padB[30]->cd();

yscale = (1.0-0.2)/(0.18-0);
h2->Divide(hRatio[30]);
cout<<"Total Number of Events in Data = "<<DataHist[30]->Integral()<<endl;
cout<<"Total Number of Events in MC   = "<<hRatio[30]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("Wjets_AK4_jj_phi");
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
h2->Draw("");
	c1->SaveAs("Wjets_AK4_jj_phi.pdf");
	c1->SaveAs("Wjets_AK4_jj_phi.png");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[31]->SetBottomMargin(0.05287462);
pad[31]->SetLogy(1);
pad[31]->Draw();
pad[31]->cd();

	t0_SigHist[31]->Scale(0.001730);
	HistMax = t0_SigHist[31]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_SigHist[31],"Signal*10","l");
	yMax=HistMax;

	t1_SigHist[31]->Scale(0.001870);
	HistMax = t1_SigHist[31]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_SigHist[31],"WTWT*10","l");
	yMax=HistMax;

	t0_BkgHist[31]->Scale(5.340000);
	HistMax = t0_BkgHist[31]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_BkgHist[31],"WJets","f");
	yMax=HistMax;

	t1_BkgHist[31]->Scale(0.087600);
	HistMax = t1_BkgHist[31]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_BkgHist[31],"TTbar","f");
	yMax=HistMax;

	DataHist[31]->Sumw2();
	HistMax = DataHist[31]->GetMaximum()*1.15;
	t0_SigHist[31]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(DataHist[31],"Data","pe");
	yMax=HistMax;

	hs[31]->Add(t0_BkgHist[31],"hist");
	hs[31]->Add(t1_BkgHist[31],"hist");
	hs[31]->Draw();
	DataHist[31]->Draw("same");
	t0_SigHist[31]->Draw("same");
	t1_SigHist[31]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[31]->Clone();
hRatio[31]->Add(t0_BkgHist[31]);
hRatio[31]->Add(t1_BkgHist[31]);


c1->cd();
padB[31]->SetGridy(1);
padB[31]->SetTopMargin(0.0);
padB[31]->SetBottomMargin(0.30);
padB[31]->Draw();
padB[31]->cd();

yscale = (1.0-0.2)/(0.18-0);
h2->Divide(hRatio[31]);
cout<<"Total Number of Events in Data = "<<DataHist[31]->Integral()<<endl;
cout<<"Total Number of Events in MC   = "<<hRatio[31]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("Wjets_AK4_jj_e");
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
h2->Draw("");
	c1->SaveAs("Wjets_AK4_jj_e.pdf");
	c1->SaveAs("Wjets_AK4_jj_e.png");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[32]->SetBottomMargin(0.05287462);
pad[32]->SetLogy(1);
pad[32]->Draw();
pad[32]->cd();

	t0_SigHist[32]->Scale(0.001730);
	HistMax = t0_SigHist[32]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_SigHist[32],"Signal*10","l");
	yMax=HistMax;

	t1_SigHist[32]->Scale(0.001870);
	HistMax = t1_SigHist[32]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_SigHist[32],"WTWT*10","l");
	yMax=HistMax;

	t0_BkgHist[32]->Scale(5.340000);
	HistMax = t0_BkgHist[32]->GetMaximum()*1.15;
	t0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t0_BkgHist[32],"WJets","f");
	yMax=HistMax;

	t1_BkgHist[32]->Scale(0.087600);
	HistMax = t1_BkgHist[32]->GetMaximum()*1.15;
	t0_SigHist[1]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(t1_BkgHist[32],"TTbar","f");
	yMax=HistMax;

	DataHist[32]->Sumw2();
	HistMax = DataHist[32]->GetMaximum()*1.15;
	t0_SigHist[32]->SetMaximum(TMath::Max(HistMax,yMax));
	leg->AddEntry(DataHist[32],"Data","pe");
	yMax=HistMax;

	hs[32]->Add(t0_BkgHist[32],"hist");
	hs[32]->Add(t1_BkgHist[32],"hist");
	hs[32]->Draw();
	DataHist[32]->Draw("same");
	t0_SigHist[32]->Draw("same");
	t1_SigHist[32]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[32]->Clone();
hRatio[32]->Add(t0_BkgHist[32]);
hRatio[32]->Add(t1_BkgHist[32]);


c1->cd();
padB[32]->SetGridy(1);
padB[32]->SetTopMargin(0.0);
padB[32]->SetBottomMargin(0.30);
padB[32]->Draw();
padB[32]->cd();

yscale = (1.0-0.2)/(0.18-0);
h2->Divide(hRatio[32]);
cout<<"Total Number of Events in Data = "<<DataHist[32]->Integral()<<endl;
cout<<"Total Number of Events in MC   = "<<hRatio[32]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("Wjets_AK4_jj_m");
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
h2->Draw("");
	c1->SaveAs("Wjets_AK4_jj_m.pdf");
	c1->SaveAs("Wjets_AK4_jj_m.png");
	leg->Clear();
	c1->Clear();
	//###########################################################




}
