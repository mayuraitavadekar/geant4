#include "construction.hh"


MyDetectorConstruction::MyDetectorConstruction()
{
}

MyDetectorConstruction::~MyDetectorConstruction()
{
}


G4VPhysicalVolume *MyDetectorConstruction::Construct() 
{
	
	G4NistManager *nist = G4NistManager::Instance();
	
	// nist manager to set material parameters
	// volume = solid + logic volume + physical volume
	G4Material *worldMaterial = nist->FindOrBuildMaterial("G4_AIR");
	
	G4Box *solidWorld = new G4Box("solidWorld", 0.5*m, 0.5*m, 0.5*m);
	
	G4LogicalVolume *logicalWorld = new G4LogicalVolume(solidWorld, worldMaterial, "logicalWorld");
	
	G4VPhysicalVolume *physicalWorld = new G4PVPlacement(0, G4ThreeVector(0,0,0), logicalWorld, "physicalWorld",  0, false, 0, true);
	
	
	// we have to return highest mother volume
	return physicalWorld;
}
