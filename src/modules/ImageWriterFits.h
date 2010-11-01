#ifndef IMAGERWRITERFITS_H_
#define IMAGERWRITERFITS_H_

/**
 * @file ImageWriterFits.h
 */

#include "pelican/modules/AbstractModule.h"

#include <QtCore/QString>
#include <QtCore/QHash>

#include <fitsio.h>
#include <vector>
#include <complex>

namespace pelican {

class ConfigNode;
class DataBlob;

namespace astro {

class ImageData;

/**
 * @class ImageWriterFits
 *
 * @brief
 * Module which will produce a brightness map given a matrix of visibility data.
 *
 * @details
 */

class ImageWriterFits : public AbstractModule
{
    private:
        friend class ImageWriterFitsTest;

    public:
        typedef std::complex<double> Complex;
        typedef double Real;

    public:
        /// Module constructor.
        ImageWriterFits(const ConfigNode& config);

        /// Module destructor.
        ~ImageWriterFits();

        /// Runs the module.
        void run(ImageData* image, const QString& fileName = "");

    public:
        /// Returns a reference to the image output directory.
        QString& directory() { return _directory; }

        /// Returns a reference to the filename.
        QString& fileName() { return _fileName; }

        /// Returns a reference to the filename prefix.
        QString& prefix() { return _prefix; }

        /// Returns a reference to the filename suffix.
        QString& suffix() { return _suffix; }

    private:
        /// Extract the configuration from the XML node, setting defaults
        /// where required.
        void _getConfiguration(const ConfigNode& config);

        /// Opens the FITS image file for writing.
        void _open(const QString& fileName, unsigned nL, unsigned nM,
                unsigned nChan, unsigned nPol, bool overwrite);

        /// Closes the FITS image file.
        void _close();

        /// Write a FITS image header.
        void _writeHeader(ImageData* image);

        /// Write a frequency table extension.
        void _writeFrequencyTable(const std::vector<unsigned>& channels);

        /// Write a FITS image.
        void _writeImage(Real* image, unsigned nL, unsigned nM, unsigned chan,
                unsigned nPol, unsigned pol);

        /// Returns the system date and time as UTC.
        QString _getDate() const;

        /// Write a header key - string value.
        void _writeKey(const QString& keyword, const QString& value,
                const QString& comment = QString());

        /// Write a header key - double value.
        void _writeKey(const QString& keyword, double value,
                const QString& comment = QString());

        /// Write a header key - int value.
        void _writeKey(const QString& keyword, int value,
                const QString& comment = QString());

        /// Write a header key - unsigned value.
        void _writeKey(const QString& keyword, unsigned value,
                const QString& comment = QString());

        /// Write a header history line.
        void _writeHistory(const QString& text);

        /// Write a header comment line.
        void _writeComment(const QString& text);

    private:
        fitsfile* _fits;

        bool _overwrite;
        bool _cube;

        QString _directory;
        QString _fileName;
        QString _prefix;
        QString _suffix;

        QString _date;
        QString _origin;
        QString _telescope;
        QString _instrument;
        QString _observer;
        QString _object;
        QString _author;
        QString _reference;
};

} // namespace astro
} // namespace pelican
#endif // IMAGERFFT_H_
