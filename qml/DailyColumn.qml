import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.9
import QtQuick.Controls 2.15
import modescentreserver 1.0

Column {
    property ModesCentreModel scheduleModel
    property string dayRole
    Layout.fillWidth: true
    Layout.fillHeight: true
    ListView {
        spacing: verticalSpacing
        width: parent.width
        height: parent.height
        model: scheduleModel
        delegate: Item {
            GridLayout {
                columnSpacing: -5
                anchors.fill: parent
                columns: 3

                Text {
                    font.pixelSize: textSize
                    text: model.hour
                }

                CheckBox {
                    scale: 0.8
                    checked: model[dayRole + "Checked"]
                    onCheckedChanged: model[dayRole + "Checked"] = checked
                }
                TextField {
                    property var regExp: /^[0-9]+(\.([0-9]{0,2})?)?$/
                    property string previousValidText
                    implicitWidth: 100
                    implicitHeight: 30
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignRight
                    height: 30
                    text: model[dayRole]
                    font.pixelSize: 17
                    background: Rectangle {
                        id: bord
                        property string borderColor: "gray"
                        color: "transparent"
                        border.color: borderColor
                        border.width: 1
                        anchors.margins: 0
                        radius: 4
                        }
                    onAccepted: {
                        bord.borderColor = "gray"
                        model[dayRole] = text
                    }
                    onTextChanged: {
                        if (model[dayRole] !== text)
                            bord.borderColor = "red"
                        if (text.length == 0)
                            return
                        if (!regExp.test(text))
                            text = previousValidText
                        else
                            previousValidText = text
                    }
                }


            }
        }
    }
}