#############################
##	Things to do
##
##	1. For every TFile include a error exceptional msg about file not found
##      2. Set Minimum range for stack plots
##
#############################
import sys
sys.stdout = open('MasterReader.C','w')

############    include Header files    ##########################
print '#include<iostream>\n#include <TROOT.h>\n#include <TChain.h>\n#include <TFile.h>\n#include "TLorentzVector.h"\n#include<vector>\n#include "TTree.h"\n#include "ClassReadTree.cc"\n#include "tdrstyle.C"\n\nusing namespace std;\n\n'



print 'void MasterReader(){\n setTDRStyle();\n\n'

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

print 'double Min[%i] = {'%(len(data.varList)/4),
for a in range(0,len(data.varList)/4):
    print data.varList[a*4+2],
    if a==((len(data.varList)/4)-1):
        print '};'
    else:
        print ',',

print 'double Max[%i] = {'%(len(data.varList)/4),
for a in range(0,len(data.varList)/4):
    print data.varList[a*4+3],
    if a==((len(data.varList)/4)-1):
        print '};\n'
    else:
        print ',',

print 'int NumPV;'

print 'int j=0;\t//for bins\nint k=3;\t//reseting the color of backgrounds'
############ END:: Setting Bin, Min and Max       ###########################


########## Define STACKED histogram  ########################
print '\tTCanvas * c1 = new TCanvas("c1","",500,500);\n'
if data.ifPUCorr == 1:
	print '\tTFile f("/tmp/PileUpHisto.root");'
	print '\tTH1F *h = (TH1F*)f.Get("j1_1");'
print '\tint binidx;'
print '\tfloat Nvtx_weight;'
print ''
print "\tTHStack** hs = new THStack*[%i];"%(len(data.varList)/4)
print "\tTPad** pad = new TPad*[%i];"%(len(data.varList)/4)
print "\tTPad** padB = new TPad*[%i];"%(len(data.varList)/4)
print '\tTH1F**hRatio = new TH1F*[%i];'%(len(data.varList)/4)
print "\tfor(int i=0; i<%i;i++){"%(len(data.varList)/4)
print '\t\ths[i] = new THStack(Form("hs%i",i),"");'
print '\t\tpad[i] = new TPad(Form("pad%i",i),"",0,0.30,1,1);'
print '\t\tpadB[i] = new TPad(Form("padB%i",i),"",0,0,1,0.30);'
print '\t\thRatio[i] = new TH1F(Form("hRatio%i",i),"Ratio",Bin[i],Min[i],Max[i]);'
print '\t}\n'
########## END:: Define STACKED histogram  ########################


########## Define histogram for sig mc  ########################
if len(data.list_mc_sig) != 0:
	for a in range(0,len(data.list_mc_sig)):
		print "\tTH1F** t%i_SigHist = new TH1F*[%i];"%(a, len(data.varList)/4)
	
	for a in range(0,len(data.list_mc_sig)):
		print "\tfor(int i=0; i<%i;i++){"%(len(data.varList)/4)
		print '\t\tif (i%%%i==0)     {k++;}\t// for line & Fill color'%(len(data.varList)/4)
		print '\t\tt%i_SigHist[i] = new TH1F(Form("t%i_SigHist%%i",i),"",Bin[i],Min[i],Max[i]);'%(a,a)
		print '\t\tt%i_SigHist[i]->SetMarkerColor(k);'%a
		print '\t\tt%i_SigHist[i]->SetLineWidth(k);'%a
		print '\t\tt%i_SigHist[i]->SetLineColor(k);\n\t}\n'%a

########## Define histogram for bkg mc  ########################
for a in range(0,len(data.list_mc_bkg)):
	print "\tTH1F** t%i_BkgHist = new TH1F*[%i];"%(a, len(data.list_mc_bkg)*len(data.varList)/4)

