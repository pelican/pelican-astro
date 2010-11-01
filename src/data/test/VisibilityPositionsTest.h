#ifndef VISIBILITYPOSITIONSTEST_H
#define VISIBILITYPOSITIONSTEST_H

/**
 * @file VisibilityPositionsTest.h
 */

#include <cppunit/extensions/HelperMacros.h>
#include "data/VisibilityPositions.h"

namespace pelican {
namespace astro {

/**
 * @class VisibilityPositionsTest
 *
 * @brief
 * Unit testing class for the visibility positions data blob.
 *
 * @details
 * Performs unit tests on the visibility positions data blob object
 * using the CppUnit framework.
 */

class VisibilityPositionsTest : public CppUnit::TestFixture
{
    public:
        typedef VisibilityPositions::Real Real;

    public:
        CPPUNIT_TEST_SUITE( VisibilityPositionsTest );
        CPPUNIT_TEST( test_accessorMethods );
        CPPUNIT_TEST_SUITE_END();

    public:
        void setUp();
        void tearDown();

        // Test Methods
        ///Test accessor methods for visibility positions class
        void test_accessorMethods();

    public:
        VisibilityPositionsTest();
        ~VisibilityPositionsTest();
};

} // namespace astro
} // namespace pelican

#endif // VISIBILITYPOSITIONSDATATEST_H
