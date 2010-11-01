#ifndef IMAGEWRITERFITS_TEST_H
#define IMAGEWRITERFITS_TEST_H

/**
 * @file ImageWriterFitsTest.h
 */

#include <cppunit/extensions/HelperMacros.h>
#include <QCoreApplication>

#include "data/ImageData.h"

namespace pelican {
namespace astro {

/**
 * @class ImageWriterFitsTest
 *
 * @brief
 *
 * @details
 *
 */

class ImageWriterFitsTest : public CppUnit::TestFixture
{
    public:
        typedef ImageData::Real Real;

    public:
        CPPUNIT_TEST_SUITE( ImageWriterFitsTest );
        CPPUNIT_TEST( test_createModule );
        CPPUNIT_TEST( test_openFile );
        CPPUNIT_TEST( test_createImage );
        CPPUNIT_TEST( test_createCube );
        CPPUNIT_TEST_SUITE_END();

    public:
        void setUp();
        void tearDown();

        // Test Methods
        void test_createModule();
        void test_openFile();
        void test_createImage();
        void test_createCube();

    public:
        ImageWriterFitsTest();
        ~ImageWriterFitsTest();

    private:
        QCoreApplication *_app;
};

} // namespace astro
} // namespace pelican

#endif // IMAGEWRITERFITS_TEST_H
