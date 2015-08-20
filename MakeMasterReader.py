import sys
sys.stdout = open('MasterReader.C','w')

############    include Header files    ##########################
print '#include<iostream>\n#include <TROOT.h>\n#include <TChain.h>\n#include <TFile.h>\n#include "TLorentzVector.h"\n#include<vector>\n#include "TTree.h"\n#include "ClassReadTree.cc"\nusing namespace std;\n\n'



print 'void MasterReader(){\n '

############    Start:: Reading the input file where variables stored    ##########################

def getVarFromFile(filename):
    import imp
    f = open(filename)
    global data
    data = imp.load_source('data', '', f)
    f.close()

getVarFromFile('InputDetails.dat')

############    END:: Reading the input file where variables stored    ##########################


############ START:: Setting Bin, Min and Max       ###########################
print 'int Bin[%s] = {'%(len(data.varList)/4),
for a in range(0,len(data.varList)/4):
    print data.varList[a*4+1],
    if a==((len(data.varList)/4)-1):
        print '};'
    else:
        print ',',

print 'int Min[%i] = {'%(len(data.varList)/4),
for a in range(0,len(data.varList)/4):
    print data.varList[a*4+2],
    if a==((len(data.varList)/4)-1):
        print '};'
    else:
        print ',',

print 'int Max[%i] = {'%(len(data.varList)/4),
for a in range(0,len(data.varList)/4):
    print data.varList[a*4+3],
    if a==((len(data.varList)/4)-1):
        print '};\n'
    else:
        print ',',

############ END:: Setting Bin, Min and Max       ###########################
#for a in range(0,3):
#    for b in range(0,3):
#        print "test = ",a+b+a*2
#
########## Define histogram for sig mc  ########################
print "\tTH1F** SigHist = new TH1F*[%i];"%(len(data.list_mc_sig)*len(data.varList)/4)

print "\tfor(int i=0; i<%i;i++){"%(len(data.list_mc_sig)*len(data.varList)/4)
print '\t\tSigHist[i] = new TH1F(Form("SigHist%i",i),"",Bin[i],Min[i],Max[i]);'
print '\t\tSigHist[i]->SetLineColor(1);\n\t}\n'
#print '\t\tSigHist[i]->SetLineColor(2i+1);\n\t}\n'

########## Define histogram for bkg mc  ########################
print "\tTH1F** BkgHist = new TH1F*[%i];"%(len(data.list_mc_bkg)*len(data.varList)/4)

print "\tfor(int i=0; i<%i;i++){"%(len(data.list_mc_bkg)*len(data.varList)/4)
print '\t\tBkgHist[i] = new TH1F(Form("BkgHist%i",i),"",Bin[i],Min[i],Max[i]);'
print '\t\tBkgHist[i]->SetLineColor(2);\n\t}\n'
#print '\t\tBkgHist[i]->SetLineColor(2*(2*(i+1)));\n\t}\n'

########## Define histogram for data mc  ########################
print "\tTH1F** DataHist = new TH1F*[%i];"%(len(data.list_data)*len(data.varList)/4)

print "\tfor(int i=0; i<%i;i++){"%(len(data.list_data)*len(data.varList)/4)
print '\t\tDataHist[i] = new TH1F(Form("DataHist%i",i),"",Bin[i],Min[i],Max[i]);'
print '\t\tDataHist[i]->SetLineColor(3);\n\t}\n'
#print '\t\tDataHist[i]->SetLineColor(2*(2*i+1));\n\t}\n'



for a in range(0,len(data.list_mc_sig)):
    print '\tTChain* t%i_mc_sig = new TChain("%s");'% (a, data.treeName)
    print '\t\tt%i_mc_sig->Add("%s%s");'%(a, data.store_mc_sig, data.list_mc_sig[a])
    print '\t\tClassReadTree mc_sig_%i(t%i_mc_sig);'%(a, a)
    print '\t\tfor(int iEv_%i_mc_sig=0;iEv_%i_mc_sig < t%i_mc_sig->GetEntries();iEv_%i_mc_sig++){'%(a, a, a, a)
    print '\t\t\tt%i_mc_sig->GetEntry(iEv_%i_mc_sig);'%(a, a)    
    for b in range(0, len(data.varList)/4):
        print '\t\t\tSigHist[%i]->Fill(mc_sig_0.%s);'%(a+b+a*((len(data.varList)/4)-1), data.varList[b*4])
    print '\t\t}'
    print '\n'

