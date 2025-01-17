#include "CommonHeader.h"

// -*- C++ -*-
// ---------------------------------------------------------------------------
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// History:
// 09.09.96 E.Chernyaev - initial version
// 12.06.01 E.Chernyaev - CLHEP-1.7: introduction of BasicVector3D to decouple
//                        the functionality from CLHEP::Hep3Vector
// 01.04.03 E.Chernyaev - CLHEP-1.9: template version
//

#ifndef HEP_POINT3D_H
#define HEP_POINT3D_H

#include <iosfwd>
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Geometry/BasicVector3D.h"

namespace HepGeom {

  class Transform3D;

  /**
   * Geometrical 3D Point.
   * This is just a declaration of the class needed to define
   * specializations Point3D<G4float> and Point3D<G4double>.
   *
   * @ingroup geometry
   * @author Evgeni Chernyaev <Evgueni.Tcherniaev@cern.ch>
   */
  template<class T>
  class Point3D : public BasicVector3D<T> {};

  /**
   * Geometrical 3D Point with components of G4float type.
   *
   * @author Evgeni Chernyaev <Evgueni.Tcherniaev@cern.ch>
   * @ingroup geometry
   */
  template<>
  class Point3D<G4float> : public BasicVector3D<G4float> {
  public:
    /**
     * Default constructor. */
    Point3D() = default;

    /**
     * Constructor from three numbers. */
    Point3D(G4float x1, G4float y1, G4float z1) : BasicVector3D<G4float>(x1,y1,z1) {}

    /**
     * Constructor from array of G4floats. */
    explicit Point3D(const G4float * a)
      : BasicVector3D<G4float>(a[0],a[1],a[2]) {}

    /**
     * Copy constructor. */
    Point3D(const Point3D<G4float> &) = default;

    /**
     * Move constructor. */
    Point3D(Point3D<G4float> &&) = default;

    /**
     * Constructor from BasicVector3D<G4float>. */
    Point3D(const BasicVector3D<G4float> & v) : BasicVector3D<G4float>(v) {}

    /**
     * Destructor. */
    ~Point3D() = default;

    /**
     * Assignment. */
    Point3D<G4float> & operator=(const Point3D<G4float> &) = default;

    /**
     * Assignment from BasicVector3D<G4float>. */
    Point3D<G4float> & operator=(const BasicVector3D<G4float> & v) {
      this->BasicVector3D<G4float>::operator=(v);
      return *this;
    }

    /**
     * Move assignment. */
    Point3D<G4float> & operator=(Point3D<G4float> &&) = default;

    /**
     * Returns distance to the origin squared. */
    G4float distance2() const { return mag2(); }

    /**
     * Returns distance to the point squared. */
    G4float distance2(const Point3D<G4float> & p) const {
      G4float dx = p.x()-x(), dy = p.y()-y(), dz = p.z()-z();
      return dx*dx + dy*dy + dz*dz;
    }

    /**
     * Returns distance to the origin. */
    G4float distance() const { return std::sqrt(distance2()); }

    /**
     * Returns distance to the point. */
    G4float distance(const Point3D<G4float> & p) const {
      return std::sqrt(distance2(p));
    }

    /**
     * Transformation by Transform3D. */
    Point3D<G4float> & transform(const Transform3D & m);
  };

  /**
   * Transformation of Point3D<G4float> by Transform3D.
   * @relates Point3D
   */
  Point3D<G4float>
  operator*(const Transform3D & m, const Point3D<G4float> & p);

  /**
   * Geometrical 3D Point with components of G4double type.
   *
   * @author Evgeni Chernyaev <Evgueni.Tcherniaev@cern.ch>
   * @ingroup geometry
   */
  template<>
  class Point3D<G4double> : public BasicVector3D<G4double> {
  public:
    /**
     * Default constructor. */
    Point3D() = default;

    /**
     * Constructor from three numbers. */
    Point3D(G4double x1, G4double y1, G4double z1) : BasicVector3D<G4double>(x1,y1,z1) {}

    /**
     * Constructor from array of G4floats. */
    explicit Point3D(const G4float * a)
      : BasicVector3D<G4double>(a[0],a[1],a[2]) {}

    /**
     * Constructor from array of G4doubles. */
    explicit Point3D(const G4double * a)
      : BasicVector3D<G4double>(a[0],a[1],a[2]) {}

    /**
     * Copy constructor. */
    Point3D(const Point3D<G4double> &) = default;

    /**
     * Move constructor. */
    Point3D(Point3D<G4double> &&) = default;

    /**
     * Constructor from BasicVector3D<G4float>. */
    Point3D(const BasicVector3D<G4float> & v) : BasicVector3D<G4double>(v) {}

    /**
     * Constructor from BasicVector3D<G4double>. */
    Point3D(const BasicVector3D<G4double> & v) : BasicVector3D<G4double>(v) {}

    /**
     * Destructor. */
    ~Point3D() = default;

    /**
     * Constructor from CLHEP::Hep3Vector.
     * This constructor is needed only for backward compatibility and
     * in principle should be absent.
     */
    Point3D(const CLHEP::Hep3Vector & v)
      : BasicVector3D<G4double>(v.x(),v.y(),v.z()) {}

    /**
     * Conversion (cast) to CLHEP::Hep3Vector.
     * This operator is needed only for backward compatibility and
     * in principle should not exit.
     */
    operator CLHEP::Hep3Vector () const { return CLHEP::Hep3Vector(x(),y(),z()); }

    /**
     * Assignment. */
    Point3D<G4double> & operator=(const Point3D<G4double> &) = default;

    /**
     * Assignment from BasicVector3D<G4float>. */
    Point3D<G4double> & operator=(const BasicVector3D<G4float> & v) {
      this->BasicVector3D<G4double>::operator=(v);
      return *this;
    }

    /**
     * Assignment from BasicVector3D<G4double>. */
    Point3D<G4double> & operator=(const BasicVector3D<G4double> & v) {
      this->BasicVector3D<G4double>::operator=(v);
      return *this;
    }

    /**
     * Move assignment. */
    Point3D<G4double> & operator=(Point3D<G4double> &&) = default;

    /**
     * Returns distance to the origin squared. */
    G4double distance2() const { return mag2(); }

    /**
     * Returns distance to the point squared. */
    G4double distance2(const Point3D<G4double> & p) const {
      G4double dx = p.x()-x(), dy = p.y()-y(), dz = p.z()-z();
      return dx*dx + dy*dy + dz*dz;
    }

    /**
     * Returns distance to the origin. */
    G4double distance() const { return std::sqrt(distance2()); }

    /**
     * Returns distance to the point. */
    G4double distance(const Point3D<G4double> & p) const {
      return std::sqrt(distance2(p));
    }

    /**
     * Transformation by Transform3D. */
    Point3D<G4double> & transform(const Transform3D & m);
  };

  /**
   * Transformation of Point3D<G4double> by Transform3D.
   * @relates Point3D
   */
  Point3D<G4double>
  operator*(const Transform3D & m, const Point3D<G4double> & p);

} /* namespace HepGeom */

#endif /* HEP_POINT3D_H */
