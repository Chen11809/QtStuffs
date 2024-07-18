// Copyright (c) 2020 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific.

#pragma once

#pragma warning(push, 1 )
#include <QImage>
#include <QLoggingCategory>
#include <QScopedPointer>
#include <QVector3D>
#include <Qt3DCore/QAttribute>
#include <Qt3DCore/QBuffer>
#include <Qt3DCore/QGeometry>
#pragma warning( pop )

#include "PointGrid.h"

Q_DECLARE_LOGGING_CATEGORY(roughnessGeometryCategory)

namespace PhenomWorld {
namespace FullHDUI {
namespace Roughness {

class RoughnessGeometry : public Qt3DCore::QGeometry
{
    Q_OBJECT
    Q_PROPERTY(HitDetection::PointGrid pointGrid READ getPointGrid WRITE setPointGrid NOTIFY pointGridChanged)
    Q_PROPERTY(int vertexCount READ getVertexCount NOTIFY vertexCountChanged)
    Q_PROPERTY(int indexCount READ getIndexCount NOTIFY indexCountChanged)

public:
    explicit RoughnessGeometry(QNode* parent = nullptr);

    const HitDetection::PointGrid& getPointGrid();
    void setPointGrid(const HitDetection::PointGrid& pointGrid);

    int getVertexCount() const;
    int getIndexCount() const;

signals:
    void pointGridChanged();
    void vertexCountChanged(int);
    void indexCountChanged(int);

private:
    void loadImage();
    void setVertexCount(int vertexCount);
    void setIndexCount(int indexCount);

    void update();
    void updateVertices();
    void updateIndices();

    QByteArray createVertexData() const;
    QByteArray createIndexData() const;

private:
    HitDetection::PointGrid m_pointGrid;

    QScopedPointer<Qt3DCore::QAttribute> m_positionAttribute;
    QScopedPointer<Qt3DCore::QAttribute> m_textureAttribute;
    QScopedPointer<Qt3DCore::QAttribute> m_indexAttribute;

    QScopedPointer<Qt3DCore::QBuffer> m_vertexBuffer;
    QScopedPointer<Qt3DCore::QBuffer> m_indexBuffer;

    // Convenience constants about the vertex array structure
    const quint32 m_vertexPositionFloats = 3;
    const quint32 m_vertexPositionSize = static_cast<quint32>(m_vertexPositionFloats * sizeof(float));
    const quint32 m_vertexTextureFloats = 2;
    const quint32 m_vertexTextureSize = static_cast<quint32>(m_vertexTextureFloats * sizeof(float));
    const quint32 m_vertexFloats = m_vertexPositionFloats + m_vertexTextureFloats;
    const quint32 m_vertexSize = static_cast<quint32>(m_vertexFloats * sizeof(float));

    // Convenience constants about the index array structure
    const quint32 m_indexShorts = 1;
    const quint32 m_indexSize = static_cast<quint32>(m_indexShorts * sizeof(uint));
};

} // namespace Roughness
} // namespace FullHDUI
} // namespace PhenomWorld

