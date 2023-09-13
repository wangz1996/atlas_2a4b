/*
   Copyright (C) 2002-2021 CERN for the benefit of the ATLAS collaboration
 */

#include "TopEvent/EventTools.h"
#include "TopConfiguration/TopConfig.h"

#include "TopObjectSelectionTools/TopObjectSelection.h"
#include "TopObjectSelectionTools/ElectronLikelihood.h"
#include "TopObjectSelectionTools/IsolationTools.h"
#include "TopObjectSelectionTools/Muon.h"
#include "TopObjectSelectionTools/SoftMuon.h"
#include "TopObjectSelectionTools/AntiMuon.h"
#include "TopObjectSelectionTools/Tau.h"
#include "TopObjectSelectionTools/Jet.h"
#include "TopObjectSelectionTools/TrackJet.h"
#include "TopObjectSelectionTools/JetGhostTrackSelection.h"
#include "TopObjectSelectionTools/TrackSelection.h"
#include "TopObjectSelectionTools/OverlapRemovalASG.h"
// R21 specific
#include "TopObjectSelectionTools/Photon.h"


///-- The custom object selections we have defined in this package --///
#include "HowtoExtendAnalysisTop/CustomObjectLoader.h"
#include "HowtoExtendAnalysisTop/CustomMuon.h"
#include "HowtoExtendAnalysisTop/CustomJet.h"

///-- We largely follow the standard, but replacing muon and jet selections with --///
///-- Those we have defined ourselves --///

// use ATH_MSG macros defined in the namespace TopAnalysis for printing information to console
#include "TopAnalysis/MsgCategory.h"
using namespace TopAnalysis;

namespace top {

  top::TopObjectSelection* CustomObjectLoader::init(std::shared_ptr<top::TopConfig> topConfig) 
  {
    top::TopObjectSelection* objectSelection = new top::TopObjectSelection(topConfig->objectSelectionName());
    top::check(objectSelection->setProperty( "config" , topConfig ) , "Failed to setProperty for top::TopObjectSelection" );
    top::check(objectSelection->initialize() , "Failed to initialize top::TopObjectSelection" );
    
    ///-- Photons --//
    if (topConfig->usePhotons()) {
      objectSelection->photonSelection(new top::Photon(topConfig->photonPtcut(),
                                                        topConfig->photonEtacut(),
                                                        topConfig->photonIdentification(),
                                                        topConfig->photonIdentificationLoose(),
                                                        new top::StandardIsolation(topConfig->photonIsolation(),
                                                                                   topConfig->photonIsolationLoose())));
    }

    ///-- Electrons --///
    if (topConfig->useElectrons()) {
      if (topConfig->electronID().find("LH") != std::string::npos &&
                 topConfig->electronIDLoose().find("LH") != std::string::npos) {
        //user wants likelihood electrons
        objectSelection->electronSelection(new top::ElectronLikelihood(topConfig->electronPtcut(),
                                                                       topConfig->electronVetoLArCrack(),
                                                                       topConfig->electronID(),
                                                                       topConfig->electronIDLoose(),
                                                                       new top::StandardIsolation(
                                                                         topConfig->electronIsolation(),
                                                                         topConfig->electronIsolationLoose()),
                                                                       topConfig->applyTTVACut(),
                                                                       topConfig->useElectronChargeIDSelection()
                                                                       ));
      } else {
        ATH_MSG_ERROR("Not sure it makes sense to use a mix of LH and cut-based electrons for the tight/loose definitions\n"
          << "Tight electron definition is " << topConfig->electronID() << "\n"
          << "Loose electron definition is " << topConfig->electronIDLoose() << "\n"
          << "If it does make sense, feel free to fix this");
        throw std::runtime_error("Mixing LH and cut-based electron definitions for tight/loose");
      }
    }

    ///-- Muons --///
    if (topConfig->useMuons()) {
      if (topConfig->useAntiMuons()) objectSelection->muonSelection(new top::AntiMuon(topConfig->muonPtcut(),
                                                                    new top::AntiMuonIsolation(topConfig->muonIsolation())));
      // custom muon selection
      else objectSelection -> muonSelection(new top::CustomMuon(topConfig->muonPtcut(),
                                                                new top::StandardIsolation(topConfig->muonIsolation(),
                                                                                           topConfig->muonIsolationLoose())));
    }

    ///-- Soft Muons --///
    if (topConfig->useSoftMuons()) {
      objectSelection->softmuonSelection(new top::SoftMuon(topConfig->softmuonPtcut()));
    }


    ///-- Taus --///
    if (topConfig->useTaus()) {
      objectSelection->tauSelection(new top::Tau());
    }

    ///-- Jets --///
    if (topConfig->useJets()) {
      // custom jet class differes from common jets by adding a fixed maximum pT cut
      double ptMax(100000.);
      objectSelection -> jetSelection(new top::CustomJet(topConfig->jetPtcut(), ptMax, topConfig->jetEtacut(), true));
    }

    ///-- Large R Jets --///
    if (topConfig->useLargeRJets()) {// not doing JVT cut for large-R jets
      objectSelection->largeJetSelection(new top::Jet(topConfig->largeRJetPtcut(),
                                                      topConfig->largeRJetEtacut(),
                                                      topConfig->largeRJetMasscut(),
                                                      false));
    }

    ///-- Track Jets --///
    if (topConfig->useTrackJets()) {
      objectSelection->trackJetSelection(new top::TrackJet(topConfig->trackJetPtcut(),
                                                           topConfig->trackJetEtacut()));
    }

    ///-- Ghost Track Jets --///
    if (topConfig->useJetGhostTrack()) {
      objectSelection->jetGhostTrackSelection(new top::JetGhostTrackSelection(topConfig->ghostTrackspT(),
                         2.5,topConfig->ghostTracksVertexAssociation(),topConfig->jetPtGhostTracks(), 2.5));
    }

    ///-- Tracks --///
    if (topConfig->useTracks()) {
      objectSelection->trackSelection(new top::TrackSelection(topConfig->trackPtcut(), topConfig->trackEtacut()));
    }

    ///-- Overlap removal --///
    /// single parameter: boolean to do OR with large-R jets
    if (!topConfig->isTruthDxAOD()) {
      objectSelection->overlapRemovalPostSelection(new top::OverlapRemovalASG((topConfig->doLargeJetOverlapRemoval() &&
                                                                               topConfig->useLargeRJets())));
    }

    return objectSelection;
  }
}
