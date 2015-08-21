import sys

############    Start:: Reading the input file where variables stored    ##########################

def getVarFromFile(filename):
    import imp
    f = open(filename)
    global data
    data = imp.load_source('data', '', f)
    f.close()

getVarFromFile('InputDetails.dat')

############    END:: Reading the input file where variables stored    ##########################

sys.stdout = open(data.FileName[0]+'.cpp','w')


print '#include<iostream>\n#include <TROOT.h>\n#include <TChain.h>\n#include <TFile.h>\n#include "TLorentzVector.h"\n#include<vector>\n#include "TTree.h"\nusing namespace std;\n\n'
print '//#include "setTDRStyle.C"'
print '//#include "CMS_lumi.C"'

print 'void %s()\n{'%data.FileName[0]

print '//========================= Add TDRStyle Starts ======================================================'
print '//  gROOT->LoadMacro("setTDRStyle.C");'
print '//  setTDRStyle();'
print ''
print '//  gROOT->LoadMacro("CMS_lumi.C");'
print '/*'
print '  writeExtraText = true;       // if extra text'
print '  extraText  = "Preliminary";  // default extra text is "Preliminary"'
print ' lumi_13TeV  = "5.59 pb^{-1}"; // default is "19.7 fb^{-1}"'
print '  lumi_7TeV  = "4.9 fb^{-1}";  // default is "5.1 fb^{-1}"'
print ''
print '  int iPeriod = 4;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV '
print '*/'
print '//========================= Add TDRStyle Ends ========================================================'
print ''
print '//========================= Scale Factors   ==========================================================    '
print 'double w_WJets = 5.59*61526.7/345324 ;'
print ''

print 'TFile fData("%s%s");'%(data.Path, data.DataFile)
print 'TTree *TData = (TTree*)fData.Get("%s");'%data.treeName
for a in range(0,len(data.BkgFile)):
    print 'TFile f%i("%s%s");'%(a, data.Path, data.BkgFile[a])
    print 'TTree *T%i = (TTree*)f%i.Get("%s");'%(a, a, data.treeName)

print 'TFile * file = new TFile("plot_TnP.root","RECREATE"); '
print ''
print '//========================= Cut Detail Starts ========================================================'
print 'TCut cutMu = "MuonsPt>20 && MuonsEta <2.5";'
print 'TCut cutJet = "JetsPt[0] > 30 && JetsPt[1] > 30 && JetsPt[2] > 30 && JetsPt[3] > 30";'
print 'TCut cutVBF = "abs(JetsEta[0]-JetsEta[1])>3.0";'
print ''
print 'TCut cut = cutMu && cutJet;'
print '//========================= Cut Detail Ends =========================================================='

for a in range(0, len(data.VarName)):
    print '//========================================================================== canvas %i starts ========='%a
    print ' '
    print 'TCanvas *c%i = new TCanvas("c%i", "c%i",201,27,989,682);'%(a,a,a)
    print '\tc%i->SetFillColor(0);'%a
    print '\tc%i->SetFrameBorderSize(1);\n'%a
    print 'TPad *pad%i = new TPad("pad%i","pad%i",0,0.2,1,1);'%(a,a,a)
    print '\tpad%i->SetBottomMargin(0.03287462);'%a
    print '\t//pad%i->SetLogy(1);'%a
    print '\tpad%i->Draw();'%a
    print '\tpad%i->cd();'%a
    print ''
    print 'THStack *hs = new THStack("hs","Number of Vertex");	// Defined Stacked histogram'
    print 'TLegend *tleg%i_8 = new TLegend(0.70,0.80,0.85,0.90,NULL,"brNDC");   // Defined legend'%a
    print ''
    for b in range(0, len(data.BkgFile)):
        print 'TH1F *j%i_1 = new TH1F("j%i_1","%s",40,0,40);'%(b, b, data.Title[a])
        print '\tT%i->Draw("%s>>j%i_1",cut,"goff");'%(b, data.VarName[a], b)
        print '\tj%i_1->SetLineColor(kBlack);'%b
        print '\tj%i_1->SetLineWidth(2);'%b
        print '\tj%i_1->SetStats(0);'%b
        print '\tj%i_1->Sumw2();'%b
        print '\t'
        print 'hs->Add(j%i_1);'%b
        print ''
        #print 'j2_1->Scale(w_WJets);'
        #print 'j1_1->Scale(1.);'
        print ''
        print ''
    
    print 'TH1F *h%i_1 = new TH1F("h%i_1","Ratio",40,0,40);'%(a, a)
    print '//TH1F *h2 = new TH1F("h2","",40,76.,106.);'
    print '//TF1* dedxpf = (TF1*)dedxf->Clone();'
    print 'TH1F *h%i = (TH1F*)j1_1->Clone();'
    print 'h1_1->Add(j2_1);'
    print ''
    print 'hs->SetMaximum(1600.);'
    print 'hs->Draw();'
    print ' pad1->Update();'
    print 'j1_1->Draw("sames");'
    print ' pad1->Update();'
    print ''
    print '  tleg1_8->AddEntry(j1_1,"Data","p");'
    print '  tleg1_8->AddEntry(j2_1,"WJets","f");'
    print ' tleg1_8->SetFillColor(kWhite);'
    print ' tleg1_8->Draw("sames");'
    print 'c1->cd();'
    print ''
    print 'TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.2);'
    print '  // TH1F *hs1=hs->Clone();'
    print '   pad2->SetGridy(1);'
    print '   pad2->SetPad(0,0.0,1.0,0.2);'
    print '   pad2->SetTopMargin(0);'
    print '   pad2->SetBottomMargin(0.5);'
    print '   pad2->Draw();'
    print '   pad2->cd();'
    print '  float yscale = (1.0-0.2)/(0.18-0);'
    print '  h2->Divide(h1_1);'
    print '  h2->SetMarkerStyle(21);'
    print '  h2->SetStats(0);'
    print '//  h1->SetMinimum(0.5);'
    print '//  h1->SetMaximum(1.5);'
    print '  h2->GetYaxis()->SetTitle("Data/#Sigma MC");'
    print '  h2->SetMinimum(-0.4);'
    print '  h2->SetMaximum(2.8);'
    print '  h2->GetXaxis()->SetTitle("");'
    print '  h2->GetXaxis()->SetTitleOffset(1.3);'
    print '  h2->GetXaxis()->SetLabelSize(0.033*yscale);'
    print '  h2->GetXaxis()->SetTitleSize(0.036*yscale);'
    print '  h2->GetXaxis()->SetTickLength(0.03*yscale);'
    print '//h1->GetYaxis()->SetLabelFont(63);'
    print '//h1->GetYaxis()->SetLabelSize(12);'
    print 'h2->GetYaxis()->SetTitleOffset(0.3);'
    print 'h2->GetYaxis()->SetNdivisions(5);'
    print 'h2->GetYaxis()->SetLabelSize(0.033*yscale);'
    print 'h2->GetYaxis()->SetTitleSize(0.036*yscale);'
    print '   h2->Draw("");'
    print ''
    print 'c1->SaveAs("Plots/pdf/OutputPlot.pdf");'
    print 'c1->SaveAs("Plots/png/OutputPlot.png");'
    print 'c1->SaveAs("Plots/C/OutputPlot.C");'
    print '//c1->SaveAs("OutputPlot.root");'
    print 'c1->Write();'
    print '//====================='
    print ''
print 'file->Close();'
print '}'
