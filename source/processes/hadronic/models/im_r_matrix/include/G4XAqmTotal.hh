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

#ifndef G4XAqmTotal_hh
#define G4XAqmTotal_hh

#include "globals.hh"
#include "G4VCrossSectionSource.hh"
#include "G4CrossSectionVector.hh"

class G4KineticTrack;

class G4XAqmTotal : public G4VCrossSectionSource
{

public:

  G4XAqmTotal();

  virtual ~G4XAqmTotal();

  G4bool operator==(const G4XAqmTotal &right) const;
  G4bool operator!=(const G4XAqmTotal &right) const;

  virtual G4double CrossSection(const G4KineticTrack& trk1, const G4KineticTrack& trk2) const;
 
  virtual const G4CrossSectionVector* GetComponents() const { return 0; }

  virtual G4bool IsValid(G4double e) const;

  virtual G4String Name() const;


protected:


private:  

  G4XAqmTotal(const G4XAqmTotal &right);
  const G4XAqmTotal& operator=(const G4XAqmTotal &right);
  
  static const G4double _lowLimit;
  static const G4double _highLimit;
  
};

#endif


















