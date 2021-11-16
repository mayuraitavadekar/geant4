/*

whenever you deal with optical photons, then you have to add
refractive indices for different materials.

*/


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
	
	// add some materials  G4Material
	auto *sio2 = new G4Material("SiO2", 2.201*g/cm3, 2);
	sio2->AddElement(nist->FindOrBuildElement("Si"), 1);
	sio2->AddElement(nist->FindOrBuildElement("O"), 2);
	
	auto *h2o = new G4Material("SiO2", 1.000*g/cm3, 2);
	h2o->AddElement(nist->FindOrBuildElement("H"), 2);
	h2o->AddElement(nist->FindOrBuildElement("O"), 1);
	
	// define element
	G4Element *c = nist->FindOrBuildElement("C");

	// construct aerogel material
	auto *aerogel = new G4Material("Aerogel", 0.200*g/cm3, 3);
	aerogel->AddMaterial(sio2, 62.5*perCent);
	aerogel->AddMaterial(h2o, 37.4*perCent);
	aerogel->AddElement(c, 0.1*perCent);
	
	// what kind of refractive index
	G4double energy[2] = {1.2398*eV/0.2, 1.2398*eV/0.9};
	G4double rindexAerogel[2] = {1.1, 1.1};
	G4double rindexWorld[2] = {1.0, 1.0};
	
	// add this refractive index to our material
	// create material property table
	auto *mptAerogel = new G4MaterialPropertiesTable();
	mptAerogel->AddProperty("RINDEX", energy, rindexAerogel, 2);
	
	aerogel->SetMaterialPropertiesTable(mptAerogel);
	
	
	// nist manager to set material parameters
	// volume = solid + logic volume + physical volume
	G4Material *worldMaterial = nist->FindOrBuildMaterial("G4_AIR");
	
	// we will create another property table for defining refractive
	// index for world material so that our photons can pass through world material
	auto *mptWorld = new G4MaterialPropertiesTable();
	mptWorld->AddProperty("RINDEX", energy, rindexWorld, 2);
	
	worldMaterial->SetMaterialPropertiesTable(mptWorld);
	
	G4Box *solidWorld = new G4Box("solidWorld", 0.5*m, 0.5*m, 0.5*m);
	
	G4LogicalVolume *logicalWorld = new G4LogicalVolume(solidWorld, worldMaterial, "logicalWorld");
	
	G4VPhysicalVolume *physicalWorld = new G4PVPlacement(0, G4ThreeVector(0,0,0), logicalWorld, "physicalWorld",  0, false, 0, true);
	
	// construct a geometry for radiator
	auto *solidRadiator = new G4Box("solidRadiator", 0.4*m, 0.4*m, 0.01*m);
	auto *logicRadiator = new G4LogicalVolume(solidRadiator, aerogel, "logicalRadiator");
	
	// physical volume placement
	auto *physRadiator = new G4PVPlacement(0, G4ThreeVector(.0,.0,0.25*m), logicRadiator, "physRadiator", logicalWorld, false, 0, true);
	
	// we have to return highest mother volume
	return physicalWorld;
}
