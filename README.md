# TreePlotter
This code (i.e. branch TreeDrawMethod) reads variables from two different trees and compare them on one canvas.

##How To Run:

1. Modify **InputDetails.dat**[1] according to its format.

2. Run python file **CreateGetPlot.py** like

    python CreateGetPlot.py

3. Above step will create a macro named **GetPlots.C**

4. Now, just run it, like:

    root -l -b -q GetPlots.C

===========================================================
===========================================================
[1] Detail of InputDetails.dat file:

1. In file InputDetails.dat there is a variable named **variable** which is list of tuples. This tuple should have size 4. First element of each tuple should be string that contains branch of the given tree, second, third and fourth element of tuple will be bin number, minx and maxx respectively.
	variable = [ ("pt",50,0,500) , ("eta",20,-3.5,3.5) ]

2. Format of array InputRootFiles: It contains name of root file and its Legend that you want to give. If you have two root files named abc.root adn xyz.root then it will look like:

    InputRootFiles = ["abc.root","ab","xyz.root","xy"]





##Introduction
This programs reads tree using the TTree::Draw method (Ref:: https://root.cern.ch/root/htmldoc/guides/users-guide/ROOTUsersGuide.html#simple-analysis-using-ttreedraw)


##Environment Setting
This code is check for only root version 6.04. So, its recommended that one should run this on root 6.04.

Lxplus setting for root 6.04:

    For tcsh shell:
    source /afs/cern.ch/sw/lcg/external/gcc/4.8/x86_64-slc6/setup.csh
    source /afs/cern.ch/sw/lcg/app/releases/ROOT/6.04.02/x86_64-slc6-gcc48-opt/root/bin/thisroot.csh

    For bash shell:
    source /afs/cern.ch/sw/lcg/external/gcc/4.8/x86_64-slc6/setup.sh
    source /afs/cern.ch/sw/lcg/app/releases/ROOT/6.04.02/x86_64-slc6-gcc48-opt/root/bin/thisroot.sh

# To Do List

1. Fix the code for compare different branches from same tree.
