#include "B1SteppingAction.hh"
#include "B1EventAction.hh"
#include "B1DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "TFile.h"
#include "TTree.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1SteppingAction::B1SteppingAction(B1EventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction)
{
  fout=new TFile("o_genG4.root","RECREATE");
  t=new TTree("t","step output");
  t->Branch("evNr",&evNr,"evNr/I");
  t->Branch("x",&x,"x/D");
  t->Branch("y",&y,"y/D");
  t->Branch("z",&z,"z/D");
  t->Branch("px",&px,"px/D");
  t->Branch("py",&py,"py/D");
  t->Branch("pz",&pz,"pz/D");
  t->Branch("kE",&kE,"kE/D");

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1SteppingAction::~B1SteppingAction()
{
  t->Write();
  fout->Close();
  // delete t;
  // delete fout;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1SteppingAction::UserSteppingAction(const G4Step* step)
{

  G4StepPoint* prePoint   = step->GetPreStepPoint();
  G4VPhysicalVolume* prePV= prePoint->GetPhysicalVolume();

  //G4cout<<"name "<<prePV->GetName()<<" "<<prePoint->GetPosition().getZ()<<G4endl;

  if (!prePV) return;
  if( !(prePV->GetName()).contains("target") ) return;
  if( step->GetTrack()->GetParentID() !=0 ) return;


  evNr = fEventAction->GetCurrentEvNr();
  x = prePoint->GetPosition().getX();
  y = prePoint->GetPosition().getY();
  z = prePoint->GetPosition().getZ();
  px = prePoint->GetMomentum().getX();
  py = prePoint->GetMomentum().getY();
  pz = prePoint->GetMomentum().getZ();
  kE = prePoint->GetKineticEnergy();
  //G4cout<<"asdf "<<prePV->GetName()<<" >> "<<x<<G4endl;
  t->Fill();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