for a in range(0,len(data.list_mc_bkg)):
	print "\tfor(int i=0; i<%i;i++){"%(len(data.varList)/4)
        if (data.list_mc_bkg[a]).find("WJet") != -1:
            print '\t\tif (i%%%i==0)     {j=0;\t//for reset bins\n\t\t\t\tk=2;}\t// for line & Fill color'%(len(data.varList)/4)
            #print '\t\tk=2;\t// for line & Fill color'
        else:
	    print '\t\tif (i%%%i==0)     {j=0;\t//for reset bins\n\t\t\t\tk++;}\t// for line & Fill color'%(len(data.varList)/4)
	print '\t\telse j++;'
	print '\t\tif (k==8) k++;'
	print '\t\tif (k==10) k++;'
	print '\t\tt%i_BkgHist[i] = new TH1F(Form("t%i_BkgHist%%i",i),"",Bin[j],Min[j],Max[j]);'%(a,a)
	print '\t\tt%i_BkgHist[i]->SetLineColor(k);'%a
	print '\t\tt%i_BkgHist[i]->SetMarkerColor(k);'%a
	print '\t\tt%i_BkgHist[i]->SetFillColor(k);\n\t}\n'%a

########## Define histogram for data mc  ########################
print "\tTH1F** DataHist = new TH1F*[%i];"%(len(data.list_data)*len(data.varList)/4)

print "\tfor(int i=0; i<%i;i++){"%(len(data.list_data)*len(data.varList)/4)
print '\t\tDataHist[i] = new TH1F(Form("DataHist%i",i),"",Bin[i],Min[i],Max[i]);'
print '\t\tDataHist[i]->SetLineColor(1);'
print '\t\tDataHist[i]->SetMarkerColor(1);'
print '\t\t//DataHist[i]->Sumw2();\n\t}\n'

################################################################
if len(data.list_mc_sig) != 0:
	for a in range(0,len(data.list_mc_sig)):
	    print '\tTChain* t%i_mc_sig = new TChain("%s");'% (a, data.treeName)
	    print '\t\tt%i_mc_sig->Add("%s%s");'%(a, data.store_mc_sig, data.list_mc_sig[a])
	    print '\t\tClassReadTree mc_sig_%i(t%i_mc_sig);'%(a, a)
	    print '\t\tfor(int iEv_%i_mc_sig=0;iEv_%i_mc_sig < t%i_mc_sig->GetEntries();iEv_%i_mc_sig++){'%(a, a, a, a)
	    print '\t\t\tt%i_mc_sig->GetEntry(iEv_%i_mc_sig);'%(a, a)    
	    if data.ifPUCorr == 1:
	    	print '\t\t\tNumPV=mc_sig_%i.nPV;'%a
	    	print '\t\t\tbinidx = h->FindBin(NumPV);'
	    	print '\t\t\tNvtx_weight = h->GetBinContent(binidx);'
	    	print '\t\t\tif(Nvtx_weight ==0) Nvtx_weight = 1 ;'
	    for b in range(0, len(data.varList)/4):
		if data.ifPUCorr == 1:
	        	print '\t\t\tt%i_SigHist[%i]->Fill(mc_sig_%s.%s,Nvtx_weight);'%(a, b, a, data.varList[b*4])
		else:
	        	print '\t\t\tt%i_SigHist[%i]->Fill(mc_sig_%s.%s);'%(a, b, a, data.varList[b*4])
	    print '\t\t}'
	    print '\n'

for a in range(0,len(data.list_mc_bkg)):
    print '\tTChain* t%i_mc_bkg = new TChain("%s");'%(a, data.treeName)
    print '\t\tt%i_mc_bkg->Add("%s%s");'%(a, data.store_mc_bkg, data.list_mc_bkg[a])
    print '\t\tClassReadTree mc_bkg_%i(t%i_mc_bkg);'%(a, a)
    print '\t\tfor(int iEv_%i_mc_bkg=0;iEv_%i_mc_bkg < t%i_mc_bkg->GetEntries();iEv_%i_mc_bkg++){'%(a, a, a, a)
    print '\t\t\tt%i_mc_bkg->GetEntry(iEv_%i_mc_bkg);'%(a, a)   
    if data.ifPUCorr == 1:
    	print '\t\t\tNumPV=mc_bkg_%i.nPV;'%a
    	print '\t\t\tbinidx = h->FindBin(NumPV);'
    	print '\t\t\tNvtx_weight = h->GetBinContent(binidx);'
    	print '\t\t\tif(Nvtx_weight ==0) Nvtx_weight = 1 ;'
    for b in range(0, len(data.varList)/4):
	if data.ifPUCorr == 1:
        	print '\t\t\tt%i_BkgHist[%i]->Fill(mc_bkg_%i.%s,Nvtx_weight);'%(a,b,a, data.varList[b*4])
	else:
                print '\t\t\tif (mc_bkg_%i.%s)'%(a,data.cuts[0])
        	print '\t\t\tt%i_BkgHist[%i]->Fill(mc_bkg_%i.%s);'%(a,b,a, data.varList[b*4])
        	#print '\t\t\tt%i_BkgHist[%i]->Fill(mc_bkg_%i.%s,mc_bkg_%i.%s);'%(a,b,a, data.varList[b*4],a,data.weights[0])
    print '\t\t}'
    print '\n'

