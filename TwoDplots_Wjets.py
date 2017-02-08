import ROOT
import re
import os
import sys
import gRootColorPalette

#ROOT.gROOT.SetBatch(True)

ROOT.gStyle.SetOptStat(0)  # Don't show the stat box

os.system('mkdir -p plots/')

path="/eos/uscms/store/user/lnujj/WpWm_aQGC_Ntuples_Ram/SecondStepOutput_2Feb2017/output_mu/"

RootFiles=[
		"WWTree_WJets100a_mu.root ",		"WWTree_WJets1200a_mu.root ",		"WWTree_WJets200a_mu.root ",		"WWTree_WJets2500a_mu.root ",		"WWTree_WJets400a_mu.root ",		"WWTree_WJets600a_mu.root ",		"WWTree_WJets800ext1_mu.root "]

factor=[
	0.755,	0.0086,
	0.404,	0.0005,
	0.2808,	0.0287,
	0.0395
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

hnew=ROOT.TH2F()
countv=0
crs = open("variableList.dat", "r")
for columns in ( raw.strip().split() for raw in crs ):
    if columns[0][:1] == "#":   continue
    titles=columns[0].split(':',1)
    h1=ROOT.TH2F("h1","",int(columns[1]),float(columns[2]),float(columns[3]),int(columns[4]),float(columns[5]),float(columns[6]))
    h1.GetZaxis().SetRangeUser(0,10);
    h1.GetXaxis().SetTitle(titles[1])
    h1.GetYaxis().SetTitle(titles[0])
    for files in RootFiles:
    	filename=re.sub('.root','',RootFiles[countf])
	filename=re.sub('WWTree_','',filename)
	filename=filename.strip()	
    	h1.SetTitle(filename)
    	f1=ROOT.TFile(path+files,"READ")
    	T=f1.Get("otree")
    	print "Total Entries = ",T.GetEntries()
    	T.Draw(columns[0]+">>h1",cut,"colz")
    	h1.Scale(factor[countf])
	if countf==0:
    		hnew = h1.Clone("hnew");
    		print "made new histo......."
	else:
    		print "Adding new histo......."
    		hnew.Add(h1);
	countf=countf+1
    c.Print("plots/"+filename+"/Scatter_"+filename+"_"+titles[0]+"_vs_"+titles[1]+".png")
    c.Print("plots/"+filename+"/Scatter_"+filename+"_"+titles[0]+"_vs_"+titles[1]+".pdf")
    countv=countv+1
