#include <QGuiApplication>
#include <QQmlApplicationEngine>
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
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif


    // register types
    using namespace PhenomWorld::FullHDUI::Roughness;
    qmlRegisterType<RoughnessCamera3DController>("RoughnessPlugin", 1, 0, "RoughnessCamera3DController");
    qmlRegisterType<RoughnessGeometry>("RoughnessPlugin", 1, 0, "RoughnessGeometry");
    qmlRegisterType<RoughnessTextureImage>("RoughnessPlugin", 1, 0, "RoughnessTextureImage");

    qmlRegisterUncreatableType<Heightmap>("RoughnessPlugin", 1, 0, "Heightmap", "Cannot create Heightmap in QML");
    qmlRegisterUncreatableType<HitDetection::PointGrid>("RoughnessPlugin", 1, 0, "PointGrid", "Cannot create PointGrid in QML");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QVector<QVector3D> points = importVectors(":/points.txt");
    HitDetection::PointGrid pointGrid(points, {1024,1024});
    QImage texture(":/Images/textureWithHeatmapImage.png");
    engine.rootContext()->setContextProperty(QString("pointgrid"), QVariant::fromValue<HitDetection::PointGrid>(pointGrid));
    engine.rootContext()->setContextProperty(QString("textureHeatmap"), texture);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
