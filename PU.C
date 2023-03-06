/*
 * =====================================================================================
 *
 *       Filename:  PU.C
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Wednesday 13 July 2016 06:01.19  CEST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ramkrishna Sharma (Ram), ramkrishna.sharma71@gmail.com
 *   Organization:  University Of Delhi, Delhi, India
 *
 * =====================================================================================
 */

void PU() {
TGaxis::SetMaxDigits(3);
TFile f1("/uscms_data/d3/rasharma/aQGC_analysis/AnalysisFramework/SecondStep/CMSSW_8_0_11/src/WWAnalysisRun2/output/output_el/WWTree_data_golden_C1D1F1G1H23.root");
TFile f2("/uscms_data/d3/rasharma/aQGC_analysis/AnalysisFramework/SecondStep/CMSSW_8_0_11/src/WWAnalysisRun2/output/output_el/WWTree_WJets_madgraph_el.root");

TTree *T1 = (TTree*)f1.Get("otree");
TTree *T2 = (TTree*)f2.Get("otree");


TH1D *h1 = new TH1D("h1","Data",55,0.,55.);
h1->SetTitle("");
h1->SetStats(0);
h1->SetMarkerStyle(3);
//T1->Draw("nPV>>h1");
T1->Draw("nPV>>h1","eff_and_pu_Weight*(pfMET>50)");
h1->GetYaxis()->SetRange(0,90000);
h1->GetYaxis()->SetTitleOffset(1.1);
h1->GetYaxis()->SetTitle("Normalized to Number of Events in Data");
h1->GetXaxis()->SetTitle("nPV");
//h1->GetXaxis()->SetTitle("nPV","pfMET>50");
//h1->Scale(1/h1->Integral());


TH1D *h2 = new TH1D("h2","WJets",55,0.,55.);
h2->SetTitle("");
h2->SetStats(0);
h2->SetMarkerStyle(2);
h2->SetLineColor(2);
h2->SetMarkerColor(2);
h2->GetYaxis()->SetTitleOffset(1.1);
h2->GetYaxis()->SetTitle("Normalized to Number of Events in Data");
h2->GetXaxis()->SetTitle("nPV");
//h2->SetFillColor(2);
h2->GetYaxis()->SetRange(0,90000);
//T2->Draw("nPV>>h2");
T2->Draw("nPV>>h2","eff_and_pu_Weight*(pfMET>50)");
//T2->Draw("nPV>>h2","totalEventWeight");
h2->Scale((h1->Integral())/(h2->Integral()));

TCanvas *c1 = new TCanvas("c1");
c1->cd();

h1->Draw("hist");
h2->Draw("sames hist");
TLegend * leg = new TLegend(0.7,0.7,0.90,0.9);
leg->AddEntry(h1,"Data","l");
leg->AddEntry(h2,"Wjets","l");
leg->Draw();

c1->SaveAs("pileup.pdf");

//
//TFile f("/tmp/PileUpHisto.root","recreate");
//
// h1->Scale(1./h1->Integral());
// h2->Scale(1./h2->Integral());
// h1->Divide(h2);
//
//h1->Write();
////h2->Write();
//f.Close();
}
