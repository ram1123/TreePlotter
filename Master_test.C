#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "ClassReadTree.cc"
#include "TChain.h"
#include "TString.h"
#include "TLorentzVector.h"
#include <vector>
#include <iostream>
using namespace std;
void Master_test( ){//main programme




TChain* t = new TChain("TreeMaker2/PreSelection");
t->Add("PHYS14.GJets_HT-400to600_Tune4C_13TeV-madgraph-tauola_105_RA2AnalysisTree.root");

TChain* ttbar = new TChain("TreeMaker2/PreSelection");
ttbar->Add("PHYS14.GJets_HT-400to600_Tune4C_13TeV-madgraph-tauola_105_RA2AnalysisTree.root");


ClassReadTree G400(t);
ClassReadTree TTbar(ttbar);



//for( int iEv = 0 ; iEv < t->GetEntries() ; iEv++){//
for( int iEv = 0 ; iEv < 1 ; iEv++){//
t->GetEntry(iEv);

cout<<"Photon size  : "<<G400.NVtx<<endl;
}//
}
