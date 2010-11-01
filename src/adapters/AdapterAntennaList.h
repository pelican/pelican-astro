#ifndef ADAPTERANTENNALIST_H
#define ADAPTERANTENNALIST_H

/**
 * @file AdapterAntennaList.h
 */

#include "pelican/core/AbstractServiceAdapter.h"
#include <QtCore/QDataStream>

namespace pelican {
class ConfigNode;

namespace astro {
class AntennaPositions;

/**
 * @class AdapterAntennaList
 *
 * @brief
 *
 * @details
 */

class AdapterAntennaListDbl : public AbstractServiceAdapter
{
    public:
        typedef double Real;

    public:
        /// Constructs a new AdapterAntennaList object.
        AdapterAntennaListDbl(const ConfigNode& config);

        /// Method to deserialise an antenna list file.
        void deserialise(QIODevice* in);

    private:
        /// Sets antenna positions data blob being read into.
        void _setData();

    private:
        unsigned _nAnt;
        AntennaPositions* _antPos;
};

} // namespace astro
} // namespace pelican

#endif // ADAPTERANTENNALIST_H
