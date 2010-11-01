#ifndef ZENITHMODELVISIBILITIES_H
#define ZENITHMODELVISIBILITIES_H

/**
 * @file ZenithModelVisibilities.h
 */

#include "data/SiteData.h"
#include "data/CelestialData.h"
#include "data/ModelVisibilityData.h"

#include "pelican/modules/AbstractModule.h"
#include "data/Constants.h"

#include <vector>
using std::vector;

namespace pelican {

class ConfigNode;
class DataBlob;

namespace astro {

class AbstractAstrometry;
class AntennaPositions;
class Source;

/**
 * @class ZenithModelVisibilities
 *
 * @brief
 * Provides facilities to model a visibility set for whole-sky views.
 *
 * @details
 *
 */

class ZenithModelVisibilities : public AbstractModule
{
    public:
        typedef std::complex<double> Complex;
        typedef double Real;

    public:
        /// Module constructor.
        ZenithModelVisibilities(const ConfigNode& config);

        /// Module destructor.
        ~ZenithModelVisibilities();

        /// Runs the module.
        void run(AntennaPositions* antPos, ModelVisibilityData* modelVis);

    private:
        /// Calculate source direction cosines.
        void _calculateDirectionCosines(unsigned nSources,
                const Source* sources, double* l, double* m);

        /// Calculate model visibilities.
        void _calculateModelVis(Complex* vis, unsigned nAnt,
                const Real* antPosX, const Real* antPosY,
                const Source* sources, unsigned nSources,
                double frequency, Polarisation polarisation,
                const double* l, const double* m);

        /// Extract data from the data hash.
        void _checkDataBlobs(AntennaPositions* antPos,
                ModelVisibilityData* modelVis);

        /// Extract configuration from the XML node. setting some defaults.
        void _getConfiguration(const ConfigNode& config);

    private:
        AbstractAstrometry* _astrometry;
        SiteData _siteData;
        CelestialData _celestialData;
        vector<Source> _sources;
        vector<unsigned> _channels;
        int _freqRefChannel;                ///< Frequency reference channel
        double _freqRef;                    ///< Reference frequency
        double _freqDelta;                  ///< Frequency delta
        Polarisation _polarisation;
};


} // namespace astro
} // namespace pelican
#endif // ZENITHMODELVISIBILITIES_H
