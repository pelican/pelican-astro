#ifndef ZENITH_IMAGER_DFT_H
#define ZENITH_IMAGER_DFT_H

/**
 * @file ZenithImagerDft.h
 */

#include "data/ImageData.h"
#include "data/VisibilityData.h"

#include "pelican/modules/AbstractModule.h"
#include "data/Constants.h"

#include <complex>
#include <vector>
using std::vector;

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
class ZenithImagerDftDbl : public AbstractModule
{
    private:
        friend class ZenithImagerDftTest;

    public:
        typedef double Real;
        typedef std::complex<double> Complex;

    public:
        /// Module constructor.
        ZenithImagerDftDbl(const ConfigNode& config);

        /// Module destructor.
        ~ZenithImagerDftDbl();

        /// Sets the channels (\p c) produce an image from.
        /// Method overrides the selected channels from the configuration.
        void setChannels(const vector<unsigned>& c) { _channels = c; }

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
                Real* coords);

        /// Calculate DFT weights for imaging.
        void _calculateWeights(unsigned nAnt, const Real* antPos,
                double frequency, unsigned nCoords, const Real* imageCoord,
                Complex* weights);

        /// Construct the image by DFT.
        void _makeImageDft(unsigned nAnt, const Real* antPosX,
                const Real* antPosY, const Complex* vis, double frequency,
                unsigned nL, unsigned nM, const Real* coordL,
                const Real* coordM, Real *image);

        /// Element wise multiplication of two complex weights vectors.
        void _multWeights(unsigned nAnt, Complex* weightsXL,
                Complex *weightsYM, Complex *weights);

        /// Cut the image outside unit radius in l, m.
        void _cutHemisphere(Real* image, unsigned nL, unsigned nM,
                Real *l, Real *m);

        /// Sets the cellsize corresponding to a full sky image.
        void _setCellsizeFullSky();

        /// Remove auto-correlations.
        void _zeroAutoCorrelations(Complex* vis, unsigned nAnt);

        /// Generate a set of visibilities for creating a point spread function.
        void _setPsfVisibilties(Complex* vis, unsigned nAnt);

        /// Sets the image meta-data.
        void _setImageMetaData(ImageData* image);

    private:
        AbstractAstrometry* _astrometry;    ///< Astrometric conversion module.

        int _visUse;                   ///< Option to image raw, model or corrected.
        vector<unsigned> _channels;    ///< Selected channel list.
        unsigned _nChannels;

        double _freqRefChannel;        ///< Frequency reference channel
        double _freqRef;               ///< Reference frequency
        double _freqDelta;             ///< Frequency delta

        Polarisation _polarisation;    ///< Selection polarisation (enumeration).
        bool _fullSky;                 ///< Image the full sky (overrides cellsize)
        bool _trimHemisphere;          ///< Cut the image to the full sky hemisphere
        bool _pixelCentred;            ///< Put the zero of the image in the middle of a pixel
        unsigned _sizeL;               ///< Image size in l (x) pixels.
        unsigned _sizeM;               ///< Image size in m (y) pixels.
        double _cellsizeL;             ///< Image pixel increment in m (y) direction.
        double _cellsizeM;             ///< Image pixel increment in l (x) direction.

        vector<Real> _coordL;        ///< Image l (x) coordinates in radians.
        vector<Real> _coordM;        ///< Image m (y) coordinates in radians.

        vector<Complex> _weightsXL;  ///< DFT weights for XL coordinates
        vector<Complex> _weightsYM;  ///< DFT weights for YM coordinates
};

} // namespace astro
} // namespace pelican

#endif // ZENITH_IMAGER_DFT_H
