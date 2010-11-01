#ifndef IMAGECOMBINER_H
#define IMAGECOMBINER_H

/**
 * @file ImageCombiner.h
 */

#include "data/ImageData.h"

#include "pelican/modules/AbstractModule.h"
#include "pelican/utility/ConfigNode.h"
#include "data/Constants.h"

namespace pelican {

class ConfigNode;

namespace astro {

/**
 * @class ImageCombiner
 *
 * @brief
 * Combines two images in various ways.
 *
 * @details
 * This module combines two images in various ways.
 * It can be used to generate difference maps.
 */
class ImageCombiner : public AbstractModule
{
    public:
        typedef ImageData::Real Real;

    public:
        /// Module constructor.
        ImageCombiner(const ConfigNode& config);

        /// Module destructor.
        ~ImageCombiner();

        /// Runs the module.
        void run(const ImageData* in1, const ImageData* in2, ImageData* out);

    private:
        /// Grab configuration options from the config node.
        void _getConfiguration(const ConfigNode& config);

        /// Compute the sum of the two images.
        void _operationSum(unsigned width, unsigned height,
                const Real* in1, const Real* in2, Real* out);

        /// Compute the sum of the two images.
        void _operationSumm(unsigned width, unsigned height,
                const Real* in1, const Real* in2, Real* out);

        /// Compute the mean of the two images.
        void _operationMean(unsigned width, unsigned height,
                const Real* in1, const Real* in2, Real* out);

        /// Multiply the two images.
        void _operationMult(unsigned width, unsigned height,
                const Real* in1, const Real* in2, Real* out);

        /// Divide the two images.
        void _operationDiv(unsigned width, unsigned height,
                const Real* in1, const Real* in2, Real* out);

    private:
        enum {SUM, SUMM, MEAN, MULT, DIV};
        static const unsigned CHANNEL_UNDEF = 100000;
        int _opcode; ///< Type of image operation.

        Real _a1; ///< First image coefficient.
        Real _a2; ///< Second image coefficient.
        Real _a3; ///< Third image coefficient.
        unsigned _nChannels;      ///< Number of channels to output.
        unsigned _nPolarisations; ///< Number of polarisations to output.
        std::vector<unsigned> _channelsInput1;
        std::vector<unsigned> _channelsInput2;
        std::vector<unsigned> _channelsOutput;
        Polarisation _polInput1;
        Polarisation _polInput2;
        Polarisation _polOutput;
};

} // namespace astro
} // namespace pelican
#endif // IMAGECOMBINER_H
