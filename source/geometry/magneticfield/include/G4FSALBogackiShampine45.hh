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
// G4FSALBogackiShampine45
//
// Class description:
//
// Bogacki-Shampine - 8 - 5(4) FSAL stepper

// Created: Somnath Banerjee, Google Summer of Code 2015, 26 May 2015
// Supervision: John Apostolakis, CERN
// --------------------------------------------------------------------
#ifndef G4FSAL_BOGACKI_SHAMPINE_45_HH
#define G4FSAL_BOGACKI_SHAMPINE_45_HH

#include "G4VFSALIntegrationStepper.hh"

class G4FSALBogackiShampine45 : public G4VFSALIntegrationStepper
{
  public:

    G4FSALBogackiShampine45(G4EquationOfMotion* EqRhs,
                            G4int numberOfVariables = 6,
                            G4bool primary = true);
    ~G4FSALBogackiShampine45();
    
    G4FSALBogackiShampine45(const G4FSALBogackiShampine45&) = delete;
    G4FSALBogackiShampine45& operator=(const G4FSALBogackiShampine45&) = delete;

    void Stepper( const G4double y[],
                  const G4double dydx[],
                        G4double h,
                        G4double yout[],
                        G4double yerr[],
                        G4double nextDydx[]) ;
    
    void interpolate( const G4double yInput[],
                      const G4double dydx[],
                            G4double yOut[],
                            G4double Step,
                            G4double tau ) ;

    G4double DistChord() const;
    inline G4int IntegratorOrder() const { return 4; }
    
  private :
    
    void PrepareConstants(); 
   
    // Working arrays -- used during stepping
    //
    G4double *ak2, *ak3, *ak4, *ak5, *ak6, *ak7, *ak8, *ak9, *ak10, *ak11,
             *DyDx, *yTemp, *yIn;
    G4double *pseudoDydx_for_DistChord;

    G4double fLastStepLength = -1.0;
    G4double *fLastInitialVector, *fLastFinalVector,
             *fLastDyDx, *fMidVector, *fMidError;
    // for DistChord calculations

    G4double b[12];     // Working array for interpolation
   
    G4FSALBogackiShampine45* fAuxStepper = nullptr;

    static G4bool fPreparedConstants;
    static G4double bi[12][7];
};

#endif
