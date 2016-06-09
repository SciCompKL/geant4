//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * The following disclaimer summarizes all the specific disclaimers *
// * of contributors to this software. The specific disclaimers,which *
// * govern, are listed with their locations in:                      *
// *   http://cern.ch/geant4/license                                  *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * This  code  implementation is the  intellectual property  of the *
// * GEANT4 collaboration.                                            *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
//
// Code developed by:
// S. Agostinelli, F. Foppiano, S. Garelli , M. Tropeano, S.Guatelli
//
//    **********************************
//    *                                *
//    *     BrachyPhysicsList.cc       *
//    *                                *
//    **********************************
//
// $Id: BrachyPhysicsList.cc,v 1.9 2003/10/20 18:09:18 vnivanch Exp $
// GEANT4 tag $Name: geant4-06-00 $
//
#include "BrachyPhysicsList.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleWithCuts.hh"
#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"
#include "G4Material.hh"
#include "G4UnitsTable.hh"
#include "G4ios.hh"              


BrachyPhysicsList::BrachyPhysicsList():  G4VUserPhysicsList()
{
  defaultCutValue = 0.1*mm;
  cutForGamma     = defaultCutValue;
  cutForElectron  = defaultCutValue;
  cutForPositron  = defaultCutValue;
  
  SetVerboseLevel(1);
}

BrachyPhysicsList::~BrachyPhysicsList()
{
}

void BrachyPhysicsList::ConstructParticle()
{
  // In this method, static member functions should be called
  // for all particles which you want to use.
  // This ensures that objects of these particle types will be
  // created in the program. 

  ConstructBosons();
  ConstructLeptons();
}

void BrachyPhysicsList::ConstructBosons()
{ 
  // gamma
  G4Gamma::GammaDefinition();

}

void BrachyPhysicsList::ConstructLeptons()
{
  // leptons
  G4Electron::ElectronDefinition();
  G4Positron::PositronDefinition();
}

void BrachyPhysicsList::ConstructProcess()
{
  AddTransportation();
  ConstructEM();
}

#include "G4MultipleScattering.hh"
// gamma
#include "G4LowEnergyRayleigh.hh" 
#include "G4LowEnergyPhotoElectric.hh"
#include "G4LowEnergyCompton.hh"  
#include "G4LowEnergyGammaConversion.hh" 
// e-
#include "G4LowEnergyIonisation.hh" 
#include "G4LowEnergyBremsstrahlung.hh" 
// e+
#include "G4eIonisation.hh" 
#include "G4eBremsstrahlung.hh" 
#include "G4eplusAnnihilation.hh"

void BrachyPhysicsList::ConstructEM()
{
  theParticleIterator->reset();
  while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();
    
    //processes
    
    if (particleName == "gamma") {
      //gamma  
      lowePhot = new  G4LowEnergyPhotoElectric("LowEnPhotoElec");
      pmanager->AddDiscreteProcess(new G4LowEnergyRayleigh);
      pmanager->AddDiscreteProcess(lowePhot);
      pmanager->AddDiscreteProcess(new G4LowEnergyCompton);
      pmanager->AddDiscreteProcess(new G4LowEnergyGammaConversion);
      
    } else if (particleName == "e-") {
      //electron
      loweIon  = new G4LowEnergyIonisation("LowEnergyIoni");
      loweBrem = new G4LowEnergyBremsstrahlung("LowEnBrem");
    
      pmanager->AddProcess(new G4MultipleScattering, -1, 1,1);
      pmanager->AddProcess(loweIon,     -1, 2,2);
      pmanager->AddProcess(loweBrem,    -1,-1,3);      
      
    } else if (particleName == "e+") {
      //positron      
      pmanager->AddProcess(new G4MultipleScattering, -1, 1,1);
      pmanager->AddProcess(new G4eIonisation,        -1, 2,2);
      pmanager->AddProcess(new G4eBremsstrahlung,    -1,-1,3);
      pmanager->AddProcess(new G4eplusAnnihilation,   0,-1,4);      
      
    }
  }  
}

void BrachyPhysicsList::SetCuts()
{
  if (verboseLevel >0){
    G4cout << "BrachyPhysicsList::SetCuts:";
    G4cout << "CutLength : " << G4BestUnit(defaultCutValue,"Length") << G4endl;
  }  

  SetCutValue(cutForGamma, "gamma");
  SetCutValue(cutForElectron, "e-");
  SetCutValue(cutForPositron, "e+");
  
  if (verboseLevel>0) DumpCutValuesTable();
}

void BrachyPhysicsList::SetGammaLowLimit(G4double lowcut)
{
  SetGELowLimit(lowcut);
}

void BrachyPhysicsList::SetElectronLowLimit(G4double lowcut)
{
  SetGELowLimit(lowcut);
}

void BrachyPhysicsList::SetGELowLimit(G4double lowcut)
{
  if (verboseLevel >0){
    G4cout << "BrachyPhysicsList::SetCuts:";
    G4cout << "Gamma and Electron cut in energy: " << lowcut*MeV << " (MeV)" << G4endl;
  }  
  G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(lowcut,1e5);
}

void BrachyPhysicsList::SetGammaCut(G4double val)
{
  ResetCuts();
  cutForGamma = val;
}

void BrachyPhysicsList::SetElectronCut(G4double val)
{
  cutForElectron = val;
}

void BrachyPhysicsList::SetPositronCut(G4double val)
{
  cutForPositron = val;
}

void BrachyPhysicsList::SetLowEnSecPhotCut(G4double cut)
{  
  G4cout<<"Low energy secondary photons cut is now set to: "
	<<cut*MeV
        <<" (MeV)"<<G4endl;

  G4cout<<"for processes LowEnergyPhotoElectric, LowEnergyBremsstrahlung, LowEnergyIonisation"<<G4endl;

  lowePhot->SetCutForLowEnSecPhotons(cut);
  loweIon->SetCutForLowEnSecPhotons(cut);
  loweBrem->SetCutForLowEnSecPhotons(cut);
}

void BrachyPhysicsList::SetLowEnSecElecCut(G4double cut)
{  
  G4cout<<"Low energy secondary electrons cut is now set to: "
        <<cut*MeV
        <<" (MeV)"<<G4endl;
  G4cout<<"for processes LowEnergyIonisation"<<G4endl;
  loweIon->SetCutForLowEnSecElectrons(cut);
}