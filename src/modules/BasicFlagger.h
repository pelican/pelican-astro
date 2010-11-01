#ifndef BASICFLAGGER_H
#define BASICFLAGGER_H

/**
 * @file BasicFlagger.h
 */

#include "data/VisibilityData.h"
#include "data/FlagTable.h"

#include "pelican/modules/AbstractModule.h"
#include "pelican/utility/ConfigNode.h"

#include <vector>
#include <complex>

namespace pelican {
namespace astro {

/**
 * @class BasicFlagger
 *
 * @brief
 * Provides basic flagging routines for visibility data.
 *
 * @details
 * The BasicFlagger module
 */

class BasicFlagger : public AbstractModule
{
    public:
        typedef double Real;
        typedef std::complex<double> Complex;

    public:
        /// Module constructor.
        BasicFlagger(const ConfigNode& config);

        /// Module destructor.
        ~BasicFlagger();

        /// Runs the module.
        void run(VisibilityData* visibilityData, FlagTable* flagTable);

    private:
        /// Flags the autocorrelations.
        void _flagAutocorrelations(const VisibilityData* visData,
                const Complex* medians, const Real minFraction,
                const Real maxFraction, FlagTable* flagTable);

        /// Gets the autocorrelations.
        void _getAutocorrelations(const VisibilityData* visData, Complex* aptr);

        /// Determines the median autocorrelation values.
        void _getMedians(unsigned nAntennas, unsigned nChannels, unsigned nPols,
                const Complex* aptr, Complex* mptr);

        /// Moves bad antennas to the end of the visibility matrix.
        void _moveBadAntennas(VisibilityData* visData, FlagTable* flagTable);

    private:
        /// Minimum visibility level at which to flag, as a fraction of the median.
        Real _minLevelMedian;

        /// Maximum visibility level at which to flag, as a fraction of the median.
        Real _maxLevelMedian;

    private:
        friend class BasicFlaggerTest;
};

bool complexCompareAbs(BasicFlagger::Complex i, BasicFlagger::Complex j);

} // namespace astro
} // namespace pelican
#endif // BASICFLAGGER_H
