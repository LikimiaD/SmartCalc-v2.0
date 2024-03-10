#ifndef SRC_MODEL_CALCULATOR_MODEL_H_
#define SRC_MODEL_CALCULATOR_MODEL_H_

#include <cctype>
#include <cmath>
#include <cstddef>
#include <functional>
#include <iostream>  //! USELESS
#include <limits>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#define BASE_COS_CHAR 'c'
#define BASE_SIN_SQRT_CHAR 's'
#define BASE_ARC_CHAR 'a'
#define BASE_LOG_LN_CHAR 'l'
#define BASE_TAN_CHAR 't'

#define COS_CHAR BASE_COS_CHAR
#define SIN_CHAR BASE_SIN_SQRT_CHAR
#define TAN_CHAR BASE_TAN_CHAR
#define LOG_CHAR BASE_LOG_LN_CHAR
#define MOD_CHAR 'm'
#define SQRT_CHAR 'q'
#define ARCCOS_CHAR 'o'
#define ARCSIN_CHAR 'i'
#define ARCTAN_CHAR 'a'
#define LN_CHAR 'n'
#define UNARY_MINUS_CHAR 'u'

#define DELIMITER ' '

/**
 * @brief The Support class provides utility functions for the calculator model.
 */
class Support {
 public:
  /**
   * @brief Checks if a character is a valid part of a double number.
   * @param sym The character to check.
   * @return True if the character is a digit, '.', or 'x'; false otherwise.
   */
  static bool isDoublePart(const char& sym) {
    return isdigit(sym) || sym == '.' || sym == 'x';
  }
  /**
   * @brief Checks if a character is an opening bracket.
   * @param sym The character to check.
   * @return True if the character is '(', false otherwise.
   */
  static bool isOpenBracket(const char& sym) { return sym == '('; }
  /**
   * @brief Checks if a character is a closing bracket.
   * @param sym The character to check.
   * @return True if the character is ')', false otherwise.
   */
  static bool isCloseBracket(const char& sym) { return sym == ')'; }
  /**
   * @brief Checks if a character is a function symbol.
   * @param sym The character to check.
   * @return True if the character is a function symbol, false otherwise.
   */
  static bool isFunctionSym(const char& sym) {
    return sym == BASE_COS_CHAR || sym == BASE_SIN_SQRT_CHAR ||
           sym == BASE_ARC_CHAR || sym == BASE_LOG_LN_CHAR ||
           sym == BASE_TAN_CHAR || sym == MOD_CHAR;
  }
  /**
   * @brief Checks if a character is a unary minus symbol.
   * @param line The string containing the character.
   * @param index The index of the character in the string.
   * @return True if the character is a unary minus symbol, false otherwise.
   */
  static bool isUnaryMinus(const std::string& line, const std::size_t& index) {
    return (!isdigit(line[index - 1]) || index == 0 ||
            line[index - 1] == '(') &&
           line[index] == '-' &&
           (isdigit(line[index + 1]) || isFunctionSym(line[index + 1])) &&
           line[index - 1] != ')';
  }
  /**
   * @brief Checks if a character is an operator symbol.
   * @param sym The character to check.
   * @return True if the character is an operator symbol, false otherwise.
   */
  static bool isOperator(const char& sym) {
    return sym == '+' || sym == '-' || sym == '^' || sym == '*' || sym == '/';
  }
  /**
   * @brief Gets the priority of an operator symbol.
   * @param sym The operator symbol.
   * @return The priority of the operator symbol.
   */
  static int getPriority(const char& sym) {
    static const std::unordered_map<char, int> priorityMap = {
        {UNARY_MINUS_CHAR, 6},
        {'^', 5},
        {COS_CHAR, 4},
        {SIN_CHAR, 4},
        {TAN_CHAR, 4},
        {ARCCOS_CHAR, 4},
        {ARCSIN_CHAR, 4},
        {ARCTAN_CHAR, 4},
        {SQRT_CHAR, 4},
        {LOG_CHAR, 4},
        {LN_CHAR, 4},
        {'*', 3},
        {'/', 3},
        {MOD_CHAR, 3},
        {'+', 2},
        {'-', 2}};

    auto it = priorityMap.find(sym);
    if (it != priorityMap.end()) {
      return it->second;
    }

    return 1;
  }
};

/**
 * @brief The Properties class represents the properties of a calculator model.
 *
 * This class stores various properties related to the calculator model, such as
 * the input line, the reverse Polish notation (RPN) line, the character stack,
 * the double stack, the RPN split, and the operations map.
 */
class Properties {
 public:
  Properties() : line("") {}
  explicit Properties(std::string line) : line(std::move(line)) {}
  ~Properties() {}

 protected:
  std::string line;
  std::string rpnline;
  std::stack<char> cStack;
  std::stack<double> dStack;
  std::vector<std::string> rpnSplited;
  std::unordered_map<char, std::function<double()>> operations;
};

/**
 * @brief The RPNModel class represents a Reverse Polish Notation (RPN)
 * calculator model.
 *
 * This class inherits from the Properties class and provides functionality for
 * reading an input line, solving the RPN expression, taking the answer, and
 * splitting the line into tokens. It also includes various helper functions for
 * performing mathematical operations.
 */
class RPNModel : private Properties {
 public:
  RPNModel() : Properties() { initOperations(); };
  explicit RPNModel(std::string line) : Properties(std::move(line)) {
    initOperations();
  }
  ~RPNModel() {}

  void inputLine(const std::string& line);

  bool readLine();    //! Public
  double solveRPN();  //! Public
  void takeAnswer();  //! Public
  void splitLine();   //! Public
  void clear();       //! Public

  std::string getDefaultLine();
  std::string getRPNLine();

 private:
  void spaceCheck();

  void cStackPop(bool endLine);

  void initOperations();

  void symAdditionLine(const char& sym);
  void symAdditionStack(const char& sym);
  void stackPull();
  void stackPullWhileOperator(const char& sym);
  void moveIndex(std::size_t& index, const int& value);

  double findFunction(const char& sym);
  void functionRecognition(const char& sym, std::size_t& index);

  double solveTwoParamsFunc(const std::function<double(double, double)>& op);
  double solveOneParamFunc(const std::function<double(double)>& op);

  double cos(const double value) { return std::cos(value); }
  double sin(const double& value) { return std::sin(value); }
  double tan(const double& value) { return std::tan(value); }
  double arccos(const double& value) { return std::acos(value); }
  double arcsin(const double& value) { return std::asin(value); }
  double arctan(const double& value) { return std::atan(value); }
  double log(const double& value) { return std::log10(value); }
  double ln(const double& value) { return std::log(value); }
  double sqrt(const double& value) { return std::sqrt(value); }
  double mod(const double& value1, const double& value2) {
    return std::fmod(value1, value2);
  }
  double plus(const double& value1, const double& value2) {
    return value1 + value2;
  }
  double minus(const double& value1, const double& value2) {
    return value1 - value2;
  }
  double divide(const double& value1, const double& value2) {
    return value1 / value2;
  }
  double multiply(const double& value1, const double& value2) {
    return value1 * value2;
  }
  double power(const double& value1, const double& value2) {
    return std::pow(value1, value2);
  }
  double unary_minus(const double& value) { return -value; }
};

class GraphModel {
 public:
  static std::string replaceX(std::string line, double value);
  static std::vector<std::pair<double, double>> getGraphPoints(
      const std::string& line, RPNModel* model);
};

#endif  // SRC_MODEL_CALCULATOR_MODEL_H_