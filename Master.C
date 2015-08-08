#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "ReadTreeClass.cc"
#include "TChain.h"
#include "TString.h"
#include "TLorentzVector.h"
#include <vector>
#include <iostream>
using namespace std;
void Master( ){//main programme




TChain* t = new TChain("TreeMaker2/PreSelection");
t->Add("PHYS14.GJets_HT-400to600_Tune4C_13TeV-madgraph-tauola_105_RA2AnalysisTree.root");

TChain* ttbar = new TChain("TreeMaker2/PreSelection");
ttbar->Add("PHYS14.GJets_HT-400to600_Tune4C_13TeV-madgraph-tauola_105_RA2AnalysisTree.root");


ReadTreeClass G400(t);
ReadTreeClass TTbar(ttbar);



for( int iEv = 0 ; iEv < t->GetEntries() ; iEv++){//
t->GetEntry(iEv);

cout<<"Photon size  : "<<G400.NVtx<<endl;


















}//



































}
