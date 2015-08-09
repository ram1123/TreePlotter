#include<iostream>
using namespace std;

void treename(){


TFile *MyFile = new TFile("PHYS14.GJets_HT-400to600_Tune4C_13TeV-madgraph-tauola_105_RA2AnalysisTree.root","READ");


cout<<gROOT->ProcessLine("gDirectory->ls()")<<endl;



//cout<<"dir name = "<<gDirectory->ls()<<endl;












} 
