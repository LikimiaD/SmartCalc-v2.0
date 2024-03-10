#include "calculator_controller.h"

bool CalculatorController::isFunction(const char& sym) {
  return sym == COS_CHAR || sym == SIN_CHAR || sym == TAN_CHAR ||
         sym == LOG_CHAR || sym == LN_CHAR || sym == SQRT_CHAR ||
         sym == ARCCOS_CHAR || sym == ARCSIN_CHAR || sym == ARCTAN_CHAR ||
         sym == MOD_CHAR;
}

void CalculatorController::equalInput(const char& sym) {
  std::string equal = view->getEqual();
  if (Support::isOperator(sym)) {
    addOperator(equal, sym);
  } else if (Support::isDoublePart(sym)) {
    addValue(equal, sym);
  } else if (isFunction(sym)) {
    addFunction(equal, sym);
  }
  view->setEqual(equal);
}

void CalculatorController::addOperator(std::string& line, const char sym) {
  if (!line.empty()) {
    char charLeft = line.back();
    if (sym == '-' &&
        (Support::isOperator(charLeft) || Support::isOpenBracket(charLeft) ||
         line.length() == 0)) {
      line += "(-";
    } else if (!Support::isOperator(charLeft) || sym != '-') {
      line += sym;
    }
  } else {
    if (sym == '-') {
      line += "(-";
    }
  }
}
void CalculatorController::addValue(std::string& line, const char sym) {
  char charLeft = line[line.length() - 1];
  if (line.length() > 0) {
    if (sym == '0' && charLeft == '/') {
      return;
    } else if (charLeft == '0' && sym != '.') {
      if (line.find('.') == std::string::npos) {
        line += '.';
      }
      line += sym;
    } else if (charLeft == '.' && sym == '.') {
      return;
    } else {
      line += sym;
    }
  } else {
    if (sym == '.') {
      line += '0';
      line += sym;
    } else if (sym == '0') {
      line += sym;
    } else {
      line += sym;
    }
  }
}
void CalculatorController::addFunction(std::string& line, const char sym) {
  const std::string modStr = "mod";
  if (line.length() >= modStr.length() &&
      line.substr(line.length() - modStr.length()) == modStr &&
      sym == MOD_CHAR) {
    return;
  }

  switch (sym) {
    case COS_CHAR:
      line.append("cos(");
      break;
    case SIN_CHAR:
      line.append("sin(");
      break;
    case TAN_CHAR:
      line.append("tan(");
      break;
    case LOG_CHAR:
      line.append("log(");
      break;
    case LN_CHAR:
      line.append("ln(");
      break;
    case SQRT_CHAR:
      line.append("sqrt(");
      break;
    case ARCCOS_CHAR:
      line.append("arccos(");
      break;
    case ARCSIN_CHAR:
      line.append("arcsin(");
      break;
    case ARCTAN_CHAR:
      line.append("arctan(");
      break;
    case MOD_CHAR:
      line.append(modStr);
      break;
    default:
      break;
  }
}
void CalculatorController::clearUI() {
  view->setEqual("");
  view->setAnswer("");
  model->clear();
}
void CalculatorController::addX(const char& sym) {
  std::string equal = view->getEqual();
  if (!equal.empty()) {
    char lastChar = equal.back();
    if (isdigit(lastChar) || lastChar == ')' || lastChar == 'x') {
      equal += '*';
    } else if (lastChar == '.') {
      equal += "0*";
    }
  }
  equal += sym;
  view->setEqual(equal);
}
void CalculatorController::addBracket() {
  std::string equal = view->getEqual();
  std::size_t openBrackets = std::count(equal.begin(), equal.end(), '(');
  std::size_t closeBrackets = std::count(equal.begin(), equal.end(), ')');
  if (openBrackets <= closeBrackets) {
    if (!equal.empty() &&
        (isdigit(equal.back()) || equal.back() == 'x' || equal.back() == ')')) {
      equal += '*';
    }
    equal += '(';
  } else if (openBrackets > closeBrackets &&
             (isdigit(equal.back()) || equal.back() == 'x' ||
              equal.back() == ')')) {
    equal += ')';
  }

  view->setEqual(equal);
}
void CalculatorController::calculate() {
  std::string equal = view->getEqual();
  std::string answer = "GRAPH";
  if (equal.find('x') == std::string::npos) {
    model->clear();
    model->inputLine(equal);
    model->readLine();
    answer = std::to_string(model->solveRPN());
  } else {
    makeGraph(equal);
  }
  view->setAnswer(answer);
}
void CalculatorController::makeGraph(std::string& line) {
  auto points = GraphModel::getGraphPoints(line, model);
  auto graphWidget = new GraphWidget();
  graphWidget->setPoints(points);
  graphWidget->resize(500, 500);
  graphWidget->show();
}
void CalculatorController::showCredit() { creditView->show(); }
void CalculatorController::showDeposit() { depositView->show(); }