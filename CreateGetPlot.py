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
print 'gROOT->ProcessLine(".L CompareAdvanced.C");'
print ''
print 'const string Cut = "%s";'%( data.cut )
print ''
print 'TCanvas *Canvas1 = new TCanvas("c1236","Muon",200,10,800,700);'
print ''
print ''

stringD = ""

for a in range(0,data.NumberOfRootFiles):
    #print ',"%s%s","%s"'%(data.PathOfRootFiles, data.InputRootFiles[2*a], data.InputRootFiles[2*a+1]),
    stringD += ',\\"%s%s\\",\\"%s\\"'%(data.PathOfRootFiles, data.InputRootFiles[2*a], data.InputRootFiles[2*a+1])

print ''
#print '=====> ',stringD
print ''
for a in range(0,len(data.variable)/4):
    #print 'gROOT->ProcessLine(Form("compareQuantities(%i,%i,%i,\\"%s\\",\\"%s\\",\\"\\",\\"\\",%s,%s,%s,\\"%%s\\",%i,\"%s%s\",\"%s\",\"%s%s\",\"%s\")",Cut.c_str()));'%(data.isNormUnity, data.isNormLumi, data.isShowEvents, data.TreeName, data.variable[a*4], data.variable[a*4+1], data.variable[a*4+2], data.variable[a*4+3], data.NumberOfRootFiles, data.PathOfRootFiles, data.InputRootFiles[0], data.InputRootFiles[1], data.PathOfRootFiles, data.InputRootFiles[2], data.InputRootFiles[3])
    print 'gROOT->ProcessLine(Form("compareQuantities(%i,%i,%i,\\"%s\\",\\"%s\\",\\"\\",\\"\\",%s,%s,%s,\\"%%s\\",%i%s)",Cut.c_str()));'%(data.isNormUnity, data.isNormLumi, data.isShowEvents, data.TreeName, data.variable[a*4], data.variable[a*4+1], data.variable[a*4+2], data.variable[a*4+3], data.NumberOfRootFiles, stringD)
    print 'Canvas1->SaveAs("%s.pdf");'%data.variable[4*a]
    print 'Canvas1->Clear();'
    print ''
print '} '
