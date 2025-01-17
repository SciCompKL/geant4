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
// This example is provided by the Geant4-DNA collaboration
// Any report or published results obtained using the Geant4-DNA software 
// shall cite the following Geant4-DNA collaboration publications:
// Med. Phys. 37 (2010) 4692-4708
// Phys. Med. 31 (2015) 861-874
// The Geant4-DNA web site is available at http://geant4-dna.org
//
/// \file medical/dna/svalue/src/EventAction.cc
/// \brief Implementation of the EventAction class

#include "EventAction.hh"
#include "Run.hh"
#include "HistoManager.hh"

#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction()
:G4UserEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event*)
{    
 //energy deposited per event
 fCytoEdep = 0.;   
 fNuclEdep = 0.;   
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event*)
{
  //plot energy deposited per event
  //
  if (fCytoEdep > 0.) {
    
    Run* run
    = static_cast<Run*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());
    
    run->AddCytoEdep(fCytoEdep);
    
    //G4cout << "*** Edep cumulated in cytoplasm (eV) = " << run->GetCytoEdep()/eV << G4endl;
    
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();    
    analysisManager->FillH1(5,fCytoEdep);
  }  

  if (fNuclEdep > 0.) {
    
    Run* run
    = static_cast<Run*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());
    
    run->AddNuclEdep(fNuclEdep);
    
    //G4cout << "*** Edep cumulated in nucleus (eV) = " << run->GetNuclEdep()/eV << G4endl;
    
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();    
    analysisManager->FillH1(6,fNuclEdep);
  }  

}

