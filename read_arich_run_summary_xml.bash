#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2019 - LBS - (Single person developer.)                 #
# Thu May 23 14:01:58 JST 2019                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                                                                      #
# Input paramete:                                                      #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

#Or analyse single root file 
inArichRunSummaryXMLFilesExp07="./rawdata/arich_run_summary_e0007.xml"
inArichRunSummaryXMLFilesExp08="./rawdata/arich_run_summary_e0008.xml"
inRootLumFileExp07="./rawdata/exp_7.Luminosity.root"
inRootLumFileExp08="./rawdata/exp_8.Luminosity.root"
outHistExp07="./rawdata/arich_run_summary_lum_e0007_hist.root"
outHistExp08="./rawdata/arich_run_summary_lum_e0008_hist.root"

function printHelp {
    echo " --> ERROR in input arguments "
    echo " [0] -d         : single root file"
    echo " [0] -exp07     : arich run summary exp07"
    echo " [0] -exp08     : arich run summary exp08"
    echo " [0] -exp07plot : plot arich run summary exp07"
    echo " [0] -exp08plot : plot arich run summary exp08"
    echo " [0] -h         : print help"
}

if [ $# -eq 0 ] 
then    
    printHelp
else
    if [ "$1" = "-d" ]; then
	runkeyID=1
	rm -rf $inArichRunSummaryXMLFilesExp07'.root'
	rm -rf $inArichRunSummaryXMLFilesExp08'.root'
	./read_arich_run_summary_xml $runkeyID $inArichRunSummaryXMLFilesExp07
	./read_arich_run_summary_xml $runkeyID $inArichRunSummaryXMLFilesExp08
    elif [ "$1" = "-exp07" ]; then
	runkeyID=1
	rm -rf $inArichRunSummaryXMLFilesExp07'.root'
	./read_arich_run_summary_xml $runkeyID $inArichRunSummaryXMLFilesExp07
    elif [ "$1" = "-exp08" ]; then
	runkeyID=1
	rm -rf $inArichRunSummaryXMLFilesExp08'.root'
	./read_arich_run_summary_xml $runkeyID $inArichRunSummaryXMLFilesExp08
    elif [ "$1" = "-exp07plot" ]; then
	runkeyID=2
	inrootARICHsumExp07=$inArichRunSummaryXMLFilesExp07'.root'
	./read_arich_run_summary_xml $runkeyID $inrootARICHsumExp07 $inRootLumFileExp07 $outHistExp07
    elif [ "$1" = "-exp08plot" ]; then
	runkeyID=2
	inrootARICHsumExp08=$inArichRunSummaryXMLFilesExp08'.root'
	./read_arich_run_summary_xml $runkeyID $inrootARICHsumExp08 $inRootLumFileExp08 $outHistExp08
    elif [ "$1" = "-h" ]; then
        printHelp
    else
        printHelp
    fi
fi

#espeak "I have done"
