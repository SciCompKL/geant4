#include "CommonHeader.h"

// -*- C++ -*-
// ----------------------------------------------------------------------
// HEP coherent system of Units
//
// This file has been provided to CLHEP by Geant4 (simulation toolkit for HEP).
//
// The basic units are :
// millimeter              (millimeter)
// nanosecond              (nanosecond)
// Mega electron Volt      (MeV)
// positron charge         (eplus)
// degree Kelvin           (kelvin)
// the amount of substance (mole)
// luminous intensity      (candela)
// radian                  (radian)
// steradian               (steradian)
//
// Below is a non exhaustive list of derived and pratical units
// (i.e. mostly the SI units).
// You can add your own units.
//
// The SI numerical value of the positron charge is defined here,
// as it is needed for conversion factor : positron charge = e_SI (coulomb)
//
// The others physical constants are defined in the header file :
// PhysicalConstants.h
//
// Authors: M.Maire, S.Giani
//
// History:
//
// 06.02.96   Created.
// 28.03.96   Added miscellaneous constants.
// 05.12.97   E.Tcherniaev: Redefined pascal (to avoid warnings on WinNT)
// 20.05.98   names: meter, second, gram, radian, degree
//            (from Brian.Lasiuk@yale.edu (STAR)). Added luminous units.
// 05.08.98   angstrom, picobarn, microsecond, picosecond, petaelectronvolt
// 01.03.01   parsec    
// 31.01.06   kilogray, milligray, microgray    
// 29.04.08   use PDG 2006 value of e_SI
// 03.11.08   use PDG 2008 value of e_SI
// 19.08.15   added liter and its sub units (mma)
// 12.01.16   added symbols for microsecond (us) and picosecond (ps) (mma)
// 17.07.20   use PDG 2019 value of e_SI
// 06.05.21   added minute, hour, day, year and millielectronvolt (mma)

#ifndef HEP_SYSTEM_OF_UNITS_H
#define HEP_SYSTEM_OF_UNITS_H

namespace CLHEP {

  //
  //
  //
  static constexpr G4double     pi  = 3.14159265358979323846;
  static constexpr G4double  twopi  = 2*pi;
  static constexpr G4double halfpi  = pi/2;
  static constexpr G4double     pi2 = pi*pi;

  // 
  // Length [L]
  //
  static constexpr G4double millimeter  = 1.;                        
  static constexpr G4double millimeter2 = millimeter*millimeter;
  static constexpr G4double millimeter3 = millimeter*millimeter*millimeter;

  static constexpr G4double centimeter  = 10.*millimeter;   
  static constexpr G4double centimeter2 = centimeter*centimeter;
  static constexpr G4double centimeter3 = centimeter*centimeter*centimeter;
    
  static constexpr G4double meter  = 1000.*millimeter;                  
  static constexpr G4double meter2 = meter*meter;
  static constexpr G4double meter3 = meter*meter*meter;

  static constexpr G4double kilometer = 1000.*meter;                   
  static constexpr G4double kilometer2 = kilometer*kilometer;
  static constexpr G4double kilometer3 = kilometer*kilometer*kilometer;

  static constexpr G4double parsec = 3.0856775807e+16*meter;

  static constexpr G4double micrometer = 1.e-6 *meter;             
  static constexpr G4double  nanometer = 1.e-9 *meter;
  static constexpr G4double  angstrom  = 1.e-10*meter;
  static constexpr G4double  fermi     = 1.e-15*meter;

  static constexpr G4double      barn = 1.e-28*meter2;
  static constexpr G4double millibarn = 1.e-3 *barn;
  static constexpr G4double microbarn = 1.e-6 *barn;
  static constexpr G4double  nanobarn = 1.e-9 *barn;
  static constexpr G4double  picobarn = 1.e-12*barn;

  // symbols
  static constexpr G4double nm  = nanometer;                        
  static constexpr G4double um  = micrometer;                        

  static constexpr G4double mm  = millimeter;                        
  static constexpr G4double mm2 = millimeter2;
  static constexpr G4double mm3 = millimeter3;

  static constexpr G4double cm  = centimeter;   
  static constexpr G4double cm2 = centimeter2;
  static constexpr G4double cm3 = centimeter3;

