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
// G4GDMLRead
//
// Class description:
//
// GDML reader.

// Author: Zoltan Torzsok, November 2007
// --------------------------------------------------------------------
#ifndef G4GDMLBASE_HH
#define G4GDMLBASE_HH 1

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLUni.hpp>
#include <xercesc/dom/DOM.hpp>

#include "G4Types.hh"

#include "G4GDMLEvaluator.hh"
#include "G4GDMLAuxStructType.hh"

class G4LogicalVolume;
class G4VPhysicalVolume;

class G4GDMLErrorHandler : public xercesc::ErrorHandler
{
  public:

    G4GDMLErrorHandler(const G4bool set) { Suppress = set; }

    void warning(const xercesc::SAXParseException& exception)
    {
      if(Suppress)
      {
        return;
      }
      char* message = xercesc::XMLString::transcode(exception.getMessage());
      G4cout << "G4GDML: VALIDATION WARNING! " << message
             << " at line: " << exception.getLineNumber() << G4endl;
      xercesc::XMLString::release(&message);
    }

    void error(const xercesc::SAXParseException& exception)
    {
      if(Suppress)
      {
        return;
      }
      char* message = xercesc::XMLString::transcode(exception.getMessage());
      G4cout << "G4GDML: VALIDATION ERROR! " << message
             << " at line: " << exception.getLineNumber() << G4endl;
      xercesc::XMLString::release(&message);
    }

    void fatalError(const xercesc::SAXParseException& exception)
    {
      error(exception);
    }
    void resetErrors() {}

  private:

    G4bool Suppress = false;
};

class G4GDMLRead
{
  public:

    virtual void DefineRead(const xercesc::DOMElement* const)           = 0;
    virtual void MaterialsRead(const xercesc::DOMElement* const)        = 0;
    virtual void SetupRead(const xercesc::DOMElement* const)            = 0;
    virtual void SolidsRead(const xercesc::DOMElement* const)           = 0;
    virtual void Paramvol_contentRead(const xercesc::DOMElement* const) = 0;
    virtual void Volume_contentRead(const xercesc::DOMElement* const)   = 0;
    virtual void StructureRead(const xercesc::DOMElement* const)        = 0;
    //
    // Pure virtual methods implemented in concrete reader plugin's classes

    virtual void ExtensionRead(const xercesc::DOMElement* const);
    //
    // To be implemented in the client code for handling extensions
    // to the GDML schema, identified with the tag "extension".
    // The implementation should be placed inside a user-class
    // inheriting from G4GDMLReadStructure and being registered
    // as argument to G4GDMLParser.

    virtual void UserinfoRead(const xercesc::DOMElement* const);
    //
    // Customisable by user to handle "userinfo" extensions to the
    // GDML schema, identified by the tag "userinfo".

    virtual G4LogicalVolume* GetVolume(const G4String&) const = 0;
    virtual G4String GetSetup(const G4String&)                = 0;
    //
    // More pure virtual methods implemented in the reader plugin.

    void Read(const G4String&, G4bool validation, G4bool isModule,
              G4bool strip = true);
    //
    // Main method for reading GDML files.

    void StripNames() const;
    void StripName(G4String&) const;
    //
    // Strip off pointers from entity IDs.

    void OverlapCheck(G4bool);
    //
    // Activate/de-activate surface check for overlaps (default is off).

    const G4GDMLAuxListType* GetAuxList() const;

  protected:

    G4GDMLRead();
    virtual ~G4GDMLRead();

    G4String Transcode(const XMLCh* const);
    G4String GenerateName(const G4String& name, G4bool strip = false);
    G4String Strip(const G4String&) const;
    void GeneratePhysvolName(const G4String&, G4VPhysicalVolume*);
    void LoopRead(const xercesc::DOMElement* const,
                  void (G4GDMLRead::*)(const xercesc::DOMElement* const));

    G4GDMLAuxStructType AuxiliaryRead(const xercesc::DOMElement* const auxElem);

  protected:

    G4GDMLEvaluator eval;
    G4bool validate = true;
    G4bool check = false;
    G4bool dostrip = true;

  private:

    G4int inLoop = 0, loopCount = 0;
    G4GDMLAuxListType auxGlobalList;
};

#endif
