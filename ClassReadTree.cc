#include<iostream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TLorentzVector.h"
#include<vector>
#include "TTree.h"
using namespace std;

class ClassReadTree {

public :

   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   Int_t           fCurrent; //!current Tree number in a TChain



// Fixed size dimensions of array or collections stored in the TTree if any.



   // Declaration of leaf types

   Int_t           run;

   Int_t           event;

   Int_t           lumi;

   Int_t           njets;

   Int_t           nPV;

   Int_t           issignal;

   Float_t         wSampleWeight;

   Float_t         totalEventWeight;

   Float_t         eff_and_pu_Weight;

   Float_t         pfMET;

   Float_t         pfMET_Phi;

   Float_t         nu_pz_type0;

   Float_t         nu_pz_type2;

   Float_t         nu_pz_run2;

   Float_t         nu_pz_run2_oth;

   Int_t           nu_pz_run2_type;

   Int_t           nu_pz_isre;

   Float_t         l_pt;

   Float_t         l_eta;

   Float_t         l_phi;

   Float_t         l_e;

   Float_t         ungroomed_jet_pt;

   Float_t         ungroomed_jet_eta;

   Float_t         ungroomed_jet_phi;

   Float_t         ungroomed_jet_e;

   Float_t         jet_mass_pr;

   Float_t         jet_mass_so;

   Float_t         jet_mass_tr;

   Float_t         jet_mass_fi;

   Float_t         jet_tau2tau1;

   Float_t         ttb_ungroomed_jet_pt;

   Float_t         ttb_ungroomed_jet_eta;

   Float_t         ttb_ungroomed_jet_phi;

   Float_t         ttb_ungroomed_jet_e;

   Float_t         ttb_jet_mass_pr;

   Float_t         ttb_jet_mass_so;

   Float_t         ttb_jet_mass_tr;

   Float_t         ttb_jet_mass_fi;

   Float_t         ttb_jet_tau2tau1;

   Float_t         ttb_deltaeta_lak8jet;

   Float_t         W_pt_gen;

   Float_t         W_pz_gen;

   Float_t         W_rap_gen;

   Float_t         genGravMass;

   Float_t         nu_pz_gen;

   Float_t         nu_pt_gen;

   Float_t         nu_phi_gen;

   Float_t         nu_eta_gen;

   Float_t         hadW_pt_gen;

   Float_t         hadW_eta_gen;

   Float_t         hadW_phi_gen;

   Float_t         hadW_e_gen;

   Float_t         hadW_m_gen;

   Float_t         lepW_pt_gen;

   Float_t         lepW_eta_gen;

   Float_t         lepW_phi_gen;

   Float_t         lepW_e_gen;

   Float_t         lepW_m_gen;

   Float_t         AK8_pt_gen;

   Float_t         AK8_eta_gen;

   Float_t         AK8_phi_gen;

   Float_t         AK8_e_gen;

   Float_t         AK8_pruned_mass_gen;

   Float_t         AK8_softdrop_mass_gen;

   Float_t         deltaR_lak8jet;

   Float_t         deltaphi_METak8jet;

   Float_t         deltaphi_Vak8jet;

   Float_t         v_pt;

   Float_t         v_eta;

   Float_t         v_phi;

   Float_t         v_mt;

   Float_t         mass_lvj_type0;

   Float_t         mass_lvj_type2;

   Float_t         mass_lvj_run2;

   Int_t           nBTagJet_loose;

   Int_t           nBTagJet_medium;

   Int_t           nBTagJet_tight;

   Float_t         mass_leptonic_closerjet;

   Float_t         mass_ungroomedjet_closerjet;

   Float_t         AK8_closerjet_pt;

   Float_t         AK8_closerjet_eta;

   Float_t         AK8_closerjet_phi;

   Float_t         AK8_closerjet_e;

   Float_t         vbf_maxpt_j1_pt;

   Float_t         vbf_maxpt_j1_eta;

