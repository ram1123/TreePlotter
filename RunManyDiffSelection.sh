# V1
#source Main.sh /home/ramkrishna/cernbox/aQGC_Studies/SecondStep_Ntuples/Changed_VBF_Wjet_Selection/output/output_mu/WWTree_tWch.root otree
# V2
#source Main.sh /home/ramkrishna/cernbox/aQGC_Studies/SecondStep_Ntuples/AddedLepFlavor_NoCutIfNoVBFfound/output/output_mu/WWTree_tWch.root otree
#source Main.sh /home/ramkrishna/cernbox/aQGC_Studies/SecondStep_Ntuples/OnlyLep_WithoutIdIso/output/output_mu/WWTree_tWch.root otree

#echo "python MakeMasterReader.py "
#python MakeMasterReader.py 
#echo "root -l -b -q MasterReader.C "
#root -l -b -q MasterReader.C 
#cp *.pdf ~/Temp_PPT_Script/
#echo -e "\n\n======================================================\n\tAll PDF files are copied to ~/Temp_PPT_Script/ directory\n\n========================================================="
today=`date +%d%m%Y_%H%M%S`

green='\033[0;32m'
red='\033[0;31m'
blue='\033[0;34m'

NC='\033[0m' # No Color

echo -e "${green}Is the document second_step_code_Details.dat updated? (default y): (y/n): ${NC}"
read DocUpdated

if [[ "$DocUpdated" == "" ]]; then
	DocUpdated=y
	echo -e "\n\n====================================================================\n\n"
	echo -e "${green}Assuming the code is updated... \n\n${NC}"	
	echo -e "${green}Going to excute the whole program	\n${NC}"
else
	if [ "$DocUpdated" == "y" ]; then
		echo -e "\n\n====================================================================\n\n"
		echo -e "${green}Going to excute the whole program	\n${NC}"
	else
		if [ "$DocUpdated" == "n" ]; then
			vi second_step_code_Details.dat
			echo -e "\n\n=====================================================================\n\n"
			echo -e "${blue}Updated the second step information	\n\n${NC}"
		else
			echo -e "\n\n=====================================================================\n\n"
			echo -e "${red} ERROR: Please enter appropriate option	\n${NC}"
			exit 1
		fi
	fi
fi