for a in range(0,len(data.list_mc_bkg)):
    print '\tTChain* t%i_mc_bkg = new TChain("%s");'%(a, data.treeName)
    print '\t\tt%i_mc_bkg->Add("%s%s");'%(a, data.store_mc_bkg, data.list_mc_bkg[a])
    print '\t\tClassReadTree mc_bkg_%i(t%i_mc_bkg);'%(a, a)
    print '\t\tfor(int iEv_%i_mc_bkg=0;iEv_%i_mc_bkg < t%i_mc_bkg->GetEntries();iEv_%i_mc_bkg++){'%(a, a, a, a)
    print '\t\t\tt%i_mc_bkg->GetEntry(iEv_%i_mc_bkg);'%(a, a)   
    for b in range(0, len(data.varList)/4):
        print '\t\t\tBkgHist[%i]->Fill(mc_bkg_0.%s);'%(a+b+a*((len(data.varList)/4)-1), data.varList[b*4])
    print '\t\t}'
    print '\n'

for a in range(0,len(data.list_data)):
    print '\tTChain* t%i_data = new TChain("%s");'%(a, data.treeName)
    print '\t\tt%i_data->Add("%s%s");'%(a, data.store_data, data.list_data[a])
    print '\t\tClassReadTree mc_data_%i(t%i_data);'%(a, a)
    print '\t\tfor(int iEv_%i_data=0;iEv_%i_data < t%i_data->GetEntries();iEv_%i_data++){'%(a, a, a, a)
    print '\t\t\tt%i_data->GetEntry(iEv_%i_data);'%(a, a)  
    for b in range(0, len(data.varList)/4):
        print '\t\t\tDataHist[%i]->Fill(mc_data_0.%s);'%(a+b+a*((len(data.varList)/4)-1), data.varList[b*4])
    print '\t\t}'
    print '\n'

print '\tTCanvas * c1 = new TCanvas("c1","",1);\n'
print '\tTLegend *leg = new TLegend(0.70,0.80,0.85,0.90,NULL,"brNDC");\n'
print 'double yMax=0.;\ndouble HistMax;'
for a in range(0,len(data.list_mc_sig)*len(data.varList)/4):
    print '\tSigHist[%i]->Scale(1/SigHist[%i]->Integral());'%(a, a)
    print '\tHistMax = SigHist[%i]->GetMaximum()*1.15;'%a
    print '\tSigHist[%i]->SetMaximum(TMath::Max(HistMax,yMax));'%a
    print '\tleg->AddEntry(SigHist[%i],"Signal","l");'%a
    print '\tyMax=HistMax;'
    print '\tSigHist[%i]->Draw();'%a
    print '\tBkgHist[%i]->Scale(1/BkgHist[%i]->Integral());'%(a, a)
    print '\tHistMax = BkgHist[%i]->GetMaximum()*1.15;'%a
    print '\tSigHist[%i]->SetMaximum(TMath::Max(HistMax,yMax));'%a
    print '\tleg->AddEntry(BkgHist[%i],"Bkg","l");'%a
    print '\tyMax=HistMax;'
    print '\tBkgHist[%i]->Draw("same");'%a
    print '\tDataHist[%i]->Scale(1/DataHist[%i]->Integral());'%(a, a)
    print '\tDataHist[%i]->Sumw2();'%a
    print '\tHistMax = DataHist[%i]->GetMaximum()*1.15;'%a
    print '\tSigHist[%i]->SetMaximum(TMath::Max(HistMax,yMax));'%a
    print '\tleg->AddEntry(DataHist[%i],"Data","l");'%a
    print '\tyMax=HistMax;'
    print '\tDataHist[%i]->Draw("same");'%a
    print '\tleg->Draw("same");'
    print '\tc1->SaveAs("%s.pdf");'%data.varList[a*4]
    print '\tc1->Clear();'
print '\n\n}'
