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

// Author: Ivana Hrivnacova, 20/07/2017 (ivana@ipno.in2p3.fr)

#include "G4Hdf5AnalysisManager.hh"
#include "G4Hdf5FileManager.hh"
#include "G4Hdf5NtupleFileManager.hh"
#include "G4AnalysisManagerState.hh"
#include "G4AnalysisUtilities.hh"
#include "G4ThreadLocalSingleton.hh"
#include "G4Threading.hh"
#include "G4AutoLock.hh"

using namespace G4Analysis;

// mutex in a file scope

namespace {
  //Mutex to lock master manager when opening a file
  G4Mutex openFileMutex = G4MUTEX_INITIALIZER;
  //Mutex to lock master manager when closing a file
  G4Mutex closeFileMutex = G4MUTEX_INITIALIZER;
}

// G4Hdf5AnalysisManager* G4Hdf5AnalysisManager::fgMasterInstance = nullptr;
// G4ThreadLocal G4bool G4Hdf5AnalysisManager::fgIsInstance = false;

//_____________________________________________________________________________
G4Hdf5AnalysisManager* G4Hdf5AnalysisManager::Instance()
{
  static G4ThreadLocalSingleton<G4Hdf5AnalysisManager> instance;
  fgIsInstance = true;
  return instance.Instance();
}

//_____________________________________________________________________________
G4bool G4Hdf5AnalysisManager::IsInstance()
{
  return fgIsInstance;
}

//_____________________________________________________________________________
G4Hdf5AnalysisManager::G4Hdf5AnalysisManager()
 : G4ToolsAnalysisManager("Hdf5")
{
#ifdef G4MULTITHREADED
#ifndef H5_HAVE_THREADSAFE
    G4Exception("G4Hdf5AnalysisManager::G4Hdf5AnalysisManager",
                "Analysis_F001", FatalException,
                "Your HDF5 lib is not built with H5_HAVE_THREADSAFE.");
#endif
#endif

  if ( ! G4Threading::IsWorkerThread() ) fgMasterInstance = this;

  // File manager
  fFileManager = std::make_shared<G4Hdf5FileManager>(fState);
  SetFileManager(fFileManager);

  // Ntuple file manager
  fNtupleFileManager = std::make_shared<G4Hdf5NtupleFileManager>(fState);
  fNtupleFileManager->SetFileManager(fFileManager);
  fNtupleFileManager->SetBookingManager(fNtupleBookingManager);
}

//_____________________________________________________________________________
G4Hdf5AnalysisManager::~G4Hdf5AnalysisManager()
{
  if ( fState.GetIsMaster() ) fgMasterInstance = nullptr;
  fgIsInstance = false;
}

//
// protected methods
//

//_____________________________________________________________________________
G4bool G4Hdf5AnalysisManager::OpenFileImpl(const G4String& fileName)
{
  // Create ntuple manager(s)
  // and set it to base class which takes then their ownership
  SetNtupleManager(fNtupleFileManager->CreateNtupleManager());

  auto result = true;

  G4AutoLock lock(&openFileMutex);
  result &= fFileManager->OpenFile(fileName);
  result &= fNtupleFileManager->ActionAtOpenFile(fFileManager->GetFullFileName());
  lock.unlock();

  return result;
}

//_____________________________________________________________________________
G4bool G4Hdf5AnalysisManager::WriteImpl()
{
  auto result = true;

  Message(kVL4, "write", "files");

  if ( G4Threading::IsWorkerThread() )  {
    result &= G4ToolsAnalysisManager::Merge();
  }
  else {
    // Open all files registered with objects
    fFileManager->OpenFiles();

    // Write all histograms/profile on master
    result &= G4ToolsAnalysisManager::WriteImpl();
  }

  // Write ASCII if activated
  if ( IsAscii() ) {
    result &= WriteAscii(fFileManager->GetFileName());
  }

  Message(kVL3, "write", "files", "", result);

  return result;
}

//_____________________________________________________________________________
G4bool G4Hdf5AnalysisManager::CloseFileImpl(G4bool reset)
{
  auto result = true;

  G4AutoLock lock(&closeFileMutex);
  result &= fFileManager->CloseFiles();

  if ( reset ) {
    // reset data
    result = ResetImpl();
    if ( ! result ) {
      Warn("Resetting data failed", fkClass, "OpenDirectory");
    }
  }
  result &= fNtupleFileManager->ActionAtCloseFile(reset);

  lock.unlock();

  return result;
}

//_____________________________________________________________________________
G4bool G4Hdf5AnalysisManager::ResetImpl()
{
  auto result = true;

  result &= G4ToolsAnalysisManager::ResetImpl();
  if ( fNtupleFileManager != nullptr ) {
    result &= fNtupleFileManager->Reset();
  }

  return result;
}
