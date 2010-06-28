#ifndef ZENITH_IMAGER_DFT_H
#define ZENITH_IMAGER_DFT_H

/**
 * @file ZenithImagerDft.h
 */

#include "data/ImageData.h"
#include "data/VisibilityData.h"

#include "pelican/modules/AbstractModule.h"
#include "pelican/utility/constants.h"

#include <vector>

namespace pelican {

class AbstractModule;
class ConfigNode;

namespace astro {

class AbstractAstrometry;
class ModelVisibilityData;
class AntennaPositions;

/**
 * @class ZenithImagerDft
 *
 * @brief
 * Provides basic imaging routines for whole-sky views.
 *
 * @details
 */
class ZenithImagerDft : public AbstractModule
{
    private:
        friend class ZenithImagerDftTest;

    public:
        /// Module constructor.
        ZenithImagerDft(const ConfigNode& config);

        /// Module destructor.
        ~ZenithImagerDft();

        /// Sets the channels (\p c) produce an image from.
        /// Method overrides the selected channels from the configuration.
        void setChannels(const std::vector<unsigned>& c) { _channels = c; }

        /// Sets the polarisation selection.
        /// Method overrides the selected channels from the configuration.
        void setPolarisation(const Polarisation p) { _polarisation = p; }

        /// Sets the image size.
        void setSize(unsigned sizeL, unsigned sizeM);

        /// Sets the image cellsize.
        void setCellsize(double cellsizeL, double cellsizeM);

        /// Sets the image size and cellsize.
        void setDimensions(unsigned sizeL, unsigned sizeM,
        		double cellsizeL, double cellsizeM);

        /// Set the image size to the full sky.
        void setFullSky();

        /// Runs the module.
        void run(ImageData* image, const AntennaPositions* antPos,
                const VisibilityData* vis = NULL);

    private:
        /// Extract the configuration from the XML node setting default where required.
        void _getConfiguration(const ConfigNode& config);

        /// Generates an array of image coordinates in radians.
        void _calculateImageCoords(double cellsize, unsigned nPixels,
                real_t* coords);

        /// Calculate DFT weights for imaging.
        void _calculateWeights(unsigned nAnt, const real_t* antPos,
                double frequency, unsigned nCoords, const real_t* imageCoord,
                complex_t* weights);

        /// Construct the image by DFT.
        void _makeImageDft(unsigned nAnt, const real_t* antPosX,
                const real_t* antPosY, const complex_t* vis, double frequency,
                unsigned nL, unsigned nM, const real_t* coordL,
                const real_t* coordM, real_t *image);

        /// Element wise multiplication of two complex weights vectors.
        void _multWeights(unsigned nAnt, complex_t* weightsXL,
                complex_t *weightsYM, complex_t *weights);

        /// Vector-vector dot product taking the complex conjugate of the
        /// second vector.
        // complex_t _vectorDotConj(unsigned n, complex_t* a, complex_t* b);

        /// Cut the image outside unit radius in l, m.
        void _cutHemisphere(real_t* image, unsigned nL, unsigned nM,
                real_t *l, real_t *m);

        /// Sets the cellsize corresponding to a full sky image.
        void _setCellsizeFullSky();

        /// Remove auto-correlations.
        void _zeroAutoCorrelations(complex_t* vis, unsigned nAnt);

        /// Generate a set of visibilities for creating a point spread function.
        void _setPsfVisibilties(complex_t* vis, unsigned nAnt);

        /// Sets the image meta-data.
        void _setImageMetaData(ImageData* image);

    private:
        AbstractAstrometry* _astrometry;    ///< Astrometric conversion module.

        int _visUse;                        ///< Option to image raw, model or corrected.
        std::vector<unsigned> _channels;    ///< Selected channel list.
        unsigned _nChannels;

        double _freqRefChannel;             ///< Frequency reference channel
        double _freqRef;                    ///< Reference frequency
        double _freqDelta;                  ///< Frequency delta

        Polarisation _polarisation;         ///< Selection polarisation (enumeration).
        bool _fullSky;                      ///< Image the full sky (overrides cellsize)
        bool _trimHemisphere;               ///< Cut the image to the full sky hemisphere
        bool _pixelCentred;                 ///< Put the zero of the image in the middle of a pixel
        unsigned _sizeL;                    ///< Image size in l (x) pixels.
        unsigned _sizeM;                    ///< Image size in m (y) pixels.
        double _cellsizeL;                  ///< Image pixel increment in m (y) direction.
        double _cellsizeM;                  ///< Image pixel increment in l (x) direction.

        std::vector<real_t> _coordL;        ///< Image l (x) coordinates in radians.
        std::vector<real_t> _coordM;        ///< Image m (y) coordinates in radians.

        std::vector<complex_t> _weightsXL;  ///< DFT weights for XL coordinates
        std::vector<complex_t> _weightsYM;  ///< DFT weights for YM coordinates
};

} // namespace astro
} // namespace pelican

#endif // ZENITH_IMAGER_DFT_H