echo -e "\n\n=====================================================================\n\n"
echo -e     "==========	Plots for electrons: With Corr & MET Cut	=============="
cp 	InputDetails_el.dat	InputDetails.dat
echo "python MakeMasterReader.py "
#python MakeMasterReader.py 
#echo "root -l -b -q MasterReader.C "
#root -l -b -q MasterReader.C 
#mkdir Plots_El_Corr_MET40_${today}
#cp second_step_code_Details.dat InputDetails.dat  MasterReader.C *.png *.pdf *.root Plots_El_Corr_MET40_${today}
#source /home/ramkrishna/MyLocalWebsite/ImageHTMLcreateScript.sh  /home/ramkrishna/PhD_New_Dir_16July2016/PhysicsAnalysis/aQGC_Analysis/aQGC_Plotting_Code/TreePlotter/Plots_El_Corr_MET40_${today}/  HTMLFiles/Plots_El_Corr_MET40_${today}.htm
#
#echo -e "\n\n=====================================================================\n\n"
#echo -e     "==========	Plots for electrons: Without Corr & MET Cut	=============="
#cp 	InputDetails_el_NoCorr.dat	InputDetails.dat
#echo "python MakeMasterReader.py "
#python MakeMasterReader.py 
#echo "root -l -b -q MasterReader.C "
#root -l -b -q MasterReader.C 
#mkdir Plots_El_NoCorr_MET40_${today}
#cp MasterReader.C second_step_code_Details.dat InputDetails.dat   *.png *.pdf *.root Plots_El_NoCorr_MET40_${today}
#source /home/ramkrishna/MyLocalWebsite/ImageHTMLcreateScript.sh /home/ramkrishna/PhD_New_Dir_16July2016/PhysicsAnalysis/aQGC_Analysis/aQGC_Plotting_Code/TreePlotter/Plots_El_NoCorr_MET40_${today}/  HTMLFiles/Plots_El_NoCorr_MET40_${today}.htm
#
#
#echo -e "\n\n=====================================================================\n\n"
#echo -e     "==========	Plots for electrons: With Corr & No MET Cut	=============="
#cp 	InputDetails_el_NoMET.dat	InputDetails.dat
#echo "python MakeMasterReader.py "
#python MakeMasterReader.py 
#echo "root -l -b -q MasterReader.C "
#root -l -b -q MasterReader.C 
#mkdir Plots_El_Corr_MET00_${today}
#cp MasterReader.C second_step_code_Details.dat InputDetails.dat   *.png *.pdf *.root Plots_El_Corr_MET00_${today}
#source /home/ramkrishna/MyLocalWebsite/ImageHTMLcreateScript.sh /home/ramkrishna/PhD_New_Dir_16July2016/PhysicsAnalysis/aQGC_Analysis/aQGC_Plotting_Code/TreePlotter/Plots_El_Corr_MET00_${today}/  HTMLFiles/Plots_El_Corr_MET00_${today}.htm
#
#
#echo -e "\n\n=====================================================================\n\n"
#echo -e     "==========	Plots for muons: With Corr & MET Cut	=============="
#cp 	InputDetails_mu.dat	InputDetails.dat
#echo "python MakeMasterReader.py "
#python MakeMasterReader.py 
#echo "root -l -b -q MasterReader.C "
#root -l -b -q MasterReader.C 
#mkdir Plots_Mu_Corr_MET40_${today}
#cp MasterReader.C second_step_code_Details.dat InputDetails.dat   *.png *.pdf *.root Plots_Mu_Corr_MET40_${today}
#source /home/ramkrishna/MyLocalWebsite/ImageHTMLcreateScript.sh /home/ramkrishna/PhD_New_Dir_16July2016/PhysicsAnalysis/aQGC_Analysis/aQGC_Plotting_Code/TreePlotter/Plots_Mu_Corr_MET40_${today}/  HTMLFiles/Plots_Mu_Corr_MET40_${today}.htm
#
#
#echo -e "\n\n=====================================================================\n\n"
#echo -e     "==========	Plots for muons: Without Corr & MET Cut	=============="
#cp 	InputDetails_mu_NoCorr.dat	InputDetails.dat
#echo "python MakeMasterReader.py "
#python MakeMasterReader.py 
#echo "root -l -b -q MasterReader.C "
#root -l -b -q MasterReader.C 
#mkdir Plots_Mu_NoCorr_MET40_${today}
#cp MasterReader.C second_step_code_Details.dat InputDetails.dat   *.png *.pdf *.root Plots_Mu_NoCorr_MET40_${today}
#source /home/ramkrishna/MyLocalWebsite/ImageHTMLcreateScript.sh /home/ramkrishna/PhD_New_Dir_16July2016/PhysicsAnalysis/aQGC_Analysis/aQGC_Plotting_Code/TreePlotter/Plots_Mu_NoCorr_MET40_${today}/  HTMLFiles/Plots_Mu_NoCorr_MET40_${today}.htm
#
#
#echo -e "\n\n=====================================================================\n\n"
#echo -e     "==========	Plots for muons: With Corr & No MET Cut	=============="
#cp 	InputDetails_mu_NoMET.dat	InputDetails.dat
#echo "python MakeMasterReader.py "
#python MakeMasterReader.py 
#echo "root -l -b -q MasterReader.C "
#root -l -b -q MasterReader.C 
#mkdir Plots_Mu_Corr_MET00_${today}
#cp MasterReader.C second_step_code_Details.dat InputDetails.dat   *.png *.pdf *.root Plots_Mu_Corr_MET00_${today}
#source /home/ramkrishna/MyLocalWebsite/ImageHTMLcreateScript.sh /home/ramkrishna/PhD_New_Dir_16July2016/PhysicsAnalysis/aQGC_Analysis/aQGC_Plotting_Code/TreePlotter/Plots_Mu_Corr_MET00_${today}/  HTMLFiles/Plots_Mu_Corr_MET00_${today}.htm
#
#echo -e "\n\n=====================================================================\n\n"
#echo -e     "==========	Plots for muons: With Corr & MET Cut in Barrel	=============="
#cp 	InputDetails_mu_Barrel.dat	InputDetails.dat
#echo "python MakeMasterReader.py "
#python MakeMasterReader.py 
#echo "root -l -b -q MasterReader.C "
#root -l -b -q MasterReader.C 
#mkdir Plots_Mu_Corr_MET40_Barrel_${today}
#cp MasterReader.C second_step_code_Details.dat InputDetails.dat   *.png *.pdf *.root Plots_Mu_Corr_MET40_Barrel_${today}
#source /home/ramkrishna/MyLocalWebsite/ImageHTMLcreateScript.sh /home/ramkrishna/PhD_New_Dir_16July2016/PhysicsAnalysis/aQGC_Analysis/aQGC_Plotting_Code/TreePlotter/Plots_Mu_Corr_MET40_Barrel_${today}/  HTMLFiles/Plots_Mu_Corr_MET40_Barrel_${today}.htm
#
#echo -e "\n\n=====================================================================\n\n"
#echo -e     "==========	Plots for electrons: With Corr & MET Cut in Barrel	=============="
#cp 	InputDetails_el_Barrel.dat	InputDetails.dat
#echo "python MakeMasterReader.py "
#python MakeMasterReader.py 
#echo "root -l -b -q MasterReader.C "
#root -l -b -q MasterReader.C 
#mkdir Plots_El_Corr_MET40_Barrel_${today}
#cp MasterReader.C second_step_code_Details.dat InputDetails.dat   *.png *.pdf *.root Plots_El_Corr_MET40_Barrel_${today}
#source /home/ramkrishna/MyLocalWebsite/ImageHTMLcreateScript.sh /home/ramkrishna/PhD_New_Dir_16July2016/PhysicsAnalysis/aQGC_Analysis/aQGC_Plotting_Code/TreePlotter/Plots_El_Corr_MET40_Barrel_${today}/  HTMLFiles/Plots_El_Corr_MET40_Barrel_${today}.htm

