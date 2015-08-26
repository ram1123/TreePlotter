/*
 * Compare Root Files
 *
 */
#include "TCanvas.h"
#include "TROOT.h"
#include <iostream>

void GetPlots()
{
gROOT->ProcessLine(".L CompareAdvanced.C");

const string Cut = "(nPV>10)";

TCanvas *Canvas1 = new TCanvas("c1236","Muon",200,10,800,700);


gROOT->ProcessLine(Form("compareQuantities(1,0,1,\"otree\",\"nPV\",\"\",\"\",40,0,40,\"%s\",2,\"/tmp/WWTree_data_el_17jul.root\",\"DataEl\",\"/tmp/WWTree_WJets_50ns.root\",\"WJets\")",Cut.c_str()));
Canvas1->SaveAs("test.pdf");
Canvas1->Clear();

// You have to clone last 3 line for each variable you want to plot.

} 
