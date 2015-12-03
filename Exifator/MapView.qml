// MapView.qml
import QtQuick 2.0
import QtPositioning 5.5
import QtLocation 5.5


Rectangle {
    //width: 360
    height: 300

    Plugin {
        id: myPlugin
        name: "osm"
        //specify plugin parameters if necessary
        //PluginParameter {...}
        //PluginParameter {...}
        //...
    }

    PositionSource {
        id: positionSource
        property variant lastSearchPosition: locationPforzheim
        active: true
        updateInterval: 120000 // 2 mins
        onPositionChanged:  {
            var currentPosition = positionSource.position.coordinate
            map.center = currentPosition
            var distance = currentPosition.distanceTo(lastSearchPosition)
            if (distance > 500) {
                // 500m from last performed pizza search
                lastSearchPosition = currentPosition
                searchModel.searchArea = QtPositioning.circle(currentPosition)
                searchModel.update()
            }
        }
    }

    property variant locationOslo: QtPositioning.coordinate( 59.93, 10.76)
    property variant locationPforzheim: QtPositioning.coordinate( 48.53, 8.41)

    PlaceSearchModel {
        id: searchModel

        plugin: myPlugin

        searchTerm: "Pizza"
        searchArea: QtPositioning.circle(locationPforzheim)

        Component.onCompleted: update()
    }

    Map {
        id: map
        anchors.fill: parent
        plugin: myPlugin;
        center: locationPforzheim
        zoomLevel: 13

        MapItemView {
            model: searchModel
            delegate: MapQuickItem {
                coordinate: place.location.coordinate

                anchorPoint.x: image.width * 0.5
                anchorPoint.y: image.height

                sourceItem: Column {
                    Image { id: image; source: "marker.png" }
                    Text { text: title; font.bold: true }
                }
            }
        }
    }

    Connections {
        target: searchModel
        onStatusChanged: {
            if (searchModel.status == PlaceSearchModel.Error)
                console.log(searchModel.errorString());
        }
    }
}

