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
//---------------------------------------------------------------------------
//
// ClassName:   
//
// Author: 2007  Gunter Folger
//   created from G4HadronPhysicsFTFP
// Modified:
// 23.11.2005 G.Folger: migration to non static particles
// 08.06.2006 V.Ivanchenko: remove stopping
// 19.06.2008 G.Folger: change default for QE to NOT use Chips QE
// 20.09.2020 V.Ivanchenko change design using G4HadProcess utility
//
//----------------------------------------------------------------------------
//
#ifndef G4HadronPhysicsFTFP_BERT_h
#define G4HadronPhysicsFTFP_BERT_h 1

#include "globals.hh"

#include "G4VPhysicsConstructor.hh"

class G4HadronPhysicsFTFP_BERT : public G4VPhysicsConstructor
{
  public: 
    G4HadronPhysicsFTFP_BERT(G4int verbose =1);
    G4HadronPhysicsFTFP_BERT(const G4String& name, G4bool quasiElastic=false);
    virtual ~G4HadronPhysicsFTFP_BERT();

    void ConstructParticle() override;
    void ConstructProcess() override;

    // copy constructor and hide assignment operator
    G4HadronPhysicsFTFP_BERT(G4HadronPhysicsFTFP_BERT &) = delete;
    G4HadronPhysicsFTFP_BERT & operator =
    (const G4HadronPhysicsFTFP_BERT &right) = delete;

  protected:
    void CreateModels();
    virtual void Neutron();
    virtual void Proton();
    virtual void Pion();
    virtual void Kaon();
    virtual void Others();
    virtual void DumpBanner();

    G4double minFTFP_pion;
    G4double maxBERT_pion;
    G4double minFTFP_kaon;
    G4double maxBERT_kaon;
    G4double minFTFP_proton;
    G4double maxBERT_proton;
    G4double minFTFP_neutron;
    G4double maxBERT_neutron;
    G4double minBERT_proton;
    G4double minBERT_neutron;
    G4bool QuasiElastic;
};

#endif

