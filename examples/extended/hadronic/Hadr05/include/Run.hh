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
/// \file Run.hh
/// \brief Definition of the Run class
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef Run_h
#define Run_h 1

#include "DetectorConstruction.hh"

#include "G4Run.hh"
#include "G4VProcess.hh"
#include "globals.hh"
#include <map>

class DetectorConstruction;
class G4ParticleDefinition;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class Run : public G4Run
{
  public:
    Run(DetectorConstruction*);
   ~Run() override;

  public:
    void SetPrimary(G4ParticleDefinition* particle, G4double energy);
    void CountProcesses(const G4VProcess* process);      
    void FillPerEvent(G4int,G4double,G4double);    
    void AddEnergyLeak (G4double eleak, G4int index);       
    void SumEnergyFlow (G4int plane, G4double Eflow);
                
    void Merge(const G4Run*) override;
    void EndOfRun();
     
  private:
    DetectorConstruction*  fDetector;
    G4ParticleDefinition*  fParticle;
    G4double               fEkin;
                           
    G4double fSumEAbs [kMaxAbsor], fSum2EAbs [kMaxAbsor]; 
    G4double fSumLAbs [kMaxAbsor], fSum2LAbs [kMaxAbsor];
    
    G4double fEnergyLeak[2];
    
    std::map<G4String,G4int> fProcCounter;            
    std::vector<G4double>    fEnergyFlow;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
