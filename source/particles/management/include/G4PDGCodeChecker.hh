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
// G4PDGCodeChecker

// Author: Hisaya Kurashige, 17 August 1999
// --------------------------------------------------------------------
#ifndef G4PDGCodeChecker_hh
#define G4PDGCodeChecker_hh 1

#include "globals.hh"
#include "G4ios.hh"

class G4PDGCodeChecker 
{
  public:

    G4PDGCodeChecker();
   ~G4PDGCodeChecker();

    G4int CheckPDGCode(G4int code, const G4String& type);

    inline G4int GetQuarkContent(G4int flavor) const ;
    inline G4int GetAntiQuarkContent(G4int flavor) const;
  
    inline G4bool IsAntiParticle() const;

    inline G4int GetQuarkFlavor(G4int idx) const;

    inline G4int GetSpin() const;
    inline G4int GetExotic() const;
    inline G4int GetRadial() const;
    inline G4int GetMultiplet() const;

    G4bool CheckCharge(G4double charge) const;

    inline G4int GetVerboseLevel() const;
    inline void SetVerboseLevel(G4int verbose);

  protected:

    enum {NumberOfQuarkFlavor = 8};

  private: 

    void GetDigits(G4int code);
    G4int CheckForQuarks();
    G4int CheckForDiQuarks();
    G4int CheckForMesons();
    G4int CheckForBaryons();
    G4int CheckForNuclei();
  
  private:

    G4int verboseLevel = 0;

    G4int code = 0;
    G4String theParticleType = "";

    G4int higherSpin = 0;
    G4int exotic = 0;
    G4int radial = 0;
    G4int multiplet = 0;
    G4int quark1 = 0;
    G4int quark2 = 0;
    G4int quark3 = 0;
    G4int spin = 0;

    G4int theQuarkContent[NumberOfQuarkFlavor];
    G4int theAntiQuarkContent[NumberOfQuarkFlavor];
      // The number of quark (minus Sign means anti-quark) contents
      // The value of flavor is assigned as follows 
      //    0:d, 1:u, 2:s, 3:c, 
      //    4:b, 5:t, 6:l(down type quark) 7:h(up type quark)
};

// ------------------------
// Inline methods
// ------------------------

inline
G4int  G4PDGCodeChecker::GetQuarkContent(G4int flavor) const
{
  G4int value = 0;
  if ((flavor>=0)&&(flavor<NumberOfQuarkFlavor))
  {
    value = theQuarkContent[flavor];
  }
  return value;
}

inline
G4int  G4PDGCodeChecker::GetAntiQuarkContent(G4int flavor) const
{
  G4int value = 0;
  if ((flavor>=0)&&(flavor<NumberOfQuarkFlavor))
  {
    value = theAntiQuarkContent[flavor];
  }
  return value;
}


inline
G4int G4PDGCodeChecker::GetQuarkFlavor(G4int idx) const
{
  G4int value;
  if (idx ==0) value = quark1;
  else if (idx ==1) value = quark2;
  else if (idx ==2) value = quark3;
  else value = -1;
  return value;
}

inline
G4int G4PDGCodeChecker::GetExotic() const
{
  return exotic;
}

inline
G4int G4PDGCodeChecker::GetRadial() const
{
  return radial;
}

inline
G4int G4PDGCodeChecker::GetMultiplet() const
{
  return multiplet;
}

inline
G4int G4PDGCodeChecker::GetSpin() const
{
  return spin;
}

inline
G4bool G4PDGCodeChecker::IsAntiParticle() const
{
  return (code <0);
}

inline 
void G4PDGCodeChecker::SetVerboseLevel(G4int value)
{
  verboseLevel = value;
}

inline 
G4int G4PDGCodeChecker::GetVerboseLevel() const
{
  return verboseLevel;
}

#endif
