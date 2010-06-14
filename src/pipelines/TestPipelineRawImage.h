#ifndef TESTPIPELINERAWIMAGE_H
#define TESTPIPELINERAWIMAGE_H

#include "pelican/core/AbstractPipeline.h"
#include <QtCore/QString>
#include <QtCore/QHash>

/**
 * @file TestPipelineRawImage.h
 */

namespace pelican {

class DataBlob;

namespace astro {

class ZenithImagerDft;
class ImageWriterFits;
class ImageData;

/**
 * @class TestPipelineRawImage
 *
 * @brief
 *
 * @details
 */
class TestPipelineRawImage : public AbstractPipeline
{
    public:
        TestPipelineRawImage();
        ~TestPipelineRawImage();

    public:
        /// Creates the required modules.
        void init();

        /// Run method for single iteration of the pipeline.
        void run(QHash<QString, DataBlob*>& data);

    private:
        ZenithImagerDft* _imager;
        ImageWriterFits* _fitsWriter;
        ImageData* _image;
};

} // namespace astro
} // namespace pelican

#endif // TESTPIPELINERAWIMAGE_H
