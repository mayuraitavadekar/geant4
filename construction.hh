#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VPhysicalVolume.hh"
#include "G4Box.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4LogicalVolume.hh"


class MyDetectorConstruction : public G4VUserDetectorConstruction 
{
	public:
		MyDetectorConstruction();
		~MyDetectorConstruction();
		
		// virtual function // declared in base class; derived in child class
		virtual G4VPhysicalVolume *Construct();
};

#endif
