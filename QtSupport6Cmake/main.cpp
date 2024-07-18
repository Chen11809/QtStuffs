#include <QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlEngine>
#include <QFile>
#include <QDataStream>
#include <QVector>
#include <QVector3D>

#include "RoughnessCamera3DController.h"
#include "RoughnessGeometry.h"
#include "RoughnessTextureImage.h"
#include "Heightmap.h"
#include "PointGrid.h"


QVector<QVector3D> importVectors(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        throw std::runtime_error("Cannot open file for reading.");
    }

    QVector<QVector3D> vectors;
    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_0); // Ensure the version matches with what was used for writing

    float x, y, z;
    while (!in.atEnd()) {
        in >> x >> y >> z;
        vectors.append(QVector3D(x, y, z));
    }

    return vectors;
}


int main(int argc, char *argv[])
{
    // With setting the environment variable it crashes
    // ASSERT: "QOpenGLContext::currentContext()" in file C:\Users\qt\work\qt\qt3d\src\quick3d\imports\scene3d\scene3drenderer.cpp, line 235
    // without it it does not show anything

    //qputenv("QT3D_RENDERER", QByteArray("opengl"));


{
    // Set OpenGL requirements
    QSurfaceFormat format = QSurfaceFormat::defaultFormat();
#ifndef QT_OPENGL_ES_2
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(3, 1);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setOption(QSurfaceFormat::DebugContext);
#else
    format.setVersion(3, 0);
    format.setProfile(QSurfaceFormat::NoProfile);
    format.setRenderableType(QSurfaceFormat::OpenGLES);
#endif
    QSurfaceFormat::setDefaultFormat(format);
}

    QGuiApplication app(argc, argv);

    // register types
    using namespace PhenomWorld::FullHDUI::Roughness;
    qmlRegisterType<RoughnessCamera3DController>("RoughnessPlugin", 1, 0, "RoughnessCamera3DController");
    qmlRegisterType<RoughnessGeometry>("RoughnessPlugin", 1, 0, "RoughnessGeometry");
    qmlRegisterType<RoughnessTextureImage>("RoughnessPlugin", 1, 0, "RoughnessTextureImage");

    qmlRegisterUncreatableType<Heightmap>("RoughnessPlugin", 1, 0, "heightmap", "Cannot create Heightmap in QML");
    qmlRegisterUncreatableType<HitDetection::PointGrid>("RoughnessPlugin", 1, 0, "pointGrid", "Cannot create PointGrid in QML");


    QQmlApplicationEngine engine;
    QVector<QVector3D> points = importVectors(":/points.txt");
    HitDetection::PointGrid pointGrid(points, {1024,1024});
    QImage texture(":/Images/textureWithHeatmapImage.png");
    engine.rootContext()->setContextProperty(QString("pointgrid"), QVariant::fromValue(pointGrid));
    engine.rootContext()->setContextProperty(QString("textureHeatmap"), texture);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.loadFromModule("QtSupport6Cmake", "Main");

    return app.exec();
}
