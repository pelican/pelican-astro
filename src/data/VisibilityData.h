#ifndef VISIBILITYDATA_H
#define VISIBILITYDATA_H

#include "data/AntennaMatrixData.h"

/**
 * @file VisibilityData.h
 */

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
        VisibilityData(const unsigned nAntennas,
                const std::vector<unsigned>& channels,
                const Polarisation polarisation,
                const QString& type = QString("VisibilityData"))
        : AntennaMatrixData<complex_t>(nAntennas, channels, polarisation,
                type) {}

        /// Visibility data destructor.
        ~VisibilityData() {}
};

} // namespace astro
} // namespace pelican

#endif // VISIBILITYDATA_H
