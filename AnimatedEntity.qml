import Qt3D.Core 2.15
import Qt3D.Render 2.7
import Qt3D.Input 2.0
import Qt3D.Extras 2.15

import QtQuick 2.0 as QQ2
import QtQml


Entity {
    id: sceneRoot
//    property RenderCapabilities capabilities : renderSettings.renderCapabilities

    Camera {
        id: camera
        projectionType: CameraLens.PerspectiveProjection
        fieldOfView: 45
        nearPlane : 0.1
        farPlane : 1000.0
        position: Qt.vector3d( 0.0, 0.0, 10.0 )
        upVector: Qt.vector3d( 0.0, 1.0, 0.0 )
        viewCenter: Qt.vector3d( 0.0, 0.0, 0.0 )
    }

//    FirstPersonCameraController { camera: camera }

    components: [
        RenderSettings {
            id: renderSettings
            activeFrameGraph: ForwardRenderer {
                camera: camera
                clearColor: "Transparent"
            }
        },
        InputSettings { }
    ]

    PhongMaterial {
        id: material
    }

    Mesh {
        id: hmdMesh
        source: "qrc:///resources/Stanford_Bunny_sample.stl"
    }

    Transform {
        id: hmdTransform
        scale3D: Qt.vector3d(1., 1., 1.)
        rotation: fromEulerAngles(-90,0,-90)
    }

    Entity {
        id: hmdEntity
        components: [hmdMesh, material, hmdTransform]
    }

    function setScale(amount){
        torusTransform.setScale(amount)
    }
}
