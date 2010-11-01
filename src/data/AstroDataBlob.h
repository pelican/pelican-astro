#ifndef ASTRO_DATABLOB_H
#define ASTRO_DATABLOB_H

/**
 * @file AstroDataBlob.h
 */

#include "pelican/data/DataBlob.h"

#include <QtCore/QString>
#include <QtCore/QSysInfo>
#include <complex>

class QIODevice;

namespace pelican {
namespace astro {

/**
 * @class AstroDataBlob
 *
 * @brief
 *
 * @details
 */

class AstroDataBlob : public DataBlob
{
    public:
        AstroDataBlob(const QString& type);

        /// Data blob destructor.
        virtual ~AstroDataBlob() {}

    public:
        /// Sets the time stamp using the current value of the system clock.
        void setTimeStamp();

        /// Sets the time stamp to the given value.
        void setTimeStamp(double timeStamp) {_modifiedJulianDate = timeStamp;}

        /// Returns the MJD timestamp of the data blob.
        double timeStamp() const { return _modifiedJulianDate; }

    private:
        /// The timestamp of the data blob, stored as a modified Julian
        /// date (MJD). Note that MJD = JD - 2400000.5, and starts
        /// from midnight rather than midday.
        double _modifiedJulianDate;
};

} // namespace astro
} // namespace pelican
#endif // ASTRO_DATABLOB_H
