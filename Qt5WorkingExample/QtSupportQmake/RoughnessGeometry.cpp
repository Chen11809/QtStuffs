// Copyright (c) 2020 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific.

#pragma warning(push, 1 )
#include <QFile>
#include <QImage>
#include <QRgb>
#include <QTextStream>
#include <QVector3D>
#pragma warning( pop )

#include "RoughnessGeometry.h"

Q_LOGGING_CATEGORY(roughnessGeometryCategory, "roughness.roughnessGeometry")

namespace PhenomWorld {
namespace FullHDUI {
namespace Roughness {

RoughnessGeometry::RoughnessGeometry(Qt3DCore::QNode* parent)
    : QGeometry(parent)
{
    m_vertexBuffer.reset(new Qt3DRender::QBuffer(this));
    m_indexBuffer.reset(new Qt3DRender::QBuffer(this));
    m_positionAttribute.reset(new Qt3DRender::QAttribute());
    m_textureAttribute.reset(new Qt3DRender::QAttribute());
    m_indexAttribute.reset(new Qt3DRender::QAttribute());

    // Attributes
    m_positionAttribute->setName(Qt3DRender::QAttribute::defaultPositionAttributeName());
    m_positionAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
    m_positionAttribute->setBuffer(m_vertexBuffer.data());
    m_positionAttribute->setVertexBaseType(Qt3DRender::QAttribute::Float);
    m_positionAttribute->setVertexSize(m_vertexPositionFloats);
    m_positionAttribute->setByteOffset(0 /*StartOfVertexData*/);
    m_positionAttribute->setByteStride(m_vertexSize);
    m_positionAttribute->setCount(static_cast<uint>(getVertexCount()));

    m_textureAttribute->setName(Qt3DRender::QAttribute::defaultTextureCoordinateAttributeName());
    m_textureAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
    m_textureAttribute->setBuffer(m_vertexBuffer.data());
    m_textureAttribute->setVertexBaseType(Qt3DRender::QAttribute::Float);
    m_textureAttribute->setVertexSize(m_vertexTextureFloats);
    m_textureAttribute->setByteOffset(0 /*StartOfVertexData*/ + m_vertexPositionSize);
    m_textureAttribute->setByteStride(m_vertexSize);
    m_textureAttribute->setCount(static_cast<uint>(getVertexCount()));

    m_indexAttribute->setAttributeType(Qt3DRender::QAttribute::IndexAttribute);
    m_indexAttribute->setBuffer(m_indexBuffer.data());
    m_indexAttribute->setVertexBaseType(Qt3DRender::QAttribute::UnsignedInt);
    m_indexAttribute->setVertexSize(1);
    m_indexAttribute->setByteOffset(0);
    m_indexAttribute->setByteStride(0);
    m_indexAttribute->setCount(static_cast<uint>(getIndexCount()));

    addAttribute(m_positionAttribute.data());
    addAttribute(m_textureAttribute.data());
    addAttribute(m_indexAttribute.data());

    //updateGeometry();
}

const HitDetection::PointGrid& RoughnessGeometry::getPointGrid()
{
    return m_pointGrid;
}

void RoughnessGeometry::setPointGrid(const HitDetection::PointGrid& pointGrid)
try
{
    m_pointGrid = pointGrid;
    update();
}
catch(const std::exception& ex)
{
    qCWarning(roughnessGeometryCategory) << "An exception occurred during setHeightmap:" << ex.what();
}

int RoughnessGeometry::getVertexCount() const
try
{
    return m_pointGrid.getSize().width() * m_pointGrid.getSize().height();
}
catch(const std::exception& ex)
{
    qCWarning(roughnessGeometryCategory) << "An exception occurred during getVertexCount:" << ex.what();
    return 0;
}

int RoughnessGeometry::getIndexCount() const
try
{
    if (getVertexCount() < 4 /* a single square */)
    {
        return 0;
    }
    const int faces = 2 * (m_pointGrid.getSize().width() - 1) * (m_pointGrid.getSize().height() - 1);
    return faces * 3 /* Indices per triangle */ * 2 /* 2 sides instead of culling */;
}
catch(const std::exception& ex)
{
    qCWarning(roughnessGeometryCategory) << "An exception occurred during getIndexCount:" << ex.what();
    return 0;
}

QVector<QVector3D> importVectors(const QString& filename) {
    QFile file(filename);

    QVector<QVector3D> vectors;
    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_0); // Ensure the version matches with what was used for writing

    float x, y, z;
    while (!in.atEnd()) {
        in >> x >> y >> z;
        vectors.append(QVector3D(x, y, z));
    }

