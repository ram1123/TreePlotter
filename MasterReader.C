#include<iostream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TLorentzVector.h"
#include<vector>
#include "TTree.h"
using namespace std;


void MasterReader(){
 
TChain* t = new TChain("TreeMaker2/PreSelection");
0
t->Add(0);
}
