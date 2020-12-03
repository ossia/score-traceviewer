#include <GraphRenderer.hpp>
#include <QProcess>
#include <QFile>

QString GraphRenderer::graph() const
{
  return m_graph;
}

void GraphRenderer::setGraph(QString graph)
{
  if (m_graph == graph)
    return;

  {
    // write the graph to a file
    {
      QFile f{"/tmp/graph.dot"};
      if(f.open(QIODevice::WriteOnly)) {
        f.write(graph.toUtf8());
      }
    }

    // execute the dot process
    static int index = 0;
    QString imagePath = QString("/tmp/graph%1.png").arg(index++);
    QProcess::execute("/usr/bin/dot", {"/tmp/graph.dot", "-T", "png", QString("-o%1").arg(imagePath)});

    // tell Qt to reload the image
    setImagePath(imagePath);
  }

  m_graph = graph;
  emit graphChanged(m_graph);
}

QString GraphRenderer::imagePath() const
{
  return m_imagePath;
}

void GraphRenderer::setImagePath(QString imagePath)
{
  if(imagePath == m_imagePath)
    return;

  m_imagePath = imagePath;
  emit imagePathChanged(m_imagePath);
}
