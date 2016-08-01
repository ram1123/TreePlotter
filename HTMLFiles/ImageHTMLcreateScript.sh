#
#	This file creates a html file only for images. 
#	Template of this is copied from https://amassiro.web.cern.ch/amassiro/HWW/2016/Jul/17/SS/
#
#
#

if [ "$#" != "2" ]; then
	echo -e "\n\nPlease enter two arguments:\n\tFirst Argument : PATH\n\tSecond Argument : OutPutFileName.htm\n\n"
	exit 1
fi

rm -f temp.dat
for f in $1/*.htm; do
	#echo $f	
	echo "<P><h3><a href=\"$f\">$(basename $f)</a></h3></P>" >> temp.dat
	#echo "<div class='pic'> <h3><a href=\"$f\">$(basename $f)</a></h3><a href=\"$(basename $f)\"><img src=\"$f\" style=\"border: none; width: 400px; \"></a></div>" >> temp.dat
done
#cp Template_per.htm Template.htm
sed "/Template_Backup_Ram/r temp.dat" Template_per.htm > $2
rm temp.dat
