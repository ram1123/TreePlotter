/*
 * Compare Root Files
 *
 */
#include "TCanvas.h"
#include "TROOT.h"

void GetPlots()
{
gROOT->ProcessLine(".L CompareAdvanced.C");

TCanvas *Canvas1 = new TCanvas("c1236","Muon",200,10,800,700);
gROOT->ProcessLine("compareQuantities(1,0,1,\"otree\",\"nPV\",\"\",\"\",40,0,40,\"\",2,\"/tmp/WWTree_data_el_17jul.root\",\"DataEl\",\"/tmp/WWTree_WJets_50ns.root\",\"WJets\")");
//gROOT->ProcessLine("compareQuantities(1,0,1,\"NVtx\",\"\",\"\",40,0,40,\"\",2,\"/home/ramkrishna/TEMP/Analysis/SingleMuonData2015B.root\",\"DataMu\",\"/home/ramkrishna/TEMP/Analysis/Merged_WJets.root\",\"WJets\")");
Canvas1->SaveAs("test.pdf");
Canvas1->Clear();

} 
