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


	int t0 = time(NULL);


	TGaxis::SetMaxDigits(3);


int Bin[26] = { 40 , 35 , 18 , 15 , 50 , 60 , 40 , 30 , 30 , 40 , 25 , 30 , 30 , 50 , 25 , 50 , 50 , 50 , 20 , 20 , 50 , 20 , 20 , 20 , 12 , 10 };
double Min[26] = { 0 , 0 , -2.1 , -3.5 , 0 , 0 , 0 , -2.4 , -2.4 , 0 , 40 , -2.4 , -2.4 , 0 , 0 , 0 , 0 , -1.5 , 0 , 0 , 0 , 0.0 , 0.0 , 0 , 3 , 0 };
double Max[26] = { 40 , 500 , 2.1 , 3.5 , 500 , 900 , 600 , 2.4 , 2.4 , 600 , 500 , 2.4 , 2.4 , 3000 , 1000 , 200 , 2000 , 1.5 , 300 , 1400 , 1800 , 6.0 , 3.3 , 3.3 , 15 , 10 };

int NumPV;
int j=0;	//for bins
int k=6;	//reseting the color of backgrounds
	TCanvas * c1 = new TCanvas("c1","",500,500);

	int binidx;
	float Nvtx_weight;

	THStack** hs = new THStack*[26];
	TPad** pad = new TPad*[26];
	TPad** padB = new TPad*[26];
	TH1F**hRatio = new TH1F*[26];
	for(int i=0; i<26;i++){
		hs[i] = new THStack(Form("hs%i",i),"");
		pad[i] = new TPad(Form("pad%i",i),"",0,0.30,1,1);
		padB[i] = new TPad(Form("padB%i",i),"",0,0,1,0.30);
		hRatio[i] = new TH1F(Form("hRatio%i",i),"Ratio",Bin[i],Min[i],Max[i]);
	}

	TH1F** t0_BkgHist = new TH1F*[390];
	TH1F** t1_BkgHist = new TH1F*[390];
	TH1F** t2_BkgHist = new TH1F*[390];
	TH1F** t3_BkgHist = new TH1F*[390];
	TH1F** t4_BkgHist = new TH1F*[390];
	TH1F** t5_BkgHist = new TH1F*[390];
	TH1F** t6_BkgHist = new TH1F*[390];
	TH1F** t7_BkgHist = new TH1F*[390];
	TH1F** t8_BkgHist = new TH1F*[390];
	TH1F** t9_BkgHist = new TH1F*[390];
	TH1F** t10_BkgHist = new TH1F*[390];
	TH1F** t11_BkgHist = new TH1F*[390];
	TH1F** t12_BkgHist = new TH1F*[390];
	TH1F** t13_BkgHist = new TH1F*[390];
	TH1F** t14_BkgHist = new TH1F*[390];
	for(int i=0; i<26;i++){
		if (i%26==0)     {j=0;	//for reset bins
				k=4;}	// for line & Fill color
		else j++;
		if (k==8) k++;
		if (k==10) k++;
		t0_BkgHist[i] = new TH1F(Form("t0_BkgHist%i",i),"",Bin[j],Min[j],Max[j]);
		t0_BkgHist[i]->SetLineColor(k);
		t0_BkgHist[i]->SetMarkerColor(k);
		t0_BkgHist[i]->SetFillColor(k);
	}

	for(int i=0; i<26;i++){
		if (i%26==0)     {j=0;	//for reset bins
				k=4;}	// for line & Fill color
		else j++;
		if (k==8) k++;
		if (k==10) k++;
		t1_BkgHist[i] = new TH1F(Form("t1_BkgHist%i",i),"",Bin[j],Min[j],Max[j]);
		t1_BkgHist[i]->SetLineColor(k);
		t1_BkgHist[i]->SetMarkerColor(k);
		t1_BkgHist[i]->SetFillColor(k);
	}

	for(int i=0; i<26;i++){
		if (i%26==0)     {j=0;	//for reset bins
				k=4;}	// for line & Fill color
		else j++;
		if (k==8) k++;
		if (k==10) k++;
		t2_BkgHist[i] = new TH1F(Form("t2_BkgHist%i",i),"",Bin[j],Min[j],Max[j]);
		t2_BkgHist[i]->SetLineColor(k);
		t2_BkgHist[i]->SetMarkerColor(k);
		t2_BkgHist[i]->SetFillColor(k);
	}

	for(int i=0; i<26;i++){
		if (i%26==0)     {j=0;	//for reset bins
				k=3;}	// for line & Fill color
		else j++;
		if (k==8) k++;
		if (k==10) k++;
		t3_BkgHist[i] = new TH1F(Form("t3_BkgHist%i",i),"",Bin[j],Min[j],Max[j]);
		t3_BkgHist[i]->SetLineColor(k);
		t3_BkgHist[i]->SetMarkerColor(k);
		t3_BkgHist[i]->SetFillColor(k);
	}

	for(int i=0; i<26;i++){
		if (i%26==0)     {j=0;	//for reset bins
				k=3;}	// for line & Fill color
		else j++;
		if (k==8) k++;
		if (k==10) k++;
		t4_BkgHist[i] = new TH1F(Form("t4_BkgHist%i",i),"",Bin[j],Min[j],Max[j]);
		t4_BkgHist[i]->SetLineColor(k);
		t4_BkgHist[i]->SetMarkerColor(k);
		t4_BkgHist[i]->SetFillColor(k);
	}

	for(int i=0; i<26;i++){
		if (i%26==0)     {j=0;	//for reset bins
				k=3;}	// for line & Fill color
		else j++;
		if (k==8) k++;
		if (k==10) k++;
		t5_BkgHist[i] = new TH1F(Form("t5_BkgHist%i",i),"",Bin[j],Min[j],Max[j]);
		t5_BkgHist[i]->SetLineColor(k);
		t5_BkgHist[i]->SetMarkerColor(k);
		t5_BkgHist[i]->SetFillColor(k);
	}

	for(int i=0; i<26;i++){
		if (i%26==0)     {j=0;	//for reset bins
				k=3;}	// for line & Fill color
		else j++;
		if (k==8) k++;
		if (k==10) k++;
		t6_BkgHist[i] = new TH1F(Form("t6_BkgHist%i",i),"",Bin[j],Min[j],Max[j]);
		t6_BkgHist[i]->SetLineColor(k);
		t6_BkgHist[i]->SetMarkerColor(k);
		t6_BkgHist[i]->SetFillColor(k);
	}

	for(int i=0; i<26;i++){
		if (i%26==0)     {j=0;	//for reset bins
				k=2;}	// for line & Fill color
		else j++;
		if (k==8) k++;
		if (k==10) k++;
		t7_BkgHist[i] = new TH1F(Form("t7_BkgHist%i",i),"",Bin[j],Min[j],Max[j]);
		t7_BkgHist[i]->SetLineColor(k);
		t7_BkgHist[i]->SetMarkerColor(k);
		t7_BkgHist[i]->SetFillColor(k);
	}

	for(int i=0; i<26;i++){
		if (i%26==0)     {j=0;	//for reset bins
				k=2;}	// for line & Fill color
		else j++;
		if (k==8) k++;
		if (k==10) k++;
		t8_BkgHist[i] = new TH1F(Form("t8_BkgHist%i",i),"",Bin[j],Min[j],Max[j]);
		t8_BkgHist[i]->SetLineColor(k);
		t8_BkgHist[i]->SetMarkerColor(k);
		t8_BkgHist[i]->SetFillColor(k);
	}

	for(int i=0; i<26;i++){
		if (i%26==0)     {j=0;	//for reset bins
				k=2;}	// for line & Fill color
		else j++;
		if (k==8) k++;
		if (k==10) k++;
		t9_BkgHist[i] = new TH1F(Form("t9_BkgHist%i",i),"",Bin[j],Min[j],Max[j]);
		t9_BkgHist[i]->SetLineColor(k);
		t9_BkgHist[i]->SetMarkerColor(k);
		t9_BkgHist[i]->SetFillColor(k);
	}

	for(int i=0; i<26;i++){
		if (i%26==0)     {j=0;	//for reset bins
				k=2;}	// for line & Fill color
		else j++;
		if (k==8) k++;
		if (k==10) k++;
		t10_BkgHist[i] = new TH1F(Form("t10_BkgHist%i",i),"",Bin[j],Min[j],Max[j]);
		t10_BkgHist[i]->SetLineColor(k);
		t10_BkgHist[i]->SetMarkerColor(k);
		t10_BkgHist[i]->SetFillColor(k);
	}

	for(int i=0; i<26;i++){
		if (i%26==0)     {j=0;	//for reset bins
				k=2;}	// for line & Fill color
		else j++;
		if (k==8) k++;
		if (k==10) k++;
		t11_BkgHist[i] = new TH1F(Form("t11_BkgHist%i",i),"",Bin[j],Min[j],Max[j]);
		t11_BkgHist[i]->SetLineColor(k);
		t11_BkgHist[i]->SetMarkerColor(k);
		t11_BkgHist[i]->SetFillColor(k);
	}

	for(int i=0; i<26;i++){
		if (i%26==0)     {j=0;	//for reset bins
				k=2;}	// for line & Fill color
		else j++;
		if (k==8) k++;
		if (k==10) k++;
		t12_BkgHist[i] = new TH1F(Form("t12_BkgHist%i",i),"",Bin[j],Min[j],Max[j]);
		t12_BkgHist[i]->SetLineColor(k);
		t12_BkgHist[i]->SetMarkerColor(k);
		t12_BkgHist[i]->SetFillColor(k);
	}

	for(int i=0; i<26;i++){
		if (i%26==0)     {j=0;	//for reset bins
				k=2;}	// for line & Fill color
		else j++;
		if (k==8) k++;
		if (k==10) k++;
		t13_BkgHist[i] = new TH1F(Form("t13_BkgHist%i",i),"",Bin[j],Min[j],Max[j]);
		t13_BkgHist[i]->SetLineColor(k);
		t13_BkgHist[i]->SetMarkerColor(k);
		t13_BkgHist[i]->SetFillColor(k);
	}

	for(int i=0; i<26;i++){
		if (i%26==0)     {j=0;	//for reset bins
				k=6;}	// for line & Fill color
		else j++;
		if (k==8) k++;
		if (k==10) k++;
		t14_BkgHist[i] = new TH1F(Form("t14_BkgHist%i",i),"",Bin[j],Min[j],Max[j]);
		t14_BkgHist[i]->SetLineColor(k);
		t14_BkgHist[i]->SetMarkerColor(k);
		t14_BkgHist[i]->SetFillColor(k);
	}

	TH1F** DataHist = new TH1F*[26];
	for(int i=0; i<26;i++){
		DataHist[i] = new TH1F(Form("DataHist%i",i),"",Bin[i],Min[i],Max[i]);
		DataHist[i]->SetLineColor(1);
		DataHist[i]->SetMarkerColor(1);
		//DataHist[i]->Sumw2();
	}

	TChain* t0_mc_bkg = new TChain("otree");
		t0_mc_bkg->Add("/afs/cern.ch/user/r/rasharma/work/aQGC_Studies/SecondStep_WWTrees/CMSSW_8_0_11/src/LepAJet_NoCutJet/copy_toRunDYEle/WWAnalysisRun2/output/output_el/WWTree_WW_excl.root");
		ClassReadTree mc_bkg_0(t0_mc_bkg);
		for(int iEv_0_mc_bkg=0;iEv_0_mc_bkg < t0_mc_bkg->GetEntries();iEv_0_mc_bkg++){
			t0_mc_bkg->GetEntry(iEv_0_mc_bkg);
			if (mc_bkg_0.pfMET>40 && mc_bkg_0.isVBFJet==1 &&( mc_bkg_0.vbf_maxpt_j1_bDiscriminatorCSV>0.935  ||  mc_bkg_0.vbf_maxpt_j2_bDiscriminatorCSV>0.935 ) )
			{
			t0_BkgHist[0]->Fill(mc_bkg_0.nPV,mc_bkg_0.totalEventWeight);
			t0_BkgHist[1]->Fill(mc_bkg_0.l_pt,mc_bkg_0.totalEventWeight);
			t0_BkgHist[2]->Fill(mc_bkg_0.l_eta,mc_bkg_0.totalEventWeight);
			t0_BkgHist[3]->Fill(mc_bkg_0.l_phi,mc_bkg_0.totalEventWeight);
			t0_BkgHist[4]->Fill(mc_bkg_0.pfMET,mc_bkg_0.totalEventWeight);
			t0_BkgHist[5]->Fill(mc_bkg_0.vbf_maxpt_j1_pt,mc_bkg_0.totalEventWeight);
			t0_BkgHist[6]->Fill(mc_bkg_0.vbf_maxpt_j2_pt,mc_bkg_0.totalEventWeight);
			t0_BkgHist[7]->Fill(mc_bkg_0.vbf_maxpt_j1_eta,mc_bkg_0.totalEventWeight);
			t0_BkgHist[8]->Fill(mc_bkg_0.vbf_maxpt_j2_eta,mc_bkg_0.totalEventWeight);
			t0_BkgHist[9]->Fill(mc_bkg_0.AK4_jet1_pt,mc_bkg_0.totalEventWeight);
			t0_BkgHist[10]->Fill(mc_bkg_0.AK4_jet2_pt,mc_bkg_0.totalEventWeight);
			t0_BkgHist[11]->Fill(mc_bkg_0.AK4_jet1_eta,mc_bkg_0.totalEventWeight);
			t0_BkgHist[12]->Fill(mc_bkg_0.AK4_jet2_eta,mc_bkg_0.totalEventWeight);
			t0_BkgHist[13]->Fill(mc_bkg_0.vbf_maxpt_jj_m,mc_bkg_0.totalEventWeight);
			t0_BkgHist[14]->Fill(mc_bkg_0.vbf_maxpt_jj_pt,mc_bkg_0.totalEventWeight);
			t0_BkgHist[15]->Fill(mc_bkg_0.AK4_jetjet_mass,mc_bkg_0.totalEventWeight);
			t0_BkgHist[16]->Fill(mc_bkg_0.AK4_jetjet_pt,mc_bkg_0.totalEventWeight);
			t0_BkgHist[17]->Fill(mc_bkg_0.AK4_jetjet_deltaeta,mc_bkg_0.totalEventWeight);
			t0_BkgHist[18]->Fill(mc_bkg_0.v_mt,mc_bkg_0.totalEventWeight);
			t0_BkgHist[19]->Fill(mc_bkg_0.v_pt,mc_bkg_0.totalEventWeight);
			t0_BkgHist[20]->Fill(mc_bkg_0.mass_lvjj_type0_AK4,mc_bkg_0.totalEventWeight);
			t0_BkgHist[21]->Fill(mc_bkg_0.deltaR_lak4jetjet,mc_bkg_0.totalEventWeight);
			t0_BkgHist[22]->Fill(mc_bkg_0.deltaphi_METak4jetjet,mc_bkg_0.totalEventWeight);
			t0_BkgHist[23]->Fill(mc_bkg_0.deltaphi_Vak4jetjet,mc_bkg_0.totalEventWeight);
			t0_BkgHist[24]->Fill(mc_bkg_0.njets,mc_bkg_0.totalEventWeight);
			t0_BkgHist[25]->Fill(mc_bkg_0.nVBFPairs,mc_bkg_0.totalEventWeight);
			}
		}


	TChain* t1_mc_bkg = new TChain("otree");
		t1_mc_bkg->Add("/afs/cern.ch/user/r/rasharma/work/aQGC_Studies/SecondStep_WWTrees/CMSSW_8_0_11/src/LepAJet_NoCutJet/copy_toRunDYEle/WWAnalysisRun2/output/output_el/WWTree_WZ_excl.root");
		ClassReadTree mc_bkg_1(t1_mc_bkg);
		for(int iEv_1_mc_bkg=0;iEv_1_mc_bkg < t1_mc_bkg->GetEntries();iEv_1_mc_bkg++){
			t1_mc_bkg->GetEntry(iEv_1_mc_bkg);
			if (mc_bkg_1.pfMET>40 && mc_bkg_1.isVBFJet==1 &&( mc_bkg_1.vbf_maxpt_j1_bDiscriminatorCSV>0.935 ||  mc_bkg_1.vbf_maxpt_j2_bDiscriminatorCSV>0.935 ) )
			{
			t1_BkgHist[0]->Fill(mc_bkg_1.nPV,mc_bkg_1.totalEventWeight);
			t1_BkgHist[1]->Fill(mc_bkg_1.l_pt,mc_bkg_1.totalEventWeight);
			t1_BkgHist[2]->Fill(mc_bkg_1.l_eta,mc_bkg_1.totalEventWeight);
			t1_BkgHist[3]->Fill(mc_bkg_1.l_phi,mc_bkg_1.totalEventWeight);
			t1_BkgHist[4]->Fill(mc_bkg_1.pfMET,mc_bkg_1.totalEventWeight);
			t1_BkgHist[5]->Fill(mc_bkg_1.vbf_maxpt_j1_pt,mc_bkg_1.totalEventWeight);
			t1_BkgHist[6]->Fill(mc_bkg_1.vbf_maxpt_j2_pt,mc_bkg_1.totalEventWeight);
			t1_BkgHist[7]->Fill(mc_bkg_1.vbf_maxpt_j1_eta,mc_bkg_1.totalEventWeight);
			t1_BkgHist[8]->Fill(mc_bkg_1.vbf_maxpt_j2_eta,mc_bkg_1.totalEventWeight);
			t1_BkgHist[9]->Fill(mc_bkg_1.AK4_jet1_pt,mc_bkg_1.totalEventWeight);
			t1_BkgHist[10]->Fill(mc_bkg_1.AK4_jet2_pt,mc_bkg_1.totalEventWeight);
			t1_BkgHist[11]->Fill(mc_bkg_1.AK4_jet1_eta,mc_bkg_1.totalEventWeight);
			t1_BkgHist[12]->Fill(mc_bkg_1.AK4_jet2_eta,mc_bkg_1.totalEventWeight);
			t1_BkgHist[13]->Fill(mc_bkg_1.vbf_maxpt_jj_m,mc_bkg_1.totalEventWeight);
			t1_BkgHist[14]->Fill(mc_bkg_1.vbf_maxpt_jj_pt,mc_bkg_1.totalEventWeight);
			t1_BkgHist[15]->Fill(mc_bkg_1.AK4_jetjet_mass,mc_bkg_1.totalEventWeight);
			t1_BkgHist[16]->Fill(mc_bkg_1.AK4_jetjet_pt,mc_bkg_1.totalEventWeight);
			t1_BkgHist[17]->Fill(mc_bkg_1.AK4_jetjet_deltaeta,mc_bkg_1.totalEventWeight);
			t1_BkgHist[18]->Fill(mc_bkg_1.v_mt,mc_bkg_1.totalEventWeight);
			t1_BkgHist[19]->Fill(mc_bkg_1.v_pt,mc_bkg_1.totalEventWeight);
			t1_BkgHist[20]->Fill(mc_bkg_1.mass_lvjj_type0_AK4,mc_bkg_1.totalEventWeight);
			t1_BkgHist[21]->Fill(mc_bkg_1.deltaR_lak4jetjet,mc_bkg_1.totalEventWeight);
			t1_BkgHist[22]->Fill(mc_bkg_1.deltaphi_METak4jetjet,mc_bkg_1.totalEventWeight);
			t1_BkgHist[23]->Fill(mc_bkg_1.deltaphi_Vak4jetjet,mc_bkg_1.totalEventWeight);
			t1_BkgHist[24]->Fill(mc_bkg_1.njets,mc_bkg_1.totalEventWeight);
			t1_BkgHist[25]->Fill(mc_bkg_1.nVBFPairs,mc_bkg_1.totalEventWeight);
			}
		}


	TChain* t2_mc_bkg = new TChain("otree");
		t2_mc_bkg->Add("/afs/cern.ch/user/r/rasharma/work/aQGC_Studies/SecondStep_WWTrees/CMSSW_8_0_11/src/LepAJet_NoCutJet/copy_toRunDYEle/WWAnalysisRun2/output/output_el/WWTree_ZZ_excl.root");
		ClassReadTree mc_bkg_2(t2_mc_bkg);
		for(int iEv_2_mc_bkg=0;iEv_2_mc_bkg < t2_mc_bkg->GetEntries();iEv_2_mc_bkg++){
			t2_mc_bkg->GetEntry(iEv_2_mc_bkg);
			if (mc_bkg_2.pfMET>40 && mc_bkg_2.isVBFJet==1 &&( mc_bkg_2.vbf_maxpt_j1_bDiscriminatorCSV>0.935 ||  mc_bkg_2.vbf_maxpt_j2_bDiscriminatorCSV>0.935 ) )
			{
			t2_BkgHist[0]->Fill(mc_bkg_2.nPV,mc_bkg_2.totalEventWeight);
			t2_BkgHist[1]->Fill(mc_bkg_2.l_pt,mc_bkg_2.totalEventWeight);
			t2_BkgHist[2]->Fill(mc_bkg_2.l_eta,mc_bkg_2.totalEventWeight);
			t2_BkgHist[3]->Fill(mc_bkg_2.l_phi,mc_bkg_2.totalEventWeight);
			t2_BkgHist[4]->Fill(mc_bkg_2.pfMET,mc_bkg_2.totalEventWeight);
			t2_BkgHist[5]->Fill(mc_bkg_2.vbf_maxpt_j1_pt,mc_bkg_2.totalEventWeight);
			t2_BkgHist[6]->Fill(mc_bkg_2.vbf_maxpt_j2_pt,mc_bkg_2.totalEventWeight);
			t2_BkgHist[7]->Fill(mc_bkg_2.vbf_maxpt_j1_eta,mc_bkg_2.totalEventWeight);
			t2_BkgHist[8]->Fill(mc_bkg_2.vbf_maxpt_j2_eta,mc_bkg_2.totalEventWeight);
			t2_BkgHist[9]->Fill(mc_bkg_2.AK4_jet1_pt,mc_bkg_2.totalEventWeight);
			t2_BkgHist[10]->Fill(mc_bkg_2.AK4_jet2_pt,mc_bkg_2.totalEventWeight);
			t2_BkgHist[11]->Fill(mc_bkg_2.AK4_jet1_eta,mc_bkg_2.totalEventWeight);
			t2_BkgHist[12]->Fill(mc_bkg_2.AK4_jet2_eta,mc_bkg_2.totalEventWeight);
			t2_BkgHist[13]->Fill(mc_bkg_2.vbf_maxpt_jj_m,mc_bkg_2.totalEventWeight);
			t2_BkgHist[14]->Fill(mc_bkg_2.vbf_maxpt_jj_pt,mc_bkg_2.totalEventWeight);
			t2_BkgHist[15]->Fill(mc_bkg_2.AK4_jetjet_mass,mc_bkg_2.totalEventWeight);
			t2_BkgHist[16]->Fill(mc_bkg_2.AK4_jetjet_pt,mc_bkg_2.totalEventWeight);
			t2_BkgHist[17]->Fill(mc_bkg_2.AK4_jetjet_deltaeta,mc_bkg_2.totalEventWeight);
			t2_BkgHist[18]->Fill(mc_bkg_2.v_mt,mc_bkg_2.totalEventWeight);
			t2_BkgHist[19]->Fill(mc_bkg_2.v_pt,mc_bkg_2.totalEventWeight);
			t2_BkgHist[20]->Fill(mc_bkg_2.mass_lvjj_type0_AK4,mc_bkg_2.totalEventWeight);
			t2_BkgHist[21]->Fill(mc_bkg_2.deltaR_lak4jetjet,mc_bkg_2.totalEventWeight);
			t2_BkgHist[22]->Fill(mc_bkg_2.deltaphi_METak4jetjet,mc_bkg_2.totalEventWeight);
			t2_BkgHist[23]->Fill(mc_bkg_2.deltaphi_Vak4jetjet,mc_bkg_2.totalEventWeight);
			t2_BkgHist[24]->Fill(mc_bkg_2.njets,mc_bkg_2.totalEventWeight);
			t2_BkgHist[25]->Fill(mc_bkg_2.nVBFPairs,mc_bkg_2.totalEventWeight);
			}
		}


	TChain* t3_mc_bkg = new TChain("otree");
		t3_mc_bkg->Add("/afs/cern.ch/user/r/rasharma/work/aQGC_Studies/SecondStep_WWTrees/CMSSW_8_0_11/src/LepAJet_NoCutJet/copy_toRunDYEle/WWAnalysisRun2/output/output_el/WWTree_tWch.root");
		ClassReadTree mc_bkg_3(t3_mc_bkg);
		for(int iEv_3_mc_bkg=0;iEv_3_mc_bkg < t3_mc_bkg->GetEntries();iEv_3_mc_bkg++){
			t3_mc_bkg->GetEntry(iEv_3_mc_bkg);
			if (mc_bkg_3.pfMET>40 && mc_bkg_3.isVBFJet==1 &&( mc_bkg_3.vbf_maxpt_j1_bDiscriminatorCSV>0.935 ||  mc_bkg_3.vbf_maxpt_j2_bDiscriminatorCSV>0.935 ) )
			{
			t3_BkgHist[0]->Fill(mc_bkg_3.nPV,mc_bkg_3.totalEventWeight);
			t3_BkgHist[1]->Fill(mc_bkg_3.l_pt,mc_bkg_3.totalEventWeight);
			t3_BkgHist[2]->Fill(mc_bkg_3.l_eta,mc_bkg_3.totalEventWeight);
			t3_BkgHist[3]->Fill(mc_bkg_3.l_phi,mc_bkg_3.totalEventWeight);
			t3_BkgHist[4]->Fill(mc_bkg_3.pfMET,mc_bkg_3.totalEventWeight);
			t3_BkgHist[5]->Fill(mc_bkg_3.vbf_maxpt_j1_pt,mc_bkg_3.totalEventWeight);
			t3_BkgHist[6]->Fill(mc_bkg_3.vbf_maxpt_j2_pt,mc_bkg_3.totalEventWeight);
			t3_BkgHist[7]->Fill(mc_bkg_3.vbf_maxpt_j1_eta,mc_bkg_3.totalEventWeight);
			t3_BkgHist[8]->Fill(mc_bkg_3.vbf_maxpt_j2_eta,mc_bkg_3.totalEventWeight);
			t3_BkgHist[9]->Fill(mc_bkg_3.AK4_jet1_pt,mc_bkg_3.totalEventWeight);
			t3_BkgHist[10]->Fill(mc_bkg_3.AK4_jet2_pt,mc_bkg_3.totalEventWeight);
			t3_BkgHist[11]->Fill(mc_bkg_3.AK4_jet1_eta,mc_bkg_3.totalEventWeight);
			t3_BkgHist[12]->Fill(mc_bkg_3.AK4_jet2_eta,mc_bkg_3.totalEventWeight);
			t3_BkgHist[13]->Fill(mc_bkg_3.vbf_maxpt_jj_m,mc_bkg_3.totalEventWeight);
			t3_BkgHist[14]->Fill(mc_bkg_3.vbf_maxpt_jj_pt,mc_bkg_3.totalEventWeight);
			t3_BkgHist[15]->Fill(mc_bkg_3.AK4_jetjet_mass,mc_bkg_3.totalEventWeight);
			t3_BkgHist[16]->Fill(mc_bkg_3.AK4_jetjet_pt,mc_bkg_3.totalEventWeight);
			t3_BkgHist[17]->Fill(mc_bkg_3.AK4_jetjet_deltaeta,mc_bkg_3.totalEventWeight);
			t3_BkgHist[18]->Fill(mc_bkg_3.v_mt,mc_bkg_3.totalEventWeight);
			t3_BkgHist[19]->Fill(mc_bkg_3.v_pt,mc_bkg_3.totalEventWeight);
			t3_BkgHist[20]->Fill(mc_bkg_3.mass_lvjj_type0_AK4,mc_bkg_3.totalEventWeight);
			t3_BkgHist[21]->Fill(mc_bkg_3.deltaR_lak4jetjet,mc_bkg_3.totalEventWeight);
			t3_BkgHist[22]->Fill(mc_bkg_3.deltaphi_METak4jetjet,mc_bkg_3.totalEventWeight);
			t3_BkgHist[23]->Fill(mc_bkg_3.deltaphi_Vak4jetjet,mc_bkg_3.totalEventWeight);
			t3_BkgHist[24]->Fill(mc_bkg_3.njets,mc_bkg_3.totalEventWeight);
			t3_BkgHist[25]->Fill(mc_bkg_3.nVBFPairs,mc_bkg_3.totalEventWeight);
			}
		}


	TChain* t4_mc_bkg = new TChain("otree");
		t4_mc_bkg->Add("/afs/cern.ch/user/r/rasharma/work/aQGC_Studies/SecondStep_WWTrees/CMSSW_8_0_11/src/LepAJet_NoCutJet/copy_toRunDYEle/WWAnalysisRun2/output/output_el/WWTree_tWch_bar.root");
		ClassReadTree mc_bkg_4(t4_mc_bkg);
		for(int iEv_4_mc_bkg=0;iEv_4_mc_bkg < t4_mc_bkg->GetEntries();iEv_4_mc_bkg++){
			t4_mc_bkg->GetEntry(iEv_4_mc_bkg);
			if (mc_bkg_4.pfMET>40 && mc_bkg_4.isVBFJet==1 &&( mc_bkg_4.vbf_maxpt_j1_bDiscriminatorCSV>0.935 ||  mc_bkg_4.vbf_maxpt_j2_bDiscriminatorCSV>0.935 ) )
			{
			t4_BkgHist[0]->Fill(mc_bkg_4.nPV,mc_bkg_4.totalEventWeight);
			t4_BkgHist[1]->Fill(mc_bkg_4.l_pt,mc_bkg_4.totalEventWeight);
			t4_BkgHist[2]->Fill(mc_bkg_4.l_eta,mc_bkg_4.totalEventWeight);
			t4_BkgHist[3]->Fill(mc_bkg_4.l_phi,mc_bkg_4.totalEventWeight);
			t4_BkgHist[4]->Fill(mc_bkg_4.pfMET,mc_bkg_4.totalEventWeight);
			t4_BkgHist[5]->Fill(mc_bkg_4.vbf_maxpt_j1_pt,mc_bkg_4.totalEventWeight);
			t4_BkgHist[6]->Fill(mc_bkg_4.vbf_maxpt_j2_pt,mc_bkg_4.totalEventWeight);
			t4_BkgHist[7]->Fill(mc_bkg_4.vbf_maxpt_j1_eta,mc_bkg_4.totalEventWeight);
			t4_BkgHist[8]->Fill(mc_bkg_4.vbf_maxpt_j2_eta,mc_bkg_4.totalEventWeight);
			t4_BkgHist[9]->Fill(mc_bkg_4.AK4_jet1_pt,mc_bkg_4.totalEventWeight);
			t4_BkgHist[10]->Fill(mc_bkg_4.AK4_jet2_pt,mc_bkg_4.totalEventWeight);
			t4_BkgHist[11]->Fill(mc_bkg_4.AK4_jet1_eta,mc_bkg_4.totalEventWeight);
			t4_BkgHist[12]->Fill(mc_bkg_4.AK4_jet2_eta,mc_bkg_4.totalEventWeight);
			t4_BkgHist[13]->Fill(mc_bkg_4.vbf_maxpt_jj_m,mc_bkg_4.totalEventWeight);
			t4_BkgHist[14]->Fill(mc_bkg_4.vbf_maxpt_jj_pt,mc_bkg_4.totalEventWeight);
			t4_BkgHist[15]->Fill(mc_bkg_4.AK4_jetjet_mass,mc_bkg_4.totalEventWeight);
			t4_BkgHist[16]->Fill(mc_bkg_4.AK4_jetjet_pt,mc_bkg_4.totalEventWeight);
			t4_BkgHist[17]->Fill(mc_bkg_4.AK4_jetjet_deltaeta,mc_bkg_4.totalEventWeight);
			t4_BkgHist[18]->Fill(mc_bkg_4.v_mt,mc_bkg_4.totalEventWeight);
			t4_BkgHist[19]->Fill(mc_bkg_4.v_pt,mc_bkg_4.totalEventWeight);
			t4_BkgHist[20]->Fill(mc_bkg_4.mass_lvjj_type0_AK4,mc_bkg_4.totalEventWeight);
			t4_BkgHist[21]->Fill(mc_bkg_4.deltaR_lak4jetjet,mc_bkg_4.totalEventWeight);
			t4_BkgHist[22]->Fill(mc_bkg_4.deltaphi_METak4jetjet,mc_bkg_4.totalEventWeight);
			t4_BkgHist[23]->Fill(mc_bkg_4.deltaphi_Vak4jetjet,mc_bkg_4.totalEventWeight);
			t4_BkgHist[24]->Fill(mc_bkg_4.njets,mc_bkg_4.totalEventWeight);
			t4_BkgHist[25]->Fill(mc_bkg_4.nVBFPairs,mc_bkg_4.totalEventWeight);
			}
		}


	TChain* t5_mc_bkg = new TChain("otree");
		t5_mc_bkg->Add("/afs/cern.ch/user/r/rasharma/work/aQGC_Studies/SecondStep_WWTrees/CMSSW_8_0_11/src/LepAJet_NoCutJet/copy_toRunDYEle/WWAnalysisRun2/output/output_el/WWTree_tch_bar.root");
		ClassReadTree mc_bkg_5(t5_mc_bkg);
		for(int iEv_5_mc_bkg=0;iEv_5_mc_bkg < t5_mc_bkg->GetEntries();iEv_5_mc_bkg++){
			t5_mc_bkg->GetEntry(iEv_5_mc_bkg);
			if (mc_bkg_5.pfMET>40 && mc_bkg_5.isVBFJet==1 &&( mc_bkg_5.vbf_maxpt_j1_bDiscriminatorCSV>0.935 ||  mc_bkg_5.vbf_maxpt_j2_bDiscriminatorCSV>0.935 ) )
			{
			t5_BkgHist[0]->Fill(mc_bkg_5.nPV,mc_bkg_5.totalEventWeight);
			t5_BkgHist[1]->Fill(mc_bkg_5.l_pt,mc_bkg_5.totalEventWeight);
			t5_BkgHist[2]->Fill(mc_bkg_5.l_eta,mc_bkg_5.totalEventWeight);
			t5_BkgHist[3]->Fill(mc_bkg_5.l_phi,mc_bkg_5.totalEventWeight);
			t5_BkgHist[4]->Fill(mc_bkg_5.pfMET,mc_bkg_5.totalEventWeight);
			t5_BkgHist[5]->Fill(mc_bkg_5.vbf_maxpt_j1_pt,mc_bkg_5.totalEventWeight);
			t5_BkgHist[6]->Fill(mc_bkg_5.vbf_maxpt_j2_pt,mc_bkg_5.totalEventWeight);
			t5_BkgHist[7]->Fill(mc_bkg_5.vbf_maxpt_j1_eta,mc_bkg_5.totalEventWeight);
			t5_BkgHist[8]->Fill(mc_bkg_5.vbf_maxpt_j2_eta,mc_bkg_5.totalEventWeight);
			t5_BkgHist[9]->Fill(mc_bkg_5.AK4_jet1_pt,mc_bkg_5.totalEventWeight);
			t5_BkgHist[10]->Fill(mc_bkg_5.AK4_jet2_pt,mc_bkg_5.totalEventWeight);
			t5_BkgHist[11]->Fill(mc_bkg_5.AK4_jet1_eta,mc_bkg_5.totalEventWeight);
			t5_BkgHist[12]->Fill(mc_bkg_5.AK4_jet2_eta,mc_bkg_5.totalEventWeight);
			t5_BkgHist[13]->Fill(mc_bkg_5.vbf_maxpt_jj_m,mc_bkg_5.totalEventWeight);
			t5_BkgHist[14]->Fill(mc_bkg_5.vbf_maxpt_jj_pt,mc_bkg_5.totalEventWeight);
			t5_BkgHist[15]->Fill(mc_bkg_5.AK4_jetjet_mass,mc_bkg_5.totalEventWeight);
			t5_BkgHist[16]->Fill(mc_bkg_5.AK4_jetjet_pt,mc_bkg_5.totalEventWeight);
			t5_BkgHist[17]->Fill(mc_bkg_5.AK4_jetjet_deltaeta,mc_bkg_5.totalEventWeight);
			t5_BkgHist[18]->Fill(mc_bkg_5.v_mt,mc_bkg_5.totalEventWeight);
			t5_BkgHist[19]->Fill(mc_bkg_5.v_pt,mc_bkg_5.totalEventWeight);
			t5_BkgHist[20]->Fill(mc_bkg_5.mass_lvjj_type0_AK4,mc_bkg_5.totalEventWeight);
			t5_BkgHist[21]->Fill(mc_bkg_5.deltaR_lak4jetjet,mc_bkg_5.totalEventWeight);
			t5_BkgHist[22]->Fill(mc_bkg_5.deltaphi_METak4jetjet,mc_bkg_5.totalEventWeight);
			t5_BkgHist[23]->Fill(mc_bkg_5.deltaphi_Vak4jetjet,mc_bkg_5.totalEventWeight);
			t5_BkgHist[24]->Fill(mc_bkg_5.njets,mc_bkg_5.totalEventWeight);
			t5_BkgHist[25]->Fill(mc_bkg_5.nVBFPairs,mc_bkg_5.totalEventWeight);
			}
		}


	TChain* t6_mc_bkg = new TChain("otree");
		t6_mc_bkg->Add("/afs/cern.ch/user/r/rasharma/work/aQGC_Studies/SecondStep_WWTrees/CMSSW_8_0_11/src/LepAJet_NoCutJet/copy_toRunDYEle/WWAnalysisRun2/output/output_el/WWTree_sch.root");
		ClassReadTree mc_bkg_6(t6_mc_bkg);
		for(int iEv_6_mc_bkg=0;iEv_6_mc_bkg < t6_mc_bkg->GetEntries();iEv_6_mc_bkg++){
			t6_mc_bkg->GetEntry(iEv_6_mc_bkg);
			if (mc_bkg_6.pfMET>40 && mc_bkg_6.isVBFJet==1 &&( mc_bkg_6.vbf_maxpt_j1_bDiscriminatorCSV>0.935 ||  mc_bkg_6.vbf_maxpt_j2_bDiscriminatorCSV>0.935 ) )
			{
			t6_BkgHist[0]->Fill(mc_bkg_6.nPV,mc_bkg_6.totalEventWeight);
			t6_BkgHist[1]->Fill(mc_bkg_6.l_pt,mc_bkg_6.totalEventWeight);
			t6_BkgHist[2]->Fill(mc_bkg_6.l_eta,mc_bkg_6.totalEventWeight);
			t6_BkgHist[3]->Fill(mc_bkg_6.l_phi,mc_bkg_6.totalEventWeight);
			t6_BkgHist[4]->Fill(mc_bkg_6.pfMET,mc_bkg_6.totalEventWeight);
			t6_BkgHist[5]->Fill(mc_bkg_6.vbf_maxpt_j1_pt,mc_bkg_6.totalEventWeight);
			t6_BkgHist[6]->Fill(mc_bkg_6.vbf_maxpt_j2_pt,mc_bkg_6.totalEventWeight);
			t6_BkgHist[7]->Fill(mc_bkg_6.vbf_maxpt_j1_eta,mc_bkg_6.totalEventWeight);
			t6_BkgHist[8]->Fill(mc_bkg_6.vbf_maxpt_j2_eta,mc_bkg_6.totalEventWeight);
			t6_BkgHist[9]->Fill(mc_bkg_6.AK4_jet1_pt,mc_bkg_6.totalEventWeight);
			t6_BkgHist[10]->Fill(mc_bkg_6.AK4_jet2_pt,mc_bkg_6.totalEventWeight);
			t6_BkgHist[11]->Fill(mc_bkg_6.AK4_jet1_eta,mc_bkg_6.totalEventWeight);
			t6_BkgHist[12]->Fill(mc_bkg_6.AK4_jet2_eta,mc_bkg_6.totalEventWeight);
			t6_BkgHist[13]->Fill(mc_bkg_6.vbf_maxpt_jj_m,mc_bkg_6.totalEventWeight);
			t6_BkgHist[14]->Fill(mc_bkg_6.vbf_maxpt_jj_pt,mc_bkg_6.totalEventWeight);
			t6_BkgHist[15]->Fill(mc_bkg_6.AK4_jetjet_mass,mc_bkg_6.totalEventWeight);
			t6_BkgHist[16]->Fill(mc_bkg_6.AK4_jetjet_pt,mc_bkg_6.totalEventWeight);
			t6_BkgHist[17]->Fill(mc_bkg_6.AK4_jetjet_deltaeta,mc_bkg_6.totalEventWeight);
			t6_BkgHist[18]->Fill(mc_bkg_6.v_mt,mc_bkg_6.totalEventWeight);
			t6_BkgHist[19]->Fill(mc_bkg_6.v_pt,mc_bkg_6.totalEventWeight);
			t6_BkgHist[20]->Fill(mc_bkg_6.mass_lvjj_type0_AK4,mc_bkg_6.totalEventWeight);
			t6_BkgHist[21]->Fill(mc_bkg_6.deltaR_lak4jetjet,mc_bkg_6.totalEventWeight);
			t6_BkgHist[22]->Fill(mc_bkg_6.deltaphi_METak4jetjet,mc_bkg_6.totalEventWeight);
			t6_BkgHist[23]->Fill(mc_bkg_6.deltaphi_Vak4jetjet,mc_bkg_6.totalEventWeight);
			t6_BkgHist[24]->Fill(mc_bkg_6.njets,mc_bkg_6.totalEventWeight);
			t6_BkgHist[25]->Fill(mc_bkg_6.nVBFPairs,mc_bkg_6.totalEventWeight);
			}
		}


	TChain* t7_mc_bkg = new TChain("otree");
		t7_mc_bkg->Add("/afs/cern.ch/user/r/rasharma/work/aQGC_Studies/SecondStep_WWTrees/CMSSW_8_0_11/src/LepAJet_NoCutJet/copy_toRunDYEle/WWAnalysisRun2/output/output_el/WWTree_WJets100.root");
		ClassReadTree mc_bkg_7(t7_mc_bkg);
		for(int iEv_7_mc_bkg=0;iEv_7_mc_bkg < t7_mc_bkg->GetEntries();iEv_7_mc_bkg++){
			t7_mc_bkg->GetEntry(iEv_7_mc_bkg);
			if (mc_bkg_7.pfMET>40 && mc_bkg_7.isVBFJet==1 &&( mc_bkg_7.vbf_maxpt_j1_bDiscriminatorCSV>0.935 ||  mc_bkg_7.vbf_maxpt_j2_bDiscriminatorCSV>0.935 ) )
			{
			t7_BkgHist[0]->Fill(mc_bkg_7.nPV,mc_bkg_7.totalEventWeight);
			t7_BkgHist[1]->Fill(mc_bkg_7.l_pt,mc_bkg_7.totalEventWeight);
			t7_BkgHist[2]->Fill(mc_bkg_7.l_eta,mc_bkg_7.totalEventWeight);
			t7_BkgHist[3]->Fill(mc_bkg_7.l_phi,mc_bkg_7.totalEventWeight);
			t7_BkgHist[4]->Fill(mc_bkg_7.pfMET,mc_bkg_7.totalEventWeight);
			t7_BkgHist[5]->Fill(mc_bkg_7.vbf_maxpt_j1_pt,mc_bkg_7.totalEventWeight);
			t7_BkgHist[6]->Fill(mc_bkg_7.vbf_maxpt_j2_pt,mc_bkg_7.totalEventWeight);
			t7_BkgHist[7]->Fill(mc_bkg_7.vbf_maxpt_j1_eta,mc_bkg_7.totalEventWeight);
			t7_BkgHist[8]->Fill(mc_bkg_7.vbf_maxpt_j2_eta,mc_bkg_7.totalEventWeight);
			t7_BkgHist[9]->Fill(mc_bkg_7.AK4_jet1_pt,mc_bkg_7.totalEventWeight);
			t7_BkgHist[10]->Fill(mc_bkg_7.AK4_jet2_pt,mc_bkg_7.totalEventWeight);
			t7_BkgHist[11]->Fill(mc_bkg_7.AK4_jet1_eta,mc_bkg_7.totalEventWeight);
			t7_BkgHist[12]->Fill(mc_bkg_7.AK4_jet2_eta,mc_bkg_7.totalEventWeight);
			t7_BkgHist[13]->Fill(mc_bkg_7.vbf_maxpt_jj_m,mc_bkg_7.totalEventWeight);
			t7_BkgHist[14]->Fill(mc_bkg_7.vbf_maxpt_jj_pt,mc_bkg_7.totalEventWeight);
			t7_BkgHist[15]->Fill(mc_bkg_7.AK4_jetjet_mass,mc_bkg_7.totalEventWeight);
			t7_BkgHist[16]->Fill(mc_bkg_7.AK4_jetjet_pt,mc_bkg_7.totalEventWeight);
			t7_BkgHist[17]->Fill(mc_bkg_7.AK4_jetjet_deltaeta,mc_bkg_7.totalEventWeight);
			t7_BkgHist[18]->Fill(mc_bkg_7.v_mt,mc_bkg_7.totalEventWeight);
			t7_BkgHist[19]->Fill(mc_bkg_7.v_pt,mc_bkg_7.totalEventWeight);
			t7_BkgHist[20]->Fill(mc_bkg_7.mass_lvjj_type0_AK4,mc_bkg_7.totalEventWeight);
			t7_BkgHist[21]->Fill(mc_bkg_7.deltaR_lak4jetjet,mc_bkg_7.totalEventWeight);
			t7_BkgHist[22]->Fill(mc_bkg_7.deltaphi_METak4jetjet,mc_bkg_7.totalEventWeight);
			t7_BkgHist[23]->Fill(mc_bkg_7.deltaphi_Vak4jetjet,mc_bkg_7.totalEventWeight);
			t7_BkgHist[24]->Fill(mc_bkg_7.njets,mc_bkg_7.totalEventWeight);
			t7_BkgHist[25]->Fill(mc_bkg_7.nVBFPairs,mc_bkg_7.totalEventWeight);
			}
		}


	TChain* t8_mc_bkg = new TChain("otree");
		t8_mc_bkg->Add("/afs/cern.ch/user/r/rasharma/work/aQGC_Studies/SecondStep_WWTrees/CMSSW_8_0_11/src/LepAJet_NoCutJet/copy_toRunDYEle/WWAnalysisRun2/output/output_el/WWTree_WJets200.root");
		ClassReadTree mc_bkg_8(t8_mc_bkg);
		for(int iEv_8_mc_bkg=0;iEv_8_mc_bkg < t8_mc_bkg->GetEntries();iEv_8_mc_bkg++){
			t8_mc_bkg->GetEntry(iEv_8_mc_bkg);
			if (mc_bkg_8.pfMET>40 && mc_bkg_8.isVBFJet==1 &&( mc_bkg_8.vbf_maxpt_j1_bDiscriminatorCSV>0.935 ||  mc_bkg_8.vbf_maxpt_j2_bDiscriminatorCSV>0.935 ) )
			{
			t8_BkgHist[0]->Fill(mc_bkg_8.nPV,mc_bkg_8.totalEventWeight);
			t8_BkgHist[1]->Fill(mc_bkg_8.l_pt,mc_bkg_8.totalEventWeight);
			t8_BkgHist[2]->Fill(mc_bkg_8.l_eta,mc_bkg_8.totalEventWeight);
			t8_BkgHist[3]->Fill(mc_bkg_8.l_phi,mc_bkg_8.totalEventWeight);
			t8_BkgHist[4]->Fill(mc_bkg_8.pfMET,mc_bkg_8.totalEventWeight);
			t8_BkgHist[5]->Fill(mc_bkg_8.vbf_maxpt_j1_pt,mc_bkg_8.totalEventWeight);
			t8_BkgHist[6]->Fill(mc_bkg_8.vbf_maxpt_j2_pt,mc_bkg_8.totalEventWeight);
			t8_BkgHist[7]->Fill(mc_bkg_8.vbf_maxpt_j1_eta,mc_bkg_8.totalEventWeight);
			t8_BkgHist[8]->Fill(mc_bkg_8.vbf_maxpt_j2_eta,mc_bkg_8.totalEventWeight);
			t8_BkgHist[9]->Fill(mc_bkg_8.AK4_jet1_pt,mc_bkg_8.totalEventWeight);
			t8_BkgHist[10]->Fill(mc_bkg_8.AK4_jet2_pt,mc_bkg_8.totalEventWeight);
			t8_BkgHist[11]->Fill(mc_bkg_8.AK4_jet1_eta,mc_bkg_8.totalEventWeight);
			t8_BkgHist[12]->Fill(mc_bkg_8.AK4_jet2_eta,mc_bkg_8.totalEventWeight);
			t8_BkgHist[13]->Fill(mc_bkg_8.vbf_maxpt_jj_m,mc_bkg_8.totalEventWeight);
			t8_BkgHist[14]->Fill(mc_bkg_8.vbf_maxpt_jj_pt,mc_bkg_8.totalEventWeight);
			t8_BkgHist[15]->Fill(mc_bkg_8.AK4_jetjet_mass,mc_bkg_8.totalEventWeight);
			t8_BkgHist[16]->Fill(mc_bkg_8.AK4_jetjet_pt,mc_bkg_8.totalEventWeight);
			t8_BkgHist[17]->Fill(mc_bkg_8.AK4_jetjet_deltaeta,mc_bkg_8.totalEventWeight);
			t8_BkgHist[18]->Fill(mc_bkg_8.v_mt,mc_bkg_8.totalEventWeight);
			t8_BkgHist[19]->Fill(mc_bkg_8.v_pt,mc_bkg_8.totalEventWeight);
			t8_BkgHist[20]->Fill(mc_bkg_8.mass_lvjj_type0_AK4,mc_bkg_8.totalEventWeight);
			t8_BkgHist[21]->Fill(mc_bkg_8.deltaR_lak4jetjet,mc_bkg_8.totalEventWeight);
			t8_BkgHist[22]->Fill(mc_bkg_8.deltaphi_METak4jetjet,mc_bkg_8.totalEventWeight);
			t8_BkgHist[23]->Fill(mc_bkg_8.deltaphi_Vak4jetjet,mc_bkg_8.totalEventWeight);
			t8_BkgHist[24]->Fill(mc_bkg_8.njets,mc_bkg_8.totalEventWeight);
			t8_BkgHist[25]->Fill(mc_bkg_8.nVBFPairs,mc_bkg_8.totalEventWeight);
			}
		}


	TChain* t9_mc_bkg = new TChain("otree");
		t9_mc_bkg->Add("/afs/cern.ch/user/r/rasharma/work/aQGC_Studies/SecondStep_WWTrees/CMSSW_8_0_11/src/LepAJet_NoCutJet/copy_toRunDYEle/WWAnalysisRun2/output/output_el/WWTree_WJets1200.root");
		ClassReadTree mc_bkg_9(t9_mc_bkg);
		for(int iEv_9_mc_bkg=0;iEv_9_mc_bkg < t9_mc_bkg->GetEntries();iEv_9_mc_bkg++){
			t9_mc_bkg->GetEntry(iEv_9_mc_bkg);
			if (mc_bkg_9.pfMET>40 && mc_bkg_9.isVBFJet==1 &&( mc_bkg_9.vbf_maxpt_j1_bDiscriminatorCSV>0.935 ||  mc_bkg_9.vbf_maxpt_j2_bDiscriminatorCSV>0.935 ) )
			{
			t9_BkgHist[0]->Fill(mc_bkg_9.nPV,mc_bkg_9.totalEventWeight);
			t9_BkgHist[1]->Fill(mc_bkg_9.l_pt,mc_bkg_9.totalEventWeight);
			t9_BkgHist[2]->Fill(mc_bkg_9.l_eta,mc_bkg_9.totalEventWeight);
			t9_BkgHist[3]->Fill(mc_bkg_9.l_phi,mc_bkg_9.totalEventWeight);
			t9_BkgHist[4]->Fill(mc_bkg_9.pfMET,mc_bkg_9.totalEventWeight);
			t9_BkgHist[5]->Fill(mc_bkg_9.vbf_maxpt_j1_pt,mc_bkg_9.totalEventWeight);
			t9_BkgHist[6]->Fill(mc_bkg_9.vbf_maxpt_j2_pt,mc_bkg_9.totalEventWeight);
			t9_BkgHist[7]->Fill(mc_bkg_9.vbf_maxpt_j1_eta,mc_bkg_9.totalEventWeight);
			t9_BkgHist[8]->Fill(mc_bkg_9.vbf_maxpt_j2_eta,mc_bkg_9.totalEventWeight);
			t9_BkgHist[9]->Fill(mc_bkg_9.AK4_jet1_pt,mc_bkg_9.totalEventWeight);
			t9_BkgHist[10]->Fill(mc_bkg_9.AK4_jet2_pt,mc_bkg_9.totalEventWeight);
			t9_BkgHist[11]->Fill(mc_bkg_9.AK4_jet1_eta,mc_bkg_9.totalEventWeight);
			t9_BkgHist[12]->Fill(mc_bkg_9.AK4_jet2_eta,mc_bkg_9.totalEventWeight);
			t9_BkgHist[13]->Fill(mc_bkg_9.vbf_maxpt_jj_m,mc_bkg_9.totalEventWeight);
			t9_BkgHist[14]->Fill(mc_bkg_9.vbf_maxpt_jj_pt,mc_bkg_9.totalEventWeight);
			t9_BkgHist[15]->Fill(mc_bkg_9.AK4_jetjet_mass,mc_bkg_9.totalEventWeight);
			t9_BkgHist[16]->Fill(mc_bkg_9.AK4_jetjet_pt,mc_bkg_9.totalEventWeight);
			t9_BkgHist[17]->Fill(mc_bkg_9.AK4_jetjet_deltaeta,mc_bkg_9.totalEventWeight);
			t9_BkgHist[18]->Fill(mc_bkg_9.v_mt,mc_bkg_9.totalEventWeight);
			t9_BkgHist[19]->Fill(mc_bkg_9.v_pt,mc_bkg_9.totalEventWeight);
			t9_BkgHist[20]->Fill(mc_bkg_9.mass_lvjj_type0_AK4,mc_bkg_9.totalEventWeight);
			t9_BkgHist[21]->Fill(mc_bkg_9.deltaR_lak4jetjet,mc_bkg_9.totalEventWeight);
			t9_BkgHist[22]->Fill(mc_bkg_9.deltaphi_METak4jetjet,mc_bkg_9.totalEventWeight);
			t9_BkgHist[23]->Fill(mc_bkg_9.deltaphi_Vak4jetjet,mc_bkg_9.totalEventWeight);
			t9_BkgHist[24]->Fill(mc_bkg_9.njets,mc_bkg_9.totalEventWeight);
			t9_BkgHist[25]->Fill(mc_bkg_9.nVBFPairs,mc_bkg_9.totalEventWeight);
			}
		}


	TChain* t10_mc_bkg = new TChain("otree");
		t10_mc_bkg->Add("/afs/cern.ch/user/r/rasharma/work/aQGC_Studies/SecondStep_WWTrees/CMSSW_8_0_11/src/LepAJet_NoCutJet/copy_toRunDYEle/WWAnalysisRun2/output/output_el/WWTree_WJets2500.root");
		ClassReadTree mc_bkg_10(t10_mc_bkg);
		for(int iEv_10_mc_bkg=0;iEv_10_mc_bkg < t10_mc_bkg->GetEntries();iEv_10_mc_bkg++){
			t10_mc_bkg->GetEntry(iEv_10_mc_bkg);
			if (mc_bkg_10.pfMET>40 && mc_bkg_10.isVBFJet==1 &&( mc_bkg_10.vbf_maxpt_j1_bDiscriminatorCSV>0.935 ||  mc_bkg_10.vbf_maxpt_j2_bDiscriminatorCSV>0.935 ) )
			{
			t10_BkgHist[0]->Fill(mc_bkg_10.nPV,mc_bkg_10.totalEventWeight);
			t10_BkgHist[1]->Fill(mc_bkg_10.l_pt,mc_bkg_10.totalEventWeight);
			t10_BkgHist[2]->Fill(mc_bkg_10.l_eta,mc_bkg_10.totalEventWeight);
			t10_BkgHist[3]->Fill(mc_bkg_10.l_phi,mc_bkg_10.totalEventWeight);
			t10_BkgHist[4]->Fill(mc_bkg_10.pfMET,mc_bkg_10.totalEventWeight);
			t10_BkgHist[5]->Fill(mc_bkg_10.vbf_maxpt_j1_pt,mc_bkg_10.totalEventWeight);
			t10_BkgHist[6]->Fill(mc_bkg_10.vbf_maxpt_j2_pt,mc_bkg_10.totalEventWeight);
			t10_BkgHist[7]->Fill(mc_bkg_10.vbf_maxpt_j1_eta,mc_bkg_10.totalEventWeight);
			t10_BkgHist[8]->Fill(mc_bkg_10.vbf_maxpt_j2_eta,mc_bkg_10.totalEventWeight);
			t10_BkgHist[9]->Fill(mc_bkg_10.AK4_jet1_pt,mc_bkg_10.totalEventWeight);
			t10_BkgHist[10]->Fill(mc_bkg_10.AK4_jet2_pt,mc_bkg_10.totalEventWeight);
			t10_BkgHist[11]->Fill(mc_bkg_10.AK4_jet1_eta,mc_bkg_10.totalEventWeight);
			t10_BkgHist[12]->Fill(mc_bkg_10.AK4_jet2_eta,mc_bkg_10.totalEventWeight);
			t10_BkgHist[13]->Fill(mc_bkg_10.vbf_maxpt_jj_m,mc_bkg_10.totalEventWeight);
			t10_BkgHist[14]->Fill(mc_bkg_10.vbf_maxpt_jj_pt,mc_bkg_10.totalEventWeight);
			t10_BkgHist[15]->Fill(mc_bkg_10.AK4_jetjet_mass,mc_bkg_10.totalEventWeight);
			t10_BkgHist[16]->Fill(mc_bkg_10.AK4_jetjet_pt,mc_bkg_10.totalEventWeight);
			t10_BkgHist[17]->Fill(mc_bkg_10.AK4_jetjet_deltaeta,mc_bkg_10.totalEventWeight);
			t10_BkgHist[18]->Fill(mc_bkg_10.v_mt,mc_bkg_10.totalEventWeight);
			t10_BkgHist[19]->Fill(mc_bkg_10.v_pt,mc_bkg_10.totalEventWeight);
			t10_BkgHist[20]->Fill(mc_bkg_10.mass_lvjj_type0_AK4,mc_bkg_10.totalEventWeight);
			t10_BkgHist[21]->Fill(mc_bkg_10.deltaR_lak4jetjet,mc_bkg_10.totalEventWeight);
			t10_BkgHist[22]->Fill(mc_bkg_10.deltaphi_METak4jetjet,mc_bkg_10.totalEventWeight);
			t10_BkgHist[23]->Fill(mc_bkg_10.deltaphi_Vak4jetjet,mc_bkg_10.totalEventWeight);
			t10_BkgHist[24]->Fill(mc_bkg_10.njets,mc_bkg_10.totalEventWeight);
			t10_BkgHist[25]->Fill(mc_bkg_10.nVBFPairs,mc_bkg_10.totalEventWeight);
			}
		}


	TChain* t11_mc_bkg = new TChain("otree");
		t11_mc_bkg->Add("/afs/cern.ch/user/r/rasharma/work/aQGC_Studies/SecondStep_WWTrees/CMSSW_8_0_11/src/LepAJet_NoCutJet/copy_toRunDYEle/WWAnalysisRun2/output/output_el/WWTree_WJets400.root");
		ClassReadTree mc_bkg_11(t11_mc_bkg);
		for(int iEv_11_mc_bkg=0;iEv_11_mc_bkg < t11_mc_bkg->GetEntries();iEv_11_mc_bkg++){
			t11_mc_bkg->GetEntry(iEv_11_mc_bkg);
			if (mc_bkg_11.pfMET>40 && mc_bkg_11.isVBFJet==1 &&( mc_bkg_11.vbf_maxpt_j1_bDiscriminatorCSV>0.935 ||  mc_bkg_11.vbf_maxpt_j2_bDiscriminatorCSV>0.935 ) )
			{
			t11_BkgHist[0]->Fill(mc_bkg_11.nPV,mc_bkg_11.totalEventWeight);
			t11_BkgHist[1]->Fill(mc_bkg_11.l_pt,mc_bkg_11.totalEventWeight);
			t11_BkgHist[2]->Fill(mc_bkg_11.l_eta,mc_bkg_11.totalEventWeight);
			t11_BkgHist[3]->Fill(mc_bkg_11.l_phi,mc_bkg_11.totalEventWeight);
			t11_BkgHist[4]->Fill(mc_bkg_11.pfMET,mc_bkg_11.totalEventWeight);
			t11_BkgHist[5]->Fill(mc_bkg_11.vbf_maxpt_j1_pt,mc_bkg_11.totalEventWeight);
			t11_BkgHist[6]->Fill(mc_bkg_11.vbf_maxpt_j2_pt,mc_bkg_11.totalEventWeight);
			t11_BkgHist[7]->Fill(mc_bkg_11.vbf_maxpt_j1_eta,mc_bkg_11.totalEventWeight);
			t11_BkgHist[8]->Fill(mc_bkg_11.vbf_maxpt_j2_eta,mc_bkg_11.totalEventWeight);
			t11_BkgHist[9]->Fill(mc_bkg_11.AK4_jet1_pt,mc_bkg_11.totalEventWeight);
			t11_BkgHist[10]->Fill(mc_bkg_11.AK4_jet2_pt,mc_bkg_11.totalEventWeight);
			t11_BkgHist[11]->Fill(mc_bkg_11.AK4_jet1_eta,mc_bkg_11.totalEventWeight);
			t11_BkgHist[12]->Fill(mc_bkg_11.AK4_jet2_eta,mc_bkg_11.totalEventWeight);
			t11_BkgHist[13]->Fill(mc_bkg_11.vbf_maxpt_jj_m,mc_bkg_11.totalEventWeight);
			t11_BkgHist[14]->Fill(mc_bkg_11.vbf_maxpt_jj_pt,mc_bkg_11.totalEventWeight);
			t11_BkgHist[15]->Fill(mc_bkg_11.AK4_jetjet_mass,mc_bkg_11.totalEventWeight);
			t11_BkgHist[16]->Fill(mc_bkg_11.AK4_jetjet_pt,mc_bkg_11.totalEventWeight);
			t11_BkgHist[17]->Fill(mc_bkg_11.AK4_jetjet_deltaeta,mc_bkg_11.totalEventWeight);
			t11_BkgHist[18]->Fill(mc_bkg_11.v_mt,mc_bkg_11.totalEventWeight);
			t11_BkgHist[19]->Fill(mc_bkg_11.v_pt,mc_bkg_11.totalEventWeight);
			t11_BkgHist[20]->Fill(mc_bkg_11.mass_lvjj_type0_AK4,mc_bkg_11.totalEventWeight);
			t11_BkgHist[21]->Fill(mc_bkg_11.deltaR_lak4jetjet,mc_bkg_11.totalEventWeight);
			t11_BkgHist[22]->Fill(mc_bkg_11.deltaphi_METak4jetjet,mc_bkg_11.totalEventWeight);
			t11_BkgHist[23]->Fill(mc_bkg_11.deltaphi_Vak4jetjet,mc_bkg_11.totalEventWeight);
			t11_BkgHist[24]->Fill(mc_bkg_11.njets,mc_bkg_11.totalEventWeight);
			t11_BkgHist[25]->Fill(mc_bkg_11.nVBFPairs,mc_bkg_11.totalEventWeight);
			}
		}


	TChain* t12_mc_bkg = new TChain("otree");
		t12_mc_bkg->Add("/afs/cern.ch/user/r/rasharma/work/aQGC_Studies/SecondStep_WWTrees/CMSSW_8_0_11/src/LepAJet_NoCutJet/copy_toRunDYEle/WWAnalysisRun2/output/output_el/WWTree_WJets600bis.root");
		ClassReadTree mc_bkg_12(t12_mc_bkg);
		for(int iEv_12_mc_bkg=0;iEv_12_mc_bkg < t12_mc_bkg->GetEntries();iEv_12_mc_bkg++){
			t12_mc_bkg->GetEntry(iEv_12_mc_bkg);
			if (mc_bkg_12.pfMET>40 && mc_bkg_12.isVBFJet==1 &&( mc_bkg_12.vbf_maxpt_j1_bDiscriminatorCSV>0.935 ||  mc_bkg_12.vbf_maxpt_j2_bDiscriminatorCSV>0.935 ) )
			{
			t12_BkgHist[0]->Fill(mc_bkg_12.nPV,mc_bkg_12.totalEventWeight);
			t12_BkgHist[1]->Fill(mc_bkg_12.l_pt,mc_bkg_12.totalEventWeight);
			t12_BkgHist[2]->Fill(mc_bkg_12.l_eta,mc_bkg_12.totalEventWeight);
			t12_BkgHist[3]->Fill(mc_bkg_12.l_phi,mc_bkg_12.totalEventWeight);
			t12_BkgHist[4]->Fill(mc_bkg_12.pfMET,mc_bkg_12.totalEventWeight);
			t12_BkgHist[5]->Fill(mc_bkg_12.vbf_maxpt_j1_pt,mc_bkg_12.totalEventWeight);
			t12_BkgHist[6]->Fill(mc_bkg_12.vbf_maxpt_j2_pt,mc_bkg_12.totalEventWeight);
			t12_BkgHist[7]->Fill(mc_bkg_12.vbf_maxpt_j1_eta,mc_bkg_12.totalEventWeight);
			t12_BkgHist[8]->Fill(mc_bkg_12.vbf_maxpt_j2_eta,mc_bkg_12.totalEventWeight);
			t12_BkgHist[9]->Fill(mc_bkg_12.AK4_jet1_pt,mc_bkg_12.totalEventWeight);
			t12_BkgHist[10]->Fill(mc_bkg_12.AK4_jet2_pt,mc_bkg_12.totalEventWeight);
			t12_BkgHist[11]->Fill(mc_bkg_12.AK4_jet1_eta,mc_bkg_12.totalEventWeight);
			t12_BkgHist[12]->Fill(mc_bkg_12.AK4_jet2_eta,mc_bkg_12.totalEventWeight);
			t12_BkgHist[13]->Fill(mc_bkg_12.vbf_maxpt_jj_m,mc_bkg_12.totalEventWeight);
			t12_BkgHist[14]->Fill(mc_bkg_12.vbf_maxpt_jj_pt,mc_bkg_12.totalEventWeight);
			t12_BkgHist[15]->Fill(mc_bkg_12.AK4_jetjet_mass,mc_bkg_12.totalEventWeight);
			t12_BkgHist[16]->Fill(mc_bkg_12.AK4_jetjet_pt,mc_bkg_12.totalEventWeight);
			t12_BkgHist[17]->Fill(mc_bkg_12.AK4_jetjet_deltaeta,mc_bkg_12.totalEventWeight);
			t12_BkgHist[18]->Fill(mc_bkg_12.v_mt,mc_bkg_12.totalEventWeight);
			t12_BkgHist[19]->Fill(mc_bkg_12.v_pt,mc_bkg_12.totalEventWeight);
			t12_BkgHist[20]->Fill(mc_bkg_12.mass_lvjj_type0_AK4,mc_bkg_12.totalEventWeight);
			t12_BkgHist[21]->Fill(mc_bkg_12.deltaR_lak4jetjet,mc_bkg_12.totalEventWeight);
			t12_BkgHist[22]->Fill(mc_bkg_12.deltaphi_METak4jetjet,mc_bkg_12.totalEventWeight);
			t12_BkgHist[23]->Fill(mc_bkg_12.deltaphi_Vak4jetjet,mc_bkg_12.totalEventWeight);
			t12_BkgHist[24]->Fill(mc_bkg_12.njets,mc_bkg_12.totalEventWeight);
			t12_BkgHist[25]->Fill(mc_bkg_12.nVBFPairs,mc_bkg_12.totalEventWeight);
			}
		}


	TChain* t13_mc_bkg = new TChain("otree");
		t13_mc_bkg->Add("/afs/cern.ch/user/r/rasharma/work/aQGC_Studies/SecondStep_WWTrees/CMSSW_8_0_11/src/LepAJet_NoCutJet/copy_toRunDYEle/WWAnalysisRun2/output/output_el/WWTree_WJets800.root");
		ClassReadTree mc_bkg_13(t13_mc_bkg);
		for(int iEv_13_mc_bkg=0;iEv_13_mc_bkg < t13_mc_bkg->GetEntries();iEv_13_mc_bkg++){
			t13_mc_bkg->GetEntry(iEv_13_mc_bkg);
			if (mc_bkg_13.pfMET>40 && mc_bkg_13.isVBFJet==1 &&( mc_bkg_13.vbf_maxpt_j1_bDiscriminatorCSV>0.935 ||  mc_bkg_13.vbf_maxpt_j2_bDiscriminatorCSV>0.935 ) )
			{
			t13_BkgHist[0]->Fill(mc_bkg_13.nPV,mc_bkg_13.totalEventWeight);
			t13_BkgHist[1]->Fill(mc_bkg_13.l_pt,mc_bkg_13.totalEventWeight);
			t13_BkgHist[2]->Fill(mc_bkg_13.l_eta,mc_bkg_13.totalEventWeight);
			t13_BkgHist[3]->Fill(mc_bkg_13.l_phi,mc_bkg_13.totalEventWeight);
			t13_BkgHist[4]->Fill(mc_bkg_13.pfMET,mc_bkg_13.totalEventWeight);
			t13_BkgHist[5]->Fill(mc_bkg_13.vbf_maxpt_j1_pt,mc_bkg_13.totalEventWeight);
			t13_BkgHist[6]->Fill(mc_bkg_13.vbf_maxpt_j2_pt,mc_bkg_13.totalEventWeight);
			t13_BkgHist[7]->Fill(mc_bkg_13.vbf_maxpt_j1_eta,mc_bkg_13.totalEventWeight);
			t13_BkgHist[8]->Fill(mc_bkg_13.vbf_maxpt_j2_eta,mc_bkg_13.totalEventWeight);
			t13_BkgHist[9]->Fill(mc_bkg_13.AK4_jet1_pt,mc_bkg_13.totalEventWeight);
			t13_BkgHist[10]->Fill(mc_bkg_13.AK4_jet2_pt,mc_bkg_13.totalEventWeight);
			t13_BkgHist[11]->Fill(mc_bkg_13.AK4_jet1_eta,mc_bkg_13.totalEventWeight);
			t13_BkgHist[12]->Fill(mc_bkg_13.AK4_jet2_eta,mc_bkg_13.totalEventWeight);
			t13_BkgHist[13]->Fill(mc_bkg_13.vbf_maxpt_jj_m,mc_bkg_13.totalEventWeight);
			t13_BkgHist[14]->Fill(mc_bkg_13.vbf_maxpt_jj_pt,mc_bkg_13.totalEventWeight);
			t13_BkgHist[15]->Fill(mc_bkg_13.AK4_jetjet_mass,mc_bkg_13.totalEventWeight);
			t13_BkgHist[16]->Fill(mc_bkg_13.AK4_jetjet_pt,mc_bkg_13.totalEventWeight);
			t13_BkgHist[17]->Fill(mc_bkg_13.AK4_jetjet_deltaeta,mc_bkg_13.totalEventWeight);
			t13_BkgHist[18]->Fill(mc_bkg_13.v_mt,mc_bkg_13.totalEventWeight);
			t13_BkgHist[19]->Fill(mc_bkg_13.v_pt,mc_bkg_13.totalEventWeight);
			t13_BkgHist[20]->Fill(mc_bkg_13.mass_lvjj_type0_AK4,mc_bkg_13.totalEventWeight);
			t13_BkgHist[21]->Fill(mc_bkg_13.deltaR_lak4jetjet,mc_bkg_13.totalEventWeight);
			t13_BkgHist[22]->Fill(mc_bkg_13.deltaphi_METak4jetjet,mc_bkg_13.totalEventWeight);
			t13_BkgHist[23]->Fill(mc_bkg_13.deltaphi_Vak4jetjet,mc_bkg_13.totalEventWeight);
			t13_BkgHist[24]->Fill(mc_bkg_13.njets,mc_bkg_13.totalEventWeight);
			t13_BkgHist[25]->Fill(mc_bkg_13.nVBFPairs,mc_bkg_13.totalEventWeight);
			}
		}


	TChain* t14_mc_bkg = new TChain("otree");
		t14_mc_bkg->Add("/afs/cern.ch/user/r/rasharma/work/aQGC_Studies/SecondStep_WWTrees/CMSSW_8_0_11/src/LepAJet_NoCutJet/copy_toRunDYEle/WWAnalysisRun2/output/output_el/WWTree_TTbar_powheg.root");
		ClassReadTree mc_bkg_14(t14_mc_bkg);
		for(int iEv_14_mc_bkg=0;iEv_14_mc_bkg < t14_mc_bkg->GetEntries();iEv_14_mc_bkg++){
			t14_mc_bkg->GetEntry(iEv_14_mc_bkg);
			if (mc_bkg_14.pfMET>40 && mc_bkg_14.isVBFJet==1 &&( mc_bkg_14.vbf_maxpt_j1_bDiscriminatorCSV>0.935 ||  mc_bkg_14.vbf_maxpt_j2_bDiscriminatorCSV>0.935 ) )
			{
			t14_BkgHist[0]->Fill(mc_bkg_14.nPV,mc_bkg_14.totalEventWeight);
			t14_BkgHist[1]->Fill(mc_bkg_14.l_pt,mc_bkg_14.totalEventWeight);
			t14_BkgHist[2]->Fill(mc_bkg_14.l_eta,mc_bkg_14.totalEventWeight);
			t14_BkgHist[3]->Fill(mc_bkg_14.l_phi,mc_bkg_14.totalEventWeight);
			t14_BkgHist[4]->Fill(mc_bkg_14.pfMET,mc_bkg_14.totalEventWeight);
			t14_BkgHist[5]->Fill(mc_bkg_14.vbf_maxpt_j1_pt,mc_bkg_14.totalEventWeight);
			t14_BkgHist[6]->Fill(mc_bkg_14.vbf_maxpt_j2_pt,mc_bkg_14.totalEventWeight);
			t14_BkgHist[7]->Fill(mc_bkg_14.vbf_maxpt_j1_eta,mc_bkg_14.totalEventWeight);
			t14_BkgHist[8]->Fill(mc_bkg_14.vbf_maxpt_j2_eta,mc_bkg_14.totalEventWeight);
			t14_BkgHist[9]->Fill(mc_bkg_14.AK4_jet1_pt,mc_bkg_14.totalEventWeight);
			t14_BkgHist[10]->Fill(mc_bkg_14.AK4_jet2_pt,mc_bkg_14.totalEventWeight);
			t14_BkgHist[11]->Fill(mc_bkg_14.AK4_jet1_eta,mc_bkg_14.totalEventWeight);
			t14_BkgHist[12]->Fill(mc_bkg_14.AK4_jet2_eta,mc_bkg_14.totalEventWeight);
			t14_BkgHist[13]->Fill(mc_bkg_14.vbf_maxpt_jj_m,mc_bkg_14.totalEventWeight);
			t14_BkgHist[14]->Fill(mc_bkg_14.vbf_maxpt_jj_pt,mc_bkg_14.totalEventWeight);
			t14_BkgHist[15]->Fill(mc_bkg_14.AK4_jetjet_mass,mc_bkg_14.totalEventWeight);
			t14_BkgHist[16]->Fill(mc_bkg_14.AK4_jetjet_pt,mc_bkg_14.totalEventWeight);
			t14_BkgHist[17]->Fill(mc_bkg_14.AK4_jetjet_deltaeta,mc_bkg_14.totalEventWeight);
			t14_BkgHist[18]->Fill(mc_bkg_14.v_mt,mc_bkg_14.totalEventWeight);
			t14_BkgHist[19]->Fill(mc_bkg_14.v_pt,mc_bkg_14.totalEventWeight);
			t14_BkgHist[20]->Fill(mc_bkg_14.mass_lvjj_type0_AK4,mc_bkg_14.totalEventWeight);
			t14_BkgHist[21]->Fill(mc_bkg_14.deltaR_lak4jetjet,mc_bkg_14.totalEventWeight);
			t14_BkgHist[22]->Fill(mc_bkg_14.deltaphi_METak4jetjet,mc_bkg_14.totalEventWeight);
			t14_BkgHist[23]->Fill(mc_bkg_14.deltaphi_Vak4jetjet,mc_bkg_14.totalEventWeight);
			t14_BkgHist[24]->Fill(mc_bkg_14.njets,mc_bkg_14.totalEventWeight);
			t14_BkgHist[25]->Fill(mc_bkg_14.nVBFPairs,mc_bkg_14.totalEventWeight);
			}
		}


	TChain* t0_data = new TChain("otree");
		t0_data->Add("/afs/cern.ch/user/r/rasharma/work/aQGC_Studies/SecondStep_WWTrees/CMSSW_8_0_11/src/LepAJet_NoCutJet/copy_toRunDYEle/WWAnalysisRun2/output/output_el/WWTree_data_golden.root");
		ClassReadTree mc_data_0(t0_data);
		for(int iEv_0_data=0;iEv_0_data < t0_data->GetEntries();iEv_0_data++){
			t0_data->GetEntry(iEv_0_data);
			if (mc_data_0.pfMET>40 && mc_data_0.isVBFJet==1 && (mc_data_0.vbf_maxpt_j1_bDiscriminatorCSV>0.935 || mc_data_0.vbf_maxpt_j1_bDiscriminatorCSV>0.935))
			{
			DataHist[0]->Fill(mc_data_0.nPV);
			DataHist[1]->Fill(mc_data_0.l_pt);
			DataHist[2]->Fill(mc_data_0.l_eta);
			DataHist[3]->Fill(mc_data_0.l_phi);
			DataHist[4]->Fill(mc_data_0.pfMET);
			DataHist[5]->Fill(mc_data_0.vbf_maxpt_j1_pt);
			DataHist[6]->Fill(mc_data_0.vbf_maxpt_j2_pt);
			DataHist[7]->Fill(mc_data_0.vbf_maxpt_j1_eta);
			DataHist[8]->Fill(mc_data_0.vbf_maxpt_j2_eta);
			DataHist[9]->Fill(mc_data_0.AK4_jet1_pt);
			DataHist[10]->Fill(mc_data_0.AK4_jet2_pt);
			DataHist[11]->Fill(mc_data_0.AK4_jet1_eta);
			DataHist[12]->Fill(mc_data_0.AK4_jet2_eta);
			DataHist[13]->Fill(mc_data_0.vbf_maxpt_jj_m);
			DataHist[14]->Fill(mc_data_0.vbf_maxpt_jj_pt);
			DataHist[15]->Fill(mc_data_0.AK4_jetjet_mass);
			DataHist[16]->Fill(mc_data_0.AK4_jetjet_pt);
			DataHist[17]->Fill(mc_data_0.AK4_jetjet_deltaeta);
			DataHist[18]->Fill(mc_data_0.v_mt);
			DataHist[19]->Fill(mc_data_0.v_pt);
			DataHist[20]->Fill(mc_data_0.mass_lvjj_type0_AK4);
			DataHist[21]->Fill(mc_data_0.deltaR_lak4jetjet);
			DataHist[22]->Fill(mc_data_0.deltaphi_METak4jetjet);
			DataHist[23]->Fill(mc_data_0.deltaphi_Vak4jetjet);
			DataHist[24]->Fill(mc_data_0.njets);
			DataHist[25]->Fill(mc_data_0.nVBFPairs);
			}
		}


	TLegend *leg = new TLegend(0.77,0.40,1.15,0.90,NULL,"brNDC");

	leg->SetNColumns(1);

	leg->SetTextSize(0.07);

	leg->SetFillColor(0);

	leg->SetFillStyle(0);

	leg->SetBorderSize(0);