  static constexpr G4double liter = 1.e+3*cm3;
  static constexpr G4double  L = liter;
  static constexpr G4double dL = 1.e-1*liter;
  static constexpr G4double cL = 1.e-2*liter;
  static constexpr G4double mL = 1.e-3*liter;       
  
  static constexpr G4double m  = meter;                  
  static constexpr G4double m2 = meter2;
  static constexpr G4double m3 = meter3;

  static constexpr G4double km  = kilometer;                   
  static constexpr G4double km2 = kilometer2;
  static constexpr G4double km3 = kilometer3;

  static constexpr G4double pc = parsec;

  //
  // Angle
  //
  static constexpr G4double radian      = 1.;                  
  static constexpr G4double milliradian = 1.e-3*radian;
  static constexpr G4double degree = (pi/180.0)*radian;

  static constexpr G4double   steradian = 1.;
  
  // symbols
  static constexpr G4double rad  = radian;
  static constexpr G4double mrad = milliradian;
  static constexpr G4double sr   = steradian;
  static constexpr G4double deg  = degree;

  //
  // Time [T]
  //
  static constexpr G4double nanosecond  = 1.;
  static constexpr G4double second      = 1.e+9 *nanosecond;
  static constexpr G4double millisecond = 1.e-3 *second;
  static constexpr G4double microsecond = 1.e-6 *second;
  static constexpr G4double picosecond  = 1.e-12*second;

  static constexpr G4double minute = 60*second;
  static constexpr G4double hour   = 60*minute;
  static constexpr G4double day    = 24*hour;
  static constexpr G4double year   = 365*day;  

  static constexpr G4double hertz = 1./second;
  static constexpr G4double kilohertz = 1.e+3*hertz;
  static constexpr G4double megahertz = 1.e+6*hertz;

  // symbols
  static constexpr G4double ns = nanosecond;
  static constexpr G4double  s = second;
  static constexpr G4double ms = millisecond;
  static constexpr G4double us = microsecond;
  static constexpr G4double ps = picosecond;

  //
  // Electric charge [Q]
  //
  static constexpr G4double eplus = 1. ;// positron charge
  static constexpr G4double e_SI  = 1.602176634e-19;// positron charge in coulomb
  static constexpr G4double coulomb = eplus/e_SI;// coulomb = 6.24150 e+18 * eplus

  //
  // Energy [E]
  //
  static constexpr G4double megaelectronvolt = 1. ;
  static constexpr G4double     electronvolt = 1.e-6*megaelectronvolt;
  static constexpr G4double kiloelectronvolt = 1.e-3*megaelectronvolt;
  static constexpr G4double gigaelectronvolt = 1.e+3*megaelectronvolt;
  static constexpr G4double teraelectronvolt = 1.e+6*megaelectronvolt;
  static constexpr G4double petaelectronvolt = 1.e+9*megaelectronvolt;
  static constexpr G4double millielectronvolt = 1.e-9*megaelectronvolt;  

  static constexpr G4double joule = electronvolt/e_SI;// joule = 6.24150 e+12 * MeV

  // symbols
  static constexpr G4double MeV = megaelectronvolt;
  static constexpr G4double  eV = electronvolt;
  static constexpr G4double keV = kiloelectronvolt;
  static constexpr G4double GeV = gigaelectronvolt;
  static constexpr G4double TeV = teraelectronvolt;
  static constexpr G4double PeV = petaelectronvolt;

  //
  // Mass [E][T^2][L^-2]
  //
  static constexpr G4double  kilogram = joule*second*second/(meter*meter);   
  static constexpr G4double      gram = 1.e-3*kilogram;
  static constexpr G4double milligram = 1.e-3*gram;

  // symbols
  static constexpr G4double  kg = kilogram;
  static constexpr G4double   g = gram;
  static constexpr G4double  mg = milligram;

  //
  // Power [E][T^-1]
  //
  static constexpr G4double watt = joule/second;// watt = 6.24150 e+3 * MeV/ns

  //
  // Force [E][L^-1]
  //
  static constexpr G4double newton = joule/meter;// newton = 6.24150 e+9 * MeV/mm

