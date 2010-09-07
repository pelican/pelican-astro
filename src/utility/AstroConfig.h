#ifndef ASTRO_CONFIG_H
#define ASTRO_CONFIG_H

#include "data/Constants.h"

#include <QtCore/QString>

namespace pelican {
namespace astro {

/**
 * @class AstroConfig
 *
 * @brief
 * Utility class for use with XML configuration specific to astrophysical
 * quantities.
 */

class AstroConfig
{
    public:
        AstroConfig() {}
        ~AstroConfig() {}

    public:
        /// Returns an enum for the polarisation described by an XML attribute value.
        static Polarisation getPolarisation(QString const& value)
        {
            QString pol = value.toLower();
            if (pol.startsWith("x"))
                return POL_X;
            else if (pol.startsWith("y"))
                return POL_Y;
            else if (pol.startsWith("both"))
                return POL_BOTH;
            else
                return POL_UNDEF;
        }

        /// Checks the polarisation consistency between the selection in the
        /// XML configuration and polarisation of input data blobs.
        static void checkPolarisationConsitency(Polarisation dataPol,
                Polarisation modulePol)
        {
            QString name = "AstroConfig::checkPolarisationConsitency()";

            if (dataPol != POL_BOTH)
            {
                if (modulePol == POL_X && dataPol != POL_X)
                {
                    throw QString("%1: Polarisation selection X is inconsistent "
                            "with input data").arg(name);
                }
                if (modulePol == POL_Y && dataPol != POL_Y)
                {
                    throw QString("%1: Polarisation selection Y is inconsistent "
                            "with input data").arg(name);
                }
            }
        }
};


} // namespace astro
} // namespace pelican
#endif // ASTRO_CONFIG_H
