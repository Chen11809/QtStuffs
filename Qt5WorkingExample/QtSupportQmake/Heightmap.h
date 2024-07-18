// Copyright (c) 2020 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific.

#pragma once

#pragma warning(push, 1 )
#include <QLoggingCategory>
#include <QSize>
#pragma warning( pop )

Q_DECLARE_LOGGING_CATEGORY(coreHeightmapCategory)

namespace PhenomWorld {
namespace FullHDUI {
namespace Roughness {

class Heightmap
{
    Q_GADGET
    Q_PROPERTY(QSizeF sizeInMeters READ sizeInMeters CONSTANT)
    Q_PROPERTY(QSize sizeInPixels READ sizeInPixels CONSTANT)
    Q_PROPERTY(double maxHeight READ maxHeight CONSTANT)

public:
    Heightmap();
    // Heightmap(const HduiImage& physicalImage, const QSizeF& sizeInMeters);

    // const HduiImage& getPhysicalImage() const;
    // const HduiImage& getNormalizedImage() const;

    bool isEmpty() const;
    QSize sizeInPixels() const;
    QSizeF sizeInMeters() const;
    double maxHeight() const;

private:
    // HduiImage normalizeImage(const HduiImage& image, const QSizeF& sizeInMeters);
    // double getPixelDiagonalInMeters(const HduiImage& image, const QSizeF& sizeInMeters) const;

private:
    // HduiImage m_physicalImage;
    QSizeF m_sizeInMeters;
    double m_maxHeight;
    // HduiImage m_normalizedImage;
};

} // namespace Roughness
} // namespace FullHDUI
} // namespace PhenomWorld

Q_DECLARE_METATYPE(PhenomWorld::FullHDUI::Roughness::Heightmap)

