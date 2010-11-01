#include "pipelines/test/TestPipelineVisibilityPrinterTest.h"
#include "pipelines/TestPipelineVisibilityPrinter.h"

#include "pelican/core/PipelineApplication.h"
#include "pelican/core/AbstractPipeline.h"
#include "pelican/utility/pelicanTimer.h"
#include "pelican/utility/TestConfig.h"

#include <QtCore/QCoreApplication>

#include <iostream>
using std::cout;
using std::endl;

#include "pelican/utility/memCheck.h"

namespace pelican {
namespace astro {

CPPUNIT_TEST_SUITE_REGISTRATION( TestPipelineVisibilityPrinterTest );

// class TestPipelineVisibilityPrinterTest
TestPipelineVisibilityPrinterTest::TestPipelineVisibilityPrinterTest()
: CppUnit::TestFixture()
{
}

TestPipelineVisibilityPrinterTest::~TestPipelineVisibilityPrinterTest()
{
}

void TestPipelineVisibilityPrinterTest::setUp()
{
    int ac = 0;
    _app = new QCoreApplication(ac, 0);
}

void TestPipelineVisibilityPrinterTest::tearDown()
{
    delete _app;
}

void TestPipelineVisibilityPrinterTest::test_method()
{
    cout << "==== TestPipelineVisibilityPrinterTest ====" << endl;
    _createConfig();
    test::TestConfig config;
    int argc = 2;
    char** argv = config.argv("TestPipelineVisibilityPrinter.xml", "pipelines");

    QCoreApplication app(argc, argv);
    PipelineApplication pApp(argc, argv);
    pApp.registerPipeline(new TestPipelineVisibilityPrinter);
    pApp.setDataClient("FileDataClient");
    pApp.start();
}


void TestPipelineVisibilityPrinterTest::_createConfig()
{
    test::TestConfig config;
    QString testVis = config.findTestFile("testVis.dat", "pipelines");

    QString xml =
    "<clients>"
    "   <FileDataClient>"
    "       <data type=\"VisibilityData\" adapter=\"AdapterLofarStationVisibilities\" file=\"" + testVis + "\"/>"
    "   </FileDataClient>"
    "</clients>"
    "<adapters>"
    "   <AdapterLofarStationVisibilities>"
    "       <antennas number=\"2\"/>"
    "       <channels start=\"0\" end=\"1\"/>"
    "       <polarisation value=\"both\"/>"
    "       <dataBytes number=\"8\"/>"
    "   </AdapterLofarStationVisibilities>"
    "</adapters>";

    config.setFromString(xml);
    config.saveTestConfig("TestPipelineVisibilityPrinter.xml", "pipelines");
}

} // namespace astro
} // namespace pelican
