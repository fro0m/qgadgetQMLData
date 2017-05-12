import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0
import qgadgettest 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    SuperModel {
        id: model
    }

   Text {
       anchors.centerIn: parent
       text: "QGadget by value  " + model.superItem.x + " " + model.superItem.y +
             "\nQGadget by pointer  "  + model.superItemP.x + " " + model.superItemP.y

   }
}