double yMax=0.;
double HistMax=0.0;
c1->cd();

pad[0]->SetBottomMargin(0.05287462);
pad[0]->SetLogy(1);
pad[0]->Draw();
pad[0]->cd();

	t0_BkgHist[0]->Scale(0.148600);
	HistMax = t0_BkgHist[0]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t0_BkgHist[0],"VV","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t1_BkgHist[0]->Scale(0.002400);
	HistMax = t1_BkgHist[0]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t2_BkgHist[0]->Scale(0.000700);
	HistMax = t2_BkgHist[0]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t3_BkgHist[0]->Scale(0.206800);
	HistMax = t3_BkgHist[0]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t3_BkgHist[0],"S Top","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t4_BkgHist[0]->Scale(0.209600);
	HistMax = t4_BkgHist[0]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t5_BkgHist[0]->Scale(0.089900);
	HistMax = t5_BkgHist[0]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t6_BkgHist[0]->Scale(0.021200);
	HistMax = t6_BkgHist[0]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t7_BkgHist[0]->Scale(0.283600);
	HistMax = t7_BkgHist[0]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t7_BkgHist[0],"WJets","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t8_BkgHist[0]->Scale(0.420700);
	HistMax = t8_BkgHist[0]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t9_BkgHist[0]->Scale(0.031300);
	HistMax = t9_BkgHist[0]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t10_BkgHist[0]->Scale(0.000700);
	HistMax = t10_BkgHist[0]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t11_BkgHist[0]->Scale(0.144400);
	HistMax = t11_BkgHist[0]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t12_BkgHist[0]->Scale(0.019900);
	HistMax = t12_BkgHist[0]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t13_BkgHist[0]->Scale(0.004800);
	HistMax = t13_BkgHist[0]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t14_BkgHist[0]->Scale(0.026500);
	HistMax = t14_BkgHist[0]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t14_BkgHist[0],"TTbar","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	DataHist[0]->Sumw2();
	HistMax = DataHist[0]->GetMaximum()*1.80;
	leg->AddEntry(DataHist[0],"Data","pe");
	yMax=HistMax;

	hs[0]->Add(t0_BkgHist[0],"hist");
	hs[0]->Add(t1_BkgHist[0],"hist");
	hs[0]->Add(t2_BkgHist[0],"hist");
	hs[0]->Add(t3_BkgHist[0],"hist");
	hs[0]->Add(t4_BkgHist[0],"hist");
	hs[0]->Add(t5_BkgHist[0],"hist");
	hs[0]->Add(t6_BkgHist[0],"hist");
	hs[0]->Add(t7_BkgHist[0],"hist");
	hs[0]->Add(t8_BkgHist[0],"hist");
	hs[0]->Add(t9_BkgHist[0],"hist");
	hs[0]->Add(t10_BkgHist[0],"hist");
	hs[0]->Add(t11_BkgHist[0],"hist");
	hs[0]->Add(t12_BkgHist[0],"hist");
	hs[0]->Add(t13_BkgHist[0],"hist");
	hs[0]->Add(t14_BkgHist[0],"hist");
	hs[0]->SetMaximum(yMax);
	hs[0]->SetMinimum(0.1);
	hs[0]->Draw();
	DataHist[0]->Draw("same");
	leg->Draw("same");
