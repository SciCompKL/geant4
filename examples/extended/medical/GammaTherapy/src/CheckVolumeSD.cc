//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * The following disclaimer summarizes all the specific disclaimers *
// * of contributors to this software. The specific disclaimers,which *
// * govern, are listed with their locations in:                      *
// *   http://cern.ch/geant4/license                                  *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * This  code  implementation is the  intellectual property  of the *
// * GEANT4 collaboration.                                            *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
// -------------------------------------------------------------
//
//      ---------- CheckVolumeSD -------------
//
//  Modified:
//
// -------------------------------------------------------------

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "CheckVolumeSD.hh"

#include "G4RunManager.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Track.hh"
#include "G4Positron.hh"
#include "globals.hh"
#include "Histo.hh"
#include "G4Gamma.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

CheckVolumeSD::CheckVolumeSD(const G4String& name)
 :G4VSensitiveDetector(name),
  theHisto(Histo::GetPointer()),
  evno(0)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

CheckVolumeSD::~CheckVolumeSD()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void CheckVolumeSD::Initialize(G4HCofThisEvent*)
{
  evno++;
  if(0 < theHisto->GetVerbose())
    G4cout << "CheckVolumeSD: Begin Of Event # " << evno << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4bool CheckVolumeSD::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
  const G4Track* track = aStep->GetTrack();
  G4double e = track->GetKineticEnergy();
  if (track->GetDefinition() == G4Gamma::Gamma()) {
    G4ThreeVector p = track->GetPosition();
    G4double x = p.x();
    G4double y = p.y();
    G4double r = std::sqrt(x*x + y*y);
    theHisto->AddGamma(e,r);
  }
  if(1 < theHisto->GetVerbose()) {
      G4cout << "CheckVolumeSD: energy = " << e/MeV
                  << G4endl;
  }
  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void CheckVolumeSD::EndOfEvent(G4HCofThisEvent*)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void CheckVolumeSD::clear()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....


void CheckVolumeSD::PrintAll()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

