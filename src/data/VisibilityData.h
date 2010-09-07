#ifndef VISIBILITYDATA_H
#define VISIBILITYDATA_H

/**
 * @file VisibilityData.h
 */

#include "data/AntennaMatrixData.h"
#include <vector>

using std::vector;

namespace pelican {
namespace astro {

/**
 * @class VisibilityData
 *
 * @brief
 * Class to define telescope visibility data.
 *
 * @details
 * This class is used to store telescope visibility data
 * (matrices of complex correlation products).
 *
 * It inherits AntennaMatrixData<complex_t>.
 */
class VisibilityData : public AntennaMatrixData<complex_t>
{
    public:
        /// Constructs an empty visibility data cube.
        VisibilityData(const QString& type = QString("VisibilityData"))
        : AntennaMatrixData<complex_t>(type) {}

        /// Constructs a pre-sized visibility data cube.
        VisibilityData(unsigned nAntennas, vector<unsigned> const& channels,
                Polarisation polarisation, const QString& type = "VisibilityData")
        : AntennaMatrixData<complex_t>(nAntennas, channels, polarisation, type) {}

        /// Visibility data destructor.
        ~VisibilityData() {}
};

} // namespace astro
} // namespace pelican

#endif // VISIBILITYDATA_H
