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

// Author: Ivana Hrivnacova, 18/06/2013  (ivana@ipno.in2p3.fr)

#include "G4XmlNtupleManager.hh"
#include "G4XmlFileManager.hh"
#include "G4AnalysisManagerState.hh"
#include "G4AnalysisUtilities.hh"
#include "G4UnitsTable.hh"

#include "tools/ntuple_booking"

using namespace G4Analysis;

//_____________________________________________________________________________
G4XmlNtupleManager::G4XmlNtupleManager(const G4AnalysisManagerState& state)
 : G4TNtupleManager<tools::waxml::ntuple, std::ofstream>(state)
{}

//
// private methods
//

//_____________________________________________________________________________
void G4XmlNtupleManager::CreateTNtupleFromBooking(
  XmlNtupleDescription* ntupleDescription)
{
    // create a file for this ntuple
    if ( ! fFileManager->CreateNtupleFile(ntupleDescription) ) return;

    // create ntuple
    ntupleDescription->fNtuple
      = new tools::waxml::ntuple(
              *(ntupleDescription->fFile), G4cerr, ntupleDescription->fNtupleBooking);
    fNtupleVector.push_back(ntupleDescription->fNtuple);
}

//_____________________________________________________________________________
void G4XmlNtupleManager::FinishTNtuple(
  XmlNtupleDescription* ntupleDescription,
  G4bool /*fromBooking*/)

{
  // Do nothing if the base file name was not yet defined
  if ( ! fFileManager->GetFileName().size() ) return;

  // Create ntuple from booking
  if ( ! ntupleDescription->fNtuple ) {
    CreateTNtupleFromBooking(ntupleDescription);
  }

  // Return if creating ntuple failed
  if ( ! ntupleDescription->fNtuple ) {
    Warn("Creating ntuple has failed. ", fkClass, "FinishTNtuple");
    return;
  }

  // Write header
  G4String path = "/";
  path.append(fFileManager->GetNtupleDirectoryName());
  ntupleDescription->fNtuple
    ->write_header(path, ntupleDescription->fNtupleBooking.name(),
                   ntupleDescription->fNtupleBooking.title());
  fFileManager->LockDirectoryNames();
}
