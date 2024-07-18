// Copyright (c) 2020 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific.

#pragma warning(push, 1 )
#include <Qt3DRender/QTextureImageDataGenerator>
#pragma warning( pop )

#include "RoughnessTextureImage.h"

Q_LOGGING_CATEGORY(roughnessTextureImage, "roughness.roughnessTextureImage")

namespace PhenomWorld {
namespace FullHDUI {
namespace Roughness {

static QImage placeholderImage()
{
  QColor accent = QColor( 0, 0, 0, 0 );
  QColor dark = QColor( 0, 0, 0, 255 );
  QImage image( 2, 2, QImage::Format_RGBA8888 );
  image.setPixelColor( 0, 0, accent );
  image.setPixelColor( 1, 0, dark );
  image.setPixelColor( 0, 1, dark );
  image.setPixelColor( 1, 1, accent );
  return image;
}

class RoughnessTextureImageDataGenerator : public Qt3DRender::QTextureImageDataGenerator
{
public:

    RoughnessTextureImageDataGenerator(const QImage& image)
      : m_image(image)
    {
    }

    virtual Qt3DRender::QTextureImageDataPtr operator()() override
    {
      Qt3DRender::QTextureImageDataPtr dataPtr = Qt3DRender::QTextureImageDataPtr::create();
      dataPtr->setImage(m_image.isNull() ? placeholderImage() : m_image); // Copies image data to the internal byte array
      return dataPtr;
    }

    virtual bool operator ==(const Qt3DRender::QTextureImageDataGenerator& other) const override
    {
        const RoughnessTextureImageDataGenerator* otherGenerator = functor_cast<RoughnessTextureImageDataGenerator>(&other);
        return m_image == otherGenerator->m_image;
    }

    #pragma warning(push)
        #pragma warning(disable: 4996)
        QT3D_FUNCTOR( RoughnessTextureImageDataGenerator )
    #pragma warning(pop)
private:
    QImage m_image;
};

RoughnessTextureImage::RoughnessTextureImage(Qt3DCore::QNode *parent )
  : Qt3DRender::QAbstractTextureImage(parent)
{
}

Qt3DRender::QTextureImageDataGeneratorPtr RoughnessTextureImage::dataGenerator() const
{
    return QSharedPointer<RoughnessTextureImageDataGenerator>::create(m_image);
}

QImage RoughnessTextureImage::getImage() const
{
    return m_image;
}

void RoughnessTextureImage::setImage(const QImage& image)
try
{
    m_image = image;
    notifyDataGeneratorChanged();
}
catch(const std::exception& ex)
{
    qCWarning(roughnessTextureImage) << "An exception occurred during setImage:" << ex.what();
}



} // namespace Roughness
} // namespace FullHDUI
} // namespace PhenomWorld
