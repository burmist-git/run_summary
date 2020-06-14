#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2019 - LBS - (Single person developer.)                 #
# Mon May 20 00:17:39 JST 2019                                         #
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

sourceHome="/home/burmist/home2/KEK/run_summary/"
inProcessData=$sourceHome'rawdata/exp7.processing'

if [ $# -eq 0 ] 
then    
    printHelp
else
    if [ "$1" = "-d" ]; then


    elif [ "$1" = "-h" ]; then        
        printHelp
    else
        printHelp
    fi
fi

#espeak "I have done"
