#include "data/test/ImageDataTest.h"
#include "data/ImageData.h"
#include "data/Constants.h"

#include "pelican/utility/pelicanTimer.h"

namespace pelican {
namespace astro {

CPPUNIT_TEST_SUITE_REGISTRATION( ImageDataTest );
// class DataRequirementsTest
ImageDataTest::ImageDataTest()
    : CppUnit::TestFixture()
{
}

ImageDataTest::~ImageDataTest()
{
}

void ImageDataTest::setUp()
{
}

void ImageDataTest::tearDown()
{
}


/**
 * @details
 * Tests the various accessor methods for the image data blob
 */
void ImageDataTest::test_accessorMethods()
{
    // Use Case
    // Construct an image and test each of the accessor methods
    unsigned nL = 256;
    unsigned nM = 125;
    unsigned nChan = 2;
    unsigned nPol = 2;
    std::vector<unsigned> channels(2);
    channels[0] = 0;
    channels[1] = 1;
    ImageData image(nL, nM, channels, POL_BOTH);
    image.cellsizeL() = 1.0;
    image.cellsizeM() = 2.0;
    image.refPixelL() = 128.5;
    image.refPixelM() = 64.0;
    image.coordType() = ImageData::COORD_AZ_EL;
    image.refCoordL() = 40.0;
    image.refCoordM() = 60.25;

    for (unsigned p = 0; p < nPol; p++ ) {
        for (unsigned c = 0; c < nChan; c++) {
            for (unsigned m = 0; m < nM; m++) {
                for (unsigned l = 0; l < nL; l++) {
                    image(l, m, c, p) = c + l + m + p;
                }
            }
        }
    }

    CPPUNIT_ASSERT_EQUAL(nL * nM * nChan * nPol, image.nPixels());
    CPPUNIT_ASSERT_EQUAL(nChan, image.nChannels());
    CPPUNIT_ASSERT_EQUAL(nPol, image.nPolarisations());
    CPPUNIT_ASSERT_EQUAL(nL, image.sizeL());
    CPPUNIT_ASSERT_EQUAL(nM, image.sizeM());

    std::vector<Real> im = image.amp();
    Real *imPtr = image.ptr();
    for (unsigned p = 0; p < nPol; p++ ) {
        for (unsigned c = 0; c < nChan; c++) {
            for (unsigned m = 0; m < nM; m++) {
                for (unsigned l = 0; l < nL; l++) {
                    unsigned index = p * nChan * nL * nM + c * nL * nM + m * nL + l;
                    Real value = static_cast<Real>(c + l + m + p);
                    CPPUNIT_ASSERT_EQUAL(value, image(l, m, c, p));
                    CPPUNIT_ASSERT_EQUAL(value, image[index]);
                    CPPUNIT_ASSERT_EQUAL(value, im[index]);
                    CPPUNIT_ASSERT_EQUAL(value, imPtr[index]);
                }
            }
        }
    }

    Real *imPtrPol0 = image.ptr(0);
    Real *imPtrPol1 = image.ptr(1);
    for (unsigned c = 0; c < nChan; c++) {
        for (unsigned m = 0; m < nM; m++) {
            for (unsigned l = 0; l < nL; l++) {
                unsigned index = c * nL * nM + m * nL + l;
                Real value = static_cast<Real>(c + m + l);
                CPPUNIT_ASSERT_EQUAL(value, imPtrPol0[index]);
                CPPUNIT_ASSERT_EQUAL(value + 1.0, imPtrPol1[index]);
            }
        }
    }

    Real *imPtrPol0Chan0 = image.ptr(0, 0);
    Real *imPtrPol1Chan1 = image.ptr(1, 1);
    for (unsigned m = 0; m < nM; m++) {
        for (unsigned l = 0; l < nL; l++) {
            unsigned index = m * nL + l;
            Real value = static_cast<Real>(m + l);
            CPPUNIT_ASSERT_EQUAL(value, imPtrPol0Chan0[index]);
            CPPUNIT_ASSERT_EQUAL(value + 2.0, imPtrPol1Chan1[index]);
        }
    }
}

} // namespace astro
} // namespace pelican