TH1F *h2 = (TH1F*)DataHist[0]->Clone();
hRatio[0]->Add(t0_BkgHist[0]);
hRatio[0]->Add(t1_BkgHist[0]);
hRatio[0]->Add(t2_BkgHist[0]);
hRatio[0]->Add(t3_BkgHist[0]);
hRatio[0]->Add(t4_BkgHist[0]);
hRatio[0]->Add(t5_BkgHist[0]);
hRatio[0]->Add(t6_BkgHist[0]);
hRatio[0]->Add(t7_BkgHist[0]);
hRatio[0]->Add(t8_BkgHist[0]);
hRatio[0]->Add(t9_BkgHist[0]);
hRatio[0]->Add(t10_BkgHist[0]);
hRatio[0]->Add(t11_BkgHist[0]);
hRatio[0]->Add(t12_BkgHist[0]);
hRatio[0]->Add(t13_BkgHist[0]);
hRatio[0]->Add(t14_BkgHist[0]);


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
cout<<"Ratio of Data/MC = "<<(DataHist[0]->Integral())/(hRatio[0]->Integral())<<endl;
cout<<"Number of event in WW  = "<<t0_BkgHist[0]->Integral()<<endl;
cout<<"Number of event in WZ  = "<<t1_BkgHist[0]->Integral()<<endl;
cout<<"Number of event in ZZ  = "<<t2_BkgHist[0]->Integral()<<endl;
cout<<"Number of event in tWch  = "<<t3_BkgHist[0]->Integral()<<endl;
cout<<"Number of event in tWch_bar  = "<<t4_BkgHist[0]->Integral()<<endl;
cout<<"Number of event in tch_bar  = "<<t5_BkgHist[0]->Integral()<<endl;
cout<<"Number of event in sch  = "<<t6_BkgHist[0]->Integral()<<endl;
cout<<"Number of event in WJets100  = "<<t7_BkgHist[0]->Integral()<<endl;
cout<<"Number of event in WJets200  = "<<t8_BkgHist[0]->Integral()<<endl;
cout<<"Number of event in WJets1200  = "<<t9_BkgHist[0]->Integral()<<endl;
cout<<"Number of event in WJets2500  = "<<t10_BkgHist[0]->Integral()<<endl;
cout<<"Number of event in WJets400  = "<<t11_BkgHist[0]->Integral()<<endl;
cout<<"Number of event in WJets600  = "<<t12_BkgHist[0]->Integral()<<endl;
cout<<"Number of event in WJets  = "<<t13_BkgHist[0]->Integral()<<endl;
cout<<"Number of event in TTbar  = "<<t14_BkgHist[0]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("nPV");
h2->GetXaxis()->CenterTitle(1);
h2->SetMinimum(0.5);
h2->SetMaximum(1.5);
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
	c1->SaveAs("nPV.C");
	c1->SaveAs("nPV.root");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[1]->SetBottomMargin(0.05287462);
pad[1]->SetLogy(1);
pad[1]->Draw();
pad[1]->cd();

	t0_BkgHist[1]->Scale(0.148600);
	HistMax = t0_BkgHist[1]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t0_BkgHist[1],"VV","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t1_BkgHist[1]->Scale(0.002400);
	HistMax = t1_BkgHist[1]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t2_BkgHist[1]->Scale(0.000700);
	HistMax = t2_BkgHist[1]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t3_BkgHist[1]->Scale(0.206800);
	HistMax = t3_BkgHist[1]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t3_BkgHist[1],"S Top","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t4_BkgHist[1]->Scale(0.209600);
	HistMax = t4_BkgHist[1]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t5_BkgHist[1]->Scale(0.089900);
	HistMax = t5_BkgHist[1]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t6_BkgHist[1]->Scale(0.021200);
	HistMax = t6_BkgHist[1]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t7_BkgHist[1]->Scale(0.283600);
	HistMax = t7_BkgHist[1]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t7_BkgHist[1],"WJets","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t8_BkgHist[1]->Scale(0.420700);
	HistMax = t8_BkgHist[1]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t9_BkgHist[1]->Scale(0.031300);
	HistMax = t9_BkgHist[1]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t10_BkgHist[1]->Scale(0.000700);
	HistMax = t10_BkgHist[1]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t11_BkgHist[1]->Scale(0.144400);
	HistMax = t11_BkgHist[1]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t12_BkgHist[1]->Scale(0.019900);
	HistMax = t12_BkgHist[1]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t13_BkgHist[1]->Scale(0.004800);
	HistMax = t13_BkgHist[1]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t14_BkgHist[1]->Scale(0.026500);
	HistMax = t14_BkgHist[1]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t14_BkgHist[1],"TTbar","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	DataHist[1]->Sumw2();
	HistMax = DataHist[1]->GetMaximum()*1.80;
	leg->AddEntry(DataHist[1],"Data","pe");
	yMax=HistMax;

	hs[1]->Add(t0_BkgHist[1],"hist");
	hs[1]->Add(t1_BkgHist[1],"hist");
	hs[1]->Add(t2_BkgHist[1],"hist");
	hs[1]->Add(t3_BkgHist[1],"hist");
	hs[1]->Add(t4_BkgHist[1],"hist");
	hs[1]->Add(t5_BkgHist[1],"hist");
	hs[1]->Add(t6_BkgHist[1],"hist");
	hs[1]->Add(t7_BkgHist[1],"hist");
	hs[1]->Add(t8_BkgHist[1],"hist");
	hs[1]->Add(t9_BkgHist[1],"hist");
	hs[1]->Add(t10_BkgHist[1],"hist");
	hs[1]->Add(t11_BkgHist[1],"hist");
	hs[1]->Add(t12_BkgHist[1],"hist");
	hs[1]->Add(t13_BkgHist[1],"hist");
	hs[1]->Add(t14_BkgHist[1],"hist");
	hs[1]->SetMaximum(yMax);
	hs[1]->SetMinimum(0.1);
	hs[1]->Draw();
	DataHist[1]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[1]->Clone();
hRatio[1]->Add(t0_BkgHist[1]);
hRatio[1]->Add(t1_BkgHist[1]);
hRatio[1]->Add(t2_BkgHist[1]);
hRatio[1]->Add(t3_BkgHist[1]);
hRatio[1]->Add(t4_BkgHist[1]);
hRatio[1]->Add(t5_BkgHist[1]);
hRatio[1]->Add(t6_BkgHist[1]);
hRatio[1]->Add(t7_BkgHist[1]);
hRatio[1]->Add(t8_BkgHist[1]);
hRatio[1]->Add(t9_BkgHist[1]);
hRatio[1]->Add(t10_BkgHist[1]);
hRatio[1]->Add(t11_BkgHist[1]);
hRatio[1]->Add(t12_BkgHist[1]);
hRatio[1]->Add(t13_BkgHist[1]);
hRatio[1]->Add(t14_BkgHist[1]);


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
cout<<"Ratio of Data/MC = "<<(DataHist[1]->Integral())/(hRatio[1]->Integral())<<endl;
cout<<"Number of event in WW  = "<<t0_BkgHist[1]->Integral()<<endl;
cout<<"Number of event in WZ  = "<<t1_BkgHist[1]->Integral()<<endl;
cout<<"Number of event in ZZ  = "<<t2_BkgHist[1]->Integral()<<endl;
cout<<"Number of event in tWch  = "<<t3_BkgHist[1]->Integral()<<endl;
cout<<"Number of event in tWch_bar  = "<<t4_BkgHist[1]->Integral()<<endl;
cout<<"Number of event in tch_bar  = "<<t5_BkgHist[1]->Integral()<<endl;
cout<<"Number of event in sch  = "<<t6_BkgHist[1]->Integral()<<endl;
cout<<"Number of event in WJets100  = "<<t7_BkgHist[1]->Integral()<<endl;
cout<<"Number of event in WJets200  = "<<t8_BkgHist[1]->Integral()<<endl;
cout<<"Number of event in WJets1200  = "<<t9_BkgHist[1]->Integral()<<endl;
cout<<"Number of event in WJets2500  = "<<t10_BkgHist[1]->Integral()<<endl;
cout<<"Number of event in WJets400  = "<<t11_BkgHist[1]->Integral()<<endl;
cout<<"Number of event in WJets600  = "<<t12_BkgHist[1]->Integral()<<endl;
cout<<"Number of event in WJets  = "<<t13_BkgHist[1]->Integral()<<endl;
cout<<"Number of event in TTbar  = "<<t14_BkgHist[1]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("l_pt");
h2->GetXaxis()->CenterTitle(1);
h2->SetMinimum(0.5);
h2->SetMaximum(1.5);
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
	c1->SaveAs("l_pt.C");
	c1->SaveAs("l_pt.root");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[2]->SetBottomMargin(0.05287462);
