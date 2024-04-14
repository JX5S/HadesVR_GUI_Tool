import QtQuick 2.0
import QtQuick.Scene3D 2.0
import Qt3D.Render 2.15

Item {
    Scene3D {
        id: scene3d
        anchors.fill: parent
        anchors.margins: 0
        focus: true
        aspects: ["input", "logic"]
        cameraAspectRatioMode: Scene3D.AutomaticAspectRatio

        AnimatedEntity {
            id: rootEntity
        }
    }

    function startAnimationCpp(){
//        animation.start()
//        rootEntity.setScale(10)
    }
}
