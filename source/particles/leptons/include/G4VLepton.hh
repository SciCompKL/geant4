// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4VLepton.hh,v 1.2 1999/12/15 14:51:08 gunter Exp $
// GEANT4 tag $Name: geant4-02-00 $
//
// 
// ------------------------------------------------------------
//      GEANT 4 class header file 
//
//      For information related to this code contact:
//      CERN, CN Division, ASD group
//      History: first implementation, based on object model of
//      2nd December 1995, G.Cosmo
//  Revised, Hisaya Kurashige, 15 Dec 1996
//  Revised, Hisaya Kurashige, 24 Frb 1997
// ------------------------------------------------------------

#ifndef G4VLepton_h
#define G4VLepton_h 1

#include "G4ios.hh"
#include "globals.hh"
#include "G4Material.hh"

#include "G4PhysicsLogVector.hh"
#include "G4ParticleWithCuts.hh"

class G4VLepton : public G4ParticleWithCuts
{
  //  A virtual class for Leptons particles. It defines
  //  public methods which describe the behavior of a
  //  lepton.

  private:

      const G4VLepton & operator=(const G4VLepton &right);

  public:

      G4VLepton(const G4String&  aName,  
                G4double         mass,     
                G4double         width,
                G4double         charge,   
                G4int            iSpin,
                G4int            iParity,
                G4int            iConjugation,
                G4int            iIsospin,   
                G4int            iIsospinZ, 
                G4int            gParity,
                const G4String&  pType,
                G4int            lepton,
                G4int            baryon,
                G4int            encoding,
                G4bool           stable,
                G4double         lifetime,
                G4DecayTable     *decaytable)
	: G4ParticleWithCuts(aName, mass, width, charge, iSpin, iParity,
                               iConjugation, iIsospin, iIsospinZ, gParity,
                               pType, lepton, baryon, encoding, stable,
                               lifetime, decaytable) {};

      virtual ~G4VLepton() {};

      G4int operator==(const G4VLepton &right) const;
      G4int operator!=(const G4VLepton &right) const;

};

#endif