pad[2]->SetLogy(1);
pad[2]->Draw();
pad[2]->cd();

	t0_BkgHist[2]->Scale(0.148600);
	HistMax = t0_BkgHist[2]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t0_BkgHist[2],"VV","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t1_BkgHist[2]->Scale(0.002400);
	HistMax = t1_BkgHist[2]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t2_BkgHist[2]->Scale(0.000700);
	HistMax = t2_BkgHist[2]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t3_BkgHist[2]->Scale(0.206800);
	HistMax = t3_BkgHist[2]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t3_BkgHist[2],"S Top","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t4_BkgHist[2]->Scale(0.209600);
	HistMax = t4_BkgHist[2]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t5_BkgHist[2]->Scale(0.089900);
	HistMax = t5_BkgHist[2]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t6_BkgHist[2]->Scale(0.021200);
	HistMax = t6_BkgHist[2]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t7_BkgHist[2]->Scale(0.283600);
	HistMax = t7_BkgHist[2]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t7_BkgHist[2],"WJets","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t8_BkgHist[2]->Scale(0.420700);
	HistMax = t8_BkgHist[2]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t9_BkgHist[2]->Scale(0.031300);
	HistMax = t9_BkgHist[2]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t10_BkgHist[2]->Scale(0.000700);
	HistMax = t10_BkgHist[2]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t11_BkgHist[2]->Scale(0.144400);
	HistMax = t11_BkgHist[2]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t12_BkgHist[2]->Scale(0.019900);
	HistMax = t12_BkgHist[2]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t13_BkgHist[2]->Scale(0.004800);
	HistMax = t13_BkgHist[2]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t14_BkgHist[2]->Scale(0.026500);
	HistMax = t14_BkgHist[2]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t14_BkgHist[2],"TTbar","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	DataHist[2]->Sumw2();
	HistMax = DataHist[2]->GetMaximum()*1.80;
	leg->AddEntry(DataHist[2],"Data","pe");
	yMax=HistMax;

	hs[2]->Add(t0_BkgHist[2],"hist");
	hs[2]->Add(t1_BkgHist[2],"hist");
	hs[2]->Add(t2_BkgHist[2],"hist");
	hs[2]->Add(t3_BkgHist[2],"hist");
	hs[2]->Add(t4_BkgHist[2],"hist");
	hs[2]->Add(t5_BkgHist[2],"hist");
	hs[2]->Add(t6_BkgHist[2],"hist");
	hs[2]->Add(t7_BkgHist[2],"hist");
	hs[2]->Add(t8_BkgHist[2],"hist");
	hs[2]->Add(t9_BkgHist[2],"hist");
	hs[2]->Add(t10_BkgHist[2],"hist");
	hs[2]->Add(t11_BkgHist[2],"hist");
	hs[2]->Add(t12_BkgHist[2],"hist");
	hs[2]->Add(t13_BkgHist[2],"hist");
	hs[2]->Add(t14_BkgHist[2],"hist");
	hs[2]->SetMaximum(yMax);
	hs[2]->SetMinimum(0.1);
	hs[2]->Draw();
	DataHist[2]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[2]->Clone();
hRatio[2]->Add(t0_BkgHist[2]);
hRatio[2]->Add(t1_BkgHist[2]);
hRatio[2]->Add(t2_BkgHist[2]);
hRatio[2]->Add(t3_BkgHist[2]);
hRatio[2]->Add(t4_BkgHist[2]);
hRatio[2]->Add(t5_BkgHist[2]);
hRatio[2]->Add(t6_BkgHist[2]);
hRatio[2]->Add(t7_BkgHist[2]);
hRatio[2]->Add(t8_BkgHist[2]);
hRatio[2]->Add(t9_BkgHist[2]);
hRatio[2]->Add(t10_BkgHist[2]);
hRatio[2]->Add(t11_BkgHist[2]);
hRatio[2]->Add(t12_BkgHist[2]);
hRatio[2]->Add(t13_BkgHist[2]);
hRatio[2]->Add(t14_BkgHist[2]);


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
cout<<"Ratio of Data/MC = "<<(DataHist[2]->Integral())/(hRatio[2]->Integral())<<endl;
cout<<"Number of event in WW  = "<<t0_BkgHist[2]->Integral()<<endl;
cout<<"Number of event in WZ  = "<<t1_BkgHist[2]->Integral()<<endl;
cout<<"Number of event in ZZ  = "<<t2_BkgHist[2]->Integral()<<endl;
cout<<"Number of event in tWch  = "<<t3_BkgHist[2]->Integral()<<endl;
cout<<"Number of event in tWch_bar  = "<<t4_BkgHist[2]->Integral()<<endl;
cout<<"Number of event in tch_bar  = "<<t5_BkgHist[2]->Integral()<<endl;
cout<<"Number of event in sch  = "<<t6_BkgHist[2]->Integral()<<endl;
cout<<"Number of event in WJets100  = "<<t7_BkgHist[2]->Integral()<<endl;
cout<<"Number of event in WJets200  = "<<t8_BkgHist[2]->Integral()<<endl;
cout<<"Number of event in WJets1200  = "<<t9_BkgHist[2]->Integral()<<endl;
cout<<"Number of event in WJets2500  = "<<t10_BkgHist[2]->Integral()<<endl;
cout<<"Number of event in WJets400  = "<<t11_BkgHist[2]->Integral()<<endl;
cout<<"Number of event in WJets600  = "<<t12_BkgHist[2]->Integral()<<endl;
cout<<"Number of event in WJets  = "<<t13_BkgHist[2]->Integral()<<endl;
cout<<"Number of event in TTbar  = "<<t14_BkgHist[2]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("l_eta");
h2->GetXaxis()->CenterTitle(1);
h2->SetMinimum(0.5);
h2->SetMaximum(1.5);
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
	c1->SaveAs("l_eta.C");
	c1->SaveAs("l_eta.root");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[3]->SetBottomMargin(0.05287462);
pad[3]->SetLogy(1);
pad[3]->Draw();
pad[3]->cd();

	t0_BkgHist[3]->Scale(0.148600);
	HistMax = t0_BkgHist[3]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t0_BkgHist[3],"VV","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t1_BkgHist[3]->Scale(0.002400);
	HistMax = t1_BkgHist[3]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t2_BkgHist[3]->Scale(0.000700);
	HistMax = t2_BkgHist[3]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t3_BkgHist[3]->Scale(0.206800);
	HistMax = t3_BkgHist[3]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t3_BkgHist[3],"S Top","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t4_BkgHist[3]->Scale(0.209600);
	HistMax = t4_BkgHist[3]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t5_BkgHist[3]->Scale(0.089900);
	HistMax = t5_BkgHist[3]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t6_BkgHist[3]->Scale(0.021200);
	HistMax = t6_BkgHist[3]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t7_BkgHist[3]->Scale(0.283600);
	HistMax = t7_BkgHist[3]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t7_BkgHist[3],"WJets","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t8_BkgHist[3]->Scale(0.420700);
	HistMax = t8_BkgHist[3]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t9_BkgHist[3]->Scale(0.031300);
	HistMax = t9_BkgHist[3]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t10_BkgHist[3]->Scale(0.000700);
	HistMax = t10_BkgHist[3]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t11_BkgHist[3]->Scale(0.144400);
	HistMax = t11_BkgHist[3]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t12_BkgHist[3]->Scale(0.019900);
	HistMax = t12_BkgHist[3]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t13_BkgHist[3]->Scale(0.004800);
	HistMax = t13_BkgHist[3]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t14_BkgHist[3]->Scale(0.026500);
	HistMax = t14_BkgHist[3]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t14_BkgHist[3],"TTbar","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	DataHist[3]->Sumw2();
	HistMax = DataHist[3]->GetMaximum()*1.80;
	leg->AddEntry(DataHist[3],"Data","pe");
	yMax=HistMax;

	hs[3]->Add(t0_BkgHist[3],"hist");
	hs[3]->Add(t1_BkgHist[3],"hist");
	hs[3]->Add(t2_BkgHist[3],"hist");
	hs[3]->Add(t3_BkgHist[3],"hist");
	hs[3]->Add(t4_BkgHist[3],"hist");
	hs[3]->Add(t5_BkgHist[3],"hist");
	hs[3]->Add(t6_BkgHist[3],"hist");
	hs[3]->Add(t7_BkgHist[3],"hist");
	hs[3]->Add(t8_BkgHist[3],"hist");
	hs[3]->Add(t9_BkgHist[3],"hist");
	hs[3]->Add(t10_BkgHist[3],"hist");
	hs[3]->Add(t11_BkgHist[3],"hist");
	hs[3]->Add(t12_BkgHist[3],"hist");
	hs[3]->Add(t13_BkgHist[3],"hist");
	hs[3]->Add(t14_BkgHist[3],"hist");
	hs[3]->SetMaximum(yMax);
	hs[3]->SetMinimum(0.1);
	hs[3]->Draw();
	DataHist[3]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[3]->Clone();
hRatio[3]->Add(t0_BkgHist[3]);
hRatio[3]->Add(t1_BkgHist[3]);
hRatio[3]->Add(t2_BkgHist[3]);
hRatio[3]->Add(t3_BkgHist[3]);
hRatio[3]->Add(t4_BkgHist[3]);
hRatio[3]->Add(t5_BkgHist[3]);
hRatio[3]->Add(t6_BkgHist[3]);
hRatio[3]->Add(t7_BkgHist[3]);
hRatio[3]->Add(t8_BkgHist[3]);
hRatio[3]->Add(t9_BkgHist[3]);
hRatio[3]->Add(t10_BkgHist[3]);
hRatio[3]->Add(t11_BkgHist[3]);
hRatio[3]->Add(t12_BkgHist[3]);
hRatio[3]->Add(t13_BkgHist[3]);
hRatio[3]->Add(t14_BkgHist[3]);


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
cout<<"Ratio of Data/MC = "<<(DataHist[3]->Integral())/(hRatio[3]->Integral())<<endl;
cout<<"Number of event in WW  = "<<t0_BkgHist[3]->Integral()<<endl;
cout<<"Number of event in WZ  = "<<t1_BkgHist[3]->Integral()<<endl;
cout<<"Number of event in ZZ  = "<<t2_BkgHist[3]->Integral()<<endl;
cout<<"Number of event in tWch  = "<<t3_BkgHist[3]->Integral()<<endl;
cout<<"Number of event in tWch_bar  = "<<t4_BkgHist[3]->Integral()<<endl;
cout<<"Number of event in tch_bar  = "<<t5_BkgHist[3]->Integral()<<endl;
cout<<"Number of event in sch  = "<<t6_BkgHist[3]->Integral()<<endl;
cout<<"Number of event in WJets100  = "<<t7_BkgHist[3]->Integral()<<endl;
cout<<"Number of event in WJets200  = "<<t8_BkgHist[3]->Integral()<<endl;
cout<<"Number of event in WJets1200  = "<<t9_BkgHist[3]->Integral()<<endl;
cout<<"Number of event in WJets2500  = "<<t10_BkgHist[3]->Integral()<<endl;
cout<<"Number of event in WJets400  = "<<t11_BkgHist[3]->Integral()<<endl;
cout<<"Number of event in WJets600  = "<<t12_BkgHist[3]->Integral()<<endl;
cout<<"Number of event in WJets  = "<<t13_BkgHist[3]->Integral()<<endl;
cout<<"Number of event in TTbar  = "<<t14_BkgHist[3]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("l_phi");
h2->GetXaxis()->CenterTitle(1);
h2->SetMinimum(0.5);
h2->SetMaximum(1.5);
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
	c1->SaveAs("l_phi.C");
	c1->SaveAs("l_phi.root");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[4]->SetBottomMargin(0.05287462);
pad[4]->SetLogy(1);
pad[4]->Draw();
pad[4]->cd();

	t0_BkgHist[4]->Scale(0.148600);
	HistMax = t0_BkgHist[4]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t0_BkgHist[4],"VV","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t1_BkgHist[4]->Scale(0.002400);
	HistMax = t1_BkgHist[4]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t2_BkgHist[4]->Scale(0.000700);
	HistMax = t2_BkgHist[4]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t3_BkgHist[4]->Scale(0.206800);
	HistMax = t3_BkgHist[4]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t3_BkgHist[4],"S Top","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t4_BkgHist[4]->Scale(0.209600);
	HistMax = t4_BkgHist[4]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t5_BkgHist[4]->Scale(0.089900);
	HistMax = t5_BkgHist[4]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t6_BkgHist[4]->Scale(0.021200);
	HistMax = t6_BkgHist[4]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t7_BkgHist[4]->Scale(0.283600);
	HistMax = t7_BkgHist[4]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t7_BkgHist[4],"WJets","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t8_BkgHist[4]->Scale(0.420700);
	HistMax = t8_BkgHist[4]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t9_BkgHist[4]->Scale(0.031300);
	HistMax = t9_BkgHist[4]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t10_BkgHist[4]->Scale(0.000700);
	HistMax = t10_BkgHist[4]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t11_BkgHist[4]->Scale(0.144400);
	HistMax = t11_BkgHist[4]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t12_BkgHist[4]->Scale(0.019900);
	HistMax = t12_BkgHist[4]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t13_BkgHist[4]->Scale(0.004800);
	HistMax = t13_BkgHist[4]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t14_BkgHist[4]->Scale(0.026500);
	HistMax = t14_BkgHist[4]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t14_BkgHist[4],"TTbar","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	DataHist[4]->Sumw2();
	HistMax = DataHist[4]->GetMaximum()*1.80;
	leg->AddEntry(DataHist[4],"Data","pe");
	yMax=HistMax;

	hs[4]->Add(t0_BkgHist[4],"hist");
	hs[4]->Add(t1_BkgHist[4],"hist");
	hs[4]->Add(t2_BkgHist[4],"hist");
	hs[4]->Add(t3_BkgHist[4],"hist");
	hs[4]->Add(t4_BkgHist[4],"hist");
	hs[4]->Add(t5_BkgHist[4],"hist");
	hs[4]->Add(t6_BkgHist[4],"hist");
	hs[4]->Add(t7_BkgHist[4],"hist");
	hs[4]->Add(t8_BkgHist[4],"hist");
	hs[4]->Add(t9_BkgHist[4],"hist");
	hs[4]->Add(t10_BkgHist[4],"hist");
	hs[4]->Add(t11_BkgHist[4],"hist");
	hs[4]->Add(t12_BkgHist[4],"hist");
	hs[4]->Add(t13_BkgHist[4],"hist");
	hs[4]->Add(t14_BkgHist[4],"hist");
	hs[4]->SetMaximum(yMax);
	hs[4]->SetMinimum(0.1);
	hs[4]->Draw();
	DataHist[4]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[4]->Clone();
hRatio[4]->Add(t0_BkgHist[4]);
hRatio[4]->Add(t1_BkgHist[4]);
hRatio[4]->Add(t2_BkgHist[4]);
hRatio[4]->Add(t3_BkgHist[4]);
hRatio[4]->Add(t4_BkgHist[4]);
hRatio[4]->Add(t5_BkgHist[4]);
hRatio[4]->Add(t6_BkgHist[4]);
hRatio[4]->Add(t7_BkgHist[4]);
hRatio[4]->Add(t8_BkgHist[4]);
hRatio[4]->Add(t9_BkgHist[4]);
hRatio[4]->Add(t10_BkgHist[4]);
hRatio[4]->Add(t11_BkgHist[4]);
hRatio[4]->Add(t12_BkgHist[4]);
hRatio[4]->Add(t13_BkgHist[4]);
hRatio[4]->Add(t14_BkgHist[4]);


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
cout<<"Ratio of Data/MC = "<<(DataHist[4]->Integral())/(hRatio[4]->Integral())<<endl;
cout<<"Number of event in WW  = "<<t0_BkgHist[4]->Integral()<<endl;
cout<<"Number of event in WZ  = "<<t1_BkgHist[4]->Integral()<<endl;
cout<<"Number of event in ZZ  = "<<t2_BkgHist[4]->Integral()<<endl;
cout<<"Number of event in tWch  = "<<t3_BkgHist[4]->Integral()<<endl;
cout<<"Number of event in tWch_bar  = "<<t4_BkgHist[4]->Integral()<<endl;
cout<<"Number of event in tch_bar  = "<<t5_BkgHist[4]->Integral()<<endl;
cout<<"Number of event in sch  = "<<t6_BkgHist[4]->Integral()<<endl;
cout<<"Number of event in WJets100  = "<<t7_BkgHist[4]->Integral()<<endl;
cout<<"Number of event in WJets200  = "<<t8_BkgHist[4]->Integral()<<endl;
cout<<"Number of event in WJets1200  = "<<t9_BkgHist[4]->Integral()<<endl;
cout<<"Number of event in WJets2500  = "<<t10_BkgHist[4]->Integral()<<endl;
cout<<"Number of event in WJets400  = "<<t11_BkgHist[4]->Integral()<<endl;
cout<<"Number of event in WJets600  = "<<t12_BkgHist[4]->Integral()<<endl;
cout<<"Number of event in WJets  = "<<t13_BkgHist[4]->Integral()<<endl;
cout<<"Number of event in TTbar  = "<<t14_BkgHist[4]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("pfMET");
h2->GetXaxis()->CenterTitle(1);
h2->SetMinimum(0.5);
h2->SetMaximum(1.5);
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
	c1->SaveAs("pfMET.C");
	c1->SaveAs("pfMET.root");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[5]->SetBottomMargin(0.05287462);
pad[5]->SetLogy(1);
pad[5]->Draw();
pad[5]->cd();

	t0_BkgHist[5]->Scale(0.148600);
	HistMax = t0_BkgHist[5]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t0_BkgHist[5],"VV","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t1_BkgHist[5]->Scale(0.002400);
	HistMax = t1_BkgHist[5]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t2_BkgHist[5]->Scale(0.000700);
	HistMax = t2_BkgHist[5]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t3_BkgHist[5]->Scale(0.206800);
	HistMax = t3_BkgHist[5]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t3_BkgHist[5],"S Top","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t4_BkgHist[5]->Scale(0.209600);
	HistMax = t4_BkgHist[5]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t5_BkgHist[5]->Scale(0.089900);
	HistMax = t5_BkgHist[5]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t6_BkgHist[5]->Scale(0.021200);
	HistMax = t6_BkgHist[5]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t7_BkgHist[5]->Scale(0.283600);
	HistMax = t7_BkgHist[5]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t7_BkgHist[5],"WJets","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t8_BkgHist[5]->Scale(0.420700);
	HistMax = t8_BkgHist[5]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t9_BkgHist[5]->Scale(0.031300);
	HistMax = t9_BkgHist[5]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t10_BkgHist[5]->Scale(0.000700);
	HistMax = t10_BkgHist[5]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t11_BkgHist[5]->Scale(0.144400);
	HistMax = t11_BkgHist[5]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t12_BkgHist[5]->Scale(0.019900);
	HistMax = t12_BkgHist[5]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t13_BkgHist[5]->Scale(0.004800);
	HistMax = t13_BkgHist[5]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t14_BkgHist[5]->Scale(0.026500);
	HistMax = t14_BkgHist[5]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t14_BkgHist[5],"TTbar","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	DataHist[5]->Sumw2();
	HistMax = DataHist[5]->GetMaximum()*1.80;
	leg->AddEntry(DataHist[5],"Data","pe");
	yMax=HistMax;

	hs[5]->Add(t0_BkgHist[5],"hist");
	hs[5]->Add(t1_BkgHist[5],"hist");
	hs[5]->Add(t2_BkgHist[5],"hist");
	hs[5]->Add(t3_BkgHist[5],"hist");
	hs[5]->Add(t4_BkgHist[5],"hist");
	hs[5]->Add(t5_BkgHist[5],"hist");
	hs[5]->Add(t6_BkgHist[5],"hist");
	hs[5]->Add(t7_BkgHist[5],"hist");
	hs[5]->Add(t8_BkgHist[5],"hist");
	hs[5]->Add(t9_BkgHist[5],"hist");
	hs[5]->Add(t10_BkgHist[5],"hist");
	hs[5]->Add(t11_BkgHist[5],"hist");
	hs[5]->Add(t12_BkgHist[5],"hist");
	hs[5]->Add(t13_BkgHist[5],"hist");
	hs[5]->Add(t14_BkgHist[5],"hist");
	hs[5]->SetMaximum(yMax);
	hs[5]->SetMinimum(0.1);
	hs[5]->Draw();
	DataHist[5]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[5]->Clone();
hRatio[5]->Add(t0_BkgHist[5]);
hRatio[5]->Add(t1_BkgHist[5]);
hRatio[5]->Add(t2_BkgHist[5]);
hRatio[5]->Add(t3_BkgHist[5]);
hRatio[5]->Add(t4_BkgHist[5]);
hRatio[5]->Add(t5_BkgHist[5]);
hRatio[5]->Add(t6_BkgHist[5]);
hRatio[5]->Add(t7_BkgHist[5]);
hRatio[5]->Add(t8_BkgHist[5]);
hRatio[5]->Add(t9_BkgHist[5]);
hRatio[5]->Add(t10_BkgHist[5]);
hRatio[5]->Add(t11_BkgHist[5]);
hRatio[5]->Add(t12_BkgHist[5]);
hRatio[5]->Add(t13_BkgHist[5]);
hRatio[5]->Add(t14_BkgHist[5]);


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
cout<<"Ratio of Data/MC = "<<(DataHist[5]->Integral())/(hRatio[5]->Integral())<<endl;
cout<<"Number of event in WW  = "<<t0_BkgHist[5]->Integral()<<endl;
cout<<"Number of event in WZ  = "<<t1_BkgHist[5]->Integral()<<endl;
cout<<"Number of event in ZZ  = "<<t2_BkgHist[5]->Integral()<<endl;
cout<<"Number of event in tWch  = "<<t3_BkgHist[5]->Integral()<<endl;
cout<<"Number of event in tWch_bar  = "<<t4_BkgHist[5]->Integral()<<endl;
cout<<"Number of event in tch_bar  = "<<t5_BkgHist[5]->Integral()<<endl;
cout<<"Number of event in sch  = "<<t6_BkgHist[5]->Integral()<<endl;
cout<<"Number of event in WJets100  = "<<t7_BkgHist[5]->Integral()<<endl;
cout<<"Number of event in WJets200  = "<<t8_BkgHist[5]->Integral()<<endl;
cout<<"Number of event in WJets1200  = "<<t9_BkgHist[5]->Integral()<<endl;
cout<<"Number of event in WJets2500  = "<<t10_BkgHist[5]->Integral()<<endl;
cout<<"Number of event in WJets400  = "<<t11_BkgHist[5]->Integral()<<endl;
cout<<"Number of event in WJets600  = "<<t12_BkgHist[5]->Integral()<<endl;
cout<<"Number of event in WJets  = "<<t13_BkgHist[5]->Integral()<<endl;
cout<<"Number of event in TTbar  = "<<t14_BkgHist[5]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("vbf_maxpt_j1_pt");
h2->GetXaxis()->CenterTitle(1);
h2->SetMinimum(0.5);
h2->SetMaximum(1.5);
h2->GetXaxis()->SetTitleOffset(0.8);
h2->GetXaxis()->SetLabelSize(0.033*yscale);
h2->GetXaxis()->SetTitleSize(0.036*yscale);
h2->GetXaxis()->SetTickLength(0.03*yscale);
h2->GetYaxis()->SetTitleOffset(0.3);
h2->GetYaxis()->SetNdivisions(5);
h2->GetYaxis()->SetLabelSize(0.033*yscale);
h2->GetYaxis()->SetTitleSize(0.036*yscale);
h2->Draw("");
	c1->SaveAs("vbf_maxpt_j1_pt.pdf");
	c1->SaveAs("vbf_maxpt_j1_pt.png");
	c1->SaveAs("vbf_maxpt_j1_pt.C");
	c1->SaveAs("vbf_maxpt_j1_pt.root");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[6]->SetBottomMargin(0.05287462);
pad[6]->SetLogy(1);
pad[6]->Draw();
pad[6]->cd();

	t0_BkgHist[6]->Scale(0.148600);
	HistMax = t0_BkgHist[6]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t0_BkgHist[6],"VV","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t1_BkgHist[6]->Scale(0.002400);
	HistMax = t1_BkgHist[6]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t2_BkgHist[6]->Scale(0.000700);
	HistMax = t2_BkgHist[6]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t3_BkgHist[6]->Scale(0.206800);
	HistMax = t3_BkgHist[6]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t3_BkgHist[6],"S Top","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t4_BkgHist[6]->Scale(0.209600);
	HistMax = t4_BkgHist[6]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t5_BkgHist[6]->Scale(0.089900);
	HistMax = t5_BkgHist[6]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t6_BkgHist[6]->Scale(0.021200);
	HistMax = t6_BkgHist[6]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t7_BkgHist[6]->Scale(0.283600);
	HistMax = t7_BkgHist[6]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t7_BkgHist[6],"WJets","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t8_BkgHist[6]->Scale(0.420700);
	HistMax = t8_BkgHist[6]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t9_BkgHist[6]->Scale(0.031300);
	HistMax = t9_BkgHist[6]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t10_BkgHist[6]->Scale(0.000700);
	HistMax = t10_BkgHist[6]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t11_BkgHist[6]->Scale(0.144400);
	HistMax = t11_BkgHist[6]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t12_BkgHist[6]->Scale(0.019900);
	HistMax = t12_BkgHist[6]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t13_BkgHist[6]->Scale(0.004800);
	HistMax = t13_BkgHist[6]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t14_BkgHist[6]->Scale(0.026500);
	HistMax = t14_BkgHist[6]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t14_BkgHist[6],"TTbar","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	DataHist[6]->Sumw2();
	HistMax = DataHist[6]->GetMaximum()*1.80;
	leg->AddEntry(DataHist[6],"Data","pe");
	yMax=HistMax;

	hs[6]->Add(t0_BkgHist[6],"hist");
	hs[6]->Add(t1_BkgHist[6],"hist");
	hs[6]->Add(t2_BkgHist[6],"hist");
	hs[6]->Add(t3_BkgHist[6],"hist");
	hs[6]->Add(t4_BkgHist[6],"hist");
	hs[6]->Add(t5_BkgHist[6],"hist");
	hs[6]->Add(t6_BkgHist[6],"hist");
	hs[6]->Add(t7_BkgHist[6],"hist");
	hs[6]->Add(t8_BkgHist[6],"hist");
	hs[6]->Add(t9_BkgHist[6],"hist");
	hs[6]->Add(t10_BkgHist[6],"hist");
	hs[6]->Add(t11_BkgHist[6],"hist");
	hs[6]->Add(t12_BkgHist[6],"hist");
	hs[6]->Add(t13_BkgHist[6],"hist");
	hs[6]->Add(t14_BkgHist[6],"hist");
	hs[6]->SetMaximum(yMax);
	hs[6]->SetMinimum(0.1);
	hs[6]->Draw();
	DataHist[6]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[6]->Clone();
hRatio[6]->Add(t0_BkgHist[6]);
hRatio[6]->Add(t1_BkgHist[6]);
hRatio[6]->Add(t2_BkgHist[6]);
hRatio[6]->Add(t3_BkgHist[6]);
hRatio[6]->Add(t4_BkgHist[6]);
hRatio[6]->Add(t5_BkgHist[6]);
hRatio[6]->Add(t6_BkgHist[6]);
hRatio[6]->Add(t7_BkgHist[6]);
hRatio[6]->Add(t8_BkgHist[6]);
hRatio[6]->Add(t9_BkgHist[6]);
hRatio[6]->Add(t10_BkgHist[6]);
hRatio[6]->Add(t11_BkgHist[6]);
hRatio[6]->Add(t12_BkgHist[6]);
hRatio[6]->Add(t13_BkgHist[6]);
hRatio[6]->Add(t14_BkgHist[6]);


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
cout<<"Ratio of Data/MC = "<<(DataHist[6]->Integral())/(hRatio[6]->Integral())<<endl;
cout<<"Number of event in WW  = "<<t0_BkgHist[6]->Integral()<<endl;
cout<<"Number of event in WZ  = "<<t1_BkgHist[6]->Integral()<<endl;
cout<<"Number of event in ZZ  = "<<t2_BkgHist[6]->Integral()<<endl;
cout<<"Number of event in tWch  = "<<t3_BkgHist[6]->Integral()<<endl;
cout<<"Number of event in tWch_bar  = "<<t4_BkgHist[6]->Integral()<<endl;
cout<<"Number of event in tch_bar  = "<<t5_BkgHist[6]->Integral()<<endl;
cout<<"Number of event in sch  = "<<t6_BkgHist[6]->Integral()<<endl;
cout<<"Number of event in WJets100  = "<<t7_BkgHist[6]->Integral()<<endl;
cout<<"Number of event in WJets200  = "<<t8_BkgHist[6]->Integral()<<endl;
cout<<"Number of event in WJets1200  = "<<t9_BkgHist[6]->Integral()<<endl;
cout<<"Number of event in WJets2500  = "<<t10_BkgHist[6]->Integral()<<endl;
cout<<"Number of event in WJets400  = "<<t11_BkgHist[6]->Integral()<<endl;
cout<<"Number of event in WJets600  = "<<t12_BkgHist[6]->Integral()<<endl;
cout<<"Number of event in WJets  = "<<t13_BkgHist[6]->Integral()<<endl;
cout<<"Number of event in TTbar  = "<<t14_BkgHist[6]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("vbf_maxpt_j2_pt");
h2->GetXaxis()->CenterTitle(1);
h2->SetMinimum(0.5);
h2->SetMaximum(1.5);
h2->GetXaxis()->SetTitleOffset(0.8);
h2->GetXaxis()->SetLabelSize(0.033*yscale);
h2->GetXaxis()->SetTitleSize(0.036*yscale);
h2->GetXaxis()->SetTickLength(0.03*yscale);
h2->GetYaxis()->SetTitleOffset(0.3);
h2->GetYaxis()->SetNdivisions(5);
h2->GetYaxis()->SetLabelSize(0.033*yscale);
h2->GetYaxis()->SetTitleSize(0.036*yscale);
h2->Draw("");
	c1->SaveAs("vbf_maxpt_j2_pt.pdf");
	c1->SaveAs("vbf_maxpt_j2_pt.png");
	c1->SaveAs("vbf_maxpt_j2_pt.C");
	c1->SaveAs("vbf_maxpt_j2_pt.root");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[7]->SetBottomMargin(0.05287462);
