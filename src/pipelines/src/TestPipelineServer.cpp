#include "pipelines/TestPipelineServer.h"

#include "modules/VisibilityPrinter.h"
#include "data/VisibilityData.h"

#include "pelican/utility/memCheck.h"

namespace pelican {
namespace astro {

/**
 * @details
 */
TestPipelineServer::TestPipelineServer()
    : AbstractPipeline()
{
    _counter = 0;
}


/**
 * @details
 */
TestPipelineServer::~TestPipelineServer()
{
}


/**
 * @details
 */
void TestPipelineServer::init()
{
    _visPrinter = (VisibilityPrinter*) createModule("VisibilityPrinter");

    requestRemoteData("VisibilityData");
}


/**
 * @details
 */
void TestPipelineServer::run(QHash<QString, DataBlob*>& remoteData)
{
    VisibilityData* vis = (VisibilityData*) remoteData["VisibilityData"];
    Q_ASSERT(vis != NULL);
    _visPrinter->run(vis);
//    sleep(1);

    // Stop the pipeline driver if we have gone through 10 iterations.
    ++_counter;
    if (_counter == 100) stop();
}

} // namespace astro
} // namespace pelican
