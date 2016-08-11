import ROOT
import re
import os
import sys

ROOT.gROOT.SetBatch(True)

ROOT.gStyle.SetOptStat('')  # Don't show the stat box


os.system('mkdir -p plots/')

path="/home/ramkrishna/cernbox/aQGC_Studies/SecondStep_Ntuples/NoBtagInPreSelection_4August2016/output_mu/"

RootFiles=["WWTree_DYJets.root","WWTree_data_golden.root","WWTree_TTbar_powheg.root","WWTree_WZ_excl.root","WWTree_ZZ_excl.root","WWTree_WJets.root","WWTree_WW_excl.root","WWTree_sch.root","WWTree_tWch.root","WWTree_tWch_bar.root","WWTree_tch_bar.root"]


#ROOT.gStyle.SetGridWidth(3)
#ROOT.gStyle.SetGridStyle(1)
ROOT.gStyle.SetPalette(1)

c=ROOT.TCanvas("c","c",800,600)
c.SetRightMargin(0.15)      # right margin for canvas
c.SetGridx()
c.SetGridy()
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
        #print columns[0],columns[1],columns[2],columns[3],columns[4],columns[5],columns[6]
        #print path+files
        f1=ROOT.TFile(path+files,"READ")
        T=f1.Get("otree")
        #print T.GetEntries()
        #print columns[0],columns[1],columns[2],columns[3],columns[4],columns[5],columns[6]

        titles=columns[0].split(':',1)

        h1=ROOT.TH2F("h1","",int(columns[1]),float(columns[2]),float(columns[3]),int(columns[4]),float(columns[5]),float(columns[6]))
        h1.SetTitle(filename)
        #h1=ROOT.TH2F("h1",titles[0]+" vs "+titles[1],int(columns[1]),float(columns[2]),float(columns[3]),int(columns[4]),float(columns[5]),float(columns[6]))
        h1.GetXaxis().SetTitle(titles[1])
        h1.GetYaxis().SetTitle(titles[0])
        T.Draw(columns[0]+">>h1","","colz")
        


        c.Print("plots/"+filename+"/Scatter_"+filename+"_"+titles[0]+"_vs_"+titles[1]+".png")
        c.Print("plots/"+filename+"/Scatter_"+filename+"_"+titles[0]+"_vs_"+titles[1]+".pdf")
        c.Print("plots/"+filename+"/Scatter_"+filename+"_"+titles[0]+"_vs_"+titles[1]+".C")
        #c.Write()
        c.Clear()
        countv=countv+1
    countf=countf+1
#outputfile.Write()
