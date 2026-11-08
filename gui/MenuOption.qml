import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic

ToolButton {
    id: root
    property string menuTitle: "Menu"
    property var menuItemsModel: []
    property bool dropDownOpen: false

    implicitHeight: header.tb_height
    height: header.tb_height
    Layout.preferredWidth: contentItem.implicitWidth + header.tb_widthPadding

    background: Rectangle {
        color: (root.hovered || dropdownMenu.visible) ? sonoraGui.headerHoverColorDark : "transparent"
    }

    contentItem: Text {
        color: "white"
        text: root.menuTitle
        font.pointSize: header.tb_fontSize
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    onClicked: {
        root.dropDownOpen = true;
        dropdownMenu.popup(0, root.height);
    }

    Menu {
        //Esto solo es un holder
        id: dropdownMenu
        Instantiator {
            model: root.menuItemsModel
            //Delegate lo que se va a aniadir
            delegate: MenuItem {
                background: Rectangle {
                    color: sonoraGui.headerHoverColorDark
                }
                topPadding: 1
                bottomPadding: 1
                contentItem: Text {
                    text: modelData.text
                    color: "white"
                }
                action: Action {
                    //Model data depende de la huevada esta del model (l. 36)
                    //Segun lo que haya en el model (una lista), se pone dentro del delegate
                    onTriggered: modelData.triggered()
                }
            }
            onObjectAdded: (i, o) => dropdownMenu.insertItem(i, o)
            onObjectRemoved: (i, o) => dropdownMenu.removeItem(i, o)
        }
    }
}
