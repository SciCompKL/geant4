// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4RectangularTrimmedSurface.cc,v 1.3 2000/01/21 13:47:52 gcosmo Exp $
// GEANT4 tag $Name: geant4-02-00 $
//

#include "G4RectangularTrimmedSurface.hh"
#include "G4FPlane.hh"
#include "G4BSplineSurface.hh"
#include "G4ToroidalSurface.hh"
#include "G4SphericalSurface.hh"

G4RectangularTrimmedSurface::G4RectangularTrimmedSurface(){}
G4RectangularTrimmedSurface::~G4RectangularTrimmedSurface()
{
  delete BasisSurface;
}  


void G4RectangularTrimmedSurface::CalcBBox()
{
  BasisSurface->CalcBBox();
  bbox = BasisSurface->bbox;
}


int G4RectangularTrimmedSurface::Intersect(const G4Ray& Rayref)
{
  if(BasisSurface->Intersect(Rayref))
  {
    G4double UHit = BasisSurface->GetUHit();
    G4double VHit = BasisSurface->GetVHit();
    
    if((TrimU1<=UHit)&&(TrimU2>=UHit)&&(TrimV1<=VHit)&&(TrimV2>=VHit))
    {
      closest_hit = BasisSurface->closest_hit;
      return 1;
    }
  }
  
  return 0;
}