/*
  Copyright (C) 2002-2019 CERN for the benefit of the ATLAS collaboration
*/

#ifndef DYNAMICKEYS_EVENTSAVER_H
#define DYNAMICKEYS_EVENTSAVER_H

#include "TopAnalysis/EventSaverFlatNtuple.h"
#include "TopConfiguration/ConfigurationSettings.h"

/**
 * This class shows you how to use DynamicKeys in your custom event saver
 *
 * It inherits from top::EventSaverFlatNtuple, which will be doing all the hard work
 *
 */

namespace top{
  class DynamicKeysEventSaver : public top::EventSaverFlatNtuple {
    public:
      ///-- Default constrcutor with no arguments - needed for ROOT --///
      DynamicKeysEventSaver();
      ///-- Destructor does nothing --///
      virtual ~DynamicKeysEventSaver() = default;

      ///-- initialize function for top::EventSaverFlatNtuple --///
      ///-- We will be setting up out custom variables here --///
      virtual void initialize(std::shared_ptr<top::TopConfig> config, TFile* file, const std::vector<std::string>& extraBranches) override final;

      ///-- Keep the asg::AsgTool happy --///
      virtual StatusCode initialize() override final {return StatusCode::SUCCESS;}

      ///-- saveEvent function for top::EventSaverFlatNtuple --///
      ///-- We will be setting our custom variables on a per-event basis --///
      virtual void saveEvent(const top::Event& event) override final;

    private:
      ///-- Pointer to the configuration settings that we need to read the dynamic keys --///
      ConfigurationSettings* m_configSettings;

      ///-- Flag if we store the extra variables --///
      bool m_storeExtraVariables;

      ///-- Some additional custom variables for the output --///
      std::vector<float> m_jet_mass;

      ///-- Tell RootCore to build a dictionary (we need this) --///
      ClassDefOverride(top::DynamicKeysEventSaver, 0);
  };
}

#endif
