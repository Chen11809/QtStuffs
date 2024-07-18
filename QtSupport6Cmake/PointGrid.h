// Copyright (c) 2020 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific.

#pragma once

#pragma warning( push, 1 )
#include <QObject>
#include <QSize>
#include <QVector>
#include <QVector3D>
#pragma warning( pop )

namespace PhenomWorld {
namespace FullHDUI {
namespace Roughness {
namespace HitDetection {

/*!
 * \brief A point grid is a list of points with a size, where the size describes the number of rows and columns.
 */
class PointGrid
{
    Q_GADGET
public:
    PointGrid() = default;
    PointGrid(const QVector<QVector3D>& points, const QSize& size);
    bool isEmpty() const;
    const QVector<QVector3D>& getPoints() const;
    const QSize& getSize() const;
    const QVector3D& getPoint(int x, int y) const;

private:
    QVector<QVector3D> m_points;
    QSize m_size;
};

} // namespace HitDetection
} // namespace Roughness
} // namespace FullHDUI
} // namespace PhenomWorld

