#include "CommonHeader.h"

// -*- C++ -*-
// ---------------------------------------------------------------------------
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// This is the implementation of the subset of those methods of the Hep3Vector 
// class which originated from the ZOOM SpaceVector class *and* which involve
// the concepts of rotation.
//

#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Vector/AxisAngle.h"
#include "CLHEP/Vector/EulerAngles.h"

#include <cmath>
#include <iostream>

namespace CLHEP  {

//-************************
// rotate about axis
//-************************

Hep3Vector & Hep3Vector::rotate (const Hep3Vector & axis,
				   G4double ddelta) {
  G4double r1 = axis.mag();
  if ( r1 == 0 ) {
    std::cerr << "Hep3Vector::rotate() - "
      << "Attempt to rotate around a zero vector axis! " << std::endl;
    return *this;
  }
  G4double scale=1.0/r1;
  G4double ux = scale*axis.getX();
  G4double uy = scale*axis.getY();
  G4double uz = scale*axis.getZ();
  G4double cd = std::cos(ddelta);
  G4double sd = std::sin(ddelta);
  G4double ocd = 1 - cd;
  G4double rx;
  G4double ry;
  G4double rz;

  { G4double  ocdux = ocd * ux;
    rx = x() * ( cd + ocdux * ux           ) +
         y() * (      ocdux * uy - sd * uz ) +
         z() * (      ocdux * uz + sd * uy ) ;
  }

  { G4double  ocduy = ocd * uy;
    ry = y() * ( cd + ocduy * uy           ) +
         z() * (      ocduy * uz - sd * ux ) +
         x() * (      ocduy * ux + sd * uz ) ;
  }

  { G4double  ocduz = ocd * uz;
    rz = z() * ( cd + ocduz * uz           ) +
         x() * (      ocduz * ux - sd * uy ) +
         y() * (      ocduz * uy + sd * ux ) ;
  }

  set(rx, ry, rz);
  return *this;
} /* rotate */


//-****************************
// rotate by three euler angles
//-****************************


Hep3Vector & Hep3Vector::rotate (G4double phi1, 
				 G4double theta1, 
				 G4double psi1)  {

  G4double rx;
  G4double ry;
  G4double rz;

  G4double sinPhi   = std::sin( phi1   ), cosPhi   = std::cos( phi1   );
  G4double sinTheta = std::sin( theta1 ), cosTheta1 = std::cos( theta1 );
  G4double sinPsi   = std::sin( psi1   ), cosPsi   = std::cos( psi1   );

  rx = 	(cosPsi * cosPhi   - cosTheta1 * sinPsi * sinPhi)   * x()  +
	(cosPsi * sinPhi   + cosTheta1 * sinPsi * cosPhi)   * y()  +
  	(sinPsi * sinTheta)				   * z()  ;

  ry = 	(- sinPsi * cosPhi - cosTheta1 * cosPsi * sinPhi)   * x()  +
	(- sinPsi * sinPhi + cosTheta1 * cosPsi * cosPhi)   * y()  +
  	(cosPsi * sinTheta)				   * z()  ;

  rz = 	(sinTheta * sinPhi)				   * x()  +
  	(- sinTheta * cosPhi)				   * y()  +
	(cosTheta1)					   * z()  ;

  set(rx, ry, rz);
  return *this;

} /* rotate */


//-*******************
// rotate(HepAxisAngle)
// rotate(HepEulerAngles)
//-*******************

Hep3Vector & Hep3Vector::rotate (const HepAxisAngle & ax ) {
  return rotate( ax.getAxis(), ax.delta() );
}

Hep3Vector & Hep3Vector::rotate (const HepEulerAngles & ex ) {
  return rotate( ex.phi(), ex.theta(), ex.psi() );
}


//-***********************
// rotationOf(HepAxisAngle)
// rotationOf(HepEulerAngles)
// and coordinate axis rotations
//-***********************

Hep3Vector rotationOf (const Hep3Vector & vec, const HepAxisAngle & ax) {
  Hep3Vector vv(vec);
  return vv.rotate (ax);
}

Hep3Vector rotationOf (const Hep3Vector & vec,
                       const Hep3Vector & axis, G4double ddelta) {
  Hep3Vector vv(vec);
  return vv.rotate(axis, ddelta);
}

Hep3Vector rotationOf (const Hep3Vector & vec, const HepEulerAngles & ex) {
  Hep3Vector vv(vec);
  return vv.rotate (ex);
}

Hep3Vector rotationOf (const Hep3Vector & vec,
                       G4double phi, G4double theta, G4double psi) {
  Hep3Vector vv(vec);
  return vv.rotate(phi, theta, psi);
}

Hep3Vector rotationXOf (const Hep3Vector & vec, G4double ddelta) {
  Hep3Vector vv(vec);
  return vv.rotateX (ddelta);
}

Hep3Vector rotationYOf (const Hep3Vector & vec, G4double ddelta) {
  Hep3Vector vv(vec);
  return vv.rotateY (ddelta);
}

Hep3Vector rotationZOf (const Hep3Vector & vec, G4double ddelta) {
  Hep3Vector vv(vec);
  return vv.rotateZ (ddelta);
}

}  // namespace CLHEP
