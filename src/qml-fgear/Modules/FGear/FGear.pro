TEMPLATE = subdirs

deployment.files += qmldir \
                    *.qml \
                    flight_pic

deployment.path = $$[QT_INSTALL_QML]/FGear
INSTALLS += deployment

OTHER_FILES += $$deployment.files
