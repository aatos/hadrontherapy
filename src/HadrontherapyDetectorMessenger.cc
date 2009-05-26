//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: HadrontherapyDetectorMessenger.cc;
// ----------------------------------------------------------------------------
//                 GEANT 4 - Hadrontherapy example
// ----------------------------------------------------------------------------
// Code developed by:
//
// G.A.P. Cirrone(a)*, F. Di Rosa(a), S. Guatelli(b), G. Russo(a)
// 
// (a) Laboratori Nazionali del Sud 
//     of the INFN, Catania, Italy
// (b) INFN Section of Genova, Genova, Italy
// 
// * cirrone@lns.infn.it
// ----------------------------------------------------------------------------

#include "HadrontherapyDetectorMessenger.hh"
#include "HadrontherapyDetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"

HadrontherapyDetectorMessenger::HadrontherapyDetectorMessenger(HadrontherapyDetectorConstruction* detector)
  :hadrontherapyDetector(detector)

{
	changeTheBeamLineDir = new G4UIdirectory("/ChangeBeamLine/");
	changeTheBeamLineDir -> SetGuidance("Command to change the transport beam line");
	
	changeTheBeamLineNameCmd = new G4UIcmdWithAString("/ChangeBeamLine/beamLineName",this);
	changeTheBeamLineNameCmd -> SetGuidance("Insert the name of the beam line you want simulate");
	changeTheBeamLineNameCmd -> SetParameterName("List",false);
	changeTheBeamLineNameCmd -> AvailableForStates(G4State_PreInit); 
	
  modulatorDir = new G4UIdirectory("/modulator/");
  modulatorDir -> SetGuidance("Command to rotate the modulator wheel");

  beamLineDir = new G4UIdirectory("/beamLine/");
  beamLineDir -> SetGuidance("set specification of range shifter");  
 
  rangeShifterDir = new G4UIdirectory("/beamLine/RangeShifter/");
  rangeShifterDir -> SetGuidance("set specification of range shifter");  

  firstScatteringFoilDir = new G4UIdirectory("/beamLine/ScatteringFoil1/");
  firstScatteringFoilDir -> SetGuidance("set specification of first scattering foil");  
 
  secondScatteringFoilDir = new G4UIdirectory("/beamLine/ScatteringFoil2/");
  secondScatteringFoilDir -> SetGuidance("set specification of second scattering foil");  
 
  rangeStopperDir = new G4UIdirectory("/beamLine/Stopper/");
  rangeStopperDir -> SetGuidance("set specification of stopper");  

  finalCollimatorDir = new G4UIdirectory("/beamLine/FinalCollimator/");
  finalCollimatorDir -> SetGuidance("set specification of final collimator");  

  modulatorAngleCmd = new G4UIcmdWithADoubleAndUnit("/modulator/angle",this);
  modulatorAngleCmd -> SetGuidance("Set Modulator Angle");
  modulatorAngleCmd -> SetParameterName("Size",false);
  modulatorAngleCmd -> SetRange("Size>=0.");
  modulatorAngleCmd -> SetUnitCategory("Angle");  
  modulatorAngleCmd -> AvailableForStates(G4State_Idle);
  
  rangeShifterMatCmd = new G4UIcmdWithAString("/beamLine/RangeShifter/RSMat",this);
  rangeShifterMatCmd -> SetGuidance("Set material of range shifter");
  rangeShifterMatCmd -> SetParameterName("choice",false);
  rangeShifterMatCmd -> AvailableForStates(G4State_Idle);
  
  rangeShifterXSizeCmd = new G4UIcmdWithADoubleAndUnit("/beamLine/RangeShifter/thickness",this);
  rangeShifterXSizeCmd -> SetGuidance("Set half of the thickness of range shifter along X axis");
  rangeShifterXSizeCmd -> SetParameterName("Size",false);
  rangeShifterXSizeCmd -> SetDefaultUnit("mm");  
  rangeShifterXSizeCmd -> SetUnitCandidates("mm cm m");  
  rangeShifterXSizeCmd -> AvailableForStates(G4State_Idle);
  
  rangeShifterXPositionCmd = new G4UIcmdWithADoubleAndUnit("/beamLine/RangeShifter/position",this);
  rangeShifterXPositionCmd -> SetGuidance("Set position of range shifter");
  rangeShifterXPositionCmd -> SetParameterName("Size",false);
  rangeShifterXPositionCmd -> SetDefaultUnit("mm");  
  rangeShifterXPositionCmd -> SetUnitCandidates("mm cm m");  
  rangeShifterXPositionCmd -> AvailableForStates(G4State_Idle);
  
  firstScatteringFoilXSizeCmd = new G4UIcmdWithADoubleAndUnit("/beamLine/ScatteringFoil1/thickness",this);
  firstScatteringFoilXSizeCmd -> SetGuidance("Set hlaf thickness of first scattering foil");
  firstScatteringFoilXSizeCmd -> SetParameterName("Size",false);
  firstScatteringFoilXSizeCmd -> SetDefaultUnit("mm");  
  firstScatteringFoilXSizeCmd -> SetUnitCandidates("mm cm m");  
  firstScatteringFoilXSizeCmd -> AvailableForStates(G4State_Idle);
  
  secondScatteringFoilXSizeCmd = new G4UIcmdWithADoubleAndUnit("/beamLine/ScatteringFoil2/thickness",this);
  secondScatteringFoilXSizeCmd -> SetGuidance("Set half thickness of second scattering foil");
  secondScatteringFoilXSizeCmd -> SetParameterName("Size",false);
  secondScatteringFoilXSizeCmd -> SetDefaultUnit("mm");  
  secondScatteringFoilXSizeCmd -> SetUnitCandidates("mm cm m");  
  secondScatteringFoilXSizeCmd -> AvailableForStates(G4State_Idle);
  
  outerRadiusStopperCmd = new G4UIcmdWithADoubleAndUnit("/beamLine/Stopper/outRadius",this);
  outerRadiusStopperCmd -> SetGuidance("Set size of outer radius");
  outerRadiusStopperCmd -> SetParameterName("Size",false);
  outerRadiusStopperCmd -> SetDefaultUnit("mm");  
  outerRadiusStopperCmd -> SetUnitCandidates("mm cm m");  
  outerRadiusStopperCmd -> AvailableForStates(G4State_Idle);
  
  innerRadiusFinalCollimatorCmd = new G4UIcmdWithADoubleAndUnit("/beamLine/FinalCollimator/halfInnerRad",this);
  innerRadiusFinalCollimatorCmd -> SetGuidance("Set size of inner radius ( max 21.5 mm)");
  innerRadiusFinalCollimatorCmd -> SetParameterName("Size",false);
  innerRadiusFinalCollimatorCmd -> SetDefaultUnit("mm");  
  innerRadiusFinalCollimatorCmd -> SetUnitCandidates("mm cm m");  
  innerRadiusFinalCollimatorCmd -> AvailableForStates(G4State_Idle);
}

