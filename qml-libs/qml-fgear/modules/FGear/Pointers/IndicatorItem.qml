import QtQuick 2.2

Image {
    id: _indicator

    property Item parentIndicator;

    property string indicatorName: name

    property alias transformX: _linearTranslate.x
    property alias transformY: _linearTranslate.y
    property alias transformAngle: _circularTranslate.angle
    source: imageSource

    Component.onCompleted: {

        switch (indicatorType) {
        case "linear":
            _linearTranslate.x = Qt.binding(function(){
                var _transform_value;
                _transform_value = value;
                _transform_value = Math.min(Math.max(minValue, _transform_value), maxValue);
                return _transform_value;
            });
            _linearTranslate.animated = animation;
            break;
        case "circular":
            transformOrigin = Item.Center;
            _circularTranslate.angle = Qt.binding(function(){
                var _transform_value;
                _transform_value = value;

                if (minValue != 0 && maxValue != 0) {
                    _transform_value = Math.min(Math.max(minValue, _transform_value), maxValue);
                } else {
                    _transform_value = _transform_value % 360;
                }

                return _transform_value;
            });
            _circularTranslate.animated = animation;
            break;
        default:
            break;
        }

            console.log( name, "completed");
        }

            Translate {
                id: _linearTranslate
                property bool animated: false
                Behavior on x {
                    enabled: _linearTranslate.animated
//                    SmoothedAnimation {}
                    SpringAnimation { spring: 2; damping: 0.2; modulus: 360 }
                }
                Behavior on y {
                    enabled:_linearTranslate.animated
//                    SmoothedAnimation {}
                    SpringAnimation { spring: 2; damping: 0.2; modulus: 360 }
                }
            }
            Rotation {
                id: _circularTranslate
                property bool animated: false
                origin.x: width / 2;
                origin.y: height / 2;
                angle: 0
                Behavior on angle {
                    enabled: _circularTranslate.animated
//                    SmoothedAnimation {}
                    SpringAnimation { spring: 2; damping: 0.2; modulus: 360 }
                }
            }
    transform: [ _linearTranslate, _circularTranslate ]

            onParentIndicatorChanged: {
                if (parentIndicator == 0) {
                    console.error("Can nor anchor to the undefined parent indicator");
                }
                console.log(name, "->", parentIndicator.indicatorName);
                _circularTranslate.angle = Qt.binding(function(){ return parentIndicator.transformAngle; });
                _linearTranslate.x = Qt.binding(function(){ return parentIndicator.transformX; });
                _linearTranslate.y = Qt.binding(function(){ return parentIndicator.transformX; })
            }
        }
