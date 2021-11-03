#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator() 
{
	fParticleGun = new G4ParticleGun(1); // one particle per event is created
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
	delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent) {
	// we need to define what kind of particles we want to create
	auto *particleTable = G4ParticleTable::GetParticleTable();
	G4String particleName = "proton";
	auto *particle = particleTable->FindParticle("proton");
	G4ThreeVector pos(0.,0.,0.);
	G4ThreeVector mom(0.,0.,1.); // +ve z direction
	
	fParticleGun->SetParticlePosition(pos);
	fParticleGun->SetParticleMomentumDirection(mom);
	fParticleGun->SetParticleMomentum(100. * GeV); // quite energetic particle
	fParticleGun->SetParticleDefinition(particle);
	
	// generate primary vertex
	fParticleGun->GeneratePrimaryVertex(anEvent);
}



