import Qt3D.Core 2.0
import Qt3D.Render 2.0

RenderTarget {
    id: root

    property real width: 1
    property real height: 2

    property alias color : colorAttachment
    property alias depth : depthAttachment

    attachments : [

        RenderTargetOutput {
            objectName : "color"
            attachmentPoint : RenderTargetOutput.Color0
            texture : Texture2D {
                id : colorAttachment
                width : root.width
                height : root.width
                format : Texture.RGBA8_UNorm
                generateMipMaps : false
                magnificationFilter : Texture.Linear
                minificationFilter : Texture.Linear
                wrapMode {
                    x: WrapMode.ClampToEdge
                    y: WrapMode.ClampToEdge
                }
            }
        },
        RenderTargetOutput {
            objectName : "depth"
            attachmentPoint : RenderTargetOutput.Depth
            texture : Texture2D {
                id : depthAttachment
                width : root.width
                height : root.width
                format : Texture.D32F
                generateMipMaps : false
                magnificationFilter : Texture.Linear
                minificationFilter : Texture.Linear
                wrapMode {
                    x: WrapMode.ClampToEdge
                    y: WrapMode.ClampToEdge
                }
            }
        }
    ] // outputs
}
