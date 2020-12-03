#pragma once
#include <QObject>

class GraphRenderer
    : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString graph READ graph WRITE setGraph NOTIFY graphChanged)
  Q_PROPERTY(QString imagePath READ imagePath WRITE setImagePath NOTIFY imagePathChanged)
  QString m_graph;
  QString m_imagePath;

public:
  using QObject::QObject;

  QString graph() const;
  QString imagePath() const;

public slots:
  void setGraph(QString graph);
  void setImagePath(QString imagePath);

signals:
  void graphChanged(QString graph);
  void imagePathChanged(QString imagePath);
};
