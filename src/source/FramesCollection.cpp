/**
 * @file FramesCollection.cpp
 *
 * A lightweight wrapper for a vector of Frames.
 *
 * This file is part of the Aquila DSP library.
 * Aquila is free software, licensed under the MIT/X11 License. A copy of
 * the license is provided with the library in the LICENSE file.
 *
 * @package Aquila
 * @version 3.0.0-dev
 * @author Zbigniew Siciarz
 * @date 2007-2010
 * @license http://www.opensource.org/licenses/mit-license.php MIT
 * @since 3.0.0
 */

#include "FramesCollection.h"

namespace Aquila
{
    /**
     * Creates the frames collection.
     */
    FramesCollection::FramesCollection():
        m_samplesPerFrame(0)
    {
    }

    /**
     * Destroys the collection, clearing the container.
     */
    FramesCollection::~FramesCollection()
    {
        clear();
    }

    void FramesCollection::divideFrames(const SignalSource &source,
                                        unsigned int samplesPerFrame,
                                        unsigned int samplesPerOverlap)
    {
        m_samplesPerFrame = samplesPerFrame;
        const std::size_t sourceSize = source.getSamplesCount();
        const unsigned int nonOverlapped = samplesPerFrame - samplesPerOverlap;
        const unsigned int framesCount = sourceSize / nonOverlapped;

        m_frames.reserve(framesCount);
        unsigned int indexBegin = 0, indexEnd = 0;
        for (std::size_t i = 0; i < framesCount; ++i)
        {
            // calculate each frame boundaries
            // when frame end exceeds source size, break out
            indexBegin = i * nonOverlapped;
            indexEnd = indexBegin + samplesPerFrame;
            if (indexEnd < sourceSize)
                m_frames.push_back(new Frame(source, indexBegin, indexEnd));
            else
                break;
        }
    }

    void FramesCollection::clear()
    {
        if (m_frames.empty())
            return;

        for(std::size_t i = 0, size = m_frames.size(); i < size; ++i)
        {
            delete m_frames[i];
        }

        m_frames.clear();
    }
}
