// Copyright (C) 2015 Klaralvdalens Datakonsult AB (KDAB).
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <Qt3DQuickExtras/qt3dquickwindow.h>
#include <QGuiApplication>

int main(int argc, char* argv[])
{
    qputenv("QT3D_RENDERER", "opengl");

    QGuiApplication app(argc, argv);
    Qt3DExtras::Quick::Qt3DQuickWindow view;

    view.setSource(QUrl("qrc:/main.qml"));
    view.show();

    return app.exec();
}
