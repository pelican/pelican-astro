#ifndef TESTPIPELINESERVER_H
#define TESTPIPELINESERVER_H

#include "pelican/core/AbstractPipeline.h"
#include <QtCore/QString>
#include <QtCore/QHash>

/**
 * @file TestPipelineServer.h
 */

namespace pelican {

class DataBlob;

namespace astro {

class VisibilityPrinter;

/**
 * @class TestPipelineServer
 *
 * @brief
 *
 * @details
 */
class TestPipelineServer : public AbstractPipeline
{
    public:
        TestPipelineServer();
        ~TestPipelineServer();

    public:
        /// Creates the required modules.
        void init();

        /// Run method for single iteration of the pipeline.
        void run(QHash<QString, DataBlob*>& data);

    private:
        VisibilityPrinter* _visPrinter;
        int _counter;

};

} // namespace astro
} // namespace pelican

#endif // TESTPIPELINESERVER_H
