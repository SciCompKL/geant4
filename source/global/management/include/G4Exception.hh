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
// G4Exception
//
// Global error function prints string to G4cerr (or G4cout in case of
// warning). May abort program according to severity.

// Authors: G.Cosmo, M.Asai - May 1999 - First implementation
// --------------------------------------------------------------------
#ifndef G4EXCEPTION_HH
#define G4EXCEPTION_HH

#include "G4String.hh"
#include "G4VExceptionHandler.hh"
#include "G4ios.hh"

using G4ExceptionDescription = std::ostringstream;

inline const G4String G4ExceptionErrBannerStart()
{
  return "\n-------- EEEE ------- G4Exception-START -------- EEEE -------\n";
}
inline const G4String G4ExceptionWarnBannerStart()
{
  return "\n-------- WWWW ------- G4Exception-START -------- WWWW -------\n";
}

inline const G4String G4ExceptionErrBannerEnd()
{
  return "\n-------- EEEE ------- G4Exception-END -------- EEEE -------\n";
}
inline const G4String G4ExceptionWarnBannerEnd()
{
  return "\n-------- WWWW ------- G4Exception-END -------- WWWW -------\n";
}

extern void G4Exception(const char* originOfException,
                        const char* exceptionCode, G4ExceptionSeverity severity,
                        const char* description);

extern void G4Exception(const char* originOfException,
                        const char* exceptionCode, G4ExceptionSeverity severity,
                        G4ExceptionDescription& description);

extern void G4Exception(const char* originOfException,
                        const char* exceptionCode, G4ExceptionSeverity severity,
                        G4ExceptionDescription& description,
                        const char* comments);

#endif
