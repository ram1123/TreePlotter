import ROOT
import re
import os
import sys
import gRootColorPalette

ROOT.gROOT.SetBatch(True)

ROOT.gStyle.SetOptStat('')  # Don't show the stat box


os.system('mkdir -p plots/')

path="/afs/cern.ch/user/r/rasharma/work/aQGC_Studies/SecondStep_WWTrees/CMSSW_8_0_11/src/BaconAnalyzer/WWAnalysisRun2/"

RootFiles=["OutPutRootFile_el.root"]
#RootFiles=["OutPutRootFile_el.root","OutPutRootFile_mu.root"]

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

c=ROOT.TCanvas("c","c",800,600)
c.SetRightMargin(0.15)      # right margin for canvas
c.SetGridx()
c.SetGridy()
c.SetLogz()
countf=0

#outputfile = ROOT.TFile("test.root","RECREATE")

for files in RootFiles:
    filename=re.sub('.root','',RootFiles[countf])
    filename=re.sub('WWTree_','',filename)
    os.system('mkdir -p plots/'+filename)
    countv=0
    crs = open("variableList.dat", "r")
    for columns in ( raw.strip().split() for raw in crs ):
        if columns[0][:1] == "#":   continue
	print "=======		PLOT DETAILS	==================\n"
	print len(columns)
	for list1 in columns:
		print list1,"\t",
	print "\n==================================================="
        #print columns[0],columns[1],columns[2],columns[3],columns[4],columns[5],columns[6],columns[7]
        #print path+files
        f1=ROOT.TFile(path+files,"READ")
        T=f1.Get("otree")
        #print T.GetEntries()
        #print columns[0],columns[1],columns[2],columns[3],columns[4],columns[5],columns[6]

	if len(columns) == 8:
		titles=columns[7].split(':',1)
		print titles
	else:
        	titles=columns[0].split(':',1)
	#titles=["assymetry jet #eta (leading)","assymetry jet #eta (sub-leading)"]

        h1=ROOT.TH2F("h1","",int(columns[1]),float(columns[2]),float(columns[3]),int(columns[4]),float(columns[5]),float(columns[6]))
        #h1.SetTitle(filename)
        h1.GetZaxis().SetRangeUser(0,10);
	#re.sub('[!@#$]', '', line)
        h1.GetXaxis().SetTitle(re.sub('["$]',' ',titles[1]))
        h1.GetYaxis().SetTitle(re.sub('["$]',' ',titles[0]))
        h1.GetYaxis().SetTitleOffset(1.2)
        T.Draw(columns[0]+">>h1",cut,"colz")
        


	t1=''.join(e for e in titles[0] if e.isalnum())
	t2=''.join(e for e in titles[1] if e.isalnum())

        c.Print("plots/"+filename+"/Scatter_"+filename+"_"+t1+"_vs_"+t2+".png")
        c.Print("plots/"+filename+"/Scatter_"+filename+"_"+t1+"_vs_"+t2+".pdf")
        c.Print("plots/"+filename+"/Scatter_"+filename+"_"+t1+"_vs_"+t2+".C")
        #c.Write()
        c.Clear()
        countv=countv+1
    countf=countf+1
#outputfile.Write()
