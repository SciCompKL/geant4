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
// --------------------------------------------------------------
//   GEANT 4 - Underground Dark Matter Detector Advanced Example
//
//      For information related to this code contact: Alex Howard
//      e-mail: alexander.howard@cern.ch
// --------------------------------------------------------------
// Comments
//
//                  Underground Advanced
//               by A. Howard and H. Araujo 
//                    (27th November 2001)
//
// SteppingActionMessenger header
// --------------------------------------------------------------

#ifndef DMXSteppingActionMessenger_h
#define DMXSteppingActionMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class DMXSteppingAction;
class G4UIdirectory;
class G4UIcmdWithAString;


class DMXSteppingActionMessenger: public G4UImessenger {

  public:
    DMXSteppingActionMessenger(DMXSteppingAction*);
   ~DMXSteppingActionMessenger();
    
  void SetNewValue(G4UIcommand*, G4String);

  private:
    DMXSteppingAction*  steppingAction;   
  
    G4UIcmdWithAString*   colourNeutronCmd;
    G4UIcmdWithAString*   colourGammaCmd;
    G4UIcmdWithAString*   colourOpticalCmd;
    G4UIcmdWithAString*   colourChargedPlusCmd;
    G4UIcmdWithAString*   colourChargedMinusCmd;

};

#endif

