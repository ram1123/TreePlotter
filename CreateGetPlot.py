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

sys.stdout = open('GetPlots.C','w')

print ''
print '/*'
print ' * Compare Root Files'
print ' *'
print ' */'
print '#include "TCanvas.h"'
print '#include "TROOT.h"'
print '#include <iostream>'
print ''
print 'void GetPlots()'
print '{'
if data.CompareAdvanced_1RootFileNBranch == 1:
	print 'gROOT->ProcessLine(".L CompareAdvanced_1RootFileNBranch.C");'
if data.CompareAdvanced_1RootFileNBranch == 0:
	print 'gROOT->ProcessLine(".L CompareAdvanced.C");'
print ''
print 'const string Cut = "%s";'%( data.cut )
print ''
print 'TCanvas *Canvas1 = new TCanvas("c1236","Muon",200,10,800,700);'
print ''
print ''

stringD = ""

if data.CompareAdvanced_1RootFileNBranch == 0:
	for a in range(0,data.NumberOfRootFiles):
	    stringD += ',\\"%s%s\\",\\"%s\\"'%(data.PathOfRootFiles, data.InputRootFiles[2*a], data.InputRootFiles[2*a+1])

print ''

if data.CompareAdvanced_1RootFileNBranch == 0:
	for a in range(0,len(data.variable)/4):
	    print 'gROOT->ProcessLine(Form("compareQuantities(%i,%i,%i,%i, %i, \\"%s\\",\\"%s\\",\\"\\",\\"\\",%s,%s,%s,\\"%%s\\",%i%s)",Cut.c_str()));'%(data.isNormUnity, data.isNormLumi, data.isShowEventsLegend, data.isLegendDraw, data.isGetStatBox, data.TreeName, data.variable[a*4], data.variable[a*4+1], data.variable[a*4+2], data.variable[a*4+3], data.NumberOfRootFiles, stringD)
	    print 'Canvas1->SaveAs("%s.pdf");'%data.variable[4*a]
	    print 'Canvas1->Clear();'
	    print ''
if data.CompareAdvanced_1RootFileNBranch == 1:
	for a in range(0,len(data.variable)):
		stringD = ""
		for b in range(0,(len(data.variable[a])-5)/2):
	    		stringD += ',\\"%s\\",\\"%s\\"'%( data.variable[a][2*b], data.variable[a][2*b+1])
		print ''
	    	print 'gROOT->ProcessLine(Form("compareQuantities(%i,\\"%s%s\\",%i,%i,%i,%i, %i, \\"%s\\",\\"\\",\\"\\",\\"%s\\",%s,%s,%s,\\"%%s\\",%i%s)",Cut.c_str()));'%(data.CompareAdvanced_1RootFileNBranch, data.PathOfRootFiles, data.InputRootFiles[0], data.isNormUnity, data.isNormLumi, data.isShowEventsLegend, data.isLegendDraw, data.isGetStatBox, data.TreeName, data.variable[a][-5], data.variable[a][-3], data.variable[a][-2], data.variable[a][-1], (len(data.variable[a])-5)/2, stringD)
	    	print 'Canvas1->SaveAs("%s.pdf");'%data.variable[a][-4]
	    	print 'Canvas1->Clear();'
	    	print ''
print '} '
