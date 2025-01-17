#include "CommonHeader.h"

// -*- C++ -*-
// CLASSDOC OFF
// ---------------------------------------------------------------------------
// CLASSDOC ON
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// ----------------------------------------------------------------------
//
//  EulerAngles.h 	EulerAngles class --
//  			Support class for PhysicsVectors classes
//
// History:
//   09-Jan-1998  WEB  FixedTypes is now found in ZMutility
//   12-Jan-1998  WEB  PI is now found in ZMutility
//   15-Jun-1998  WEB  Added namespace support
//   02-May-2000  WEB  No global using
//   26-Jul-2000  MF   CLHEP version
//
// ----------------------------------------------------------------------

#ifndef HEP_EULERANGLES_H
#define HEP_EULERANGLES_H

#include <iostream>

namespace CLHEP {

// Declarations of classes and global methods
class HepEulerAngles;
std::ostream & operator<<(std::ostream & os, const HepEulerAngles & aa);
std::istream & operator>>(std::istream & is,       HepEulerAngles & aa);

/**
 * @author
 * @ingroup vector
 */
class HepEulerAngles {

protected:
  typedef HepEulerAngles EA;       // just an abbreviation
  static G4double tolerance;      // to determine relative nearness

public:

  // ----------  Constructors:
  inline HepEulerAngles();
  inline HepEulerAngles( G4double phi, G4double theta, G4double psi );

  // ----------  Destructor, copy constructor, assignment:
  // use C++ defaults

  // ----------  Accessors:

public:
  inline  G4double  getPhi() const;
  inline  G4double  phi()    const;
  inline  EA &       setPhi( G4double phi );

  inline  G4double  getTheta() const;
  inline  G4double  theta()    const;
  inline  EA &       setTheta( G4double theta );

  inline  G4double  getPsi() const;
  inline  G4double  psi()    const;
  inline  EA &       setPsi( G4double psi );

  inline EA & set( G4double phi, G4double theta, G4double psi );

  // ----------  Operations:

  //   comparisons:
  inline int  compare   ( const EA & ea ) const;

  inline bool operator==( const EA & ea ) const;
  inline bool operator!=( const EA & ea ) const;
  inline bool operator< ( const EA & ea ) const;
  inline bool operator<=( const EA & ea ) const;
  inline bool operator> ( const EA & ea ) const;
  inline bool operator>=( const EA & ea ) const;

  //   relative comparison:
  inline static G4double getTolerance();
  inline static G4double setTolerance( G4double tol );

  bool isNear ( const EA & ea, G4double epsilon = tolerance ) const;
  G4double  howNear( const EA & ea ) const;

  // ----------  I/O:

  friend std::ostream & operator<<( std::ostream & os, const EA & ea );
  friend std::istream & operator>>( std::istream & is,       EA & ea );

  // ---------- Helper methods:

protected:
    G4double distance( const HepEulerAngles & ex ) const;

  // ----------  Data members:
protected:
  G4double phi_;
  G4double theta_;
  G4double psi_;

};  // HepEulerAngles

}  // namespace CLHEP

#include "CLHEP/Vector/EulerAngles.icc"

#endif // EULERANGLES_H
