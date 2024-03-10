#include "calculator_model.h"

/**
 * Initializes the operations map with the corresponding lambda functions.
 */
void RPNModel::initOperations() {
  operations[COS_CHAR] = [this] {
    return solveOneParamFunc(
        std::bind(&RPNModel::cos, this, std::placeholders::_1));
  };
  operations[SIN_CHAR] = [this] {
    return solveOneParamFunc(
        std::bind(&RPNModel::sin, this, std::placeholders::_1));
  };
  operations[TAN_CHAR] = [this] {
    return solveOneParamFunc(
        std::bind(&RPNModel::tan, this, std::placeholders::_1));
  };
  operations[ARCCOS_CHAR] = [this] {
    return solveOneParamFunc(
        std::bind(&RPNModel::arccos, this, std::placeholders::_1));
  };
  operations[ARCSIN_CHAR] = [this] {
    return solveOneParamFunc(
        std::bind(&RPNModel::arcsin, this, std::placeholders::_1));
  };
  operations[ARCTAN_CHAR] = [this] {
    return solveOneParamFunc(
        std::bind(&RPNModel::arctan, this, std::placeholders::_1));
  };
  operations[SQRT_CHAR] = [this] {
    return solveOneParamFunc(
        std::bind(&RPNModel::sqrt, this, std::placeholders::_1));
  };
  operations[LOG_CHAR] = [this] {
    return solveOneParamFunc(
        std::bind(&RPNModel::log, this, std::placeholders::_1));
  };
  operations[LN_CHAR] = [this] {
    return solveOneParamFunc(
        std::bind(&RPNModel::ln, this, std::placeholders::_1));
  };
  operations['*'] = [this] {
    return solveTwoParamsFunc(std::bind(&RPNModel::multiply, this,
                                        std::placeholders::_1,
                                        std::placeholders::_2));
  };
  operations['/'] = [this] {
    return solveTwoParamsFunc(std::bind(
        &RPNModel::divide, this, std::placeholders::_1, std::placeholders::_2));
  };
  operations['^'] = [this] {
    return solveTwoParamsFunc(std::bind(
        &RPNModel::power, this, std::placeholders::_1, std::placeholders::_2));
  };
  operations[MOD_CHAR] = [this] {
    return solveTwoParamsFunc(std::bind(
        &RPNModel::mod, this, std::placeholders::_1, std::placeholders::_2));
  };
  operations['+'] = [this] {
    return solveTwoParamsFunc(std::bind(
        &RPNModel::plus, this, std::placeholders::_1, std::placeholders::_2));
  };
  operations['-'] = [this] {
    return solveTwoParamsFunc(std::bind(
        &RPNModel::minus, this, std::placeholders::_1, std::placeholders::_2));
  };
  operations[UNARY_MINUS_CHAR] = [this] {
    return solveOneParamFunc(
        std::bind(&RPNModel::unary_minus, this, std::placeholders::_1));
  };
}
/**
 * Solves a function that takes one parameter.
 * @param op The function to solve.
 * @return The result of the function.
 */
double RPNModel::solveOneParamFunc(const std::function<double(double)>& op) {
  double value = dStack.top();
  dStack.pop();
  return op(value);
}
/**
 * Solves a function that takes two parameters.
 * @param op The function to solve.
 * @return The result of the function.
 */
double RPNModel::solveTwoParamsFunc(
    const std::function<double(double, double)>& op) {
  double value2 = dStack.top();
  dStack.pop();
  double value1 = dStack.top();
  dStack.pop();
  return op(value1, value2);
}
/**
 * Checks if the last character in the RPN line is part of a double.
 * If it is, adds a space to the end of the line.
 */
void RPNModel::spaceCheck() {
  if (Support::isDoublePart(rpnline.back())) {
    rpnline.push_back(' ');
  }
}
/**
 * Pops the top element from the cStack and appends it to the rpnline.
 * If endLine is false, a space character is also appended to the rpnline.
 *
 * @param endLine Indicates whether to append a space character to the rpnline.
 */
