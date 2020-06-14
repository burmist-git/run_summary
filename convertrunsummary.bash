#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2019 - LBS - (Single person developer.)                 #
# Tue May 14 13:16:50 JST 2019                                         #
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
source /home/burmist/root_v6.14.00/root-6.14.00-install/bin/thisroot.sh

function printHelp {
    echo " --> ERROR in input arguments "
    echo " [0] -d : default"
    echo " [0] -h : print help"
}

#Start
strStartArr=(
    RC.runtype
    DAQ.ExpNumber
    DAQ.RunNumber
    TTD.trig.type
    ECL.Luminosity.accel
    SKB.CGHINJ.BKSEL.NOB_SET
    SKB.CGLINJ.BKSEL.NOB_SET
    SKB.HER.beam.current
    SKB.LER.beam.current
    SKB.HER.beam.size.x
    SKB.HER.beam.size.y
    SKB.LER.beam.size.x
    SKB.LER.beam.size.y
    RC.PXD.used
    RC.SVD.used
    RC.CDC.used
    RC.TOP.used
    RC.ARICH.used
    RC.ECL.used
    RC.KLM.used
    RC.TRG.used
)
strStartNameArr=(
    runType
    expNumber
    runNumber
    triggerType
    delLumiStart
    nBunchesHER
    nBunchesLER
    beamIHERstart
    beamILERstart
    beam_x_HERstart
    beam_y_HERstart
    beam_x_LERstart
    beam_y_LERstart
    statusPXD
    statusSVD
    statusCDC
    statusTOP
    statusARICH
    statusECL
    statusKLM
    statusTRG
)
nnStartArr=${#strStartArr[@]}
let nnStartArr=nnStartArr-1

#End
strEndArr=(
    TTD.run.length
    TTD.trig.count.out
    ECL.Luminosity.accel
    ECL.Luminosity.det.total
    SKB.HER.beam.current
    SKB.LER.beam.current
    SKB.HER.beam.size.x
    SKB.HER.beam.size.y
    SKB.LER.beam.size.x
    SKB.LER.beam.size.y
)
strEndNameArr=(
    runLength
    numberOfEvents
    delLumiStop
    intLumOfRun
    beamIHERstop
    beamILERstop
    beam_x_HERstop
    beam_y_HERstop
    beam_x_LERstop
    beam_y_LERstop
)
nnEndArr=${#strEndArr[@]}
let nnEndArr=nnEndArr-1

sourceHome="/home/burmist/home2/KEK/run_summary/"

#inrawdataFolder=$sourceHome'rawdata/exp7/'
#outputrootFile=$sourceHome'rootdata/exp07/runSummary_exp07.root'
#outputrootFile=$sourceHome'rootdata/exp07/runSummary_exp07_test.root'
inrawdataFolder=$sourceHome'rawdata/exp3/'
outputrootFile=$sourceHome'rootdata/exp03/runSummary_exp03.root'
rm -rf $outputrootFile

if [ $# -eq 0 ] 
then    
    printHelp
else
    if [ "$1" = "-d" ]; then
	if [ $# -eq 1 ]
        then
	    #for inRawFileStart in `ls -l /home/burmist/home2/KEK/run_summary/rawdata/exp7/start_0007_003582.txt | awk '{print $9}' | xargs`;
	    #for inRawFileStart in `ls -l /home/burmist/home2/KEK/run_summary/rawdata/exp3/start_0003_003001.txt | awk '{print $9}' | xargs`;
	    for inRawFileStart in `ls -l $inrawdataFolder'start_'* | awk '{print $9}' | xargs`;
	    do
		inRawFileEnd=`(dirname $inRawFileStart)`/end_`echo $inRawFileStart | tail -c 16`
		if [ -f "$inRawFileStart" ]; then
		    if [ -f "$inRawFileEnd" ]; then
			echo $inRawFileStart
			echo $inRawFileEnd
			dataInfoStart=""
			for i in `seq 0 $nnStartArr`;
			do
			    dataInfon=`(grep ${strStartArr[$i]} $inRawFileStart | awk '{print $3}')`
			    nsizeDataInfon=`(echo "$dataInfon" | wc -w)`
			    if [ "$nsizeDataInfon" -eq 0 ];then
				#echo "nsizeDataInfon = $nsizeDataInfon"
				dataInfon="-999"
			    fi
			    dataInfoStart=$dataInfoStart" ${strStartNameArr[$i]} "$dataInfon
			done
			#
			startTime=`(grep DAQ.Date $inRawFileStart | awk '{print $3"-"$4}')`
			#echo "startTime = $startTime"
			#
			#echo $dataInfoStart
			dataInfoEnd=""
			for i in `seq 0 $nnEndArr`;
			do
			    dataInfon=`(grep ${strEndArr[$i]} $inRawFileEnd | awk '{print $3}')`
			    nsizeDataInfon=`(echo "$dataInfon" | wc -w)`
			    if [ "$nsizeDataInfon" -eq 0 ];then
				#echo "nsizeDataInfon = $nsizeDataInfon"
				dataInfon="-999"
			    fi
			    dataInfoEnd=$dataInfoEnd" ${strEndNameArr[$i]} "$dataInfon
			done
			#
			stopTime=`(grep DAQ.Date $inRawFileEnd | awk '{print $3"-"$4}')`
			#echo "stopTime = $stopTime"
			#
			#echo $dataInfoEnd
			dataInfo=$dataInfoStart" "$dataInfoEnd" startTime $startTime stopTime $stopTime"
			#echo $dataInfo
			#echo $dataInfo | wc -w
			$sourceHome/pushStructInRoot 0 $outputrootFile $dataInfo
		    fi
		fi
	    done
        else
            printHelp
        fi
    elif [ "$1" = "-h" ]; then        
        printHelp
    else
        printHelp
    fi
fi

#espeak "I have done"