   Float_t         vbf_maxpt_j1_phi;

   Float_t         vbf_maxpt_j1_e;

   Float_t         vbf_maxpt_j1_bDiscriminatorCSV;

   Float_t         vbf_maxpt_j2_pt;

   Float_t         vbf_maxpt_j2_eta;

   Float_t         vbf_maxpt_j2_phi;

   Float_t         vbf_maxpt_j2_e;

   Float_t         vbf_maxpt_j2_bDiscriminatorCSV;

   Float_t         vbf_maxpt_jj_pt;

   Float_t         vbf_maxpt_jj_eta;

   Float_t         vbf_maxpt_jj_phi;

   Float_t         vbf_maxpt_jj_m;



   // List of branches

   TBranch        *b_run;   //!

   TBranch        *b_event;   //!

   TBranch        *b_lumi;   //!

   TBranch        *b_njets;   //!

   TBranch        *b_nPV;   //!

   TBranch        *b_issignal;   //!

   TBranch        *b_wSampleWeight;   //!

   TBranch        *b_totalEventWeight;   //!

   TBranch        *b_eff_and_pu_Weight;   //!

   TBranch        *b_pfMET;   //!

   TBranch        *b_pfMET_Phi;   //!

   TBranch        *b_nu_pz_type0;   //!

   TBranch        *b_nu_pz_type2;   //!

   TBranch        *b_nu_pz_run2;   //!

   TBranch        *b_nu_pz_run2_oth;   //!

   TBranch        *b_nu_pz_run2_type;   //!

   TBranch        *b_nu_pz_isre;   //!

   TBranch        *b_l_pt;   //!

   TBranch        *b_l_eta;   //!

   TBranch        *b_l_phi;   //!

   TBranch        *b_l_e;   //!

   TBranch        *b_ungroomed_jet_pt;   //!

   TBranch        *b_ungroomed_jet_eta;   //!

   TBranch        *b_ungroomed_jet_phi;   //!

   TBranch        *b_ungroomed_jet_e;   //!

   TBranch        *b_jet_mass_pr;   //!

   TBranch        *b_jet_mass_so;   //!

   TBranch        *b_jet_mass_tr;   //!

   TBranch        *b_jet_mass_fi;   //!

   TBranch        *b_jet_tau2tau1;   //!

   TBranch        *b_ttb_ungroomed_jet_pt;   //!

   TBranch        *b_ttb_ungroomed_jet_eta;   //!

   TBranch        *b_ttb_ungroomed_jet_phi;   //!

   TBranch        *b_ttb_ungroomed_jet_e;   //!

   TBranch        *b_ttb_jet_mass_pr;   //!

   TBranch        *b_ttb_jet_mass_so;   //!

   TBranch        *b_ttb_jet_mass_tr;   //!

   TBranch        *b_ttb_jet_mass_fi;   //!

   TBranch        *b_ttb_jet_tau2tau1;   //!

   TBranch        *b_ttb_deltaeta_lak8jet;   //!

   TBranch        *b_W_pt_gen;   //!

   TBranch        *b_W_pz_gen;   //!

   TBranch        *b_W_rap_gen;   //!

   TBranch        *b_genGravMass;   //!

   TBranch        *b_nu_pz_gen;   //!

   TBranch        *b_nu_pt_gen;   //!

   TBranch        *b_nu_phi_gen;   //!

   TBranch        *b_nu_eta_gen;   //!

   TBranch        *b_hadW_pt_gen;   //!

   TBranch        *b_hadW_eta_gen;   //!

   TBranch        *b_hadW_phi_gen;   //!

   TBranch        *b_hadW_e_gen;   //!

   TBranch        *b_hadW_m_gen;   //!

   TBranch        *b_lepW_pt_gen;   //!

   TBranch        *b_lepW_eta_gen;   //!

   TBranch        *b_lepW_phi_gen;   //!

   TBranch        *b_lepW_e_gen;   //!

   TBranch        *b_lepW_m_gen;   //!