void RPNModel::cStackPop(bool endLine = false) {
  rpnline.push_back(cStack.top());
  if (!endLine) {
    rpnline.push_back(' ');
  }
  cStack.pop();
}
/**
 * Adds a symbol to the RPN line.
 * @param sym The symbol to add.
 */
void RPNModel::symAdditionLine(const char& sym) { rpnline.push_back(sym); }
/**
 * Adds a symbol to the character stack.
 * @param sym The symbol to add.
 */
void RPNModel::symAdditionStack(const char& sym) { cStack.push(sym); }
/**
 * Pops characters from the character stack and adds them to the RPN line
 * until an open bracket is found.
 */
void RPNModel::stackPull() {
  spaceCheck();

  while (!cStack.empty() && !Support::isOpenBracket(cStack.top())) {
    cStackPop();
  }
  cStack.pop();
}
/**
 * Pops characters from the character stack and adds them to the RPN line
 * while the top character of the stack has a priority greater than or equal to
 * the given symbol.
 * @param sym The symbol to compare priorities with.
 */
void RPNModel::stackPullWhileOperator(const char& sym) {
  spaceCheck();
  while (!cStack.empty() &&
         Support::getPriority(cStack.top()) >= Support::getPriority(sym)) {
    cStackPop();
  }
}
/**
 * Moves the index by a given value.
 * @param index The index to move.
 * @param value The value to move the index by.
 */
void RPNModel::moveIndex(std::size_t& index, const int& value) {
  index += value;
}
/**
 * Recognizes a function based on the given symbol and adds it to the character
 * stack.
 * @param sym The symbol to recognize the function from.
 * @param index The current index in the line.
 */
void RPNModel::functionRecognition(const char& sym, std::size_t& index) {
  if (sym == BASE_COS_CHAR || sym == MOD_CHAR || sym == BASE_TAN_CHAR) {
    if (sym == BASE_COS_CHAR) {
      symAdditionStack(COS_CHAR);
    } else if (sym == MOD_CHAR) {
      symAdditionStack(MOD_CHAR);
    } else {
      symAdditionStack(TAN_CHAR);
    }
    moveIndex(index, 2);
  } else if (sym == BASE_SIN_SQRT_CHAR) {
    if (line[index + 1] == SQRT_CHAR) {
      symAdditionStack(SQRT_CHAR);
      moveIndex(index, 3);
    } else {
      symAdditionStack(SIN_CHAR);
      moveIndex(index, 2);
    }
  } else if (sym == BASE_ARC_CHAR) {
    if (line[index + 3] == COS_CHAR) {
      symAdditionStack(ARCCOS_CHAR);
    } else if (line[index + 3] == SIN_CHAR) {
      symAdditionStack(ARCSIN_CHAR);
    } else {
      symAdditionStack(ARCTAN_CHAR);
    }
    moveIndex(index, 5);
  } else {
    if (line[index + 1] == LN_CHAR) {
      symAdditionStack(LN_CHAR);
      moveIndex(index, 1);
    } else {
      symAdditionStack(LOG_CHAR);
      moveIndex(index, 2);
    }
  }
}
/**
 * Reads a line of input and processes it according to the Reverse Polish
 * Notation (RPN) algorithm.
 *
 * @return true if the line contains the variable 'x', false otherwise.
 */
bool RPNModel::readLine() {
  bool xInLine = false;
  for (std::size_t index = 0; index < line.size(); index++) {
    char sym = line[index];
    if (Support::isDoublePart(sym)) {
      if (sym == 'x') {
        xInLine = true;
      }
      symAdditionLine(sym);
    } else if (Support::isOpenBracket(sym)) {
      symAdditionStack(sym);
    } else if (Support::isCloseBracket(sym)) {
      stackPull();
    } else if (Support::isFunctionSym(sym)) {
      spaceCheck();
      functionRecognition(sym, index);
    } else if (Support::isUnaryMinus(line, index)) {
      symAdditionStack(UNARY_MINUS_CHAR);
    } else if (Support::isOperator(sym)) {
      stackPullWhileOperator(sym);
      cStack.push(sym);
    }
  }
  if (cStack.size() > 0) {
    spaceCheck();
  }
  while (!cStack.empty()) {
    cStackPop(cStack.size() == 1);
  }
  return xInLine;
}
/**
 * Splits the RPN line into tokens.
 */
