#include "adapters/test/AdapterLofarStationVisibilitiesTest.h"
#include "adapters/test/VisGen.h"
#include "adapters/AdapterLofarStationVisibilities.h"
#include "data/VisibilityData.h"


#include "pelican/utility/ConfigNode.h"
#include "pelican/utility/constants.h"
#include "pelican/utility/pelicanTimer.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QString>
#include <QtCore/QFile>
#include <QtCore/QDataStream>
#include <QtCore/QBuffer>

#include <iostream>
#include <iomanip>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

namespace pelican {
namespace astro {

CPPUNIT_TEST_SUITE_REGISTRATION( AdapterLofarStationVisibilitiesTest );

// class FileAdapterLofarVisibilitiesTest
AdapterLofarStationVisibilitiesTest::AdapterLofarStationVisibilitiesTest()
: CppUnit::TestFixture()
{
}

AdapterLofarStationVisibilitiesTest::~AdapterLofarStationVisibilitiesTest()
{
}

void AdapterLofarStationVisibilitiesTest::setUp()
{
    int argc = 1;
    char *argv[] = {(char*)"pelican"};
    _app = new QCoreApplication(argc, argv);
    _err = 1.0e-4;
}


void AdapterLofarStationVisibilitiesTest::tearDown()
{
    delete _app;
}


void AdapterLofarStationVisibilitiesTest::test_deserialise_buffer()
{
    try {
        // Create visibility data blob.
        unsigned nAnt = 96;
        unsigned nChan = 512;
        unsigned nPol = 2;
        vector<unsigned> channels(nChan);
        VisibilityData *data = new VisibilityData(nAnt, channels, POL_BOTH);

        // Create the adapter.
        ConfigNode config;
        AdapterLofarStationVisibilities* adapter =
                new AdapterLofarStationVisibilities(config);
        adapter->_nChan = nChan;
        adapter->_nPol = nPol;
        adapter->_nAnt = nAnt;
        adapter->_channels = channels;
        adapter->_polarisation = POL_BOTH;

        // Generate data.
        VisGen generator;
        generator.generate(nAnt, nChan, nPol);

        // Create a buffer from the generated data.
        QByteArray array = generator.byteArray();
        QBuffer buffer(&array);
        buffer.open(QBuffer::ReadOnly);
        CPPUNIT_ASSERT_EQUAL((int)generator.size(), (int)buffer.size());
        adapter->config(data, generator.size(), QHash<QString, DataBlob*>());

        // Deserialise the data.
        TIMER_START
        CPPUNIT_ASSERT_NO_THROW(adapter->deserialise(&buffer));
        TIMER_STOP("Time to deserialise %.2f MByte buffer",
                (float)buffer.size()/(1024*1024))

        // Test some values in the visibility data blob.
        complex_t* vis = NULL;
        unsigned ai = 0, aj = 0, c = 0, p = 0;
        CPPUNIT_ASSERT(vis = data->ptr(c, p));
        CPPUNIT_ASSERT_DOUBLES_EQUAL(_dataVal(ai, aj, c, p),
                vis[aj * nAnt + ai].real(), _err);

        ai = 1; aj = 2; c = 3; p = 1;
        CPPUNIT_ASSERT(vis = data->ptr(c, p));
        CPPUNIT_ASSERT_DOUBLES_EQUAL(_dataVal(ai, aj, c, p),
                vis[aj * nAnt + ai].real(), _err);

        ai = 12; aj = 34; c = 56; p = 0;
        CPPUNIT_ASSERT(vis = data->ptr(c, p));
        CPPUNIT_ASSERT_DOUBLES_EQUAL(_dataVal(ai, aj, c, p),
                vis[aj * nAnt + ai].real(), _err);

        ai = nAnt-1; aj = nAnt-2; c = nChan-1; p = nPol-1;
        CPPUNIT_ASSERT(vis = data->ptr(c, p));
        CPPUNIT_ASSERT_DOUBLES_EQUAL(_dataVal(ai, aj, c, p),
                vis[aj * nAnt + ai].real(), _err);

        // Clean up.
        delete adapter;
        delete data;
    }
    catch (const QString& err)
    {
        CPPUNIT_FAIL(err.toStdString());
    }
}

void AdapterLofarStationVisibilitiesTest::test_deserialise_file()
{
    // Create visibility data blob.
    unsigned nAnt = 96;
    unsigned nChan = 512;
    unsigned nPol = 2;
    std::vector<unsigned> channels(nChan);
    VisibilityData *data = new VisibilityData(nAnt, channels, POL_BOTH);

    // Create the adapter.
    ConfigNode config;
    AdapterLofarStationVisibilities* adapter = new AdapterLofarStationVisibilities(config);
    adapter->_nChan = nChan;
    adapter->_nPol = nPol;
    adapter->_nAnt = nAnt;
    adapter->_channels = channels;
    adapter->_polarisation = POL_BOTH;

    // Generate data.
    VisGen generator;
    generator.generate(nAnt, nChan, nPol);

    // Create a file from the generated data.
    QString fileName = "deserialise_file.dat";
    generator.write(fileName.toStdString());
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    adapter->config(data, generator.size(), QHash<QString, DataBlob*>());


    // Deserialise the data.
    TIMER_START
    CPPUNIT_ASSERT_NO_THROW(adapter->deserialise(&file));
    TIMER_STOP("Time to deserialise %.2f MByte file",
            (float)file.size()/(1024*1024))

    // Test some values in the visibility data blob.
    complex_t* vis = NULL;
    unsigned ai = 0, aj = 0, c = 0, p = 0;
    CPPUNIT_ASSERT(vis = data->ptr(c, p));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_dataVal(ai, aj, c, p),
            vis[aj * nAnt + ai].real(), _err);

    ai = 1; aj = 2; c = 3; p = 1;
    CPPUNIT_ASSERT(vis = data->ptr(c, p));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_dataVal(ai, aj, c, p),
            vis[aj * nAnt + ai].real(), _err);

    ai = 12; aj = 34; c = 56; p = 0;
    CPPUNIT_ASSERT(vis = data->ptr(c, p));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_dataVal(ai, aj, c, p),
            vis[aj * nAnt + ai].real(), _err);

    ai = nAnt-1; aj = nAnt-2; c = nChan-1; p = nPol-1;
    CPPUNIT_ASSERT(vis = data->ptr(c, p));
    CPPUNIT_ASSERT_DOUBLES_EQUAL(_dataVal(ai, aj, c, p),
            vis[aj * nAnt + ai].real(), _err);

    // Clean up.
    delete adapter;
    delete data;
    file.remove();
}

} // namespace astro
} // namespace pelican
