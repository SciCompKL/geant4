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
// Created on 2016/04/08
//
// Authors: D. Sakata, S. Incerti
//
// This class perform transmission term of volume plasmon excitation,
// based on Quinn Model, see Phys. Rev. vol 126, number 4 (1962)

#ifndef G4DNAPlasmonExcitation_h
#define G4DNAPlasmonExcitation_h 1

#include "G4VEmProcess.hh"

#include "G4DNAQuinnPlasmonExcitationModel.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4DNAPlasmonExcitation : public G4VEmProcess
{
public: 

  G4DNAPlasmonExcitation(const G4String& processName ="DNAPlasmonExcitation",
           G4ProcessType type = fElectromagnetic);

  virtual ~G4DNAPlasmonExcitation();

  virtual G4bool IsApplicable(const G4ParticleDefinition&);
  
  virtual void PrintInfo();

  //static G4int ProcessSubType()
  //{
  //  return 56;
  //}

protected:

  virtual void InitialiseProcess(const G4ParticleDefinition*);

private:
     
  G4bool       isInitialised;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  
#endif
