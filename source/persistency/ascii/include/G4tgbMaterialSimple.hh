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
// G4tgbMaterialSimple
//
// Class description:
//
// Class to represent a simple material definition.

// Author: P.Arce, CIEMAT (November 2007)
// --------------------------------------------------------------------
#ifndef G4tgbMaterialSimple_hh
#define G4tgbMaterialSimple_hh 1

#include <iostream>

#include "globals.hh"
#include "G4tgbMaterial.hh"

class G4tgbMaterialSimple : public G4tgbMaterial
{
  public:

    G4tgbMaterialSimple();
    ~G4tgbMaterialSimple();

    G4tgbMaterialSimple(G4tgrMaterial* tgr);
      // Fill the data interpreting the list of words read 'wl'

    friend std::ostream& operator<<(std::ostream&, const G4tgbMaterialSimple&);

    G4Material* BuildG4Material();
      // Return the associated G4Material and if does not exist build it

    G4double GetZ() const { return theZ; }
    G4double GetA() const { return theA; }

  private:

    G4double theZ = 0.0;
    G4double theA = 0.0;
};

#endif
