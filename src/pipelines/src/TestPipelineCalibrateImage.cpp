#include "pipelines/TestPipelineCalibrateImage.h"

#include "modules/ZenithImagerDft.h"
#include "modules/ImageWriterFits.h"
#include "modules/ZenithModelVisibilities.h"
#include "modules/ZenithCalibrater.h"
#include "modules/ImageCombiner.h"
#include "data/AntennaPositions.h"
#include "data/ModelVisibilityData.h"
#include "data/VisibilityData.h"
#include "data/CorrectedVisibilityData.h"
#include "data/ImageData.h"

#include <iostream>

#include "pelican/utility/memCheck.h"

namespace pelican {
namespace astro {


/**
 * @details
 */
TestPipelineCalibrateImage::TestPipelineCalibrateImage()
    : AbstractPipeline()
{
}


/**
 * @details
 */
TestPipelineCalibrateImage::~TestPipelineCalibrateImage()
{
}


/**
 * @details
 */
void TestPipelineCalibrateImage::init()
{
    _imager = (ZenithImagerDft*) createModule("ZenithImagerDft");
    _imagerModel = (ZenithImagerDft*) createModule("ZenithImagerDft", "model");
    _fitsWriter = (ImageWriterFits*) createModule("ImageWriterFits");
    _modelGen = (ZenithModelVisibilities*) createModule("ZenithModelVisibilities");
    _calibrate = (ZenithCalibrater*) createModule("ZenithCalibrater");
    _imageCombiner = (ImageCombiner*) createModule("ImageCombiner");

    // Requests for remote data to be inserted in the data hash.
    requestRemoteData("AntennaPositions");
    requestRemoteData("VisibilityData");

    _calImage = (ImageData*) createBlob("ImageData");
    _psfImage = (ImageData*) createBlob("ImageData");
    _rawImage = (ImageData*) createBlob("ImageData");
    _modelImage = (ImageData*) createBlob("ImageData");
    _diffImage = (ImageData*) createBlob("ImageData");
    _modelVis = (ModelVisibilityData*) createBlob("ModelVisibilityData");
    _correctedVis = (CorrectedVisibilityData*) createBlob("CorrectedVisibilityData");
}


/**
 * @details
 */
void TestPipelineCalibrateImage::run(QHash<QString, DataBlob*>& remoteData)
{
    AntennaPositions* antPos = (AntennaPositions*) remoteData["AntennaPositions"];
    VisibilityData* rawVis = (VisibilityData*) remoteData["VisibilityData"];
    Q_ASSERT(antPos);
    Q_ASSERT(rawVis);

    _modelVis->setTimeStamp(rawVis->timeStamp());
    _modelGen->run(antPos, _modelVis);
//    _calibrate->run(rawVis, _modelVis, _correctedVis);

    _imager->run(_rawImage, antPos, rawVis);
    _imager->run(_psfImage, antPos);

    _imagerModel->run(_modelImage, antPos, _modelVis);
//    _imager->run(_calImage, antPos, _correctedVis);
//
//    _imageCombiner->run(_calImage, _modelImage, _diffImage);

    _fitsWriter->run(_rawImage, "calibPipe-raw");
    _fitsWriter->run(_psfImage, "calibPipe-psf");
    _fitsWriter->run(_modelImage, "calibPipe-model");
//    _fitsWriter->run(_calImage, "calibPipe-calibrated");
//    _fitsWriter->run(_diffImage, "calibPipe-diff_cal-model");

    stop();
}

} // namespace astro
} // namespace pelican
