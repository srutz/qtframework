import QtQuick 2.15

Item {

    Rectangle {
        id: page
        anchors.fill: parent
        color: "#ff4040"
    }

    Image {
        id: image1
        source: "/home/sr/stepan.jpg"
        fillMode: Image.PreserveAspectFit
        anchors.fill: parent
        transformOrigin: Item.Center
        transform: Scale { xScale: 1; yScale: 1 }

        states: State {
            name: "rotated1"
            PropertyChanges { target: image1; rotation: 180 }
        }

        transitions: Transition {
            RotationAnimation { duration: 1000; direction: RotationAnimation.Counterclockwise }
        }

        MouseArea {
            anchors.fill: parent
            onPressed: {
                if (image1.state === "rotated1") {
                    image1.state = "";
                } else {
                    image1.state = "rotated1"
                }
            }
        }


    }
}
