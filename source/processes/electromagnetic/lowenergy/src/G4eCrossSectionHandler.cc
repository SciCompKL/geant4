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
// Author: Vladimir Ivanchenko
//
// History:
// -----------
// 1  Jun 2011   V.Ivanchenko  Created
//
// -------------------------------------------------------------------
#include "G4eCrossSectionHandler.hh"
#include "G4VDataSetAlgorithm.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
G4eCrossSectionHandler::G4eCrossSectionHandler(G4VDataSetAlgorithm* alg,
  G4double emin, G4double emax, G4int nbin): G4VCrossSectionHandler()
{ 
  G4VCrossSectionHandler::Initialise(alg, emin, emax, nbin);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4eCrossSectionHandler::~G4eCrossSectionHandler()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
std::vector<G4VEMDataSet*>*
G4eCrossSectionHandler::BuildCrossSectionsForMaterials(const G4DataVector&,
						       const G4DataVector*)
{
  std::vector<G4VEMDataSet*>* matCrossSections = new std::vector<G4VEMDataSet*>;
  return matCrossSections;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
