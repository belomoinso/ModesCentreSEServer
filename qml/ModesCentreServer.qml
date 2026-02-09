import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.9
import QtQuick.Controls 2.15
import modescentreserver 1.0

Window {
    visible: true
    width: 650
    height: 850
    title: qsTr("Импорт ПДГ. Клиент/сервер")

    property ModesCentreServer modesCentreServer: ModesCentreServer{}
    property RestApiClient restApiClient: RestApiClient{ model: modesCentreServer.model }
    property int verticalSpacing: 30
    property int textSize: 20

    GridLayout {
        id: gr
        anchors.fill: parent
        columns: 3
        anchors.margins: 20
        columnSpacing: 150

        GridLayout {
            columns: 6
            Layout.columnSpan: 3
            columnSpacing: 14
            Button {
                text: "Сгенерировать"
                onClicked: modesCentreServer.model.generateValues()
            }
            Text {
                Layout.alignment: Qt.AlignLeft
                font.pixelSize: textSize
                text: "IP-адрес"
            }
            TextField {
                property var regExp: /^$|^(?:25[0-5]|2[0-4]\d|1\d{2}|[1-9]\d|[1-9])(?:\.(?:25[0-5]|2[0-4]\d|1\d{2}|[1-9]\d|[0-9])){3}$/
                property string previousValidText
                implicitWidth: 140
                implicitHeight: 30
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignRight
                height: 30
                maximumLength: 15
                text: restApiClient.ipaddr
                font.pixelSize: 17
                background: Rectangle {
                    id: br
                    property string borderColor: "gray"
                    color: "transparent"
                    border.color: borderColor
                    border.width: 1
                    anchors.margins: 0
                    radius: 4
                    }
                onTextChanged: {
                    restApiClient.ipaddr = text
                    if (!regExp.test(text))
                        br.borderColor = "red"
                    else
                        br.borderColor = "gray"
                }
            }
            Text {
                Layout.alignment: Qt.AlignLeft
                font.pixelSize: textSize
                text: "Порт"
            }
            TextField {
                property var regExp: /^(?:[0-5]?[0-9]{1,4}|[6][0-5][0-9]{0,2})$/
                implicitWidth: 60
                implicitHeight: 30
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignRight
                height: 30
                maximumLength: 5
                text: restApiClient.port
                font.pixelSize: 17
                background: Rectangle {
                    id: brR
                    property string borderColor: "gray"
                    color: "transparent"
                    border.color: borderColor
                    border.width: 1
                    anchors.margins: 0
                    radius: 4
                    }
                onTextChanged: {
                    restApiClient.port = parseInt(text, 10)
                    if (!regExp.test(text))
                        brR.borderColor = "red"
                    else
                        brR.borderColor = "gray"
                }
            }
            Button {
                text: "Отправить на сервер"
                onClicked: restApiClient.sendValues()
            }
        }

        Row {
            Layout.columnSpan: 3
            height: 5
        }

        Text {
            Layout.alignment: Qt.AlignLeft
            font.pixelSize: textSize
            text: "Вчера"
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
            Layout.columnSpan: 3
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
                            text: model.yesterday
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
                                model.yesterday = text
                            }
                            onTextChanged: {
                                if (model.yesterday !== text)
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
                                id: bordr
                                property string borderColor: "gray"
                                color: "transparent"
                                border.color: borderColor
                                border.width: 1
                                anchors.margins: 0
                                radius: 4
                                }
                            onAccepted: {
                                bordr.borderColor = "gray"
                                model.today = text
                            }
                            onTextChanged: {
                                if (model.today !== text)
                                    bordr.borderColor = "red"
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
