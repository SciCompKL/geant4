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
/// \file medical/dna/range/include/DetectorConstruction.hh
/// \brief Definition of the DetectorConstruction class
//
// $Id: DetectorConstruction.hh 78723 2014-01-20 10:32:17Z gcosmo $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4LogicalVolume.hh"

class G4VPhysicalVolume;
class G4Material;
class G4MultiFunctionalDetector;
class DetectorMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DetectorConstruction: public G4VUserDetectorConstruction
{
public:
  DetectorConstruction();
  ~DetectorConstruction();

public:
  void SetNReplicaR(G4int);
  void SetNReplicaAzm(G4int);
  void SetAbsRadius(G4double);
  void SetAbsMaterial(G4String);
  void SetNPRadius(G4double);
  void SetNPMaterial(G4String);
  void SetTrackingCut(G4double);
  virtual G4VPhysicalVolume* Construct();

  inline G4double GetNReplicaR() const
  {
    return fNreplicaR;
  }
  inline G4double GetNReplicaAzm() const
  {
    return fNreplicaAzm;
  }
  inline G4double GetAbsRadius() const
  {
    return fAbsRadius;
  }
  inline G4double GetNPRadius() const
  {
    return fNPRadius;
  }
  inline G4Material* GetNPMaterial() const
  {
    return fNPMaterial;
  }
  inline G4double GetTrackingCut() const 
  {
  return fTrackingCut;
  }
  inline G4double GetNPMass() const
  {
    return fLogicalNP->GetMass();
  }

  inline G4MultiFunctionalDetector* GetMFDetector() const
  {
    return fMFD;
  }
  void PrintParameters() const;
  G4Region *GetTargetRegion(){return fRegion;}

private:
  void DefineMaterials();
  G4VPhysicalVolume* ConstructVolumes();

  G4int fNreplicaR;
  G4int fNreplicaAzm;
  G4double fTrackingCut;
  G4double fNPRadius;
  G4double fAbsRadius;
  G4Material* fNPMaterial;
  G4Material* fAbsMaterial;
  G4VPhysicalVolume* pWorld;
  G4VPhysicalVolume* fNP;
  G4VPhysicalVolume* fAbs;
  G4LogicalVolume* fLogicalNP;
  G4LogicalVolume* fLogicalAbs;
  DetectorMessenger* fDetectorMessenger;
  G4MultiFunctionalDetector* fMFD;
  G4Region   *fRegion;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

