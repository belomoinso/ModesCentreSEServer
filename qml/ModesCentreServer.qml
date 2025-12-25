import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.9
import QtQuick.Controls 2.15
import modescentreserver 1.0

Window {
    visible: true
    width: 450
    height: 850
    title: qsTr("Эмулятор сервера Modes Centre SE")

    property ModesCentreServer modesCentreServer: ModesCentreServer{}
    property int verticalSpacing: 30
    property int textSize: 20


    GridLayout {
        id: gr
        anchors.fill: parent
        columns: 2
        anchors.margins: 20
        columnSpacing: 150

        Button {
            Layout.columnSpan: 2
            text: "Сгенерировать"
            onClicked: modesCentreServer.model.generateValues()
        }
        Row {
            Layout.columnSpan: 2
            height: 5
        }

        Text {
            Layout.alignment: Qt.AlignLeft
            font.pixelSize: textSize
            text: "Сегодня"
        }

        Text {
            Layout.alignment: Qt.AlignLeft
            font.pixelSize: textSize
            text: "Завтра"
        }

        Row {
            Layout.columnSpan: 2
            height: 5
        }

        Column {
            Layout.fillWidth: true
            Layout.fillHeight: true
            ListView {
                spacing: verticalSpacing
                width: parent.width
                height: parent.height
                model: modesCentreServer.model
                delegate: Item {
                    GridLayout {
                        columnSpacing: 30
                        anchors.fill: parent
                        columns: 2

                        Text {
                            font.pixelSize: textSize
                            text: model.hour
                        }
                        TextField {
                            property var regExp: /^[0-9]+(\.([0-9]{0,2})?)?$/
                            property string previousValidText
                            implicitWidth: 100
                            implicitHeight: 30
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignRight
                            height: 30
                            text: model.today
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
                                model.today = text
                            }
                            onTextChanged: {
                                if (model.today !== text)
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

        Column {
            Layout.fillWidth: true
            Layout.fillHeight: true
            ListView {
                spacing: verticalSpacing
                width: parent.width
                height: parent.height
                model: modesCentreServer.model
                delegate: Item {
                    GridLayout {
                        columnSpacing: 20
                        anchors.fill: parent
                        columns: 2

                        Text {
                            font.pixelSize: textSize
                            text: model.hour
                        }
                        TextField {
                            property var regExp: /^[0-9]+(\.([0-9]{0,2})?)?$/
                            property string previousValidText
                            implicitWidth: 100
                            implicitHeight: 30
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignRight
                            height: 30
                            text: model.tomorrow
                            font.pixelSize: 17
                            background: Rectangle {
                                    id: bordRec
                                    property string borderColor: "gray"
                                    color: "transparent"
                                    border.color: borderColor
                                    border.width: 1
                                    anchors.margins: 0
                                    radius: 4
                                }
                            onAccepted: {
                                bordRec.borderColor = "gray"
                                model.tomorrow = text
                            }
                            onTextChanged: {
                                if (model.tomorrow !== text)
                                    bordRec.borderColor = "red"
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

    }

}
