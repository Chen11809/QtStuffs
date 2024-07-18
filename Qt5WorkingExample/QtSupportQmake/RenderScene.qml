import QtQuick 2.13
import QtQuick.Scene3D 2.13
import Qt3D.Render 2.13

Scene3D {
    id: scene
    focus: true
    aspects: ["input", "logic"]
    hoverEnabled: true

    // Use AutomaticAspectRatio which doesn't deform the model but only scales with height changes.
    // Note that UserAspectRatio deforms the model by scaling with the viewport in both directions.
    cameraAspectRatioMode: Scene3D.AutomaticAspectRatio
    property Camera camera: entity.camera


    RenderEntity {
        id: entity
        //heightmap: //TODO heightmap
        textureImage: textureHeatmap
        //lineModel: null
        lockedToTopView: false
    }
}
