/*
  Copyright (C) 2002-2017 CERN for the benefit of the ATLAS collaboration
*/

#ifndef HOWTOEXTENDANALYSISTOP_CUSTOMJET_H
#define HOWTOEXTENDANALYSISTOP_CUSTOMJET_H

#include "TopObjectSelectionTools/JetSelectionBase.h"
#include "JetAnalysisInterfaces/IJetJvtEfficiency.h"

#include "TopEvent/EventTools.h" //for top::check

#include "AsgTools/ToolHandle.h"

namespace top{
  /**
   * @brief Select jet with a pt min and a pt max
   *        No physics reason, demonstration of a plug-in
   */
  class CustomJet : public JetSelectionBase {
    public:
      CustomJet(const double ptMin, const double ptMax, const double etamax, const bool doJVTCut);
      virtual ~CustomJet(){}
      
      virtual bool passSelection(const xAOD::Jet& jet) ;

      ///Print the cuts to the ostream.
      virtual void print(std::ostream& os) const ;

    protected: 
      ///The lower pT cut threshold to apply to the object.
      double m_ptMin;
      ///The upper pT cut threshold to apply to the object.
      double m_ptMax;      

      ///The upper eta cut.
      double m_etamax;

      ///To do JVT cut - should be false for large-R jets
      bool m_applyJVTCut;
      
      ToolHandle<CP::IJetJvtEfficiency> m_jvt_tool;
  };
}
#endif
