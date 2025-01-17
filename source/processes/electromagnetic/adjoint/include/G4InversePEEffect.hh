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
////////////////////////////////////////////////////////////////////////////////
//  Class:   G4InversePEEffect
//  Author:         L. Desorgher
//  Organisation:   SpaceIT GmbH
//
//  Adjoint/reverse photo electric process
////////////////////////////////////////////////////////////////////////////////

#ifndef G4InversePEEffect_h
#define G4InversePEEffect_h 1

#include "globals.hh"
#include "G4VAdjointReverseReaction.hh"

class G4AdjointPhotoElectricModel;

class G4InversePEEffect : public G4VAdjointReverseReaction
{
 public:
  explicit G4InversePEEffect(G4String process_name,
                             G4AdjointPhotoElectricModel* aModel);
  ~G4InversePEEffect() override;

  void ProcessDescription(std::ostream&) const override;
  void DumpInfo() const override { ProcessDescription(G4cout); };

  G4InversePEEffect(G4InversePEEffect&) = delete;
  G4InversePEEffect& operator=(const G4InversePEEffect& right) = delete;
};

#endif
