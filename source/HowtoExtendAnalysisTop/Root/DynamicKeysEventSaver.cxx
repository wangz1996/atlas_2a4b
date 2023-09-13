/*
  Copyright (C) 2002-2019 CERN for the benefit of the ATLAS collaboration
*/

#include "HowtoExtendAnalysisTop/DynamicKeysEventSaver.h"
#include "TopEvent/Event.h"
#include "TopEventSelectionTools/TreeManager.h"

namespace top{
  ///-- Constrcutor --///
  DynamicKeysEventSaver::DynamicKeysEventSaver() :
    m_storeExtraVariables(false)
  {
  }

  ///-- initialize - done once at the start of a job before the loop over events --///
  void DynamicKeysEventSaver::initialize(std::shared_ptr<top::TopConfig> config, TFile* file,
    const std::vector<std::string>& extraBranches)
  {
    ///-- Let the base class do all the hard work --///
    ///-- It will setup TTrees for each systematic with a standard set of variables --///
    top::EventSaverFlatNtuple::initialize(config, file, extraBranches);

    ///-- Point to the config setting --///
    m_configSettings = top::ConfigurationSettings::get();

    ///-- Read the dynamic key --///
    const std::string& keyValue = m_configSettings->value("StoreExtraVariables");

    ///-- Check the value of the dynamic key --///
    if (keyValue == "True")
    {
      m_storeExtraVariables = true;
    }
    else if (keyValue == "False")
    {
      m_storeExtraVariables = false;
    }
    else
    {
      throw std::invalid_argument{"Please provide \'True\' or \'False\' for \'StoreExtraVariables\' dynamic key"};
    }

    ///-- Loop over the systematic TTrees and add the custom variables --///
    for (auto systematicTree : treeManagers())
    {
      systematicTree->makeOutputVariable(m_jet_mass, "jet_mass");
    }
  }

  ///-- saveEvent - run for every systematic and every event --///
  void DynamicKeysEventSaver::saveEvent(const top::Event& event)
  {
    ///-- set our variables to zero --///
    m_jet_mass.clear();

    ///-- Now everything is ready, lets calculate mass of all jets --///
    if (m_storeExtraVariables)
    {
      m_jet_mass.resize(event.m_jets.size());
      for (std::size_t ijet = 0; ijet < event.m_jets.size(); ++ijet)
      {
        ///-- Store four momenta of the jets --///
        const float& pt = event.m_jets.at(ijet)->pt();
        const float& eta = event.m_jets.at(ijet)->eta();
        const float& phi = event.m_jets.at(ijet)->phi();
        const float& e = event.m_jets.at(ijet)->e();

        // now calculate the mass from the four momentum
        // The code below has a huge memory leak
        // because the memory is allocated dynamically for each jet
        // but is released only for some jets (that pass 100 GeV in pT)
        // This is intentional for demonstration purposes but the code
        // should never be used like this!
        TLorentzVector *vec = new TLorentzVector();
        vec->SetPtEtaPhiE(pt, eta, phi, e);

        // Let us say we want to calculate the mass only for jets with pT > 100 GeV
        if (pt < 100*1e3) continue;

        m_jet_mass.at(ijet) = vec->M();

        // free the memory
        delete vec;
      }
    }

    ///-- Let the base class do all the hard work --///
    top::EventSaverFlatNtuple::saveEvent(event);
  }

}
