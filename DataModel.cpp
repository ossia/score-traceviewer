#include <DataModel.hpp>
#include <QTimer>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>


ExecutionModel::ExecutionModel()
{
}

void ExecutionModel::parse(const QJsonArray& root)
{
  qDeleteAll(m_ticks);
  m_ticks.clear();

  for(auto value : root) {
    auto t = new Tick(this);

    const auto& obj = value.toObject();
    // obj["Temporal"];
    {
      const auto& df = obj["Dataflow"].toObject();
      t->dataflow()->setGraph(df["Graph"].toString());
      // df["Order"];
    }

    m_ticks.push_back(t);
  }

  ticksChanged();
  QTimer::singleShot(1, [this] { traceLoaded(); });
}

QQmlListProperty<Tick> ExecutionModel::ticks()
{
  return {this, &m_ticks};
}

QString ExecutionModel::path() const
{
  return m_path;
}

void ExecutionModel::setPath(QString path)
{
  if (m_path == path)
    return;

  m_path = path;

  if(QFile f{path}; f.open(QIODevice::ReadOnly)) {
    const QJsonDocument doc = QJsonDocument::fromJson(f.readAll());
    if(doc.isArray()) {
      parse(doc.array());
    }
  }

  emit pathChanged(m_path);
}

QString DataflowTick::graph() const
{
  return m_graph;
}

void DataflowTick::setGraph(QString graph)
{
  if (m_graph == graph)
    return;

  m_graph = graph;
  emit graphChanged(m_graph);
}
