import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Extras 2.0

Entity {
    id: root

    property Layer layer
    property Buffer overlapSSBO
    property vector2d winSize

    readonly property Material material: Material {
        parameters: [
            Parameter { name: "OverlapSSBO"; value: root.overlapSSBO },
            Parameter { name: "winSize"; value: root.winSize }
        ]

        effect: Effect {
            techniques: Technique {

                graphicsApiFilter {
                    api: GraphicsApiFilter.OpenGL
                    profile: GraphicsApiFilter.CoreProfile
                    majorVersion: 4
                    minorVersion: 3
                }

                renderPasses: RenderPass {
                    shaderProgram: ShaderProgram {
                        vertexShaderCode: loadSource("qrc:/simpleColor.vert")
                        fragmentShaderCode: loadSource("qrc:/simpleColor.frag")
                    }
                    renderStates: [
                        NoDepthMask {},
                        CullFace {
                            mode: CullFace.NoCulling
                        },
                        DepthTest {
                            depthFunction: DepthTest.LessOrEqual
                        },
                        BlendEquation {
                            blendFunction: BlendEquation.Add
                        },
                        BlendEquationArguments {
                            sourceRgb: BlendEquationArguments.SourceAlpha
                            destinationRgb: BlendEquationArguments.OneMinusSourceAlpha
                        }
                    ]
                }
            }
        }
    }

    readonly property PlaneMesh geometryRenderer: PlaneMesh {
        width: 2.0
        height: 2.0
        meshResolution: Qt.size(2, 2)
    }

    // Plane 1
    Entity {
        readonly property Transform transform: Transform {
            scale: 10
            translation: Qt.vector3d(2.0, -2.0, 0.0)
            rotationX:  90
        }

        components: [layer, geometryRenderer, material, transform]
    }

    // Plane 2
    Entity {
        readonly property Transform transform: Transform {
            scale: 10
            translation: Qt.vector3d(10.0, -10.0, -5.0)
            rotationX:  90
        }

        components: [layer, geometryRenderer, material, transform]
    }
}
