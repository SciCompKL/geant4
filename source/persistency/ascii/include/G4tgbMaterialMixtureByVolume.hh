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
// G4tgbMaterialMixtureByVolume
//
// Class description:
//
// Class to represent a material whose components are given by volume.

// Author: P.Arce, CIEMAT (November 2007)
// --------------------------------------------------------------------
#ifndef G4tgbMaterialMixtureByVolume_hh
#define G4tgbMaterialMixtureByVolume_hh 1

#include "globals.hh"
#include "G4tgbMaterialMixture.hh"

class G4tgbMaterialMixtureByVolume : public G4tgbMaterialMixture
{
  public:

    G4tgbMaterialMixtureByVolume();
    G4tgbMaterialMixtureByVolume(G4tgrMaterial* tgr);
    ~G4tgbMaterialMixtureByVolume();

    G4Material* BuildG4Material();
      // Return the associated G4Material and if does not exist build it

    void TransformToFractionsByWeight();

  private:

    std::vector<G4double> theFractionsByWeight;
};

#endif
