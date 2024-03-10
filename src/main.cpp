#include <QApplication>

#include "controller/calculator_controller.h"
#include "model/calculator_model.h"
#include "view/creditui.h"
#include "view/depositui.h"
#include "view/mainwindow.h"

int main(int argc, char *argv[]) {
  CalculatorController controller;
  QApplication a(argc, argv);
  MainWindow view;
  creditUi creditView;
  DepositUI depositView;
  creditView.setController(&controller);
  depositView.setController(&controller);
  view.setController(&controller);
  controller.setView(&view);
  controller.setCreditView(&creditView);
  controller.setDepositView(&depositView);
  RPNModel model;
  controller.setModel(&model);
  view.loadStyle();
  view.show();
  return a.exec();
}