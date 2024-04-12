import QtQuick 2.0
import QtQuick.Scene3D 2.0
import Qt3D.Render 2.15

Item {
//    Rectangle {
//        id: scene
//        anchors.fill: parent
//        anchors.margins: 0
//        color: "White"

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
//    }

    SequentialAnimation {
        id: animation

        PauseAnimation { duration: 500 }
        NumberAnimation {
            to: 0.5
            duration: 1000
            target: scene
            property: "scale"
            easing.type: Easing.OutElastic
        }
        PauseAnimation { duration: 500 }
        NumberAnimation {
            to: 1.0
            duration: 1000
            target: scene
            property: "scale"
            easing.type: Easing.OutElastic
        }
        PauseAnimation { duration: 500 }
    }

    function startAnimationCpp(){
//        animation.start()
        rootEntity.setScale(10)
    }
}
