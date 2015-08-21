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

TFile fData("/home/ramkrishna/TEMP/AnalysisWWTrees/output_el/WWTree_data_el_17jul.root");
TTree *TData = (TTree*)fData.Get("otree");
TFile f0("/home/ramkrishna/TEMP/AnalysisWWTrees/output_el/WWTree_WJets_50ns.root");
TTree *T0 = (TTree*)f0.Get("otree");
TFile f1("/home/ramkrishna/TEMP/AnalysisWWTrees/output_el/WWTree_TTbar_madgraph_50ns.root");
TTree *T1 = (TTree*)f1.Get("otree");
TFile * file = new TFile("plot_TnP.root","RECREATE"); 

//========================= Cut Detail Starts ========================================================
TCut cutMu = "MuonsPt>20 && MuonsEta <2.5";
TCut cutJet = "JetsPt[0] > 30 && JetsPt[1] > 30 && JetsPt[2] > 30 && JetsPt[3] > 30";
TCut cutVBF = "abs(JetsEta[0]-JetsEta[1])>3.0";

TCut cut = cutMu && cutJet;
//========================= Cut Detail Ends ==========================================================
//========================================================================== canvas 0 starts =========
 
TCanvas *c0 = new TCanvas("c0", "c0",201,27,989,682);
	c0->SetFillColor(0);
	c0->SetFrameBorderSize(1);

TPad *pad0 = new TPad("pad0","pad0",0,0.2,1,1);
	pad0->SetBottomMargin(0.03287462);
	//pad0->SetLogy(1);
	pad0->Draw();
	pad0->cd();

THStack *hs = new THStack("hs","Number of Vertex");	// Defined Stacked histogram
TLegend *tleg0_8 = new TLegend(0.70,0.80,0.85,0.90,NULL,"brNDC");   // Defined legend

TH1F *j0_1 = new TH1F("j0_1","Nvtx",40,0,40);
	T0->Draw("NVtx>>j0_1",cut,"goff");
	j0_1->SetLineColor(kBlack);
	j0_1->SetLineWidth(2);
	j0_1->SetStats(0);
	j0_1->Sumw2();
	
TH1F *j1_1 = new TH1F("j1_1","Nvtx",40,0,40);
	T1->Draw("NVtx>>j1_1",cut,"goff");
	j1_1->SetLineColor(kBlack);
	j1_1->SetLineWidth(2);
	j1_1->SetStats(0);
	j1_1->Sumw2();
	
TH1F *j2_1 = new TH1F("j2_1","Number of Vertex",40,0,40);
  T2->Draw("NVtx>>j2_1",cut,"goff");
//  T2->Draw("JetsPt[3]>>j2_1","");
  j2_1->SetFillColor(kRed);
  j2_1->SetLineColor(kRed);
  j2_1->SetLineWidth(2);
  j2_1->SetStats(0);

hs->Add(j2_1);

j2_1->Scale(w_WJets);
j1_1->Scale(1.);


TH1F *h1_1 = new TH1F("h1_1","Ratio",40,0,40);
//TH1F *h2 = new TH1F("h2","",40,76.,106.);
//TF1* dedxpf = (TF1*)dedxf->Clone();
TH1F *h2 = (TH1F*)j1_1->Clone();
h1_1->Add(j2_1);

hs->SetMaximum(1600.);
hs->Draw();
 pad1->Update();
j1_1->Draw("sames");
 pad1->Update();

  tleg1_8->AddEntry(j1_1,"Data","p");
  tleg1_8->AddEntry(j2_1,"WJets","f");
 tleg1_8->SetFillColor(kWhite);
 tleg1_8->Draw("sames");
c1->cd();

TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.2);
  // TH1F *hs1=hs->Clone();
   pad2->SetGridy(1);
   pad2->SetPad(0,0.0,1.0,0.2);
   pad2->SetTopMargin(0);
   pad2->SetBottomMargin(0.5);
   pad2->Draw();
   pad2->cd();
  float yscale = (1.0-0.2)/(0.18-0);
  h2->Divide(h1_1);
  h2->SetMarkerStyle(21);
  h2->SetStats(0);
//  h1->SetMinimum(0.5);
//  h1->SetMaximum(1.5);
  h2->GetYaxis()->SetTitle("Data/#Sigma MC");
  h2->SetMinimum(-0.4);
  h2->SetMaximum(2.8);
  h2->GetXaxis()->SetTitle("");
  h2->GetXaxis()->SetTitleOffset(1.3);
  h2->GetXaxis()->SetLabelSize(0.033*yscale);
  h2->GetXaxis()->SetTitleSize(0.036*yscale);
  h2->GetXaxis()->SetTickLength(0.03*yscale);
