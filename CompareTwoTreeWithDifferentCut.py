import re
import sys 
import os
import ROOT
from ROOT import TFile, TH1F, TObject, TLatex

ROOT.gROOT.SetBatch(True)  # This will prevent histogram to show
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetOptFit(0)

Path1 = "/home/ramkrishna/cernbox/aQGC_Studies/SecondStep_Ntuples/WW_Sample_NoVBFjetSelection_13Sept2016/output/output_el/"
Path2 = "/home/ramkrishna/cernbox/aQGC_Studies/SecondStep_Ntuples/NoBtagInPreSelection_4August2016/output_el/"

RootFiles = [
	["WWTree_WJets100.root", "WWTree_WJets100.root",100,0,500],
	["WWTree_WJets200.root", "WWTree_WJets200.root",100,0,1000],
	["WWTree_WJets1200.root", "WWTree_WJets1200.root"],
	["WWTree_WJets2500.root", "WWTree_WJets2500.root"],
	["WWTree_WJets400.root", "WWTree_WJets400.root",100,0,1500],
	["WWTree_WJets600bis.root", "WWTree_WJets600bis.root",100,0,2000],
	["WWTree_WJets800.root", "WWTree_WJets800.root",100,0,2500]
	]

Variables = [
	["AK4_jetjet_mass", "M_{W#rightarrow jj}", 100, 0, 4500]
	#,["l_pt"	, "", 	100, 0, 500]
	#,["pfMET", "",	100, 0, 500]
	#,["v_mt"	, "",	100, 0, 300]
	]

if Path2 = "":
	Path2 = Path1

c=ROOT.TCanvas("c","c",800,600)
c.SetRightMargin(0.05)      # right margin for canvas
c.SetLeftMargin(0.10)      # right margin for canvas
c.SetGridx()
c.SetGridy()

for InputRootFile in RootFiles:
	#print "Input Root File: ",InputRootFile
	#print Path2+InputRootFile[1]
	OutPutFN = re.sub('.root', '', InputRootFile[0])
	OutPutFN = re.sub('WWTree_', '', OutPutFN)

	RootFile1 = TFile(Path1+InputRootFile[0],"read")
	RootFile2 = TFile(Path2+InputRootFile[0],"read")

	t1 = RootFile1.Get("otree")
	t2 = RootFile2.Get("otree")
	
	count = 0
	for var in Variables:
		print "Plot: ",var
	
		if var[1] == "":
			var[1] = var[0]
	
		if len(InputRootFile) == 5:
			h1=TH1F("h1", "", InputRootFile[2], InputRootFile[3], InputRootFile[4])
			h2=TH1F("h2", "", InputRootFile[2], InputRootFile[3], InputRootFile[4])
		else:
			h1=TH1F("h1", "", var[2], var[3], var[4])
			h2=TH1F("h2", "", var[2], var[3], var[4])

		v1 = var[0]+">>h1"
		v2 = var[0]+">>h2"
	
		t1.Draw(v1)
		t2.Draw(v2,"isVBFJet_NoB==1")
	
		h1.Scale(1./h1.Integral())
		h2.Scale(1./h2.Integral())

		ymax = max(h1.GetMaximum(),h2.GetMaximum())

		h1.SetMaximum(ymax*1.1)
		
		h1.SetLineColor(1)
		h2.SetLineColor(2)
		
		h1.GetYaxis().SetTitle("Frequency (normalized to unity)")
		h1.GetXaxis().SetTitle(var[1])
		h1.GetYaxis().SetTitleOffset(1.3)
		
		h1.Draw()
		h2.Draw("sames")

		print h1.GetMean()

		leg = ROOT.TLegend(0.7,0.7,0.9,0.9,OutPutFN)
		leg.AddEntry(h1,"WW","l")
		leg.AddEntry(h2,"WW with VBF","l")
		
		leg.Draw("sames")

		txt1 = TLatex();  txt1.SetTextSize(0.04);	txt1.SetTextColor(1)
		txt2 = TLatex();  txt2.SetTextSize(0.04);	txt2.SetTextColor(2)

		txt1.DrawLatexNDC(0.65,0.6,"mean = "+str(h1.GetMean()))
		txt2.DrawLatexNDC(0.65,0.5,"mean = "+str(h2.GetMean()))
		
		c.SaveAs(OutPutFN+"_"+var[0]+".pdf");
		c.SaveAs(OutPutFN+"_"+var[0]+".png");
	
		h1.Delete()
		h2.Delete()
		c.Clear()
		count = count+1
		print ""
