#ifndef UVFITS_LOADER_H_
#define UVFITS_LOADER_H_

/**
 * @file uvfitsLoader.h
 */

#include "pelican/modules/AbstractModule.h"
#include <fitsio.h>
#include <vector>

#include <QtCore/QMultiHash>
#include <QtCore/QString>

namespace pelican {
namespace astro {

/**
 * @class UvfitsLoader
 *
 * @brief
 * Module to load random groups UV FITS format visibility data files.
 *
 * @details
 * Wrapper on CFITSIO to load UVFITS files into a Pelican visibility data
 * blob.
 * http://heasarc.nasa.gov/docs/software/fitsio/fitsio.html
 *
 * @todo
 * Make this an adapter?
 */

class UvfitsLoader: public pelican::AbstractModule
{
    public:
        typedef enum { SORT_TIME_BASELINE, SORT_UNDEF } uvSort;
        typedef enum { POL_UNDEF } polarisation;

    public:

        /// Module constructor
        UvfitsLoader(const ConfigNode& config);

        /// Module destructor
        virtual ~UvfitsLoader();

        /// Loads the UV fits file into the visibility data.
        void run(VisibilityData* rawVis);

    private:
        /// Read the FITS header.
        void _readHeader();

        /// Read the UV data section.
        void _readData();

        /// Opens the FITS file for reading
        void _open(const QString& fileName);

        /// Closes the FITS file
        void _close();

    private:
        /// Get the configuration from the XML node.
        void _getConfiguration(const ConfigNode& config);


    private: // CFITSIO utility wrappers.

        /// Read a double type value keyword.
        double _readKeyDbl(const QString& key) const;

        /// Read a long type header keyword.
        long _readKeyLng(const QString key) const;

        /// Read a string type header keyword.
        QString _readKeyStr(const QString& key) const;

        /// Read number of long type header keywords.
        /// ie. NAXIS<*> keywords
        void _readKeysLng(const QString key, int start, int end,
                std::vector<long>& values) const;

        /// Read a number of double header keywords.
        void _readKeysDbl(const QString key, int start, int end,
                std::vector<double>& values) const;

        /// Read a number of string type header keywords.
        void _readKeysStr(const QString key, int start, int end,
                std::vector<QString>& values) const;

    private:
        /// Creates an error message to throw.
        QString err(const QString& message);

    private:
        fitsfile* _fits;

    private: // Configuration options
        QString _fileName;
        unsigned _startTime;
        unsigned _endTime;
        unsigned _startChannel;
        unsigned _endChannel;
        unsigned _startPolarisation;
        unsigned _endPolarisation;
        unsigned _pointingRa;
        unsigned _pointingDec;

    private: // FITS header

        long _nGroupsTotal;
        unsigned _nAntennas;

        unsigned _nAxes;
        std::vector<long> _naxis;
        std::vector<QString> _ctype;
        std::vector<double> _crval;
        std::vector<double> _cdelt;
        std::vector<double> _crpix;
        std::vector<double> _crota;
        QMultiHash<QString, unsigned> _axes;

        unsigned _nParametersPerGroup;
        std::vector<QString> _ptype;
        std::vector<double> _pzero;
        std::vector<double> _pscal;
        QMultiHash<QString, unsigned> _parameters;

        uvSort _sortOrder;
};

} // namespace astro
} // namespace pelican

#endif // UVFITS_LOADER_H_
