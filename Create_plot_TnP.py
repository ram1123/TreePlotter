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
for a in range(1,len(data.BkgFile)+1):
    print 'TFile f%i("%s%s");'%(a, data.Path, data.BkgFile[a-1])
    print 'TTree *T%i = (TTree*)f%i.Get("%s");'%(a, a, data.treeName)

print 'TFile * file = new TFile("plot_TnP.root","RECREATE"); '
print ''
print '//========================= Cut Detail Starts ========================================================'
print 'TCut cutMu = "MuonsPt>20 && MuonsEta <2.5";'
print 'TCut cutJet = "JetsPt[0] > 30 && JetsPt[1] > 30 && JetsPt[2] > 30 && JetsPt[3] > 30";'
print 'TCut cutVBF = "abs(JetsEta[0]-JetsEta[1])>3.0";'
print ''
print 'TCut cut = "%s";'%data.cut
print '//========================= Cut Detail Ends =========================================================='

for a in range(1, len(data.VarName)+1):
    print '//========================================================================== canvas %i starts ========='%a
    print ' '
    print 'TCanvas *c%i = new TCanvas("c%i", "c%i",201,27,989,682);'%(a,a,a)
    print '\tc%i->SetFillColor(0);'%a
    print '\tc%i->SetFrameBorderSize(1);\n'%a
    print 'TPad *pad%i_1 = new TPad("pad%i_1","pad%i_1",0,0.2,1,1);'%(a,a,a)
    print '\tpad%i_1->SetBottomMargin(0.03287462);'%a
    print '\t//pad%i_1->SetLogy(1);'%a
    print '\tpad%i_1->Draw();'%a
    print '\tpad%i_1->cd();'%a
    print ''
    print 'THStack *hs%i = new THStack("hs%i","Number of Vertex");	// Defined Stacked histogram'%(a,a)
    print 'TLegend *tleg%i_8 = new TLegend(0.70,0.80,0.85,0.90,NULL,"brNDC");   // Defined legend'%a
    print ''
    for b in range(1, len(data.BkgFile)+1):
        print 'TH1F *j%i_%i = new TH1F("j%i_%i","%s",%s,%s,%s);'%(a, b, a, b, data.Title[a-1], data.Range[(a-1)*3], data.Range[(a-1)*3+1], data.Range[(a-1)*3+2])
        print '\tT%i->Draw("%s>>j%i_%i",cut,"goff");'%(b, data.VarName[a-1], a, b)
        print '\tj%i_%i->SetLineColor(%i);'%(a, b, b)
        print '\tj%i_%i->SetFillColor(%i);'%(a, b, b)
        print '\tj%i_%i->SetLineWidth(2);'%(a, b)
        print '\tj%i_%i->SetStats(0);'%(a, b)
        if b == 1:
            print '\tj%i_%i->Sumw2();'%(a, b)
        print '\t'
        print ''
        #print 'j2_1->Scale(w_WJets);'
        #print 'j1_1->Scale(1.);'
        print ''
        print ''
    
    for b in range(1, len(data.BkgFile)+1):
        if b != 1:
            print 'hs%i->Add(j%i_%i);'%(a, a, b)

    print ''
    for b in range(1, len(data.BkgFile)+1):
        print 'j%i_%i->Scale(1.0);'%(a, b)
        #print 'j%i_%i->Scale(scale[%i]);'%(b, b-1)

    print 'TH1F *h%i_1 = new TH1F("h%i_1","Ratio",%s, %s, %s);'%(a, a, data.Range[(a-1)*3], data.Range[(a-1)*3+1], data.Range[(a-1)*3+2])
    #print '//TH1F *h2 = new TH1F("h2","",40,76.,106.);'
    #print '//TF1* dedxpf = (TF1*)dedxf->Clone();'
    print 'TH1F *h%i = (TH1F*)j%i_%i->Clone();'%(a,a,b)
    for b in range(1, len(data.BkgFile)+1):
        print 'h%i_1->Add(j%i_%i);'%(a,a, b)
    print ''
    print '//hs%i->SetMaximum(1600.);'%a
    print 'hs%i->Draw();'%a
    print 'pad%i_1->Update();'%a
    print 'j%i_1->Draw("sames"); // Draw the signal'%(a)    # presently J%i_1 but 1 should be changed accordingly
    print 'pad%i_1->Update();'%a
    print ''
    for b in range(1, len(data.BkgFile)+1):
        print 'tleg%i_8->AddEntry(j%i_%i,"%s","l");'%(a,a, b, data.BkgFile[b-1])
    print 'tleg%i_8->SetFillColor(kWhite);'%a
    print 'tleg%i_8->Draw("sames");'%a
    print 'c%i->cd();'%a
    print ''
    print 'TPad *pad%i_2 = new TPad("pad%i_2","pad%i_2",0,0,1,0.2);'%(a,a,a)
    print '// TH1F *hs%i1=hs%i->Clone();'%(a,a)
    print 'pad%i_2->SetGridy(1);'%a
    print 'pad%i_2->SetPad(0,0.0,1.0,0.2);'%a
    print 'pad%i_2->SetTopMargin(0);'%a
    print 'pad%i_2->SetBottomMargin(0.5);'%a
    print 'pad%i_2->Draw();'%a
    print 'pad%i_2->cd();'%a
    print 'float yscale_%i = (1.0-0.2)/(0.18-0);'%a
    print 'h%i->Divide(h1_1);'%a
    print 'h%i->SetMarkerStyle(21);'%a
    print 'h%i->SetStats(0);'%a
    print '//h1->SetMinimum(0.5);'
    print '//h1->SetMaximum(1.5);'
    print 'h%i->GetYaxis()->SetTitle("Data/#Sigma MC");'%a
    print 'h%i->SetMinimum(-0.4);'%a
    print 'h%i->SetMaximum(2.8);'%a
    print 'h%i->GetXaxis()->SetTitle("");'%a
    print 'h%i->GetXaxis()->SetTitleOffset(1.3);'%a
    print 'h%i->GetXaxis()->SetLabelSize(0.033*yscale_%i);'%(a,a)
    print 'h%i->GetXaxis()->SetTitleSize(0.036*yscale_%i);'%(a,a)
    print 'h%i->GetXaxis()->SetTickLength(0.03*yscale_%i);'%(a,a)
    print '//h%i->GetYaxis()->SetLabelFont(63);'%a
    print '//h%i->GetYaxis()->SetLabelSize(12);'%a
    print 'h%i->GetYaxis()->SetTitleOffset(0.3);'%a
    print 'h%i->GetYaxis()->SetNdivisions(5);'%a
    print 'h%i->GetYaxis()->SetLabelSize(0.033*yscale_%i);'%(a,a)
    print 'h%i->GetYaxis()->SetTitleSize(0.036*yscale_%i);'%(a,a)
    print 'h%i->Draw("");'%a
    print ''
    print 'c%i->SaveAs("Plots/pdf/%s.pdf");'%(a, data.OutPutFileName[a-1])
    print 'c%i->SaveAs("Plots/png/%s.png");'%(a, data.OutPutFileName[a-1])
    print 'c%i->SaveAs("Plots/C/%s.C");'%(a, data.OutPutFileName[a-1])
    print '//c%i->SaveAs("%s.root");'%(a, data.OutPutFileName[a-1])
    print 'c%i->Write();'%a
    print '//====================='
    print ''
print 'file->Close();'
print '}'