HadrontherapyDetectorMessenger::~HadrontherapyDetectorMessenger()
{ 
  delete innerRadiusFinalCollimatorCmd;  
  delete outerRadiusStopperCmd;  
  delete secondScatteringFoilXSizeCmd; 
  delete firstScatteringFoilXSizeCmd; 
  delete rangeShifterXPositionCmd;
  delete rangeShifterXSizeCmd;
  delete rangeShifterMatCmd;
  delete modulatorAngleCmd;
  delete finalCollimatorDir; 
  delete rangeStopperDir;
  delete secondScatteringFoilDir;
  delete firstScatteringFoilDir; 
  delete rangeShifterDir;  
  delete beamLineDir; 
  delete modulatorDir;   
}

void HadrontherapyDetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  if( command == modulatorAngleCmd )
    { hadrontherapyDetector -> SetModulatorAngle
           (modulatorAngleCmd -> GetNewDoubleValue(newValue));}

  if( command == rangeShifterMatCmd )
    { hadrontherapyDetector -> SetRSMaterial(newValue);}

  if( command == rangeShifterXSizeCmd )
    { hadrontherapyDetector -> SetRangeShifterXSize
            (rangeShifterXSizeCmd -> GetNewDoubleValue(newValue));}

  if( command == rangeShifterXPositionCmd )
    { hadrontherapyDetector -> SetRangeShifterXPosition
                  (rangeShifterXPositionCmd -> GetNewDoubleValue(newValue));}

  if( command == firstScatteringFoilXSizeCmd )
    { hadrontherapyDetector -> SetFirstScatteringFoilSize
                  (firstScatteringFoilXSizeCmd -> GetNewDoubleValue(newValue));}

  if( command == secondScatteringFoilXSizeCmd )
    { hadrontherapyDetector -> SetSecondScatteringFoilSize
                  (secondScatteringFoilXSizeCmd -> GetNewDoubleValue(newValue));}

  if( command == outerRadiusStopperCmd )
    { hadrontherapyDetector -> SetOuterRadiusStopper(
                    outerRadiusStopperCmd -> GetNewDoubleValue(newValue));}

  if( command == innerRadiusFinalCollimatorCmd )
    { hadrontherapyDetector -> SetInnerRadiusFinalCollimator
                  (innerRadiusFinalCollimatorCmd -> GetNewDoubleValue(newValue));}
}