   TBranch        *b_AK8_pt_gen;   //!

   TBranch        *b_AK8_eta_gen;   //!

   TBranch        *b_AK8_phi_gen;   //!

   TBranch        *b_AK8_e_gen;   //!

   TBranch        *b_AK8_pruned_mass_gen;   //!

   TBranch        *b_AK8_softdrop_mass_gen;   //!

   TBranch        *b_deltaR_lak8jet;   //!

   TBranch        *b_deltaphi_METak8jet;   //!

   TBranch        *b_deltaphi_Vak8jet;   //!

   TBranch        *b_v_pt;   //!

   TBranch        *b_v_eta;   //!

   TBranch        *b_v_phi;   //!

   TBranch        *b_v_mt;   //!

   TBranch        *b_mass_lvj_type0;   //!

   TBranch        *b_mass_lvj_type2;   //!

   TBranch        *b_mass_lvj_run2;   //!

   TBranch        *b_nBTagJet_loose;   //!

   TBranch        *b_nBTagJet_medium;   //!

   TBranch        *b_nBTagJet_tight;   //!

   TBranch        *b_mass_leptonic_closerjet;   //!

   TBranch        *b_mass_ungroomedjet_closerjet;   //!

   TBranch        *b_AK8_closerjet_pt;   //!

   TBranch        *b_AK8_closerjet_eta;   //!

   TBranch        *b_AK8_closerjet_phi;   //!

   TBranch        *b_AK8_closerjet_e;   //!

   TBranch        *b_vbf_maxpt_j1_pt;   //!

   TBranch        *b_vbf_maxpt_j1_eta;   //!

   TBranch        *b_vbf_maxpt_j1_phi;   //!

   TBranch        *b_vbf_maxpt_j1_e;   //!

   TBranch        *b_vbf_maxpt_j1_bDiscriminatorCSV;   //!

   TBranch        *b_vbf_maxpt_j2_pt;   //!

   TBranch        *b_vbf_maxpt_j2_eta;   //!

   TBranch        *b_vbf_maxpt_j2_phi;   //!

   TBranch        *b_vbf_maxpt_j2_e;   //!

   TBranch        *b_vbf_maxpt_j2_bDiscriminatorCSV;   //!

   TBranch        *b_vbf_maxpt_jj_pt;   //!

   TBranch        *b_vbf_maxpt_jj_eta;   //!

   TBranch        *b_vbf_maxpt_jj_phi;   //!

   TBranch        *b_vbf_maxpt_jj_m;   //!



   ClassReadTree(TTree *tree);

   virtual ~ClassReadTree();

   

   

   

   virtual void     Init(TTree *tree);

   

   

   

};

ClassReadTree::~ClassReadTree()

{

   if (!fChain) return;

   delete fChain->GetCurrentFile();

}

void ClassReadTree::Init(TTree *tree)

