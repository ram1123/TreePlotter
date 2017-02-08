import ROOT
import re
import os
import sys
import gRootColorPalette

ROOT.gROOT.SetBatch(True)

ROOT.gStyle.SetOptStat('')  # Don't show the stat box


os.system('mkdir -p plots/')

path="/eos/uscms/store/user/lnujj/WpWm_aQGC_Ntuples_Ram/SecondStepOutput_2Feb2017/output_mu/"
#path="/uscms_data/d3/rasharma/aQGC_analysis/AnalysisFramework/SecondStep/CMSSW_8_0_11/src/WWAnalysisRun2/output/output_mu/"
#path="/uscms_data/d3/rasharma/aQGC_analysis/AnalysisFramework/SecondStep/CMSSW_8_0_11/src/WWAnalysisRun2/output/output_el/"

RootFiles=[
#		"WWTree_Signal_LL_mu.root", "WWTree_Signal_LT_mu.root", "WWTree_Signal_TT_mu.root", 
		"WWTree_Signal_LLpLTpTT_mu.root"
#		"WWTree_WW_excla_mu.root ",		"WWTree_WZ_excl_amcatnlo_mu.root ",		"WWTree_ZZ_excl_amcatnlo_mu.root ",
#		"WWTree_sch_mu.root ",
#		"WWTree_tWch_bara_mu.root ",		"WWTree_tWcha_mu.root ",
#		"WWTree_tch_bar_mu.root ",		"WWTree_tch_mu.root ",
#		"WWTree_DYJetsToLL_amcatnlo_ext1_mu.root ",
		,"WWTree_TTbar_powheg_mu.root "
#		,"WWTree_WJets_madgraph_mu.root"
#		,"WWTree_WJets_amcatnlo_mu.root"
#		"WWTree_WJets100a_mu.root ",		"WWTree_WJets1200a_mu.root ",		"WWTree_WJets200a_mu.root ",		"WWTree_WJets2500a_mu.root ",		"WWTree_WJets400a_mu.root ",		"WWTree_WJets600a_mu.root ",		"WWTree_WJets800ext1_mu.root "]
#RootFiles=["SM.root","FT0_minus2p5.root","FT0_plus2p5.root"
]

factor=[
	0.0035,
	0.3965,
	76.25,
	93.91
]

cutlist = open("CutList.dat", "r")

cut=""
count=0
for columns in ( raw.strip().split() for raw in cutlist ):
	if columns[0][:1] == "#": continue
        if count == 0:
                cut=str(columns[0])
        else:
                cut=" "+str(cut)+" && "+str(columns[0])
        count=count+1

#ROOT.gStyle.SetGridWidth(3)
#ROOT.gStyle.SetGridStyle(1)
#ROOT.gStyle.SetPalette(1)
ROOT.gStyle.SetTitleAlign(13)

c=ROOT.TCanvas("c","c",800,600)
c.SetRightMargin(0.15)      # right margin for canvas
c.SetGridx()
c.SetGridy()
c.SetLogz()
countf=0

#outputfile = ROOT.TFile("test.root","RECREATE")

for files in RootFiles:
    filename=re.sub('.root','',RootFiles[countf])
    #print "Filename = ",filename
    filename=re.sub('WWTree_','',filename)
    #Remove space in filename using .strip()
    filename=filename.strip()	
    #print "Filename = ",filename
    os.system('mkdir -p plots/'+filename)
    countv=0
    crs = open("variableList.dat", "r")
    for columns in ( raw.strip().split() for raw in crs ):
        if columns[0][:1] == "#":   continue
        #print columns[0],columns[1],columns[2],columns[3],columns[4],columns[5],columns[6]
        #print path+files
        f1=ROOT.TFile(path+files,"READ")
        T=f1.Get("otree")
        print "Total Entries = ",T.GetEntries()
        #print columns[0],columns[1],columns[2],columns[3],columns[4],columns[5],columns[6]

        titles=columns[0].split(':',1)

        h1=ROOT.TH2F("h1","",int(columns[1]),float(columns[2]),float(columns[3]),int(columns[4]),float(columns[5]),float(columns[6]))
        T.Draw(columns[0]+">>h1",cut,"colz")
	h1.Scale(factor[countf])
        h1.SetTitle(filename)
	#h1.CenterTitle()
        h1.GetXaxis().SetTitle(titles[1])
        h1.GetYaxis().SetTitle(titles[0])
        h1.GetZaxis().SetRangeUser(0,1);
	#print columns[0],cut
        c.Print("plots/"+"Scatter_"+filename+"_"+titles[0]+"_vs_"+titles[1]+".png")
        c.Print("plots/"+"Scatter_"+filename+"_"+titles[0]+"_vs_"+titles[1]+".pdf")
        #c.Write()
        c.Clear()
        countv=countv+1
    countf=countf+1
#outputfile.Write()