pad[7]->SetLogy(1);
pad[7]->Draw();
pad[7]->cd();

	t0_BkgHist[7]->Scale(0.148600);
	HistMax = t0_BkgHist[7]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t0_BkgHist[7],"VV","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t1_BkgHist[7]->Scale(0.002400);
	HistMax = t1_BkgHist[7]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t2_BkgHist[7]->Scale(0.000700);
	HistMax = t2_BkgHist[7]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t3_BkgHist[7]->Scale(0.206800);
	HistMax = t3_BkgHist[7]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t3_BkgHist[7],"S Top","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t4_BkgHist[7]->Scale(0.209600);
	HistMax = t4_BkgHist[7]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t5_BkgHist[7]->Scale(0.089900);
	HistMax = t5_BkgHist[7]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t6_BkgHist[7]->Scale(0.021200);
	HistMax = t6_BkgHist[7]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t7_BkgHist[7]->Scale(0.283600);
	HistMax = t7_BkgHist[7]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t7_BkgHist[7],"WJets","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t8_BkgHist[7]->Scale(0.420700);
	HistMax = t8_BkgHist[7]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t9_BkgHist[7]->Scale(0.031300);
	HistMax = t9_BkgHist[7]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t10_BkgHist[7]->Scale(0.000700);
	HistMax = t10_BkgHist[7]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t11_BkgHist[7]->Scale(0.144400);
	HistMax = t11_BkgHist[7]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t12_BkgHist[7]->Scale(0.019900);
	HistMax = t12_BkgHist[7]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t13_BkgHist[7]->Scale(0.004800);
	HistMax = t13_BkgHist[7]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t14_BkgHist[7]->Scale(0.026500);
	HistMax = t14_BkgHist[7]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t14_BkgHist[7],"TTbar","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	DataHist[7]->Sumw2();
	HistMax = DataHist[7]->GetMaximum()*1.80;
	leg->AddEntry(DataHist[7],"Data","pe");
	yMax=HistMax;

	hs[7]->Add(t0_BkgHist[7],"hist");
	hs[7]->Add(t1_BkgHist[7],"hist");
	hs[7]->Add(t2_BkgHist[7],"hist");
	hs[7]->Add(t3_BkgHist[7],"hist");
	hs[7]->Add(t4_BkgHist[7],"hist");
	hs[7]->Add(t5_BkgHist[7],"hist");
	hs[7]->Add(t6_BkgHist[7],"hist");
	hs[7]->Add(t7_BkgHist[7],"hist");
	hs[7]->Add(t8_BkgHist[7],"hist");
	hs[7]->Add(t9_BkgHist[7],"hist");
	hs[7]->Add(t10_BkgHist[7],"hist");
	hs[7]->Add(t11_BkgHist[7],"hist");
	hs[7]->Add(t12_BkgHist[7],"hist");
	hs[7]->Add(t13_BkgHist[7],"hist");
	hs[7]->Add(t14_BkgHist[7],"hist");
	hs[7]->SetMaximum(yMax);
	hs[7]->SetMinimum(0.1);
	hs[7]->Draw();
	DataHist[7]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[7]->Clone();
hRatio[7]->Add(t0_BkgHist[7]);
hRatio[7]->Add(t1_BkgHist[7]);
hRatio[7]->Add(t2_BkgHist[7]);
hRatio[7]->Add(t3_BkgHist[7]);
hRatio[7]->Add(t4_BkgHist[7]);
hRatio[7]->Add(t5_BkgHist[7]);
hRatio[7]->Add(t6_BkgHist[7]);
hRatio[7]->Add(t7_BkgHist[7]);
hRatio[7]->Add(t8_BkgHist[7]);
hRatio[7]->Add(t9_BkgHist[7]);
hRatio[7]->Add(t10_BkgHist[7]);
hRatio[7]->Add(t11_BkgHist[7]);
hRatio[7]->Add(t12_BkgHist[7]);
hRatio[7]->Add(t13_BkgHist[7]);
hRatio[7]->Add(t14_BkgHist[7]);


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
cout<<"Ratio of Data/MC = "<<(DataHist[7]->Integral())/(hRatio[7]->Integral())<<endl;
cout<<"Number of event in WW  = "<<t0_BkgHist[7]->Integral()<<endl;
cout<<"Number of event in WZ  = "<<t1_BkgHist[7]->Integral()<<endl;
cout<<"Number of event in ZZ  = "<<t2_BkgHist[7]->Integral()<<endl;
cout<<"Number of event in tWch  = "<<t3_BkgHist[7]->Integral()<<endl;
cout<<"Number of event in tWch_bar  = "<<t4_BkgHist[7]->Integral()<<endl;
cout<<"Number of event in tch_bar  = "<<t5_BkgHist[7]->Integral()<<endl;
cout<<"Number of event in sch  = "<<t6_BkgHist[7]->Integral()<<endl;
cout<<"Number of event in WJets100  = "<<t7_BkgHist[7]->Integral()<<endl;
cout<<"Number of event in WJets200  = "<<t8_BkgHist[7]->Integral()<<endl;
cout<<"Number of event in WJets1200  = "<<t9_BkgHist[7]->Integral()<<endl;
cout<<"Number of event in WJets2500  = "<<t10_BkgHist[7]->Integral()<<endl;
cout<<"Number of event in WJets400  = "<<t11_BkgHist[7]->Integral()<<endl;
cout<<"Number of event in WJets600  = "<<t12_BkgHist[7]->Integral()<<endl;
cout<<"Number of event in WJets  = "<<t13_BkgHist[7]->Integral()<<endl;
cout<<"Number of event in TTbar  = "<<t14_BkgHist[7]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("vbf_maxpt_j1_eta");
h2->GetXaxis()->CenterTitle(1);
h2->SetMinimum(0.5);
h2->SetMaximum(1.5);
h2->GetXaxis()->SetTitleOffset(0.8);
h2->GetXaxis()->SetLabelSize(0.033*yscale);
h2->GetXaxis()->SetTitleSize(0.036*yscale);
h2->GetXaxis()->SetTickLength(0.03*yscale);
h2->GetYaxis()->SetTitleOffset(0.3);
h2->GetYaxis()->SetNdivisions(5);
h2->GetYaxis()->SetLabelSize(0.033*yscale);
h2->GetYaxis()->SetTitleSize(0.036*yscale);
h2->Draw("");
	c1->SaveAs("vbf_maxpt_j1_eta.pdf");
	c1->SaveAs("vbf_maxpt_j1_eta.png");
	c1->SaveAs("vbf_maxpt_j1_eta.C");
	c1->SaveAs("vbf_maxpt_j1_eta.root");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[8]->SetBottomMargin(0.05287462);
pad[8]->SetLogy(1);
pad[8]->Draw();
pad[8]->cd();

	t0_BkgHist[8]->Scale(0.148600);
	HistMax = t0_BkgHist[8]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t0_BkgHist[8],"VV","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t1_BkgHist[8]->Scale(0.002400);
	HistMax = t1_BkgHist[8]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t2_BkgHist[8]->Scale(0.000700);
	HistMax = t2_BkgHist[8]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t3_BkgHist[8]->Scale(0.206800);
	HistMax = t3_BkgHist[8]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t3_BkgHist[8],"S Top","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t4_BkgHist[8]->Scale(0.209600);
	HistMax = t4_BkgHist[8]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t5_BkgHist[8]->Scale(0.089900);
	HistMax = t5_BkgHist[8]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t6_BkgHist[8]->Scale(0.021200);
	HistMax = t6_BkgHist[8]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t7_BkgHist[8]->Scale(0.283600);
	HistMax = t7_BkgHist[8]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t7_BkgHist[8],"WJets","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t8_BkgHist[8]->Scale(0.420700);
	HistMax = t8_BkgHist[8]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t9_BkgHist[8]->Scale(0.031300);
	HistMax = t9_BkgHist[8]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t10_BkgHist[8]->Scale(0.000700);
	HistMax = t10_BkgHist[8]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t11_BkgHist[8]->Scale(0.144400);
	HistMax = t11_BkgHist[8]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t12_BkgHist[8]->Scale(0.019900);
	HistMax = t12_BkgHist[8]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t13_BkgHist[8]->Scale(0.004800);
	HistMax = t13_BkgHist[8]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t14_BkgHist[8]->Scale(0.026500);
	HistMax = t14_BkgHist[8]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t14_BkgHist[8],"TTbar","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	DataHist[8]->Sumw2();
	HistMax = DataHist[8]->GetMaximum()*1.80;
	leg->AddEntry(DataHist[8],"Data","pe");
	yMax=HistMax;

	hs[8]->Add(t0_BkgHist[8],"hist");
	hs[8]->Add(t1_BkgHist[8],"hist");
	hs[8]->Add(t2_BkgHist[8],"hist");
	hs[8]->Add(t3_BkgHist[8],"hist");
	hs[8]->Add(t4_BkgHist[8],"hist");
	hs[8]->Add(t5_BkgHist[8],"hist");
	hs[8]->Add(t6_BkgHist[8],"hist");
	hs[8]->Add(t7_BkgHist[8],"hist");
	hs[8]->Add(t8_BkgHist[8],"hist");
	hs[8]->Add(t9_BkgHist[8],"hist");
	hs[8]->Add(t10_BkgHist[8],"hist");
	hs[8]->Add(t11_BkgHist[8],"hist");
	hs[8]->Add(t12_BkgHist[8],"hist");
	hs[8]->Add(t13_BkgHist[8],"hist");
	hs[8]->Add(t14_BkgHist[8],"hist");
	hs[8]->SetMaximum(yMax);
	hs[8]->SetMinimum(0.1);
	hs[8]->Draw();
	DataHist[8]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[8]->Clone();
hRatio[8]->Add(t0_BkgHist[8]);
hRatio[8]->Add(t1_BkgHist[8]);
hRatio[8]->Add(t2_BkgHist[8]);
hRatio[8]->Add(t3_BkgHist[8]);
hRatio[8]->Add(t4_BkgHist[8]);
hRatio[8]->Add(t5_BkgHist[8]);
hRatio[8]->Add(t6_BkgHist[8]);
hRatio[8]->Add(t7_BkgHist[8]);
hRatio[8]->Add(t8_BkgHist[8]);
hRatio[8]->Add(t9_BkgHist[8]);
hRatio[8]->Add(t10_BkgHist[8]);
hRatio[8]->Add(t11_BkgHist[8]);
hRatio[8]->Add(t12_BkgHist[8]);
hRatio[8]->Add(t13_BkgHist[8]);
hRatio[8]->Add(t14_BkgHist[8]);


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
cout<<"Ratio of Data/MC = "<<(DataHist[8]->Integral())/(hRatio[8]->Integral())<<endl;
cout<<"Number of event in WW  = "<<t0_BkgHist[8]->Integral()<<endl;
cout<<"Number of event in WZ  = "<<t1_BkgHist[8]->Integral()<<endl;
cout<<"Number of event in ZZ  = "<<t2_BkgHist[8]->Integral()<<endl;
cout<<"Number of event in tWch  = "<<t3_BkgHist[8]->Integral()<<endl;
cout<<"Number of event in tWch_bar  = "<<t4_BkgHist[8]->Integral()<<endl;
cout<<"Number of event in tch_bar  = "<<t5_BkgHist[8]->Integral()<<endl;
cout<<"Number of event in sch  = "<<t6_BkgHist[8]->Integral()<<endl;
cout<<"Number of event in WJets100  = "<<t7_BkgHist[8]->Integral()<<endl;
cout<<"Number of event in WJets200  = "<<t8_BkgHist[8]->Integral()<<endl;
cout<<"Number of event in WJets1200  = "<<t9_BkgHist[8]->Integral()<<endl;
cout<<"Number of event in WJets2500  = "<<t10_BkgHist[8]->Integral()<<endl;
cout<<"Number of event in WJets400  = "<<t11_BkgHist[8]->Integral()<<endl;
cout<<"Number of event in WJets600  = "<<t12_BkgHist[8]->Integral()<<endl;
cout<<"Number of event in WJets  = "<<t13_BkgHist[8]->Integral()<<endl;
cout<<"Number of event in TTbar  = "<<t14_BkgHist[8]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("vbf_maxpt_j2_eta");
h2->GetXaxis()->CenterTitle(1);
h2->SetMinimum(0.5);
h2->SetMaximum(1.5);
h2->GetXaxis()->SetTitleOffset(0.8);
h2->GetXaxis()->SetLabelSize(0.033*yscale);
h2->GetXaxis()->SetTitleSize(0.036*yscale);
h2->GetXaxis()->SetTickLength(0.03*yscale);
h2->GetYaxis()->SetTitleOffset(0.3);
h2->GetYaxis()->SetNdivisions(5);
h2->GetYaxis()->SetLabelSize(0.033*yscale);
h2->GetYaxis()->SetTitleSize(0.036*yscale);
h2->Draw("");
	c1->SaveAs("vbf_maxpt_j2_eta.pdf");
	c1->SaveAs("vbf_maxpt_j2_eta.png");
	c1->SaveAs("vbf_maxpt_j2_eta.C");
	c1->SaveAs("vbf_maxpt_j2_eta.root");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[9]->SetBottomMargin(0.05287462);
pad[9]->SetLogy(1);
pad[9]->Draw();
pad[9]->cd();

	t0_BkgHist[9]->Scale(0.148600);
	HistMax = t0_BkgHist[9]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t0_BkgHist[9],"VV","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t1_BkgHist[9]->Scale(0.002400);
	HistMax = t1_BkgHist[9]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t2_BkgHist[9]->Scale(0.000700);
	HistMax = t2_BkgHist[9]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t3_BkgHist[9]->Scale(0.206800);
	HistMax = t3_BkgHist[9]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t3_BkgHist[9],"S Top","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t4_BkgHist[9]->Scale(0.209600);
	HistMax = t4_BkgHist[9]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t5_BkgHist[9]->Scale(0.089900);
	HistMax = t5_BkgHist[9]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t6_BkgHist[9]->Scale(0.021200);
	HistMax = t6_BkgHist[9]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t7_BkgHist[9]->Scale(0.283600);
	HistMax = t7_BkgHist[9]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t7_BkgHist[9],"WJets","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t8_BkgHist[9]->Scale(0.420700);
	HistMax = t8_BkgHist[9]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t9_BkgHist[9]->Scale(0.031300);
	HistMax = t9_BkgHist[9]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t10_BkgHist[9]->Scale(0.000700);
	HistMax = t10_BkgHist[9]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t11_BkgHist[9]->Scale(0.144400);
	HistMax = t11_BkgHist[9]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t12_BkgHist[9]->Scale(0.019900);
	HistMax = t12_BkgHist[9]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t13_BkgHist[9]->Scale(0.004800);
	HistMax = t13_BkgHist[9]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t14_BkgHist[9]->Scale(0.026500);
	HistMax = t14_BkgHist[9]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t14_BkgHist[9],"TTbar","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	DataHist[9]->Sumw2();
	HistMax = DataHist[9]->GetMaximum()*1.80;
	leg->AddEntry(DataHist[9],"Data","pe");
	yMax=HistMax;

	hs[9]->Add(t0_BkgHist[9],"hist");
	hs[9]->Add(t1_BkgHist[9],"hist");
	hs[9]->Add(t2_BkgHist[9],"hist");
	hs[9]->Add(t3_BkgHist[9],"hist");
	hs[9]->Add(t4_BkgHist[9],"hist");
	hs[9]->Add(t5_BkgHist[9],"hist");
	hs[9]->Add(t6_BkgHist[9],"hist");
	hs[9]->Add(t7_BkgHist[9],"hist");
	hs[9]->Add(t8_BkgHist[9],"hist");
	hs[9]->Add(t9_BkgHist[9],"hist");
	hs[9]->Add(t10_BkgHist[9],"hist");
	hs[9]->Add(t11_BkgHist[9],"hist");
	hs[9]->Add(t12_BkgHist[9],"hist");
	hs[9]->Add(t13_BkgHist[9],"hist");
	hs[9]->Add(t14_BkgHist[9],"hist");
	hs[9]->SetMaximum(yMax);
	hs[9]->SetMinimum(0.1);
	hs[9]->Draw();
	DataHist[9]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[9]->Clone();
hRatio[9]->Add(t0_BkgHist[9]);
hRatio[9]->Add(t1_BkgHist[9]);
hRatio[9]->Add(t2_BkgHist[9]);
hRatio[9]->Add(t3_BkgHist[9]);
hRatio[9]->Add(t4_BkgHist[9]);
hRatio[9]->Add(t5_BkgHist[9]);
hRatio[9]->Add(t6_BkgHist[9]);
hRatio[9]->Add(t7_BkgHist[9]);
hRatio[9]->Add(t8_BkgHist[9]);
hRatio[9]->Add(t9_BkgHist[9]);
hRatio[9]->Add(t10_BkgHist[9]);
hRatio[9]->Add(t11_BkgHist[9]);
hRatio[9]->Add(t12_BkgHist[9]);
hRatio[9]->Add(t13_BkgHist[9]);
hRatio[9]->Add(t14_BkgHist[9]);


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
cout<<"Ratio of Data/MC = "<<(DataHist[9]->Integral())/(hRatio[9]->Integral())<<endl;
cout<<"Number of event in WW  = "<<t0_BkgHist[9]->Integral()<<endl;
cout<<"Number of event in WZ  = "<<t1_BkgHist[9]->Integral()<<endl;
cout<<"Number of event in ZZ  = "<<t2_BkgHist[9]->Integral()<<endl;
cout<<"Number of event in tWch  = "<<t3_BkgHist[9]->Integral()<<endl;
cout<<"Number of event in tWch_bar  = "<<t4_BkgHist[9]->Integral()<<endl;
cout<<"Number of event in tch_bar  = "<<t5_BkgHist[9]->Integral()<<endl;
cout<<"Number of event in sch  = "<<t6_BkgHist[9]->Integral()<<endl;
cout<<"Number of event in WJets100  = "<<t7_BkgHist[9]->Integral()<<endl;
cout<<"Number of event in WJets200  = "<<t8_BkgHist[9]->Integral()<<endl;
cout<<"Number of event in WJets1200  = "<<t9_BkgHist[9]->Integral()<<endl;
cout<<"Number of event in WJets2500  = "<<t10_BkgHist[9]->Integral()<<endl;
cout<<"Number of event in WJets400  = "<<t11_BkgHist[9]->Integral()<<endl;
cout<<"Number of event in WJets600  = "<<t12_BkgHist[9]->Integral()<<endl;
cout<<"Number of event in WJets  = "<<t13_BkgHist[9]->Integral()<<endl;
cout<<"Number of event in TTbar  = "<<t14_BkgHist[9]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("AK4_jet1_pt");
h2->GetXaxis()->CenterTitle(1);
h2->SetMinimum(0.5);
h2->SetMaximum(1.5);
h2->GetXaxis()->SetTitleOffset(0.8);
h2->GetXaxis()->SetLabelSize(0.033*yscale);
h2->GetXaxis()->SetTitleSize(0.036*yscale);
h2->GetXaxis()->SetTickLength(0.03*yscale);
h2->GetYaxis()->SetTitleOffset(0.3);
h2->GetYaxis()->SetNdivisions(5);
h2->GetYaxis()->SetLabelSize(0.033*yscale);
h2->GetYaxis()->SetTitleSize(0.036*yscale);
h2->Draw("");
	c1->SaveAs("AK4_jet1_pt.pdf");
	c1->SaveAs("AK4_jet1_pt.png");
	c1->SaveAs("AK4_jet1_pt.C");
	c1->SaveAs("AK4_jet1_pt.root");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[10]->SetBottomMargin(0.05287462);
pad[10]->SetLogy(1);
pad[10]->Draw();
pad[10]->cd();

	t0_BkgHist[10]->Scale(0.148600);
	HistMax = t0_BkgHist[10]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t0_BkgHist[10],"VV","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t1_BkgHist[10]->Scale(0.002400);
	HistMax = t1_BkgHist[10]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t2_BkgHist[10]->Scale(0.000700);
	HistMax = t2_BkgHist[10]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t3_BkgHist[10]->Scale(0.206800);
	HistMax = t3_BkgHist[10]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t3_BkgHist[10],"S Top","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t4_BkgHist[10]->Scale(0.209600);
	HistMax = t4_BkgHist[10]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t5_BkgHist[10]->Scale(0.089900);
	HistMax = t5_BkgHist[10]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t6_BkgHist[10]->Scale(0.021200);
	HistMax = t6_BkgHist[10]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t7_BkgHist[10]->Scale(0.283600);
	HistMax = t7_BkgHist[10]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t7_BkgHist[10],"WJets","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t8_BkgHist[10]->Scale(0.420700);
	HistMax = t8_BkgHist[10]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t9_BkgHist[10]->Scale(0.031300);
	HistMax = t9_BkgHist[10]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t10_BkgHist[10]->Scale(0.000700);
	HistMax = t10_BkgHist[10]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t11_BkgHist[10]->Scale(0.144400);
	HistMax = t11_BkgHist[10]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t12_BkgHist[10]->Scale(0.019900);
	HistMax = t12_BkgHist[10]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t13_BkgHist[10]->Scale(0.004800);
	HistMax = t13_BkgHist[10]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t14_BkgHist[10]->Scale(0.026500);
	HistMax = t14_BkgHist[10]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t14_BkgHist[10],"TTbar","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	DataHist[10]->Sumw2();
	HistMax = DataHist[10]->GetMaximum()*1.80;
	leg->AddEntry(DataHist[10],"Data","pe");
	yMax=HistMax;

	hs[10]->Add(t0_BkgHist[10],"hist");
	hs[10]->Add(t1_BkgHist[10],"hist");
	hs[10]->Add(t2_BkgHist[10],"hist");
	hs[10]->Add(t3_BkgHist[10],"hist");
	hs[10]->Add(t4_BkgHist[10],"hist");
	hs[10]->Add(t5_BkgHist[10],"hist");
	hs[10]->Add(t6_BkgHist[10],"hist");
	hs[10]->Add(t7_BkgHist[10],"hist");
	hs[10]->Add(t8_BkgHist[10],"hist");
	hs[10]->Add(t9_BkgHist[10],"hist");
	hs[10]->Add(t10_BkgHist[10],"hist");
	hs[10]->Add(t11_BkgHist[10],"hist");
	hs[10]->Add(t12_BkgHist[10],"hist");
	hs[10]->Add(t13_BkgHist[10],"hist");
	hs[10]->Add(t14_BkgHist[10],"hist");
	hs[10]->SetMaximum(yMax);
	hs[10]->SetMinimum(0.1);
	hs[10]->Draw();
	DataHist[10]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[10]->Clone();
hRatio[10]->Add(t0_BkgHist[10]);
hRatio[10]->Add(t1_BkgHist[10]);
hRatio[10]->Add(t2_BkgHist[10]);
hRatio[10]->Add(t3_BkgHist[10]);
hRatio[10]->Add(t4_BkgHist[10]);
hRatio[10]->Add(t5_BkgHist[10]);
hRatio[10]->Add(t6_BkgHist[10]);
hRatio[10]->Add(t7_BkgHist[10]);
hRatio[10]->Add(t8_BkgHist[10]);
hRatio[10]->Add(t9_BkgHist[10]);
hRatio[10]->Add(t10_BkgHist[10]);
hRatio[10]->Add(t11_BkgHist[10]);
hRatio[10]->Add(t12_BkgHist[10]);
hRatio[10]->Add(t13_BkgHist[10]);
hRatio[10]->Add(t14_BkgHist[10]);


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
cout<<"Ratio of Data/MC = "<<(DataHist[10]->Integral())/(hRatio[10]->Integral())<<endl;
cout<<"Number of event in WW  = "<<t0_BkgHist[10]->Integral()<<endl;
cout<<"Number of event in WZ  = "<<t1_BkgHist[10]->Integral()<<endl;
cout<<"Number of event in ZZ  = "<<t2_BkgHist[10]->Integral()<<endl;
cout<<"Number of event in tWch  = "<<t3_BkgHist[10]->Integral()<<endl;
cout<<"Number of event in tWch_bar  = "<<t4_BkgHist[10]->Integral()<<endl;
cout<<"Number of event in tch_bar  = "<<t5_BkgHist[10]->Integral()<<endl;
cout<<"Number of event in sch  = "<<t6_BkgHist[10]->Integral()<<endl;
cout<<"Number of event in WJets100  = "<<t7_BkgHist[10]->Integral()<<endl;
cout<<"Number of event in WJets200  = "<<t8_BkgHist[10]->Integral()<<endl;
cout<<"Number of event in WJets1200  = "<<t9_BkgHist[10]->Integral()<<endl;
cout<<"Number of event in WJets2500  = "<<t10_BkgHist[10]->Integral()<<endl;
cout<<"Number of event in WJets400  = "<<t11_BkgHist[10]->Integral()<<endl;
cout<<"Number of event in WJets600  = "<<t12_BkgHist[10]->Integral()<<endl;
cout<<"Number of event in WJets  = "<<t13_BkgHist[10]->Integral()<<endl;
cout<<"Number of event in TTbar  = "<<t14_BkgHist[10]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("AK4_jet2_pt");
h2->GetXaxis()->CenterTitle(1);
h2->SetMinimum(0.5);
h2->SetMaximum(1.5);
h2->GetXaxis()->SetTitleOffset(0.8);
h2->GetXaxis()->SetLabelSize(0.033*yscale);
h2->GetXaxis()->SetTitleSize(0.036*yscale);
h2->GetXaxis()->SetTickLength(0.03*yscale);
h2->GetYaxis()->SetTitleOffset(0.3);
h2->GetYaxis()->SetNdivisions(5);
h2->GetYaxis()->SetLabelSize(0.033*yscale);
h2->GetYaxis()->SetTitleSize(0.036*yscale);
h2->Draw("");
	c1->SaveAs("AK4_jet2_pt.pdf");
	c1->SaveAs("AK4_jet2_pt.png");
	c1->SaveAs("AK4_jet2_pt.C");
	c1->SaveAs("AK4_jet2_pt.root");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[11]->SetBottomMargin(0.05287462);
pad[11]->SetLogy(1);
pad[11]->Draw();
pad[11]->cd();

	t0_BkgHist[11]->Scale(0.148600);
	HistMax = t0_BkgHist[11]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t0_BkgHist[11],"VV","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t1_BkgHist[11]->Scale(0.002400);
	HistMax = t1_BkgHist[11]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t2_BkgHist[11]->Scale(0.000700);
	HistMax = t2_BkgHist[11]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t3_BkgHist[11]->Scale(0.206800);
	HistMax = t3_BkgHist[11]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t3_BkgHist[11],"S Top","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t4_BkgHist[11]->Scale(0.209600);
	HistMax = t4_BkgHist[11]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t5_BkgHist[11]->Scale(0.089900);
	HistMax = t5_BkgHist[11]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t6_BkgHist[11]->Scale(0.021200);
	HistMax = t6_BkgHist[11]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t7_BkgHist[11]->Scale(0.283600);
	HistMax = t7_BkgHist[11]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t7_BkgHist[11],"WJets","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t8_BkgHist[11]->Scale(0.420700);
	HistMax = t8_BkgHist[11]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t9_BkgHist[11]->Scale(0.031300);
	HistMax = t9_BkgHist[11]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t10_BkgHist[11]->Scale(0.000700);
	HistMax = t10_BkgHist[11]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t11_BkgHist[11]->Scale(0.144400);
	HistMax = t11_BkgHist[11]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t12_BkgHist[11]->Scale(0.019900);
	HistMax = t12_BkgHist[11]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t13_BkgHist[11]->Scale(0.004800);
	HistMax = t13_BkgHist[11]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t14_BkgHist[11]->Scale(0.026500);
	HistMax = t14_BkgHist[11]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t14_BkgHist[11],"TTbar","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	DataHist[11]->Sumw2();
	HistMax = DataHist[11]->GetMaximum()*1.80;
	leg->AddEntry(DataHist[11],"Data","pe");
	yMax=HistMax;

	hs[11]->Add(t0_BkgHist[11],"hist");
	hs[11]->Add(t1_BkgHist[11],"hist");
	hs[11]->Add(t2_BkgHist[11],"hist");
	hs[11]->Add(t3_BkgHist[11],"hist");
	hs[11]->Add(t4_BkgHist[11],"hist");
	hs[11]->Add(t5_BkgHist[11],"hist");
	hs[11]->Add(t6_BkgHist[11],"hist");
	hs[11]->Add(t7_BkgHist[11],"hist");
	hs[11]->Add(t8_BkgHist[11],"hist");
	hs[11]->Add(t9_BkgHist[11],"hist");
	hs[11]->Add(t10_BkgHist[11],"hist");
	hs[11]->Add(t11_BkgHist[11],"hist");
	hs[11]->Add(t12_BkgHist[11],"hist");
	hs[11]->Add(t13_BkgHist[11],"hist");
	hs[11]->Add(t14_BkgHist[11],"hist");
	hs[11]->SetMaximum(yMax);
	hs[11]->SetMinimum(0.1);
	hs[11]->Draw();
	DataHist[11]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[11]->Clone();
hRatio[11]->Add(t0_BkgHist[11]);
hRatio[11]->Add(t1_BkgHist[11]);
hRatio[11]->Add(t2_BkgHist[11]);
hRatio[11]->Add(t3_BkgHist[11]);
hRatio[11]->Add(t4_BkgHist[11]);
hRatio[11]->Add(t5_BkgHist[11]);
hRatio[11]->Add(t6_BkgHist[11]);
hRatio[11]->Add(t7_BkgHist[11]);
hRatio[11]->Add(t8_BkgHist[11]);
hRatio[11]->Add(t9_BkgHist[11]);
hRatio[11]->Add(t10_BkgHist[11]);
hRatio[11]->Add(t11_BkgHist[11]);
hRatio[11]->Add(t12_BkgHist[11]);
hRatio[11]->Add(t13_BkgHist[11]);
hRatio[11]->Add(t14_BkgHist[11]);


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
cout<<"Ratio of Data/MC = "<<(DataHist[11]->Integral())/(hRatio[11]->Integral())<<endl;
cout<<"Number of event in WW  = "<<t0_BkgHist[11]->Integral()<<endl;
cout<<"Number of event in WZ  = "<<t1_BkgHist[11]->Integral()<<endl;
cout<<"Number of event in ZZ  = "<<t2_BkgHist[11]->Integral()<<endl;
cout<<"Number of event in tWch  = "<<t3_BkgHist[11]->Integral()<<endl;
cout<<"Number of event in tWch_bar  = "<<t4_BkgHist[11]->Integral()<<endl;
cout<<"Number of event in tch_bar  = "<<t5_BkgHist[11]->Integral()<<endl;
cout<<"Number of event in sch  = "<<t6_BkgHist[11]->Integral()<<endl;
cout<<"Number of event in WJets100  = "<<t7_BkgHist[11]->Integral()<<endl;
cout<<"Number of event in WJets200  = "<<t8_BkgHist[11]->Integral()<<endl;
cout<<"Number of event in WJets1200  = "<<t9_BkgHist[11]->Integral()<<endl;
cout<<"Number of event in WJets2500  = "<<t10_BkgHist[11]->Integral()<<endl;
cout<<"Number of event in WJets400  = "<<t11_BkgHist[11]->Integral()<<endl;
cout<<"Number of event in WJets600  = "<<t12_BkgHist[11]->Integral()<<endl;
cout<<"Number of event in WJets  = "<<t13_BkgHist[11]->Integral()<<endl;
cout<<"Number of event in TTbar  = "<<t14_BkgHist[11]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("AK4_jet1_eta");
h2->GetXaxis()->CenterTitle(1);
h2->SetMinimum(0.5);
h2->SetMaximum(1.5);
h2->GetXaxis()->SetTitleOffset(0.8);
h2->GetXaxis()->SetLabelSize(0.033*yscale);
h2->GetXaxis()->SetTitleSize(0.036*yscale);
h2->GetXaxis()->SetTickLength(0.03*yscale);
h2->GetYaxis()->SetTitleOffset(0.3);
h2->GetYaxis()->SetNdivisions(5);
h2->GetYaxis()->SetLabelSize(0.033*yscale);
h2->GetYaxis()->SetTitleSize(0.036*yscale);
h2->Draw("");
	c1->SaveAs("AK4_jet1_eta.pdf");
	c1->SaveAs("AK4_jet1_eta.png");
	c1->SaveAs("AK4_jet1_eta.C");
	c1->SaveAs("AK4_jet1_eta.root");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[12]->SetBottomMargin(0.05287462);
