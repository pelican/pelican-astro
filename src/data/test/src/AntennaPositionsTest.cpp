#include "data/test/AntennaPositionsTest.h"
#include "data/AntennaPositions.h"

namespace pelican {
namespace astro {

CPPUNIT_TEST_SUITE_REGISTRATION( AntennaPositionsTest );
// class DataRequirementsTest
AntennaPositionsTest::AntennaPositionsTest()
    : CppUnit::TestFixture()
{
}

AntennaPositionsTest::~AntennaPositionsTest()
{
}

void AntennaPositionsTest::setUp()
{
}

void AntennaPositionsTest::tearDown()
{
}


/**
 * @details
 * Tests the various accessor methods for the antenna positions data blob.
 */
void AntennaPositionsTest::test_accessorMethods()
{
    unsigned nAnt = 96;
    AntennaPositions antPos(nAnt);
    for (unsigned i = 0; i < nAnt; i++) {
        antPos.x(i) = static_cast<Real>(i + 0.25);
        antPos.y(i) = static_cast<Real>(i + 0.5);
        antPos.z(i) = static_cast<Real>(i + 0.75);
    }

    CPPUNIT_ASSERT(antPos.nAntennas() == nAnt);
    Real* xPtr = antPos.xPtr();
    Real* yPtr = antPos.yPtr();
    Real* zPtr = antPos.zPtr();
    std::vector<Real> x = antPos.x();
    std::vector<Real> y = antPos.y();
    std::vector<Real> z = antPos.z();

    for (unsigned i = 0; i < nAnt; i++) {
        Real xpos = static_cast<Real>(i + 0.25);
        Real ypos = static_cast<Real>(i + 0.5);
        Real zpos = static_cast<Real>(i + 0.75);

        double delta = 1.0e-5;
        CPPUNIT_ASSERT_DOUBLES_EQUAL(xpos, antPos.x(i), delta);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(xpos, xPtr[i], delta);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(xpos, x[i], delta);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(ypos, antPos.y(i), delta);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(ypos, yPtr[i], delta);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(ypos, y[i], delta);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(zpos, antPos.z(i), delta);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(zpos, zPtr[i], delta);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(zpos, z[i], delta);
    }
}


} // namespace astro
} // namespace pelican
