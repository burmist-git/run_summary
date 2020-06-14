#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2019 - LBS - (Single person developer.)                 #
# Mon May 20 11:28:19 JST 2019                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                                                                      #
# Input paramete:                                                      #
#                                                                      #
########################################################################

offskim_bhabhaecl=0
offskim_dstar=1
offskim_mumu=2

inRawDataFile="./rawdata/exp7.offskim_mumu.processing.short"
outRoot="./rawdata/exp7.offskim_mumu.processing.short.root"
rm -rf $outRoot

function printHelp {
    echo " --> ERROR in input arguments "
    echo " [0] -d     : default"
    echo " [0] -exp03 : analyze run summary of exp03"
    echo " [0] -exp07 : analyze run summary of exp07"
    echo " [0] -h     : print help"
}

if [ $# -eq 0 ] 
then    
    printHelp
else
    if [ "$1" = "-d" ]; then
        printHelp
    elif [ "$1" = "-exp03" ]; then
        printHelp
    elif [ "$1" = "-exp07" ]; then
	vectorlength=`(more $inRawDataFile | awk '{print $1" "$2" "$3" "$4}' | xargs | wc -w)`
	datavector=`(more $inRawDataFile | awk '{print $1" "$2" "$3" "$4}' | xargs )`
	./runmdstana 3 $outRoot $offskim_mumu $vectorlength $datavector
    elif [ "$1" = "-l" ]; then
        printHelp
    elif [ "$1" = "-h" ]; then
        printHelp
    else
        printHelp
    fi
fi

#espeak "I have done"
