#ifndef VISIBILITY_PRINTER_H
#define VISIBILITY_PRINTER_H

#include "pelican/modules/AbstractModule.h"
#include <QtCore/QHash>
#include <QtCore/QString>

/**
 * @file VisibilityPrinter.h
 */

namespace pelican {

class DataBlob;

namespace astro {

class VisibilityData;

/**
 * @class VisibilityPrinter
 *
 * @brief
 * Test module to print out visibilities
 *
 * @details
 *
 */

class VisibilityPrinter : public AbstractModule
{
    public:
        VisibilityPrinter(const ConfigNode& config);
        ~VisibilityPrinter();

    public:
        /// Runs the module
        void run(VisibilityData* vis);

    private:
        unsigned _counter;
};


} // namespace astro
} // namespace pelican

#endif // VISIBILITY_PRINTER_H
