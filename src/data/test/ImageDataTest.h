#ifndef IMAGEDATATEST_H_
#define IMAGEDATATEST_H

/**
 * @file ImageDataTest.h
 */

#include <cppunit/extensions/HelperMacros.h>
#include "data/ImageData.h"

namespace pelican {
namespace astro {

/**
 * @class ImageDataTest
 *
 * @brief
 * Unit testing class for the image data blob.
 *
 * @details
 * Performs unit tests on the image data blob object
 * using the CppUnit framework.
 */

class ImageDataTest : public CppUnit::TestFixture
{
    public:
        typedef ImageData::Real Real;

    public:
        CPPUNIT_TEST_SUITE( ImageDataTest );
        CPPUNIT_TEST( test_accessorMethods );
        CPPUNIT_TEST_SUITE_END();

    public:
        void setUp();
        void tearDown();

        // Test Methods
        ///Test accessor methods for image blob
        void test_accessorMethods();

    public:
        ImageDataTest();
        ~ImageDataTest();

    private:
};

} // namespace astro
} // namespace pelican

#endif // IMAGEDATATEST_H_
