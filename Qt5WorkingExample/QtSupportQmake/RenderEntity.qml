import Qt3D.Core 2.10
import Qt3D.Render 2.10
import Qt3D.Input 2.1
import Qt3D.Extras 2.10

import RoughnessPlugin 1.0

Entity {
    id: root

    property var heightmap
    property var textureImage

    property bool lockedToTopView: false
    property real maxViewportHeight2D: 1.1

    property Camera camera: camera3D

    components: [
        RenderSettings {
            activeFrameGraph: ForwardRenderer {
                camera: camera3D
                clearColor: "transparent"
            }
            pickingSettings.pickMethod: PickingSettings.TrianglePicking
            pickingSettings.pickResultMode: PickingSettings.NearestPick
        },
        InputSettings {  }
    ]

    Camera {
        id: camera3D
        projectionType: CameraLens.PerspectiveProjection
        nearPlane: 0.001
        farPlane: 1000
    }

    RoughnessCamera3DController {
        id: camera3DController
        camera: camera3D
        enabled: !lockedToTopView
    }

    Entity {
        components: [ geometry, material ]

        GeometryRenderer {
            id: geometry
            instanceCount: 1
            indexOffset: 0
            firstInstance: 0
            vertexCount: roughnessGeometry.indexCount
            primitiveType: GeometryRenderer.Triangles
            geometry: RoughnessGeometry {
                id: roughnessGeometry
                pointGrid: pointgrid
            }
        }

        RoughnessMapMaterial {
            id: material
            diffuseImage: root.textureImage
        }
    }
}
