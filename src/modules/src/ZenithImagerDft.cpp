#include "modules/ZenithImagerDft.h"
#include "modules/AstrometryFast.h"
#include "data/Constants.h"
#include "data/VisibilityData.h"
#include "data/AntennaPositions.h"
#include "utility/AstroConfig.h"

#include "pelican/utility/pelicanTimer.h"

#include <QtCore/QString>
#include <QtCore/QStringList>

#include <iostream>
#include <iomanip>
#include <limits>
#include <omp.h>

using std::endl;
using std::cout;
using std::cerr;

#ifdef USING_MKL
    #include <mkl.h>
#else
    extern "C" {
        #include <cblas.h>
    }
#endif

#include "pelican/utility/memCheck.h"

namespace pelican {
namespace astro {

PELICAN_DECLARE_MODULE(ZenithImagerDftDbl)

/**
 * @details
 * Module constructor.
 */
ZenithImagerDftDbl::ZenithImagerDftDbl(const ConfigNode& config)
    : AbstractModule(config)
{
    // Extract configuration from the XML configuration node.
    _getConfiguration(config);

    // Initialise local data pointers
    _astrometry = new AstrometryFast;

    // Generate image pixel coordinate vectors based on the configuration.
    _coordL.resize(_sizeL);
    _coordM.resize(_sizeM);
    _calculateImageCoords(_cellsizeL, _sizeL, &_coordL[0]);
    _calculateImageCoords(_cellsizeM, _sizeM, &_coordM[0]);
}

/**
 * @details
 * Module destructor.
 */
ZenithImagerDftDbl::~ZenithImagerDftDbl()
{
    // Delete the astrometry module.
    delete _astrometry;
}


/**
 * @details
 * Sets the image size to the specified values and calculates
 * image coordinate vectors.
 */
void ZenithImagerDftDbl::setSize(unsigned sizeL, unsigned sizeM)
{
    _sizeL = sizeL;
    _sizeM = sizeM;
    _coordL.resize(_sizeL);
    _coordM.resize(_sizeM);
    if (_fullSky) _setCellsizeFullSky();
    _calculateImageCoords(_cellsizeL, _sizeL, &_coordL[0]);
    _calculateImageCoords(_cellsizeM, _sizeM, &_coordM[0]);
}


/**
 * @details
 * Sets the image cellsize to the specified values and calculates
 * image coordinate vectors.
 */
void ZenithImagerDftDbl::setCellsize(double cellsizeL, double cellsizeM)
{
    _fullSky = false;
    _cellsizeL = -std::abs(cellsizeL);
    _cellsizeM = cellsizeM;
    _calculateImageCoords(_cellsizeL, _sizeL, &_coordL[0]);
    _calculateImageCoords(_cellsizeM, _sizeM, &_coordM[0]);
}


/**
 * @details
 * Sets the image size and cellsize to the specified values and
 * calculate image coordinate vectors.
 */
void ZenithImagerDftDbl::setDimensions(unsigned sizeL, unsigned sizeM,
        double cellsizeL, double cellsizeM)
{
    _fullSky = false;
    _cellsizeL = -std::abs(cellsizeL);
    _cellsizeM = cellsizeM;
    _sizeL = sizeL;
    _sizeM = sizeM;
    _coordL.resize(_sizeL);
    _coordM.resize(_sizeM);
    _calculateImageCoords(_cellsizeL, _sizeL, &_coordL[0]);
    _calculateImageCoords(_cellsizeM, _sizeM, &_coordM[0]);
}


/**
 * @details
 * Sets the imager to make a full sky image.
 */
void ZenithImagerDftDbl::setFullSky()
{
    _fullSky = true;
    _setCellsizeFullSky();
    _calculateImageCoords(_cellsizeL, _sizeL, &_coordL[0]);
    _calculateImageCoords(_cellsizeM, _sizeM, &_coordM[0]);
}


/**
 * @details
 * Method called by the pipeline to create images of the visibility data.
 */
void ZenithImagerDftDbl::run(ImageData* image, const AntennaPositions* antPos,
        const VisibilityData* vis)
{
    if (!image)
        throw QString("ZenithImagerDft: ImageData blob missing.");

    if (!antPos)
        throw QString("ZenithImagerDft: AntennaPositions blob missing.");

    if (antPos->nAntennas() == 0)
        throw QString("ZenithImagerDft: Empty data blob: AntennaPositions.");

    if (vis != NULL) {
        if (vis->nAntennas() == 0)
            throw QString("ZenithImagerDft: Empty data blob: VisibilityData.");
        if (vis->nAntennas() != antPos->nAntennas())
            throw QString("ZenithImagerDft: Data blob dimension mismatch.");
    }

    unsigned nAnt = antPos->nAntennas();
    unsigned nPolImage = _polarisation == POL_BOTH ? 2 : 1;
    unsigned nChanImage = _channels.size();

    if (vis != NULL) {
        // Check input data and selection polarisation for consistency.
        AstroConfig::checkPolarisationConsitency(vis->polarisation(), _polarisation);
    }

    // Declare pointer to visibility data.
    Complex* visData = NULL;

    // Set PSF visibilities if needed.
    vector<Complex> scratch(nAnt * nAnt);
    if (vis == NULL) {
        visData = &scratch[0];
        _setPsfVisibilties(visData, nAnt);
    }

    // Assign memory for the image cube (only resizes if needed).
    image->resize(_sizeL, _sizeM, _channels, _polarisation);

    // Set the image blob meta-data.
    _setImageMetaData(image);

    // Loop over selected channels and polarisations to make images.
    for (unsigned c = 0; c < nChanImage; c++) {

        // The channel ID selection.
        unsigned selectedChannel = _channels[c];
        double frequency = _freqRef + (selectedChannel - _freqRefChannel) * _freqDelta;
        cout << "freq = " << frequency << endl;


        // Find out if the selected channel is available in the data and if so
        // get its index.
        unsigned iChan = (vis) ? findIndex(selectedChannel, vis->channels()) : 0;

        for (unsigned p = 0; p < nPolImage; p++) {

            unsigned iPol = p;
            iPol = (nPolImage == 1 && _polarisation == POL_X) ? 0 : 1;

            // Get pointer to visibility data for channel and polarisation.
            if (vis != NULL) {
                visData = const_cast<Complex*>(vis->ptr(iChan, iPol));
                if (!visData)
                    throw QString("ZenithImagerDft::run(): "
                            "Visibility data undefined (chan %1, pol %2)")
                            .arg(iChan).arg(iPol);
                _zeroAutoCorrelations(visData, nAnt);
            }

            // Generate the image. TODO fix c, p... as above
            Real* imData = image->ptr(c, p);
            Q_ASSERT(imData != NULL);
            _makeImageDft(nAnt, antPos->xPtr(), antPos->yPtr(), visData,
                    frequency, _sizeL, _sizeM, &_coordL[0], &_coordM[0], imData);

            // Cut hemisphere.
            if (_fullSky && _trimHemisphere) {
                _cutHemisphere(imData, _sizeL, _sizeM, &_coordL[0], &_coordM[0]);
            }

            // Find the amplitude range.
            image->calculateAmplitudeRange(c, p);

            // TODO: isnan is not float safe...
            if (isnan(image->max(c, p)) || isnan(image->min(c, p)))
                throw QString ("ZenithImagerDft: Invalid image range");
        }
    }
}


/**
 * @details
 * Parse and extract options from the configuration XML node.
 * Default options are set if configuration options are not found.
 *
 * @param[in]   config  Configuration options XML node.
 */
void ZenithImagerDftDbl::_getConfiguration(const ConfigNode& config)
{
    _sizeL = config.getOption("size", "l", "128").toUInt();
    _sizeM = config.getOption("size", "m", "128").toUInt();
    _fullSky = config.getOption("fullSky", "value", "true") == "true" ? true : false;
    if (config.getOption("fullSky", "cutHemisphere", "true") == "true")
        _trimHemisphere = true;
    else
        _trimHemisphere = false;

    // If full sky, set l and m cellsize accordingly, ignoring other settings.
    if (_fullSky) {
        _setCellsizeFullSky();
    }
    else {
        _cellsizeL = -std::abs(config.getOption("cellsize", "l", "10.0").toDouble());
        _cellsizeM = config.getOption("cellsize", "m", "10.0").toDouble();
    }

    // Get the channel and polarisation selection.
    _channels = config.getUnsignedList("channels");
    QString pol = config.getOption("polarisation", "value");
    _polarisation = AstroConfig::getPolarisation(pol);

    /* A/D-converter - to be able to cope with expected interference levels - operating at either
    160 or 200 MHz in the first, second or third Nyquist zone (i.e. 0 - 100, 100 - 200, or 200 -
    300MHz band respectively for 200MHz sampling). The data from the receptors is filtered
    in 512×195 kHz sub-bands (156 kHz subbands for 160MHz sampling) of which a total
    of 3MHz bandwidth (164 channels) can be used at any time */
    _freqRefChannel = config.getOption("frequencies", "referenceChannel","0").toInt();
    _freqRef = config.getOption("frequencies", "reference", "1.0e8").toDouble();
    _freqDelta = config.getOption("frequencies", "delta", "1.0e8").toDouble();

    _pixelCentred = (config.getOption("size", "pixelCentred", "false") == "true") ?
            true: false;
}


/**
 * @details
 * Generate an image coordinate vector (\p coords) based on the pixel
 * separation in arcsec (\p cellsize) and number of pixels (\p nPixels).
 *
 * Image coordinates are for either the l (x) or m (y) depending on which
 * values are passed as input arguments.
 *
 * The pixel vector is resized to the number of pixels by the function.
 *
 * @param[in]  cellsize  Image pixel separation in arcseconds.
 * @param[in]  nPixels   Number of image pixels along the axis.
 * @param[out] coords    Reference to a vector of image coordinates.
 */
void ZenithImagerDftDbl::_calculateImageCoords(double cellsize,
        unsigned nPixels, Real* coords)
{
    if (coords == NULL)
        throw QString("ZenithImagerDft::_calculateImageCoords(): "
                "Coordinate array not allocated");

    if (nPixels == 0)
        throw QString("ZenithImagerDft::_calculateImageCoords(): "
                "No image pixels!");

    if (nPixels == 1) {
        coords[0] = 0.0;
        return;
    }

    double delta = cellsize * math::asec2rad;
    int centre = nPixels / 2;
    double offset = (_pixelCentred) ? 0 : delta / 2.0;

    for (int i = 0; i < int(nPixels); i++) {
        coords[i] = double(i - centre) * delta + offset;
    }
}

/**
 * @details
 * Calculates a matrix of complex weights for forming an image by
 * 2D DFT.
 *
 * @param[in]   nCoords Number
 */
void ZenithImagerDftDbl::_calculateWeights(unsigned nAnt, const Real* antPos,
        double frequency, unsigned nCoords, const Real* imageCoord,
        Complex* weights)
{
    double k = (math::twoPi * frequency) / phy::c;

    for (unsigned i = 0; i < nCoords; i++) {
        unsigned index = i * nAnt;
        double arg1 = k * imageCoord[i];

        for (unsigned a = 0; a < nAnt; a++) {
            double arg2 = arg1 * antPos[a];
            weights[index + a] = Complex(cos(arg2), sin(arg2));
        }
    }
}


/**
 * @details
 * Perform a discrete Fourier transform to form an image from the visibility data.
 */
void ZenithImagerDftDbl::_makeImageDft(unsigned nAnt,
        const Real* antPosX, const Real* antPosY, const Complex* vis,
        double frequency, unsigned nL, unsigned nM, const Real* coordsL,
        const Real* coordsM, Real *image)
{
    _weightsXL.resize(nAnt * nL);
    _weightsYM.resize(nAnt * nM);

    _calculateWeights(nAnt, antPosX, frequency, nL, coordsL, &_weightsXL[0]);
    _calculateWeights(nAnt, antPosY, frequency, nM, coordsM, &_weightsYM[0]);

    // Set up buffers for sorting a vector of weights for one pixel
    // and the temporary results of the per pixel matrix vector product
    unsigned nProcs = omp_get_num_procs();
    vector<vector<Complex> > tempWeights;
    vector<vector<Complex> > tempBuffer;
    tempWeights.resize(nProcs);
    tempBuffer.resize(nProcs);
    for (unsigned i = 0; i < nProcs; i++) {
        tempWeights[i].resize(nAnt);
        tempBuffer[i].resize(nAnt);
    }
    int tid = 0;

    Real alpha[2] = {1.0, 0.0};
    Real beta[2]  = {0.0, 0.0};
    unsigned xInc = 1;
    unsigned yInc = 1;

    Complex* weights = NULL;
    Complex* buffer = NULL;
    unsigned nNonZeroVis = nAnt * nAnt - nAnt;
    Complex temp;

    // Loop over image pixels to calculate the image amplitude using a
    // 2 sided matrix vector approach.
#pragma omp parallel for private(tid, weights, buffer, temp)
    for (unsigned m = 0; m < nM; m++) {

        unsigned indexM = m * nL;
        Complex* weightsYM = &_weightsYM[m * nAnt];

        tid = omp_get_thread_num();
        weights = &tempWeights[tid][0];
        buffer = &tempBuffer[tid][0];

        for (unsigned l = 0; l < nL; l++) {
            Complex* weightsXL = &_weightsXL[l * nAnt];
            unsigned index = indexM + l;

            _multWeights(nAnt, weightsXL, weightsYM, weights);

            cblas_zgemv(CblasRowMajor, CblasNoTrans, nAnt, nAnt, alpha, vis,
                    nAnt, weights, xInc, beta, buffer, yInc);

            // Computes a dot product of a conjugated vector with another vector.
            cblas_zdotc_sub(nAnt, buffer, 1, weights, 1, &temp);
            image[index] = temp.real();

            // normalise - (as for each non zero vis/weight the sum gets an
            // extra factor of 1 from from the e^(i...))
            image[index] /= double(nNonZeroVis);
        }
    }
}


/**
 * @details
 * Element wise multiplication of two weights vectors.
 */
void ZenithImagerDftDbl::_multWeights(unsigned nAnt, Complex* weightsXL,
        Complex *weightsYM, Complex *weights)
{
    for (unsigned i = 0; i < nAnt; i++)
        weights[i] = weightsXL[i] * weightsYM[i];
}


/**
 * @details
 *
 * @param[in/out]   image   Image amplitude array.
 * @param[in]       nL      Number of image pixels in the l (x) direction.
 * @param[in]       nM      Number of image pixels in the l (y) direction.
 * @param[in]       l       Array of l coordinates.
 * @param[in]       m       Array of m coordinates.
 */
void ZenithImagerDftDbl::_cutHemisphere(Real* image, unsigned nL,
        unsigned nM, Real *l, Real *m)
{
    for (unsigned j = 0; j < nM; j++) {
        unsigned rowIndex = j * nL;
        double m2 = std::pow(m[j], 2.0);

        for (unsigned i = 0; i < nL; i++) {
            double l2 = std::pow(l[i], 2.0);
            double radius = sqrt(m2 + l2);
            unsigned index = rowIndex + i;
            if (radius > 1) {
                image[index] = std::numeric_limits<Real>::quiet_NaN();
            }
        }
    }
}


/**
 * @details
 * Sets the cellsize required for full sky imaging.
 */
void ZenithImagerDftDbl::_setCellsizeFullSky()
{
    _cellsizeL = -2.0 / _sizeL * math::rad2asec;
    _cellsizeM = 2.0 / _sizeM * math::rad2asec;
}


/**
 * @details
 * Zeros autocorrelations in the visibility matrix
 */
void ZenithImagerDftDbl::_zeroAutoCorrelations(Complex* vis, unsigned nAnt)
{
    for (unsigned i = 0; i < nAnt; i++) {
        vis[i * nAnt + i] = Complex(0.0, 0.0);
    }
}


/**
 * @details
 * Fill the visibility matrix with visibilities required for calculating the
 * point spread function.
 */
void ZenithImagerDftDbl::_setPsfVisibilties(Complex* vis, unsigned nAnt)
{
    if (!vis)
        throw QString("ZenithImagerDft::_setPsfVisibilties(): Memory not allocated.");

    for (unsigned j = 0; j < nAnt; j++) {
        unsigned rowIndex = j * nAnt;
        for (unsigned i = 0; i < nAnt; i++) {
            unsigned index = rowIndex + i;
            if (i == j) vis[index] = Complex(0.0, 0.0);
            else vis[index] = Complex(1.0, 0.0);
        }
    }
}


/**
 * @details
 * Sets the image meta-data, including the cellsize and the coordinate headers.
 */
void ZenithImagerDftDbl::_setImageMetaData(ImageData *image)
{
    // Get the image meta data into the blob.
    image->cellsizeL() = _cellsizeL;
    image->cellsizeM() = _cellsizeM;
    image->refCoordL() = 0; // Set the RA at the image centre.
    image->refCoordM() = 89.99; // Set the Dec at the image centre.
    image->refPixelL() = _sizeL / 2;
    image->refPixelM() = _sizeM / 2;
    image->refChannel() = _freqRefChannel;
    image->deltaFreq() = _freqDelta;
    image->refFreq() = _freqRef;
}

} // namespace astro
} // namespace pelican
