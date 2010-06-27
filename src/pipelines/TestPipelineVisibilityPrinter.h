#ifndef TESTPIPELINEVISIBILITYPRINTER_H
#define TESTPIPELINEVISIBILITYPRINTER_H

#include "pelican/core/AbstractPipeline.h"
#include <QtCore/QString>
#include <QtCore/QHash>

/**
 * @file TestPipelineVisibilityPrinter.h
 */

namespace pelican {

class DataBlob;

namespace astro {

class VisibilityPrinter;

/**
 * @class TestPipelineVisibilityPrinter
 *
 * @brief
 *
 * @details
 */
class TestPipelineVisibilityPrinter : public AbstractPipeline
{
    public:
        TestPipelineVisibilityPrinter();
        ~TestPipelineVisibilityPrinter();

    public:
        /// Creates the required modules.
        void init();

        /// Run method for single iteration of the pipeline.
        void run(QHash<QString, DataBlob*>& data);

    private:
        VisibilityPrinter* _visPrinter;

};

} // namespace astro
} // namespace pelican

#endif // TESTPIPELINEVISIBILITYPRINTER_H
