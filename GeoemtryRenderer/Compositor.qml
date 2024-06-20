import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Extras 2.0

Entity {
    id: root
    property Layer layer
    property Texture2D colorTexture
    property Buffer overlapSSBO
    property vector2d winSize

    readonly property PlaneMesh geometryRenderer: PlaneMesh {
        width: 2.0
        height: 2.0
        meshResolution: Qt.size(2, 2)
    }

    readonly property Transform transform: Transform { // We rotate the plane so that it faces us
        rotation: fromAxisAndAngle(Qt.vector3d(1, 0, 0), 90)
    }

    readonly property Material material: Material {
        parameters: [
            Parameter { name: "colorTexture"; value: root.colorTexture },
            Parameter { name: "OverlapSSBO"; value: root.overlapSSBO },
            Parameter { name: "winSize"; value: root.winSize }
        ]
        effect : Effect {
            techniques: Technique {

                graphicsApiFilter {
                    api: GraphicsApiFilter.OpenGL
                    profile: GraphicsApiFilter.CoreProfile
                    majorVersion: 4
                    minorVersion: 3
                }

                renderPasses: RenderPass {
                    shaderProgram: ShaderProgram {
                        vertexShaderCode: loadSource("qrc:/compositor.vert")
                        fragmentShaderCode: loadSource("qrc:/compositor.frag")
                    }
                }
            }
        }
    }

    components : [layer, geometryRenderer, material, transform]
}
