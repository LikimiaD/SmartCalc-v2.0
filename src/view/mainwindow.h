#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QFile>
#include <QGraphicsDropShadowEffect>
#include <QMainWindow>

class CalculatorController;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT
 private:
  Ui::MainWindow* ui;
  CalculatorController* controller;
  void makeConnections();
  void loadSVG();
  QString getStyleSheet();

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

  void setController(CalculatorController* controller) {
    this->controller = controller;
  }
  void loadStyle();

  std::string getEqual();
  void setEqual(const std::string& str);
  void setAnswer(const std::string& str);
};
#endif  // MAINWINDOW_H
