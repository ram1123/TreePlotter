# TreePlotter
Trying to make an intelligent tree plotting code, where we just need to tell name of root file and variables to plot and it should do everything else automatically.

# What this framework can do

1. You just need to set a InputDetails.dat file as per its format. Here you just need to give name of input file, variables to plot, cut (upto max 6; one can increase this).

2. Then it will give you plots for all the variables with stack plot.

##Environment Setting
This code is check for only root version 6.04. So, its recommended that one should run this on root 6.04.

Lxplus setting for root 6.04:

    For tcsh shell:
    source /afs/cern.ch/sw/lcg/external/gcc/4.8/x86_64-slc6/setup.csh
    source /afs/cern.ch/sw/lcg/app/releases/ROOT/6.04.02/x86_64-slc6-gcc48-opt/root/bin/thisroot.csh

    For bash shell:
    source /afs/cern.ch/sw/lcg/external/gcc/4.8/x86_64-slc6/setup.sh
    source /afs/cern.ch/sw/lcg/app/releases/ROOT/6.04.02/x86_64-slc6-gcc48-opt/root/bin/thisroot.sh

##How To Use it

1. Step.1 : **Header File Creater**

    source Main.sh NameOfRootFile.root TreeName

Then this will create a general header file with all your existing variable in tree defined. then we can use it as per our uses by modifying Master_test.C

2. Step. 2: **C++ Macro Creator**
 * Edit file **InputDetails.dat** as per its format give necessary information about path of data, name of data, variable to plot, etc
 * Run command:

    python MakeMasterReader.py

 * Now you will get a c++ file named **MasterReader.C**. So, just run it like:

    root -l -b MasterReader.C

 * Finally, you will get all the plots in pdf format.


##Things To Implement

1. Set Option for Stack Plot.
2. Normalize to cross-section.
3. Normalize of a particular data.
4. Fix the code to automatically plot for Endcap; presently it is not working because for endcap we need to do code using fabs.


    
##Find our webpage [here](http://ram1123.github.io/TreePlotter/)

    
