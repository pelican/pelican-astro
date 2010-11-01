#include "pipelines/test/TestPipelineRawImageTest.h"
#include "pipelines/TestPipelineRawImage.h"

#include "pelican/core/PipelineApplication.h"
#include "pelican/core/AbstractPipeline.h"
#include "pelican/utility/pelicanTimer.h"
#include "pelican/utility/TestConfig.h"

#include <QtCore/QCoreApplication>
#include <iostream>
using std::cout;
using std::endl;

namespace pelican {

using test::TestConfig;

namespace astro {


CPPUNIT_TEST_SUITE_REGISTRATION( TestPipelineRawImageTest );
/**
 *@details TestPipelineRawImageTest
 */
TestPipelineRawImageTest::TestPipelineRawImageTest()
    : CppUnit::TestFixture()
{
}

/**
 *@details
 */
TestPipelineRawImageTest::~TestPipelineRawImageTest()
{
}

void TestPipelineRawImageTest::setUp()
{
    int ac = 0;
    _app = new QCoreApplication(ac, NULL);
}

void TestPipelineRawImageTest::tearDown()
{
    delete _app;
}

void TestPipelineRawImageTest::test_method()
{
    cout << "==== TestPipelineRawImageTest ====" << endl;
    TestConfig config;
    int argc = 2;
    char** argv = config.argv("TestPipelineRawImage.xml", "pipelines");

    TIMER_START
    QCoreApplication app(argc, argv);
    PipelineApplication pApp(argc, argv);
    pApp.registerPipeline(new TestPipelineRawImage);
    pApp.setDataClient("FileDataClient");
    pApp.start();
    TIMER_STOP("TestPipelineRawImageTest");
}

} // namespace astro
} // namespace pelican
