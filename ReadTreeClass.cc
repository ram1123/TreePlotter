#include<iostream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TLorentzVector.h"
#include<vector>
#include "TTree.h"
using namespace std;

class ReadTreeClass{


public:

   TTree* fChain;

   UInt_t          RunNum;
   UInt_t          LumiBlockNum;
   UInt_t          EvtNum;
   Int_t           NVtx;
   Int_t           isoElectronTracks;
   Int_t           isoMuonTracks;
   Int_t           isoPionTracks;
   Int_t           Leptons;
   Int_t           TagLeptonHighPT;
   Int_t           NumPhotons;
   Int_t           METFilters;
   Int_t           CSCTightHaloFilter;
   Int_t           HBHENoiseFilter;
   Int_t           EcalDeadCellTriggerPrimitiveFilter;
   Int_t           NJets;
   Int_t           BTags;
   Int_t           ZNum;
   Int_t           NJetsclean;
   Int_t           BTagsclean;
   Float_t         Weight;
   Float_t         HT;
   Float_t         MHT;
   Float_t         MHT_Phi;
   Float_t         DeltaPhi1;
   Float_t         DeltaPhi2;
   Float_t         DeltaPhi3;
   Float_t         minDeltaPhiN;
   Float_t         DeltaPhiN1;
   Float_t         DeltaPhiN2;
   Float_t         DeltaPhiN3;
   Float_t         METPt;
   Float_t         METPhi;
   Float_t         HTclean;
   Float_t         DeltaPhi1clean;
   Float_t         DeltaPhi2clean;
   Float_t         DeltaPhi3clean;
   Float_t         MHTclean;
   Float_t         minDeltaPhiNclean;
   Float_t         METPtclean;
   Float_t         rho;
   UChar_t         JetID;
   vector<int>     *genParticles_PDGid;
   vector<int>     *PassTrigger;
   vector<int>     *MuonCharge;
   vector<int>     *ElectronCharge;
   vector<int>     *ak4Jets_chargedHadMult;
   vector<int>     *ak4Jets_neutralHadMult;
   vector<int>     *ak4Jets_photonMult;
   vector<int>     *ak4Jets_flavor;
   vector<double>  *photon_isEB;
   vector<double>  *photon_genMatched;
   vector<double>  *photon_hadTowOverEM;
   vector<double>  *photon_hasPixelSeed;
   vector<double>  *photon_passElectronVeto;
   vector<double>  *photon_pfChargedIso;
   vector<double>  *photon_pfChargedIsoRhoCorr;
   vector<double>  *photon_pfGammaIso;
   vector<double>  *photon_pfGammaIsoRhoCorr;
   vector<double>  *photon_pfNeutralIso;
   vector<double>  *photon_pfNeutralIsoRhoCorr;
   vector<double>  *photon_sigmaIetaIeta;
   vector<double>  *ak4Jets_CSVdisc;
   vector<double>  *ak4Jets_MVAdisc;
   vector<double>  *ak4Jets_chargeHadEfrac;
   vector<double>  *ak4Jets_neutralHadEfrac;
   vector<double>  *ak4Jets_photonEfrac;
   vector<string>  *TriggerNames;
   vector<TLorentzVector> *genParticles;
   vector<TLorentzVector> *bestPhoton;
   vector<TLorentzVector> *photonCands;
   vector<TLorentzVector> *Zp4;
   vector<TLorentzVector> *Muons;
   vector<TLorentzVector> *Electrons;
   vector<TLorentzVector> *ak4Jets;
   vector<TLorentzVector> *ak4JetsRaw;




ReadTreeClass(TTree* t_){
fChain=t_;

   genParticles_PDGid = 0;
   PassTrigger = 0;
   MuonCharge = 0;
   ElectronCharge = 0;
   ak4Jets_chargedHadMult = 0;
   ak4Jets_neutralHadMult = 0;
   ak4Jets_photonMult = 0;
   ak4Jets_flavor = 0;
   photon_isEB = 0;
   photon_genMatched = 0;
   photon_hadTowOverEM = 0;
   photon_hasPixelSeed = 0;
   photon_passElectronVeto = 0;
   photon_pfChargedIso = 0;
   photon_pfChargedIsoRhoCorr = 0;
   photon_pfGammaIso = 0;
   photon_pfGammaIsoRhoCorr = 0;
   photon_pfNeutralIso = 0;
   photon_pfNeutralIsoRhoCorr = 0;
   photon_sigmaIetaIeta = 0;
   ak4Jets_CSVdisc = 0;
   ak4Jets_MVAdisc = 0;
   ak4Jets_chargeHadEfrac = 0;
   ak4Jets_neutralHadEfrac = 0;
   ak4Jets_photonEfrac = 0;
   TriggerNames = 0;
   genParticles = 0;
   bestPhoton = 0;
   photonCands = 0;
   Zp4 = 0;
   Muons = 0;
   Electrons = 0;
   ak4Jets = 0;
   ak4JetsRaw = 0;


   fChain->SetBranchAddress("RunNum", &RunNum);
   fChain->SetBranchAddress("LumiBlockNum", &LumiBlockNum);
   fChain->SetBranchAddress("EvtNum", &EvtNum);
   fChain->SetBranchAddress("NVtx", &NVtx);
   fChain->SetBranchAddress("isoElectronTracks", &isoElectronTracks);
   fChain->SetBranchAddress("isoMuonTracks", &isoMuonTracks);
   fChain->SetBranchAddress("isoPionTracks", &isoPionTracks);
   fChain->SetBranchAddress("Leptons", &Leptons);
   fChain->SetBranchAddress("TagLeptonHighPT", &TagLeptonHighPT);
   fChain->SetBranchAddress("NumPhotons", &NumPhotons);
   fChain->SetBranchAddress("METFilters", &METFilters);
   fChain->SetBranchAddress("CSCTightHaloFilter", &CSCTightHaloFilter);
   fChain->SetBranchAddress("HBHENoiseFilter", &HBHENoiseFilter);
   fChain->SetBranchAddress("EcalDeadCellTriggerPrimitiveFilter", &EcalDeadCellTriggerPrimitiveFilter);
   fChain->SetBranchAddress("NJets", &NJets);
   fChain->SetBranchAddress("BTags", &BTags);
   fChain->SetBranchAddress("ZNum", &ZNum);
   fChain->SetBranchAddress("NJetsclean", &NJetsclean);
   fChain->SetBranchAddress("BTagsclean", &BTagsclean);
   fChain->SetBranchAddress("Weight", &Weight);
   fChain->SetBranchAddress("HT", &HT);
   fChain->SetBranchAddress("MHT", &MHT);
   fChain->SetBranchAddress("MHT_Phi", &MHT_Phi);
   fChain->SetBranchAddress("DeltaPhi1", &DeltaPhi1);
   fChain->SetBranchAddress("DeltaPhi2", &DeltaPhi2);
   fChain->SetBranchAddress("DeltaPhi3", &DeltaPhi3);
   fChain->SetBranchAddress("minDeltaPhiN", &minDeltaPhiN);
   fChain->SetBranchAddress("DeltaPhiN1", &DeltaPhiN1);
   fChain->SetBranchAddress("DeltaPhiN2", &DeltaPhiN2);
   fChain->SetBranchAddress("DeltaPhiN3", &DeltaPhiN3);
   fChain->SetBranchAddress("METPt", &METPt);
   fChain->SetBranchAddress("METPhi", &METPhi);
   fChain->SetBranchAddress("HTclean", &HTclean);
   fChain->SetBranchAddress("DeltaPhi1clean", &DeltaPhi1clean);
   fChain->SetBranchAddress("DeltaPhi2clean", &DeltaPhi2clean);
   fChain->SetBranchAddress("DeltaPhi3clean", &DeltaPhi3clean);
   fChain->SetBranchAddress("MHTclean", &MHTclean);
   fChain->SetBranchAddress("minDeltaPhiNclean", &minDeltaPhiNclean);
   fChain->SetBranchAddress("METPtclean", &METPtclean);
   fChain->SetBranchAddress("rho", &rho);
   fChain->SetBranchAddress("JetID", &JetID);
   fChain->SetBranchAddress("genParticles_PDGid", &genParticles_PDGid);
   fChain->SetBranchAddress("PassTrigger", &PassTrigger);
   fChain->SetBranchAddress("MuonCharge", &MuonCharge);
   fChain->SetBranchAddress("ElectronCharge", &ElectronCharge);
   fChain->SetBranchAddress("ak4Jets_chargedHadMult", &ak4Jets_chargedHadMult);
   fChain->SetBranchAddress("ak4Jets_neutralHadMult", &ak4Jets_neutralHadMult);
   fChain->SetBranchAddress("ak4Jets_photonMult", &ak4Jets_photonMult);
   fChain->SetBranchAddress("ak4Jets_flavor", &ak4Jets_flavor);
   fChain->SetBranchAddress("photon_isEB", &photon_isEB);
   fChain->SetBranchAddress("photon_genMatched", &photon_genMatched);
   fChain->SetBranchAddress("photon_hadTowOverEM", &photon_hadTowOverEM);
   fChain->SetBranchAddress("photon_hasPixelSeed", &photon_hasPixelSeed);
   fChain->SetBranchAddress("photon_passElectronVeto", &photon_passElectronVeto);
   fChain->SetBranchAddress("photon_pfChargedIso", &photon_pfChargedIso);
   fChain->SetBranchAddress("photon_pfChargedIsoRhoCorr", &photon_pfChargedIsoRhoCorr);
   fChain->SetBranchAddress("photon_pfGammaIso", &photon_pfGammaIso);
   fChain->SetBranchAddress("photon_pfGammaIsoRhoCorr", &photon_pfGammaIsoRhoCorr);
   fChain->SetBranchAddress("photon_pfNeutralIso", &photon_pfNeutralIso);
   fChain->SetBranchAddress("photon_pfNeutralIsoRhoCorr", &photon_pfNeutralIsoRhoCorr);
   fChain->SetBranchAddress("photon_sigmaIetaIeta", &photon_sigmaIetaIeta);
   fChain->SetBranchAddress("ak4Jets_CSVdisc", &ak4Jets_CSVdisc);
   fChain->SetBranchAddress("ak4Jets_MVAdisc", &ak4Jets_MVAdisc);
   fChain->SetBranchAddress("ak4Jets_chargeHadEfrac", &ak4Jets_chargeHadEfrac);
   fChain->SetBranchAddress("ak4Jets_neutralHadEfrac", &ak4Jets_neutralHadEfrac);
   fChain->SetBranchAddress("ak4Jets_photonEfrac", &ak4Jets_photonEfrac);
   fChain->SetBranchAddress("TriggerNames", &TriggerNames);
   fChain->SetBranchAddress("genParticles", &genParticles);
   fChain->SetBranchAddress("bestPhoton", &bestPhoton);
   fChain->SetBranchAddress("photonCands", &photonCands);
   fChain->SetBranchAddress("Zp4", &Zp4);
   fChain->SetBranchAddress("Muons", &Muons);
   fChain->SetBranchAddress("Electrons", &Electrons);
   fChain->SetBranchAddress("ak4Jets", &ak4Jets);
   fChain->SetBranchAddress("ak4JetsRaw", &ak4JetsRaw);














};



















};



