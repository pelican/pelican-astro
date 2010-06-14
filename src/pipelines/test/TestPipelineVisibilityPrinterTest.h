#ifndef TESTPIPELINEVISIBILITYPRINTERTEST_H
#define TESTPIPELINEVISIBILITYPRINTERTEST_H

#include <cppunit/extensions/HelperMacros.h>

/**
 * @file TestPipelineVisibilityPrinterTest.h
 */

class QCoreApplication;

namespace pelican {
namespace astro {

/**
 * @class TestPipelineVisibilityPrinterTest
 *
 * @brief
 *
 * @details
 *
 */

class TestPipelineVisibilityPrinterTest : public CppUnit::TestFixture
{
    public:
        CPPUNIT_TEST_SUITE( TestPipelineVisibilityPrinterTest );
        CPPUNIT_TEST( test_method );
        CPPUNIT_TEST_SUITE_END();


    public:
        void setUp();
        void tearDown();

        // Test Methods
        void test_method();

    private:
        // Create xml configuration
        void _createConfig();

    public:
        TestPipelineVisibilityPrinterTest();
        ~TestPipelineVisibilityPrinterTest();

    private:
        QCoreApplication *_app;
};

} // namespace astro
} // namespace pelican

#endif // TESTPIPELINEVISIBILITYPRINTERTEST_H
