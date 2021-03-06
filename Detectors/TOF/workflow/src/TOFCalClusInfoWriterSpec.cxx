// Copyright CERN and copyright holders of ALICE O2. This software is
// distributed under the terms of the GNU General Public License v3 (GPL
// Version 3), copied verbatim in the file "COPYING".
//
// See http://alice-o2.web.cern.ch/license for full licensing information.
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

/// @file   TOFCalClusInfoWriterSpec.cxx

#include "TOFWorkflowUtils/TOFCalClusInfoWriterSpec.h"
#include "DPLUtils/MakeRootTreeWriterSpec.h"
#include "DataFormatsTOF/CalibInfoCluster.h"
#include "DataFormatsTOF/CosmicInfo.h"

using namespace o2::framework;

namespace o2
{
namespace tof
{
template <typename T>
using BranchDefinition = MakeRootTreeWriterSpec::BranchDefinition<T>;
using OutputType = std::vector<o2::tof::CalibInfoCluster>;
using OutputCosmicType = std::vector<o2::tof::CosmicInfo>;
using namespace o2::header;

DataProcessorSpec getTOFCalClusInfoWriterSpec(bool isCosmics)
{
  // Spectators for logging
  auto logger = [](OutputType const& indata) {
    LOG(DEBUG) << "RECEIVED CLUS CAL INFO SIZE " << indata.size();
  };
  auto loggerCosmics = [](OutputCosmicType const& indata) {
    LOG(DEBUG) << "RECEIVED COSMICS INFO SIZE " << indata.size();
  };

  return MakeRootTreeWriterSpec("TOFCalClusInfoWriter",
                                "tofclusCalInfo.root",
                                "o2sim",
                                BranchDefinition<OutputType>{InputSpec{"clusters", gDataOriginTOF, "INFOCALCLUS", 0},
                                                             "TOFClusterCalInfo",
                                                             "tofclusters-branch-name",
                                                             1,
                                                             logger},
                                BranchDefinition<OutputCosmicType>{InputSpec{"cosmics", gDataOriginTOF, "INFOCOSMICS", 0},
                                                                   "TOFCosmics",
                                                                   "tofcosmics-branch-name",
                                                                   (isCosmics ? 1 : 0),
                                                                   loggerCosmics})();
}
} // namespace tof
} // namespace o2
