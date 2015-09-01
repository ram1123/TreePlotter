#include<iostream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TLorentzVector.h"
#include<vector>
#include "TTree.h"
using namespace std;


//#include "setTDRStyle.C"
//#include "CMS_lumi.C"
void plot_TnP1()
{
//========================= Add TDRStyle Starts ======================================================
//  gROOT->LoadMacro("setTDRStyle.C");
//  setTDRStyle();

//  gROOT->LoadMacro("CMS_lumi.C");
/*
  writeExtraText = true;       // if extra text
  extraText  = "Preliminary";  // default extra text is "Preliminary"
 lumi_13TeV  = "5.59 pb^{-1}"; // default is "19.7 fb^{-1}"
  lumi_7TeV  = "4.9 fb^{-1}";  // default is "5.1 fb^{-1}"

  int iPeriod = 4;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV 
*/
//========================= Add TDRStyle Ends ========================================================

//========================= Scale Factors   ==========================================================    
double w_WJets = 5.59*61526.7/345324 ;

TFile fData("/home/ramkrishna/TEMP/DataMCComparision/WWTree_data_el_17jul.root");
TTree *TData = (TTree*)fData.Get("otree");
TFile f1("/home/ramkrishna/TEMP/DataMCComparision/WWTree_data_el_prompt.root");
TTree *T1 = (TTree*)f1.Get("otree");
TFile f2("/home/ramkrishna/TEMP/DataMCComparision/WWTree_WJets_50ns.root");
TTree *T2 = (TTree*)f2.Get("otree");
TFile f3("/home/ramkrishna/TEMP/DataMCComparision/WWTree_TTbar_madgraph_50ns.root");
TTree *T3 = (TTree*)f3.Get("otree");
TFile * file = new TFile("plot_TnP.root","RECREATE"); 

//========================= Cut Detail Starts ========================================================
TCut cutMu = "MuonsPt>20 && MuonsEta <2.5";
TCut cutJet = "JetsPt[0] > 30 && JetsPt[1] > 30 && JetsPt[2] > 30 && JetsPt[3] > 30";
TCut cutVBF = "abs(JetsEta[0]-JetsEta[1])>3.0";

TCut cut = "totalEventWeight";
//========================= Cut Detail Ends ==========================================================
//========================================================================== canvas 1 starts =========
 
TCanvas *c1 = new TCanvas("c1", "c1",201,27,989,682);
	c1->SetFillColor(0);
	c1->SetFrameBorderSize(1);

TPad *pad1_1 = new TPad("pad1_1","pad1_1",0,0.2,1,1);
	pad1_1->SetBottomMargin(0.03287462);
	//pad1_1->SetLogy(1);
	pad1_1->Draw();
	pad1_1->cd();

THStack *hs1 = new THStack("hs1","Number of Vertex");	// Defined Stacked histogram
TLegend *tleg1_8 = new TLegend(0.70,0.80,0.85,0.90,NULL,"brNDC");   // Defined legend

TH1F *j1_1 = new TH1F("j1_1","Nvtx",40,0,40);
	T1->Draw("nPV>>j1_1",cut,"goff");
	j1_1->SetLineColor(1);
	j1_1->SetLineWidth(2);
	j1_1->SetStats(0);
	j1_1->Sumw2();
	



TH1F *j1_2 = new TH1F("j1_2","Nvtx",40,0,40);
	T2->Draw("nPV>>j1_2",cut,"goff");
	j1_2->SetLineColor(2);
	j1_2->SetLineWidth(2);
	j1_2->SetStats(0);
	



TH1F *j1_3 = new TH1F("j1_3","Nvtx",40,0,40);
	T3->Draw("nPV>>j1_3",cut,"goff");
	j1_3->SetLineColor(3);
	j1_3->SetLineWidth(2);
	j1_3->SetStats(0);
	



hs1->Add(j1_2);
hs1->Add(j1_3);

j1_1->Scale(1.0);
j1_2->Scale(1.0);
j1_3->Scale(1.0);
TH1F *h1_1 = new TH1F("h1_1","Ratio",40, 0, 40);
TH1F *h1 = (TH1F*)j1_3->Clone();
h1_1->Add(j1_1);
h1_1->Add(j1_2);
h1_1->Add(j1_3);

//hs1->SetMaximum(1600.);
hs1->Draw();
pad1_1->Update();
j1_1->Draw("sames"); // Draw the signal
pad1_1->Update();

tleg1_8->AddEntry(j1_1,"WWTree_data_el_prompt.root","l");
tleg1_8->AddEntry(j1_2,"WWTree_WJets_50ns.root","l");
tleg1_8->AddEntry(j1_3,"WWTree_TTbar_madgraph_50ns.root","l");
tleg1_8->SetFillColor(kWhite);
tleg1_8->Draw("sames");
c1->cd();

TPad *pad1_2 = new TPad("pad1_2","pad1_2",0,0,1,0.2);
// TH1F *hs11=hs1->Clone();
pad1_2->SetGridy(1);
pad1_2->SetPad(0,0.0,1.0,0.2);
pad1_2->SetTopMargin(0);
pad1_2->SetBottomMargin(0.5);
pad1_2->Draw();
pad1_2->cd();
float yscale_1 = (1.0-0.2)/(0.18-0);
h1->Divide(h1_1);
h1->SetMarkerStyle(21);
h1->SetStats(0);
//h1->SetMinimum(0.5);
//h1->SetMaximum(1.5);
h1->GetYaxis()->SetTitle("Data/#Sigma MC");
h1->SetMinimum(-0.4);
h1->SetMaximum(2.8);
h1->GetXaxis()->SetTitle("");
h1->GetXaxis()->SetTitleOffset(1.3);
h1->GetXaxis()->SetLabelSize(0.033*yscale_1);
h1->GetXaxis()->SetTitleSize(0.036*yscale_1);
h1->GetXaxis()->SetTickLength(0.03*yscale_1);
//h1->GetYaxis()->SetLabelFont(63);
//h1->GetYaxis()->SetLabelSize(12);
h1->GetYaxis()->SetTitleOffset(0.3);
h1->GetYaxis()->SetNdivisions(5);
h1->GetYaxis()->SetLabelSize(0.033*yscale_1);
h1->GetYaxis()->SetTitleSize(0.036*yscale_1);
h1->Draw("");

c1->SaveAs("Plots/pdf/NVtx.pdf");
c1->SaveAs("Plots/png/NVtx.png");
c1->SaveAs("Plots/C/NVtx.C");
//c1->SaveAs("NVtx.root");
c1->Write();
//=====================

//========================================================================== canvas 2 starts =========
 
TCanvas *c2 = new TCanvas("c2", "c2",201,27,989,682);
	c2->SetFillColor(0);
	c2->SetFrameBorderSize(1);

TPad *pad2_1 = new TPad("pad2_1","pad2_1",0,0.2,1,1);
	pad2_1->SetBottomMargin(0.03287462);
	//pad2_1->SetLogy(1);
	pad2_1->Draw();
	pad2_1->cd();

THStack *hs2 = new THStack("hs2","Number of Vertex");	// Defined Stacked histogram
TLegend *tleg2_8 = new TLegend(0.70,0.80,0.85,0.90,NULL,"brNDC");   // Defined legend

TH1F *j2_1 = new TH1F("j2_1","pt",40,0,300);
	T1->Draw("l_pt>>j2_1",cut,"goff");
	j2_1->SetLineColor(1);
	j2_1->SetLineWidth(2);
	j2_1->SetStats(0);
	j2_1->Sumw2();
	



TH1F *j2_2 = new TH1F("j2_2","pt",40,0,300);
	T2->Draw("l_pt>>j2_2",cut,"goff");
	j2_2->SetLineColor(2);
	j2_2->SetLineWidth(2);
	j2_2->SetStats(0);
	



TH1F *j2_3 = new TH1F("j2_3","pt",40,0,300);
	T3->Draw("l_pt>>j2_3",cut,"goff");
	j2_3->SetLineColor(3);
	j2_3->SetLineWidth(2);
	j2_3->SetStats(0);
	



hs2->Add(j2_2);
hs2->Add(j2_3);

j2_1->Scale(1.0);
j2_2->Scale(1.0);
j2_3->Scale(1.0);
TH1F *h2_1 = new TH1F("h2_1","Ratio",40, 0, 300);
TH1F *h2 = (TH1F*)j2_3->Clone();
h2_1->Add(j2_1);
h2_1->Add(j2_2);
h2_1->Add(j2_3);

//hs2->SetMaximum(1600.);
hs2->Draw();
pad2_1->Update();
j2_1->Draw("sames"); // Draw the signal
pad2_1->Update();

tleg2_8->AddEntry(j2_1,"WWTree_data_el_prompt.root","l");
tleg2_8->AddEntry(j2_2,"WWTree_WJets_50ns.root","l");
tleg2_8->AddEntry(j2_3,"WWTree_TTbar_madgraph_50ns.root","l");
tleg2_8->SetFillColor(kWhite);
tleg2_8->Draw("sames");
c2->cd();

TPad *pad2_2 = new TPad("pad2_2","pad2_2",0,0,1,0.2);
// TH1F *hs21=hs2->Clone();
pad2_2->SetGridy(1);
pad2_2->SetPad(0,0.0,1.0,0.2);
pad2_2->SetTopMargin(0);
pad2_2->SetBottomMargin(0.5);
pad2_2->Draw();
pad2_2->cd();
float yscale_2 = (1.0-0.2)/(0.18-0);
h2->Divide(h1_1);
h2->SetMarkerStyle(21);
h2->SetStats(0);
//h1->SetMinimum(0.5);
//h1->SetMaximum(1.5);
h2->GetYaxis()->SetTitle("Data/#Sigma MC");
h2->SetMinimum(-0.4);
h2->SetMaximum(2.8);
h2->GetXaxis()->SetTitle("");
h2->GetXaxis()->SetTitleOffset(1.3);
h2->GetXaxis()->SetLabelSize(0.033*yscale_2);
h2->GetXaxis()->SetTitleSize(0.036*yscale_2);
h2->GetXaxis()->SetTickLength(0.03*yscale_2);
//h2->GetYaxis()->SetLabelFont(63);
//h2->GetYaxis()->SetLabelSize(12);
h2->GetYaxis()->SetTitleOffset(0.3);
h2->GetYaxis()->SetNdivisions(5);
h2->GetYaxis()->SetLabelSize(0.033*yscale_2);
h2->GetYaxis()->SetTitleSize(0.036*yscale_2);
h2->Draw("");

c2->SaveAs("Plots/pdf/pt.pdf");
c2->SaveAs("Plots/png/pt.png");
c2->SaveAs("Plots/C/pt.C");
//c2->SaveAs("pt.root");
c2->Write();
//=====================

file->Close();
}
