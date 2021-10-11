#include<iostream>

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "construction.hh"
#include "physics.hh"

int main(int argc, char** argv) {
	G4RunManager *runManager = new G4RunManager();
	
	runManager->SetUserInitialization(new MyDetectorConstruction());
	runManager->SetUserInitialization(new MyPhysicsList());
	
	runManager->Initialize();
	
	G4UIExecutive *ui = new G4UIExecutive(argc, argv);
	
	G4VisManager *visManager = new G4VisExecutive();
	
	visManager->Initialize();
	
	G4UImanager *UImanager = G4UImanager::GetUIpointer();
	
	// openGL is industry standard tool. we use as display for simulations.
	UImanager->ApplyCommand("/vis/open OGL");
	// after opening display, we need draw volume on it
	UImanager->ApplyCommand("/vis/drawVolume");
	
	ui->SessionStart();
	
	// returning the value
	return 0;
}
