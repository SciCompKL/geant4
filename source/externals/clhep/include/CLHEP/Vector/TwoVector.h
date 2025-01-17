#include "CommonHeader.h"

// -*- C++ -*-
// CLASSDOC OFF
// ---------------------------------------------------------------------------
// CLASSDOC ON
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// Hep2Vector is a general 2-vector class defining vectors in two 
// dimension using G4double components.   It comes from the ZOOM
// PlaneVector class (the PhysicsVectors PlaneVector.h will typedef
// PlaneVector to Hep2Vector).
//
// .SS See Also
// ThreeVector.h
//
// .SS Authors
// John Marraffino and Mark Fischler
//

#ifndef HEP_TWOVECTOR_H
#define HEP_TWOVECTOR_H

#include <iostream>

#include "CLHEP/Vector/ThreeVector.h" 

namespace CLHEP {

// Declarations of classes and global methods
class Hep2Vector;
std::ostream & operator << (std::ostream &, const Hep2Vector &);
std::istream & operator >> (std::istream &, Hep2Vector &);
inline G4double operator * (const Hep2Vector & a,const Hep2Vector & b);
inline Hep2Vector operator * (const Hep2Vector & p, G4double a);
inline Hep2Vector operator * (G4double a, const Hep2Vector & p);
       Hep2Vector operator / (const Hep2Vector & p, G4double a);
inline Hep2Vector operator + (const Hep2Vector & a, const Hep2Vector & b);
inline Hep2Vector operator - (const Hep2Vector & a, const Hep2Vector & b);

/**
 * @author
 * @ingroup vector
 */
class Hep2Vector {

public:

  enum { X=0, Y=1, NUM_COORDINATES=2, SIZE=NUM_COORDINATES };
  // Safe indexing of the coordinates when using with matrices, arrays, etc.

  inline Hep2Vector( G4double x = 0.0, G4double y = 0.0 );
  // The constructor.

  inline Hep2Vector(const Hep2Vector & p);
  inline Hep2Vector(Hep2Vector && p) = default;
  // The copy and move constructors.

  explicit Hep2Vector( const Hep3Vector & );
  // "demotion" constructor"
  // WARNING -- THIS IGNORES THE Z COMPONENT OF THE Hep3Vector.
  //		SO IN GENERAL, Hep2Vector(v)==v WILL NOT HOLD!

  inline ~Hep2Vector();
  // The destructor.

  inline G4double x() const;
  inline G4double y() const;
  // The components in cartesian coordinate system.

         G4double operator () (int i) const;
  inline G4double operator [] (int i) const;
  // Get components by index.  0-based.

         G4double & operator () (int i);
  inline G4double & operator [] (int i);
  // Set components by index.  0-based.

  inline void setX(G4double x);
  inline void setY(G4double y);
  inline void set (G4double x, G4double y);
  // Set the components in cartesian coordinate system.

  inline G4double phi() const;
  // The azimuth angle.

  inline G4double mag2() const;
  // The magnitude squared.

  inline G4double mag() const;
  // The magnitude.

  inline G4double r() const;
  // r in polar coordinates (r, phi):  equal to mag().

  inline void setPhi(G4double phi);
  // Set phi keeping mag constant.

  inline void setMag(G4double r);
  // Set magnitude keeping phi constant.

  inline void setR(G4double r);
  // Set R keeping phi constant.  Same as setMag.

  inline void setPolar(G4double r, G4double phi);
  // Set by polar coordinates.

  inline Hep2Vector & operator = (const Hep2Vector & p);
  inline Hep2Vector & operator = (Hep2Vector && p) = default;
  // The copy and move assignment operators.

  inline bool operator == (const Hep2Vector & v) const;
  inline bool operator != (const Hep2Vector & v) const;
  // Comparisons.

  int compare (const Hep2Vector & v) const;
  bool operator > (const Hep2Vector & v) const;
  bool operator < (const Hep2Vector & v) const;
  bool operator>= (const Hep2Vector & v) const;
  bool operator<= (const Hep2Vector & v) const;
  // dictionary ordering according to y, then x component

  static inline G4double getTolerance();
  static G4double setTolerance(G4double tol);

  G4double howNear (const Hep2Vector &p) const;
  bool isNear  (const Hep2Vector & p, G4double epsilon=tolerance) const;

  G4double howParallel (const Hep2Vector &p) const;
  bool isParallel 
		(const Hep2Vector & p, G4double epsilon=tolerance) const;

  G4double howOrthogonal (const Hep2Vector &p) const;
  bool isOrthogonal
		(const Hep2Vector & p, G4double epsilon=tolerance) const;

  inline Hep2Vector & operator += (const Hep2Vector &p);
  // Addition.

  inline Hep2Vector & operator -= (const Hep2Vector &p);
  // Subtraction.

  inline Hep2Vector operator - () const;
  // Unary minus.

  inline Hep2Vector & operator *= (G4double a);
  // Scaling with real numbers.

  inline Hep2Vector unit() const;
  // Unit vector parallel to this.

  inline Hep2Vector orthogonal() const;
  // Vector orthogonal to this.

  inline G4double dot(const Hep2Vector &p) const;
  // Scalar product.

  inline G4double angle(const Hep2Vector &) const;
  // The angle w.r.t. another 2-vector.

  void rotate(G4double);
  // Rotates the Hep2Vector.

  operator Hep3Vector () const;
  // Cast a Hep2Vector as a Hep3Vector.

  // The remaining methods are friends, thus defined at global scope:
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  friend std::ostream & operator<< (std::ostream &, const Hep2Vector &);
  // Output to a stream.

  inline friend G4double operator * (const Hep2Vector & a,
				   const Hep2Vector & b);
  // Scalar product.

  inline friend Hep2Vector operator * (const Hep2Vector & p, G4double a);
  // v*c

  inline friend Hep2Vector operator * (G4double a, const Hep2Vector & p);
  // c*v

         friend Hep2Vector operator / (const Hep2Vector & p, G4double a);
  // v/c

  inline friend Hep2Vector operator + (const Hep2Vector & a,
				       const Hep2Vector & b);
  // v1+v2

  inline friend Hep2Vector operator - (const Hep2Vector & a,
				        const Hep2Vector & b);
  // v1-v2

  enum { ZMpvToleranceTicks = 100 };

private:

  G4double dx;
  G4double dy;
  // The components.

  static G4double tolerance;
  // default tolerance criterion for isNear() to return true.

};  // Hep2Vector

static const Hep2Vector X_HAT2(1.0, 0.0);
static const Hep2Vector Y_HAT2(0.0, 1.0);

}  // namespace CLHEP

#include "CLHEP/Vector/TwoVector.icc"

#endif /* HEP_TWOVECTOR_H */
