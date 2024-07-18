// Copyright (c) 2020 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific.

#include "PointGrid.h"

namespace PhenomWorld {
namespace FullHDUI {
namespace Roughness {
namespace HitDetection {

PointGrid::PointGrid(const QVector<QVector3D>& points, const QSize& size)
    : m_points(points)
    , m_size(size)
{
}

bool PointGrid::isEmpty() const
{
    return m_points.isEmpty() &&
            m_size.isEmpty();
}

const QVector<QVector3D>& PointGrid::getPoints() const
{
    return m_points;
}

const QSize& PointGrid::getSize() const
{
    return m_size;
}

const QVector3D& PointGrid::getPoint(int x, int y) const
{
    return m_points[y*m_size.width() + x];
}

} // namespace HitDetection
} // namespace Roughness
} // namespace FullHDUI
} // namespace PhenomWorld
