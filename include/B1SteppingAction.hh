
#ifndef B1SteppingAction_h
#define B1SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class B1EventAction;
class G4LogicalVolume;
class TTree;
class TFile;

/// Stepping action class
/// 
class B1SteppingAction : public G4UserSteppingAction{
public:
  B1SteppingAction(B1EventAction* eventAction);
  ~B1SteppingAction();
  
  // method from the base class
  virtual void UserSteppingAction(const G4Step*);
  
private:
  B1EventAction*  fEventAction;
  G4LogicalVolume* fScoringVolume;

  TTree *t;
  TFile *fout;
  G4int evNr;
  G4double x,y,z;
  G4double px,py,pz;
  G4double kE;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
