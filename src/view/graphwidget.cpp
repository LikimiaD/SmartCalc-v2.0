#include "graphwidget.h"

#include <QVBoxLayout>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

using namespace QtCharts;

GraphWidget::GraphWidget(QWidget *parent) : QWidget(parent), ui(nullptr) {
  QChart *chart = new QChart();
  chart->setTitle("Graph of the function");
  chart->legend()->hide();
  chart->createDefaultAxes();
  QChartView *chartView = new QChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);

  QVBoxLayout *layout = new QVBoxLayout(this);
  layout->addWidget(chartView);
}

GraphWidget::~GraphWidget() {}

void GraphWidget::setPoints(
    const std::vector<std::pair<double, double>> &points) {
  QChart *chart =
      static_cast<QChartView *>(layout()->itemAt(0)->widget())->chart();
  chart->removeAllSeries();

  QLineSeries *currentSeries = new QLineSeries();
  for (const auto &point : points) {
    if (std::isnan(point.second)) {
      if (!currentSeries->points().isEmpty()) {
        chart->addSeries(currentSeries);
        currentSeries = new QLineSeries();
      }
    } else {
      currentSeries->append(point.first, point.second);
    }
  }
  if (!currentSeries->points().isEmpty()) {
    chart->addSeries(currentSeries);
  }
  chart->createDefaultAxes();
}
