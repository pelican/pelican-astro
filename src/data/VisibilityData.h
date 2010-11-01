#ifndef VISIBILITYDATA_H
#define VISIBILITYDATA_H

/**
 * @file VisibilityData.h
 */

#include "data/AntennaMatrixData.h"
#include <vector>
using std::vector;
#include <complex>

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
 * Inherits AntennaMatrixData<T>.
 */

class VisibilityData : public AntennaMatrixData<std::complex<double> >
{
    public:
        typedef std::complex<double> Complex;
        typedef double Real;

    public:
        /// Constructs an empty visibility data cube.
        VisibilityData(const QString& type = QString("VisibilityData"))
        : AntennaMatrixData<Complex>(type) {}

        /// Constructs a pre-sized visibility data cube.
        VisibilityData(unsigned nAntennas, vector<unsigned> const& channels,
                Polarisation polarisation, const QString& type = "VisibilityData")
        : AntennaMatrixData<Complex>(nAntennas, channels, polarisation, type) {}

        /// Visibility data destructor.
        ~VisibilityData() {}
};

} // namespace astro
} // namespace pelican

#endif // VISIBILITYDATA_H
