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
/// \file electromagnetic/TestEm10/src/StackingAction.cc
/// \brief Implementation of the StackingAction class
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "StackingAction.hh"

#include "G4AnalysisManager.hh"
#include "G4Track.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4EmProcessSubType.hh"
#include "G4VProcess.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

StackingAction::StackingAction()
 : G4UserStackingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

StackingAction::~StackingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ClassificationOfNewTrack
StackingAction::ClassifyNewTrack(const G4Track* track)
{
  // do nothing if primary particle
  if (track->GetParentID() == 0) { return fUrgent; }

  //count secondary particles

  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  //
  //energy spectrum of secondaries
  //
  G4double energy = track->GetKineticEnergy();

  // Gamma 
  if (track->GetDefinition() == G4Gamma::Gamma()) {
    // XTR gamma
    // G4int processSubType 
    //   = track->GetCreatorProcess()->GetProcessSubType();
    // if ( processSubType == fTransitionRadiation) {
    G4String creatorProcessName = track->GetCreatorProcess()->GetProcessName();
    if (creatorProcessName.find("XTRadiator") != std::string::npos) {
      analysisManager->FillH1(2, energy);
    }

    // all gamma
    analysisManager->FillH1(3, energy);
  }

  // e-
  if (track->GetDefinition() == G4Electron::Electron()) {
    analysisManager->FillH1(4, energy);
  }
    
  return fUrgent;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
