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
// This is the *BASIC* version of IORT, a Geant4-based application
//
// Main Authors: G.Russo(a,b), C.Casarino*(c), G.C. Candiano(c), G.A.P. Cirrone(d), F.Romano(d)
// Contributor Authors: S.Guatelli(e)
// Past Authors: G.Arnetta(c), S.E.Mazzaglia(d)
//    
//   (a) Fondazione Istituto San Raffaele G.Giglio, Cefalù, Italy
//   (b) IBFM-CNR , Segrate (Milano), Italy
//   (c) LATO (Laboratorio di Tecnologie Oncologiche), Cefalù, Italy
//   (d) Laboratori Nazionali del Sud of the INFN, Catania, Italy
//   (e) University of Wallongong, Australia
//
//   *Corresponding author, email to carlo.casarino@polooncologicocefalu.it
//////////////////////////////////////////////////////////////////////////////////////////////
#ifndef IORTGeometryMessenger_h
#define IORTGeometryMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4String.hh"

class IORTGeometryController;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAString;
class G4UIcmdWithoutParameter;

class IORTGeometryMessenger: public G4UImessenger
{
public:
  IORTGeometryMessenger(IORTGeometryController* );
  ~IORTGeometryMessenger();
    
  void SetNewValue(G4UIcommand*, G4String );
    
private:

  // Pointer to the detector component
  IORTGeometryController* iortGeometryController;

  G4UIdirectory *changeTheGeometryDir;      ///> UI directory for the geometry control
  G4UIcmdWithAString *changeTheGeometryCmd; ///> Select the geometry
  G4UIcmdWithoutParameter *updateCmd;
};
#endif

