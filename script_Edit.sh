#!/bin/sh

  fname=VarName.dat

  fname2=Title.dat

  fname3=Range.dat

  fname4=Fname.dat

  fname5=PlotName.dat

  exec 3<$fname
  exec 4<$fname2
  exec 5<$fname3
  exec 6<$fname4
  exec 7<$fname5
function make_dir
{

	if [ -d "${1}" ]; then
		echo "Directory ${1} Exists......."
	else
		mkdir ${1}
		echo "Directory ${1} Created................."
	fi
}

make_dir Plots
make_dir Plots/pdf
make_dir Plots/png
make_dir Plots/C
make_dir Plots/Root
make_dir tempCode

  while IFS= read -r line1 <&3
  IFS= read -r line2 <&4
  IFS= read -r line3 <&5
  IFS= read -r line4 <&6
  IFS= read -r line5 <&7
  do
	rm ${line4}.cpp
	rm Plots/Root/plot_TnP.root
	rm Plots/Root/Plot_TnP.root
	echo ${line4}.cpp
	sed  "s/NVtx/${line1}/" plot_TnP.cpp > /tmp/temp1.txt
	sed  "s/Number of Vertex/${line2}/" /tmp/temp1.txt > /tmp/temp2.txt
	sed  "s/40,0,40/${line3}/" /tmp/temp2.txt > /tmp/temp3.txt
	sed  "s/plot_TnP/${line4}/" /tmp/temp3.txt > /tmp/temp4.txt
	sed  "s/OutputPlot/${line5}/" /tmp/temp4.txt > tempCode/${line4}.cpp
	rm /tmp/temp1.txt /tmp/temp2.txt /tmp/temp3.txt /tmp/temp4.txt
	echo "root -l -b -q tempCode/${line4}.cpp"
	root -l -b -q tempCode/${line4}.cpp
  done
  hadd Plots/Root/Plot_TnP.root /tmp/plot_TnP*.root
  rm /tmp/plot_TnP*.root
