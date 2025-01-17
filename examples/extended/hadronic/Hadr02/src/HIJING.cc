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
/// \file hadronic/Hadr02/src/HIJING.cc
/// \brief Implementation of the HIJING class methods
//
//---------------------------------------------------------------------------
//
// ClassName:   
//
// Author: 2012  Andrea Dotti
//   created from FTFP_BERT
//
// Modified:
// -  18-May-2021 Alberto Ribon : Migrated to non-templated physics list.
//
//----------------------------------------------------------------------------
//
#include <iomanip>   
#include <CLHEP/Units/SystemOfUnits.h>
#include "globals.hh"
#include "G4ios.hh"
#include "HIJING.hh"

#ifdef G4_USE_HIJING

#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4StoppingPhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4NeutronTrackingCut.hh"
#include "HadronPhysicsHIJING.hh"
#include "IonHIJINGPhysics.hh"


HIJING::HIJING( G4int ver ) {
  if ( ver > 0 ) {
    G4cout << "<<< Geant4 Physics List simulation engine: HIJING" << G4endl << G4endl;
  }
  defaultCutValue = 0.7*CLHEP::mm;  
  SetVerboseLevel( ver );
  RegisterPhysics( new G4EmStandardPhysics( ver ) );     // EM Physics
  RegisterPhysics( new G4EmExtraPhysics( ver ) );        // Synchroton Radiation & GN Physics
  RegisterPhysics( new G4DecayPhysics( ver ) );          // Decays
  RegisterPhysics( new G4HadronElasticPhysics( ver ) );  // Hadron Elastic physics  
  RegisterPhysics( new HadronPhysicsHIJING( ver ) );     // Hadron Inelastic physics
  RegisterPhysics( new G4StoppingPhysics( ver ) );       // Stopping Physics
  RegisterPhysics( new IonHIJINGPhysics( ver ) );        // Ion Physics
  RegisterPhysics( new G4NeutronTrackingCut( ver ) );    // Neutron tracking cut
}

#else  //i.e. G4_USE_HIJING not defined

HIJING::HIJING( G4int ) {
  G4ExceptionDescription de;
  de << "Support for HIJING not enabled" << G4endl;
  G4Exception( __FILE__, "HIJING-01", FatalException, de,
               "Code should be compiled with G4_USE_HIJING environment variable set." );
}

#endif  //G4_USE_HIJING
