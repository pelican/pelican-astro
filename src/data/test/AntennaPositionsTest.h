#ifndef ANTENNAPOSITIONSTEST_H
#define ANTENNAPOSITIONSTEST_H

/**
 * @file AntennaPositionsTest.h
 */

#include <cppunit/extensions/HelperMacros.h>
#include "data/AntennaPositions.h"

namespace pelican {
namespace astro {

/**
 * @class AntennaPositionsTest
 *
 * @brief
 * Unit testing class for the antenna positions data blob.
 *
 * @details
 * Performs unit tests on the antenna positions data blob object
 * using the CppUnit framework.
 */

class AntennaPositionsTest : public CppUnit::TestFixture
{
    public:
        typedef AntennaPositions::Real Real;

    public:
        CPPUNIT_TEST_SUITE( AntennaPositionsTest );
        CPPUNIT_TEST( test_accessorMethods );
        CPPUNIT_TEST_SUITE_END();

    public:
        void setUp();
        void tearDown();

        // Test Methods
        /// Test accessor methods for visibility positions class
        void test_accessorMethods();

    public:
        AntennaPositionsTest();
        ~AntennaPositionsTest();
};

} // namespace astro
} // namespace pelican

#endif // ANTENNAPOSITIONSTEST_H
