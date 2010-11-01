#include "pipelines/TestPipelineRawImage.h"

#include "modules/ZenithImagerDft.h"
#include "modules/ImageWriterFits.h"
#include "data/AntennaPositions.h"
#include "data/VisibilityData.h"
#include "data/ImageData.h"

#include <iostream>

#include "pelican/utility/memCheck.h"

namespace pelican {
namespace astro {


/**
 * @details
 */
TestPipelineRawImage::TestPipelineRawImage()
    : AbstractPipeline()
{
}


/**
 * @details
 */
TestPipelineRawImage::~TestPipelineRawImage()
{
}


/**
 * @details
 */
void TestPipelineRawImage::init()
{
    _imager = (ZenithImagerDftDbl*) createModule("ZenithImagerDft");
    _fitsWriter = (ImageWriterFits*) createModule("ImageWriterFits");

    // Requests for remote data to be inserted in the data hash.
    requestRemoteData("AntennaPositions");
    requestRemoteData("VisibilityData");

    _image = (ImageData*) createBlob("ImageData");
}


/**
 * @details
 */
void TestPipelineRawImage::run(QHash<QString, DataBlob*>& remoteData)
{
    AntennaPositions* antPos = (AntennaPositions*) remoteData["AntennaPositions"];
    VisibilityData* rawVis = (VisibilityData*) remoteData["VisibilityData"];
    Q_ASSERT(antPos != NULL);
    Q_ASSERT(rawVis != NULL);

    _imager->run(_image, antPos, rawVis);
    _fitsWriter->run(_image);

    stop();
}

} // namespace astro
} // namespace pelican
