#import sys
#sys.stdout = open('MasterReader.C', 'w')


print '#include<iostream>\n#include <TROOT.h>\n#include <TChain.h>\n#include <TFile.h>\n#include "TLorentzVector.h"\n#include<vector>\n#include "TTree.h"\nusing namespace std;\n\n'



print 'void MasterReader(){\n '




path1="/eos/uscms/store/user/bmahakud/LeptoQuarkSpring15/"
path2="/eos/uscms/store/user/awhitbe1/PHYS14productionV15/"

store_mc_sig="/uscms_data/d3/bmahakud/DevelopingMakeClassCode/TreePlotter/"
store_mc_bkg="/uscms_data/d3/bmahakud/DevelopingMakeClassCode/TreePlotter/"
store_data="/uscms_data/d3/bmahakud/DevelopingMakeClassCode/TreePlotter/"

list_mc_sig = ["PHYS14.GJets_HT-400to600_Tune4C_13TeV-madgraph-tauola_*_RA2AnalysisTree.root"]

list_mc_bkg = ["PHYS14.GJets_HT-400to600_Tune4C_13TeV-madgraph-tauola_*_RA2AnalysisTree.root"]

list_data = ["PHYS14.GJets_HT-400to600_Tune4C_13TeV-madgraph-tauola_*_RA2AnalysisTree.root"]


for a in range(0,len(list_mc_sig)):
    print 'TChain* t%i_mc_sig = new TChain("TreeMaker2/PreSelection");'%a
    print ('t%i_mc_sig->Add("%s%s");'%(a, store_mc_sig, list_mc_sig[a]))
    print 'ClassReadTree mc_sig_%i(t%i_mc_sig);'%(a, a)
    print 'for(int iEv_%i_mc_sig=0;iEv_%i_mc_sig < t%i_mc_sig->GetEntries();iEv_%i_mc_sig++){'%(a, a, a, a)
    print 't%i_mc_sig->GetEntry(iEv_%i_mc_sig);'%(a, a)    


    print '\n'
    print ' }'

    print '\n'

print '\n\n'



for a in range(0,len(list_mc_bkg)):
    print 'TChain* t%i_mc_bkg = new TChain("TreeMaker2/PreSelection");'%a
    print ('t%i_mc_bkg->Add("%s%s");'%(a, store_mc_bkg, list_mc_bkg[a]))
    print 'ClassReadTree mc_bkg_%i(t%i_mc_bkg);'%(a, a)
    print 'for(int iEv_%i_mc_bkg=0;iEv_%i_mc_bkg < t%i_mc_bkg->GetEntries();iEv_%i_mc_bkg++){'%(a, a, a, a)
    print 't%i_mc_bkg->GetEntry(iEv_%i_mc_bkg);'%(a, a)   


    print '\n'
    print ' }'


    print '\n'

print '\n\n'

for a in range(0,len(list_data)):
    print 'TChain* t%i_data = new TChain("TreeMaker2/PreSelection");'%a
    print ('t%i_data->Add("%s%s");'%(a, store_data, list_data[a]))
    print 'ClassReadTree mc_data_%i(t%i_mc_data);'%(a, a)
    print 'for(int iEv_%i_data=0;iEv_%i_data < t%i_data->GetEntries();iEv_%i_data++){'%(a, a, a, a)
    print 't%i_data->GetEntry(iEv_%i_data);'%(a, a)  


    print '\n'
    print ' }'

    print '\n'
   

print '\n\n'




"""
//for( int iEv = 0 ; iEv < t->GetEntries() ; iEv++){//
for( int iEv = 0 ; iEv < 1 ; iEv++){//
t->GetEntry(iEv);

cout<<"Photon size  : "<<G400.NVtx<<endl;
}//
"""


















print '\n\n}'


























