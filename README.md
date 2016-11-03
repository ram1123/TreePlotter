# This macro creates two dimension histogram from a root tree

1. In file **TwoDplots.py** modify two things
	1. Path of input root file
	2. Name of tree in root file
	3. Name of all input root files for which you want to make 2D histogram
2. In file **variableList.dat** provide the list of all variables to plot with its range as per its format.
3. In file **CutList.dat** you can add all the cuts in seperate line without any spaces between any characters.

# How To Run
After modifying above files you can just run it like:

	python TwoDplots.py

It will put all the plots in a directory named **plots** (this directory will be created by macro itself if its not there).
