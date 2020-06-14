#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2019 - LBS - (Single person developer.)                 #
# Wed May 22 14:20:14 JST 2019                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                                                                      #
# Input paramete:                                                      #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

LC_TIME=en_US.UTF-8
#source /home/burmist/root_v6.14.00/root-6.14.00-install/bin/thisroot.sh

function printHelp {
    echo " --> ERROR in input arguments "
    echo " [0] -d : default"
    echo " [0] -h : print help"
}

function getListOfIntegratedLuminosity_bash {
    for i in `seq 1 $nnRunIDmax`;
    do
	intL=`(/group/belle2/group/detector/ECL/integrated_luminosity -e $1 $i | awk '{print $1}'| grep -v "10^33")`
        nsize_intL=`(echo "$intL" | wc -w)`		    
	if [ "$nsize_intL" -ne 0 ];then
	    if [ "$intL" != "0.0" ];then
       	    #echo "nsize_intL = $nsize_intL"
	    #intL="0.0"
       		echo "$1  $i  $intL"
	    fi
	fi	
    done
}

nnRunIDmax=10000
sourceHome="/home/belle2/burmist/basf2/run_summary/"

#inrawdataFolder=$sourceHome'rawdata/exp7/'
#outputrootFile=$sourceHome'rootdata/exp07/runSummary_exp07.root'
#outputrootFile=$sourceHome'rootdata/exp07/runSummary_exp07_test.root'
#inrawdataFolder=$sourceHome'rawdata/exp3/'
#outputrootFile=$sourceHome'rootdata/exp03/runSummary_exp03.root'
#rm -rf $outputrootFile

if [ $# -eq 0 ] 
then    
    printHelp
else
    if [ "$1" = "-d" ]; then
	expID=7
	getListOfIntegratedLuminosity_bash $expID | tee 'exp_'$expID'.Luminosity'
	expID=8
	getListOfIntegratedLuminosity_bash $expID | tee 'exp_'$expID'.Luminosity'
    elif [ "$1" = "-h" ]; then        
        printHelp
    else
        printHelp
    fi
fi

#espeak "I have done"