//h1->GetYaxis()->SetLabelFont(63);
//h1->GetYaxis()->SetLabelSize(12);
h2->GetYaxis()->SetTitleOffset(0.3);
h2->GetYaxis()->SetNdivisions(5);
h2->GetYaxis()->SetLabelSize(0.033*yscale);
h2->GetYaxis()->SetTitleSize(0.036*yscale);
   h2->Draw("");

c1->SaveAs("Plots/pdf/OutputPlot.pdf");
c1->SaveAs("Plots/png/OutputPlot.png");
c1->SaveAs("Plots/C/OutputPlot.C");
//c1->SaveAs("OutputPlot.root");
c1->Write();
//=====================

//========================================================================== canvas 1 starts =========
 
TCanvas *c1 = new TCanvas("c1", "c1",201,27,989,682);
	c1->SetFillColor(0);
	c1->SetFrameBorderSize(1);

TPad *pad1 = new TPad("pad1","pad1",0,0.2,1,1);
	pad1->SetBottomMargin(0.03287462);
	//pad1->SetLogy(1);
	pad1->Draw();
	pad1->cd();

THStack *hs = new THStack("hs","Number of Vertex");	// Defined Stacked histogram
TLegend *tleg1_8 = new TLegend(0.70,0.80,0.85,0.90,NULL,"brNDC");   // Defined legend

TH1F *j0_1 = new TH1F("j0_1","pt",40,0,40);
	T0->Draw("pt>>j0_1",cut,"goff");
	j0_1->SetLineColor(kBlack);
	j0_1->SetLineWidth(2);
	j0_1->SetStats(0);
	j0_1->Sumw2();
	
TH1F *j1_1 = new TH1F("j1_1","pt",40,0,40);
	T1->Draw("pt>>j1_1",cut,"goff");
	j1_1->SetLineColor(kBlack);
	j1_1->SetLineWidth(2);
	j1_1->SetStats(0);
	j1_1->Sumw2();
	
TH1F *j2_1 = new TH1F("j2_1","Number of Vertex",40,0,40);
  T2->Draw("NVtx>>j2_1",cut,"goff");
//  T2->Draw("JetsPt[3]>>j2_1","");
  j2_1->SetFillColor(kRed);
  j2_1->SetLineColor(kRed);
  j2_1->SetLineWidth(2);
  j2_1->SetStats(0);

hs->Add(j2_1);

j2_1->Scale(w_WJets);
j1_1->Scale(1.);


TH1F *h1_1 = new TH1F("h1_1","Ratio",40,0,40);
//TH1F *h2 = new TH1F("h2","",40,76.,106.);
//TF1* dedxpf = (TF1*)dedxf->Clone();
TH1F *h2 = (TH1F*)j1_1->Clone();
h1_1->Add(j2_1);

hs->SetMaximum(1600.);
hs->Draw();
 pad1->Update();
j1_1->Draw("sames");
 pad1->Update();

  tleg1_8->AddEntry(j1_1,"Data","p");
  tleg1_8->AddEntry(j2_1,"WJets","f");
 tleg1_8->SetFillColor(kWhite);
 tleg1_8->Draw("sames");
c1->cd();

TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.2);
  // TH1F *hs1=hs->Clone();
   pad2->SetGridy(1);
   pad2->SetPad(0,0.0,1.0,0.2);
   pad2->SetTopMargin(0);
   pad2->SetBottomMargin(0.5);
   pad2->Draw();
   pad2->cd();
  float yscale = (1.0-0.2)/(0.18-0);
  h2->Divide(h1_1);
  h2->SetMarkerStyle(21);
  h2->SetStats(0);
//  h1->SetMinimum(0.5);
//  h1->SetMaximum(1.5);
  h2->GetYaxis()->SetTitle("Data/#Sigma MC");
  h2->SetMinimum(-0.4);
  h2->SetMaximum(2.8);
  h2->GetXaxis()->SetTitle("");
  h2->GetXaxis()->SetTitleOffset(1.3);
  h2->GetXaxis()->SetLabelSize(0.033*yscale);
  h2->GetXaxis()->SetTitleSize(0.036*yscale);
  h2->GetXaxis()->SetTickLength(0.03*yscale);
//h1->GetYaxis()->SetLabelFont(63);
//h1->GetYaxis()->SetLabelSize(12);
h2->GetYaxis()->SetTitleOffset(0.3);
h2->GetYaxis()->SetNdivisions(5);
h2->GetYaxis()->SetLabelSize(0.033*yscale);
h2->GetYaxis()->SetTitleSize(0.036*yscale);
   h2->Draw("");

c1->SaveAs("Plots/pdf/OutputPlot.pdf");
c1->SaveAs("Plots/png/OutputPlot.png");
c1->SaveAs("Plots/C/OutputPlot.C");
//c1->SaveAs("OutputPlot.root");
c1->Write();
//=====================

file->Close();
}
