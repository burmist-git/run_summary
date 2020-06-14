#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2018 - LBS - (Single person developer.)                 #
# Tue Mar  6 20:15:29 JST 2018                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                 This script run the analysis class.                  #
#                                                                      #
# Input paramete:                                                      #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

#make -f Makefilemdstana clean; make -f Makefilemdstana runmdstana;

#Or analyse single root file 
inRootFilesExp03="./rootdata/exp03/runSummary_exp03.root"
inRootFilesExp07="./rootdata/exp07/runSummary_exp07.root"
outHistSingleFexp03="./rootdata/exp03/runSummary_exp03_hist.root"
outHistSingleFexp07="./rootdata/exp07/runSummary_exp07_hist.root"
inProcessingInfoRootFileexp07="./rawdata/exp7.offskim_mumu.processing.short.root"
inLuminosityInfoRootFileexp07="./rawdata/exp_7.Luminosity.root"

function printHelp {
    echo " --> ERROR in input arguments "
    echo " [0] -d         : single root file"
    echo " [0] -exp03     : analyze run summary of exp03"
    echo " [0] -exp07     : analyze run summary of exp07"
    echo " [0] -exp03proc : analyze run summary of exp03 with processing info"
    echo " [0] -exp07proc : analyze run summary of exp07 with processing info"
    echo " [0] -l         : list of root files"
    echo " [0] -h         : print help"
}

if [ $# -eq 0 ] 
then    
    printHelp
else
    if [ "$1" = "-d" ]; then
	./runmdstana 1 $inRootFilesExp03 $outHistSingleFexp03
	./runmdstana 1 $inRootFilesExp07 $outHistSingleFexp07
    elif [ "$1" = "-exp03" ]; then
	./runmdstana 1 $inRootFilesExp03 $outHistSingleFexp03
    elif [ "$1" = "-exp07" ]; then
	./runmdstana 1 $inRootFilesExp07 $outHistSingleFexp07
    elif [ "$1" = "-exp03proc" ]; then
	./runmdstana 2 $inRootFilesExp03 $outHistSingleFexp03 $inProcessingInfoRootFileexp03
    elif [ "$1" = "-exp07proc" ]; then
	./runmdstana 21 $inRootFilesExp07 $outHistSingleFexp07 $inProcessingInfoRootFileexp07 $inLuminosityInfoRootFileexp07
    elif [ "$1" = "-l" ]; then
        printHelp
    elif [ "$1" = "-h" ]; then
        printHelp
    else
        printHelp
    fi
fi

#espeak "I have done"
