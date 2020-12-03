#include <DataModel.hpp>
#include <GraphRenderer.hpp>


#include <QGuiApplication>

#include <QQmlApplicationEngine>


int main(int argc, char *argv[])
{
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

  qmlRegisterType<ExecutionModel>("io.ossia", 1, 0, "ExecutionModel");
  qmlRegisterType<GraphRenderer>("io.ossia", 1, 0, "GraphRenderer");
  qmlRegisterType<Tick>("io.ossia", 1, 0, "Tick");
  QQmlApplicationEngine engine;
  const QUrl url(QStringLiteral("qrc:/main.qml"));
  QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                   &app, [url](QObject *obj, const QUrl &objUrl) {
    if (!obj && url == objUrl)
      QCoreApplication::exit(-1);
  }, Qt::QueuedConnection);
  engine.load(url);

  return app.exec();
}