for a in range(0,len(data.list_data)):
    print '\tTChain* t%i_data = new TChain("%s");'%(a, data.treeName)
    print '\t\tt%i_data->Add("%s%s");'%(a, data.store_data, data.list_data[a])
    print '\t\tClassReadTree mc_data_%i(t%i_data);'%(a, a)
    print '\t\tfor(int iEv_%i_data=0;iEv_%i_data < t%i_data->GetEntries();iEv_%i_data++){'%(a, a, a, a)
    print '\t\t\tt%i_data->GetEntry(iEv_%i_data);'%(a, a)  
    for b in range(0, len(data.varList)/4):
        #print '\t\t\tif (mc_data_0.%s && mc_data_0.mass_lvjj_type0_AK4 < 200)'%(data.cuts[0])
        print '\t\t\tif (mc_data_0.%s)'%(data.cuts[0])
        print '\t\t\tDataHist[%i]->Fill(mc_data_0.%s);'%(a+b+a*((len(data.varList)/4)-1), data.varList[b*4])
    print '\t\t}'
    print '\n'

print '\tTLegend *leg = new TLegend(0.79,0.40,1.09,0.89,NULL,"brNDC");\n'
print 'double yMax=0.;\ndouble HistMax=0.0;\nc1->cd();\n'
for a in range(0,len(data.varList)/4):
    #print '\n\n\n\n===========================================================\n\n'
    #print a
    #print '\n\n\n\n===========================================================\n\n'

    print 'pad[%i]->SetBottomMargin(0.05287462);'%a
    print 'pad[%i]->SetLogy(1);'%a
    print 'pad[%i]->Draw();'%a
    print 'pad[%i]->cd();\n'%a

    if len(data.list_mc_sig) != 0:
    	for sig in range(0,len(data.list_mc_sig)):
		print '\tt%i_SigHist[%i]->Scale(%f);'%(sig,a,float(data.SigScale[sig]))
    		print '\tHistMax = t%i_SigHist[%i]->GetMaximum()*1.15;'%(sig,a)
    		print '\tt0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));'
    		print '\tt0_SigHist[0]->SetMinimum(0.0);'
    		print '\tleg->AddEntry(t%i_SigHist[%i],"%s","l");'%(sig,a,data.NameSig[sig])
    		print '\tyMax=HistMax;\n'
		print '\tcout<<"=====> \tHistMax = "<<yMax<<endl;'
		print '\tcout<<"============================>>> \t MaxValue Y-axis = "<< t%i_SigHist[%i]->GetMaximum() << endl;'%(sig,a)

    CountWjet = 0
    for bkg in range(0,len(data.list_mc_bkg)):
    	print '\tt%i_BkgHist[%i]->Scale(%f);'%(bkg,a,float(data.scale[bkg]))
    	print '\tHistMax = t%i_BkgHist[%i]->GetMaximum()*1.15;'%(bkg, a)
	if len(data.list_mc_sig) != 0:
    		print '\tt0_SigHist[0]->SetMaximum(TMath::Max(HistMax,yMax));'
    		print '\tt0_SigHist[0]->SetMinimum(0.0);'
	else:
    		print '\tt0_BkgHist[0]->SetMaximum(TMath::Max(HistMax,yMax));'
    		print '\tt0_BkgHist[0]->SetMinimum(0.0);'
        if (data.list_mc_bkg[bkg]).find("WJet" or "TTBar") == -1:
            print '\tleg->AddEntry(t%i_BkgHist[%i],"%s","f");'%(bkg, a, str(data.NameBkg[bkg]))
        else:
            if CountWjet == 0:
                print '\tleg->AddEntry(t%i_BkgHist[%i],"WJets","f");'%(bkg, a)            
            CountWjet=CountWjet+1
    	print '\tyMax=HistMax;\n'
	print '\tcout<<"=====> \tHistMax = "<<yMax<<endl;'
	#if len(data.list_mc_sig) != 0:
	#	print '\tcout<<"============================>>> \t MaxValue Y-axis = "<< t%i_SigHist[%i]->GetMaximum() << endl;'%(sig,a)
	#else:
	#	print '\tcout<<"============================>>> \t MaxValue Y-axis = "<< t%i_BkgHist[%i]->GetMaximum() << endl;'%(bkg,a)


    print '\tDataHist[%i]->Sumw2();'%a
    print '\tHistMax = DataHist[%i]->GetMaximum()*1.15;'%a
    print '\tleg->AddEntry(DataHist[%i],"Data","pe");'%(a)
    print '\tyMax=HistMax;\n'

    for bkg in range(0,len(data.list_mc_bkg)):
    	print '\ths[%i]->Add(t%i_BkgHist[%i],"hist");'%(a, bkg, a)
    #print '\ths[%i]->SetMinimum(0.0);'%a       // By adding this I am getting error saying "Error in <THistPainter::PaintInit>: Cannot set Y axis to log scale"
    print '\ths[%i]->SetMaximum(yMax);'%a
    print '\ths[%i]->Draw();'%a
    print '\tDataHist[%i]->Draw("same");'%a
    if len(data.list_mc_sig) != 0:
    	for sig in range(0,len(data.list_mc_sig)):
    		print '\tt%i_SigHist[%i]->Draw("same");'%(sig,a)
    print '\tleg->Draw("same");'

    if a==0:
	print 'TH1F *h2 = (TH1F*)DataHist[%i]->Clone();'%a
    else:
	print 'h2 = (TH1F*)DataHist[%i]->Clone();'%a
    for bkg in range(0,len(data.list_mc_bkg)):
    	print 'hRatio[%i]->Add(t%i_BkgHist[%i]);'%(a, bkg, a)
    print ''
    print ''
    print 'c1->cd();'
    print 'padB[%i]->SetGridy(1);'%a
    print 'padB[%i]->SetTopMargin(0.0);'%a
    print 'padB[%i]->SetBottomMargin(0.30);'%a
    print 'padB[%i]->Draw();'%a
    print 'padB[%i]->cd();'%a
    print ''
    if a==0:
    	print 'float yscale = (1.0-0.2)/(0.18-0);'
    else:
    	print 'yscale = (1.0-0.2)/(0.18-0);'
    print 'h2->Divide(hRatio[%i]);'%a
    #print a
    print 'cout<<"Total Number of Events in Data = "<<DataHist[%i]->Integral()<<endl;'%a
    print 'cout<<"Total Number of Events in MC   = "<<hRatio[%i]->Integral()<<endl;'%a
    print 'cout<<"Ratio of Data/MC = "<<(DataHist[%i]->Integral())/(hRatio[%i]->Integral())<<endl;'%(a,a)
    if len(data.list_mc_sig) != 0:
    	for sig in range(0,len(data.list_mc_sig)):
    		print 'cout<<"Number of event in %s  = "<<t%i_BkgHist[%i]->Integral()<<endl;'%(data.NameSig[sig],sig,a)
    for bkg in range(0,len(data.list_mc_bkg)):
    	print 'cout<<"Number of event in %s  = "<<t%i_BkgHist[%i]->Integral()<<endl;'%(data.NameBkg[bkg],bkg,a)

    print 'h2->SetMarkerStyle(21);'
    print 'h2->SetStats(0);'
    print 'h2->GetYaxis()->SetTitle("Data/#Sigma MC");'
    print 'h2->GetXaxis()->SetTitle("%s");'%(str(data.varList[4*a]))
    print 'h2->SetMinimum(0.5);'
    print 'h2->SetMaximum(1.5);'
    print 'h2->GetXaxis()->SetTitleOffset(0.8);'
    print 'h2->GetXaxis()->SetLabelSize(0.033*yscale);'
    print 'h2->GetXaxis()->SetTitleSize(0.036*yscale);'
    print 'h2->GetXaxis()->SetTickLength(0.03*yscale);'
    print 'h2->GetYaxis()->SetTitleOffset(0.3);'
    print 'h2->GetYaxis()->SetNdivisions(5);'
    print 'h2->GetYaxis()->SetLabelSize(0.033*yscale);'
    print 'h2->GetYaxis()->SetTitleSize(0.036*yscale);'
    print 'h2->Draw("");'
    print '\tc1->SaveAs("%s.pdf");'%data.varList[a*4]
    print '\tc1->SaveAs("%s.png");'%data.varList[a*4]
    print '\tleg->Clear();'
    print '\tc1->Clear();\n\t//###########################################################\n\n'

print '\n\n}'
