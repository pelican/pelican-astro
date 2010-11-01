#include "adapters/test/AdapterAntennaListTest.h"
#include "adapters/AdapterAntennaList.h"
#include "data/AntennaPositions.h"

#include "pelican/utility/ConfigNode.h"

#include <QtCore/QCoreApplication>
#include <QtXml/QDomElement>
#include <QtCore/QFile>

#include "pelican/utility/memCheck.h"

namespace pelican {
namespace astro {

CPPUNIT_TEST_SUITE_REGISTRATION( AdapterAntennaListTest );


/**
 *@details AdapterAntennaListTest
 */
AdapterAntennaListTest::AdapterAntennaListTest()
    : CppUnit::TestFixture()
{
}

/**
 *@details
 */
AdapterAntennaListTest::~AdapterAntennaListTest()
{
}

void AdapterAntennaListTest::setUp()
{
    int argc = 1;
    char *argv[] = {(char*)"pelican"};
    _app = new QCoreApplication(argc, argv);
}

void AdapterAntennaListTest::tearDown()
{
    delete _app;
}

void AdapterAntennaListTest::test_method()
{
    QString fileName = "pelican/data/antennaPositions.dat";
    QFile file(fileName);
    if (!file.exists()) return;
    file.open(QIODevice::ReadOnly);
    AdapterAntennaListDbl *adapter = new AdapterAntennaListDbl(ConfigNode(QDomElement()));
    AntennaPositions data;
    adapter->config(&data, file.size());
    adapter->deserialise(&file);
    delete adapter;
}

} // namespace astro
} // namespace pelican
