#include "mainwindow.h"

#include "../controller/calculator_controller.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

QString MainWindow::getStyleSheet() {
  QFile file(":/css/style.qss");
  QString styleSheet;
  if (file.open(QFile::ReadOnly)) {
    styleSheet = QString::fromUtf8(file.readAll());
  } else {
    qDebug() << "Failed to open .qss file";
  }
  return styleSheet;
}

void MainWindow::makeConnections() {
  connect(ui->button_0, &QPushButton::clicked, this,
          [this]() { controller->equalInput('0'); });
  connect(ui->button_1, &QPushButton::clicked, this,
          [this]() { controller->equalInput('1'); });
  connect(ui->button_2, &QPushButton::clicked, this,
          [this]() { controller->equalInput('2'); });
  connect(ui->button_3, &QPushButton::clicked, this,
          [this]() { controller->equalInput('3'); });
  connect(ui->button_4, &QPushButton::clicked, this,
          [this]() { controller->equalInput('4'); });
  connect(ui->button_5, &QPushButton::clicked, this,
          [this]() { controller->equalInput('5'); });
  connect(ui->button_6, &QPushButton::clicked, this,
          [this]() { controller->equalInput('6'); });
  connect(ui->button_7, &QPushButton::clicked, this,
          [this]() { controller->equalInput('7'); });
  connect(ui->button_8, &QPushButton::clicked, this,
          [this]() { controller->equalInput('8'); });
  connect(ui->button_9, &QPushButton::clicked, this,
          [this]() { controller->equalInput('9'); });
  connect(ui->button_dot, &QPushButton::clicked, this,
          [this]() { controller->equalInput('.'); });
  connect(ui->button_plus, &QPushButton::clicked, this,
          [this]() { controller->equalInput('+'); });
  connect(ui->button_minus, &QPushButton::clicked, this,
          [this]() { controller->equalInput('-'); });
  connect(ui->button_power, &QPushButton::clicked, this,
          [this]() { controller->equalInput('^'); });
  connect(ui->button_multiplie, &QPushButton::clicked, this,
          [this]() { controller->equalInput('*'); });
  connect(ui->button_divide, &QPushButton::clicked, this,
          [this]() { controller->equalInput('/'); });
  connect(ui->button_cos, &QPushButton::clicked, this,
          [this]() { controller->equalInput(COS_CHAR); });
  connect(ui->button_sin, &QPushButton::clicked, this,
          [this]() { controller->equalInput(SIN_CHAR); });
  connect(ui->button_tan, &QPushButton::clicked, this,
          [this]() { controller->equalInput(TAN_CHAR); });
  connect(ui->button_acos, &QPushButton::clicked, this,
          [this]() { controller->equalInput(ARCCOS_CHAR); });
  connect(ui->button_asin, &QPushButton::clicked, this,
          [this]() { controller->equalInput(ARCSIN_CHAR); });
  connect(ui->button_atan, &QPushButton::clicked, this,
          [this]() { controller->equalInput(ARCTAN_CHAR); });
  connect(ui->button_ln, &QPushButton::clicked, this,
          [this]() { controller->equalInput(LN_CHAR); });
  connect(ui->button_log, &QPushButton::clicked, this,
          [this]() { controller->equalInput(LOG_CHAR); });
  connect(ui->button_sqrt, &QPushButton::clicked, this,
          [this]() { controller->equalInput(SQRT_CHAR); });
  connect(ui->button_mod, &QPushButton::clicked, this,
          [this]() { controller->equalInput(MOD_CHAR); });
  connect(ui->button_clear, &QPushButton::clicked, this,
          [this]() { controller->clearUI(); });
  connect(ui->button_x, &QPushButton::clicked, this,
          [this]() { controller->addX('x'); });
  connect(ui->button_bracket, &QPushButton::clicked, this,
          [this]() { controller->addBracket(); });
  connect(ui->button_equal, &QPushButton::clicked, this,
          [this]() { controller->calculate(); });
  connect(ui->button_credit, &QPushButton::clicked, this,
          [this]() { controller->showCredit(); });
  connect(ui->button_deposit, &QPushButton::clicked, this,
          [this]() { controller->showDeposit(); });
}

void MainWindow::loadSVG() {
  QIcon credit_icon(":/svg/credit.svg");
  QIcon deposit_icon(":/svg/deposit.svg");

  ui->button_credit->setObjectName("credit_button");
  ui->button_credit->setIcon(credit_icon);
  ui->button_credit->setIconSize(QSize(50, 50));
  ui->button_deposit->setObjectName("deposit_button");
  ui->button_deposit->setIcon(deposit_icon);
  ui->button_deposit->setIconSize(QSize(50, 50));
}

void MainWindow::loadStyle() {
  makeConnections();
  this->setStyleSheet(getStyleSheet());
  QGraphicsDropShadowEffect *shadowEffectWhite =
      new QGraphicsDropShadowEffect();
  QGraphicsDropShadowEffect *shadowEffectBlack =
      new QGraphicsDropShadowEffect();
  shadowEffectWhite->setBlurRadius(8);
  shadowEffectWhite->setXOffset(0);
  shadowEffectWhite->setYOffset(0);
  shadowEffectWhite->setColor(Qt::gray);

  shadowEffectBlack->setBlurRadius(25);
  shadowEffectBlack->setXOffset(0);
  shadowEffectBlack->setYOffset(0);
  shadowEffectBlack->setColor(Qt::black);

  ui->app_window->setObjectName("app_window");
  ui->app_static->setObjectName("app_static");
  ui->app_static->setGraphicsEffect(shadowEffectBlack);

  QPushButton *base_buttons[] = {
      ui->button_0,      ui->button_1,       ui->button_2,
      ui->button_3,      ui->button_4,       ui->button_5,
      ui->button_6,      ui->button_7,       ui->button_8,
      ui->button_9,      ui->button_plus,    ui->button_minus,
      ui->button_mod,    ui->button_dot,     ui->button_multiplie,
      ui->button_divide, ui->button_bracket, ui->button_power,
      ui->button_x,
  };
  for (QPushButton *button : base_buttons) {
    button->setObjectName("button");
    QGraphicsDropShadowEffect *effectCopy = new QGraphicsDropShadowEffect();
    effectCopy->setBlurRadius(shadowEffectWhite->blurRadius());
    effectCopy->setXOffset(shadowEffectWhite->xOffset());
    effectCopy->setYOffset(shadowEffectWhite->yOffset());
    effectCopy->setColor(shadowEffectWhite->color());
    button->setGraphicsEffect(effectCopy);
  }

  QPushButton *func_buttons[] = {
      ui->button_sin,  ui->button_cos,  ui->button_tan,
      ui->button_acos, ui->button_asin, ui->button_atan,
      ui->button_ln,   ui->button_log,  ui->button_sqrt,
  };
  for (QPushButton *button : func_buttons) {
    button->setObjectName("func_button");
  }
  ui->button_equal->setObjectName("equal_button");
  ui->button_clear->setObjectName("clear_button");

  ui->answer_box->setObjectName("answer_box");
  ui->answer_box->setAlignment(Qt::AlignRight);
  ui->equal_box->setObjectName("equal_box");
  ui->equal_box->setAlignment(Qt::AlignRight);

  loadSVG();
}

std::string MainWindow::getEqual() {
  return ui->equal_box->text().toStdString();
}

void MainWindow::setEqual(const std::string &str) {
  ui->equal_box->setText(QString::fromStdString(str));
}

void MainWindow::setAnswer(const std::string &str) {
  ui->answer_box->setText(QString::fromStdString(str));
}
