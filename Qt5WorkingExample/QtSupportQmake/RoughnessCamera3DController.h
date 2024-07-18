// Copyright (c) 2020 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific.

#pragma once

#pragma warning(push, 1 )
#include <QAbstractCameraController>
#include <QVector3D>
#include <QtMath>
#pragma warning( pop )

namespace PhenomWorld {
namespace FullHDUI {
namespace Roughness {

class RoughnessCamera3DController : public Qt3DExtras::QAbstractCameraController
{
    Q_OBJECT
    Q_PROPERTY(bool enabled READ getEnabled WRITE setEnabled NOTIFY enabledChanged)

public:
    explicit RoughnessCamera3DController(Qt3DCore::QNode *parent = nullptr);

    bool getEnabled() const;
    void setEnabled(bool enabled);

signals:
    void enabledChanged(bool);

private:
    void moveCamera(const Qt3DExtras::QAbstractCameraController::InputState &state, float dt) override;
    void setCameraVectors();

private:
    bool m_enabled = false;
    float m_xyAngle = static_cast<float>(-M_PI_2);
    float m_pitchAngle = -static_cast<float>(M_PI / 4.f);
    float m_distance = 2.0;
    float m_fov = 40.0;
};

} // namespace Roughness
} // namespace FullHDUI
} // namespace PhenomWorld

