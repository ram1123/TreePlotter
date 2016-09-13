import re
import sys 
import os
import ROOT
from ROOT import TFile, TH1F, TObject, TLatex

ROOT.gROOT.SetBatch(True)  # This will prevent histogram to show
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetOptFit(0)

RootFile1 = TFile("/home/ramkrishna/cernbox/aQGC_Studies/SecondStep_Ntuples/WW_Sample_NoVBFjetSelection_13Sept2016/output/output_el/WWTree_WJets.root","read")
RootFile2 = TFile("/home/ramkrishna/cernbox/aQGC_Studies/SecondStep_Ntuples/NoBtagInPreSelection_4August2016/output_el/WWTree_WJets.root","read")

t1 = RootFile1.Get("otree")
t2 = RootFile2.Get("otree")

c=ROOT.TCanvas("c","c",800,600)
c.SetRightMargin(0.05)      # right margin for canvas
c.SetLeftMargin(0.10)      # right margin for canvas
c.SetGridx()
c.SetGridy()


Variables = [
	["AK4_jetjet_mass", "M_{W#rightarrow jj}", 100, 0, 1500],
	["l_pt"	, "", 	100, 0, 500],
	["pfMET", "",	100, 0, 500],
	["v_mt"	, "",	100, 0, 300]
	]

for var in range(0,len(Variables)):
	print "Plot: ",Variables[var]

	if Variables[var][1] == "":
		Variables[var][1] = Variables[var][0]

	h1=TH1F("h1", "", Variables[var][2], Variables[var][3], Variables[var][4])
	h2=TH1F("h2", "", Variables[var][2], Variables[var][3], Variables[var][4])

	v1 = Variables[var][0]+">>h1"
	v2 = Variables[var][0]+">>h2"

	t1.Draw(v1)
	t2.Draw(v2,"isVBFJet_NoB==1")

	h1.Scale(1./h1.Integral())
	h2.Scale(1./h2.Integral())
	
	h1.SetLineColor(1)
	h2.SetLineColor(2)
	
	h1.GetYaxis().SetTitle("Frequency (normalized to unity)")
	h1.GetXaxis().SetTitle(Variables[var][1])
	h1.GetYaxis().SetTitleOffset(1.3)
	
	h1.Draw()
	h2.Draw("sames")
	
	leg = ROOT.TLegend(0.7,0.7,0.9,0.9,"Wjet Sample")
	leg.AddEntry(h1,"WW","l")
	leg.AddEntry(h2,"WW with VBF","l")
	
	leg.Draw("sames")
	
	c.SaveAs(Variables[var][0]+".pdf");
	c.SaveAs(Variables[var][0]+".png");

	h1.Delete()
	h2.Delete()
	c.Clear()
	print ""
