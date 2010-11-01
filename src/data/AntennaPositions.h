#ifndef ANTENNAPOSITIONS_H
#define ANTENNAPOSITIONS_H

/**
 * @file AntennaPositions.h
 */

#include "pelican/data/DataBlob.h"
#include <vector>
using std::vector;

namespace pelican {
namespace astro {

/**
 * @class AntennaPositions
 *
 * @brief
 * Container class to hold antenna positions.
 *
 * @details
 * This class holds antenna positions for a telescope.
 */
class AntennaPositions : public DataBlob
{
    public:
        typedef double Real;

    public:
        /// Constructs an empty antenna positions data blob.
        AntennaPositions() : DataBlob("AntennaPositions") {}

        /// Constructs and assigns memory for an antenna positions data blob.
        AntennaPositions(unsigned nAntennas) : DataBlob("AntennaPositions")
        { resize(nAntennas); }

    public:
        /// Clears the antenna positions data.
        void clear();

        /// Assign memory for antenna positions.
        void resize(unsigned nAntennas);

    public:
        /// Returns the number of antennas for which positions are held.
        unsigned nAntennas() const { return _x.size(); }

        /// Returns a reference to the x coordinate antenna position for
        /// antenna \p i.
        Real & x(unsigned i) { return _x[i]; }

        /// Returns a reference to the y coordinate antenna position for
        /// antenna \p i.
        Real & y(unsigned i) { return _y[i]; }

        /// Returns a reference to the z coordinate antenna position for
        /// antenna \p i.
        Real & z(unsigned i) { return _z[i]; }

        /// Returns a reference to the vector for the x antenna positions.
        vector<Real> & x() { return _x; }

        /// Returns a reference to the vector for the y antenna positions.
        vector<Real> & y() { return _y; }

        /// Returns a reference to the vector for the z antenna positions.
        vector<Real> & z() { return _z; }

        /// Returns a pointer to the x antenna positions.
        Real * xPtr() { return _x.size() > 0 ? &_x[0] : 0; }

        /// Returns a pointer to the y antenna positions.
        Real * yPtr() { return _y.size() > 0 ? &_y[0] : 0; }

        /// Returns a pointer to the z antenna positions.
        Real * zPtr() { return _z.size() > 0 ? &_z[0] : 0; }

        /// Returns a pointer to the x antenna positions.
        Real const * xPtr() const { return _x.size() > 0 ? &_x[0] : 0; }

        /// Returns a pointer to the y antenna positions.
        Real const * yPtr() const { return _y.size() > 0 ? &_y[0] : 0; }

        /// Returns a pointer to the z antenna positions.
        Real const * zPtr() const { return _z.size() > 0 ? &_z[0] : 0; }

    private:
        vector<Real> _x; ///< x coordinate of antenna position in metres.
        vector<Real> _y; ///< y coordinate of antenna position in metres.
        vector<Real> _z; ///< z coordinate of antenna position in metres.
};

} // namespace astro
} // namespace pelican

#endif // ANTENNAPOSITIONS_H
