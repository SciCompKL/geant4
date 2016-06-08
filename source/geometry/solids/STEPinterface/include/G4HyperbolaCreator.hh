// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4HyperbolaCreator.hh,v 1.2 2000/01/21 13:45:26 gcosmo Exp $
// GEANT4 tag $Name: geant4-02-00 $
//
// ----------------------------------------------------------------------
// Class G4HyperbolaCreator
//
// Class description:
//
//

// Authors: J.Sulkimo, P.Urban.
// Revisions by: L.Broglia, G.Cosmo.
//
// History:
//   18-Nov-1999: First step of re-engineering - G.Cosmo
// ----------------------------------------------------------------------
#ifndef G4HYPERBOLACREATOR_HH
#define G4HYPERBOLACREATOR_HH

#include "G4GeometryCreator.hh"

class G4HyperbolaCreator: private G4GeometryCreator 
{
  public:

  // Constructor & destructor

    G4HyperbolaCreator();
    ~G4HyperbolaCreator();

  // Member functions

    void CreateG4Geometry(STEPentity&);
    void CreateSTEPGeometry(void* G4obj);
    G4String Name() { return "Hyperbola"; }
    static G4HyperbolaCreator GetInstance() { return csc; }

  // Members
  
  private:

    static G4HyperbolaCreator csc;
};

#endif