pad[12]->SetLogy(1);
pad[12]->Draw();
pad[12]->cd();

	t0_BkgHist[12]->Scale(0.148600);
	HistMax = t0_BkgHist[12]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t0_BkgHist[12],"VV","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t1_BkgHist[12]->Scale(0.002400);
	HistMax = t1_BkgHist[12]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t2_BkgHist[12]->Scale(0.000700);
	HistMax = t2_BkgHist[12]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t3_BkgHist[12]->Scale(0.206800);
	HistMax = t3_BkgHist[12]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t3_BkgHist[12],"S Top","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t4_BkgHist[12]->Scale(0.209600);
	HistMax = t4_BkgHist[12]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t5_BkgHist[12]->Scale(0.089900);
	HistMax = t5_BkgHist[12]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t6_BkgHist[12]->Scale(0.021200);
	HistMax = t6_BkgHist[12]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t7_BkgHist[12]->Scale(0.283600);
	HistMax = t7_BkgHist[12]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t7_BkgHist[12],"WJets","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t8_BkgHist[12]->Scale(0.420700);
	HistMax = t8_BkgHist[12]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t9_BkgHist[12]->Scale(0.031300);
	HistMax = t9_BkgHist[12]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t10_BkgHist[12]->Scale(0.000700);
	HistMax = t10_BkgHist[12]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t11_BkgHist[12]->Scale(0.144400);
	HistMax = t11_BkgHist[12]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t12_BkgHist[12]->Scale(0.019900);
	HistMax = t12_BkgHist[12]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t13_BkgHist[12]->Scale(0.004800);
	HistMax = t13_BkgHist[12]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t14_BkgHist[12]->Scale(0.026500);
	HistMax = t14_BkgHist[12]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t14_BkgHist[12],"TTbar","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	DataHist[12]->Sumw2();
	HistMax = DataHist[12]->GetMaximum()*1.80;
	leg->AddEntry(DataHist[12],"Data","pe");
	yMax=HistMax;

	hs[12]->Add(t0_BkgHist[12],"hist");
	hs[12]->Add(t1_BkgHist[12],"hist");
	hs[12]->Add(t2_BkgHist[12],"hist");
	hs[12]->Add(t3_BkgHist[12],"hist");
	hs[12]->Add(t4_BkgHist[12],"hist");
	hs[12]->Add(t5_BkgHist[12],"hist");
	hs[12]->Add(t6_BkgHist[12],"hist");
	hs[12]->Add(t7_BkgHist[12],"hist");
	hs[12]->Add(t8_BkgHist[12],"hist");
	hs[12]->Add(t9_BkgHist[12],"hist");
	hs[12]->Add(t10_BkgHist[12],"hist");
	hs[12]->Add(t11_BkgHist[12],"hist");
	hs[12]->Add(t12_BkgHist[12],"hist");
	hs[12]->Add(t13_BkgHist[12],"hist");
	hs[12]->Add(t14_BkgHist[12],"hist");
	hs[12]->SetMaximum(yMax);
	hs[12]->SetMinimum(0.1);
	hs[12]->Draw();
	DataHist[12]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[12]->Clone();
hRatio[12]->Add(t0_BkgHist[12]);
hRatio[12]->Add(t1_BkgHist[12]);
hRatio[12]->Add(t2_BkgHist[12]);
hRatio[12]->Add(t3_BkgHist[12]);
hRatio[12]->Add(t4_BkgHist[12]);
hRatio[12]->Add(t5_BkgHist[12]);
hRatio[12]->Add(t6_BkgHist[12]);
hRatio[12]->Add(t7_BkgHist[12]);
hRatio[12]->Add(t8_BkgHist[12]);
hRatio[12]->Add(t9_BkgHist[12]);
hRatio[12]->Add(t10_BkgHist[12]);
hRatio[12]->Add(t11_BkgHist[12]);
hRatio[12]->Add(t12_BkgHist[12]);
hRatio[12]->Add(t13_BkgHist[12]);
hRatio[12]->Add(t14_BkgHist[12]);


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
cout<<"Ratio of Data/MC = "<<(DataHist[12]->Integral())/(hRatio[12]->Integral())<<endl;
cout<<"Number of event in WW  = "<<t0_BkgHist[12]->Integral()<<endl;
cout<<"Number of event in WZ  = "<<t1_BkgHist[12]->Integral()<<endl;
cout<<"Number of event in ZZ  = "<<t2_BkgHist[12]->Integral()<<endl;
cout<<"Number of event in tWch  = "<<t3_BkgHist[12]->Integral()<<endl;
cout<<"Number of event in tWch_bar  = "<<t4_BkgHist[12]->Integral()<<endl;
cout<<"Number of event in tch_bar  = "<<t5_BkgHist[12]->Integral()<<endl;
cout<<"Number of event in sch  = "<<t6_BkgHist[12]->Integral()<<endl;
cout<<"Number of event in WJets100  = "<<t7_BkgHist[12]->Integral()<<endl;
cout<<"Number of event in WJets200  = "<<t8_BkgHist[12]->Integral()<<endl;
cout<<"Number of event in WJets1200  = "<<t9_BkgHist[12]->Integral()<<endl;
cout<<"Number of event in WJets2500  = "<<t10_BkgHist[12]->Integral()<<endl;
cout<<"Number of event in WJets400  = "<<t11_BkgHist[12]->Integral()<<endl;
cout<<"Number of event in WJets600  = "<<t12_BkgHist[12]->Integral()<<endl;
cout<<"Number of event in WJets  = "<<t13_BkgHist[12]->Integral()<<endl;
cout<<"Number of event in TTbar  = "<<t14_BkgHist[12]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("AK4_jet2_eta");
h2->GetXaxis()->CenterTitle(1);
h2->SetMinimum(0.5);
h2->SetMaximum(1.5);
h2->GetXaxis()->SetTitleOffset(0.8);
h2->GetXaxis()->SetLabelSize(0.033*yscale);
h2->GetXaxis()->SetTitleSize(0.036*yscale);
h2->GetXaxis()->SetTickLength(0.03*yscale);
h2->GetYaxis()->SetTitleOffset(0.3);
h2->GetYaxis()->SetNdivisions(5);
h2->GetYaxis()->SetLabelSize(0.033*yscale);
h2->GetYaxis()->SetTitleSize(0.036*yscale);
h2->Draw("");
	c1->SaveAs("AK4_jet2_eta.pdf");
	c1->SaveAs("AK4_jet2_eta.png");
	c1->SaveAs("AK4_jet2_eta.C");
	c1->SaveAs("AK4_jet2_eta.root");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[13]->SetBottomMargin(0.05287462);
pad[13]->SetLogy(1);
pad[13]->Draw();
pad[13]->cd();

	t0_BkgHist[13]->Scale(0.148600);
	HistMax = t0_BkgHist[13]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t0_BkgHist[13],"VV","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t1_BkgHist[13]->Scale(0.002400);
	HistMax = t1_BkgHist[13]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t2_BkgHist[13]->Scale(0.000700);
	HistMax = t2_BkgHist[13]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t3_BkgHist[13]->Scale(0.206800);
	HistMax = t3_BkgHist[13]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t3_BkgHist[13],"S Top","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t4_BkgHist[13]->Scale(0.209600);
	HistMax = t4_BkgHist[13]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t5_BkgHist[13]->Scale(0.089900);
	HistMax = t5_BkgHist[13]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t6_BkgHist[13]->Scale(0.021200);
	HistMax = t6_BkgHist[13]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t7_BkgHist[13]->Scale(0.283600);
	HistMax = t7_BkgHist[13]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t7_BkgHist[13],"WJets","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t8_BkgHist[13]->Scale(0.420700);
	HistMax = t8_BkgHist[13]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t9_BkgHist[13]->Scale(0.031300);
	HistMax = t9_BkgHist[13]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t10_BkgHist[13]->Scale(0.000700);
	HistMax = t10_BkgHist[13]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t11_BkgHist[13]->Scale(0.144400);
	HistMax = t11_BkgHist[13]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t12_BkgHist[13]->Scale(0.019900);
	HistMax = t12_BkgHist[13]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t13_BkgHist[13]->Scale(0.004800);
	HistMax = t13_BkgHist[13]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t14_BkgHist[13]->Scale(0.026500);
	HistMax = t14_BkgHist[13]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t14_BkgHist[13],"TTbar","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	DataHist[13]->Sumw2();
	HistMax = DataHist[13]->GetMaximum()*1.80;
	leg->AddEntry(DataHist[13],"Data","pe");
	yMax=HistMax;

	hs[13]->Add(t0_BkgHist[13],"hist");
	hs[13]->Add(t1_BkgHist[13],"hist");
	hs[13]->Add(t2_BkgHist[13],"hist");
	hs[13]->Add(t3_BkgHist[13],"hist");
	hs[13]->Add(t4_BkgHist[13],"hist");
	hs[13]->Add(t5_BkgHist[13],"hist");
	hs[13]->Add(t6_BkgHist[13],"hist");
	hs[13]->Add(t7_BkgHist[13],"hist");
	hs[13]->Add(t8_BkgHist[13],"hist");
	hs[13]->Add(t9_BkgHist[13],"hist");
	hs[13]->Add(t10_BkgHist[13],"hist");
	hs[13]->Add(t11_BkgHist[13],"hist");
	hs[13]->Add(t12_BkgHist[13],"hist");
	hs[13]->Add(t13_BkgHist[13],"hist");
	hs[13]->Add(t14_BkgHist[13],"hist");
	hs[13]->SetMaximum(yMax);
	hs[13]->SetMinimum(0.1);
	hs[13]->Draw();
	DataHist[13]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[13]->Clone();
hRatio[13]->Add(t0_BkgHist[13]);
hRatio[13]->Add(t1_BkgHist[13]);
hRatio[13]->Add(t2_BkgHist[13]);
hRatio[13]->Add(t3_BkgHist[13]);
hRatio[13]->Add(t4_BkgHist[13]);
hRatio[13]->Add(t5_BkgHist[13]);
hRatio[13]->Add(t6_BkgHist[13]);
hRatio[13]->Add(t7_BkgHist[13]);
hRatio[13]->Add(t8_BkgHist[13]);
hRatio[13]->Add(t9_BkgHist[13]);
hRatio[13]->Add(t10_BkgHist[13]);
hRatio[13]->Add(t11_BkgHist[13]);
hRatio[13]->Add(t12_BkgHist[13]);
hRatio[13]->Add(t13_BkgHist[13]);
hRatio[13]->Add(t14_BkgHist[13]);


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
cout<<"Ratio of Data/MC = "<<(DataHist[13]->Integral())/(hRatio[13]->Integral())<<endl;
cout<<"Number of event in WW  = "<<t0_BkgHist[13]->Integral()<<endl;
cout<<"Number of event in WZ  = "<<t1_BkgHist[13]->Integral()<<endl;
cout<<"Number of event in ZZ  = "<<t2_BkgHist[13]->Integral()<<endl;
cout<<"Number of event in tWch  = "<<t3_BkgHist[13]->Integral()<<endl;
cout<<"Number of event in tWch_bar  = "<<t4_BkgHist[13]->Integral()<<endl;
cout<<"Number of event in tch_bar  = "<<t5_BkgHist[13]->Integral()<<endl;
cout<<"Number of event in sch  = "<<t6_BkgHist[13]->Integral()<<endl;
cout<<"Number of event in WJets100  = "<<t7_BkgHist[13]->Integral()<<endl;
cout<<"Number of event in WJets200  = "<<t8_BkgHist[13]->Integral()<<endl;
cout<<"Number of event in WJets1200  = "<<t9_BkgHist[13]->Integral()<<endl;
cout<<"Number of event in WJets2500  = "<<t10_BkgHist[13]->Integral()<<endl;
cout<<"Number of event in WJets400  = "<<t11_BkgHist[13]->Integral()<<endl;
cout<<"Number of event in WJets600  = "<<t12_BkgHist[13]->Integral()<<endl;
cout<<"Number of event in WJets  = "<<t13_BkgHist[13]->Integral()<<endl;
cout<<"Number of event in TTbar  = "<<t14_BkgHist[13]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("vbf_maxpt_jj_m");
h2->GetXaxis()->CenterTitle(1);
h2->SetMinimum(0.5);
h2->SetMaximum(1.5);
h2->GetXaxis()->SetTitleOffset(0.8);
h2->GetXaxis()->SetLabelSize(0.033*yscale);
h2->GetXaxis()->SetTitleSize(0.036*yscale);
h2->GetXaxis()->SetTickLength(0.03*yscale);
h2->GetYaxis()->SetTitleOffset(0.3);
h2->GetYaxis()->SetNdivisions(5);
h2->GetYaxis()->SetLabelSize(0.033*yscale);
h2->GetYaxis()->SetTitleSize(0.036*yscale);
h2->Draw("");
	c1->SaveAs("vbf_maxpt_jj_m.pdf");
	c1->SaveAs("vbf_maxpt_jj_m.png");
	c1->SaveAs("vbf_maxpt_jj_m.C");
	c1->SaveAs("vbf_maxpt_jj_m.root");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[14]->SetBottomMargin(0.05287462);
pad[14]->SetLogy(1);
pad[14]->Draw();
pad[14]->cd();

	t0_BkgHist[14]->Scale(0.148600);
	HistMax = t0_BkgHist[14]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t0_BkgHist[14],"VV","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t1_BkgHist[14]->Scale(0.002400);
	HistMax = t1_BkgHist[14]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t2_BkgHist[14]->Scale(0.000700);
	HistMax = t2_BkgHist[14]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t3_BkgHist[14]->Scale(0.206800);
	HistMax = t3_BkgHist[14]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t3_BkgHist[14],"S Top","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t4_BkgHist[14]->Scale(0.209600);
	HistMax = t4_BkgHist[14]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t5_BkgHist[14]->Scale(0.089900);
	HistMax = t5_BkgHist[14]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t6_BkgHist[14]->Scale(0.021200);
	HistMax = t6_BkgHist[14]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t7_BkgHist[14]->Scale(0.283600);
	HistMax = t7_BkgHist[14]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t7_BkgHist[14],"WJets","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t8_BkgHist[14]->Scale(0.420700);
	HistMax = t8_BkgHist[14]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t9_BkgHist[14]->Scale(0.031300);
	HistMax = t9_BkgHist[14]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t10_BkgHist[14]->Scale(0.000700);
	HistMax = t10_BkgHist[14]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t11_BkgHist[14]->Scale(0.144400);
	HistMax = t11_BkgHist[14]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t12_BkgHist[14]->Scale(0.019900);
	HistMax = t12_BkgHist[14]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t13_BkgHist[14]->Scale(0.004800);
	HistMax = t13_BkgHist[14]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t14_BkgHist[14]->Scale(0.026500);
	HistMax = t14_BkgHist[14]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t14_BkgHist[14],"TTbar","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	DataHist[14]->Sumw2();
	HistMax = DataHist[14]->GetMaximum()*1.80;
	leg->AddEntry(DataHist[14],"Data","pe");
	yMax=HistMax;

	hs[14]->Add(t0_BkgHist[14],"hist");
	hs[14]->Add(t1_BkgHist[14],"hist");
	hs[14]->Add(t2_BkgHist[14],"hist");
	hs[14]->Add(t3_BkgHist[14],"hist");
	hs[14]->Add(t4_BkgHist[14],"hist");
	hs[14]->Add(t5_BkgHist[14],"hist");
	hs[14]->Add(t6_BkgHist[14],"hist");
	hs[14]->Add(t7_BkgHist[14],"hist");
	hs[14]->Add(t8_BkgHist[14],"hist");
	hs[14]->Add(t9_BkgHist[14],"hist");
	hs[14]->Add(t10_BkgHist[14],"hist");
	hs[14]->Add(t11_BkgHist[14],"hist");
	hs[14]->Add(t12_BkgHist[14],"hist");
	hs[14]->Add(t13_BkgHist[14],"hist");
	hs[14]->Add(t14_BkgHist[14],"hist");
	hs[14]->SetMaximum(yMax);
	hs[14]->SetMinimum(0.1);
	hs[14]->Draw();
	DataHist[14]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[14]->Clone();
hRatio[14]->Add(t0_BkgHist[14]);
hRatio[14]->Add(t1_BkgHist[14]);
hRatio[14]->Add(t2_BkgHist[14]);
hRatio[14]->Add(t3_BkgHist[14]);
hRatio[14]->Add(t4_BkgHist[14]);
hRatio[14]->Add(t5_BkgHist[14]);
hRatio[14]->Add(t6_BkgHist[14]);
hRatio[14]->Add(t7_BkgHist[14]);
hRatio[14]->Add(t8_BkgHist[14]);
hRatio[14]->Add(t9_BkgHist[14]);
hRatio[14]->Add(t10_BkgHist[14]);
hRatio[14]->Add(t11_BkgHist[14]);
hRatio[14]->Add(t12_BkgHist[14]);
hRatio[14]->Add(t13_BkgHist[14]);
hRatio[14]->Add(t14_BkgHist[14]);


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
cout<<"Ratio of Data/MC = "<<(DataHist[14]->Integral())/(hRatio[14]->Integral())<<endl;
cout<<"Number of event in WW  = "<<t0_BkgHist[14]->Integral()<<endl;
cout<<"Number of event in WZ  = "<<t1_BkgHist[14]->Integral()<<endl;
cout<<"Number of event in ZZ  = "<<t2_BkgHist[14]->Integral()<<endl;
cout<<"Number of event in tWch  = "<<t3_BkgHist[14]->Integral()<<endl;
cout<<"Number of event in tWch_bar  = "<<t4_BkgHist[14]->Integral()<<endl;
cout<<"Number of event in tch_bar  = "<<t5_BkgHist[14]->Integral()<<endl;
cout<<"Number of event in sch  = "<<t6_BkgHist[14]->Integral()<<endl;
cout<<"Number of event in WJets100  = "<<t7_BkgHist[14]->Integral()<<endl;
cout<<"Number of event in WJets200  = "<<t8_BkgHist[14]->Integral()<<endl;
cout<<"Number of event in WJets1200  = "<<t9_BkgHist[14]->Integral()<<endl;
cout<<"Number of event in WJets2500  = "<<t10_BkgHist[14]->Integral()<<endl;
cout<<"Number of event in WJets400  = "<<t11_BkgHist[14]->Integral()<<endl;
cout<<"Number of event in WJets600  = "<<t12_BkgHist[14]->Integral()<<endl;
cout<<"Number of event in WJets  = "<<t13_BkgHist[14]->Integral()<<endl;
cout<<"Number of event in TTbar  = "<<t14_BkgHist[14]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("vbf_maxpt_jj_pt");
h2->GetXaxis()->CenterTitle(1);
h2->SetMinimum(0.5);
h2->SetMaximum(1.5);
h2->GetXaxis()->SetTitleOffset(0.8);
h2->GetXaxis()->SetLabelSize(0.033*yscale);
h2->GetXaxis()->SetTitleSize(0.036*yscale);
h2->GetXaxis()->SetTickLength(0.03*yscale);
h2->GetYaxis()->SetTitleOffset(0.3);
h2->GetYaxis()->SetNdivisions(5);
h2->GetYaxis()->SetLabelSize(0.033*yscale);
h2->GetYaxis()->SetTitleSize(0.036*yscale);
h2->Draw("");
	c1->SaveAs("vbf_maxpt_jj_pt.pdf");
	c1->SaveAs("vbf_maxpt_jj_pt.png");
	c1->SaveAs("vbf_maxpt_jj_pt.C");
	c1->SaveAs("vbf_maxpt_jj_pt.root");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[15]->SetBottomMargin(0.05287462);
pad[15]->SetLogy(1);
pad[15]->Draw();
pad[15]->cd();

	t0_BkgHist[15]->Scale(0.148600);
	HistMax = t0_BkgHist[15]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t0_BkgHist[15],"VV","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t1_BkgHist[15]->Scale(0.002400);
	HistMax = t1_BkgHist[15]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t2_BkgHist[15]->Scale(0.000700);
	HistMax = t2_BkgHist[15]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t3_BkgHist[15]->Scale(0.206800);
	HistMax = t3_BkgHist[15]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t3_BkgHist[15],"S Top","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t4_BkgHist[15]->Scale(0.209600);
	HistMax = t4_BkgHist[15]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t5_BkgHist[15]->Scale(0.089900);
	HistMax = t5_BkgHist[15]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t6_BkgHist[15]->Scale(0.021200);
	HistMax = t6_BkgHist[15]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t7_BkgHist[15]->Scale(0.283600);
	HistMax = t7_BkgHist[15]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t7_BkgHist[15],"WJets","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t8_BkgHist[15]->Scale(0.420700);
	HistMax = t8_BkgHist[15]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t9_BkgHist[15]->Scale(0.031300);
	HistMax = t9_BkgHist[15]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t10_BkgHist[15]->Scale(0.000700);
	HistMax = t10_BkgHist[15]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t11_BkgHist[15]->Scale(0.144400);
	HistMax = t11_BkgHist[15]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t12_BkgHist[15]->Scale(0.019900);
	HistMax = t12_BkgHist[15]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t13_BkgHist[15]->Scale(0.004800);
	HistMax = t13_BkgHist[15]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t14_BkgHist[15]->Scale(0.026500);
	HistMax = t14_BkgHist[15]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t14_BkgHist[15],"TTbar","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	DataHist[15]->Sumw2();
	HistMax = DataHist[15]->GetMaximum()*1.80;
	leg->AddEntry(DataHist[15],"Data","pe");
	yMax=HistMax;

	hs[15]->Add(t0_BkgHist[15],"hist");
	hs[15]->Add(t1_BkgHist[15],"hist");
	hs[15]->Add(t2_BkgHist[15],"hist");
	hs[15]->Add(t3_BkgHist[15],"hist");
	hs[15]->Add(t4_BkgHist[15],"hist");
	hs[15]->Add(t5_BkgHist[15],"hist");
	hs[15]->Add(t6_BkgHist[15],"hist");
	hs[15]->Add(t7_BkgHist[15],"hist");
	hs[15]->Add(t8_BkgHist[15],"hist");
	hs[15]->Add(t9_BkgHist[15],"hist");
	hs[15]->Add(t10_BkgHist[15],"hist");
	hs[15]->Add(t11_BkgHist[15],"hist");
	hs[15]->Add(t12_BkgHist[15],"hist");
	hs[15]->Add(t13_BkgHist[15],"hist");
	hs[15]->Add(t14_BkgHist[15],"hist");
	hs[15]->SetMaximum(yMax);
	hs[15]->SetMinimum(0.1);
	hs[15]->Draw();
	DataHist[15]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[15]->Clone();
hRatio[15]->Add(t0_BkgHist[15]);
hRatio[15]->Add(t1_BkgHist[15]);
hRatio[15]->Add(t2_BkgHist[15]);
hRatio[15]->Add(t3_BkgHist[15]);
hRatio[15]->Add(t4_BkgHist[15]);
hRatio[15]->Add(t5_BkgHist[15]);
hRatio[15]->Add(t6_BkgHist[15]);
hRatio[15]->Add(t7_BkgHist[15]);
hRatio[15]->Add(t8_BkgHist[15]);
hRatio[15]->Add(t9_BkgHist[15]);
hRatio[15]->Add(t10_BkgHist[15]);
hRatio[15]->Add(t11_BkgHist[15]);
hRatio[15]->Add(t12_BkgHist[15]);
hRatio[15]->Add(t13_BkgHist[15]);
hRatio[15]->Add(t14_BkgHist[15]);


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
cout<<"Ratio of Data/MC = "<<(DataHist[15]->Integral())/(hRatio[15]->Integral())<<endl;
cout<<"Number of event in WW  = "<<t0_BkgHist[15]->Integral()<<endl;
cout<<"Number of event in WZ  = "<<t1_BkgHist[15]->Integral()<<endl;
cout<<"Number of event in ZZ  = "<<t2_BkgHist[15]->Integral()<<endl;
cout<<"Number of event in tWch  = "<<t3_BkgHist[15]->Integral()<<endl;
cout<<"Number of event in tWch_bar  = "<<t4_BkgHist[15]->Integral()<<endl;
cout<<"Number of event in tch_bar  = "<<t5_BkgHist[15]->Integral()<<endl;
cout<<"Number of event in sch  = "<<t6_BkgHist[15]->Integral()<<endl;
cout<<"Number of event in WJets100  = "<<t7_BkgHist[15]->Integral()<<endl;
cout<<"Number of event in WJets200  = "<<t8_BkgHist[15]->Integral()<<endl;
cout<<"Number of event in WJets1200  = "<<t9_BkgHist[15]->Integral()<<endl;
cout<<"Number of event in WJets2500  = "<<t10_BkgHist[15]->Integral()<<endl;
cout<<"Number of event in WJets400  = "<<t11_BkgHist[15]->Integral()<<endl;
cout<<"Number of event in WJets600  = "<<t12_BkgHist[15]->Integral()<<endl;
cout<<"Number of event in WJets  = "<<t13_BkgHist[15]->Integral()<<endl;
cout<<"Number of event in TTbar  = "<<t14_BkgHist[15]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("AK4_jetjet_mass");
h2->GetXaxis()->CenterTitle(1);
h2->SetMinimum(0.5);
h2->SetMaximum(1.5);
h2->GetXaxis()->SetTitleOffset(0.8);
h2->GetXaxis()->SetLabelSize(0.033*yscale);
h2->GetXaxis()->SetTitleSize(0.036*yscale);
h2->GetXaxis()->SetTickLength(0.03*yscale);
h2->GetYaxis()->SetTitleOffset(0.3);
h2->GetYaxis()->SetNdivisions(5);
h2->GetYaxis()->SetLabelSize(0.033*yscale);
h2->GetYaxis()->SetTitleSize(0.036*yscale);
h2->Draw("");
	c1->SaveAs("AK4_jetjet_mass.pdf");
	c1->SaveAs("AK4_jetjet_mass.png");
	c1->SaveAs("AK4_jetjet_mass.C");
	c1->SaveAs("AK4_jetjet_mass.root");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[16]->SetBottomMargin(0.05287462);
pad[16]->SetLogy(1);
pad[16]->Draw();
pad[16]->cd();

	t0_BkgHist[16]->Scale(0.148600);
	HistMax = t0_BkgHist[16]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t0_BkgHist[16],"VV","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t1_BkgHist[16]->Scale(0.002400);
	HistMax = t1_BkgHist[16]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t2_BkgHist[16]->Scale(0.000700);
	HistMax = t2_BkgHist[16]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t3_BkgHist[16]->Scale(0.206800);
	HistMax = t3_BkgHist[16]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t3_BkgHist[16],"S Top","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t4_BkgHist[16]->Scale(0.209600);
	HistMax = t4_BkgHist[16]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t5_BkgHist[16]->Scale(0.089900);
	HistMax = t5_BkgHist[16]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t6_BkgHist[16]->Scale(0.021200);
	HistMax = t6_BkgHist[16]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t7_BkgHist[16]->Scale(0.283600);
	HistMax = t7_BkgHist[16]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t7_BkgHist[16],"WJets","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t8_BkgHist[16]->Scale(0.420700);
	HistMax = t8_BkgHist[16]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t9_BkgHist[16]->Scale(0.031300);
	HistMax = t9_BkgHist[16]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t10_BkgHist[16]->Scale(0.000700);
	HistMax = t10_BkgHist[16]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t11_BkgHist[16]->Scale(0.144400);
	HistMax = t11_BkgHist[16]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t12_BkgHist[16]->Scale(0.019900);
	HistMax = t12_BkgHist[16]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t13_BkgHist[16]->Scale(0.004800);
	HistMax = t13_BkgHist[16]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t14_BkgHist[16]->Scale(0.026500);
	HistMax = t14_BkgHist[16]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t14_BkgHist[16],"TTbar","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	DataHist[16]->Sumw2();
	HistMax = DataHist[16]->GetMaximum()*1.80;
	leg->AddEntry(DataHist[16],"Data","pe");
	yMax=HistMax;

	hs[16]->Add(t0_BkgHist[16],"hist");
	hs[16]->Add(t1_BkgHist[16],"hist");
	hs[16]->Add(t2_BkgHist[16],"hist");
	hs[16]->Add(t3_BkgHist[16],"hist");
	hs[16]->Add(t4_BkgHist[16],"hist");
	hs[16]->Add(t5_BkgHist[16],"hist");
	hs[16]->Add(t6_BkgHist[16],"hist");
	hs[16]->Add(t7_BkgHist[16],"hist");
	hs[16]->Add(t8_BkgHist[16],"hist");
	hs[16]->Add(t9_BkgHist[16],"hist");
	hs[16]->Add(t10_BkgHist[16],"hist");
	hs[16]->Add(t11_BkgHist[16],"hist");
	hs[16]->Add(t12_BkgHist[16],"hist");
	hs[16]->Add(t13_BkgHist[16],"hist");
	hs[16]->Add(t14_BkgHist[16],"hist");
	hs[16]->SetMaximum(yMax);
	hs[16]->SetMinimum(0.1);
	hs[16]->Draw();
	DataHist[16]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[16]->Clone();
