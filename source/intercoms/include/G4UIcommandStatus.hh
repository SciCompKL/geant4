#include "CommonHeader.h"

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
// G4UIcommandStatus
//
// Description:
//
// Enumeration of all states associated to a UI command

// Author: Makoto Asai (SLAC), 1998
// --------------------------------------------------------------------
#ifndef G4UIcommandStatus_hh
#define G4UIcommandStatus_hh 1

enum G4UIcommandStatus
{
  fCommandSucceeded         = 0,
  fCommandNotFound          = 100,
  fIllegalApplicationState  = 200,
  fParameterOutOfRange      = 300,
  fParameterUnreadable      = 400,
  fParameterOutOfCandidates = 500,
  fAliasNotFound            = 600
};

#endif
