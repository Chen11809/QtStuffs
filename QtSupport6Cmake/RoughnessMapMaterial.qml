import Qt3D.Core
import Qt3D.Render
import Qt3D.Extras

import RoughnessPlugin 1.0

// Note that OpenGL ES is currently not supported
Material {
    id: root

    property alias diffuseImage: diffuseTextureImage.image
    property alias drawingImage: drawingTextureImage.image

    parameters: [
        Parameter {
            name:  "diffuseTexture"
            value: Texture2D {
                id: diffuseTexture
                minificationFilter: Texture.LinearMipMapLinear
                magnificationFilter: Texture.Linear
                wrapMode {
                    x: WrapMode.ClampToEdge
                    y: WrapMode.ClampToEdge
                }
                generateMipMaps: true
                maximumAnisotropy: 16.0
                RoughnessTextureImage { id: diffuseTextureImage }
            }
        },
        Parameter {
            name: "drawingTexture"
            value: Texture2D {
                id: drawingTexture
                minificationFilter: Texture.LinearMipMapLinear
                magnificationFilter: Texture.Linear
                wrapMode {
                    x: WrapMode.Repeat
                    y: WrapMode.Repeat
                }
                generateMipMaps: true
                maximumAnisotropy: 16.0
                RoughnessTextureImage { id: drawingTextureImage }
            }
        }
    ]

    effect: Effect {

        property string vertex: "qrc:/Shaders/gl3/roughnessMap.vert"
        property string fragment: "qrc:/Shaders/gl3/roughnessMap.frag"
        property string vertexRHI: "qrc:/Shaders/gl45/roughnessMap.vert"
        property string fragmentRHI: "qrc:/Shaders/gl45/roughnessMap.frag"

        FilterKey {
            id: forward
            name: "renderingStyle"
            value: "forward"
        }

        ShaderProgram {
            id: gl3Shader
            vertexShaderCode: loadSource(parent.vertex)
            fragmentShaderCode: loadSource(parent.fragment)
        }
        ShaderProgram {
            id: rhiShader
            vertexShaderCode: loadSource(parent.vertexRHI)
            fragmentShaderCode: loadSource(parent.fragmentRHI)
        }

        techniques: [
            Technique {
                filterKeys: [forward]
                graphicsApiFilter {
                    api: GraphicsApiFilter.OpenGL
                    profile: GraphicsApiFilter.CoreProfile
                    majorVersion: 3
                    minorVersion: 1
                }
                renderPasses: RenderPass {
                    shaderProgram: gl3Shader
                }
            },
            // RHI 1.0
            Technique {
                filterKeys: [forward]
                graphicsApiFilter {
                    api: GraphicsApiFilter.RHI
                    profile: GraphicsApiFilter.NoProfile
                    majorVersion: 1
                    minorVersion: 0
                }
                renderPasses: RenderPass {
                    shaderProgram: rhiShader
                }
            }
        ]

    }
}
