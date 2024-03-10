#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include <QtCharts>

namespace Ui {
class GraphWidget;
}

class GraphWidget : public QWidget {
  Q_OBJECT

 public:
  explicit GraphWidget(QWidget *parent = nullptr);
  ~GraphWidget();
  void setPoints(const std::vector<std::pair<double, double>> &points);

 private:
  Ui::GraphWidget *ui;
};

#endif  // GRAPHWIDGET_H
