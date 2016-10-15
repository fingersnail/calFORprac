#ifndef CALCULATIONEXCEPTION_H
#define CALCULATIONEXCEPTION_H
#include <stdexcept>

class CalException : public std::exception {
public:
    virtual const char * what() const throw() { return "计算发生错误"; }
};

class ExpressionErrorException : public CalException {
    virtual const char * what() const throw() { return "表达式错误"; }
};

class IllegalCharactorException : public ExpressionErrorException {
    virtual const char * what() const throw() { return "表达式含有非法字符"; }
};

class DecimalPointException : public ExpressionErrorException {
    virtual const char * what() const throw() { return "小数点使用错误"; }
};

class OperatorException : public ExpressionErrorException {
    virtual const char * what() const throw() { return "运算符使用错误"; }
};

class BracketNotMatchException : public ExpressionErrorException {
    virtual const char * what() const throw() { return "括号不匹配"; }
};

class ExpressionEndingException : public ExpressionErrorException {
    virtual const char * what() const throw() { return "表达式尾部错误"; }
};

class CalTimeException : public CalException {
    virtual const char * what() const throw() { return "计算时发生错误"; }
};

class PowerException : public CalTimeException {
    virtual const char * what() const throw() { return "指数计算无意义"; }
};

class LogException : public CalTimeException {
    virtual const char * what() const throw() { return "对数计算无意义"; }
};

class DividedByZeroException : public CalTimeException {
    virtual const char * what() const throw() { return "某个地方0成为了除数"; }
};
#endif // CALCULATIONEXCEPTION_H