hRatio[16]->Add(t0_BkgHist[16]);
hRatio[16]->Add(t1_BkgHist[16]);
hRatio[16]->Add(t2_BkgHist[16]);
hRatio[16]->Add(t3_BkgHist[16]);
hRatio[16]->Add(t4_BkgHist[16]);
hRatio[16]->Add(t5_BkgHist[16]);
hRatio[16]->Add(t6_BkgHist[16]);
hRatio[16]->Add(t7_BkgHist[16]);
hRatio[16]->Add(t8_BkgHist[16]);
hRatio[16]->Add(t9_BkgHist[16]);
hRatio[16]->Add(t10_BkgHist[16]);
hRatio[16]->Add(t11_BkgHist[16]);
hRatio[16]->Add(t12_BkgHist[16]);
hRatio[16]->Add(t13_BkgHist[16]);
hRatio[16]->Add(t14_BkgHist[16]);


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
cout<<"Ratio of Data/MC = "<<(DataHist[16]->Integral())/(hRatio[16]->Integral())<<endl;
cout<<"Number of event in WW  = "<<t0_BkgHist[16]->Integral()<<endl;
cout<<"Number of event in WZ  = "<<t1_BkgHist[16]->Integral()<<endl;
cout<<"Number of event in ZZ  = "<<t2_BkgHist[16]->Integral()<<endl;
cout<<"Number of event in tWch  = "<<t3_BkgHist[16]->Integral()<<endl;
cout<<"Number of event in tWch_bar  = "<<t4_BkgHist[16]->Integral()<<endl;
cout<<"Number of event in tch_bar  = "<<t5_BkgHist[16]->Integral()<<endl;
cout<<"Number of event in sch  = "<<t6_BkgHist[16]->Integral()<<endl;
cout<<"Number of event in WJets100  = "<<t7_BkgHist[16]->Integral()<<endl;
cout<<"Number of event in WJets200  = "<<t8_BkgHist[16]->Integral()<<endl;
cout<<"Number of event in WJets1200  = "<<t9_BkgHist[16]->Integral()<<endl;
cout<<"Number of event in WJets2500  = "<<t10_BkgHist[16]->Integral()<<endl;
cout<<"Number of event in WJets400  = "<<t11_BkgHist[16]->Integral()<<endl;
cout<<"Number of event in WJets600  = "<<t12_BkgHist[16]->Integral()<<endl;
cout<<"Number of event in WJets  = "<<t13_BkgHist[16]->Integral()<<endl;
cout<<"Number of event in TTbar  = "<<t14_BkgHist[16]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("AK4_jetjet_pt");
h2->GetXaxis()->CenterTitle(1);
h2->SetMinimum(0.5);
h2->SetMaximum(1.5);
h2->GetXaxis()->SetTitleOffset(0.8);
h2->GetXaxis()->SetLabelSize(0.033*yscale);
h2->GetXaxis()->SetTitleSize(0.036*yscale);
h2->GetXaxis()->SetTickLength(0.03*yscale);
h2->GetYaxis()->SetTitleOffset(0.3);
h2->GetYaxis()->SetNdivisions(5);
h2->GetYaxis()->SetLabelSize(0.033*yscale);
h2->GetYaxis()->SetTitleSize(0.036*yscale);
h2->Draw("");
	c1->SaveAs("AK4_jetjet_pt.pdf");
	c1->SaveAs("AK4_jetjet_pt.png");
	c1->SaveAs("AK4_jetjet_pt.C");
	c1->SaveAs("AK4_jetjet_pt.root");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[17]->SetBottomMargin(0.05287462);
pad[17]->SetLogy(1);
pad[17]->Draw();
pad[17]->cd();

	t0_BkgHist[17]->Scale(0.148600);
	HistMax = t0_BkgHist[17]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t0_BkgHist[17],"VV","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t1_BkgHist[17]->Scale(0.002400);
	HistMax = t1_BkgHist[17]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t2_BkgHist[17]->Scale(0.000700);
	HistMax = t2_BkgHist[17]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t3_BkgHist[17]->Scale(0.206800);
	HistMax = t3_BkgHist[17]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t3_BkgHist[17],"S Top","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t4_BkgHist[17]->Scale(0.209600);
	HistMax = t4_BkgHist[17]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t5_BkgHist[17]->Scale(0.089900);
	HistMax = t5_BkgHist[17]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t6_BkgHist[17]->Scale(0.021200);
	HistMax = t6_BkgHist[17]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t7_BkgHist[17]->Scale(0.283600);
	HistMax = t7_BkgHist[17]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t7_BkgHist[17],"WJets","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t8_BkgHist[17]->Scale(0.420700);
	HistMax = t8_BkgHist[17]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t9_BkgHist[17]->Scale(0.031300);
	HistMax = t9_BkgHist[17]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t10_BkgHist[17]->Scale(0.000700);
	HistMax = t10_BkgHist[17]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t11_BkgHist[17]->Scale(0.144400);
	HistMax = t11_BkgHist[17]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t12_BkgHist[17]->Scale(0.019900);
	HistMax = t12_BkgHist[17]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t13_BkgHist[17]->Scale(0.004800);
	HistMax = t13_BkgHist[17]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t14_BkgHist[17]->Scale(0.026500);
	HistMax = t14_BkgHist[17]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t14_BkgHist[17],"TTbar","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	DataHist[17]->Sumw2();
	HistMax = DataHist[17]->GetMaximum()*1.80;
	leg->AddEntry(DataHist[17],"Data","pe");
	yMax=HistMax;

	hs[17]->Add(t0_BkgHist[17],"hist");
	hs[17]->Add(t1_BkgHist[17],"hist");
	hs[17]->Add(t2_BkgHist[17],"hist");
	hs[17]->Add(t3_BkgHist[17],"hist");
	hs[17]->Add(t4_BkgHist[17],"hist");
	hs[17]->Add(t5_BkgHist[17],"hist");
	hs[17]->Add(t6_BkgHist[17],"hist");
	hs[17]->Add(t7_BkgHist[17],"hist");
	hs[17]->Add(t8_BkgHist[17],"hist");
	hs[17]->Add(t9_BkgHist[17],"hist");
	hs[17]->Add(t10_BkgHist[17],"hist");
	hs[17]->Add(t11_BkgHist[17],"hist");
	hs[17]->Add(t12_BkgHist[17],"hist");
	hs[17]->Add(t13_BkgHist[17],"hist");
	hs[17]->Add(t14_BkgHist[17],"hist");
	hs[17]->SetMaximum(yMax);
	hs[17]->SetMinimum(0.1);
	hs[17]->Draw();
	DataHist[17]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[17]->Clone();
hRatio[17]->Add(t0_BkgHist[17]);
hRatio[17]->Add(t1_BkgHist[17]);
hRatio[17]->Add(t2_BkgHist[17]);
hRatio[17]->Add(t3_BkgHist[17]);
hRatio[17]->Add(t4_BkgHist[17]);
hRatio[17]->Add(t5_BkgHist[17]);
hRatio[17]->Add(t6_BkgHist[17]);
hRatio[17]->Add(t7_BkgHist[17]);
hRatio[17]->Add(t8_BkgHist[17]);
hRatio[17]->Add(t9_BkgHist[17]);
hRatio[17]->Add(t10_BkgHist[17]);
hRatio[17]->Add(t11_BkgHist[17]);
hRatio[17]->Add(t12_BkgHist[17]);
hRatio[17]->Add(t13_BkgHist[17]);
hRatio[17]->Add(t14_BkgHist[17]);


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
cout<<"Ratio of Data/MC = "<<(DataHist[17]->Integral())/(hRatio[17]->Integral())<<endl;
cout<<"Number of event in WW  = "<<t0_BkgHist[17]->Integral()<<endl;
cout<<"Number of event in WZ  = "<<t1_BkgHist[17]->Integral()<<endl;
cout<<"Number of event in ZZ  = "<<t2_BkgHist[17]->Integral()<<endl;
cout<<"Number of event in tWch  = "<<t3_BkgHist[17]->Integral()<<endl;
cout<<"Number of event in tWch_bar  = "<<t4_BkgHist[17]->Integral()<<endl;
cout<<"Number of event in tch_bar  = "<<t5_BkgHist[17]->Integral()<<endl;
cout<<"Number of event in sch  = "<<t6_BkgHist[17]->Integral()<<endl;
cout<<"Number of event in WJets100  = "<<t7_BkgHist[17]->Integral()<<endl;
cout<<"Number of event in WJets200  = "<<t8_BkgHist[17]->Integral()<<endl;
cout<<"Number of event in WJets1200  = "<<t9_BkgHist[17]->Integral()<<endl;
cout<<"Number of event in WJets2500  = "<<t10_BkgHist[17]->Integral()<<endl;
cout<<"Number of event in WJets400  = "<<t11_BkgHist[17]->Integral()<<endl;
cout<<"Number of event in WJets600  = "<<t12_BkgHist[17]->Integral()<<endl;
cout<<"Number of event in WJets  = "<<t13_BkgHist[17]->Integral()<<endl;
cout<<"Number of event in TTbar  = "<<t14_BkgHist[17]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("AK4_jetjet_deltaeta");
h2->GetXaxis()->CenterTitle(1);
h2->SetMinimum(0.5);
h2->SetMaximum(1.5);
h2->GetXaxis()->SetTitleOffset(0.8);
h2->GetXaxis()->SetLabelSize(0.033*yscale);
h2->GetXaxis()->SetTitleSize(0.036*yscale);
h2->GetXaxis()->SetTickLength(0.03*yscale);
h2->GetYaxis()->SetTitleOffset(0.3);
h2->GetYaxis()->SetNdivisions(5);
h2->GetYaxis()->SetLabelSize(0.033*yscale);
h2->GetYaxis()->SetTitleSize(0.036*yscale);
h2->Draw("");
	c1->SaveAs("AK4_jetjet_deltaeta.pdf");
	c1->SaveAs("AK4_jetjet_deltaeta.png");
	c1->SaveAs("AK4_jetjet_deltaeta.C");
	c1->SaveAs("AK4_jetjet_deltaeta.root");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[18]->SetBottomMargin(0.05287462);
pad[18]->SetLogy(1);
pad[18]->Draw();
pad[18]->cd();

	t0_BkgHist[18]->Scale(0.148600);
	HistMax = t0_BkgHist[18]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t0_BkgHist[18],"VV","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t1_BkgHist[18]->Scale(0.002400);
	HistMax = t1_BkgHist[18]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t2_BkgHist[18]->Scale(0.000700);
	HistMax = t2_BkgHist[18]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t3_BkgHist[18]->Scale(0.206800);
	HistMax = t3_BkgHist[18]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t3_BkgHist[18],"S Top","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t4_BkgHist[18]->Scale(0.209600);
	HistMax = t4_BkgHist[18]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t5_BkgHist[18]->Scale(0.089900);
	HistMax = t5_BkgHist[18]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t6_BkgHist[18]->Scale(0.021200);
	HistMax = t6_BkgHist[18]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t7_BkgHist[18]->Scale(0.283600);
	HistMax = t7_BkgHist[18]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t7_BkgHist[18],"WJets","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t8_BkgHist[18]->Scale(0.420700);
	HistMax = t8_BkgHist[18]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t9_BkgHist[18]->Scale(0.031300);
	HistMax = t9_BkgHist[18]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t10_BkgHist[18]->Scale(0.000700);
	HistMax = t10_BkgHist[18]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t11_BkgHist[18]->Scale(0.144400);
	HistMax = t11_BkgHist[18]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t12_BkgHist[18]->Scale(0.019900);
	HistMax = t12_BkgHist[18]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t13_BkgHist[18]->Scale(0.004800);
	HistMax = t13_BkgHist[18]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t14_BkgHist[18]->Scale(0.026500);
	HistMax = t14_BkgHist[18]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t14_BkgHist[18],"TTbar","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	DataHist[18]->Sumw2();
	HistMax = DataHist[18]->GetMaximum()*1.80;
	leg->AddEntry(DataHist[18],"Data","pe");
	yMax=HistMax;

	hs[18]->Add(t0_BkgHist[18],"hist");
	hs[18]->Add(t1_BkgHist[18],"hist");
	hs[18]->Add(t2_BkgHist[18],"hist");
	hs[18]->Add(t3_BkgHist[18],"hist");
	hs[18]->Add(t4_BkgHist[18],"hist");
	hs[18]->Add(t5_BkgHist[18],"hist");
	hs[18]->Add(t6_BkgHist[18],"hist");
	hs[18]->Add(t7_BkgHist[18],"hist");
	hs[18]->Add(t8_BkgHist[18],"hist");
	hs[18]->Add(t9_BkgHist[18],"hist");
	hs[18]->Add(t10_BkgHist[18],"hist");
	hs[18]->Add(t11_BkgHist[18],"hist");
	hs[18]->Add(t12_BkgHist[18],"hist");
	hs[18]->Add(t13_BkgHist[18],"hist");
	hs[18]->Add(t14_BkgHist[18],"hist");
	hs[18]->SetMaximum(yMax);
	hs[18]->SetMinimum(0.1);
	hs[18]->Draw();
	DataHist[18]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[18]->Clone();
hRatio[18]->Add(t0_BkgHist[18]);
hRatio[18]->Add(t1_BkgHist[18]);
hRatio[18]->Add(t2_BkgHist[18]);
hRatio[18]->Add(t3_BkgHist[18]);
hRatio[18]->Add(t4_BkgHist[18]);
hRatio[18]->Add(t5_BkgHist[18]);
hRatio[18]->Add(t6_BkgHist[18]);
hRatio[18]->Add(t7_BkgHist[18]);
hRatio[18]->Add(t8_BkgHist[18]);
hRatio[18]->Add(t9_BkgHist[18]);
hRatio[18]->Add(t10_BkgHist[18]);
hRatio[18]->Add(t11_BkgHist[18]);
hRatio[18]->Add(t12_BkgHist[18]);
hRatio[18]->Add(t13_BkgHist[18]);
hRatio[18]->Add(t14_BkgHist[18]);


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
cout<<"Ratio of Data/MC = "<<(DataHist[18]->Integral())/(hRatio[18]->Integral())<<endl;
cout<<"Number of event in WW  = "<<t0_BkgHist[18]->Integral()<<endl;
cout<<"Number of event in WZ  = "<<t1_BkgHist[18]->Integral()<<endl;
cout<<"Number of event in ZZ  = "<<t2_BkgHist[18]->Integral()<<endl;
cout<<"Number of event in tWch  = "<<t3_BkgHist[18]->Integral()<<endl;
cout<<"Number of event in tWch_bar  = "<<t4_BkgHist[18]->Integral()<<endl;
cout<<"Number of event in tch_bar  = "<<t5_BkgHist[18]->Integral()<<endl;
cout<<"Number of event in sch  = "<<t6_BkgHist[18]->Integral()<<endl;
cout<<"Number of event in WJets100  = "<<t7_BkgHist[18]->Integral()<<endl;
cout<<"Number of event in WJets200  = "<<t8_BkgHist[18]->Integral()<<endl;
cout<<"Number of event in WJets1200  = "<<t9_BkgHist[18]->Integral()<<endl;
cout<<"Number of event in WJets2500  = "<<t10_BkgHist[18]->Integral()<<endl;
cout<<"Number of event in WJets400  = "<<t11_BkgHist[18]->Integral()<<endl;
cout<<"Number of event in WJets600  = "<<t12_BkgHist[18]->Integral()<<endl;
cout<<"Number of event in WJets  = "<<t13_BkgHist[18]->Integral()<<endl;
cout<<"Number of event in TTbar  = "<<t14_BkgHist[18]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("v_mt");
h2->GetXaxis()->CenterTitle(1);
h2->SetMinimum(0.5);
h2->SetMaximum(1.5);
h2->GetXaxis()->SetTitleOffset(0.8);
h2->GetXaxis()->SetLabelSize(0.033*yscale);
h2->GetXaxis()->SetTitleSize(0.036*yscale);
h2->GetXaxis()->SetTickLength(0.03*yscale);
h2->GetYaxis()->SetTitleOffset(0.3);
h2->GetYaxis()->SetNdivisions(5);
h2->GetYaxis()->SetLabelSize(0.033*yscale);
h2->GetYaxis()->SetTitleSize(0.036*yscale);
h2->Draw("");
	c1->SaveAs("v_mt.pdf");
	c1->SaveAs("v_mt.png");
	c1->SaveAs("v_mt.C");
	c1->SaveAs("v_mt.root");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[19]->SetBottomMargin(0.05287462);
pad[19]->SetLogy(1);
pad[19]->Draw();
pad[19]->cd();

	t0_BkgHist[19]->Scale(0.148600);
	HistMax = t0_BkgHist[19]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t0_BkgHist[19],"VV","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t1_BkgHist[19]->Scale(0.002400);
	HistMax = t1_BkgHist[19]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t2_BkgHist[19]->Scale(0.000700);
	HistMax = t2_BkgHist[19]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t3_BkgHist[19]->Scale(0.206800);
	HistMax = t3_BkgHist[19]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t3_BkgHist[19],"S Top","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t4_BkgHist[19]->Scale(0.209600);
	HistMax = t4_BkgHist[19]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t5_BkgHist[19]->Scale(0.089900);
	HistMax = t5_BkgHist[19]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t6_BkgHist[19]->Scale(0.021200);
	HistMax = t6_BkgHist[19]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t7_BkgHist[19]->Scale(0.283600);
	HistMax = t7_BkgHist[19]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t7_BkgHist[19],"WJets","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t8_BkgHist[19]->Scale(0.420700);
	HistMax = t8_BkgHist[19]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t9_BkgHist[19]->Scale(0.031300);
	HistMax = t9_BkgHist[19]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t10_BkgHist[19]->Scale(0.000700);
	HistMax = t10_BkgHist[19]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t11_BkgHist[19]->Scale(0.144400);
	HistMax = t11_BkgHist[19]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t12_BkgHist[19]->Scale(0.019900);
	HistMax = t12_BkgHist[19]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t13_BkgHist[19]->Scale(0.004800);
	HistMax = t13_BkgHist[19]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t14_BkgHist[19]->Scale(0.026500);
	HistMax = t14_BkgHist[19]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t14_BkgHist[19],"TTbar","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	DataHist[19]->Sumw2();
	HistMax = DataHist[19]->GetMaximum()*1.80;
	leg->AddEntry(DataHist[19],"Data","pe");
	yMax=HistMax;

	hs[19]->Add(t0_BkgHist[19],"hist");
	hs[19]->Add(t1_BkgHist[19],"hist");
	hs[19]->Add(t2_BkgHist[19],"hist");
	hs[19]->Add(t3_BkgHist[19],"hist");
	hs[19]->Add(t4_BkgHist[19],"hist");
	hs[19]->Add(t5_BkgHist[19],"hist");
	hs[19]->Add(t6_BkgHist[19],"hist");
	hs[19]->Add(t7_BkgHist[19],"hist");
	hs[19]->Add(t8_BkgHist[19],"hist");
	hs[19]->Add(t9_BkgHist[19],"hist");
	hs[19]->Add(t10_BkgHist[19],"hist");
	hs[19]->Add(t11_BkgHist[19],"hist");
	hs[19]->Add(t12_BkgHist[19],"hist");
	hs[19]->Add(t13_BkgHist[19],"hist");
	hs[19]->Add(t14_BkgHist[19],"hist");
	hs[19]->SetMaximum(yMax);
	hs[19]->SetMinimum(0.1);
	hs[19]->Draw();
	DataHist[19]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[19]->Clone();
hRatio[19]->Add(t0_BkgHist[19]);
hRatio[19]->Add(t1_BkgHist[19]);
hRatio[19]->Add(t2_BkgHist[19]);
hRatio[19]->Add(t3_BkgHist[19]);
hRatio[19]->Add(t4_BkgHist[19]);
hRatio[19]->Add(t5_BkgHist[19]);
hRatio[19]->Add(t6_BkgHist[19]);
hRatio[19]->Add(t7_BkgHist[19]);
hRatio[19]->Add(t8_BkgHist[19]);
hRatio[19]->Add(t9_BkgHist[19]);
hRatio[19]->Add(t10_BkgHist[19]);
hRatio[19]->Add(t11_BkgHist[19]);
hRatio[19]->Add(t12_BkgHist[19]);
hRatio[19]->Add(t13_BkgHist[19]);
hRatio[19]->Add(t14_BkgHist[19]);


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
cout<<"Ratio of Data/MC = "<<(DataHist[19]->Integral())/(hRatio[19]->Integral())<<endl;
cout<<"Number of event in WW  = "<<t0_BkgHist[19]->Integral()<<endl;
cout<<"Number of event in WZ  = "<<t1_BkgHist[19]->Integral()<<endl;
cout<<"Number of event in ZZ  = "<<t2_BkgHist[19]->Integral()<<endl;
cout<<"Number of event in tWch  = "<<t3_BkgHist[19]->Integral()<<endl;
cout<<"Number of event in tWch_bar  = "<<t4_BkgHist[19]->Integral()<<endl;
cout<<"Number of event in tch_bar  = "<<t5_BkgHist[19]->Integral()<<endl;
cout<<"Number of event in sch  = "<<t6_BkgHist[19]->Integral()<<endl;
cout<<"Number of event in WJets100  = "<<t7_BkgHist[19]->Integral()<<endl;
cout<<"Number of event in WJets200  = "<<t8_BkgHist[19]->Integral()<<endl;
cout<<"Number of event in WJets1200  = "<<t9_BkgHist[19]->Integral()<<endl;
cout<<"Number of event in WJets2500  = "<<t10_BkgHist[19]->Integral()<<endl;
cout<<"Number of event in WJets400  = "<<t11_BkgHist[19]->Integral()<<endl;
cout<<"Number of event in WJets600  = "<<t12_BkgHist[19]->Integral()<<endl;
cout<<"Number of event in WJets  = "<<t13_BkgHist[19]->Integral()<<endl;
cout<<"Number of event in TTbar  = "<<t14_BkgHist[19]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("v_pt");
h2->GetXaxis()->CenterTitle(1);
h2->SetMinimum(0.5);
h2->SetMaximum(1.5);
h2->GetXaxis()->SetTitleOffset(0.8);
h2->GetXaxis()->SetLabelSize(0.033*yscale);
h2->GetXaxis()->SetTitleSize(0.036*yscale);
h2->GetXaxis()->SetTickLength(0.03*yscale);
h2->GetYaxis()->SetTitleOffset(0.3);
h2->GetYaxis()->SetNdivisions(5);
h2->GetYaxis()->SetLabelSize(0.033*yscale);
h2->GetYaxis()->SetTitleSize(0.036*yscale);
h2->Draw("");
	c1->SaveAs("v_pt.pdf");
	c1->SaveAs("v_pt.png");
	c1->SaveAs("v_pt.C");
	c1->SaveAs("v_pt.root");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[20]->SetBottomMargin(0.05287462);
pad[20]->SetLogy(1);
pad[20]->Draw();
pad[20]->cd();

	t0_BkgHist[20]->Scale(0.148600);
	HistMax = t0_BkgHist[20]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t0_BkgHist[20],"VV","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t1_BkgHist[20]->Scale(0.002400);
	HistMax = t1_BkgHist[20]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t2_BkgHist[20]->Scale(0.000700);
	HistMax = t2_BkgHist[20]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t3_BkgHist[20]->Scale(0.206800);
	HistMax = t3_BkgHist[20]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t3_BkgHist[20],"S Top","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t4_BkgHist[20]->Scale(0.209600);
	HistMax = t4_BkgHist[20]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t5_BkgHist[20]->Scale(0.089900);
	HistMax = t5_BkgHist[20]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t6_BkgHist[20]->Scale(0.021200);
	HistMax = t6_BkgHist[20]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t7_BkgHist[20]->Scale(0.283600);
	HistMax = t7_BkgHist[20]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t7_BkgHist[20],"WJets","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t8_BkgHist[20]->Scale(0.420700);
	HistMax = t8_BkgHist[20]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t9_BkgHist[20]->Scale(0.031300);
	HistMax = t9_BkgHist[20]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t10_BkgHist[20]->Scale(0.000700);
	HistMax = t10_BkgHist[20]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t11_BkgHist[20]->Scale(0.144400);
	HistMax = t11_BkgHist[20]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t12_BkgHist[20]->Scale(0.019900);
	HistMax = t12_BkgHist[20]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t13_BkgHist[20]->Scale(0.004800);
	HistMax = t13_BkgHist[20]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t14_BkgHist[20]->Scale(0.026500);
	HistMax = t14_BkgHist[20]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t14_BkgHist[20],"TTbar","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	DataHist[20]->Sumw2();
	HistMax = DataHist[20]->GetMaximum()*1.80;
	leg->AddEntry(DataHist[20],"Data","pe");
	yMax=HistMax;

	hs[20]->Add(t0_BkgHist[20],"hist");
	hs[20]->Add(t1_BkgHist[20],"hist");
	hs[20]->Add(t2_BkgHist[20],"hist");
	hs[20]->Add(t3_BkgHist[20],"hist");
	hs[20]->Add(t4_BkgHist[20],"hist");
	hs[20]->Add(t5_BkgHist[20],"hist");
	hs[20]->Add(t6_BkgHist[20],"hist");
	hs[20]->Add(t7_BkgHist[20],"hist");
	hs[20]->Add(t8_BkgHist[20],"hist");
	hs[20]->Add(t9_BkgHist[20],"hist");
	hs[20]->Add(t10_BkgHist[20],"hist");
	hs[20]->Add(t11_BkgHist[20],"hist");
	hs[20]->Add(t12_BkgHist[20],"hist");
	hs[20]->Add(t13_BkgHist[20],"hist");
	hs[20]->Add(t14_BkgHist[20],"hist");
	hs[20]->SetMaximum(yMax);
	hs[20]->SetMinimum(0.1);
	hs[20]->Draw();
	DataHist[20]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[20]->Clone();
hRatio[20]->Add(t0_BkgHist[20]);
hRatio[20]->Add(t1_BkgHist[20]);
hRatio[20]->Add(t2_BkgHist[20]);
hRatio[20]->Add(t3_BkgHist[20]);
hRatio[20]->Add(t4_BkgHist[20]);
hRatio[20]->Add(t5_BkgHist[20]);
hRatio[20]->Add(t6_BkgHist[20]);
hRatio[20]->Add(t7_BkgHist[20]);
hRatio[20]->Add(t8_BkgHist[20]);
hRatio[20]->Add(t9_BkgHist[20]);
hRatio[20]->Add(t10_BkgHist[20]);
hRatio[20]->Add(t11_BkgHist[20]);
hRatio[20]->Add(t12_BkgHist[20]);
hRatio[20]->Add(t13_BkgHist[20]);
hRatio[20]->Add(t14_BkgHist[20]);


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
cout<<"Ratio of Data/MC = "<<(DataHist[20]->Integral())/(hRatio[20]->Integral())<<endl;
cout<<"Number of event in WW  = "<<t0_BkgHist[20]->Integral()<<endl;
cout<<"Number of event in WZ  = "<<t1_BkgHist[20]->Integral()<<endl;
cout<<"Number of event in ZZ  = "<<t2_BkgHist[20]->Integral()<<endl;
cout<<"Number of event in tWch  = "<<t3_BkgHist[20]->Integral()<<endl;
cout<<"Number of event in tWch_bar  = "<<t4_BkgHist[20]->Integral()<<endl;
cout<<"Number of event in tch_bar  = "<<t5_BkgHist[20]->Integral()<<endl;
cout<<"Number of event in sch  = "<<t6_BkgHist[20]->Integral()<<endl;
cout<<"Number of event in WJets100  = "<<t7_BkgHist[20]->Integral()<<endl;
cout<<"Number of event in WJets200  = "<<t8_BkgHist[20]->Integral()<<endl;
cout<<"Number of event in WJets1200  = "<<t9_BkgHist[20]->Integral()<<endl;
cout<<"Number of event in WJets2500  = "<<t10_BkgHist[20]->Integral()<<endl;
cout<<"Number of event in WJets400  = "<<t11_BkgHist[20]->Integral()<<endl;
cout<<"Number of event in WJets600  = "<<t12_BkgHist[20]->Integral()<<endl;
cout<<"Number of event in WJets  = "<<t13_BkgHist[20]->Integral()<<endl;
cout<<"Number of event in TTbar  = "<<t14_BkgHist[20]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("mass_lvjj_type0_AK4");
h2->GetXaxis()->CenterTitle(1);
h2->SetMinimum(0.5);
h2->SetMaximum(1.5);
h2->GetXaxis()->SetTitleOffset(0.8);
h2->GetXaxis()->SetLabelSize(0.033*yscale);
h2->GetXaxis()->SetTitleSize(0.036*yscale);
h2->GetXaxis()->SetTickLength(0.03*yscale);
h2->GetYaxis()->SetTitleOffset(0.3);
h2->GetYaxis()->SetNdivisions(5);
h2->GetYaxis()->SetLabelSize(0.033*yscale);
h2->GetYaxis()->SetTitleSize(0.036*yscale);
h2->Draw("");
	c1->SaveAs("mass_lvjj_type0_AK4.pdf");
	c1->SaveAs("mass_lvjj_type0_AK4.png");
	c1->SaveAs("mass_lvjj_type0_AK4.C");
	c1->SaveAs("mass_lvjj_type0_AK4.root");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[21]->SetBottomMargin(0.05287462);
pad[21]->SetLogy(1);
pad[21]->Draw();
pad[21]->cd();

	t0_BkgHist[21]->Scale(0.148600);
	HistMax = t0_BkgHist[21]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t0_BkgHist[21],"VV","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t1_BkgHist[21]->Scale(0.002400);
	HistMax = t1_BkgHist[21]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t2_BkgHist[21]->Scale(0.000700);
	HistMax = t2_BkgHist[21]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t3_BkgHist[21]->Scale(0.206800);
	HistMax = t3_BkgHist[21]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t3_BkgHist[21],"S Top","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t4_BkgHist[21]->Scale(0.209600);
	HistMax = t4_BkgHist[21]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t5_BkgHist[21]->Scale(0.089900);
	HistMax = t5_BkgHist[21]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t6_BkgHist[21]->Scale(0.021200);
	HistMax = t6_BkgHist[21]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t7_BkgHist[21]->Scale(0.283600);
	HistMax = t7_BkgHist[21]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t7_BkgHist[21],"WJets","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t8_BkgHist[21]->Scale(0.420700);
	HistMax = t8_BkgHist[21]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t9_BkgHist[21]->Scale(0.031300);
	HistMax = t9_BkgHist[21]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t10_BkgHist[21]->Scale(0.000700);
	HistMax = t10_BkgHist[21]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t11_BkgHist[21]->Scale(0.144400);
	HistMax = t11_BkgHist[21]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t12_BkgHist[21]->Scale(0.019900);
	HistMax = t12_BkgHist[21]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t13_BkgHist[21]->Scale(0.004800);
	HistMax = t13_BkgHist[21]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t14_BkgHist[21]->Scale(0.026500);
	HistMax = t14_BkgHist[21]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t14_BkgHist[21],"TTbar","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	DataHist[21]->Sumw2();
	HistMax = DataHist[21]->GetMaximum()*1.80;
	leg->AddEntry(DataHist[21],"Data","pe");
	yMax=HistMax;

	hs[21]->Add(t0_BkgHist[21],"hist");
	hs[21]->Add(t1_BkgHist[21],"hist");
	hs[21]->Add(t2_BkgHist[21],"hist");
	hs[21]->Add(t3_BkgHist[21],"hist");
	hs[21]->Add(t4_BkgHist[21],"hist");
	hs[21]->Add(t5_BkgHist[21],"hist");
	hs[21]->Add(t6_BkgHist[21],"hist");
	hs[21]->Add(t7_BkgHist[21],"hist");
	hs[21]->Add(t8_BkgHist[21],"hist");
	hs[21]->Add(t9_BkgHist[21],"hist");
	hs[21]->Add(t10_BkgHist[21],"hist");
	hs[21]->Add(t11_BkgHist[21],"hist");
	hs[21]->Add(t12_BkgHist[21],"hist");
	hs[21]->Add(t13_BkgHist[21],"hist");
	hs[21]->Add(t14_BkgHist[21],"hist");
	hs[21]->SetMaximum(yMax);
	hs[21]->SetMinimum(0.1);
	hs[21]->Draw();
	DataHist[21]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[21]->Clone();
