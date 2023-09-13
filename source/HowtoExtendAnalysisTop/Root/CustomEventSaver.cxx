/*
  Copyright (C) 2002-2017 CERN for the benefit of the ATLAS collaboration
*/

#include "HowtoExtendAnalysisTop/CustomEventSaver.h"
#include "TopEvent/Event.h"
#include "TopEventSelectionTools/TreeManager.h"

#include <TRandom3.h>


namespace top{
  ///-- Constrcutor --///
  CustomEventSaver::CustomEventSaver() :
    m_randomNumber(0.),
    m_someOtherVariable(0.)
  {
  }
  
  ///-- initialize - done once at the start of a job before the loop over events --///
  void CustomEventSaver::initialize(std::shared_ptr<top::TopConfig> config, TFile* file,
    const std::vector<std::string>& extraBranches)
  {
	std::cout<<"Using HowToUse HERE#############"<<std::endl;
    ///-- Let the base class do all the hard work --///
    ///-- It will setup TTrees for each systematic with a standard set of variables --///
    top::EventSaverFlatNtuple::initialize(config, file, extraBranches);
    
    ///-- Loop over the systematic TTrees and add the custom variables --///
    for (auto systematicTree : treeManagers()) {
      systematicTree->makeOutputVariable(m_randomNumber, "randomNumber");
      systematicTree->makeOutputVariable(m_someOtherVariable,"someOtherVariable");
      systematicTree->makeOutputVariable(m_jet_EMFrac,"jet_EMFrac");
    }
  }
  
  ///-- calculateEvent - run for every systematic and every event --///
  void CustomEventSaver::calculateEvent(const top::Event& event) 
  {
    ///-- Let the base class do all the hard work --///
    top::EventSaverFlatNtuple::calculateEvent(event);

    ///-- set our variables to zero --///
    m_randomNumber = 0.;
    m_someOtherVariable = 0.;
    m_jet_EMFrac.clear();
    m_truthJets = nullptr;
    
    ///-- Fill them - you should probably do something more complicated --///
    TRandom3 random( event.m_info->eventNumber() );
    m_randomNumber = random.Rndm();    
    m_someOtherVariable = 42;
    //Store the EM fraction of jets
    for(const xAOD::Jet* jet : event.m_jets){
        float emfrac=-999.;
        if(jet->isAvailable<float>("EMFrac")){
            emfrac=jet->auxdata<float>("EMFrac");
        }
        m_jet_EMFrac.emplace_back(emfrac);
    }
    //top::check(evtStore()->retrieve(m_truthJets, top::TopConfig()->sgKeyTruthJets()), "Failed to read truth jets in custom event saver");
  }
  
}
