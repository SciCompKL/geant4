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
/// \file medical/DICOM/include/DicomNestedParamDetectorConstruction.hh
/// \brief Definition of the DicomNestedParamDetectorConstruction class
//

#ifndef DicomNestedParamDetectorConstruction_h
#define DicomNestedParamDetectorConstruction_h 1

#include "globals.hh"
#include "DicomDetectorConstruction.hh"

//*******************************************************
/// Construct the phantom using DicomPhantomParameterisationColour
///
/// History: 30.11.07  First version
/// \author  P. Arce
//*******************************************************

class DicomNestedParamDetectorConstruction : public DicomDetectorConstruction
{
public:

  DicomNestedParamDetectorConstruction();
  ~DicomNestedParamDetectorConstruction();

protected:
    //virtual void ConstructSDandField();
    
private:

  virtual void ConstructPhantom();

};

#endif

