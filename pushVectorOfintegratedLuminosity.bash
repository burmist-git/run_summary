#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2019 - LBS - (Single person developer.)                 #
# Wed May 22 15:26:12 JST 2019                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                                                                      #
# Input paramete:                                                      #
#                                                                      #
########################################################################

recorded=0
delivered=1

inRawDataFileExp07="./rawdata/exp_7.Luminosity"
inRawDataFileExp08="./rawdata/exp_8.Luminosity"

function printHelp {
    echo " --> ERROR in input arguments "
    echo " [0] -d     : default"
    echo " [0] -exp07 : push in root file the integrated luminosity of exp07"
    echo " [0] -exp08 : push in root file the integrated luminosity of exp08"
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
	outRoot=$inRawDataFileExp07'.root'
	rm -rf $outRoot
	vectorlength=`(more $inRawDataFileExp07 | awk '{print $1" "$2" "$3}' | xargs | wc -w)`
	datavector=`(more $inRawDataFileExp07 | awk '{print $1" "$2" "$3}' | xargs )`
	./runmdstana 4 $outRoot $recorded $vectorlength $datavector
    elif [ "$1" = "-exp08" ]; then
	outRoot=$inRawDataFileExp08'.root'
	rm -rf $outRoot
	vectorlength=`(more $inRawDataFileExp08 | awk '{print $1" "$2" "$3}' | xargs | wc -w)`
	datavector=`(more $inRawDataFileExp08 | awk '{print $1" "$2" "$3}' | xargs )`
	./runmdstana 4 $outRoot $recorded $vectorlength $datavector
    elif [ "$1" = "-l" ]; then
        printHelp
    elif [ "$1" = "-h" ]; then
        printHelp
    else
        printHelp
    fi
fi

#espeak "I have done"
