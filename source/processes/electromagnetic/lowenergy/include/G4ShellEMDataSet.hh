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
//
// Author: Maria Grazia Pia (Maria.Grazia.Pia@cern.ch)
//
// History:
// -----------
// 31 Jul 2001   MGP                 Created
//  9 Mar 2008   MGP                 Cleaned up unreadable code modified by former developer
//                                   (Further clean-up needed)
// 15 Jul 2009   N.A.Karakatsanis    New methods added for loading logarithmic data
//                                   to enhance computing performance of interpolation 
//
// -------------------------------------------------------------------

// Class description:
// Low Energy Electromagnetic Physics
// Data set for an electromagnetic physics process
// A strategy pattern is used to encapsulate algorithms for data interpolation
// Further documentation available from http://www.ge.infn.it/geant4/lowE

// -------------------------------------------------------------------

#ifndef  G4SHELLEMDATASET_HH
#define  G4SHELLEMDATASET_HH 1

#include <vector>
#include <CLHEP/Units/SystemOfUnits.h>

#include "globals.hh"
#include "G4VEMDataSet.hh"

class G4VDataSetAlgorithm;

class G4ShellEMDataSet : public G4VEMDataSet 
{ 
public:
  explicit G4ShellEMDataSet(G4int Z, 
		   G4VDataSetAlgorithm* algo, 
		   G4double eUnit=CLHEP::MeV, 
		   G4double dataUnit=CLHEP::barn);
  virtual ~G4ShellEMDataSet();
 
  G4double FindValue(G4double energy, G4int componentId=0) const override;
  
  void PrintData(void) const override;

  const G4VEMDataSet*  GetComponent(G4int componentId) const override { return components[componentId]; }
  void AddComponent(G4VEMDataSet* dataSet) override { components.push_back(dataSet); }
  size_t NumberOfComponents(void) const override { return components.size(); }

  const G4DataVector& GetEnergies(G4int componentId) const override { return GetComponent(componentId)->GetEnergies(0); }
  const G4DataVector& GetData(G4int componentId) const override { return GetComponent(componentId)->GetData(0); }
  const G4DataVector& GetLogEnergies(G4int componentId) const override
  { return GetComponent(componentId)->GetLogEnergies(0); }
  const G4DataVector& GetLogData(G4int componentId) const override { return GetComponent(componentId)->GetLogData(0); }

  void SetEnergiesData(G4DataVector* energies, G4DataVector* data, G4int componentId) override;
  void SetLogEnergiesData(G4DataVector* energies,
			  G4DataVector* data,
			  G4DataVector* log_energies, 
			  G4DataVector* log_data,
			  G4int componentId) override;

  G4bool LoadData(const G4String& fileName) override;
  G4bool LoadNonLogData(const G4String& fileName) override;
  G4bool SaveData(const G4String& fileName) const override;
  G4double RandomSelect(G4int /*componentId = 0*/) const override { return -1.; };

  G4ShellEMDataSet(const G4ShellEMDataSet& copy) = delete;
  G4ShellEMDataSet& operator=(const G4ShellEMDataSet& right) = delete;

protected:
  G4double GetUnitEnergies() const { return unitEnergies; }
  G4double GetUnitData() const { return unitData; }
  const G4VDataSetAlgorithm* GetAlgorithm() const { return algorithm; }   
  void CleanUpComponents();

private:
  G4String FullFileName(const G4String& fileName) const;

  std::vector<G4VEMDataSet*> components;          // Owned pointers
  G4VDataSetAlgorithm* algorithm;           // Owned pointer 
  
  G4double unitEnergies;
  G4double unitData;
  G4int z;
};
#endif /* G4SHELLEMDATASET_HH */
