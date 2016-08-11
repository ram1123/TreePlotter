import ROOT
import re
ROOT.gROOT.SetBatch(True)

path="/home/ramkrishna/cernbox/aQGC_Studies/SecondStep_Ntuples/NoBtagInPreSelection_4August2016/output_mu/"

RootFiles=["WWTree_TTbar_powheg_1.root","WWTree_DYJets.root"]

c=ROOT.TCanvas("c","c",800,600)

countf=0

for files in RootFiles:
    countv=0
    crs = open("variableList.dat", "r")
    for columns in ( raw.strip().split() for raw in crs ):
        if columns[0][:1] == "#":
            continue
        #print columns[0],columns[1],columns[2],columns[3],columns[4],columns[5],columns[6]
        #print path+files
        f1=ROOT.TFile(path+files)
        T=f1.Get("otree")
        #print T.GetEntries()
        #print columns[0],columns[1],columns[2],columns[3],columns[4],columns[5],columns[6]
        titles=columns[0].split(':',1)

        h1=ROOT.TH2F("h1","",int(columns[1]),float(columns[2]),float(columns[3]),int(columns[4]),float(columns[5]),float(columns[6]))
        #h1=ROOT.TH2F("h1",titles[0]+" vs "+titles[1],int(columns[1]),float(columns[2]),float(columns[3]),int(columns[4]),float(columns[5]),float(columns[6]))
        h1.GetXaxis().SetTitle(titles[1])
        h1.GetYaxis().SetTitle(titles[0])
        T.Draw(columns[0]+">>h1","","colz")
        

        filename=re.sub('.root','',RootFiles[countf])
        filename=re.sub('WWTree_','',filename)


        c.Print("Scatter_"+filename+"_"+titles[0]+"_vs_"+titles[1]+".png")
        c.Clear()
        countv=countv+1
    countf=countf+1
