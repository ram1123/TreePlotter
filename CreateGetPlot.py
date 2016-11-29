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

#sys.stdout = open('GetPlots.C','w')

file_Out = open('GetPlots.C','w')

file_Out.write( '\n')
file_Out.write( '/*\n')
file_Out.write( ' * Compare Root Files\n')
file_Out.write( ' *\n')
file_Out.write( ' */\n')
file_Out.write( '#include "TCanvas.h"\n')
file_Out.write( '#include "TROOT.h"\n')
file_Out.write( '#include <iostream>\n')
file_Out.write( '\n')
file_Out.write( 'void GetPlots()\n')
file_Out.write( '{\n')
if data.CompareAdvanced_1RootFileNBranch == 1:
	file_Out.write( 'gROOT->ProcessLine(".L CompareAdvanced_1RootFileNBranch.C");\n')
if data.CompareAdvanced_1RootFileNBranch == 0:
	file_Out.write( 'gROOT->ProcessLine(".L CompareAdvanced.C");\n')
file_Out.write( '')
file_Out.write( 'const string Cut = "%s";\n'%( data.cut ))
file_Out.write( '\n')
file_Out.write( 'TCanvas *Canvas1 = new TCanvas("c1236","Muon",200,10,800,700);\n')
file_Out.write( '\n')
file_Out.write( '')

stringD = ""

if data.CompareAdvanced_1RootFileNBranch == 0:
	for a in range(0,len(data.InputRootFiles)/2):
	    stringD += ',\\"%s%s\\",\\"%s\\"'%(data.PathOfRootFiles, data.InputRootFiles[2*a], data.InputRootFiles[2*a+1])

file_Out.write( '\n')

if data.CompareAdvanced_1RootFileNBranch == 0:
	for a in range(0,len(data.variable)):
	    file_Out.write( 'gROOT->ProcessLine(Form("compareQuantities(%i,%i,%i,%i, %i, \\"%s\\",\\"%s\\",\\"\\",\\"\\",%s,%s,%s,\\"%%s\\",%i%s)",Cut.c_str()));\n'%(data.isNormUnity, data.isNormLumi, data.isShowEventsLegend, data.isLegendDraw, data.isGetStatBox, data.TreeName, data.variable[a][0], data.variable[a][1], data.variable[a][2], data.variable[a][3], len(data.InputRootFiles)/2, stringD))
	    file_Out.write( 'Canvas1->SaveAs("%s.pdf");\n'%(''.join(e for e in data.variable[a][0] if e.isalnum())))
	    file_Out.write( 'Canvas1->SaveAs("%s.png");\n'%(''.join(e for e in data.variable[a][0] if e.isalnum())))
	    file_Out.write( 'Canvas1->Clear();\n')
	    file_Out.write( '\n')
if data.CompareAdvanced_1RootFileNBranch == 1:
	print "Test 1"
	print data.variable_1RF
	for a in range(0,len(data.variable_1RF)):
		print "====\n\n"
		stringD = ""
		print data.variable_1RF[a][0]
		for b in range(0,(len(data.variable_1RF[a][0]))):
	    		#stringD += ',\\"%s\\",\\"%s\\"'%( data.variable[0][0], data.variable[0][0])
			stringD += ',\\"%s\\"'%(data.variable_1RF[a][0][b])
		print "stringD = ",stringD
		file_Out.write( '\n')
	    	file_Out.write( 'gROOT->ProcessLine(Form("compareQuantities(\\"%s%s\\",%i,%i,%i,%i, %i, \\"%s\\",\\"\\",\\"\\",\\"%s\\",%s,%s,%s,\\"%%s\\",%i%s)",Cut.c_str()));\n'%( data.PathOfRootFiles, data.InputRootFiles[0], data.isNormUnity, data.isNormLumi, data.isShowEventsLegend, data.isLegendDraw, data.isGetStatBox, data.TreeName, data.variable_1RF[a][2], data.variable_1RF[a][1][0], data.variable_1RF[a][1][1], data.variable_1RF[a][1][2],  (len(data.variable_1RF[a][0])/2), stringD))
	    	file_Out.write( 'Canvas1->SaveAs("%s.pdf");\n'%(''.join(e for e in data.variable_1RF[a][2] if e.isalnum())))
	    	file_Out.write( 'Canvas1->SaveAs("%s.png");\n'%(''.join(e for e in data.variable_1RF[a][2] if e.isalnum())))
	    	file_Out.write( 'Canvas1->Clear();\n')
	#    	file_Out.write( '\n')
file_Out.write( '} \n')
file_Out.close()
print "Run the command:"
print "root -l -b -q GetPlots.C"
