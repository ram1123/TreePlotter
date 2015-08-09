# TreePlotter
Trying to make an intelligent tree plotting code, where we just need to tell name of root file and variables to plot and it should do everything else automatically.

**Environment Setting**
This code is check for only root version 6.04. So, its recommended that one should run this on root 6.04.

Lxplus setting for root 6.04:

    For tcsh shell:
    source /afs/cern.ch/sw/lcg/external/gcc/4.8/x86_64-slc6/setup.csh
    source /afs/cern.ch/sw/lcg/app/releases/ROOT/6.04.02/x86_64-slc6-gcc48-opt/root/bin/thisroot.csh

    For bash shell:
    source /afs/cern.ch/sw/lcg/external/gcc/4.8/x86_64-slc6/setup.sh
    source /afs/cern.ch/sw/lcg/app/releases/ROOT/6.04.02/x86_64-slc6-gcc48-opt/root/bin/thisroot.sh

**How To Use it**

    source Main.sh NameOfRootFile.root

Then this will create a general header file with all your existing variable in tree defined. then we can use it as per our uses by modifying Master_test.C

