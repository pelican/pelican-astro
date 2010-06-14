#include "pipelines/TestPipelineVisibilityPrinter.h"
#include "modules/VisibilityPrinter.h"
#include "data/VisibilityData.h"

#include "pelican/utility/memCheck.h"

namespace pelican {
namespace astro {


/**
 * @details
 */
TestPipelineVisibilityPrinter::TestPipelineVisibilityPrinter()
    : AbstractPipeline()
{
}


/**
 * @details
 */
TestPipelineVisibilityPrinter::~TestPipelineVisibilityPrinter()
{
}


/**
 * @details
 */
void TestPipelineVisibilityPrinter::init()
{
    _visPrinter = (VisibilityPrinter*) createModule("VisibilityPrinter");

    requestRemoteData("VisibilityData");
}


/**
 * @details
 */
void TestPipelineVisibilityPrinter::run(QHash<QString, DataBlob*>& remoteData)
{
    VisibilityData* vis = (VisibilityData*) remoteData["VisibilityData"];
    Q_ASSERT(vis != NULL);
    _visPrinter->run(vis);

    // Stop the pipeline driver.
    stop();
}

} // namespace astro
} // namespace pelican
