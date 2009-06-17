# $Id: GNUmakefile,v 1.6 2008/06/15 17:28:20 cirrone Exp $
# --------------------------------------------------------------
# GNUmakefile for examples module.  Gabriele Cosmo, 06/04/98.
# --------------------------------------------------------------

name := Hadrontherapy
G4TARGET := $(name)
G4EXLIB := true

ifndef G4INSTALL
  G4INSTALL = ../../..
endif

.PHONY: all
all: lib bin

include $(G4INSTALL)/config/architecture.gmk

# Setting the environment variable G4ROOTANALYSIS_USE enables ROOT
# based histogramming and disables the AIDA one.
ifdef G4ROOTANALYSIS_USE
CPPFLAGS += $(shell root-config --cflags) -DG4ROOTANALYSIS_USE
LDFLAGS  += $(shell root-config --glibs)
endif

include $(G4INSTALL)/config/binmake.gmk

ifdef G4ANALYSIS_USE 
endif