    return vectors;
}

void RoughnessGeometry::updateGeometry()
{
    QVector<QVector3D> points = importVectors("C:/points.txt");
    HitDetection::PointGrid pointGrid(points, {1024,1024});
    setPointGrid(pointGrid);
}

void RoughnessGeometry::update()
{
    if (!m_pointGrid.isEmpty())
    {
        updateVertices();
        updateIndices();
    }
}

void RoughnessGeometry::updateVertices()
{
    auto vertexCount = getVertexCount();
    m_positionAttribute->setCount(static_cast<uint>(vertexCount));
    m_textureAttribute->setCount(static_cast<uint>(vertexCount));
    m_vertexBuffer->setData(vertexCount > 0 ? createVertexData() : QByteArray()); // ->setDataGenerator(QSharedPointer<PlaneVertexBufferFunctor>::create(d->m_width, d->m_height, d->m_meshResolution, d->m_mirrored));
    emit vertexCountChanged(vertexCount);
}

void RoughnessGeometry::updateIndices()
{
    auto indexCount = getIndexCount();
    m_indexAttribute->setCount(static_cast<uint>(indexCount));
    m_indexBuffer->setData(indexCount > 0 ? createIndexData() : QByteArray()); // ->setDataGenerator(QSharedPointer<PlaneIndexBufferFunctor>::create(d->m_meshResolution));
    emit indexCountChanged(indexCount);
}

QByteArray RoughnessGeometry::createVertexData() const
{
    Q_ASSERT_X(!m_pointGrid.isEmpty(), "RoughnessGeometry::createVertexData", "Scaled image is empty");
    Q_ASSERT_X(m_pointGrid.getSize().width() == m_pointGrid.getSize().height(),
               "RoughnessGeometry::createVertexData", "Heightmap is not square");

    QByteArray vertexBufferData;
    vertexBufferData.resize(static_cast<int>(m_vertexSize) * getVertexCount());
    float* rawVertexArray = reinterpret_cast<float *>(vertexBufferData.data());

    auto points = m_pointGrid.getPoints();
    auto size = m_pointGrid.getSize();

    for (int row = 0; row < size.height(); row++)
    {
        for (int col = 0; col < size.width(); col++)
        {
            auto point = points[row * size.width() + col];

            // Position x,y,z
            *rawVertexArray++ = point.x();
            *rawVertexArray++ = point.y();
            *rawVertexArray++ = point.z();

            // Texture x,y
            *rawVertexArray++ = point.x() + 0.5f;
            *rawVertexArray++ = -point.y() + 0.5f;
        }
    }
    return vertexBufferData;
}

QByteArray RoughnessGeometry::createIndexData() const
{
    uint horizontalPoints = static_cast<uint>(m_pointGrid.getSize().width());
    uint verticalPoints = static_cast<uint>(m_pointGrid.getSize().height());

    uint indicesPerSquare = 6;
    uint indexCount = (horizontalPoints - 1) * (verticalPoints - 1) * indicesPerSquare * 2 /* 2 sides instead of culling */;

    QByteArray indexBufferData;
    indexBufferData.resize(static_cast<int>(m_indexSize * indexCount));
    uint* rawIndexArray = reinterpret_cast<uint*>(indexBufferData.data());

    for (uint z = 0; z < verticalPoints - 1; z++)
    {
        const uint rowStartIndex = z * horizontalPoints;
        const uint nextRowStartIndex = (z + 1) * horizontalPoints;

        for (uint x = 0; x < horizontalPoints - 1; x++)
        {
            // Create two triangles for each square
            *rawIndexArray++ = rowStartIndex + x;
            *rawIndexArray++ = nextRowStartIndex + x;
            *rawIndexArray++ = rowStartIndex + x + 1;

            *rawIndexArray++ = nextRowStartIndex + x;
            *rawIndexArray++ = nextRowStartIndex + x + 1;
            *rawIndexArray++ = rowStartIndex + x + 1;

            // Also create two triangles on the other side
            *rawIndexArray++ = rowStartIndex + x;
            *rawIndexArray++ = rowStartIndex + x + 1;
            *rawIndexArray++ = nextRowStartIndex + x;

            *rawIndexArray++ = nextRowStartIndex + x;
            *rawIndexArray++ = rowStartIndex + x + 1;
            *rawIndexArray++ = nextRowStartIndex + x + 1;
        }
    }

    return indexBufferData;
}

} // namespace Roughness
} // namespace FullHDUI
} // namespace PhenomWorld
