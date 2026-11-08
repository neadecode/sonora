import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic

ApplicationWindow {
    id: sonoraGui
    visible: true
    width: 800
    height: 600

    property color headerHoverColorDark: "#4D4D4D"
    property color headerColorDarkMode: "#262626"

    background: Rectangle {
        color: "#212325"
    }

    header: Rectangle {
        id: menuWrapper
        property int tb_height: 20
        property int tb_fontSize: 10
        property int tb_widthPadding: 10

        width: sonoraGui.width
        height: tb_height
        color: "#262626"

        RowLayout {
            spacing: 0

            MenuOption {
                menuTitle: qsTr("File")
                menuItemsModel: [
                    { text: qsTr("New Project"), triggered: 0 },
                    { text: qsTr("New Project"), triggered: 0 }
                ]
            }

            MenuOption {
                menuTitle: qsTr("Track")
                menuItemsModel: [
                    { text: qsTr("New Project"), triggered: 0 },
                    { text: qsTr("New Project"), triggered: 0 }
                ]
            }
        }
    }

    footer: Rectangle {
        height: header.tb_height
    }
}
