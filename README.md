# TreePlotter
Trying to make an intelligent tree plotting code, where we just need to tell name of root file and variables to plot and it should do everything else automatically.

**Introduction**
This programs reads tree using the TTree::Draw method (Ref:: https://root.cern.ch/root/htmldoc/guides/users-guide/ROOTUsersGuide.html#simple-analysis-using-ttreedraw)


**Environment Setting**
This code is check for only root version 6.04. So, its recommended that one should run this on root 6.04.

Lxplus setting for root 6.04:

    For tcsh shell:
    source /afs/cern.ch/sw/lcg/external/gcc/4.8/x86_64-slc6/setup.csh
    source /afs/cern.ch/sw/lcg/app/releases/ROOT/6.04.02/x86_64-slc6-gcc48-opt/root/bin/thisroot.csh

    For bash shell:
    source /afs/cern.ch/sw/lcg/external/gcc/4.8/x86_64-slc6/setup.sh
    source /afs/cern.ch/sw/lcg/app/releases/ROOT/6.04.02/x86_64-slc6-gcc48-opt/root/bin/thisroot.sh

**How To Run:**

Inputs taken by Macro CompareAdvanced.C:

compareQuantities(bool NormUnity, bool NormLumi, bool ShowEvents, string treeName, string var1, string var2, string xtitle, int nbins, float min, float max, string cut, int n , ... )


var1: Name of branch( variable) to plot

var2: not in use now

xtitle: x-axis title. If it is blank then it will set x-axis title as the var1.

cut: define your cut

n: number of root files


Note: after enter n, enter n number of root file name but enter like this : first write root file name then its legend, then enter 2nd file name and then its legend, ...., nth root file name and then its legend.



Method:1: 
    
    $root -l
    $.L CompareAdvanced.C
    $compareQuantities(1, 0, 0, otree, Lep_pt, "", "", 40, 0, 300, "", 2 , "abc.root", "abc", "xyz.root", "xyz" )

Method:2
Edit the GetPlot.C macro, and enter approx same things there as in method:1 and just run it.
