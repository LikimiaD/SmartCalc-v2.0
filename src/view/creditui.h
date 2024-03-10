#ifndef SRC_VIEW_CREDITUI_H_
#define SRC_VIEW_CREDITUI_H_

#include <QWidget>

class CalculatorController;

namespace Ui {
class creditUi;
}

class creditUi : public QWidget {
  Q_OBJECT
 private:
  Ui::creditUi* ui;
  CalculatorController* controller;

 public:
  explicit creditUi(QWidget* parent = nullptr);
  ~creditUi();
  void setController(CalculatorController* controller) {
    this->controller = controller;
  }
 private slots:
  void on_pushButton_clicked();
};

#endif /* SRC_VIEW_CREDITUI_H_ */