#echo -e "\n\n=====================================================================\n\n"
#echo -e     "==========	Plots for muons: With Corr & MET Cut in EndCap	=============="
#cp 	InputDetails_mu_EndCap.dat	InputDetails.dat
#echo "python MakeMasterReader.py "
#python MakeMasterReader.py 
#echo "root -l -b -q MasterReader.C "
#root -l -b -q MasterReader_mu_EndCap.C 
#mkdir Plots_Mu_Corr_MET40_EndCap_${today}
#cp second_step_code_Details.dat InputDetails.dat  MasterReader.C *.png *.pdf *.root Plots_Mu_Corr_MET40_EndCap_${today}
#source /home/ramkrishna/MyLocalWebsite/ImageHTMLcreateScript.sh /home/ramkrishna/PhD_New_Dir_16July2016/PhysicsAnalysis/aQGC_Analysis/aQGC_Plotting_Code/TreePlotter/Plots_Mu_Corr_MET40_EndCap_${today}/  HTMLFiles/Plots_Mu_Corr_MET40_EndCap_${today}.htm

#echo -e "\n\n=====================================================================\n\n"
#echo -e     "==========	Plots for electrons: With Corr & MET Cut in EndCap	=============="
##cp 	InputDetails_el_EndCap.dat	InputDetails.dat
##echo "python MakeMasterReader.py "
##python MakeMasterReader.py 
#echo "root -l -b -q MasterReader.C "
#root -l -b -q MasterReader_el_EndCap.C
#mkdir Plots_El_Corr_MET40_EndCap_${today}
#cp MasterReader.C second_step_code_Details.dat InputDetails.dat   *.png *.pdf *.root Plots_El_Corr_MET40_EndCap_${today}
#source /home/ramkrishna/MyLocalWebsite/ImageHTMLcreateScript.sh /home/ramkrishna/PhD_New_Dir_16July2016/PhysicsAnalysis/aQGC_Analysis/aQGC_Plotting_Code/TreePlotter/Plots_El_Corr_MET40_EndCap_${today}/  HTMLFiles/Plots_El_Corr_MET40_EndCap_${today}.htm