void RPNModel::splitLine() {
  std::string token;
  std::istringstream tokenStream(rpnline);
  while (std::getline(tokenStream, token, DELIMITER)) {
    rpnSplited.push_back(token);
  }
}
/**
 * Solves the RPN line.
 * @return The result of the calculation.
 */
double RPNModel::solveRPN() {
  splitLine();
  for (const auto& token : rpnSplited) {
    if (token.length() > 1 || Support::isDoublePart(token[0])) {
      dStack.push(std::stof(token));
    } else {
      double answer = findFunction(token[0]);
      dStack.push(answer);
    }
  }
  return dStack.top();
}
/**
 * Finds the function corresponding to the given symbol and solves it.
 * @param sym The symbol of the function to find.
 * @return The result of the function, or 0.0 if the function was not found.
 */
double RPNModel::findFunction(const char& sym) {
  auto it = operations.find(sym);
  if (it != operations.end()) {
    return it->second();
  }
  return 0.0;
}

/**
 * @brief Get the default line of the RPNModel.
 *
 * @return std::string The default line.
 */
std::string RPNModel::getDefaultLine() { return line; }
/**
 * @brief Get the RPN line.
 *
 * @return std::string The RPN line.
 */
std::string RPNModel::getRPNLine() { return rpnline; }
/**
 * Sets the input line for the RPNModel.
 *
 * @param line The input line to be set.
 */
void RPNModel::inputLine(const std::string& line) { this->line = line; }
/**
 * @brief Clears the RPNModel by resetting all internal data structures.
 */
void RPNModel::clear() {
  line.clear();
  rpnline.clear();
  rpnSplited.clear();
  while (!cStack.empty()) {
    cStack.pop();
  }
  while (!dStack.empty()) {
    dStack.pop();
  }
}
/**
 * @brief Represents a sequence of characters.
 *
 * The std::string class is a container that holds and manipulates a sequence of
 * characters. It provides various member functions to perform operations on
 * strings, such as finding characters, replacing characters, and concatenating
 * strings.
 */
std::string GraphModel::replaceX(std::string line, double value) {
  std::ostringstream ss;
  ss << value;
  std::size_t found = line.find('x');
  while (found != std::string::npos) {
    line.replace(found, 1, ss.str());
    found = line.find('x', found + ss.str().length());
  }
  return line;
}

/**
 * @brief Represents a collection of points on a graph.
 *
 * The points are represented as pairs of double values, where the first value
 * represents the x-coordinate and the second value represents the y-coordinate.
 */
std::vector<std::pair<double, double>> GraphModel::getGraphPoints(
    const std::string& line, RPNModel* model) {
  std::vector<std::pair<double, double>> points;
  for (double x = -100; x <= 100; x += 0.25) {
    double pi = 3.14159265358979323846;
    double x_mod_pi = fmod(x, pi);
    if (std::abs(x_mod_pi - pi / 2) < 0.15 ||
        std::abs(x_mod_pi + pi / 2) < 0.15) {
      if (!points.empty()) {
        points.push_back(
            std::make_pair(std::numeric_limits<double>::quiet_NaN(),
                           std::numeric_limits<double>::quiet_NaN()));
      }
      continue;
    }

    std::string newLine = replaceX(line, x);
    model->clear();
    model->inputLine(newLine);
    model->readLine();
    double y = model->solveRPN();
    if (std::isfinite(y) && std::abs(y) < 1e6) {
      points.push_back(std::make_pair(x, y));
    } else {
      points.push_back(
          std::make_pair(std::numeric_limits<double>::quiet_NaN(),
                         std::numeric_limits<double>::quiet_NaN()));
    }
  }
  return points;
}