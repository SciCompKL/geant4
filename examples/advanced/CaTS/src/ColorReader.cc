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
// ********************************************************************
//
//  CaTS (Calorimetry and Tracking Simulation)
//
//  Authors : Hans Wenzel
//            Soon Yung Jun
//            (Fermi National Accelerator Laboratory)
//
// History
//   October 18th, 2021 : first implementation
//
// ********************************************************************
//
/// \file ColorReader.cc
/// \brief extending gdml reader to deal with colors and visualization attributes
//

// Geant4 headers
#include "G4LogicalVolume.hh"
#include "G4VisAttributes.hh"
// project headers
#include "ColorReader.hh"
#include "ConfigurationManager.hh"
ColorReader::ColorReader()
  : G4GDMLReadStructure()
{}

ColorReader::~ColorReader()
{
#if(G4VERSION_NUMBER > 1072)
  for(auto [name, attribute] : fAttribs)
  {
    delete attribute;
  }
#else
  std::map<G4String, G4VisAttributes*>::iterator pos;
  for(pos = fAttribs.begin(); pos != fAttribs.end(); pos++)
  {
    delete pos->second;
  }
#endif
}

void ColorReader::ExtensionRead(const xercesc::DOMElement* const extElement)
{
  G4bool verbose = ConfigurationManager::getInstance()->isEnable_verbose();
  if(verbose)
  {
    G4cout << "ColorReaderReading GDML extension..." << G4endl;
    G4cout << "ColorReader: Reading new GDML extension..." << G4endl;
  }
  for(xercesc::DOMNode* iter = extElement->getFirstChild(); iter != 0;
      iter                   = iter->getNextSibling())
  {
    if(iter->getNodeType() != xercesc::DOMNode::ELEMENT_NODE)
    {
      continue;
    }
    const xercesc::DOMElement* const child =
      dynamic_cast<xercesc::DOMElement*>(iter);
    const G4String tag = Transcode(child->getTagName());
    if(verbose)
    {
      G4cout << "G4GDML:" << tag << G4endl;
    }
    if(tag == "color")
    {
      ColorRead(child);
    }
    else
    {
      G4String error_msg = "Unknown tag in structure: " + tag;
      G4Exception("ColorReader::ExtensionRead()", "ReadError", FatalException,
                  error_msg);
    }
  }
}

void ColorReader::VolumeRead(const xercesc::DOMElement* const volumeElement)
{
  G4bool verbose = ConfigurationManager::getInstance()->isEnable_verbose();
  if(verbose)
  {
    G4cout << "G4GDML: VolumeRead" << G4endl;
  }
  G4VSolid* solidPtr       = 0;
  G4Material* materialPtr  = 0;
  G4VisAttributes* attrPtr = 0;
  G4GDMLAuxListType auxList;
  XMLCh* name_attr    = xercesc::XMLString::transcode("name");
  const G4String name = Transcode(volumeElement->getAttribute(name_attr));
  xercesc::XMLString::release(&name_attr);
  for(xercesc::DOMNode* iter = volumeElement->getFirstChild(); iter != 0;
      iter                   = iter->getNextSibling())
  {
    if(iter->getNodeType() != xercesc::DOMNode::ELEMENT_NODE)
    {
      continue;
    }
    const xercesc::DOMElement* const child =
      dynamic_cast<xercesc::DOMElement*>(iter);
    const G4String tag = Transcode(child->getTagName());
    if(tag == "auxiliary")
    {
      auxList.push_back(AuxiliaryRead(child));
    }
    else if(tag == "materialref")
    {
      materialPtr = GetMaterial(GenerateName(RefRead(child), true));
    }
    else if(tag == "solidref")
    {
      solidPtr = GetSolid(GenerateName(RefRead(child)));
    }
    else if(tag == "colorref")
    {
      if(verbose)
      {
        G4cout << "G4GDML: found visual attribute ..." << G4endl;
      }
      attrPtr = GetVisAttribute(GenerateName(RefRead(child)));
    }
  }
  pMotherLogical =
    new G4LogicalVolume(solidPtr, materialPtr, GenerateName(name), 0, 0, 0);
  if(verbose)
  {
    G4cout << "G4GDML: attaching visual attribute ..." << G4endl;
  }
  pMotherLogical->SetVisAttributes(attrPtr);
  if(!auxList.empty())
  {
    auxMap[pMotherLogical] = auxList;
  }
  Volume_contentRead(volumeElement);
}

void ColorReader::ColorRead(const xercesc::DOMElement* const colorElement)
{
  G4bool verbose = ConfigurationManager::getInstance()->isEnable_verbose();
  if(verbose)
  {
    G4cout << "G4GDML: ColorRead" << G4endl;
  }
  G4String name;
  G4VisAttributes* color = 0;
  G4double r = 0., g = 0., b = 0., a = 0.;
  const xercesc::DOMNamedNodeMap* const attributes =
    colorElement->getAttributes();
  XMLSize_t attributeCount = attributes->getLength();
  for(XMLSize_t attribute_index = 0; attribute_index < attributeCount;
      attribute_index++)
  {
    xercesc::DOMNode* attribute_node = attributes->item(attribute_index);
    if(attribute_node->getNodeType() != xercesc::DOMNode::ATTRIBUTE_NODE)
    {
      continue;
    }
    const xercesc::DOMAttr* const attribute =
      dynamic_cast<xercesc::DOMAttr*>(attribute_node);
    const G4String attName  = Transcode(attribute->getName());
    const G4String attValue = Transcode(attribute->getValue());
    if(attName == "name")
    {
      name = GenerateName(attValue);
    }
    else if(attName == "R")
    {
      r = eval.Evaluate(attValue);
    }
    else if(attName == "G")
    {
      g = eval.Evaluate(attValue);
    }
    else if(attName == "B")
    {
      b = eval.Evaluate(attValue);
    }
    else if(attName == "A")
    {
      a = eval.Evaluate(attValue);
    }
  }
  if(verbose)
  {
    G4cout << "Color attribute (R,G,B,A) is: " << r << ", " << g << ", " << b
           << ", " << a << " !" << G4endl;
  }
  color = new G4VisAttributes(G4Color(r, g, b, a));
  fAttribs.insert(std::make_pair(name, color));
}

G4VisAttributes* ColorReader::GetVisAttribute(const G4String& ref)
{
  G4bool verbose = ConfigurationManager::getInstance()->isEnable_verbose();
  if(verbose)
  {
    G4cout << "G4GDML: GetVisAttribute" << G4endl;
  }
  G4VisAttributes* col                               = 0;
  std::map<G4String, G4VisAttributes*>::iterator pos = fAttribs.find(ref);
  if(pos != fAttribs.end())
  {
    col = pos->second;
  }
  else
  {
    G4String err_mess = "Attribute: " + ref + " NOT found !";
    G4Exception("ColorReader::GetVisAttribute()", "ReadError", FatalException,
                err_mess);
  }
  return col;
}
