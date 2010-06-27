#include "pipelines/test/TestPipelineMultipleImagesTest.h"
#include "pipelines/TestPipelineMultipleImages.h"

#include "pelican/core/PipelineApplication.h"
#include "pelican/core/AbstractPipeline.h"
#include "pelican/utility/pelicanTimer.h"
#include "pelican/utility/TestConfig.h"

#include <QtCore/QCoreApplication>

#include "pelican/utility/memCheck.h"

namespace pelican {
namespace astro {

CPPUNIT_TEST_SUITE_REGISTRATION( TestPipelineMultipleImagesTest );


/**
 *@details TestPipelineMultipleImages
 */
TestPipelineMultipleImagesTest::TestPipelineMultipleImagesTest()
    : CppUnit::TestFixture()
{
}

/**
 *@details
 */
TestPipelineMultipleImagesTest::~TestPipelineMultipleImagesTest()
{
}


void TestPipelineMultipleImagesTest::setUp()
{
    int ac = 0;
    _app = new QCoreApplication(ac, NULL);
}


void TestPipelineMultipleImagesTest::tearDown()
{
    delete _app;
}


void TestPipelineMultipleImagesTest::test_method()
{
    TestConfig config;
    int argc = 2;
    char** argv = config.argv("TestPipelineMultipleImages.xml", "pipelines");

    TIMER_START
    QCoreApplication app(argc, argv);
    PipelineApplication pApp(argc, argv);
    pApp.registerPipeline(new TestPipelineMultipleImages);
    pApp.setDataClient("FileDataClient");
    pApp.start();
    TIMER_STOP("TestPipelineMultipleImages");
}

} // namespace astro
} // namespace pelican
