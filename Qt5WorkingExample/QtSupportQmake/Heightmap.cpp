// Copyright (c) 2020 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific.

#include "Heightmap.h"

Q_LOGGING_CATEGORY(coreHeightmapCategory, "core.heightmap")

namespace PhenomWorld {
namespace FullHDUI {
namespace Roughness {

Heightmap::Heightmap()
{
}

// Heightmap::Heightmap(const HduiImage& physicalImage, const QSizeF& sizeInMeters)
//     : m_physicalImage(physicalImage)
//     , m_sizeInMeters(sizeInMeters)
//     , m_normalizedImage(HduiImage(normalizeImage(m_physicalImage, m_sizeInMeters)))
// {
//     if (isEmpty())
//     {
//         throw HduiException("Empty image not allowed");
//     }
//     if (m_sizeInMeters.isNull() || m_sizeInMeters.isEmpty())
//     {
//         throw HduiException("Image without sizeInMeters not allowed");
//     }
//     m_maxHeight = Processing::MakeStatistics(toPhenomWorld(physicalImage)).max;
// }

// const HduiImage& Heightmap::getPhysicalImage() const
// {
//     return m_physicalImage;
// }

// const HduiImage& Heightmap::getNormalizedImage() const
// {
//     return m_normalizedImage;
// }

bool Heightmap::isEmpty() const
{
    // return m_physicalImage.getIsEmpty();
    return false;
}

QSize Heightmap::sizeInPixels() const
try
{
    return QSize();
    // return isEmpty() ? QSize() : QSize(m_physicalImage.getWidth(), m_physicalImage.getHeight());
}
catch(const std::exception& ex)
{
    qCWarning(coreHeightmapCategory) << "An exception occurred during sizeInPixels:" << ex.what();
    return QSize();
}

QSizeF Heightmap::sizeInMeters() const
{
    return m_sizeInMeters;
}

double Heightmap::maxHeight() const
{
    return m_maxHeight;
}

// HduiImage Heightmap::normalizeImage(const HduiImage& image, const QSizeF& sizeInMeters)
// {
//     if (image.getIsEmpty() || sizeInMeters.isEmpty())
//     {
//         return image;
//     }
//     if (image.getEncoding() != HduiPixelType::Float32)
//     {
//         qCCritical(coreHeightmapCategory) << "Invalid image encoding. Expected Float32, was" << image.getEncoding();
//         throw HduiException("Invalid image encoding");
//     }
//     if (qFuzzyIsNull(sizeInMeters.width() / image.getWidth()))
//     {
//         return image;
//     }
//     return toHdui(toPhenomWorld(image) / (sizeInMeters.width() / image.getWidth()));
// }

} // namespace Roughness
} // namespace FullHDUI
} // namespace PhenomWorld
