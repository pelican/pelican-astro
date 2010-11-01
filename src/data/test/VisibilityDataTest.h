#ifndef VISIBILITYDATATEST_H_
#define VISIBILITYDATATEST_H_

/**
 * @file VisibilityDataTest.h
 */

#include <cppunit/extensions/HelperMacros.h>
#include "data/VisibilityData.h"

namespace pelican {
namespace astro {

/**
 * @class VisibilityDataTest
 *
 * @brief
 * Unit testing class for the visibility data blob.
 *
 * @details
 * Performs unit tests on the visibility data blob object
 * using the CppUnit framework.
 */

class VisibilityDataTest : public CppUnit::TestFixture
{
    public:
        typedef VisibilityData::Real Real;
        typedef VisibilityData::Complex Complex;

    public:
        CPPUNIT_TEST_SUITE( VisibilityDataTest );
        CPPUNIT_TEST( test_accessorMethods );
        CPPUNIT_TEST( test_accessorMethodsLinear );
        CPPUNIT_TEST( test_emptyBlob );
        CPPUNIT_TEST( test_resize );
        CPPUNIT_TEST( test_swap_same );
        CPPUNIT_TEST( test_swap_twice );
        CPPUNIT_TEST_SUITE_END();

    public:
        void setUp();
        void tearDown();

        // Test Methods
        /// Test indexed accessor methods for 2D visibility data blob.
        void test_accessorMethods();

        /// Test linear accessor methods for 2D visibility data blob.
        void test_accessorMethodsLinear();

        /// Test trying to access an empty blob.
        void test_emptyBlob();

        /// Test trying to resize empty and non-empty blobs.
        void test_resize();

        /// Test swap of antenna data with itself.
        void test_swap_same();

        /// Test swap of antenna rows and columns.
        void test_swap_twice();

    public:
        VisibilityDataTest();
        ~VisibilityDataTest();

    private:
};

} // namespace astro
} // namespace pelican

#endif // VISIBILITYDATATEST_H_
