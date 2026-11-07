import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic

ApplicationWindow {
    id: root
    visible: true
    width: 800
    height: 600

    header: ToolBar {
        property int tb_height: 20
        property int tb_fontSize: 10
        property int tb_widthPadding: 10

        property color headerHoverColorDark: "#4D4D4D"
        property color headerColorDarkMode: "#262626"

        height: tb_height

        Rectangle {
            id: menuWrapper
            width: parent.width
            height: parent.height
            color: "#262626"

            RowLayout {
                width: parent
                spacing: 0

                MenuOption {
                    menuTitle: qsTr("File")
                    menuItemsModel: [
                        {
                            text: qsTr("New Project"),
                            triggered: 0
                        },
                        {
                            text: qsTr("New Project"),
                            triggered: 0
                        }
                    ]
                }

                MenuOption {
                    menuTitle: qsTr("Track")
                    menuItemsModel: [
                        {
                            text: qsTr("New Project"),
                            triggered: 0
                        },
                        {
                            text: qsTr("New Project"),
                            triggered: 0
                        }
                    ]
                }
            }
        }
    }
}