hRatio[21]->Add(t0_BkgHist[21]);
hRatio[21]->Add(t1_BkgHist[21]);
hRatio[21]->Add(t2_BkgHist[21]);
hRatio[21]->Add(t3_BkgHist[21]);
hRatio[21]->Add(t4_BkgHist[21]);
hRatio[21]->Add(t5_BkgHist[21]);
hRatio[21]->Add(t6_BkgHist[21]);
hRatio[21]->Add(t7_BkgHist[21]);
hRatio[21]->Add(t8_BkgHist[21]);
hRatio[21]->Add(t9_BkgHist[21]);
hRatio[21]->Add(t10_BkgHist[21]);
hRatio[21]->Add(t11_BkgHist[21]);
hRatio[21]->Add(t12_BkgHist[21]);
hRatio[21]->Add(t13_BkgHist[21]);
hRatio[21]->Add(t14_BkgHist[21]);


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
cout<<"Ratio of Data/MC = "<<(DataHist[21]->Integral())/(hRatio[21]->Integral())<<endl;
cout<<"Number of event in WW  = "<<t0_BkgHist[21]->Integral()<<endl;
cout<<"Number of event in WZ  = "<<t1_BkgHist[21]->Integral()<<endl;
cout<<"Number of event in ZZ  = "<<t2_BkgHist[21]->Integral()<<endl;
cout<<"Number of event in tWch  = "<<t3_BkgHist[21]->Integral()<<endl;
cout<<"Number of event in tWch_bar  = "<<t4_BkgHist[21]->Integral()<<endl;
cout<<"Number of event in tch_bar  = "<<t5_BkgHist[21]->Integral()<<endl;
cout<<"Number of event in sch  = "<<t6_BkgHist[21]->Integral()<<endl;
cout<<"Number of event in WJets100  = "<<t7_BkgHist[21]->Integral()<<endl;
cout<<"Number of event in WJets200  = "<<t8_BkgHist[21]->Integral()<<endl;
cout<<"Number of event in WJets1200  = "<<t9_BkgHist[21]->Integral()<<endl;
cout<<"Number of event in WJets2500  = "<<t10_BkgHist[21]->Integral()<<endl;
cout<<"Number of event in WJets400  = "<<t11_BkgHist[21]->Integral()<<endl;
cout<<"Number of event in WJets600  = "<<t12_BkgHist[21]->Integral()<<endl;
cout<<"Number of event in WJets  = "<<t13_BkgHist[21]->Integral()<<endl;
cout<<"Number of event in TTbar  = "<<t14_BkgHist[21]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("deltaR_lak4jetjet");
h2->GetXaxis()->CenterTitle(1);
h2->SetMinimum(0.5);
h2->SetMaximum(1.5);
h2->GetXaxis()->SetTitleOffset(0.8);
h2->GetXaxis()->SetLabelSize(0.033*yscale);
h2->GetXaxis()->SetTitleSize(0.036*yscale);
h2->GetXaxis()->SetTickLength(0.03*yscale);
h2->GetYaxis()->SetTitleOffset(0.3);
h2->GetYaxis()->SetNdivisions(5);
h2->GetYaxis()->SetLabelSize(0.033*yscale);
h2->GetYaxis()->SetTitleSize(0.036*yscale);
h2->Draw("");
	c1->SaveAs("deltaR_lak4jetjet.pdf");
	c1->SaveAs("deltaR_lak4jetjet.png");
	c1->SaveAs("deltaR_lak4jetjet.C");
	c1->SaveAs("deltaR_lak4jetjet.root");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[22]->SetBottomMargin(0.05287462);
pad[22]->SetLogy(1);
pad[22]->Draw();
pad[22]->cd();

	t0_BkgHist[22]->Scale(0.148600);
	HistMax = t0_BkgHist[22]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t0_BkgHist[22],"VV","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t1_BkgHist[22]->Scale(0.002400);
	HistMax = t1_BkgHist[22]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t2_BkgHist[22]->Scale(0.000700);
	HistMax = t2_BkgHist[22]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t3_BkgHist[22]->Scale(0.206800);
	HistMax = t3_BkgHist[22]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t3_BkgHist[22],"S Top","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t4_BkgHist[22]->Scale(0.209600);
	HistMax = t4_BkgHist[22]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t5_BkgHist[22]->Scale(0.089900);
	HistMax = t5_BkgHist[22]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t6_BkgHist[22]->Scale(0.021200);
	HistMax = t6_BkgHist[22]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t7_BkgHist[22]->Scale(0.283600);
	HistMax = t7_BkgHist[22]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t7_BkgHist[22],"WJets","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t8_BkgHist[22]->Scale(0.420700);
	HistMax = t8_BkgHist[22]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t9_BkgHist[22]->Scale(0.031300);
	HistMax = t9_BkgHist[22]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t10_BkgHist[22]->Scale(0.000700);
	HistMax = t10_BkgHist[22]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t11_BkgHist[22]->Scale(0.144400);
	HistMax = t11_BkgHist[22]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t12_BkgHist[22]->Scale(0.019900);
	HistMax = t12_BkgHist[22]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t13_BkgHist[22]->Scale(0.004800);
	HistMax = t13_BkgHist[22]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t14_BkgHist[22]->Scale(0.026500);
	HistMax = t14_BkgHist[22]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t14_BkgHist[22],"TTbar","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	DataHist[22]->Sumw2();
	HistMax = DataHist[22]->GetMaximum()*1.80;
	leg->AddEntry(DataHist[22],"Data","pe");
	yMax=HistMax;

	hs[22]->Add(t0_BkgHist[22],"hist");
	hs[22]->Add(t1_BkgHist[22],"hist");
	hs[22]->Add(t2_BkgHist[22],"hist");
	hs[22]->Add(t3_BkgHist[22],"hist");
	hs[22]->Add(t4_BkgHist[22],"hist");
	hs[22]->Add(t5_BkgHist[22],"hist");
	hs[22]->Add(t6_BkgHist[22],"hist");
	hs[22]->Add(t7_BkgHist[22],"hist");
	hs[22]->Add(t8_BkgHist[22],"hist");
	hs[22]->Add(t9_BkgHist[22],"hist");
	hs[22]->Add(t10_BkgHist[22],"hist");
	hs[22]->Add(t11_BkgHist[22],"hist");
	hs[22]->Add(t12_BkgHist[22],"hist");
	hs[22]->Add(t13_BkgHist[22],"hist");
	hs[22]->Add(t14_BkgHist[22],"hist");
	hs[22]->SetMaximum(yMax);
	hs[22]->SetMinimum(0.1);
	hs[22]->Draw();
	DataHist[22]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[22]->Clone();
hRatio[22]->Add(t0_BkgHist[22]);
hRatio[22]->Add(t1_BkgHist[22]);
hRatio[22]->Add(t2_BkgHist[22]);
hRatio[22]->Add(t3_BkgHist[22]);
hRatio[22]->Add(t4_BkgHist[22]);
hRatio[22]->Add(t5_BkgHist[22]);
hRatio[22]->Add(t6_BkgHist[22]);
hRatio[22]->Add(t7_BkgHist[22]);
hRatio[22]->Add(t8_BkgHist[22]);
hRatio[22]->Add(t9_BkgHist[22]);
hRatio[22]->Add(t10_BkgHist[22]);
hRatio[22]->Add(t11_BkgHist[22]);
hRatio[22]->Add(t12_BkgHist[22]);
hRatio[22]->Add(t13_BkgHist[22]);
hRatio[22]->Add(t14_BkgHist[22]);


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
cout<<"Ratio of Data/MC = "<<(DataHist[22]->Integral())/(hRatio[22]->Integral())<<endl;
cout<<"Number of event in WW  = "<<t0_BkgHist[22]->Integral()<<endl;
cout<<"Number of event in WZ  = "<<t1_BkgHist[22]->Integral()<<endl;
cout<<"Number of event in ZZ  = "<<t2_BkgHist[22]->Integral()<<endl;
cout<<"Number of event in tWch  = "<<t3_BkgHist[22]->Integral()<<endl;
cout<<"Number of event in tWch_bar  = "<<t4_BkgHist[22]->Integral()<<endl;
cout<<"Number of event in tch_bar  = "<<t5_BkgHist[22]->Integral()<<endl;
cout<<"Number of event in sch  = "<<t6_BkgHist[22]->Integral()<<endl;
cout<<"Number of event in WJets100  = "<<t7_BkgHist[22]->Integral()<<endl;
cout<<"Number of event in WJets200  = "<<t8_BkgHist[22]->Integral()<<endl;
cout<<"Number of event in WJets1200  = "<<t9_BkgHist[22]->Integral()<<endl;
cout<<"Number of event in WJets2500  = "<<t10_BkgHist[22]->Integral()<<endl;
cout<<"Number of event in WJets400  = "<<t11_BkgHist[22]->Integral()<<endl;
cout<<"Number of event in WJets600  = "<<t12_BkgHist[22]->Integral()<<endl;
cout<<"Number of event in WJets  = "<<t13_BkgHist[22]->Integral()<<endl;
cout<<"Number of event in TTbar  = "<<t14_BkgHist[22]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("deltaphi_METak4jetjet");
h2->GetXaxis()->CenterTitle(1);
h2->SetMinimum(0.5);
h2->SetMaximum(1.5);
h2->GetXaxis()->SetTitleOffset(0.8);
h2->GetXaxis()->SetLabelSize(0.033*yscale);
h2->GetXaxis()->SetTitleSize(0.036*yscale);
h2->GetXaxis()->SetTickLength(0.03*yscale);
h2->GetYaxis()->SetTitleOffset(0.3);
h2->GetYaxis()->SetNdivisions(5);
h2->GetYaxis()->SetLabelSize(0.033*yscale);
h2->GetYaxis()->SetTitleSize(0.036*yscale);
h2->Draw("");
	c1->SaveAs("deltaphi_METak4jetjet.pdf");
	c1->SaveAs("deltaphi_METak4jetjet.png");
	c1->SaveAs("deltaphi_METak4jetjet.C");
	c1->SaveAs("deltaphi_METak4jetjet.root");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[23]->SetBottomMargin(0.05287462);
pad[23]->SetLogy(1);
pad[23]->Draw();
pad[23]->cd();

	t0_BkgHist[23]->Scale(0.148600);
	HistMax = t0_BkgHist[23]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t0_BkgHist[23],"VV","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t1_BkgHist[23]->Scale(0.002400);
	HistMax = t1_BkgHist[23]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t2_BkgHist[23]->Scale(0.000700);
	HistMax = t2_BkgHist[23]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t3_BkgHist[23]->Scale(0.206800);
	HistMax = t3_BkgHist[23]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t3_BkgHist[23],"S Top","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t4_BkgHist[23]->Scale(0.209600);
	HistMax = t4_BkgHist[23]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t5_BkgHist[23]->Scale(0.089900);
	HistMax = t5_BkgHist[23]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t6_BkgHist[23]->Scale(0.021200);
	HistMax = t6_BkgHist[23]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t7_BkgHist[23]->Scale(0.283600);
	HistMax = t7_BkgHist[23]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t7_BkgHist[23],"WJets","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t8_BkgHist[23]->Scale(0.420700);
	HistMax = t8_BkgHist[23]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t9_BkgHist[23]->Scale(0.031300);
	HistMax = t9_BkgHist[23]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t10_BkgHist[23]->Scale(0.000700);
	HistMax = t10_BkgHist[23]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t11_BkgHist[23]->Scale(0.144400);
	HistMax = t11_BkgHist[23]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t12_BkgHist[23]->Scale(0.019900);
	HistMax = t12_BkgHist[23]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t13_BkgHist[23]->Scale(0.004800);
	HistMax = t13_BkgHist[23]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t14_BkgHist[23]->Scale(0.026500);
	HistMax = t14_BkgHist[23]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t14_BkgHist[23],"TTbar","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	DataHist[23]->Sumw2();
	HistMax = DataHist[23]->GetMaximum()*1.80;
	leg->AddEntry(DataHist[23],"Data","pe");
	yMax=HistMax;

	hs[23]->Add(t0_BkgHist[23],"hist");
	hs[23]->Add(t1_BkgHist[23],"hist");
	hs[23]->Add(t2_BkgHist[23],"hist");
	hs[23]->Add(t3_BkgHist[23],"hist");
	hs[23]->Add(t4_BkgHist[23],"hist");
	hs[23]->Add(t5_BkgHist[23],"hist");
	hs[23]->Add(t6_BkgHist[23],"hist");
	hs[23]->Add(t7_BkgHist[23],"hist");
	hs[23]->Add(t8_BkgHist[23],"hist");
	hs[23]->Add(t9_BkgHist[23],"hist");
	hs[23]->Add(t10_BkgHist[23],"hist");
	hs[23]->Add(t11_BkgHist[23],"hist");
	hs[23]->Add(t12_BkgHist[23],"hist");
	hs[23]->Add(t13_BkgHist[23],"hist");
	hs[23]->Add(t14_BkgHist[23],"hist");
	hs[23]->SetMaximum(yMax);
	hs[23]->SetMinimum(0.1);
	hs[23]->Draw();
	DataHist[23]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[23]->Clone();
hRatio[23]->Add(t0_BkgHist[23]);
hRatio[23]->Add(t1_BkgHist[23]);
hRatio[23]->Add(t2_BkgHist[23]);
hRatio[23]->Add(t3_BkgHist[23]);
hRatio[23]->Add(t4_BkgHist[23]);
hRatio[23]->Add(t5_BkgHist[23]);
hRatio[23]->Add(t6_BkgHist[23]);
hRatio[23]->Add(t7_BkgHist[23]);
hRatio[23]->Add(t8_BkgHist[23]);
hRatio[23]->Add(t9_BkgHist[23]);
hRatio[23]->Add(t10_BkgHist[23]);
hRatio[23]->Add(t11_BkgHist[23]);
hRatio[23]->Add(t12_BkgHist[23]);
hRatio[23]->Add(t13_BkgHist[23]);
hRatio[23]->Add(t14_BkgHist[23]);


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
cout<<"Ratio of Data/MC = "<<(DataHist[23]->Integral())/(hRatio[23]->Integral())<<endl;
cout<<"Number of event in WW  = "<<t0_BkgHist[23]->Integral()<<endl;
cout<<"Number of event in WZ  = "<<t1_BkgHist[23]->Integral()<<endl;
cout<<"Number of event in ZZ  = "<<t2_BkgHist[23]->Integral()<<endl;
cout<<"Number of event in tWch  = "<<t3_BkgHist[23]->Integral()<<endl;
cout<<"Number of event in tWch_bar  = "<<t4_BkgHist[23]->Integral()<<endl;
cout<<"Number of event in tch_bar  = "<<t5_BkgHist[23]->Integral()<<endl;
cout<<"Number of event in sch  = "<<t6_BkgHist[23]->Integral()<<endl;
cout<<"Number of event in WJets100  = "<<t7_BkgHist[23]->Integral()<<endl;
cout<<"Number of event in WJets200  = "<<t8_BkgHist[23]->Integral()<<endl;
cout<<"Number of event in WJets1200  = "<<t9_BkgHist[23]->Integral()<<endl;
cout<<"Number of event in WJets2500  = "<<t10_BkgHist[23]->Integral()<<endl;
cout<<"Number of event in WJets400  = "<<t11_BkgHist[23]->Integral()<<endl;
cout<<"Number of event in WJets600  = "<<t12_BkgHist[23]->Integral()<<endl;
cout<<"Number of event in WJets  = "<<t13_BkgHist[23]->Integral()<<endl;
cout<<"Number of event in TTbar  = "<<t14_BkgHist[23]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("deltaphi_Vak4jetjet");
h2->GetXaxis()->CenterTitle(1);
h2->SetMinimum(0.5);
h2->SetMaximum(1.5);
h2->GetXaxis()->SetTitleOffset(0.8);
h2->GetXaxis()->SetLabelSize(0.033*yscale);
h2->GetXaxis()->SetTitleSize(0.036*yscale);
h2->GetXaxis()->SetTickLength(0.03*yscale);
h2->GetYaxis()->SetTitleOffset(0.3);
h2->GetYaxis()->SetNdivisions(5);
h2->GetYaxis()->SetLabelSize(0.033*yscale);
h2->GetYaxis()->SetTitleSize(0.036*yscale);
h2->Draw("");
	c1->SaveAs("deltaphi_Vak4jetjet.pdf");
	c1->SaveAs("deltaphi_Vak4jetjet.png");
	c1->SaveAs("deltaphi_Vak4jetjet.C");
	c1->SaveAs("deltaphi_Vak4jetjet.root");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[24]->SetBottomMargin(0.05287462);
pad[24]->SetLogy(1);
pad[24]->Draw();
pad[24]->cd();

	t0_BkgHist[24]->Scale(0.148600);
	HistMax = t0_BkgHist[24]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t0_BkgHist[24],"VV","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t1_BkgHist[24]->Scale(0.002400);
	HistMax = t1_BkgHist[24]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t2_BkgHist[24]->Scale(0.000700);
	HistMax = t2_BkgHist[24]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t3_BkgHist[24]->Scale(0.206800);
	HistMax = t3_BkgHist[24]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t3_BkgHist[24],"S Top","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t4_BkgHist[24]->Scale(0.209600);
	HistMax = t4_BkgHist[24]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t5_BkgHist[24]->Scale(0.089900);
	HistMax = t5_BkgHist[24]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t6_BkgHist[24]->Scale(0.021200);
	HistMax = t6_BkgHist[24]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t7_BkgHist[24]->Scale(0.283600);
	HistMax = t7_BkgHist[24]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t7_BkgHist[24],"WJets","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t8_BkgHist[24]->Scale(0.420700);
	HistMax = t8_BkgHist[24]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t9_BkgHist[24]->Scale(0.031300);
	HistMax = t9_BkgHist[24]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t10_BkgHist[24]->Scale(0.000700);
	HistMax = t10_BkgHist[24]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t11_BkgHist[24]->Scale(0.144400);
	HistMax = t11_BkgHist[24]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t12_BkgHist[24]->Scale(0.019900);
	HistMax = t12_BkgHist[24]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t13_BkgHist[24]->Scale(0.004800);
	HistMax = t13_BkgHist[24]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t14_BkgHist[24]->Scale(0.026500);
	HistMax = t14_BkgHist[24]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t14_BkgHist[24],"TTbar","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	DataHist[24]->Sumw2();
	HistMax = DataHist[24]->GetMaximum()*1.80;
	leg->AddEntry(DataHist[24],"Data","pe");
	yMax=HistMax;

	hs[24]->Add(t0_BkgHist[24],"hist");
	hs[24]->Add(t1_BkgHist[24],"hist");
	hs[24]->Add(t2_BkgHist[24],"hist");
	hs[24]->Add(t3_BkgHist[24],"hist");
	hs[24]->Add(t4_BkgHist[24],"hist");
	hs[24]->Add(t5_BkgHist[24],"hist");
	hs[24]->Add(t6_BkgHist[24],"hist");
	hs[24]->Add(t7_BkgHist[24],"hist");
	hs[24]->Add(t8_BkgHist[24],"hist");
	hs[24]->Add(t9_BkgHist[24],"hist");
	hs[24]->Add(t10_BkgHist[24],"hist");
	hs[24]->Add(t11_BkgHist[24],"hist");
	hs[24]->Add(t12_BkgHist[24],"hist");
	hs[24]->Add(t13_BkgHist[24],"hist");
	hs[24]->Add(t14_BkgHist[24],"hist");
	hs[24]->SetMaximum(yMax);
	hs[24]->SetMinimum(0.1);
	hs[24]->Draw();
	DataHist[24]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[24]->Clone();
hRatio[24]->Add(t0_BkgHist[24]);
hRatio[24]->Add(t1_BkgHist[24]);
hRatio[24]->Add(t2_BkgHist[24]);
hRatio[24]->Add(t3_BkgHist[24]);
hRatio[24]->Add(t4_BkgHist[24]);
hRatio[24]->Add(t5_BkgHist[24]);
hRatio[24]->Add(t6_BkgHist[24]);
hRatio[24]->Add(t7_BkgHist[24]);
hRatio[24]->Add(t8_BkgHist[24]);
hRatio[24]->Add(t9_BkgHist[24]);
hRatio[24]->Add(t10_BkgHist[24]);
hRatio[24]->Add(t11_BkgHist[24]);
hRatio[24]->Add(t12_BkgHist[24]);
hRatio[24]->Add(t13_BkgHist[24]);
hRatio[24]->Add(t14_BkgHist[24]);


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
cout<<"Ratio of Data/MC = "<<(DataHist[24]->Integral())/(hRatio[24]->Integral())<<endl;
cout<<"Number of event in WW  = "<<t0_BkgHist[24]->Integral()<<endl;
cout<<"Number of event in WZ  = "<<t1_BkgHist[24]->Integral()<<endl;
cout<<"Number of event in ZZ  = "<<t2_BkgHist[24]->Integral()<<endl;
cout<<"Number of event in tWch  = "<<t3_BkgHist[24]->Integral()<<endl;
cout<<"Number of event in tWch_bar  = "<<t4_BkgHist[24]->Integral()<<endl;
cout<<"Number of event in tch_bar  = "<<t5_BkgHist[24]->Integral()<<endl;
cout<<"Number of event in sch  = "<<t6_BkgHist[24]->Integral()<<endl;
cout<<"Number of event in WJets100  = "<<t7_BkgHist[24]->Integral()<<endl;
cout<<"Number of event in WJets200  = "<<t8_BkgHist[24]->Integral()<<endl;
cout<<"Number of event in WJets1200  = "<<t9_BkgHist[24]->Integral()<<endl;
cout<<"Number of event in WJets2500  = "<<t10_BkgHist[24]->Integral()<<endl;
cout<<"Number of event in WJets400  = "<<t11_BkgHist[24]->Integral()<<endl;
cout<<"Number of event in WJets600  = "<<t12_BkgHist[24]->Integral()<<endl;
cout<<"Number of event in WJets  = "<<t13_BkgHist[24]->Integral()<<endl;
cout<<"Number of event in TTbar  = "<<t14_BkgHist[24]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("njets");
h2->GetXaxis()->CenterTitle(1);
h2->SetMinimum(0.5);
h2->SetMaximum(1.5);
h2->GetXaxis()->SetTitleOffset(0.8);
h2->GetXaxis()->SetLabelSize(0.033*yscale);
h2->GetXaxis()->SetTitleSize(0.036*yscale);
h2->GetXaxis()->SetTickLength(0.03*yscale);
h2->GetYaxis()->SetTitleOffset(0.3);
h2->GetYaxis()->SetNdivisions(5);
h2->GetYaxis()->SetLabelSize(0.033*yscale);
h2->GetYaxis()->SetTitleSize(0.036*yscale);
h2->Draw("");
	c1->SaveAs("njets.pdf");
	c1->SaveAs("njets.png");
	c1->SaveAs("njets.C");
	c1->SaveAs("njets.root");
	leg->Clear();
	c1->Clear();
	//###########################################################


pad[25]->SetBottomMargin(0.05287462);
pad[25]->SetLogy(1);
pad[25]->Draw();
pad[25]->cd();

	t0_BkgHist[25]->Scale(0.148600);
	HistMax = t0_BkgHist[25]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t0_BkgHist[25],"VV","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t1_BkgHist[25]->Scale(0.002400);
	HistMax = t1_BkgHist[25]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t2_BkgHist[25]->Scale(0.000700);
	HistMax = t2_BkgHist[25]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t3_BkgHist[25]->Scale(0.206800);
	HistMax = t3_BkgHist[25]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t3_BkgHist[25],"S Top","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t4_BkgHist[25]->Scale(0.209600);
	HistMax = t4_BkgHist[25]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t5_BkgHist[25]->Scale(0.089900);
	HistMax = t5_BkgHist[25]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t6_BkgHist[25]->Scale(0.021200);
	HistMax = t6_BkgHist[25]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t7_BkgHist[25]->Scale(0.283600);
	HistMax = t7_BkgHist[25]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t7_BkgHist[25],"WJets","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t8_BkgHist[25]->Scale(0.420700);
	HistMax = t8_BkgHist[25]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t9_BkgHist[25]->Scale(0.031300);
	HistMax = t9_BkgHist[25]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t10_BkgHist[25]->Scale(0.000700);
	HistMax = t10_BkgHist[25]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t11_BkgHist[25]->Scale(0.144400);
	HistMax = t11_BkgHist[25]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t12_BkgHist[25]->Scale(0.019900);
	HistMax = t12_BkgHist[25]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t13_BkgHist[25]->Scale(0.004800);
	HistMax = t13_BkgHist[25]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	t14_BkgHist[25]->Scale(0.026500);
	HistMax = t14_BkgHist[25]->GetMaximum()*1.80;
	t0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));
	t0_BkgHist[0]->SetMinimum(0.1);
	leg->AddEntry(t14_BkgHist[25],"TTbar","f");
	yMax=HistMax;

	cout<<"=====> 	HistMax = "<<yMax<<endl;
	DataHist[25]->Sumw2();
	HistMax = DataHist[25]->GetMaximum()*1.80;
	leg->AddEntry(DataHist[25],"Data","pe");
	yMax=HistMax;

	hs[25]->Add(t0_BkgHist[25],"hist");
	hs[25]->Add(t1_BkgHist[25],"hist");
	hs[25]->Add(t2_BkgHist[25],"hist");
	hs[25]->Add(t3_BkgHist[25],"hist");
	hs[25]->Add(t4_BkgHist[25],"hist");
	hs[25]->Add(t5_BkgHist[25],"hist");
	hs[25]->Add(t6_BkgHist[25],"hist");
	hs[25]->Add(t7_BkgHist[25],"hist");
	hs[25]->Add(t8_BkgHist[25],"hist");
	hs[25]->Add(t9_BkgHist[25],"hist");
	hs[25]->Add(t10_BkgHist[25],"hist");
	hs[25]->Add(t11_BkgHist[25],"hist");
	hs[25]->Add(t12_BkgHist[25],"hist");
	hs[25]->Add(t13_BkgHist[25],"hist");
	hs[25]->Add(t14_BkgHist[25],"hist");
	hs[25]->SetMaximum(yMax);
	hs[25]->SetMinimum(0.1);
	hs[25]->Draw();
	DataHist[25]->Draw("same");
	leg->Draw("same");
h2 = (TH1F*)DataHist[25]->Clone();
hRatio[25]->Add(t0_BkgHist[25]);
hRatio[25]->Add(t1_BkgHist[25]);
hRatio[25]->Add(t2_BkgHist[25]);
hRatio[25]->Add(t3_BkgHist[25]);
hRatio[25]->Add(t4_BkgHist[25]);
hRatio[25]->Add(t5_BkgHist[25]);
hRatio[25]->Add(t6_BkgHist[25]);
hRatio[25]->Add(t7_BkgHist[25]);
hRatio[25]->Add(t8_BkgHist[25]);
hRatio[25]->Add(t9_BkgHist[25]);
hRatio[25]->Add(t10_BkgHist[25]);
hRatio[25]->Add(t11_BkgHist[25]);
hRatio[25]->Add(t12_BkgHist[25]);
hRatio[25]->Add(t13_BkgHist[25]);
hRatio[25]->Add(t14_BkgHist[25]);


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
cout<<"Ratio of Data/MC = "<<(DataHist[25]->Integral())/(hRatio[25]->Integral())<<endl;
cout<<"Number of event in WW  = "<<t0_BkgHist[25]->Integral()<<endl;
cout<<"Number of event in WZ  = "<<t1_BkgHist[25]->Integral()<<endl;
cout<<"Number of event in ZZ  = "<<t2_BkgHist[25]->Integral()<<endl;
cout<<"Number of event in tWch  = "<<t3_BkgHist[25]->Integral()<<endl;
cout<<"Number of event in tWch_bar  = "<<t4_BkgHist[25]->Integral()<<endl;
cout<<"Number of event in tch_bar  = "<<t5_BkgHist[25]->Integral()<<endl;
cout<<"Number of event in sch  = "<<t6_BkgHist[25]->Integral()<<endl;
cout<<"Number of event in WJets100  = "<<t7_BkgHist[25]->Integral()<<endl;
cout<<"Number of event in WJets200  = "<<t8_BkgHist[25]->Integral()<<endl;
cout<<"Number of event in WJets1200  = "<<t9_BkgHist[25]->Integral()<<endl;
cout<<"Number of event in WJets2500  = "<<t10_BkgHist[25]->Integral()<<endl;
cout<<"Number of event in WJets400  = "<<t11_BkgHist[25]->Integral()<<endl;
cout<<"Number of event in WJets600  = "<<t12_BkgHist[25]->Integral()<<endl;
cout<<"Number of event in WJets  = "<<t13_BkgHist[25]->Integral()<<endl;
cout<<"Number of event in TTbar  = "<<t14_BkgHist[25]->Integral()<<endl;
h2->SetMarkerStyle(21);
h2->SetStats(0);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->GetXaxis()->SetTitle("nVBFPairs");
h2->GetXaxis()->CenterTitle(1);
h2->SetMinimum(0.5);
h2->SetMaximum(1.5);
h2->GetXaxis()->SetTitleOffset(0.8);
h2->GetXaxis()->SetLabelSize(0.033*yscale);
h2->GetXaxis()->SetTitleSize(0.036*yscale);
h2->GetXaxis()->SetTickLength(0.03*yscale);
h2->GetYaxis()->SetTitleOffset(0.3);
h2->GetYaxis()->SetNdivisions(5);
h2->GetYaxis()->SetLabelSize(0.033*yscale);
h2->GetYaxis()->SetTitleSize(0.036*yscale);
h2->Draw("");
	c1->SaveAs("nVBFPairs.pdf");
	c1->SaveAs("nVBFPairs.png");
	c1->SaveAs("nVBFPairs.C");
	c1->SaveAs("nVBFPairs.root");
	leg->Clear();
	c1->Clear();
	//###########################################################


	int t1 = time(NULL);

	printf ("time to run this code = %d secs", t1 - t0);


}
