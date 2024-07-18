// Copyright (c) 2020 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific.

#pragma once

#pragma warning(push, 1 )
#include <QLoggingCategory>
#include <Qt3DRender>
#pragma warning( pop )

Q_DECLARE_LOGGING_CATEGORY(roughnessTextureImage)

namespace PhenomWorld {
namespace FullHDUI {
namespace Roughness {

class RoughnessTextureImage : public Qt3DRender::QAbstractTextureImage
{
    Q_OBJECT
    Q_PROPERTY(QImage image READ getImage WRITE setImage NOTIFY imageChanged)

public:
    RoughnessTextureImage(Qt3DCore::QNode* parent = nullptr);

    Qt3DRender::QTextureImageDataGeneratorPtr dataGenerator() const override;

    void invalidate();

    QImage getImage() const;
    void setImage(const QImage& image);

signals:
    void imageChanged();

private:
    QImage m_image;
};

} // namespace Roughness
} // namespace FullHDUI
} // namespace PhenomWorld