{

   // The Init() function is called when the selector needs to initialize

   // a new tree or chain. Typically here the branch addresses and branch

   // pointers of the tree will be set.

   // It is normally not necessary to make changes to the generated

   // code, but the routine can be extended by the user if needed.

   // Init() will be called many times when running on PROOF

   // (once per file to be processed).



   // Set branch addresses and branch pointers

   if (!tree) return;

   fChain = tree;

   fCurrent = -1;

   fChain->SetMakeClass(1);



   fChain->SetBranchAddress("run", &run, &b_run);

   fChain->SetBranchAddress("event", &event, &b_event);

   fChain->SetBranchAddress("lumi", &lumi, &b_lumi);

   fChain->SetBranchAddress("njets", &njets, &b_njets);

   fChain->SetBranchAddress("nPV", &nPV, &b_nPV);

   fChain->SetBranchAddress("issignal", &issignal, &b_issignal);

   fChain->SetBranchAddress("wSampleWeight", &wSampleWeight, &b_wSampleWeight);

   fChain->SetBranchAddress("totalEventWeight", &totalEventWeight, &b_totalEventWeight);

   fChain->SetBranchAddress("eff_and_pu_Weight", &eff_and_pu_Weight, &b_eff_and_pu_Weight);

   fChain->SetBranchAddress("pfMET", &pfMET, &b_pfMET);

   fChain->SetBranchAddress("pfMET_Phi", &pfMET_Phi, &b_pfMET_Phi);

   fChain->SetBranchAddress("nu_pz_type0", &nu_pz_type0, &b_nu_pz_type0);

   fChain->SetBranchAddress("nu_pz_type2", &nu_pz_type2, &b_nu_pz_type2);

   fChain->SetBranchAddress("nu_pz_run2", &nu_pz_run2, &b_nu_pz_run2);

   fChain->SetBranchAddress("nu_pz_run2_oth", &nu_pz_run2_oth, &b_nu_pz_run2_oth);

   fChain->SetBranchAddress("nu_pz_run2_type", &nu_pz_run2_type, &b_nu_pz_run2_type);

   fChain->SetBranchAddress("nu_pz_isre", &nu_pz_isre, &b_nu_pz_isre);

   fChain->SetBranchAddress("l_pt", &l_pt, &b_l_pt);

   fChain->SetBranchAddress("l_eta", &l_eta, &b_l_eta);

   fChain->SetBranchAddress("l_phi", &l_phi, &b_l_phi);

   fChain->SetBranchAddress("l_e", &l_e, &b_l_e);

   fChain->SetBranchAddress("ungroomed_jet_pt", &ungroomed_jet_pt, &b_ungroomed_jet_pt);

   fChain->SetBranchAddress("ungroomed_jet_eta", &ungroomed_jet_eta, &b_ungroomed_jet_eta);

   fChain->SetBranchAddress("ungroomed_jet_phi", &ungroomed_jet_phi, &b_ungroomed_jet_phi);

   fChain->SetBranchAddress("ungroomed_jet_e", &ungroomed_jet_e, &b_ungroomed_jet_e);

   fChain->SetBranchAddress("jet_mass_pr", &jet_mass_pr, &b_jet_mass_pr);

   fChain->SetBranchAddress("jet_mass_so", &jet_mass_so, &b_jet_mass_so);

   fChain->SetBranchAddress("jet_mass_tr", &jet_mass_tr, &b_jet_mass_tr);

   fChain->SetBranchAddress("jet_mass_fi", &jet_mass_fi, &b_jet_mass_fi);

   fChain->SetBranchAddress("jet_tau2tau1", &jet_tau2tau1, &b_jet_tau2tau1);

   fChain->SetBranchAddress("ttb_ungroomed_jet_pt", &ttb_ungroomed_jet_pt, &b_ttb_ungroomed_jet_pt);

   fChain->SetBranchAddress("ttb_ungroomed_jet_eta", &ttb_ungroomed_jet_eta, &b_ttb_ungroomed_jet_eta);

   fChain->SetBranchAddress("ttb_ungroomed_jet_phi", &ttb_ungroomed_jet_phi, &b_ttb_ungroomed_jet_phi);

   fChain->SetBranchAddress("ttb_ungroomed_jet_e", &ttb_ungroomed_jet_e, &b_ttb_ungroomed_jet_e);

   fChain->SetBranchAddress("ttb_jet_mass_pr", &ttb_jet_mass_pr, &b_ttb_jet_mass_pr);

   fChain->SetBranchAddress("ttb_jet_mass_so", &ttb_jet_mass_so, &b_ttb_jet_mass_so);

   fChain->SetBranchAddress("ttb_jet_mass_tr", &ttb_jet_mass_tr, &b_ttb_jet_mass_tr);

   fChain->SetBranchAddress("ttb_jet_mass_fi", &ttb_jet_mass_fi, &b_ttb_jet_mass_fi);

   fChain->SetBranchAddress("ttb_jet_tau2tau1", &ttb_jet_tau2tau1, &b_ttb_jet_tau2tau1);

   fChain->SetBranchAddress("ttb_deltaeta_lak8jet", &ttb_deltaeta_lak8jet, &b_ttb_deltaeta_lak8jet);

   fChain->SetBranchAddress("W_pt_gen", &W_pt_gen, &b_W_pt_gen);

   fChain->SetBranchAddress("W_pz_gen", &W_pz_gen, &b_W_pz_gen);

   fChain->SetBranchAddress("W_rap_gen", &W_rap_gen, &b_W_rap_gen);

   fChain->SetBranchAddress("genGravMass", &genGravMass, &b_genGravMass);

   fChain->SetBranchAddress("nu_pz_gen", &nu_pz_gen, &b_nu_pz_gen);

   fChain->SetBranchAddress("nu_pt_gen", &nu_pt_gen, &b_nu_pt_gen);

   fChain->SetBranchAddress("nu_phi_gen", &nu_phi_gen, &b_nu_phi_gen);

   fChain->SetBranchAddress("nu_eta_gen", &nu_eta_gen, &b_nu_eta_gen);

   fChain->SetBranchAddress("hadW_pt_gen", &hadW_pt_gen, &b_hadW_pt_gen);

   fChain->SetBranchAddress("hadW_eta_gen", &hadW_eta_gen, &b_hadW_eta_gen);

   fChain->SetBranchAddress("hadW_phi_gen", &hadW_phi_gen, &b_hadW_phi_gen);

   fChain->SetBranchAddress("hadW_e_gen", &hadW_e_gen, &b_hadW_e_gen);

   fChain->SetBranchAddress("hadW_m_gen", &hadW_m_gen, &b_hadW_m_gen);

   fChain->SetBranchAddress("lepW_pt_gen", &lepW_pt_gen, &b_lepW_pt_gen);

   fChain->SetBranchAddress("lepW_eta_gen", &lepW_eta_gen, &b_lepW_eta_gen);

   fChain->SetBranchAddress("lepW_phi_gen", &lepW_phi_gen, &b_lepW_phi_gen);

   fChain->SetBranchAddress("lepW_e_gen", &lepW_e_gen, &b_lepW_e_gen);

   fChain->SetBranchAddress("lepW_m_gen", &lepW_m_gen, &b_lepW_m_gen);

   fChain->SetBranchAddress("AK8_pt_gen", &AK8_pt_gen, &b_AK8_pt_gen);

   fChain->SetBranchAddress("AK8_eta_gen", &AK8_eta_gen, &b_AK8_eta_gen);

   fChain->SetBranchAddress("AK8_phi_gen", &AK8_phi_gen, &b_AK8_phi_gen);

   fChain->SetBranchAddress("AK8_e_gen", &AK8_e_gen, &b_AK8_e_gen);

   fChain->SetBranchAddress("AK8_pruned_mass_gen", &AK8_pruned_mass_gen, &b_AK8_pruned_mass_gen);

   fChain->SetBranchAddress("AK8_softdrop_mass_gen", &AK8_softdrop_mass_gen, &b_AK8_softdrop_mass_gen);

   fChain->SetBranchAddress("deltaR_lak8jet", &deltaR_lak8jet, &b_deltaR_lak8jet);

   fChain->SetBranchAddress("deltaphi_METak8jet", &deltaphi_METak8jet, &b_deltaphi_METak8jet);

   fChain->SetBranchAddress("deltaphi_Vak8jet", &deltaphi_Vak8jet, &b_deltaphi_Vak8jet);

   fChain->SetBranchAddress("v_pt", &v_pt, &b_v_pt);

   fChain->SetBranchAddress("v_eta", &v_eta, &b_v_eta);

   fChain->SetBranchAddress("v_phi", &v_phi, &b_v_phi);

   fChain->SetBranchAddress("v_mt", &v_mt, &b_v_mt);

   fChain->SetBranchAddress("mass_lvj_type0", &mass_lvj_type0, &b_mass_lvj_type0);

   fChain->SetBranchAddress("mass_lvj_type2", &mass_lvj_type2, &b_mass_lvj_type2);

   fChain->SetBranchAddress("mass_lvj_run2", &mass_lvj_run2, &b_mass_lvj_run2);

   fChain->SetBranchAddress("nBTagJet_loose", &nBTagJet_loose, &b_nBTagJet_loose);

   fChain->SetBranchAddress("nBTagJet_medium", &nBTagJet_medium, &b_nBTagJet_medium);

   fChain->SetBranchAddress("nBTagJet_tight", &nBTagJet_tight, &b_nBTagJet_tight);

   fChain->SetBranchAddress("mass_leptonic_closerjet", &mass_leptonic_closerjet, &b_mass_leptonic_closerjet);

   fChain->SetBranchAddress("mass_ungroomedjet_closerjet", &mass_ungroomedjet_closerjet, &b_mass_ungroomedjet_closerjet);

   fChain->SetBranchAddress("AK8_closerjet_pt", &AK8_closerjet_pt, &b_AK8_closerjet_pt);

   fChain->SetBranchAddress("AK8_closerjet_eta", &AK8_closerjet_eta, &b_AK8_closerjet_eta);

   fChain->SetBranchAddress("AK8_closerjet_phi", &AK8_closerjet_phi, &b_AK8_closerjet_phi);

   fChain->SetBranchAddress("AK8_closerjet_e", &AK8_closerjet_e, &b_AK8_closerjet_e);

   fChain->SetBranchAddress("vbf_maxpt_j1_pt", &vbf_maxpt_j1_pt, &b_vbf_maxpt_j1_pt);

   fChain->SetBranchAddress("vbf_maxpt_j1_eta", &vbf_maxpt_j1_eta, &b_vbf_maxpt_j1_eta);

   fChain->SetBranchAddress("vbf_maxpt_j1_phi", &vbf_maxpt_j1_phi, &b_vbf_maxpt_j1_phi);

   fChain->SetBranchAddress("vbf_maxpt_j1_e", &vbf_maxpt_j1_e, &b_vbf_maxpt_j1_e);

   fChain->SetBranchAddress("vbf_maxpt_j1_bDiscriminatorCSV", &vbf_maxpt_j1_bDiscriminatorCSV, &b_vbf_maxpt_j1_bDiscriminatorCSV);

   fChain->SetBranchAddress("vbf_maxpt_j2_pt", &vbf_maxpt_j2_pt, &b_vbf_maxpt_j2_pt);

   fChain->SetBranchAddress("vbf_maxpt_j2_eta", &vbf_maxpt_j2_eta, &b_vbf_maxpt_j2_eta);

   fChain->SetBranchAddress("vbf_maxpt_j2_phi", &vbf_maxpt_j2_phi, &b_vbf_maxpt_j2_phi);

   fChain->SetBranchAddress("vbf_maxpt_j2_e", &vbf_maxpt_j2_e, &b_vbf_maxpt_j2_e);

   fChain->SetBranchAddress("vbf_maxpt_j2_bDiscriminatorCSV", &vbf_maxpt_j2_bDiscriminatorCSV, &b_vbf_maxpt_j2_bDiscriminatorCSV);

   fChain->SetBranchAddress("vbf_maxpt_jj_pt", &vbf_maxpt_jj_pt, &b_vbf_maxpt_jj_pt);

   fChain->SetBranchAddress("vbf_maxpt_jj_eta", &vbf_maxpt_jj_eta, &b_vbf_maxpt_jj_eta);

   fChain->SetBranchAddress("vbf_maxpt_jj_phi", &vbf_maxpt_jj_phi, &b_vbf_maxpt_jj_phi);

   fChain->SetBranchAddress("vbf_maxpt_jj_m", &vbf_maxpt_jj_m, &b_vbf_maxpt_jj_m);

   

}

ClassReadTree::ClassReadTree(TTree *tree)
{
	Init(tree);
}