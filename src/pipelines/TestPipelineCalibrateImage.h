#ifndef TESTPIPELINECALIBRATEIMAGE_H
#define TESTPIPELINECALIBRATEIMAGE_H

#include "pelican/core/AbstractPipeline.h"
#include <QtCore/QString>
#include <QtCore/QHash>

/**
 * @file TestPipelineCalibrateImage.h
 */

namespace pelican {

class DataBlob;

namespace astro {

class ZenithImagerDftDbl;
class ImageWriterFits;
class ZenithModelVisibilities;
class ZenithCalibrater;
class ImageCombiner;

class ModelVisibilityData;
class CorrectedVisibilityData;
class ImageData;

/**
 * @class TestPipelineCalibrateImage
 *
 * @brief
 *
 * @details
 */

class TestPipelineCalibrateImage : public AbstractPipeline
{
    public:
        TestPipelineCalibrateImage();
        ~TestPipelineCalibrateImage();

    public:
        /// Creates the required modules
        void init();

        /// Run method for single iteration of the pipeline
        void run(QHash<QString, DataBlob*>& data);

    private:
        ZenithImagerDftDbl* _imager;
        ZenithImagerDftDbl* _imagerModel;
        ZenithModelVisibilities* _modelGen;
        ImageWriterFits* _fitsWriter;
        ZenithCalibrater* _calibrate;
        ImageCombiner* _imageCombiner;

        ModelVisibilityData* _modelVis;
        CorrectedVisibilityData* _correctedVis;
        ImageData* _calImage;
        ImageData* _rawImage;
        ImageData* _psfImage;
        ImageData* _modelImage;
        ImageData* _diffImage;
};

} // namespace astro
} // namespace pelican

#endif // TESTPIPELINECALIBRATEIMAGE_H
