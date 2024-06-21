// Copyright (C) 2015 Klaralvdalens Datakonsult AB (KDAB).
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 2.2 as QQ2
import Qt3D.Core 2.0
import Qt3D.Render 2.12
import Qt3D.Input 2.0
import Qt3D.Extras 2.0

Entity {
    id: sceneRoot

    Camera {
        id: camera
        projectionType: CameraLens.PerspectiveProjection
        fieldOfView: 45
        aspectRatio: 16/9
        nearPlane : 0.1
        farPlane : 1000.0
        position: Qt.vector3d( 0.0, 0.0, 40.0 )
        upVector: Qt.vector3d( 0.0, 1.0, 0.0 )
        viewCenter: Qt.vector3d( 0.0, 0.0, 0.0 )
    }

    OrbitCameraController { camera: camera }

    readonly property Layer offscreenLayer: Layer{}
    readonly property Layer compositingLayer: Layer{}
    readonly property vector2d winSize: surfaceSelector.surface ? Qt.vector2d(surfaceSelector.surface.width, surfaceSelector.surface.height) : Qt.vector2d(1, 1)

    Buffer {
        id: fragmentOverlapSSBO

        function initializeOverlapSSBO()
        {
            var w = winSize.x;
            var h = winSize.y;
            var bufferData = new Int32Array(w * h);

            for (var i = 0; i < w; ++i) {
                for (var j = 0; j < h; ++j) {
                    bufferData[j * w + i] = 0
                }
            }
            return bufferData;
        }

        data: initializeOverlapSSBO()
    }

    components: [
        RenderSettings {
            activeFrameGraph: RenderSurfaceSelector {
                id: surfaceSelector

                ClearBuffers {
                    clearColor: Qt.rgba(0.5, 0.5, 1, 1)
                    buffers: ClearBuffers.ColorDepthBuffer

                    // Offscreen Pass
                    LayerFilter {
                        layers: offscreenLayer
                        CameraSelector {
                            camera: camera
                            RenderTargetSelector {
                                target: OffscreenRenderTarget {
                                    id: offscreenRenderTarget
                                    width: winSize.x
                                    height: winSize.y
                                }
                            }
                        }
                    }

                    // Compositing Pass
                    LayerFilter {
                        MemoryBarrier{ waitFor: MemoryBarrier.ShaderStorage}
                        layers: compositingLayer
                    }
                }
            }
        },
        // Event Source will be set by the Qt3DQuickWindow
        InputSettings { }
    ]

    OverlappingTriangles {
        layer: offscreenLayer
        overlapSSBO: fragmentOverlapSSBO
        winSize: sceneRoot.winSize
    }

    Compositor {
        layer: compositingLayer
        colorTexture: offscreenRenderTarget.color
        overlapSSBO: fragmentOverlapSSBO
        winSize: sceneRoot.winSize
    }
}
