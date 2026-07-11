import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

pragma ComponentBehavior: Bound

ApplicationWindow {
    id: window
    width: 1280
    height: 720
    minimumWidth: 1000
    minimumHeight: 620
    visible: true
    title: "Culina C-100 Touchscreen Simulator"
    color: "#171a1d"
    required property var device
    property int page: 0

    onClosing: function(close) {
        if (!window.device.readyToQuit) {
            close.accepted = false
            window.device.requestShutdown()
        }
    }

    Connections {
        target: window.device
        function onStateChanged() {
            if (window.device.sessionState === "running" || window.device.sessionState === "stopping"
                    || window.device.sessionState === "FAULT")
                window.page = 3
        }
    }

    component TouchButton: Button {
        id: control
        implicitHeight: 54
        font.pixelSize: 18
        font.weight: Font.DemiBold
        contentItem: Text {
            text: control.text
            color: control.enabled ? "#ffffff" : "#737b80"
            font: control.font
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
        background: Rectangle {
            radius: 12
            color: !control.enabled ? "#30363a"
                                    : control.down ? "#278f75" : "#31b795"
        }
    }

    component QuietButton: TouchButton {
        id: quietButton
        background: Rectangle {
            radius: 12
            color: quietButton.down ? "#465056" : "#343b40"
            border.color: "#59636a"
        }
    }

    component MetricCard: Rectangle {
        id: metricCard
        property string metric: ""
        property string label: ""
        color: "#252a2e"
        radius: 16
        implicitHeight: 112
        Column {
            anchors.centerIn: parent
            spacing: 6
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: metricCard.metric
                color: "#f4f7f6"
                font.pixelSize: 30
                font.weight: Font.DemiBold
            }
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: metricCard.label
                color: "#9aa4a9"
                font.pixelSize: 14
                font.letterSpacing: 1
            }
        }
    }

    RowLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 18

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumWidth: 650
            color: "#0d1012"
            radius: 28
            border.color: "#343a3e"
            border.width: 5
            clip: true

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 30
                spacing: 20

                RowLayout {
                    Layout.fillWidth: true
                    Text {
                        text: "CULINA"
                        color: "#31b795"
                        font.pixelSize: 22
                        font.weight: Font.Bold
                        font.letterSpacing: 3
                    }
                    Item { Layout.fillWidth: true }
                    Text {
                        text: window.device.lidState + "  ·  " + window.device.sessionState
                        color: "#aab3b7"
                        font.pixelSize: 15
                    }
                }

                StackLayout {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    currentIndex: window.page

                    ColumnLayout {
                        spacing: 22
                        Text {
                            Layout.alignment: Qt.AlignHCenter
                            text: "What would you like to cook?"
                            color: "#f5f7f7"
                            font.pixelSize: 32
                            font.weight: Font.DemiBold
                        }
                        RowLayout {
                            Layout.fillWidth: true
                            spacing: 16
                            MetricCard {
                                Layout.fillWidth: true
                                metric: window.device.temperature.toFixed(1) + " °C"
                                label: "BOWL"
                            }
                            MetricCard {
                                Layout.fillWidth: true
                                metric: window.device.weight + " g"
                                label: "WEIGHT"
                            }
                            MetricCard {
                                Layout.fillWidth: true
                                metric: window.device.rpm + ""
                                label: "RPM"
                            }
                        }
                        Item { Layout.fillHeight: true }
                        RowLayout {
                            Layout.fillWidth: true
                            spacing: 18
                            TouchButton {
                                Layout.fillWidth: true
                                Layout.preferredHeight: 90
                                text: "Manual cooking"
                                onClicked: window.page = 1
                            }
                            TouchButton {
                                Layout.fillWidth: true
                                Layout.preferredHeight: 90
                                text: "Guided recipes"
                                onClicked: window.page = 2
                            }
                        }
                    }

                    ColumnLayout {
                        spacing: 18
                        Text {
                            text: "Manual cooking"
                            color: "#f5f7f7"
                            font.pixelSize: 32
                            font.weight: Font.DemiBold
                        }
                        GridLayout {
                            Layout.fillWidth: true
                            columns: 3
                            columnSpacing: 18
                            rowSpacing: 10
                            Text { text: "Temperature"; color: "#9aa4a9"; font.pixelSize: 16 }
                            Text { text: "Speed"; color: "#9aa4a9"; font.pixelSize: 16 }
                            Text { text: "Duration"; color: "#9aa4a9"; font.pixelSize: 16 }
                            SpinBox {
                                id: temperature
                                Layout.fillWidth: true
                                from: 37; to: 160; value: 80
                                editable: true
                                font.pixelSize: 24
                            }
                            SpinBox {
                                id: speed
                                Layout.fillWidth: true
                                from: 0; to: 10; value: 2
                                font.pixelSize: 24
                            }
                            SpinBox {
                                id: duration
                                Layout.fillWidth: true
                                from: 1; to: 1440; value: 15
                                editable: true
                                font.pixelSize: 24
                            }
                            Text { text: temperature.value + " °C"; color: "#f5f7f7"; font.pixelSize: 22 }
                            Text { text: "Level " + speed.value; color: "#f5f7f7"; font.pixelSize: 22 }
                            Text { text: duration.value + " min"; color: "#f5f7f7"; font.pixelSize: 22 }
                        }
                        Item { Layout.fillHeight: true }
                        RowLayout {
                            Layout.fillWidth: true
                            QuietButton { text: "Back"; Layout.preferredWidth: 140; onClicked: window.page = 0 }
                            Item { Layout.fillWidth: true }
                            TouchButton {
                                text: "Start cooking"
                                Layout.preferredWidth: 240
                                onClicked: {
                                    if (window.device.startManual(temperature.value, speed.value, duration.value))
                                        window.page = 3
                                }
                            }
                        }
                    }

                    ColumnLayout {
                        spacing: 14
                        Text {
                            text: "Guided recipes"
                            color: "#f5f7f7"
                            font.pixelSize: 32
                            font.weight: Font.DemiBold
                        }
                        ListView {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            clip: true
                            spacing: 8
                            model: window.device.recipeNames
                            delegate: Rectangle {
                                id: recipeItem
                                required property int index
                                required property string modelData
                                width: ListView.view.width
                                height: 58
                                radius: 12
                                color: recipeTap.pressed ? "#313a3d" : "#252a2e"
                                Text {
                                    anchors.left: parent.left
                                    anchors.leftMargin: 20
                                    anchors.verticalCenter: parent.verticalCenter
                                    text: recipeItem.modelData
                                    color: "#f4f7f6"
                                    font.pixelSize: 19
                                }
                                TapHandler {
                                    id: recipeTap
                                    onTapped: {
                                        if (window.device.startRecipe(recipeItem.index))
                                            window.page = 3
                                    }
                                }
                            }
                        }
                        QuietButton { text: "Back"; Layout.preferredWidth: 140; onClicked: window.page = 0 }
                    }

                    ColumnLayout {
                        spacing: 18
                        Text {
                            Layout.alignment: Qt.AlignHCenter
                            text: window.device.programName === "-" ? "Finishing" : window.device.programName
                            color: "#f5f7f7"
                            font.pixelSize: 32
                            font.weight: Font.DemiBold
                        }
                        Text {
                            Layout.alignment: Qt.AlignHCenter
                            visible: window.device.progressTotal > 0
                            text: "Step " + window.device.progressCurrent + " of " + window.device.progressTotal
                            color: "#31b795"
                            font.pixelSize: 17
                        }
                        Text {
                            Layout.fillWidth: true
                            Layout.preferredHeight: 70
                            text: window.device.programStatus
                            color: "#dce2e1"
                            font.pixelSize: 24
                            wrapMode: Text.WordWrap
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                        RowLayout {
                            Layout.fillWidth: true
                            spacing: 14
                            MetricCard { Layout.fillWidth: true; metric: window.device.temperature.toFixed(1) + " °C"; label: "BOWL" }
                            MetricCard { Layout.fillWidth: true; metric: window.device.weight + " g"; label: "WEIGHT" }
                            MetricCard { Layout.fillWidth: true; metric: window.device.rpm + ""; label: "RPM" }
                        }
                        Item { Layout.fillHeight: true }
                        RowLayout {
                            Layout.fillWidth: true
                            QuietButton {
                                text: "Stop"
                                Layout.preferredWidth: 180
                                enabled: window.device.sessionState === "running"
                                onClicked: window.device.stop()
                            }
                            Item { Layout.fillWidth: true }
                            TouchButton {
                                text: "Next step"
                                Layout.preferredWidth: 220
                                visible: window.device.awaitingUser
                                onClicked: window.device.nextStep()
                            }
                            TouchButton {
                                text: "Return home"
                                Layout.preferredWidth: 220
                                visible: window.device.sessionState === "done"
                                onClicked: window.page = 0
                            }
                        }
                    }
                }

                Rectangle {
                    Layout.fillWidth: true
                    implicitHeight: visible ? 46 : 0
                    visible: window.device.hotBowl || window.device.fault !== ""
                    radius: 10
                    color: window.device.fault !== "" ? "#7c2d35" : "#81581f"
                    Text {
                        anchors.centerIn: parent
                        text: window.device.fault !== "" ? window.device.fault : "Caution: bowl is hot"
                        color: "white"
                        font.pixelSize: 17
                        font.weight: Font.DemiBold
                    }
                }
            }

            Rectangle {
                anchors.fill: parent
                visible: !window.device.connected
                color: "#e60d1012"
                z: 20
                Column {
                    anchors.centerIn: parent
                    spacing: 12
                    Text { anchors.horizontalCenter: parent.horizontalCenter; text: "MCU disconnected"; color: "#ffffff"; font.pixelSize: 30 }
                    Text { anchors.horizontalCenter: parent.horizontalCenter; text: "Restart the simulator launcher"; color: "#aab3b7"; font.pixelSize: 17 }
                }
            }
        }

        Rectangle {
            Layout.preferredWidth: 290
            Layout.fillHeight: true
            color: "#24292d"
            radius: 18
            border.color: "#3c4449"

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 22
                spacing: 16
                Text {
                    text: "SIMULATOR LAB"
                    color: "#e8eceb"
                    font.pixelSize: 18
                    font.weight: Font.Bold
                    font.letterSpacing: 1.5
                }
                Text {
                    Layout.fillWidth: true
                    text: "These controls represent physical actions outside the touchscreen."
                    color: "#98a2a7"
                    wrapMode: Text.WordWrap
                    font.pixelSize: 14
                }
                Rectangle { Layout.fillWidth: true; Layout.preferredHeight: 1; color: "#41494e" }
                Text { text: "Add ingredient"; color: "#e8eceb"; font.pixelSize: 17 }
                ComboBox {
                    id: ingredient
                    Layout.fillWidth: true
                    model: ["water", "oil", "flour", "other"]
                }
                SpinBox {
                    id: grams
                    Layout.fillWidth: true
                    from: 1; to: 2200; value: 250
                    editable: true
                    textFromValue: function(value) { return value + " g" }
                    valueFromText: function(text) { return parseInt(text) }
                }
                TouchButton {
                    Layout.fillWidth: true
                    text: "Add to bowl"
                    enabled: window.device.controlConnected
                    onClicked: window.device.addIngredient(grams.value, ingredient.currentText)
                }
                Rectangle { Layout.fillWidth: true; Layout.preferredHeight: 1; color: "#41494e" }
                Text { text: "Physical lid"; color: "#e8eceb"; font.pixelSize: 17 }
                RowLayout {
                    Layout.fillWidth: true
                    QuietButton { Layout.fillWidth: true; text: "Open"; onClicked: window.device.setLidOpen(true) }
                    QuietButton { Layout.fillWidth: true; text: "Close"; onClicked: window.device.setLidOpen(false) }
                }
                Item { Layout.fillHeight: true }
                Text {
                    Layout.fillWidth: true
                    text: window.device.controlConnected ? window.device.simulatorStatus : "Control socket disconnected"
                    color: window.device.controlConnected ? "#8fd8c4" : "#ef8d96"
                    wrapMode: Text.WordWrap
                    font.pixelSize: 13
                }
            }
        }
    }
}
