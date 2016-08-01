/*
 * =====================================================================================
 *
 *       Filename:  PU.C
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Wednesday 13 July 2016 06:01:59  CEST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ramkrishna Sharma (Ram), ramkrishna.sharma71@gmail.com
 *   Organization:  University Of Delhi, Delhi, India
 *
 * =====================================================================================
 */

void PU() {
TFile f1("/home/ramkrishna/cernbox/aQGC_Studies/SecondStep_Ntuples/Changed_VBF_Wjet_Selection/output/output_mu//WWTree_data_golden.root");
TFile f2("/home/ramkrishna/cernbox/aQGC_Studies/SecondStep_Ntuples/Changed_VBF_Wjet_Selection/output/output_mu//WWTree_WJets.root");
//TFile f1("/home/ramkrishna/cernbox/LaptopBackup/AllAnalysis/WWScattering/2ndStep/OutPut_of_2nd_Step/Understanding_Cuts/mu/data_mu_prompt_25ns_runD.root");
//TFile f2("/home/ramkrishna/cernbox/LaptopBackup/AllAnalysis/WWScattering/2ndStep/OutPut_of_2nd_Step/Understanding_Cuts/mu/WJets.root");

TTree *T1 = (TTree*)f1.Get("otree");
TTree *T2 = (TTree*)f2.Get("otree");


TH1D *h1 = new TH1D("h1","Data",40,0.,40.);
h1->SetMarkerStyle(3);
T1->Draw("nPV>>h1");
h1->SetMaximum(200000.0);
h1->SetMinimum(0.0);
//h1->Scale(1/h1->Integral());


TH1D *h2 = new TH1D("h2","WJets",40,0.,40.);
h2->SetMarkerStyle(2);
h2->SetLineColor(2);
h2->SetMarkerColor(2);
h2->SetFillColor(2);
h2->SetMaximum(200000.0);
h2->SetMinimum(0.0e3);
T2->Draw("nPV>>h2");
//T2->Draw("nPV>>h2","eff_and_pu_Weight");
h2->Scale((h1->Integral())/(h2->Integral()));

TCanvas *c1 = new TCanvas("c1");
c1->cd();

h2->Draw();
h1->Draw("sames");

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
