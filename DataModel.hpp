#pragma once
#include <QObject>
#include <QQmlListProperty>

struct TemporalTick
    : QObject
{
  Q_OBJECT
public:
  using QObject::QObject;

};

struct DataflowTick
    : QObject
{
  Q_OBJECT
  Q_PROPERTY(QString graph READ graph WRITE setGraph NOTIFY graphChanged)
  QString m_graph;

public:
  using QObject::QObject;

  QString graph() const;
public slots:
  void setGraph(QString graph);
signals:
  void graphChanged(QString graph);
};

struct Tick
    : QObject
{
  Q_OBJECT
  Q_PROPERTY(TemporalTick* temporal READ temporal)
  Q_PROPERTY(DataflowTick* dataflow READ dataflow)

public:
  using QObject::QObject;
  TemporalTick* temporal() noexcept { return &m_temporalTick; }
  DataflowTick* dataflow() noexcept { return &m_dataflowTick; }

private:
  TemporalTick m_temporalTick{this};
  DataflowTick m_dataflowTick{this};
};

struct ExecutionModel
    : QObject
{
  Q_OBJECT
  Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
  Q_PROPERTY(QQmlListProperty<Tick> ticks READ ticks NOTIFY ticksChanged)

  QString m_path;

public:
  ExecutionModel();

  void parse(const QJsonArray& root);

  QQmlListProperty<Tick> ticks();
  QString path() const;


public slots:
  void setPath(QString path);
signals:
  void pathChanged(QString path);
  void traceLoaded();

  void ticksChanged();

private:
  QList<Tick*> m_ticks;
};

Q_DECLARE_METATYPE(DataflowTick*)
Q_DECLARE_METATYPE(TemporalTick*)
Q_DECLARE_METATYPE(ExecutionModel*)
Q_DECLARE_METATYPE(Tick*)
