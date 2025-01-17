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
//
// J. M. Quesada (August 2008).  
// Based  on previous work by V. Lara
//
// Modified:
// 20.08.2010 V.Ivanchenko added int Z and A and cleanup; added 
//                        G4ParticleDefinition to constructor,
//                        moved constructor and destructor to source,
//                        added inline methods

#ifndef G4PreCompoundIon_h
#define G4PreCompoundIon_h 1

#include "G4PreCompoundFragment.hh"

class G4PreCompoundIon : public G4PreCompoundFragment
{
public:

  G4PreCompoundIon(const G4ParticleDefinition*,
		   G4VCoulombBarrier * aCoulombBarrier);
  
  virtual ~G4PreCompoundIon();

  G4PreCompoundIon(const G4PreCompoundIon &right) = delete;
  const G4PreCompoundIon& operator =
  (const G4PreCompoundIon &right) = delete;
  G4bool operator==(const G4PreCompoundIon &right) const = delete;
  G4bool operator!=(const G4PreCompoundIon &right) const = delete;

protected:

  G4double ProbabilityDistributionFunction(G4double eKin, 
					   const G4Fragment&) override;

  G4double GetBeta() const override;

  virtual G4double GetRj(G4int NumberParticles, G4int NumberCharged) const = 0;
          
  virtual G4double FactorialFactor(G4int N, G4int P) const = 0;

  virtual G4double CoalescenceFactor(G4int A) const = 0; 

private:

  G4double fact;
};

#endif
