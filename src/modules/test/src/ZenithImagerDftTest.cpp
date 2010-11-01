#include "modules/test/ZenithImagerDftTest.h"
#include "modules/ZenithImagerDft.h"
#include "data/ImageData.h"
#include "data/VisibilityData.h"
#include "data/AntennaPositions.h"
#include "data/Constants.h"

#include "pelican/utility/pelicanTimer.h"
#include "pelican/utility/ConfigNode.h"

#include <limits>
#include <vector>
#include <iostream>

using std::vector;

#include "pelican/utility/memCheck.h"

namespace pelican {
namespace astro {

CPPUNIT_TEST_SUITE_REGISTRATION( ZenithImagerDftTest );
// class ZenithImagerDftTest
ZenithImagerDftTest::ZenithImagerDftTest()
    : CppUnit::TestFixture()
{
}

ZenithImagerDftTest::~ZenithImagerDftTest()
{
}

void ZenithImagerDftTest::setUp()
{
}

void ZenithImagerDftTest::tearDown()
{
}


/**
 * @details
 * Test imager configuration.
 */
void ZenithImagerDftTest::test_configuration()
{
    /// Use case
    /// Pass an empty configuration node.
    /// Expect configuration defaults
    {
        ConfigNode config;
        ZenithImagerDftDbl imager(config);
        CPPUNIT_ASSERT(imager._sizeL == 128);
        CPPUNIT_ASSERT(imager._sizeM == 128);
        CPPUNIT_ASSERT(imager._fullSky == true);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-(2.0 / 128.0) * math::rad2asec,
                imager._cellsizeL, 1.0e-5);
        CPPUNIT_ASSERT_DOUBLES_EQUAL((2.0 / 128.0) * math::rad2asec,
                imager._cellsizeM, 1.0e-5);
        CPPUNIT_ASSERT(imager._polarisation == POL_UNDEF);
        CPPUNIT_ASSERT(imager._channels.size() == 1);
        CPPUNIT_ASSERT(imager._channels[0] == 0);
    }
}


/**
 * @details
 * Tests for handling of missing / empty input data.
 */
void ZenithImagerDftTest::test_inputDataBlobs()
{
    try {
        ConfigNode config;
        ZenithImagerDftDbl imager(config);
        imager._polarisation = POL_X;
        ImageData image;
        VisibilityData vis;
        AntennaPositions ant;

        // Use case
        // No data blobs
        // Expect to throw
        {
            CPPUNIT_ASSERT_THROW(imager.run(0, 0, 0), QString);
        }

        // Use case
        // Assigned data blobs
        // Expect not to throw
        {
            vector<unsigned> channels(2);
            image.resize(10, 10, channels, POL_X);
            vis.resize(5, channels, POL_X);
            ant.resize(5);
            imager.run(&image, &ant, &vis);
            //CPPUNIT_ASSERT_NO_THROW(imager.run(&image, &ant, &vis));
        }

    }
    catch (const QString& err)
    {
        CPPUNIT_FAIL(err.toStdString());
    }
}


/**
 * @details
 * Test for calculating image coordinates
 */
void ZenithImagerDftTest::test_calculateImageCoords()
{
    // Use case
    // Setup a imager module. Time and check calculation of image coordinates
    // Expect predictable image coordinates and negligible time taken
    {
        ConfigNode config;
        ZenithImagerDftDbl imager(config);
        int sizeL = 256;
        int sizeM = 256;
        double cellsizeL = math::rad2asec;
        double cellsizeM = 0.1 * math::rad2asec;
        imager.setDimensions(sizeL, sizeM, cellsizeL, cellsizeM);

        // Check we have the right image dimensions
        CPPUNIT_ASSERT(imager._sizeL == static_cast<unsigned>(sizeL));
        CPPUNIT_ASSERT(imager._sizeM == static_cast<unsigned>(sizeM));
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-cellsizeL, imager._cellsizeL, 1.0e-5);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(cellsizeM, imager._cellsizeM, 1.0e-5);

        // Time generation of image coordinates
        TIMER_START
        imager._calculateImageCoords(imager._cellsizeL, imager._sizeL,
                &imager._coordL[0]);
        imager._calculateImageCoords(imager._cellsizeM, imager._sizeM,
                &imager._coordM[0]);
        TIMER_STOP("ZenithImagerDft::_calculateImageCoords()");

        // Check coordinates are correct
        double minL = -(sizeL / 2.0);
        double minM = -(sizeM / 2.0) * 0.1;
        double maxL = (sizeL / 2.0) - 1.0;
        double maxM = ((sizeM / 2.0) - 1.0) * 0.1;
        double delta = 1.0e10;
        CPPUNIT_ASSERT_DOUBLES_EQUAL(minL, imager._coordL[0], delta);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(maxL, imager._coordL[sizeL - 1], delta);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(minM, imager._coordM[0], delta);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(maxM, imager._coordM[sizeM - 1], delta);
    }
}


