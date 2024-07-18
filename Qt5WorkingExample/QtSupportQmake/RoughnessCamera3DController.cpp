// Copyright (c) 2020 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific.

#pragma warning(push, 1)
#include <Qt3DRender/QCamera>
#include <Qt3DCore/QTransform>
#pragma warning(pop)

#include "RoughnessCamera3DController.h"

namespace PhenomWorld {
namespace FullHDUI {
namespace Roughness {

RoughnessCamera3DController::RoughnessCamera3DController(Qt3DCore::QNode *parent)
    : QAbstractCameraController(parent)
{
    QObject::connect(this, &QAbstractCameraController::cameraChanged, this, &RoughnessCamera3DController::setCameraVectors);
}

bool RoughnessCamera3DController::getEnabled() const
{
    return m_enabled;
}

void RoughnessCamera3DController::setEnabled(bool enabled)
{
    if (enabled == m_enabled)
    {
        return;
    }
    m_enabled = enabled;
    emit enabledChanged(m_enabled);
}

float normalizeRadian(float radian)
{
    if (radian > 2.f*M_PI)
    {
        return radian - 2.f*M_PI;
    }
    if (radian < 0)
    {
        return radian + 2.f*M_PI;
    }
    return radian;
}

float clipPitch(float radian)
{
    return qBound(static_cast<float>(-M_PI_2), radian, 0.f);
}

void RoughnessCamera3DController::moveCamera(const Qt3DExtras::QAbstractCameraController::InputState &state, float dt)
{
    Q_UNUSED(dt)
    if (!m_enabled || !camera())
    {
        return;
    }

    if (state.rightMouseButtonActive)
    {
        if (!qFuzzyIsNull(state.rxAxisValue))
        {
            m_xyAngle = normalizeRadian(m_xyAngle - 2.f*state.rxAxisValue*M_PI/100.0f);
        }
        if (!qFuzzyIsNull(state.ryAxisValue))
        {
            m_pitchAngle = clipPitch(m_pitchAngle + 2.f*state.ryAxisValue*M_PI/100.0f);

        }
    }
    if (!qFuzzyIsNull(state.tzAxisValue))
    {
        m_distance *= std::pow(1.1f, -state.tzAxisValue);
    }
    setCameraVectors();
}

void RoughnessCamera3DController::setCameraVectors()
{
    if (auto cam = camera())
    {
        auto pitchRotation = QQuaternion::fromEulerAngles(0, m_pitchAngle*180.0f/M_PI, 0);
        auto yawRotation = QQuaternion::fromEulerAngles(0, 0, m_xyAngle*180.0f/M_PI);
        auto rotation = yawRotation*pitchRotation;
        cam->setPosition(m_distance * rotation.rotatedVector(QVector3D(1, 0, 0)).normalized());
        cam->setUpVector(rotation.rotatedVector(QVector3D(0, 0, 1)).normalized());
        cam->setViewCenter(QVector3D(0, 0, 0));
        cam->setFieldOfView(m_fov);
    }
}

} // namespace Roughness
} // namespace FullHDUI
} // namespace PhenomWorld
