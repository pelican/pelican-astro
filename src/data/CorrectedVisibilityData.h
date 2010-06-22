#ifndef CORRECTED_VISIBILITY_DATA_H_
#define CORRECTED_VISIBILITY_DATA_H_

#include "data/VisibilityData.h"
#include <vector>

/**
 * @file CorrectedVisibilityData.h
 */

namespace pelican {
namespace astro {

/**
 * @class CorrectedVisibilityData
 *
 * @brief
 * Container class to hold corrected visibilities.
 *
 * @details
 */
class CorrectedVisibilityData : public VisibilityData
{
    public:
        /// Constructs an empty corrected visibility data blob.
        CorrectedVisibilityData() : VisibilityData("CorrectedVisibilityData") {}

        /// Constructs and resizes corrected visibility data blob.
        CorrectedVisibilityData(const unsigned nAntennas,
                const std::vector<unsigned>& channels,
                const Polarisation polarisation)
        : VisibilityData(nAntennas, channels, polarisation, "CorrectedVisibilityData") {}

        /// Destroys the corrected visibility data blob.
        ~CorrectedVisibilityData() {}
};

} // namespace astro
} // namespace pelican

#endif // CORRECTED_VISIBILITY_DATA_H_
