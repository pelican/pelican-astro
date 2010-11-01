#include "modules/test/BasicFlaggerTest.h"

#include "modules/BasicFlagger.h"
#include "data/VisibilityData.h"
#include "data/FlagTable.h"
#include "data/Constants.h"

#include "pelican/utility/pelicanTimer.h"
#include <algorithm>

namespace pelican {
namespace astro {

CPPUNIT_TEST_SUITE_REGISTRATION( BasicFlaggerTest );

// class BasicFlaggerTest
BasicFlaggerTest::BasicFlaggerTest()
    : CppUnit::TestFixture()
{
}

BasicFlaggerTest::~BasicFlaggerTest()
{
}

/**
 * @details
 * Set-up routine called before each test.
 */
void BasicFlaggerTest::setUp()
{
    // Create a new module with empty configuration before each test.
    ConfigNode config;
    _basicFlagger = new BasicFlagger(config);
}

/**
 * @details
 * Clean-up routine called after each test.
 */
void BasicFlaggerTest::tearDown()
{
    // Delete the module after each test.
    delete _basicFlagger;
}

/**
 * @details
 * Tests the run() method of the BasicFlagger using an empty data hash,
 * and a hash containing no visibilities.
 */
void BasicFlaggerTest::test_run_noData()
{
    // Use Case
    // Pass null data blobs.
    // Expect an exception.
    {
        CPPUNIT_ASSERT_THROW(_basicFlagger->run(NULL, NULL), QString);
    }

    // Use Case
    // Pass a data blob hash containing empty visibility data.
    // Expect an exception.
    {
        VisibilityData vis;
        FlagTable flagTable;
        CPPUNIT_ASSERT_THROW(_basicFlagger->run(&vis, &flagTable), QString);
    }
}

/**
 * @details
 * Tests the run() method of the BasicFlagger using
 * visibility data and flag table.
 */
void BasicFlaggerTest::test_run_withData()
{
    // Use Case
    // Create a set of test visibility data and pass it to the module.
    const unsigned nAntennas = 96;
    const unsigned nChannels = 512;
    std::vector<unsigned> channels(nChannels);
    VisibilityData visData(nAntennas, channels, POL_BOTH);
    FlagTable flagTable(nAntennas, channels, POL_BOTH);
    CPPUNIT_ASSERT_NO_THROW(_basicFlagger->run(&visData, &flagTable));
}


/**
 * @details
 * Tests the routine to flag the autocorrelations (diagonal terms)
 * in the visibility matrix.
 */
void BasicFlaggerTest::test__flagAutocorrelations()
{
    // Use Case
    // Create a set of test visibility data and get the autocorrelations.
    const unsigned nAntennas = 97;
    const unsigned nChannels = 512;
    const unsigned nPols = 2;
    const double minFraction = 0.25;
    const double maxFraction = 1.25;
    std::vector<unsigned> channels(nChannels);
    VisibilityData visData(nAntennas, channels, POL_BOTH);
    FlagTable flagTable(nAntennas, channels, POL_BOTH);
    std::vector<std::complex<double> > medians(nChannels * nPols);

    // Fill the visibility matrix
    for (unsigned p = 0; p < nPols; p++) {
        for (unsigned c = 0; c < nChannels; c++) {
            std::complex<double>* vis = visData.ptr(c, p);
            for (unsigned aj = 0; aj < nAntennas; aj++) {
                for (unsigned ai = 0; ai < nAntennas; ai++) {
                    std::complex<double> val( sqrt((ai+1)*(aj+1)) );
                    vis[ai + aj * nAntennas] = val;
                }
            }
            medians[c + p * nChannels] = vis[nAntennas/2 + nAntennas/2 * nAntennas];
        }
    }

    // Get the autocorrelations.
    TIMER_START
    _basicFlagger->_flagAutocorrelations(&visData, &medians[0],
            minFraction, maxFraction, &flagTable);
    TIMER_STOP("BasicFlagger::_flagAutocorrelations (%u/%u ant in %u chan, %u pol)",
            flagTable.nFlaggedAntennas(0, 0), nAntennas, nChannels, nPols)
}

/**
 * @details
 * Tests the routine to get the autocorrelations (diagonal terms)
 * from the visibility matrix.
 */
void BasicFlaggerTest::test__getAutocorrelations()
{
    // Use Case
    // Create a set of test visibility data and get the autocorrelations.
    const unsigned nAntennas = 96;
    const unsigned nChannels = 512;
    const unsigned nPols = 2;
    std::vector<unsigned> channels(nChannels);
    VisibilityData visData(nAntennas, channels, POL_BOTH);
    std::vector<Complex> autocorr(nAntennas * nChannels * nPols);

    // Fill the visibility matrix
    for (unsigned p = 0; p < nPols; p++) {
        for (unsigned c = 0; c < nChannels; c++) {
            Complex* vis = visData.ptr(c, p);
            for (unsigned aj = 0; aj < nAntennas; aj++) {
                for (unsigned ai = 0; ai < nAntennas; ai++) {
                    std::complex<Real> val( (ai+1)*(aj+1) );
                    vis[ai + aj * nAntennas] = val;
                }
            }
        }
    }

    // Get the autocorrelations.
    TIMER_START
    _basicFlagger->_getAutocorrelations(&visData, &autocorr[0]);
    TIMER_STOP("BasicFlagger::_getAutocorrelations (%u ant, %u chan, %u pol)",
            nAntennas, nChannels, nPols)

    // Check the autocorrelations.
    for (unsigned p = 0, i = 0; p < nPols; p++) {
        for (unsigned c = 0; c < nChannels; c++) {
            for (unsigned a = 0; a < nAntennas; a++) {
                std::complex<Real> val( (a+1)*(a+1) );
                CPPUNIT_ASSERT_EQUAL( val, autocorr[i] );
                i++;
            }
        }
    }
}

/**
 * @details
 * Tests the routine to get the median antenna power for each
 * channel and polarisation.
 */
void BasicFlaggerTest::test__getMedians()
{
    // Use Case
    // Create a set of test values and get the medians.
    const unsigned nAntennas = 96;
    const unsigned nChannels = 512;
    const unsigned nPols = 2;
    std::vector<Complex> autocorr(nAntennas * nChannels * nPols);
    std::vector<Complex> medians(nChannels * nPols);

    // Fill the autocorrelation data.
    for (unsigned p = 0; p < nPols; p++) {
        for (unsigned c = 0; c < nChannels; c++) {
            /* Get the address of the start of the antenna list */
            const unsigned i = c * nAntennas + p * nAntennas * nChannels;
            Complex* beg = &autocorr[i];
            Complex* end = &autocorr[i + nAntennas];

            for (unsigned a = 0; a < nAntennas; a++) {
                std::complex<Real> val( p + c + a*a );
                autocorr[i + a] = val;
            }
            std::random_shuffle(beg, end);
        }
    }

    // Get the medians.
    TIMER_START
    _basicFlagger->_getMedians(nAntennas, nChannels, nPols, &autocorr[0], &medians[0]);
    TIMER_STOP("BasicFlagger::_getMedians (%u ant, %u chan, %u pol)",
            nAntennas, nChannels, nPols)

    // Check the medians.
    for (unsigned p = 0, i = 0; p < nPols; p++) {
        for (unsigned c = 0; c < nChannels; c++) {
            std::complex<Real> val( p + c + (nAntennas/2)*(nAntennas/2) );
            CPPUNIT_ASSERT_EQUAL( val, medians[i] );
            i++;
        }
    }
}

/**
 * @details
 * Tests the routine to move the bad antennas to the edge of the visibility
 * matrix.
 */
void BasicFlaggerTest::test__moveBadAntennas()
{
    // Use Case
    // Create a set of test visibility data and get the autocorrelations.
    const unsigned nAntennas = 97;
    const unsigned nChannels = 512;
    const unsigned nPols = 2;
    const Real minFraction = 0.5;
    const Real maxFraction = 1.5;
    std::vector<unsigned> channels(nChannels);
    VisibilityData visData(nAntennas, channels, POL_BOTH);
    FlagTable flagTable(nAntennas, channels, POL_BOTH);
    std::vector<Complex> medians(nChannels * nPols);

    // Fill the visibility matrix
    for (unsigned p = 0; p < nPols; p++) {
        for (unsigned c = 0; c < nChannels; c++) {
            Complex* vis = visData.ptr(c, p);
            for (unsigned aj = 0; aj < nAntennas; aj++) {
                for (unsigned ai = 0; ai < nAntennas; ai++) {
                    std::complex<Real> val( sqrt((ai+1)*(aj+1)) );
                    vis[ai + aj * nAntennas] = val;
                }
            }
            medians[c + p * nChannels] = vis[nAntennas/2 + nAntennas/2 * nAntennas];
        }
    }

    // Flag the autocorrelations.
    _basicFlagger->_flagAutocorrelations(&visData, &medians[0],
            minFraction, maxFraction, &flagTable);

    // Move the bad antennas.
    TIMER_START
    _basicFlagger->_moveBadAntennas(&visData, &flagTable);
    TIMER_STOP("BasicFlagger::_moveBadAntennas (%u/%u ant in %u chan, %u pol)",
            flagTable.nFlaggedAntennas(0, 0), nAntennas, nChannels, nPols)
}

} // namespace astro
} // namespace pelican