  //
  // Pressure [E][L^-3]
  //
#define pascal hep_pascal                          // a trick to avoid warnings 
  static constexpr G4double hep_pascal = newton/m2;   // pascal = 6.24150 e+3 * MeV/mm3
  static constexpr G4double bar        = 100000*pascal; // bar    = 6.24150 e+8 * MeV/mm3
  static constexpr G4double atmosphere = 101325*pascal; // atm    = 6.32420 e+8 * MeV/mm3

  //
  // Electric current [Q][T^-1]
  //
  static constexpr G4double      ampere = coulomb/second; // ampere = 6.24150 e+9 * eplus/ns
  static constexpr G4double milliampere = 1.e-3*ampere;
  static constexpr G4double microampere = 1.e-6*ampere;
  static constexpr G4double  nanoampere = 1.e-9*ampere;

  //
  // Electric potential [E][Q^-1]
  //
  static constexpr G4double megavolt = megaelectronvolt/eplus;
  static constexpr G4double kilovolt = 1.e-3*megavolt;
  static constexpr G4double     volt = 1.e-6*megavolt;

  //
  // Electric resistance [E][T][Q^-2]
  //
  static constexpr G4double ohm = volt/ampere;// ohm = 1.60217e-16*(MeV/eplus)/(eplus/ns)

  //
  // Electric capacitance [Q^2][E^-1]
  //
  static constexpr G4double farad = coulomb/volt;// farad = 6.24150e+24 * eplus/Megavolt
  static constexpr G4double millifarad = 1.e-3*farad;
  static constexpr G4double microfarad = 1.e-6*farad;
  static constexpr G4double  nanofarad = 1.e-9*farad;
  static constexpr G4double  picofarad = 1.e-12*farad;

  //
  // Magnetic Flux [T][E][Q^-1]
  //
  static constexpr G4double weber = volt*second;// weber = 1000*megavolt*ns

  //
  // Magnetic Field [T][E][Q^-1][L^-2]
  //
  static constexpr G4double tesla     = volt*second/meter2;// tesla =0.001*megavolt*ns/mm2

  static constexpr G4double gauss     = 1.e-4*tesla;
  static constexpr G4double kilogauss = 1.e-1*tesla;

  //
  // Inductance [T^2][E][Q^-2]
  //
  static constexpr G4double henry = weber/ampere;// henry = 1.60217e-7*MeV*(ns/eplus)**2

  //
  // Temperature
  //
  static constexpr G4double kelvin = 1.;

  //
  // Amount of substance
  //
  static constexpr G4double mole = 1.;

  //
  // Activity [T^-1]
  //
  static constexpr G4double becquerel = 1./second ;
  static constexpr G4double curie = 3.7e+10 * becquerel;
  static constexpr G4double kilobecquerel = 1.e+3*becquerel;
  static constexpr G4double megabecquerel = 1.e+6*becquerel;
  static constexpr G4double gigabecquerel = 1.e+9*becquerel;
  static constexpr G4double millicurie = 1.e-3*curie;
  static constexpr G4double microcurie = 1.e-6*curie;
  static constexpr G4double Bq = becquerel;
  static constexpr G4double kBq = kilobecquerel;
  static constexpr G4double MBq = megabecquerel;
  static constexpr G4double GBq = gigabecquerel;
  static constexpr G4double Ci = curie;
  static constexpr G4double mCi = millicurie;
  static constexpr G4double uCi = microcurie;

  //
  // Absorbed dose [L^2][T^-2]
  //
  static constexpr G4double      gray = joule/kilogram ;
  static constexpr G4double  kilogray = 1.e+3*gray;
  static constexpr G4double milligray = 1.e-3*gray;
  static constexpr G4double microgray = 1.e-6*gray;

  //
  // Luminous intensity [I]
  //
  static constexpr G4double candela = 1.;

  //
  // Luminous flux [I]
  //
  static constexpr G4double lumen = candela*steradian;

  //
  // Illuminance [I][L^-2]
  //
  static constexpr G4double lux = lumen/meter2;

  //
  // Miscellaneous
  //
  static constexpr G4double perCent     = 0.01 ;
  static constexpr G4double perThousand = 0.001;
  static constexpr G4double perMillion  = 0.000001;

}  // namespace CLHEP

#endif /* HEP_SYSTEM_OF_UNITS_H */
