QT       += core gui sql quickwidgets quickcontrols2 positioning opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    circlemenu.cpp \
    databasemanager.cpp \
    databasemenu.cpp \
    glwidget.cpp \
    linemenu.cpp \
    main.cpp \
    mainwindow.cpp \
    pointmenu.cpp \
    polygonmenu.cpp \
    shapefileselectiondialog.cpp

HEADERS += \
    circlemenu.h \
    databasemanager.h \
    databasemenu.h \
    glwidget.h \
    linemenu.h \
    mainwindow.h \
    pointmenu.h \
    polygonmenu.h \
    shapefileselectiondialog.h

FORMS += \
    circlemenu.ui \
    databasemenu.ui \
    linemenu.ui \
    mainwindow.ui \
    pointmenu.ui \
    polygonmenu.ui

# Default rules for deployment.
RC_ICONS = earthlogo.ico
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qml.qrc \
    shaders.qrc

# GDAL configuration
INCLUDEPATH += C:/OSGeo4W/include
INCLUDEPATH+=C:/Qt/6.7.2/msvc2019_64/include
LIBS += -LC:/OSGeo4W/lib -lgdal

# Set GDAL_DATA and PROJ_LIB environment variables
QMAKE_RPATHDIR += C:/OSGeo4W/share/gdal
QMAKE_RPATHDIR += C:/OSGeo4W/share/proj

DEFINES += GDAL_DATA=\\\"C:/OSGeo4W/share/gdal\\\"
DEFINES += PROJ_LIB=\\\"C:/OSGeo4W/share/proj\\\"

# Copy GDAL DLLs
GDAL_BIN_DIR = C:/OSGeo4W/bin
GDAL_DLLS = $$files($${GDAL_BIN_DIR}/gdal*.dll)
GDAL_DLLS += $$files($${GDAL_BIN_DIR}/ogr_*.dll)
GDAL_DLLS += $$files($${GDAL_BIN_DIR}/proj*.dll)

for(DLL, GDAL_DLLS) {
    QMAKE_POST_LINK += $$quote(cmd /c if exist "$${DLL}" xcopy /y "$${DLL}" "$$OUT_PWD/debug" || echo DLL $${DLL} not found. Skipping.)$$escape_expand(\\n\\t)
}

# Add this line to see more detailed linking information
QMAKE_LFLAGS += -Wl,--verbose

DISTFILES += \
    fragment.frag \
    vertex.vert
