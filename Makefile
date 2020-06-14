########################################################################
#                                                                      #
# Copyright(C) 2019 - LBS - (Single person developer.)                 #
# Tue May 14 01:03:07 JST 2019                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# Script description:                                                  #
#                                                                      #
# Input paramete:                                                      #
#                                                                      #
# This software is provided "as is" without any warranty.              #
########################################################################

ROOTCFLAGS  = $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTLIBS    = $(shell $(ROOTSYS)/bin/root-config --libs)
ROOTGLIBS   = $(shell $(ROOTSYS)/bin/root-config --glibs)
ROOTLDFLAGS = $(shell $(ROOTSYS)/bin/root-config --ldflags)

LIBPUSHVEC=/home/burmist/home2/KEK/run_summary/pcstatlog_arichxx/obj/libpushVectorInRoot.so
INCPUSHVEC=/home/burmist/home2/KEK/run_summary/pcstatlog_arichxx/

# add xml files
ROOTLIBS += -lMLP -lXMLIO

OUTLIB = /home/burmist/home2/KEK/run_summary/obj/

CXX  = g++
CXX += -I./     
CXX += -I$(INCPUSHVEC)

CXXFLAGS  = -g -Wall -fPIC -Wno-deprecated
CXXFLAGS += $(ROOTCFLAGS)
CXXFLAGS += $(ROOTLIBS)
CXXFLAGS += $(ROOTGLIBS)
CXXFLAGS += $(ROOTLDFLAGS)
CXXFLAGSDICT = -g -Wall -fPIC -Wno-deprecated

PATHTOSHAREDLIB=$(OUTLIB)

.PHONY: clean all

#----------------------------------------------------#

all: makedir pushStructInRoot runmdstana read_arich_run_summary_xml

makedir:
	mkdir -p $(OUTLIB);

pushStructInRoot: pushStructInRoot.cc
	$(CXX) -DPUSHSTRUCTINROOT_MAIN -o $@ $< $(CXXFLAGS)

read_arich_run_summary_xml: libpushVectorInRoot read_arich_run_summary_xml.cc 
	$(CXX) -DREAD_ARICH_RUN_SUMMARY_XML_MAIN -o $@ read_arich_run_summary_xml.cc $(LIBPUSHVEC) $(CXXFLAGS)

runmdstana: libpushVectorInRoot Makefilemdstana processingInfoStr.h
	make -f Makefilemdstana

libpushVectorInRoot: pcstatlog_arichxx/Makefile
	make -C ./pcstatlog_arichxx/ -f Makefile obj/libpushVectorInRoot.so

clean: 
	rm -f *~
	rm -f .*~
	rm -rf $(OUTLIB)
	rm -f pushStructInRoot
	rm -f read_arich_run_summary_xml
	make -f Makefilemdstana clean
	make -C ./pcstatlog_arichxx/ -f Makefile clean
