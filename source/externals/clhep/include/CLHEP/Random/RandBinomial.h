#include "CommonHeader.h"

// -*- C++ -*-
//
// -----------------------------------------------------------------------
//                             HEP Random
//                         --- RandBinomial ---
//                          class header file
// -----------------------------------------------------------------------

// Class defining methods for shooting binomial distributed random values,
// given a sample size n (default=1) and a probability p (default=0.5).
// Default values are used for operator()().
//
// Valid input values satisfy the relation n*min(p,1-p) > 0. When invalid
// values are presented, the code silently returns -1.0.

// =======================================================================
// John Marraffino - Created: 12th May 1998  Based on the C-Rand package
//                   by Ernst Stadlober and Franz Niederl of the Technical
//                   University of Graz, Austria.
// Gabriele Cosmo  - Removed useless methods and data: 5th Jan 1999
// M Fischler      - put and get to/from streams 12/10/04
// =======================================================================

#ifndef RandBinomial_h
#define RandBinomial_h 1

#include "CLHEP/Random/Random.h"
#include "CLHEP/Utility/memory.h"

namespace CLHEP {

/**
 * @author
 * @ingroup random
 */
class RandBinomial : public HepRandom {

public:

  inline RandBinomial ( HepRandomEngine& anEngine, long n=1,
                                                     G4double p=0.5 );
  inline RandBinomial ( HepRandomEngine* anEngine, long n=1,
                                                     G4double p=0.5 );
  // These constructors should be used to instantiate a RandBinomial
  // distribution object defining a local engine for it.
  // The static generator will be skipped using the non-static methods
  // defined below.
  // If the engine is passed by pointer the corresponding engine object
  // will be deleted by the RandBinomial destructor.
  // If the engine is passed by reference the corresponding engine object
  // will not be deleted by the RandBinomial destructor.

  virtual ~RandBinomial();
  // Destructor

  // Static methods to shoot random values using the static generator

  static inline G4double shoot();

  static G4double shoot( long n, G4double p );

  static void shootArray ( const int size, G4double* vect,
                            long n=1, G4double p=0.5 );

  //  Static methods to shoot random values using a given engine
  //  by-passing the static generator.

  static inline G4double shoot( HepRandomEngine* anEngine );

  static G4double shoot( HepRandomEngine* anEngine, 
                                  long n, G4double p );

  static void shootArray ( HepRandomEngine* anEngine, const int size,
                            G4double* vect, long n=1,
                            G4double p=0.5 );

  //  Methods using the localEngine to shoot random values, by-passing
  //  the static generator.

  inline G4double fire();

  G4double fire( long n, G4double p );
  
  void fireArray ( const int size, G4double* vect);
  void fireArray ( const int size, G4double* vect,
                   long n, G4double p );
  inline G4double operator()();
  inline G4double operator()( long n, G4double p );

  // Save and restore to/from streams
  
  std::ostream & put ( std::ostream & os ) const;
  std::istream & get ( std::istream & is );

  std::string name() const;
  HepRandomEngine & engine();

  static std::string distributionName() {return "RandBinomial";}  
  // Provides the name of this distribution class

private:

  static G4double genBinomial( HepRandomEngine *anEngine, long n, G4double p );

  std::shared_ptr<HepRandomEngine> localEngine;
  long defaultN;
  G4double defaultP;
 
};

}  // namespace CLHEP

#include "CLHEP/Random/RandBinomial.icc"

#endif
