#ifndef DEPOSITUI_H
#define DEPOSITUI_H

#include <QWidget>

class CalculatorController;

namespace Ui {
class DepositUI;
}

class DepositUI : public QWidget {
  Q_OBJECT
 private:
  Ui::DepositUI *ui;
  CalculatorController *controller;

 public:
  explicit DepositUI(QWidget *parent = nullptr);
  ~DepositUI();
  QVector<double> parseList(const QString &list);
  void setController(CalculatorController *controller) {
    this->controller = controller;
  }

 private slots:
  void on_pushButton_clicked();
};

#endif  // DEPOSITUI_H
