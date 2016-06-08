// This code implementation is the intellectual property of
// neutron_hp -- header file
// J.P. Wellisch, Nov-1996
// A prototype of the low energy neutron transport model.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4NeutronHPLCFissionFS.hh,v 1.3 1999/07/02 09:59:19 johna Exp $
// GEANT4 tag $Name: geant4-02-00 $
//
#ifndef G4NeutronHPLCFissionFS_h
#define G4NeutronHPLCFissionFS_h 1

#include "globals.hh"
#include "G4Track.hh"
#include "G4DynamicParticleVector.hh"
#include "G4NeutronHPFissionBaseFS.hh"

class G4NeutronHPLCFissionFS : public G4NeutronHPFissionBaseFS
{
  public:
  
  G4NeutronHPLCFissionFS(){ hasXsec = false; }
  ~G4NeutronHPLCFissionFS(){}
  void Init (G4double A, G4double Z, G4String & dirName, G4String & aFSType);
  G4DynamicParticleVector * ApplyYourself(G4int NNeutrons);
  G4NeutronHPFinalState * New() 
  {
   G4NeutronHPLCFissionFS * theNew = new G4NeutronHPLCFissionFS;
   return theNew;
  }
  
  private:
  G4ParticleChange * ApplyYourself(const G4Track & theTrack) { return NULL; }
    
};
#endif