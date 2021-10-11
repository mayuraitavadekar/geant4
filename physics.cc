#include "physics.hh"

MyPhysicsList::MyPhysicsList() {
	
	// most of the physics that you will need is already implemented in geant4
	// more physics you implement, the longer it will take for calculations; use only physics which will need in application because it influence your calculations.
	RegisterPhysics(new G4EmStandardPhysics());
	RegisterPhysics(new G4OpticalPhysics());
}

MyPhysicsList::~MyPhysicsList() {
	// nothing
}
