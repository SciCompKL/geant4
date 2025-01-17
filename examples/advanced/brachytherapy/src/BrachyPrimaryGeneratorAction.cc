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
//                 GEANT 4 - Brachytherapy example
// --------------------------------------------------------------
//
// Code developed by:
// S.Guatelli
//
//    ********************************************
//    *                                          *
//    *    BrachyPrimaryGeneratorAction.cc       *
//    *                                          *
//    ********************************************
//
//

#include "globals.hh"

#include "BrachyPrimaryGeneratorAction.hh"
#include "Randomize.hh"  
#include "G4AnalysisManager.hh"
#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"

BrachyPrimaryGeneratorAction::BrachyPrimaryGeneratorAction()
{
// Use the GPS to generate primary particles,
// Particle type, energy position, direction are specified in 
// macro files
 fGun = new G4GeneralParticleSource();
}

BrachyPrimaryGeneratorAction::~BrachyPrimaryGeneratorAction()
{
delete fGun;
}

void BrachyPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
 fGun -> GeneratePrimaryVertex(anEvent);

 if (fGun -> GetParticleDefinition()-> GetParticleName()== "gamma")
 { 
  auto analysisManager = G4AnalysisManager::Instance();
  G4double energy = fGun -> GetParticleEnergy();
  // Fill histogram with the energy spectrum of 
  // the photons emitted by the radionuclide
  // when modelling the photons as primary particles (not via radioactive decay)
   analysisManager -> FillH1(0, energy/keV);
 }
}


