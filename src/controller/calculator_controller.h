#ifndef SRC_CONTROLLER_CALCULATOR_CONTROLLER_H_
#define SRC_CONTROLLER_CALCULATOR_CONTROLLER_H_

#include <utility>

#include "../model/calculator_model.h"
#include "../view/creditui.h"
#include "../view/depositui.h"
#include "../view/graphwidget.h"
#include "../view/mainwindow.h"

class CalculatorController {
 public:
  CalculatorController()
      : view(nullptr),
        model(nullptr),
        creditView(nullptr),
        depositView(nullptr) {}

  void equalInput(const char& sym);
  void addX(const char& sym);
  void addBracket();
  void calculate();

  void setView(MainWindow* view) { this->view = view; }
  void setModel(RPNModel* model) { this->model = model; }
  void setCreditView(creditUi* creditView) { this->creditView = creditView; }
  void setDepositView(DepositUI* depositView) {
    this->depositView = depositView;
  }
  void showCredit();
  void showDeposit();

  void clearUI();

 private:
  MainWindow* view;
  RPNModel* model;
  creditUi* creditView;
  DepositUI* depositView;

  bool isFunction(const char& sym);
  void addOperator(std::string& line, const char sym);
  void addValue(std::string& line, const char sym);
  void addFunction(std::string& line, const char sym);
  void makeGraph(std::string& line);
};

#endif /* SRC_CONTROLLER_CALCULATOR_CONTROLLER_H_ */
