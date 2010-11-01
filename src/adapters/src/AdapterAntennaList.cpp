#include "adapters/AdapterAntennaList.h"
#include "data/AntennaPositions.h"
#include <QtCore/QTextStream>

#include "pelican/utility/memCheck.h"

namespace pelican {
namespace astro {

PELICAN_DECLARE_ADAPTER(AdapterAntennaListDbl)

/**
 * @details
 * Constructs a new antenna list service data adapter.
 */
AdapterAntennaListDbl::AdapterAntennaListDbl(const ConfigNode& config)
    : AbstractServiceAdapter(config)
{
    _nAnt = config.getOption("antennas", "number", "96").toUInt();
}

/**
 * @details
 * Desearalise a LOFAR station antenna list file.
 * Assumes that the QIODevice points to a ascii text file handle.
 */
void AdapterAntennaListDbl::deserialise(QIODevice* in)
{
    _setData();

    QTextStream s(in);

    Real* x = _antPos->xPtr();
    Real* y = _antPos->yPtr();
    Real* z = _antPos->zPtr();
    Real temp;

    for (unsigned a = 0; a < _nAnt; a++) {
        s >> x[a] >> y[a] >> z[a] >> temp >> temp >> temp;
    }
}

/**
 * @details
 */
void AdapterAntennaListDbl::_setData()
{
    if (_chunkSize == 0)
        throw QString("No data to read. Stream chunk size set to zero.");

    if (_data == NULL)
        throw QString("Cannot deserialise into an unallocated blob!");

    _antPos = static_cast<AntennaPositions*>(_data);
    _antPos->resize(_nAnt);
}


} // namespace astro
} // namespace pelican
