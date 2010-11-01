#ifndef VISIBILITYPOSITIONS_H
#define VISIBILITYPOSITIONS_H

/**
 * @file VisibilityPositions.h
 */

#include "pelican/data/DataBlob.h"
#include <vector>
using std::vector;

namespace pelican {
namespace astro {

/**
 * @class VisibilityPositionsData
 *
 * @brief
 * Visibility positions container class.
 *
 * @details
 * This class holds visibility positions for a telescope.
 * Positions are stored for a reference frequency channel and scaled upon demand.
 * This approach was chosen to save nChannels storage.
 *
 * Visibility positions are indexed by channel then either a pair of antenna ids
 * or and either a pair of antenna index from a list of visibility id's.
 */

class VisibilityPositions : public DataBlob
{
    public:
        typedef double Real;

    public:
        /// Constructs an empty visibility positions data blob.
        VisibilityPositions() : DataBlob("VisibilityPositions") {}

        /// Constructs and assigns memory for a visibility positions data blob.
        VisibilityPositions(unsigned nAntennas) : DataBlob("VisibilityPositions")
        { resize(nAntennas); }

    public:
        /// Clears the visibility positions data
        void clear();

        /// Returns a frequency scaling factor.
        double freqScaleFactor(unsigned channel);

        /// Assign memory for visibility positions
        void resize(unsigned nAntennas);

    public:
        /// Returns the number of antenna for which visibility positions are stored.
        unsigned nAntennas() const { return _nAntennas; }

        /// Returns the number of visibility coordinates held.
        unsigned nVis() const { return _u.size(); }

        /// Returns a reference to the reference frequency channel id.
        unsigned& refChannel() { return _refChannel; }

        /// Returns a reference to the frequency of the reference channel.
        double& refFreq() { return _refFreq; }

        /// Frequency a reference to the increment between channels.
        double& freqInc() { return _freqInc; }

        /// Returns a reference to the u coordinates vector.
        std::vector<Real>& u() { return _u; }

        /// Returns the u coordinate for the visibility i at the reference frequency.
        Real& u(unsigned i) { return _u[i]; }

        /// Returns the u coordinate for the visibility indexed by antennas at
        /// the reference frequency
        Real& u(unsigned a1, unsigned a2)
        { return _u[a2 * _nAntennas + a1]; }

        /// Returns the u coordinate for the visibility indexed by antennas at
        /// the specified frequency
        Real u(unsigned a1, unsigned a2, unsigned channel)
        { return _u[a2 * _nAntennas + a1] * freqScaleFactor(channel); }

        /// Returns a reference to the v coordinates vector.
        std::vector<Real>& v() { return _v; }

        /// Returns the v coordinate for the visibility i at the reference frequency
        Real& v(unsigned i) { return _v[i]; }

        /// Returns the v coordinate for the visibility indexed by antennas at the reference frequency
        Real& v(unsigned a1, unsigned a2)
        { return _v[a2 * _nAntennas + a1]; }

        /// Returns the v coordinate for the visibility indexed by antennas at
        /// the specified frequency
        Real v(unsigned a1, unsigned a2, unsigned channel)
        { return static_cast<Real>(_v[a2 * _nAntennas + a1] * freqScaleFactor(channel)); }

        /// Returns a reference to the u coordinates vector.
        std::vector<Real>& w() { return _w; }

        /// Returns the w coordinate for the visibility \p i at the reference frequency.
        Real& w(unsigned i) { return _w[i]; }

        /// Returns the w coordinate for the visibility indexed by antennas
        /// \p a1, \p a2 at the reference frequency.
        Real& w(unsigned a1, unsigned a2)
        { return _w[a2 * _nAntennas + a1]; }

        /// Returns the w coordinate for the visibility indexed by antennas
        /// \p a1 and \p a2 at the specified frequency channel \p c.
        Real w(unsigned a1, unsigned a2, unsigned channel)
        { return _w[a2 * _nAntennas + a1] * freqScaleFactor(channel); }

        /// Returns a pointer to the u antenna positions.
        Real* uPtr() { return (_u.size() > 0) ? &_u[0] : NULL; }

        /// Returns a pointer to the v antenna positions.
        Real* vPtr() { return (_v.size() > 0) ? &_v[0] : NULL; }

        /// Returns a pointer to the w antenna positions.
        Real* wPtr() { return (_w.size() > 0) ? &_w[0] : NULL; }

    private:
        unsigned _nAntennas;    ///< The number of antennas.
        unsigned _refChannel;   ///< Reference frequency channel id.
        double _refFreq;        ///< Frequency of the reference channel.
        double _freqInc;        ///< Frequency increment between channels.
        vector<Real> _u;        ///< u coordinate of visibility.
        vector<Real> _v;        ///< v coordinate of visibility.
        vector<Real> _w;        ///< w coordinate of visibility.
};

} // namespace astro
} // namespace pelican
#endif // VISIBILITYPOSITIONS_H