/**
 * @details
 * Test for calculating DFT weights.
 */
void ZenithImagerDftTest::test_calculateWeights()
{
    typedef ZenithImagerDftDbl::Real Real;
    typedef ZenithImagerDftDbl::Complex Complex;

    ConfigNode config;
    ZenithImagerDftDbl imager(config);

    // Use case
    // Setup a imager module. Time and check calculation of image DFT weights
    // Expect predictable image weights and negligible time taken
    {
        // Make a antenna positions array
        unsigned nAnt = 96;
        std::vector<Real> antPos(nAnt);
        for (unsigned a = 0; a < nAnt; a++) {
            antPos[a] = static_cast<double>(a) / 15.0;
        }

        // Make an image coordinate array
        unsigned nCoords = 256;
        std::vector<Real> coords(nCoords);
        for (unsigned i = 0; i < nCoords; i++) {
            coords[i] = static_cast<double>(i) / 10.0;
        }

        double freq = 1.0e8;
        std::vector<Complex> weights(nAnt * nCoords);

        TIMER_START
        imager._calculateWeights(nAnt, &antPos[0], freq, nCoords, &coords[0],
                &weights[0]);
        TIMER_STOP("ZenithImagerDft::_calculateWeights()");

        // Need to check something here....?
        CPPUNIT_ASSERT(weights[0] == Complex(1.0, 0.0));
        // check all the weights are in range 1 to -1
        for (unsigned w = 0; w < nAnt * nCoords; w++) {
            CPPUNIT_ASSERT(weights[w].real() <= 1.0 && weights[w].real() >= -1.0);
            CPPUNIT_ASSERT(weights[w].imag() <= 1.0 && weights[w].imag() >= -1.0);
        }
    }

    // Use case
    // Setup 2 complex weights vectors and multiply them together
    // Check the result is as expected for element wise multiplication
    // and negligible time taken
    {
        unsigned nAnt = 96;
        std::vector<Complex> weightsXL(nAnt);
        std::vector<Complex> weightsYM(nAnt);
        std::vector<Complex> weights(nAnt);
        for (unsigned a = 0; a < nAnt; a++) {
            weightsXL[a] = Complex(a * 0.1, a * 0.2);
            weightsXL[a] = Complex(a * 0.3, a * 0.4);
        }

        TIMER_START
        imager._multWeights(nAnt,& weightsXL[0], &weightsYM[0], &weights[0]);
        TIMER_STOP("ZenithImagerDft::_multWeights()");

        for (unsigned a = 0; a < nAnt; a++) {
            CPPUNIT_ASSERT(weights[a] == weightsXL[a] * weightsYM[a]);
        }
    }
}


/**
 * @details
 */
void ZenithImagerDftTest::test_makeImageDft()
{
    typedef ZenithImagerDftDbl::Real Real;
    typedef ZenithImagerDftDbl::Complex Complex;

    ConfigNode config;
    ZenithImagerDftDbl imager(config);
    unsigned nAnt = 96;
    double freq = 1.0e8;
    unsigned nL = 128;
    unsigned nM = 128;
    std::vector<Real> antX(nAnt);
    std::vector<Real> antY(nAnt);
    std::vector<Complex> vis(nAnt * nAnt);
    std::vector<Real> coordL(nL);
    std::vector<Real> coordM(nM);
    std::vector<Real> image(nL * nM);

    TIMER_START
    imager._makeImageDft(nAnt, &antX[0], &antY[0], &vis[0], freq, nL, nM,
            &coordL[0], &coordM[0], &image[0]);
    TIMER_STOP("ZenithImagerDft::_makeImageDft()");
}


/**
 * @details
 */
void ZenithImagerDftTest::test_run()
{
}

} // namespace astro
} // namespace pelican
